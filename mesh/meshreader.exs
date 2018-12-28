# File.stream!("D:\\bunny.mesh") |>
# Stream.map( &(String.replace(&1, "\n", "")) ) |>
# Stream.with_index |>
# Enum.each( fn({contents, line_num}) ->
#   IO.puts "#{line_num + 1} #{contents}"
# end)

# {:ok, file} = File.open("D:\\bunny.mesh", [:read, :write])
# IO.read(file, :all) |> IO.inspect

# If one file can contain multiple meshes
# %{
#     status: triangles / xyz_with_index / nothing
#     0 -> %{
#         vertices: 3, 
#         triangles: 1,
#         xyz_with_index: %{0 -> {x,y,z}, 1-> {x,y,z}, ...},
#         triangles: [{i1, i2, i3}, {i1, i2, i3}]
#     }
# }

# First, lets only do it for one mesh
#         %{
    #         number_vertices: 3, 
    #         number_triangles: 1,
    #         xyz_with_index: %{0 -> {x,y,z}, 1-> {x,y,z}, ...},
    #         triangles: [{i1, i2, i3}, {i1, i2, i3}]
    #     }

# text =  File.read! "D:\\bunny.mesh"
defmodule MeshReader do
    def readValues(filename \\ "D:\\lucy.mesh") do
        # text = "1\n0 0 0\n1.5 2.1 3.2\n-1.2 1.1 5.6\n1\n0 1 2"
        text =  File.read! filename
        list = String.split(text, "\n")
        startstate = %{status: :start, xyz_with_index: %{}, triangles: []}
        readFileLines(List.flatten(list), startstate, 0)
    end

    def readFileLines([head | tail], %{status: status} = state, offset) when status == :triangles do
        nstate = case String.split(head) |> processLine(state.status, offset) do
            {:triangle, offsettuple} -> %{state | triangles: [offsettuple | state.triangles]}
            :skip -> 
                IO.puts "Skipping this line.."
                state     
        end
        readFileLines(tail, nstate, offset)
    end
    
    def readFileLines([head | tail], %{status: status} = state, offset) when status == :xyz_vertices or status == :start do
        {nstate, offset} = case String.split(head) |> processLine(state.status, offset) do
            {:startVertices, number_vertices} -> 
                IO.puts "starting status switch to xyz vertices: "<> Integer.to_string(number_vertices)
                {%{Map.put(state, :number_vertices, number_vertices) | status: :xyz_vertices}, 0}
            {:startTriangles, number_triangles} ->
                IO.puts "starting status switch to triangle associations: "<> Integer.to_string(number_triangles)
                {%{Map.put(state, :number_triangles, number_triangles) | status: :triangles}, 0}
            {offset, xyz_tuple} -> {%{state | xyz_with_index: Map.put(state.xyz_with_index, offset, xyz_tuple)}, offset+1}
        end 
        readFileLines(tail, nstate, offset)
    end

    def readFileLines([], state, _offset), do: state

    def processLine([number|_] = line, status, _offset) when length(line) == 1 do
        number = String.to_integer number
        case status do
            :triangles -> IO.puts "Something went wrong!!!! More mesh collections in the same file"
            :xyz_vertices -> 
                {:startTriangles, number}
            :start -> 
                {:startVertices, number}
        end
    end
    def processLine([n1,n2,n3|_] = line, status, offset) when length(line) == 3 do
        case status do
            :triangles -> 
                {:triangle, {String.to_integer(n1), String.to_integer(n2), String.to_integer(n3)}}
            :xyz_vertices -> 
                {offset, {n1, n2, n3}}
            :start -> 
                IO.puts "Something went wrong!!!! invalid start of file"
        end
    end
    def processLine(_,_,_), do: :skip
end
:observer.start
IO.inspect MeshReader.readValues()

defmodule MeshReader do
    def readValues(filename \\ "D:\\bunny.mesh") do
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


defmodule Trianglesorter do
    def sort_triangle_arr(triangles, vertices, axis) when is_number(axis) and axis<3 do
        Enum.sort_by(triangles, 
            fn triangle -> 
                sorted_triangle_points = Trianglesorter.sort_tp_by_axis(triangle, vertices, axis)
                first_sorted_point = elem(sorted_triangle_points,0)
                point_data = Map.get(vertices, first_sorted_point)
                elem(point_data,axis) |> Float.parse() |> elem(0) 
            end)

    end

    def sort_tp_by_axis(triangle, vertices, axis) when is_number(axis) and axis < 3 do
        Tuple.to_list(triangle) |> Enum.sort_by(
            &( 
                elem(Map.get(vertices,&1), axis) |> String.to_float() 
            )) |> List.to_tuple()
    end 

    # def sort_tp_by_axis(a,b,c) when is_atom(c), do: sort_tp_by_axis(a,b,"0"|>String.to_integer)

    def get_min_max_from_triangles(triangles, vertices) do
        triangles = for triangle <- triangles, into: [] do
            Tuple.to_list triangle
        end
        triangles = List.flatten triangles
        start = %{
            minx: nil,
            miny: nil,
            minz: nil,
            maxx: nil,
            maxy: nil,
            maxz: nil,
        }
        Enum.reduce(triangles, start, fn x,acc -> 
            triangle_x = elem(Map.get(vertices, x),0) |> String.to_float
            triangle_y = elem(Map.get(vertices, x),1) |> String.to_float
            triangle_z = elem(Map.get(vertices, x),2) |> String.to_float
            minx = acc.minx
            maxx = acc.maxx
            miny = acc.miny
            maxy = acc.maxy
            minz = acc.minz
            maxz = acc.maxz
            minx = cond do
                minx == nil -> nil
                is_binary(minx) -> String.to_float(minx)  
                is_number(minx) -> minx 
            end
            maxx = cond do
                maxx == nil -> nil
                is_binary(maxx) -> String.to_float(maxx)  
                is_number(maxx) -> maxx 
            end
            miny = cond do
                miny == nil -> nil
                is_binary(miny) -> String.to_float(miny)  
                is_number(miny) -> miny 
            end
            maxy = cond do
                maxy == nil -> nil
                is_binary(maxy) -> String.to_float(maxy)  
                is_number(maxy) -> maxy 
            end
            minz = cond do
                minz == nil -> nil
                is_binary(minz) -> String.to_float(minz)  
                is_number(minz) -> minz 
            end
            maxz = cond do
                maxz == nil -> nil
                is_binary(maxz) -> String.to_float(maxz)  
                is_number(maxz) -> maxz 
            end
        
            acc = cond do
                minx == nil -> %{acc | minx: triangle_x}
                triangle_x <= minx -> %{acc | minx: triangle_x} 
                true -> acc   
            end
            acc = cond do
                maxx == nil -> %{acc | maxx: triangle_x}
                triangle_x > maxx -> %{acc | maxx: triangle_x} 
                true -> acc   
            end
            acc = cond do
                miny == nil -> %{acc | miny: triangle_y}
                triangle_y <= miny -> %{acc | miny: triangle_y}  
                true -> acc     
            end
            acc = cond do
                maxy == nil -> %{acc | maxy: triangle_y}
                triangle_y > maxy -> %{acc | maxy: triangle_y}    
                true -> acc   
            end
            acc = cond do
                minz == nil -> %{acc | minz: triangle_z}
                triangle_z <= minz -> %{acc | minz: triangle_z} 
                true -> acc      
            end
            acc = cond do
                maxz == nil -> %{acc | maxz: triangle_z}
                triangle_z > maxz -> %{acc | maxz: triangle_z}  
                true -> acc     
            end
            acc
        end)
    end

    def print_tp(triangle, vertices) do
        x = elem(triangle, 0)
        y = elem(triangle, 1)
        z = elem(triangle, 2)
        {x1,x2,x3} = Map.get(vertices, x)
        {y1,y2,y3} = Map.get(vertices, y)
        {z1,z2,z3} = Map.get(vertices, z)
        IO.puts "p1 = \t x:#{x1}\ty:#{x2}\tz:#{x3}\n"<>
            "p2 = \t x:#{y1}\ty:#{y2}\tz:#{y3}\n"<>
            "p3 = \t x:#{z1}\ty:#{z2}\tz:#{z3}\t\n\n"
    end
end

defmodule MeshOptimizer do
    def optimizeData(data) when data |> is_map do
        optimized = %{
            bboxes: %{},
            xyz_with_index: data.xyz_with_index,
            tasks: [box: %{id: 0,parent: nil, triangles: data.triangles}]
        }
        bboxCreator(optimized)
    end

    defp find_dimensions(triangles, vertices) do
        t = Trianglesorter.get_min_max_from_triangles(triangles, vertices)
        diffx = t.maxx - t.minx
        diffy = t.maxy - t.miny
        diffz = t.maxz - t.minz
        {diffx,diffy,diffz}
    end

    defp find_largest_axis(triangles, vertices) do
        {dx,dy,dz} = find_dimensions(triangles, vertices)
        cond do
            (dx >= dy) && (dx >=dz) -> 0
            (dy >= dx) && (dy >=dz) -> 1
            (dz >= dx) && (dz >=dy) -> 2
        end
    end

    def bboxCreator(%{bboxes: boxes, tasks: []}= data) do
        data
    end
    # When there is no parent
    def bboxCreator(%{bboxes: boxes, tasks: [box: %{id: 0, parent: nil, triangles: triangles}] = tasks} =data)  when length(tasks) == 1 do
        [box: box] = data.tasks
        cond do
            length(triangles)<=150 -> 
                %{data | bboxes: %{box.id => box}}
            length(triangles)>150 ->
                axis = find_largest_axis(triangles, data.xyz_with_index)
                sorted = Trianglesorter.sort_triangle_arr(triangles, data.xyz_with_index, axis)
                median = (length(triangles) / 2) |> round
                p1 = Enum.slice triangles, 0, median
                p2 = Enum.slice triangles, median..-1
                task1 = %{id: 1, parent: box.id, triangles: p1}
                task2 = %{id: 2, parent: box.id, triangles: p2}
                bboxCreator(%{data | tasks: [task1, task2], bboxes: Map.put(boxes, box.id, Map.delete(box, :triangles))})
        end
    end
    # Normal iteration
    def bboxCreator(%{bboxes: boxes, tasks: [current_task | remainder]} =data) do
        triangles = current_task.triangles
        cond do
            length(triangles)<=150 ->
                updated_bboxes= Map.put(boxes, current_task.id, current_task)
                bboxCreator(%{data | tasks: remainder, bboxes: updated_bboxes})
            length(triangles)>150 -> 
                axis = find_largest_axis(triangles, data.xyz_with_index)
                sorted = Trianglesorter.sort_triangle_arr(triangles, data.xyz_with_index, axis)
                median = (length(triangles) / 2) |> round
                p1 = Enum.slice triangles, 0, median
                p2 = Enum.slice triangles, median..-1
                index = length(Map.keys(boxes)) + length(data.tasks)
                task1 = %{id: index+1, parent: current_task.id, triangles: p1}
                task2 = %{id: index+2, parent: current_task.id, triangles: p2}
                cleaned_task =  Map.delete(current_task, :triangles)
                bboxCreator(%{data | tasks: [task1, task2 | remainder], bboxes: Map.put(boxes, current_task.id, cleaned_task)})
        end
    end
end

defmodule MeshWriter do
    def writeToFile(infile, outfile) when is_binary(infile) and is_binary(outfile) do
        
    end

    def writeToFile() do
        data =  MeshReader.readValues()
        temp = MeshOptimizer.optimizeData data
        newdata = transformTrianglePointsInBoxes(temp)
        Map.delete(newdata, :xyz_with_index) |> Map.delete(:triangles)
    end

    def transformTrianglePointsInBoxes(data) when is_map(data) do
        boxes_w_triangles = Enum.filter(data.bboxes, fn {k,v} -> Map.has_key?(v, :triangles) end)
        for {id, box} <- boxes_w_triangles, into: %{} do
            ntriangles = for {p1,p2,p3} <- box.triangles, into: [] do
                np1 = Map.get(data.xyz_with_index, p1)
                np2 = Map.get(data.xyz_with_index, p2)
                np3 = Map.get(data.xyz_with_index, p3)
                {np1, np2, np3}
            end
            {id, %{box | triangles: ntriangles}}
        end
    end
end





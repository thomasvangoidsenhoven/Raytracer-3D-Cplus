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

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

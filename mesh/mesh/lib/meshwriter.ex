defmodule MeshWriter do
    def writeToFile(infile \\ "D:\\bunny.mesh", outfile \\ "D:\\optimized.json") when is_binary(infile) and is_binary(outfile) do
        data =  MeshReader.readValues(infile)
        temp = MeshOptimizer.optimizeData data
        newdata = transformTrianglePointsInBoxes(temp)
        cleaned = Map.delete(newdata, :xyz_with_index) |> Map.delete(:triangles)
        merged = Map.merge(temp.bboxes, cleaned)
        parseAndWrite(merged, outfile)
    end

    def parseAndWrite(cleaned, outfile) do
        string = Poison.encode!(cleaned)
        File.write!(outfile, string, [:write])
    end

    def transformTrianglePointsInBoxes(data) when is_map(data) do
        boxes_w_triangles = Enum.filter(data.bboxes, fn {k,v} -> Map.has_key?(v, :triangles) end)
        for {id, box} <- boxes_w_triangles, into: %{} do
            ntriangles = for {p1,p2,p3} <- box.triangles, into: [] do
                np1 = Map.get(data.xyz_with_index, p1) |> Tuple.to_list
                np2 = Map.get(data.xyz_with_index, p2) |> Tuple.to_list
                np3 = Map.get(data.xyz_with_index, p3) |> Tuple.to_list
                [np1, np2, np3]
            end
            {id, %{box | triangles: ntriangles}}
        end
    end
end

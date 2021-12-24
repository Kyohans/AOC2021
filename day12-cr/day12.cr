def dfs(graph, origin, visited) : Int32
  if origin == "end"
    return 1
  end
  
  if !visited.includes? origin && graph.has_key? origin
    if origin == "start" || origin.chars[0].ascii_lowercase?
      visited << origin
    end

    graph[origin].each do |point|
      if point != "start" && !visited.includes?(point)
        return dfs(graph, point, visited)
      end
    end
  end

  return 0
end

def part_one(filename)
  graph = Hash(String, Array(String)).new

  File.each_line(filename) do |line|
    key, point = line.split('-')
    
    if !graph[key]?
      graph[key] = Array(String).new
    end

    if !graph[point]?
      graph[point] = Array(String).new
    end
    
    graph[key] << point
    graph[point] << key
  end

  paths = Int32.new(0)
  graph["start"].each do |key|
    paths += dfs(graph, key, Set(String).new)
  end

  puts paths
end

part_one("example1")
part_one("example2")
part_one("example3")

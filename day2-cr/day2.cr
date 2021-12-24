def part_one (filename)
  pos, depth = 0, 0

  File.each_line(filename) do |line|
    direction, num = line.split

    case direction
    when "forward"
      pos += num.to_i
    when "up"
      depth -= num.to_i
    when "down"
      depth += num.to_i
    end
  end

  return pos * depth
end

def part_two (filename)
  aim, pos, depth = 0, 0, 0

  File.each_line(filename) do |line|
    direction, num = line.split

    case direction
    when "forward"
      pos += num.to_i
      depth += aim * num.to_i
    when "down"
      aim += num.to_i
    when "up"
      aim -= num.to_i
    end
  end

  return pos * depth
end

puts "part_one example: ", part_one "example"
puts "part_one answer: ", part_one "input"

puts "part_two example: ", part_two "example"
puts "part_two answer: ", part_two "input"

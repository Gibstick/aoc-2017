local i = 1
local jumps = {}

for line in io.lines() do
    jumps[i] = tonumber(line)
    i = i + 1
end

day2 = arg[1]
if day2 then print("Running day 2 solution") end


local len = #jumps

local cur = 1
local steps = 0

while cur >= 1 and cur <= len do
    offset = jumps[cur]
    if day2 and offset >= 3 then
        jumps[cur] = offset - 1
    else
        jumps[cur] = offset + 1
    end
    cur = offset + cur
    steps = steps + 1
end

print(steps)

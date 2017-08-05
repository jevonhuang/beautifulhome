function string.split(str, delimiter)
    str = tostring(str)
    delimiter = tostring(delimiter)
    if str == '' or delimiter == '' then 
		return {} 
	end
	
    local pos = 0
	local arr = {}
    for st, sp in function() return string.find(str, delimiter, pos, true) end do
        table.insert(arr, string.sub(str, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(str, pos))
    return arr
end
def skip_animals(animals, skip)
    arr=Array.new
    animals.each_with_index {|it,ind| arr.push("#{ind}:"+it) unless ind < skip}
    return arr
end
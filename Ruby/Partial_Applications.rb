def factorial(n)
    1.upto(n).reduce(1, :*)
end

combination = lambda do |n|
    lambda do |r|
        factorial(n) / (factorial(r) * factorial(n - r))
    end
end

n = gets.to_i
r = gets.to_i
nCr = combination.(n)
puts nCr.(r)
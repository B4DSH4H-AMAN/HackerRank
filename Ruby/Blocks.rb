def factorial(n)
    1.upto(n).inject(1, :*)
end

n = gets.to_i
puts factorial(n)
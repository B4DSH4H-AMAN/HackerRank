require 'prime'

n = gets.to_i

pal_primes = Prime.lazy.select do |p|
    p.to_s.chars.reverse.join.to_i == p
end.take(n).to_a

p pal_primes
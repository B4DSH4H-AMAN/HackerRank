def sum_terms(n)
    1.upto(n).reduce(0) do |m, x|
      m + fn(x)
    end
  end
  
  
  def fn(x)
    x*x + 1
  end
  
  def _sum_terms(n)
    1.upto(n).reduce(0) do |m, x|
      m + fn(x)
    end
  end
  
  
  num = gets.to_i
  t1 = sum_terms(num)
  
  t1 = sum_terms(num)
  a1 = _sum_terms(num)
  
  unless (t1.is_a? Fixnum or t1.is_a? Bignum)
    puts 'Your method must return an Integer (Fixnum, Bignum).'
    exit(0)
  end
  
  unless t1 == a1
    puts 'Ooops! Seems like you have done some mistake. Try again!'
    exit(0)
  end
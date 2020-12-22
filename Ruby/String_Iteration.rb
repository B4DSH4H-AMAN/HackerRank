def count_multibyte_char(s)
    i = 0
    s.each_char {|x| i+=1 if x.bytesize>1}
    i
end
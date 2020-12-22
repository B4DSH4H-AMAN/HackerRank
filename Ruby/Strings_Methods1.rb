def process_text(s)
    s.each{|x| x.strip!}
    text = s.join(" ")
    text
end
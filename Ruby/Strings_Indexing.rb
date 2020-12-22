def serial_average(code)
    code = code.split("-")
    z = ((code[1].to_f + code[2].to_f)/2).round(2)
    "#{code[0]}-#{z}"
end
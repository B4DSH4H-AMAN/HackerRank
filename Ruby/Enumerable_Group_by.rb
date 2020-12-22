def group_by_marks(marks, n)
    marks.group_by{|x| x[1] < n ? "Failed" : "Passed" }
end
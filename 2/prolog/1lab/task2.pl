% Task 2: Relational Data

% The line below imports the data
:-['three.pl'].
:-['std_list.pl'].


get_marks(Group, Student, Subject, Num) :- 
    student(Group, Student, Marks),
    member1(grade(Subject, Num), Marks). 

calculate_marks(Subject, Res) :- 
    subject(Sub, Subject),
    findall(X, get_marks(_, _, Sub, X), Marks),
    length1(Marks, Len),
    sum_list1(Marks, Sum),
    Res is  Sum/Len.

task1():-
    findall(X, subject(_, X), S),
    write_ans3(S).

write_ans3([]).
write_ans3([X|L]):-
    calculate_marks(X, Res), write(X), write(': '), write(' '), write(Res), write('\n'),
    write_ans3(L).





bad_students_group(Group, Student, Subject) :- 
    student(Group, Student, Marks),
    member1(grade(Subject, 2), Marks). 

find_students(Group, Len) :- 
    findall(X, bad_students_group(Group, X, _), Students),
    setof(X, member1(X, Students), Set_Student),
    length1(Set_Student, Len).

task2():-
    findall(X, student(X,_,_), S),
    setof(X, member1(X, S), L),
    write_ans(L).

write_ans([]).
write_ans([X|L]):-
    find_students(X, Len), write('Group '), write(X), write(': '), write(' '), write(Len), write('\n'),
    write_ans(L).




bad_students_subject(Group, Student, Subject) :- 
    student(Group, Student, Marks),
    member1(grade(Subject, 2), Marks). 

find_subjects(Subject, Len) :- 
    subject(Sub, Subject),
    findall(X, bad_students_subject(_, X, Sub), Students),
    length1(Students, Len).

task3():-
    findall(X, subject(_, X), S),
    write_ans1(S).

write_ans1([]).
write_ans1([X|L]):-
    find_subjects(X, Len), write(X), write(': '), write(' '), write(Len), write('\n'),
    write_ans1(L).

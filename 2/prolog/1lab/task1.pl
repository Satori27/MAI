:-['std_list.pl'].

remove_el(1,[_|T],T). % удаление элемента под номером
remove_el(N,[Y|T],[Y|T1]):-
    N1 is N-1, remove_el(N1,T,T1).


% Удаление под номером с использованием предиката
remove_with_pr(N, A, Y):-
    append1(X,_,A), length1(X, N), append1(R1,[_],X),
    length1(A,NA),
    N1 is NA-N, append1(_,X1,A), length1(X1, N1),
    append1(R1,X1,Y), !.



% суммирование векторов без стандартных предикатов.
sum([],0).
sum([X|Y],R):-
    sum(Y,S),
    R is S+X.
    
vector_sum(X,Y,S) :-
    sum(X, Num1),
    sum(Y, Num2),
    S is (Num1+Num2).


% суммирование векторов с использование стандартных предикатов
vector_sum_pr(X, Y, N) :-
    append1(X,Y,Z),
    sum_list1(Z,N).

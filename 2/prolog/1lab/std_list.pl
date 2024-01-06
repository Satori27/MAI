length1([], 0) . 
length1([_|Y], N) :- length1(Y, N1), N is N1 + 1.

member1(A, [A|_]).
member1(A, [_|Z]) :- member1(A, Z).

append1([], X, X).
append1([A|X], Y, [A|Z]) :- append1(X,Y,Z).


remove_n(L,X,N):-append(_,X,L), length(X, N).

sublist(S,L):-append(_,L1,L),append(S,_,L1).


remove(X,[X|T],T).
remove(X,[Y|T],[Y|T1]):-remove(X,T,T1).

permute([],[]).
permute(L,[X|T]):-remove(X,L,R),permute(R,T).

sum_list1([],0).
sum_list1([X|Y],R):-
    sum_list1(Y,S),
    R is S+X.
    


del_last(L,R):- append(R,[_],L).
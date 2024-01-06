append1([], X, X).
append1([A|X], Y, [A|Z]) :- append1(X,Y,Z).

member1(A, [A|_]).
member1(A, [_|Z]) :- member1(A, Z).

length1([], 0) . 
length1([_|Y], N) :- length1(Y, N1), N is N1 + 1.

name(X) :- (X = leonid; X = michail; X = nickolay; X = oleg; X = petr).
surn(X) :- (X = atarov; X = bartenev; X = klenov; X = danilin; X = ivanov).
pers(N, S) :- name(N), surn(S).


fact(oleg, petr).
fact(michail, petr).
fact(nickolay, petr).
fact(leonid, petr).
fact(leonid, michail).
fact(leonid, nickolay).
fact(leonid, oleg).
fact(michail, nickolay).
fact(michail, oleg).
fact(nickolay, oleg).

is_unique([]).
is_unique([H | T]) :- 
   not(member1(H, T)),
   is_unique(T).

relationship([]) :- fail.
relationship([[N, S], [N1, S1]]) :- 
   pers(N, S), pers(N1, S1), 
   is_unique([N, N1]),
   is_unique([S, S1]).
relationship([[N, S], [N1, S1], [N2, S2]]) :- 
   pers(N, S), pers(N1, S1), pers(N2, S2),
   is_unique([N, N1, N2]), fact(N1, N2),
   is_unique([S, S1, S2]).
relationship([[N, S], [N1, S1], [N2, S2], [N3, S3]]) :- 
   pers(N, S), pers(N1, S1), pers(N2, S2), pers(N3, S3),
   is_unique([N, N1, N2, N3]), fact(N1, N2), fact(N1, N3), fact(N2, N3),
   is_unique([S, S1, S2, S3]).

accordance([[_, _]]).
accordance([[N, S] | T]) :- 
   member1([N, AS], T), not(AS = S), !, fail;
   member1([AN, S], T), not(AN = N), !, fail;
   accordance(T).

solve(V, W, X, Y, Z) :- 
   V = [[leonid, S1] | T1],
   relationship([[leonid, S1] | T1]),
   append1([[leonid, S1]], T1, L1),
   % 1
   %------------------------------------------------------------------------------

   (
      S1 = bartenev,
      length1(T1, 2);
      not(S1 = bartenev)
   ),

   length1(T1, 1),

   (
      S1 = danilin,
      not(member1([michail, _], T1));
      not(S1 = danilin)
   ),
   
   not(member1([michail, danilin], T1)),

   (
      S1 = ivanov,
      member1([nickolay, _], T1);
      not(S1 = ivanov)
   ),
   not(member1([nickolay, ivanov], T1)),

   (
      S1 = atarov,
      length1(T1, 3);
      not(S1 = atarov)
   ),
   
   (
      S1 = klenov,
      length1(T1, 1);
      not(S1 = klenov)
   ),
   % 2
   %------------------------------------------------------------------------------

   W = [[michail, S2] | T2],
   relationship([[michail, S2] | T2]),
   append1([[michail, S2]], T2, L2),
   append1(L1, L2, L6),

   (
      S2 = bartenev,
      length1(T2, 2);
      not(S2 = bartenev)
   ),

   not(member1([_, danilin], T2)),

   not(S2 = danilin),

   (
      S2 = ivanov,
      member1([nickolay, _], T2);
      not(S2 = ivanov)
   ),

   not(member1([nickolay, ivanov], T2)),

   member1([nickolay, _], T2),
   member1([oleg, _], T2),

   (
      S2 = atarov,
      length1(T2, 3);
      not(S2 = atarov)
   ),
   
   (
      S2 = klenov,
      length1(T2, 1);
      not(S2 = klenov)
   ),
   %3
   %------------------------------------------------------------------------------

   X = [[nickolay, S3] | T3],
   relationship([[nickolay, S3] | T3]),
   append1([[nickolay, S3]], T3, L3),
   append1(L6, L3, L7),

   (
      S3 = bartenev,
      length1(T3, 2);
      not(S3 = bartenev)
   ),

   (
      S3 = danilin,
      not(member1([michail, S2], T3));
      not(S3 = danilin)
   ),
   not(member1([michail, danilin], T3)),

   member1([_, ivanov], T3),
   
   not(S3 = ivanov),

   member1([michail, S2], T3),

   member1([oleg, _], T3),

   (
      S3 = atarov,
      length1(T3, 3);
      not(S3 = atarov)
   ),
   
   (
      S3 = klenov,
      length1(T3, 1);
      not(S3 = klenov)
   ),
   %4
   %------------------------------------------------------------------------------

   Y = [[oleg, S4] | T4],
   relationship([[oleg, S4] | T4]),
   append1([[oleg, S4]], T4, L4),
   append1(L7, L4, L8),

   (
      S4 = bartenev,
      length1(T4, 2);
      not(S4 = bartenev)
   ),

   (
      S4 = danilin,
      not(member1([michail, S2], T4));
      not(S4 = danilin)
   ),
   
   not(member1([michail, danilin], T4)),

   (
      S4 = ivanov,
      member1([nickolay, S3], T4);
      not(S4 = ivanov)
   ),
   not(member1([nickolay, ivanov], T4)),

   member1([michail, S2], T4),

   member1([nickolay, S3], T4),

   (
      S4 = atarov,
      length1(T4, 3);
      not(S4 = atarov)
   ),
   
   (
      S4 = klenov,
      length1(T4, 1);
      not(S4 = klenov)
   ),

   (
      member1([petr, S5], T1), member1([petr, S5], T2), member1([petr, S5], T3), not(member1([petr, S5], T4));
      member1([petr, S5], T1), member1([petr, S5], T2), member1([petr, S5], T4), not(member1([petr, S5], T3));
      member1([petr, S5], T1), member1([petr, S5], T3), member1([petr, S5], T4), not(member1([petr, S5], T2));
      member1([petr, S5], T2), member1([petr, S5], T3), member1([petr, S5], T4), not(member1([petr, S5], T1))
   ),

   % 5
   %------------------------------------------------------------------------------

   Z = [[petr, S5] | T5],
   relationship([[petr, S5] | T5]),
   is_unique([S1, S2, S3, S4, S5]),
   append1([[petr, S5]], T5, L5),
   append1(L8, L5, L),
   accordance(L),

   (
      S5 = bartenev,
      length1(T5, 2);
      not(S5 = bartenev)
   ),

   length1(T5, 3),

   (
      member1([leonid, S1], T2), not(member1([leonid, S1], T3)), not(member1([leonid, S1], T4)), not(member1([leonid, S1], T5));
      member1([leonid, S1], T3), not(member1([leonid, S1], T2)), not(member1([leonid, S1], T4)), not(member1([leonid, S1], T5));
      member1([leonid, S1], T4), not(member1([leonid, S1], T2)), not(member1([leonid, S1], T3)), not(member1([leonid, S1], T5));
      member1([leonid, S1], T5), not(member1([leonid, S1], T2)), not(member1([leonid, S1], T3)), not(member1([leonid, S1], T4))
   ),

   (
      S5 = danilin,
      not(member1([michail, S2], T5));
      not(S5 = danilin)
   ),

   not(member1([michail, danilin], T5)),

   (
      S5 = ivanov,
      member1([nickolay, S3], T5);
      not(S5 = ivanov)
   ),
   not(member1([nickolay, ivanov], T5)),

   (
      S5 = atarov,
      length1(T5, 3);
      not(S5 = atarov)
   ),
   
   (
      S5 = klenov,
      length1(T5, 1);
      not(S5 = klenov)
   ).
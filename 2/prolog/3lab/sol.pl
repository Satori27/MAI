


lol(X,Y):-
    write([X|Y]=[1]).


prolong([X|T], [Y,X|T]) :-
    move(X, Y),
    not(member(Y, [X|T])).

move([[RLeft|TLeft], Tupik, Right], [TLeft, [RLeft|Tupik], Right]).
move([Left, [RTupik|TTupik], Right], [Left, TTupik, [RTupik|Right]]).
move([[RLeft|TLeft], Tupik, Right], [TLeft, Tupik, [RLeft|Right]]).

right_end([], [], _).
right_end([_ | [_ | Tail]], [w|[b|End]], w) :-
    right_end(Tail, End, w).
right_end([_ | [_ | Tail]], [b|[w|End]], b) :-
    right_end(Tail, End, b).

% Поиск в глубину
ddts([X|T], X, [X|T]).
ddts(Path, Y, R) :-
    prolong(Path, Path1),
    ddts(Path1, Y, R).

dfs_path(Cond) :-
    right_end(Cond, End, w),
    ddts([[Cond, [], []]], [[], [], End], Path),
    length(Path,N),
    write("Длина решения "), write(N), write('\n'),
    write(Path), write('\n').

dfs_path(Cond) :-
    right_end(Cond, End, b),
    ddts([[Cond, [], []]], [[], [], End], Path),
    length(Path,N),
    write("Длина решения "), write(N), write('\n'),
    write(Path), write('\n').

% Поиск в ширину
bdts([[X|A]|_], X, [X|A]).
bdts([Path|QI], X, R) :-
    findall(Z, prolong(Path, Z), A),
    append(QI, A, QO),
    bdts(QO, X, R).

bfs_path(Cond) :-
    right_end(Cond, End, w),
    bdts([[[Cond, [], []]]], [[], [], End], Path),
    length(Path, N),
    write("Длина решения "), write(N), write('\n'),
    write(Path), write('\n').

bfs_path(Cond) :-
    right_end(Cond, End, b),
    bdts([[[Cond, [], []]]], [[], [], End], Path),
    length(Path, N),
    write("Длина решения "), write(N), write('\n'),
    write(Path), write('\n').


% Поиск с итеративным погружением
search(Start, End, Path, Limit) :-
    between(1, Limit, Level),
    depth_id([Start], End, Path, Level).

depth_id([End|T], End, [End|T], 0).
depth_id(Path, End, R, N) :-
    N > 0,
    prolong(Path, NewPath),
    N1 is N - 1,
    depth_id(NewPath, End, R, N1).

iter_dfs(Cond, Limit) :-
    right_end(Cond, End, w),
    search([Cond, [], []], [[], [], End], Path, Limit),
    length(Path,N),
    write("Длина решения "), write(N), write('\n'),
    write(Path), write('\n').

iter_dfs(Cond, Limit) :-
    right_end(Cond, End, b),
    search([Cond, [], []], [[], [], End], Path, Limit),
    length(Path,N),
    write("Длина решения "), write(N), write('\n'),
    write(Path), write('\n').
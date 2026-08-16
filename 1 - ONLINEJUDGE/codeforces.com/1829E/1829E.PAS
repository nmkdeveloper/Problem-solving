{$mode objfpc}{$H+}

program CF1829E;
uses sysutils, math;

type
    T2DArrayInt = array of array of integer;
    T2DArrayBool = array of array of boolean;
const
    DX : array[0..3] of integer = (1, -1, 0, 0);
    DY : array[0..3] of integer = (0, 0, 1, -1);

procedure FileIO;
const filename = '1829E';
begin
    if (filename <> '') and FileExists(filename + '.INP') then
    begin
        assign(input, filename + '.INP');
        reset(input);
        assign(output, filename + '.OUT');
        rewrite(output);
    end;
end;

function DFS(const map : T2DArrayInt; const x, y, n, m : integer; var visited : T2DArrayBool) : longint;
var 
    nx, ny, i : integer;
    sum : longint;
begin
    visited[x][y] := true;
    sum := map[x][y];
    for i := 0 to 3 do
    begin
        nx := x + DX[i];
        ny := y + DY[i];
        if (nx >= 0) and (nx < n) and (ny >= 0) and (ny < m) and (map[nx][ny] <> 0) and (not visited[nx][ny]) then
        begin
            sum := sum + DFS(map, nx, ny, n, m, visited);
        end;
    end;
    exit(sum);
end;

function Solve(const n : integer; const m : integer; const map : T2DArrayInt) : longint;
var 
    i, j : integer;
    visited : T2DArrayBool;
    res : longint;
begin
    res := 0;
    SetLength(visited, n, m);
    for i := 0 to n - 1 do
    begin
        for j := 0 to m - 1 do
        begin
            visited[i][j] := false;
        end;
    end;
    for i := 0 to n - 1 do
    begin
        for j := 0 to m - 1 do
        begin
            if (not visited[i][j]) and (map[i][j] <> 0) then 
            begin
                res := max(res, DFS(map, i, j, n, m, visited));
            end;
        end;
    end;
    
    exit(res);
end;

procedure readData;
var 
    i, j, t : integer;
    n, m : integer;
    map : T2DArrayInt;
begin
    readln(t);
    while (t > 0) do begin
        readln(n, m);
        SetLength(map, n, m);
        for i := 0 to (n - 1) do
        begin
            for j := 0 to (m - 1) do
            begin
                read(map[i][j]);
            end;
        end;
        writeln(Solve(n, m, map));
        t := t - 1;
    end;
end;

begin
    FileIO;
    readData;
end.

{
    'Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
     Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do 
              du chi mot chut. Toi thay chi can nhu vay la du roi.'

                                             — Sousou no Frieren —
    ───────────────────────────────────────────────────────────────────────
    Template by : Nguyen Minh Khoi (github/nmkdeveloper)
    Adapted for : Free Pascal (FPC)
}
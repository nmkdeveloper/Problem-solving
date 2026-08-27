{$mode objfpc}{$H+}

program default;
uses sysutils;

procedure FileIO;
const filename = '';
begin
    if (filename <> '') and FileExists(filename + '.INP') then
    begin
        assign(input, filename + '.INP');
        reset(input);
        assign(output, filename + '.OUT');
        rewrite(output);
    end;
end;

procedure readData;
begin
end;

procedure Solve;
begin
    
end;

begin
    fileIO;
    readData;
    Solve;
end.

{
    'Frieren: Vay theo cau chung ta phai lam gi de nguoi khac nho den chung ta chu?
     Himmel:  Cung khong co gi to tac, do la hay thay doi cuoc doi cua ai do 
              du chi mot chut. Toi thay chi can nhu vay la du roi.'

                                             — Sousou no Frieren —
    =======================================================================
    Template by : Nguyen Minh Khoi (github/nmkdeveloper)
    Adapted for : Free Pascal (FPC)
}
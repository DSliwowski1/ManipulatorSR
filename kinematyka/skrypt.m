clear all;

a = 84;
l1 = 40;
l2 = 150;
l3 = 168;

syms q1;
syms q2;
syms q3;
syms q;
q = [q1; q2; q3];

A0 = [1 0 0 0; 0 1 0 0; 0 0 1 a; 0 0 0 1];

%%%% A1 %%%%
syms Rz1;
Rz1 = [cos(q1) -sin(q1)     0         0;
       sin(q1)  cos(q1)     0         0;
       0        0           1         0;
       0        0           0         1];
   
Tz1 = [sym(1)        0           0         0;
       0        1           0         0;
       0        0           1         l1;
       0        0           0         1];
   
Rx1 = [1        0           0         0;
       0        cos(sym(pi/2))  -sin(sym(pi/2)) 0;
       0        sin(sym(pi/2))   cos(sym(pi/2)) 0;
       0        0           0         1]
   
A1 = Rz1 * Tz1 * Rx1;

%%%% A2 %%%%
Rz2 = [cos(q2 + sym(pi/2)) -sin(q2 + sym(pi/2))     0         0;
       sin(q2 + sym(pi/2))  cos(q2 + sym(pi/2))     0         0;
       0        0           1         0;
       0        0           0         1];

Tx2 = [sym(1)   0           0         l2;
       0        1           0         0;
       0        0           1         0;
       0        0           0         1];
   
A2 = Rz2 * Tx2;

%%% A3 %%%
Rz3 = [cos(q3 - sym(pi/2)) -sin(q3 - sym(pi/2))     0         0;
       sin(q3 - sym(pi/2))  cos(q3 - sym(pi/2))     0         0;
       0        0           1         0;
       0        0           0         1];

Tx3 = [sym(1)   0           0         l3;
       0        1           0         0;
       0        0           1         0;
       0        0           0         1];

A3 = Rz3 * Tx3;

%%% Transformacje %%%
A01 = A1 * A0;
A02 = A2 * A1 * A0;
A03 = A3 * A2 * A1 * A0;
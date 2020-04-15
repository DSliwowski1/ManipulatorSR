clear all;

a  = 0.084;
l1 = 0.040;
l2 = 0.150;
l3 = 0.168;

syms q1;
syms q2;
syms q3;
syms q;
q = [q1; q2; q3];

syms dq1;
syms dq2;
syms dq3;
syms dq;
dq = [dq1; dq2; dq3];

A0b = [1 0 0 0; 0 1 0 0; 0 0 1 a; 0 0 0 1];

%%%% A10 %%%%
syms Rz1;
Rz1 = [cos(q1) -sin(q1)     0         0;
       sin(q1)  cos(q1)     0         0;
       0        0           1         0;
       0        0           0         1];
   
Tz1 = [1        0           0         0;
       0        1           0         0;
       0        0           1         sym(l1);
       0        0           0         1];
   
Rx1 = [1        0           0         0;
       0        cos(sym(pi/2))  -sin(sym(pi/2)) 0;
       0        sin(sym(pi/2))   cos(sym(pi/2)) 0;
       0        0           0         1];
   
A01 = A0b * Rz1 * Tz1 * Rx1;

%%%% A2 %%%%
Rz2 = [cos(q2 + sym(pi/2)) -sin(q2 + sym(pi/2))     0         0;
       sin(q2 + sym(pi/2))  cos(q2 + sym(pi/2))     0         0;
       0        0           1         0;
       0        0           0         1];

Tx2 = [sym(1)   0           0         l2;
       0        1           0         0;
       0        0           1         0;
       0        0           0         1];
   
A02 = A01 * Rz2 * Tx2;

%%% A3 %%%
Rz3 = [cos(q3 - sym(pi/2)) -sin(q3 - sym(pi/2))     0         0;
       sin(q3 - sym(pi/2))  cos(q3 - sym(pi/2))     0         0;
       0        0           1         0;
       0        0           0         1];

Tx3 = [sym(1)   0           0         l3;
       0        1           0         0;
       0        0           1         0;
       0        0           0         1];

A03 = A02 * Rz3 * Tx3;



%%%%% Dynamika %%%%%

J1 = [sym(580.981)	  -258.644	   -0.83	-8.613792
         -258.644	   131.166	   -3.264	-5.290824
           -0.83	    -3.264	 1087.299	 0.08712
           -8.613792	-8.613792	0.08712	 0.264];

  
J2 = [sym(292.685)	0	      0	       0
            0	   10.337	-15.357	  -2.28225
            0	  -15.357	283.452	  -0.10059
            0	   -2.8225	 -0.10059  0.03];

  
J3 = [sym(4.291)   -0.01	      8.713	  -3.852896
         -0.01	  622.525	      0	      -0.00038
          8.713	    0	        619.262	   0.041914
         -3.852896 -0.00038	      0.041914 0.038];


%%%% Macierz bezwładności Q(q) %%%%
syms Q;

for j=[1:3]
   for k=[1:3]
     d01 = diff(A01, q(j));
     d01T = diff(A01, q(k)).';
     d02 = diff(A02, q(j));
     d02T = diff(A02, q(k)).';
     d03 = diff(A03, q(j));
     d03T = diff(A03, q(k)).';
     
     Q(j, k) = trace(d01 * J1 * d01T) + trace(d02 * J2 * d02T) + trace(d03 * J3 * d03T);
     
   end
end

%%%% Siły odsrodkowe i Coriollisa C(q, dq) %%%%%%
syms C;
tmp = sym(0);

for i=[1:3]
   for j=[1:3]
        for k = [1, 3]
            d1 = diff(Q(i, j), q(k));
            d2 = diff(Q(i, k), q(j));
            d3 = diff(Q(j, k), q(i));
           tmp = tmp + 1/2*(d1 + d2 + d3)*dq(k);
        end
        C(i, j) = tmp;
   end
end

%%%% Siły potencjalne %%%%
syms g;
syms V;

g = [sym(0); 0; -9.8; 0];

r1 = J1(1:4, 4); r1(4, 1) = 1;
r2 = J2(1:4, 4); r2(4, 1) = 1;
r3 = J3(1:4, 4); r3(4, 1) = 1;

V1 = -J1(4,4) * g.' * A01 * r1;
V2 = -J2(4,4) * g.' * A02 * r2;
V3 = -J3(4,4) * g.' * A03 * r3;

V = [V1; V2; V3];

D = jacobian(V, q);

%%%% Tarcie %%%%
Ts = 0.492;
Tv = 0;

T = Ts * tanh(0.95 * dq);





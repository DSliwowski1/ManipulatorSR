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


%%%%% Dynamika %%%%%
syms Q;

J1 = [sym(532.019)	  0.83	    40.378	   -8.613792;
      0.83	      1038.337	    0.237	    0.08712;
      40.378	  0.237	        1313.166	3.880272;
      -8.613792	 -8.613792	    3.880272	0.264];
  
J2 = [sym(282.847)	0	          0	       0;
      0	           10.337	     -0.022	   2.21775;
      0	           -0.022	    273.614   -0.10059;
      0	            2.21775	     -0.10059  0.03];
  
J3 = [sym(400.011)	  -0.655  	    0.017	  -0.013224;
           -0.655	   4.296       -1.676	  -2.527722;
            0.017	  -1.676	  396.752	   0.041914;
           -0.013224  -2.527722	    0.041914   0.038];

%%%% Macierz bezwładności %%%%

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


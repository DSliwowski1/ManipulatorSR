
kin_m = {A03(1:3,4), A02(1:3,4), A01(1:3, 4), [0;0;0]};

q_c = [0;0;0];

polz = [0.16; -0.0; 0.4];

tmp = ccd3(polz, q_c);
y_os = double(subs(A03(1:3, 4), [q1;q2;q3], tmp))

polp = double(subs(A03(1:3, 4), [q1; q2; q3], q_c));

v = polz - polp;

i=[0:0.01:1];
prosta = v*i + polp;

plot3(prosta(1,:), prosta(2,:), prosta(3,:), '-');
hold on, grid on;
res = [];
err = [];
for i=[0:0.05:1]
    punkt = v*i + polp
    q_c = ccd3(punkt, q_c);
    y_os = double(subs(A03(1:3, 4), [q1;q2;q3], q_c))
    e = norm(y_os - punkt);
    err = [err, e];
    res = [res,y_os];
end
plot3(res(1,:), res(2,:), res(3,:), '-');
%tmp = ccd3(y_des, q_c);

%y_os = double(subs(A03(1:3, 4), [q1;q2;q3], tmp))

function out = ccd3(y_des, q_c)
    kin_m = evalin('base', 'kin_m');
    syms q1;
    syms q2;
    syms q3;
    syms t
    iter = 0;
    
    y_tmp = y_des;
    y_tmp(3) = 0;

    y_root = double(subs(kin_m{4}, [q1;q2;q3], q_c));

    y_eff = double(subs(kin_m{1}, [q1;q2;q3], q_c));
    y_eff(3) = 0;

    if(Mdist(y_eff, y_des) > 0.001)
        %Odpowiedznie wektory
        cur_vec = y_eff - y_root;
        des_vec = y_tmp - y_root;

        % Normalizacja
        cur_vec = cur_vec / norm(cur_vec);
        des_vec = des_vec / norm(des_vec);

        % Iloczyn skalarny zrwaca warrtość kąta
        cos_tmp = dot(cur_vec, des_vec);

        if cos_tmp < 0.9999
            % Określenie kierunku
            cross_v = cross(cur_vec, des_vec);

            if cross_v(3) > 0
                turn_a_rad = acos(cos_tmp);                  
                q_c(1) = q_c(1) + turn_a_rad;
            elseif cross_v(3) < 0
                turn_a_rad = acos(cos_tmp);                  
                q_c(1) = q_c(1) - turn_a_rad;
            end
        end
    end

    while iter < 50
        % dla każdego ogniwa
        for i = [1:2]
            y_root = double(subs(kin_m{i+1}, [q1;q2;q3], q_c));

            y_eff = double(subs(kin_m{1}, [q1;q2;q3], q_c));

            %plot3([y_root(1), y_eff(1)], [y_root(2), y_eff(2)], [y_root(3), y_eff(3)], '-o');
            %hold on;
            %plot3([y_root(1), y_tmp(1)], [y_root(2), y_tmp(2)], [y_root(3), y_tmp(3)], '-o');
            
            if(Mdist(y_eff, y_des) > 0.001)
                %Odpowiedznie wektory
                cur_vec = y_eff - y_root;
                des_vec = y_des - y_root;

                % Normalizacja
                cur_vec = cur_vec / norm(cur_vec);
                des_vec = des_vec / norm(des_vec);

                % Iloczyn skalarny zrwaca warrtość kąta
                cos_tmp = dot(cur_vec, des_vec);
                

                if cos_tmp < 0.9999
                    % Określenie kierunku
                    cross_v = cross(cur_vec, des_vec);
                    %tmp = y_root + cross_v;
                    %plot3([y_root(1), tmp(1)], [y_root(2), tmp(2)], [y_root(3), tmp(3)], '-o');

                    if cross_v(2) > 0
                        turn_a_rad = acos(cos_tmp);                  
                        q_c(4-i) = q_c(4-i) - turn_a_rad;
                    elseif cross_v(2) < 0
                        turn_a_rad = acos(cos_tmp);                  
                        q_c(4-i) = q_c(4-i) + turn_a_rad;
                    end
                end
            end
        end
        iter = iter +1;
    end
    out = q_c;
end


function out = Mdist(u1, u2)
    out = norm(u2- u1);
end
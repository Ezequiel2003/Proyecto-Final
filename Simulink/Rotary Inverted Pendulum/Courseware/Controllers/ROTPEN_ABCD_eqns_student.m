% State Space Representation
A = eye(4,4);
B = [0;0;0;1];
C = eye(2,4);
D = zeros(2,1);

% Add actuator dynamics

A(3,3) = A(3,3) - Kg^2*kt*km/Rm*B(3);
A(4,3) = A(4,3) - Kg^2*kt*km/Rm*B(4);
B = Kg * kt * B / Rm;
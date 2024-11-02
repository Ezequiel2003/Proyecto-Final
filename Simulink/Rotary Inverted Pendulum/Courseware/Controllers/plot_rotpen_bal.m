%% Load data
% load('data_rotpen_bal_theta.mat');
% load('data_rotpen_bal_alpha.mat');
% load('data_rotpen_bal_Vm.mat');
%
%% Plot
% time
t = data_theta(:,1);
% desired rotary arm angle
th_d = data_theta(:,2);
% measured/simulated rotary arm angle
th = data_theta(:,3);
% measured/simulated pendulum angle
al = data_alpha(:,2);
% voltage
u = data_Vm(:,2);
%
% plot arm response
subplot(3,1,1)
plot(t,th_d,'b--',t,th,'r-','linewidth',2);
% axis([10 20 -50 50]);
xlabel('time (s)');
ylabel('\theta (deg)');
% plot pendulum respons
subplot(3,1,2)
plot(t,al,'r-','linewidth',2);
% axis([10 20 -10 10]);
xlabel('time (s)');
ylabel('\alpha (deg)');
% plot voltage respons
subplot(3,1,3)
plot(t,u,'r-','linewidth',2);
% axis([10 20 -5 5]);
xlabel('time (s)');
ylabel('u (V)');

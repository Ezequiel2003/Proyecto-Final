%% Load data
% load('data_rotpen_mdl_theta.mat');
% load('data_rotpen_mdl_alpha.mat');
% load('data_rotpen_mdl_Vm.mat');
%
%% Plot
% time
t = data_theta(:,1);
% measured rotary arm angle
th = data_theta(:,2);
% measured pendulum angle
al = data_alpha(:,2);
% votlage
u = data_Vm(:,2);
% plot arm response
subplot(2,1,1)
plot(t,th,'b-','linewidth',2);
axis([0 4 -50 150]);
xlabel('time (s)');
ylabel('\theta (deg)');
% plot voltage respons
subplot(2,1,2)
plot(t,u,'r-','linewidth',2);
axis([0 4 -2 2]);
xlabel('time (s)');
ylabel('u (V)');

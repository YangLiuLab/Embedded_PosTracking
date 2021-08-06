% GaussSignal: simulate the signal with gaussian shape
% I: simulated signal
% xc: center position
% A: amplitude
% R: signal radius
% sigma: standard deviation of gaussian function
% bg: background
% rn: random noise
% Developed by Hongqiang Ma @ PITT, on July 2020.


function [I, xc] = GaussSignal(R, A, sigma, bg, rn)

xc = R + rand(1);
X = 1:(2*R+1);
Ir = A*exp(-(X-xc).^2/(2*sigma^2))+bg;
I = poissrnd(Ir)+ rn*rand();

end
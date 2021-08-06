clc
clear

SR = 100; % signal radius
A = 1000; % signal amplitude
sigma = 2; % gaussian width
bg = 200; % background
rn = 100; % random noise

[I, xc] = GaussSignal(SR, A, sigma, bg, rn);
[ROI, R, x] = extractROI(I);
ep_xc = ephasor(ROI,R);

x_error = (ep_xc+x) - xc;

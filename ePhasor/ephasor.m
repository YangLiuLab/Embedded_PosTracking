% ephasor: 1st Fourier Harmonic position estimation %%
% xc: estimated position
% ROI: the extracted region of signal 
% R: region radius
% Developed by Hongqiang Ma @ PITT, on July 2020. 

function [xc] = ephasor(ROI,R)

fft_ix = fft(ROI);
ROI_cx = angle(fft_ix(2));

if(ROI_cx>0)
    ROI_cx = ROI_cx - 2*pi;
end

xc = (-(ROI_cx)/(2*pi/(2*R+1)) + 1) - (R+1);
end
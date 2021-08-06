% extractROI: extract ROI from raw signal 
% I: raw signal
% ROI: the extracted region of signal 
% R: radius of ROI
% x: ROI center position
% Developed by Hongqiang Ma @ PITT, on July 2020.


function [ROI, R, x] = extractROI(I)

bg = min(I) + 0.1*(max(I) - min(I));
Ibg = I - bg;
Ibg(Ibg<bg) = 0;
id = 1:length(I);
c = sum(Ibg.*id)/sum(Ibg);
sigma = (sum(Ibg.*abs(id-c))/sum(Ibg));
x = round(c);
R = round(4*sigma);
ROI = I(x-R:x+R);

end
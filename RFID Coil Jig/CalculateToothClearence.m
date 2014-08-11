% File:   CalculateToothClearence.m
% Author: Seb Madgwick
%
% Calculates tooth clearance for design in SolidWorks.
%
% Adjust femaleToothArc and repetitions to achieve desired toothClearance.
% MakerBot requires an extra 0.2 mm clearance on each surface (i.e.
% toothClearance of 0.4 mm)

clear;

innerRadius = 45; % mm
innerCircumference = 2*pi*innerRadius; % mm

femaleToothArc = 10.3; % degrees (extruded cut)
femaleToothCircumference = (innerCircumference / 360) * femaleToothArc; % mm

repetitions = 18; % SolidWorks Circular Pattern equal spacing
totalMaleToothCircumference = innerCircumference - (repetitions * femaleToothCircumference); % mm
maleToothCircumference = totalMaleToothCircumference / repetitions; % mm

toothClearance = femaleToothCircumference - maleToothCircumference

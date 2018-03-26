function [f,vP] = findFeatures(IM)
     points = detectSURFFeatures(IM);
     [f,vP] = extractFeatures(IM,points,'SURFSize',128);
end
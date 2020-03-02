function [A]= areaIsosurface(F,V)
%Function to calculate the area of an isosurface generated by MATLAB's
%   built-in isosurface().
%SCd 07/12/2010
%
%This function uses Heron's numerically stable formula available here:
%>>web('http://en.wikipedia.org/wiki/Heron''s_formula','-new');
%
%Input Arguments:
%   [F,V] = isosurface(...);   
%   F: calculation above
%   V: calculation above
%   
%Output Arguments:
%   A: surface area of the triangulated isosurface.
%
      %Calculate side lengths:
      sides = zeros(size(F,1),3); %Preallocate
      sides(:,1) = sqrt(... %a
          (V(F(:,1),1)-V(F(:,2),1)).^2+...
          (V(F(:,1),2)-V(F(:,2),2)).^2+...
          (V(F(:,1),3)-V(F(:,2),3)).^2);
      sides(:,2) = sqrt(... %b
          (V(F(:,2),1)-V(F(:,3),1)).^2+...
          (V(F(:,2),2)-V(F(:,3),2)).^2+...
          (V(F(:,2),3)-V(F(:,3),3)).^2);
      sides(:,3) = sqrt(... %c
          (V(F(:,1),1)-V(F(:,3),1)).^2+...
          (V(F(:,1),2)-V(F(:,3),2)).^2+...
          (V(F(:,1),3)-V(F(:,3),3)).^2);
      %Sort so: sides(:,1)>=sides(:,2)>=sides(:,3).
      sides = sort(sides,2,'descend');
      %Calculate Area!
      A = sum(sqrt(...
          (sides(:,1)+(sides(:,2)+sides(:,3))).*...
          (sides(:,3)-(sides(:,1)-sides(:,2))).*...
          (sides(:,3)+(sides(:,1)-sides(:,2))).*...
          (sides(:,1)+(sides(:,2)-sides(:,3)))))/4;
  end

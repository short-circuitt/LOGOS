function diff_mat = distCosine(A,B)
            denom1 = sqrt(sum(A.^2,2));
            denom2 = sqrt(sum(B.^2,2));
            diff_mat = 1- A*B'./(denom1*denom2');
end

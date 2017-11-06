function [r,c] = getrc(loc)

    if (loc < 4)
        r = 1;
        c = loc + 1;
    elseif (loc < 8)
        r = 2;
        c = loc - 3;
    elseif (loc < 12)
        r = 3;
        c = loc - 7;
    elseif (loc < 16)
        r = 4;
        c = loc - 11;
    else
        r = 5;
        c = loc - 15;
    end

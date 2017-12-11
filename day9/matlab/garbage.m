fid = fopen('../input.txt');
str = fscanf(fid, '%s\n');

group_score = 0;
total_score = 0;
garbage_count = 0;
len = length(str);
i = 1;
while i <= len
    switch str(i)
        case '{'
            group_score = group_score + 1;
        case '}'
            total_score = total_score + group_score;
            group_score = group_score - 1;
        case '<'
            while true
                i = i + 1;
                if str(i) == '!'
                    i = i + 1;
                elseif str(i) == '>'
                    break
                else
                    garbage_count = garbage_count + 1;
                end
            end
    end
    i = i + 1;
end

fprintf(1, '%d\n%d\n', total_score, garbage_count)

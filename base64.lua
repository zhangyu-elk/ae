local b = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_/'

-- encoding
function enc(data)
    return ((data:gsub('.', function(x) 
        local r, a = '', x:byte()
        for i = 8, 1, -1 do
            r = r .. (a % 2^i - a % 2^(i-1) > 0 and '1' or '0')
        end
        --1, 高字节在前
        --2,  a%2^4=a%00010000=0000xxxx相当于和00001111进行与操作, (a % 2^i - a % 2^(i-1) > 0就可以判断第i位是否是1

        return r
    end) .. '0000'):gsub('%d%d%d?%d?%d?%d?', function(x)
        --每三个字节转变为4个字节, 如果多出1个8位扩展为12位, 如果多出2个16位扩展为18位; 所以最多添加4个0
        if (#x < 6) then 
            return '' 
        end

        local index = 0
        for i = 1, 6 do 
            index = index + (x:sub(i, i) == '1' and 2^(6-i) or 0)
        end

        return b:sub(index+1, index+1)
    end))
end

-- decoding
function dec(data)
    data = string.gsub(data, '[^'..b..']', '')
    --只允许编码的字符
    return (data:gsub('.', function(x)
        local ret, f = '', (b:find(x)-1)
        for i=6, 1, -1 do 
            ret = ret .. (f % 2^i - f % 2^(i-1) > 0 and '1' or '0')
            --将数字转为二进制
        end
        return ret
    end):gsub('%d%d%d?%d?%d?%d?%d?%d?', function(x)
        if (#x ~= 8) then 
            return '' 
        end
        local c = 0
        for i = 1, 8 do 
            c = c + (x:sub(i,i) == '1' and 2^(8-i) or 0) 
        end
        --每8位作为一个二进制数转变为10进制
        return string.char(c)
        --将ASCII重新转变为字符
    end))
end
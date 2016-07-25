    
s = serial('COM5','BaudRate',38400);
set(s,'Terminator','CR');                        %set(s,'Terminator','CR');
fopen(s);
f = fopen('MyNewData.txt','a+');       %a+ r/w append data

while 1
a = fscanf(s);             %a=fscanf(s,'%d',14)
%a
%end

%f = fopen('MyData.txt','a+');       %a+ r/w append data
fprintf(f,'%s\n',a);
end

fclose(f);
fclose(s);      

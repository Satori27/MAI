first_str = str(input())
print(first_str)

n=0;
while first_str[n]!=" ":
    n+=1

n+=1
for i in range(n, len(first_str)):

    # if(first_str[i]==" "):
    #     continue
    
    print("value", first_str[i-1])
    string = first_str[i]
    if first_str[i+2]=="F":
        string+=" False"
        i+=5
    if first_str[i+2]=="T":
        string+=" True"
        i+=4
    # print(first_str[i+1])
    print("string", string)
    variable_name, value = string.split(" ")
    # value = eval(value.capitalize())
    globals()[variable_name] = value

    # print(first_str[i])
    # stro = ""
    # stro = first_str[i]
    # stro+=' =='
    # if(first_str[i+2]== "F"):
    #     stro+=" False"
    #     i+=7
    # if(first_str[i+2]== "T"):
    #     stro+=" True"
    #     i+=6
    # print(f"1{stro}")
    # eval(stro)




strlogical=""
for i in range(0, n):
    strlogical+=first_str[i]

eval(strlogical)
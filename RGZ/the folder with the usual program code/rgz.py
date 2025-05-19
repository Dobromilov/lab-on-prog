def input_func(arr,st,i,j):
    ind=0
    for y in range(i):
        for x in range(j):
            arr[y][x]=st[ind]
            ind += 1
    return mas

def output_func(arr,i,j):
    for x in range(j):
        for y in range(i):
            print(arr[y][x],end="")

i=int(input())
j=int(input())
mas = [0] * i
for p in range(i):
    mas[p] = [0] * j
st=input()[::-1].zfill(24).replace('0',' ').replace(' ','_')[::-1]
input_func(mas,st,i,j)
output_func(mas,i,j)
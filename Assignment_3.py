import numpy as np

class Matrix():
    def __init__(self):
        self.mat=np.zeros((m,n),dtype=int)
    def add(self,m1,m2):
        for i in range(m):
            for j in range(n):
                # self.mat[i][j]=m1[i][j]+m2[i][j]
                self.mat[i,j]=m1[i,j] + m2[i,j]
        print("Addition of matrix is:\n",self.mat)
        
    def sub(self,m1,m2):
        for i in range(m):
            for j in range(n):
                self.mat[i][j]=m1[i][j] - m2[i][j]
        print("Substraction of matrix is:\n",self.mat)
        
    def mult(self,m1,m2):
        self.mat=np.zeros((m,n),dtype=int)
        for i in range(m):
            for j in range(n):
                for k in range(n):
                    self.mat[i][j]+=m1[i][k] * m2[k][j]
        print("Multiplication of matrix is:\n",self.mat)
        
    def trans(self,m1):
        for i in range(m):
            for j in range(n):
                self.mat[j][i] = m1[i][j]
        print("Transpose of matrix is:\n",self.mat)


print("""Operations on Matrix are
1.Matrix input
2.Addition
3.Substraction
4.Mutiplication
5.Transpose
6.Exit""")
while(True):
    num=int(input("Enter the operation number:"))
    
    if num==1:
        m=int(input("Enter the number of coloumn:"))
        n=int(input("Enter the number of rows:"))

        mat1=np.zeros((m,n),int)
        mat2=np.zeros((m,n),int)

        for i in range(m): 
            for j in range(n):
                mat1[i][j]=int(input(f"Enter the {i,j}th element for matrix A:"))
        for i in range(m):
            for j in range(n):
                mat2[i][j]=int(input(f"Enter the {i,j}th element for matrix B:"))
        obj=Matrix()
        
    elif num==2:
        obj.add(mat1,mat2)
        
    elif num==3:
        obj.sub(mat1,mat2)
        
    elif num==4:
        obj.mult(mat1,mat2)

    elif num==5:
        obj.trans(mat1)
        obj.trans(mat2)

    elif num==6:
        print("Exited successfully")
        break


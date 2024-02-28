import numpy as np
class Search():
    def linear(self,arr,k):
        print("Using Linear Search:")
        b=False
        for i in range(arr.size):
            if arr[i]==k:
                print(f"The element is found at {i}th index\n")
                b=True
                break
        if b==False:    
            print("Element is not found\n")
            
    def sentinel(self,arr,k):
        print("Using Sentinel Search:")
        arr=np.append(arr,k)
        b=False
        for i in range(arr.size):
            if arr[i]==k and i<arr.size:
                print(f"The element is found at {i}th index\n")
                b=True
                break
        if b==False:    
            print("Element is not found\n")        
                
                

print("""Operations are
    1.Add array
    2.Linear Search
    3.Sentinel Search
    4.Exit""")
while(True):
    m=int(input("Enter the operation number:"))
    
    if m==1:
        n=int(input("\nEnter the number of elements:"))
        arr=np.zeros((n),dtype=int)
        for i in range(n):
            arr[i]=int(input("Enter the element:"))

        ser=int(input("Enter the element you want to search:"))    
        print("\n")
        obj=Search()     
           
    elif m==2:
        print(arr)
        obj.linear(arr,ser)
        
    elif m==3:
        print(arr)
        obj.sentinel(arr,ser)
        
    elif m==4:
        print("Exited successfully")
        break  
    else:
        print("Enter valid operation")
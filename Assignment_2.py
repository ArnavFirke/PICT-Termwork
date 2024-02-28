class String:
    def __init__(self,str):
        self.str=str
        self.str+=" "
    def longestword(self):
        longestLength=0
        longestWord=""
        count=0
        word=""
        for i in range(len(self.str)):
            if self.str[i]==" ":
                if longestLength<count:
                    longestLength=count
                    longestWord=word
                count=0
                word=""

            # elif i==len(self.str)-1:
            #     count+=1
            #     word+=self.str[i]
            #     if longestLength<count:
            #         longestLength=count
            #         longestWord=word
            
            else:
                count+=1
                word+=self.str[i]

        print("The Longest word is:",longestWord,"\n")


    def char(self):
        sub=input("Enter the character:")
        count=0
        for i in range(len(self.str)):
            if self.str[i]==sub:
                count+=1
        print(f"The Frequency of char {sub} is:",count,"\n")

    def palindrome(self):
        if self.str==self.str[-1::-1]:
            print(f"{self.str} is a panlindrome.","\n")
        else:
            print(f"{self.str} is not a panlindrome.","\n")
    
    def position(self):
        substring=input("Enter the sub string:")
        x=len(self.str)
        y=len(substring)

        if y==1:
            for i in range(x):
                if self.str[i]==substring:
                    print(f"{substring} is at {i}th position of {self.str}","\n")
                    break
        else:
            for i in range(x-y+1):
                for j in range(y):
                    if self.str[i+j] != substring[j]:
                        continue
                    if j + 1 == y:
                        print(f"{substring} is at {i}th position of {self.str}","\n")


    def occurence(self):
        EachWord = {}
        word = ""
        for i in range(len(self.str)):
            if self.str[i] == " ":
                if word in EachWord.keys():
                    EachWord[word] += 1
                else:
                    EachWord[word] = 1
                word = ""

            # elif i == len(self.str) - 1:
            #     word += self.str[i]
            #     if word in EachWord.keys():
            #         EachWord[word] += 1
            #     else:
            #         EachWord[word] = 1

            else:
                word += self.str[i]
        print("Occurence of each word is:",EachWord,"\n")    

# Taking string as input  
string=input("Enter the String:")
s=String(string)

print("""Operations are
1.Longest word
2.Frequency of word
3.Panlindrome
4.position of substring
5.occurence of each word
6.Exit""")
while(True):
    n=int(input("Enter the operation number:"))
    if n==1:
        s.longestword()
        
    elif n==2:
        s.char()
        
    elif n==3:
        s.palindrome()

    elif n==4:
        s.position()

    elif n==5:
        s.occurence()

    elif n==6:
        print("Exited successfully")
        break
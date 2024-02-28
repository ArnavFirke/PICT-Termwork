'''  Declaring empty lists '''
cls_lst = []
cric_lst = []
bad_lst = []
foot_lst = []
cricbad = []
cric_bad = []
not_cricbad = []
list_4 = []

'''  Taking input for total students  '''

total_stud = int(input('Enter total number of students: '))
for i in range(total_stud):
    roll = int(input('Enter roll numbers: '))
    cls_lst.append(roll)
# print(cls_lst)

'''  Taking input for cricket list  '''

cric_stud = int(input('Enter no of students playing cricket: '))
for i in range(cric_stud):
    roll_cric = int(input('Enter roll numbers: '))
    cric_lst.append(roll_cric)
# print(cric_lst)

'''  Taking input for badminton list  '''

bad_stud = int(input('Enter no of stud playing badminton: '))
for i in range(bad_stud):
    roll_bad = int(input('Enter roll numbers: '))
    bad_lst.append(roll_bad)
# print(bad_lst)

'''   Taking input for football list   '''

foot_stud = int(input('Enter no of stud playing football: '))
for i in range(foot_stud):
    roll_foot = int(input('Enter roll numbers: '))
    foot_lst.append(roll_foot)
# print(foot_lst)
#print(min(cric_stud, bad_stud))

print('''Operations:
1:students playing both cricket and badminton
2:students playing either cric or badminton but not both
3:students playing neither cricket nor badminton
4:students playing cric and foot but not badminton
5:students playing none of game
6:students playing either game
7:Exit''')
while (True):
    n = int(input("Enter the operation:"))

    if n == 1:
        '''  Calculating no of students playing both cricket and badminton '''

        # for i in range(cric_stud):
        #     if cric_lst[i] in bad_lst:
        #         #print(cric_lst[i])
        #         cricbad.append(cric_lst[i])
        # for i in range(cric_stud):
        #     for j in range(bad_stud):
        #         if cric_lst[i]==bad_lst[j]:
        #             cricbad.append(cric_lst[i])
        # print('Students playing both cricket and badminton:', cricbad)
        for i in range(cric_stud):
            if cric_lst[i] in bad_lst:
                cricbad.append(cric_lst[i])
        print('Students playing both cricket and badminton:', cricbad)

    elif n == 2:
        '''  Code for getting students playing either cric or bad but not both  '''
        for i in range(cric_stud):
            if cric_lst[i] not in cricbad:
                cric_bad.append(cric_lst[i])
        for i in range(bad_stud):
            if bad_lst[i] not in cricbad:
                cric_bad.append(bad_lst[i])
        print("Students playing either cricket or badminton but not both:", cric_bad)

    elif n == 3:
        '''  Code for getting students playing neither cricket nor badminton '''
        for i in range(total_stud):
            if cls_lst[i] not in cric_lst+bad_lst:
                not_cricbad.append(cls_lst[i])

        print('Students not playing cricket or badminton:', not_cricbad)

    elif n == 4:
        '''  Code for students playing cric and football but not badminton  '''
        cricunfoot = cric_lst + foot_lst
        for i in range(len(cricunfoot)):
            if cricunfoot[i] not in bad_lst:
                list_4.append(cricunfoot[i])
        print('Students playing cric and football but not badminton:', list_4)
    elif n == 5:
        '''  Code for students playing none of game  '''
        aunbunc = cric_lst + bad_lst + foot_lst
        list_5 = []
        for i in range(total_stud):
            if cls_lst[i] not in aunbunc:
                list_5.append(cls_lst[i])
        print('Students playing none:', list_5)
    elif n == 6:
        '''  Code for students playing either game  '''
        list_6 = []
        for i in range(total_stud):
            if cls_lst[i] in aunbunc:
                list_6.append(cls_lst[i])
        print('Students playing either of game:', list_6)
    elif n == 7:
        print("Exited")
        break


// TODO(student)

Group name: 
  BestTeam 

Programmers:
    Qiqi Hu, 
    Reiner Optiz

# Contribution by each person
  50% for each

# Data structures used
  Queue and Binary Search Tree

# clang-tidy Error that cannot fix
1. constructor does not initialize these fields: balance     [cppcoreguidelines-pro-type-member-init,-warnings-as-errors]
Account::Account(string firstName, string lastName, int idNum)
^

2. std::move()

3. class 'BSTree' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [cppcoreguidelines-special-member-functions,-warnings-as-errors]

# update BankTransIn.txt to be 100% covered

O Cash Johnny 1001
D 10010 542
D 10011 1542
D 10012 5442
D 10013 7540
D 10017 5442
D 10016 7542
D 10011 1500
D 10012 5000
D 10013 7000
D 10017 6543
D 10016 7576
W 10017 1000
W 10016 65
W 10010 72
T 10017 54 10015
W 10017 20000
H 1001
O Williams Hank 1253
D 12530 10000
D 12531 10000
D 12532 10000
D 12533 10000
D 12534 10000
D 12535 10000
D 12536 10000
D 12537 10000
D 12538 10000
D 12539 10000
H 12534
W 12532 10000
W 12533 5000
T 12530 15000 12536
T 12536 10000 12530
T 12536 5000 12531
T 12532 15000 12537
T 12537 10000 12532
T 12537 5000 12533
T 12531 15000 12536
T 12536 10000 12531
T 12536 5000 12530
T 12533 15000 12537
T 12537 10000 12533
T 12537 5000 1253
T 12530 20001 12536
T 12532 20001 12537
T 12531 20001 12536
T 12533 20001 12537
D 12530 10000
D 12532 10000
H 1253
T 12539 765 43567
O Nelson Willie 9876
O Willis Bob 9876
O Horatio Hornblower 5768
T 12530 25000 57680
T 12530 25000 57682
H 1253
D 57686 100
D 57687 45665
D 57680 4548
D 57683 124568
W 57681 22000 
W 57862 20000  
T 57683 4000 12530
T 57683 100 57682 
T 57686 1000 57680
D 57684 568
W 57685 10000
W 57682 50
H 5768
D 18869 50
W 18865 50
T 18868 50 57682
T 57682 50 18868
D 57681 500
W 57680 9000
W 57682 100
D 57680 9000
D 57682 100
W 57680 15000
W 57682 130000
H 1886


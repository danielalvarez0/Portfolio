Name: Daniel Alvarez
date: 11/19/17
Time Invested: 2 hours

resources used: c++ documentation on vectors, shared_ptrs, and unique_pointers. I also found several answers to questions on
stack overflow that helped me fix several of the problems I encountered.

In this project I created a new UniqueStrBlob class that used a unique_ptr to access a vector of strings. 
The uniqueStrBlob class was created by modifying a class named StrBlob that performed the same functions I was 
trying to accomplish, but used shared pointers rather than unique pointers. I modified the existing code to use unique 
pointers and then added two functions. I added a makeStrBlob function that passed the data from the UniqueStrBlob to a new
 StrBlob, leaving the original UniqueStrBlob a nullptr. Then I overloaded the + operator for the UniqueStrBlob class
 to append the vector of strings contained in the right hand opperand to the left hand opperand. After I got those functions 
 completed I modified the test driver for StrBlob to test my Unique StrBlob class. When I included a line of code
 trying to dirrectly assign one UniqueStrBlob to another (UniqueStrBlob1 = UniqueStrBlob2;) the code would not compile correctly
 which is what should happen.
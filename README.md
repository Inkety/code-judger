# Code Judger
A super simple and portable code judger that you can use to check if your program outputs the right data, inspired by how DMOJ does it (https://dmoj.ca).
It's also not a very good judge, but hey, it works.

# Instructions
Test cases should be put into the DATA folder.
Each test case needs an input and an output file, containing the input and the expected output.
They should be named startin from 0, with 0.in, 0.out, 1.in, and 1.out, and so on.

Line 1 of the config.txt file should be the time limit, and line 2 of the config.txt file should be the absolute time limit, both measured in seconds.
The absolute time limit is approximately when the judge will stop running the code. The judge will not stop running it early if it finishes early.
The status code TLEK means that the program was killed because it took longer than the absolute time limit.
The next lines denote the amount of points that each test case will be worth if the answer is accepted, each corresponding to one test case.

# Link Time Optimization(tlo)

## 比较编译选项使用-flto 和不使用在性能上的差异
- Compile options with *lto*:gcc -flto -o2 main.c -L. -lmath -o main
- Compile options without lto: gcc -O2 main.c -L. -lmath1 -o main_no_lto

## test reslut 
| test command        | result          
| ------------------- |:-------------:|
| time ./main         | real    0m0.005s <br> user    0m0.001s <br> sys     0m0.004s |
| time ./main_no_lto  | real    0m0.005s <br> user    0m0.000s <br> sys     0m0.004s |

## conclusion
No significant difference, maybe the test round is not enough

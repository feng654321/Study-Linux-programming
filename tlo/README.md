# Link Time Optimization(tlo)

## 比较编译选项使用-flto 和不使用在性能上的差异
- Compile options with *lto*:gcc -flto  main.c -L. -lmath -o main
- Compile options without lto: gcc main.c -L. -lmath1 -o main_no_lto

## test reslut 
| test command        | result          
| ------------------- |:-------------:|
| time ./main         | real    0m0.617s <br> user    0m0.617s <br> sys     0m0.000s |
| time ./main_no_lto  | real    0m0.631s <br> user    0m0.631s <br> sys     0m0.000s |

## conclusion
Has significant difference



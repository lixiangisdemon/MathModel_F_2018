# 2018-研究生数学建模F题

模拟退火解决登机口分配问题
解决该问题的代码分成三个文件。
第一个时DataStruture.h 它包含了一些定义的结构体和几个常用的函数。
第二个文件AirPort.hpp是对类文件，它将解决本问题所有的实现都封装起来，包括读取数据并生成论文中所用到的集合和参数；用模拟退火求最优化；对优化的航班分配作统计。
第三个文件Run.cpp是主程序入口。
代码中主要用了三个结构体Pucks, Tickets 和 Gates 用于读取文件中的相应的信息。

```
   另外为了方便对数据的操作，我们把题目提供的EXCEL文件里的内容拷贝到txt文件，在进行操作。这三个数据文件也在附录中分别为对于航班记录的data1.txt, 
   对应乘客记录的data2.txt 和对应登机口信息的data3.txt.
```

代码的运作方式如下：
   1.	进入主函数main()根据你的输入来相应调用 solution1(), solution2(), solution3()来解决三个问题中你选择解决的问题。
   2.	进入某个solution函数会执行：

      1.	提取数据并建立解决该问题用到的集合以及参数，如问题1中要用到集合N，K_i，参数a_i, d_i（见论文）。
      2.	建立好解决该问题的目标函数，和变量（见论文）
      3.	用模拟退火算法优化目标函数。
      4.	优化结束，得到一个最优解，输出航班分配结果和相应的优化的目标值。统计出问题中要求的一些数值。

   3.	算法结束。

本文的程序实现全部是用C++实现，一些函数是使用的C++的官方库里的函数，没有调用第三方库，所有在不同的电脑上不同的系统上都可以运行或编译成功。
程序的运行：

   1.	Windows上可以使用Visual Studio 建立项目，将代码添加到项目中来编译运行（AirPort.hpp是头文件）。也可以使用其他的IDE工具编译。
   2.	Mac OS， Linux上，创建一个文件夹，比如叫code，将代码和要用到的数据data1.txt, data2.txt, data3.txt放到一个code文件夹中。然后打开终端(terminal)进入code目录，然后输入:

      g++ run.cpp -o run -std=c++11

   就会编译程序最后生成一个叫run的可执行文件。在终端中之间输入 ./run 就能运行。
注意：

      a)	程序中默认将data1.txt的数据文件的目来前缀设为运行程序的目来下，你可以按情况更改 AirPort.hpp 里的那个 变量 “prefix”。
      b)	代码中，一些中文上的输出放到在别的机器上或别的系统上可能乱码，可以把他改成英文。

对每个问题程序会输出两个文件，第一的是航班分配表，第二个文件含有求出的最优目标值和一些对航班分配的统计数值。

# 运行与运行结果
运行时输入命令

   ./run 

运行时保证data1.txt, data2.txt和data3.txt与run文件在同一目录下。运行结果如下所示：

      iterations: 495000
      tempature: 0.0184859    cost1: 67       cost2: 56

      iterations: 500000
      tempature: 0.0172708    cost1: 67       cost2: 56

      iterations: 505000
      tempature: 0.0161356    cost1: 67       cost2: 56

      iterations: 510000
      tempature: 0.0150749    cost1: 67       cost2: 56

      iterations: 515000
      tempature: 0.014084     cost1: 67       cost2: 56

      iterations: 520000
      tempature: 0.0131583    cost1: 67       cost2: 56

      iterations: 525000
      tempature: 0.0129757    cost1: 67       cost2: 56

      iterations: 530000
      tempature: 0.0121228    cost1: 67       cost2: 56

      iterations: 535000
      tempature: 0.0113259    cost1: 67       cost2: 56

      iterations: 540000
      tempature: 0.0105814    cost1: 67       cost2: 56
      pass
      ...
      complete!

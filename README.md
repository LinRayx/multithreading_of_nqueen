# n皇后多线程

线程采用了线程池的写法。n皇后算法采用位运算形式。多线程的方法就是枚举第一行放置n皇后的方案。


"->"是一个尾置限定符，用来指明返回类型。
std::future<类型>是一个异步的方法，用来创建线程, std::future<return_type> res = task->get_future();中的res是一个未来的值，即当前还没有值，只有当线程运行完，res才会有值。
std::result_of<函数名，参数> 能自动推断函数的返回值。
std::bind(函数，参数) 相当于构造一个函数。
using return_type = typename std::result_of<F(Args...)>::type中的typename只是声明一个类型，这里的using和typedef差不多。


std::future<>的get会阻塞线程，直到获取到结果为止，所以不能再enqueue的时候直接get，这样就相当于单线程运行。
比较好的办法是采用future的wait_for方法，判断是否该线程已经返回了结果，如果是的话，再调用get。




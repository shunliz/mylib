#Add a variable to simplify the writing of the makefile.
OBJS = main.o dlist.o Locker.o locker_pthread.o

#The make can find the dependency .c file of the object .o file.
#You can remove the filename.c of the oject filename.o from dependency.

init:
	@echo Making the Makefile...................

main:$(OBJS)
	gcc -o main $(OBJS)

main.o: dlist.h Locker.h locker_pthread.h
	gcc -c main.c

dlist.o: dlist.h
	gcc -c dlist.c
	
Locker.o: Locker.h
	gcc -c Locker.c
	
locker_pthread.o:Locker.h
	gcc -c locker_pthread.c

#这个规则的意思是，所有的[.d]文件依赖于[.c]文件，
#“rm -f $@”的意思是删除所有的目标，也就是[.d]文件，
#第二行的意思是，为每个依赖文件“$<”，也就是[.c]文
#件生成依赖文件，“$@”表示模式“%.d”文件，如果有一个
#C文件是name.c，那么“%”就是“name”，“$$$$”意为一个
#随机编号，第二行生成的文件有可能是“name.d.12345”，
#第三行使用sed命令做了一个替换，关于sed命令的
#用法请参看相关的使用文档。第四行就是删除临时文件。 
	
%.d: %.c 
	@set -e; rm -f $@; \ 
	$(CC) -M $(CPPFLAGS) $< >; $@.$$$$; \ 
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ >; $@; \ 
	rm -f $@.$$$$ 

#-w show the enter and leaving the subdirectory message.
subsystem: 
	cd subdir && $(MAKE) 
	


#add - before command indicate that ignore the error of the command exec.	
clean: 
	-rm -f main *.o
	
	
#在Unix世界中，软件发布时，特别是GNU这种开源软件的发布时，
#其makefile都包含了编译、安装、打包等功能。我们可以参照这种规则来书写我们的makefile中的目标。 
#
#     “all” 
#        这个伪目标是所有目标的目标，其功能一般是编译所有的目标。 
#     “clean” 
#        这个伪目标功能是删除所有被make创建的文件。 
#     “install” 
#        这个伪目标功能是安装已编译好的程序，其实就是把目标执行文件拷贝到指定的目标中去。 
#     “print” 
#        这个伪目标的功能是例出改变过的源文件。 
#     “tar” 
#        这个伪目标功能是把源程序打包备份。也就是一个tar文件。 
#     “dist” 
#        这个伪目标功能是创建一个压缩文件，一般是把tar文件压成Z文件。或是gz文件。 
#     “TAGS” 
#       这个伪目标功能是更新所有的目标，以备完整地重编译使用。 
#     “check”和“test” 
#        这两个伪目标一般用来测试makefile的流程。

#自动变量说明：
#$@ 
#    表示规则中的目标文件集。在模式规则中，如果有多个目标，那么，"$@"就是匹配于目标中模式定义的集合。 
#
#$% 
#    仅当目标是函数库文件中，表示规则中的目标成员名。例如，如果一个目标是"foo.a(bar.o)"，那么，"$%"就是"bar.o"，"$@"就是"foo.a"。如果目标不是函数库文件（Unix下是[.a]，Windows下是[.lib]），那么，其值为空。 
#
#$< 
#    依赖目标中的第一个目标名字。如果依赖目标是以模式（即"%"）定义的，那么"$<"将是符合模式的一系列的文件集。注意，其是一个一个取出来的。 
#
#$? 
#    所有比目标新的依赖目标的集合。以空格分隔。 
#
#$^ 
#    所有的依赖目标的集合。以空格分隔。如果在依赖目标中有多个重复的，那个这个变量会去除重复的依赖目标，只保留一份。 
#
#$+ 
#    这个变量很像"$^"，也是所有依赖目标的集合。只是它不去除重复的依赖目标。 
#
#$*  
#   这个变量表示目标模式中"%"及其之前的部分。如果目标是"dir/a.foo.b"，并且目标的模式是"a.%.b"，那么，"$*"的值就是"dir/a.foo"。这个变量对于构造有关联的文件名是比较有较。如果目标中没有模式的定义，那么"$*"也就不能被推导出，但是，如果目标文件的后缀是make所识别的，那么"$*"就是除了后缀的那一部分。例如：如果目标是"foo.c"，因为".c"是make所能识别的后缀名，所以，"$*"的值就是"foo"。这个特性是GNU make的，很有可能不兼容于其它版本的make，所以，你应该尽量避免使用"$*"，除非是在隐含规则或是静态模式中。如果目标中的后缀是make所不能识别的，那么"$*"就是空值。 

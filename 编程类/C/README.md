**函数指针**

最简单粗暴的shellcode调用方法，VirtualAlloc用以开辟堆空间，返回该空间的起始地址，通过memcpy将存放shellcode的数组拷贝到堆空间内，通过函数指针的方式调用该堆空间。

> 生成的shellcode已经是机器码了，因此计算机能够直接运行，而不需要进行编译

------

**UUID**

通过将加密成以UUID形式的shellcode通过在内存中解密为原始shellcode（通过UuidFromStringA进行解密），通过EnumSystemLocalesA函数进行回调调用。

-----




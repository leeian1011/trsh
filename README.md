## TRash SHell  

While working on [dash](https://github.com/leeian1011/dsh) I learnt a lot about how the shell works and also about
child processes and why certain programs can be made externally and why some are built-in, most of them tend to be performance issues
but others are process logic issues like 'cd'!

I've decided to make a mini simple shell that imitates the behaviour of typical shells like bash from scratch with C to further my understanding!

## Side Notes
Before making this I learnt a bit about OOP with Java but it didnt really click but using [this](https://www.youtube.com/watch?v=ubt-UjcQUYg&t=684s)
as a reference and without copying entirely one for one, I understand better why OOP is likeable, having methods making this would help a lot.

Working with strings really help me understand pointers even more with how you can technically traverse back-to-back memory addresses
the same way you would traverse a linked list in C!

Despite knowing this, I feel that indexing into a `char *` with '/[x]' syntax is much better and more readable honestly.

So I was messing around with the shell trying all sort of edge cases and one particular one came up. When running "grep ls", the process
loops on forever, which is to be expected, but when I force quit with `ctrl + c`, it terminates the shell process altogether and returns me to 
my original zsh shell, so a simple search online tells me about the `sys/signal.h` library and how certain signals have to be handled.

What nobody I've ever seen mentioned was that the `signal()` function accepts a whole function as an argument ???
FUNCTION POINTERS ??? WHAT ??? 










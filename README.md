# Chess Engine
_Why have I done this_?
I have been studying the amazing book _computer systems a programmer's perspective_ so I wanted to put in practice the topics I have cover so far, some of them are:
1. The C programming language.
2. How information is stored and represented in computers.
3. Basic assembly
4. High performance C programming.

I was looking for a project to implement this topics and after some researching I found a chess engine, if you ask Wikipedia what a chess engine is : 
> In [computer chess](https://en.wikipedia.org/wiki/Computer_chess "Computer chess"), a **chess engine** is a [computer program](https://en.wikipedia.org/wiki/Computer_program "Computer program") that analyzes [chess](https://en.wikipedia.org/wiki/Chess "Chess") or [chess variant](https://en.wikipedia.org/wiki/List_of_chess_variants "List of chess variants") positions, and generates a move or list of moves that it regards as strongest.

This is a really good fit because it needs to be really fast to analyze a lot of chess positions, evaluate those positions and decide the next move to play, also the structures that support the engine have to be lighweight and efficient because you will store a lot of them.  

### Resources I used
This one is recent, really good structure and easy to follow, is written in _Rust_  but still really useful.
- https://rustic-chess.org/board_representation/zobrist_hashing.html

Not as recent but its really popular in the chessprogramming community.
- https://www.youtube.com/watch?v=bGAfaepBco4&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg

This one is not that well organized but you is in _C_ so you can see how thigs are implementd.
- https://www.youtube.com/watch?v=QUNP-UjujBM&list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs

The **best** online resource for chess programming.
- https://www.chessprogramming.org/Getting_Started

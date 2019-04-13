# SLR(1) Table Generator

Generates a table from a Context-Free Grammar to be printed or used as a base for Syntax Analysis.

## Getting Started

### Prerequisites

- A Context-Free Grammar to be used as an input following the format bellow:

```
<Non_Term_1> <Non_Term_2> .. <Non_Term_N>
<Terminal_1> <Terminal_2> .. <Terminal_N>
<Rule_1>
<Rule_2>
<Rule_3>
........
<Rule_N>
```
* **Non_Term_1** is the **Start Variable**.
* **"@"**, **"$"** and **"SS"** can't be used as **Non Terminals** nor **Terminals**. 
* **ALL** Non Terminals and Terminals used within the rules must be declared beforehand.

**Example:**

```
T A
i ; [ ] e =
T i A ;
A [ e ]
A = e
A 
```

### Installing

Compile **srt1.cpp** and run passing the Grammar through **STDIN**.

- Compile
```
g++ -o srt1 srt1.cpp
```

- Run (Linux)
```
srt1 < grammar
```

## Built With

* C++

## Authors

* **Pedro Pontes** - [Github](https://github.com/pedroccrp)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

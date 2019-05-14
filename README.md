# SLR(1) Table Generator

Generates a table from a Context-Free Grammar to be printed or used as a base for Syntax Analysis.

## Getting Started

### Pre-requisites

- A Context-Free Grammar to be used as an input following the format bellow:
  
  * **Non Terminals** after the #NON_TERMS line
  * **Terminals** after the #TERMS line
  * **Rules** after the #RULES line

**Model:**

```
#NON_TERMS
<Non_Term_1> <Non_Term_2> .. <Non_Term_N>
#TERMS
<Terminal_1> <Terminal_2> .. <Terminal_N>
#RULES
<Rule_1>
<Rule_2>
<Rule_3>
........
<Rule_N>
```

- Obs:

  * **Non_Term_1** is the **Start Variable**
  * **"."**, **"$"** and **"SS"** can't be used as **Non Terminals** nor **Terminals**
  * **ALL** Non Terminals and Terminals used within the rules must be declared beforehand
  * Any number of **blank lines** or **spaces** are allowed between any statements
  
**Example:**

```
#NON_TERMS
T A

#TERMS
i ; [ ] e =

#RULES
T i A ;

A [ e ]
A = e
A 
```

### Installing

* Compile
```
make
```

* Run (Linux)
```
bin/slr1 < grammar
```

## Built With

* C++

## Authors

* **Pedro Pontes** - [Github](https://github.com/pedroccrp)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

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

**Comments:**

- Lines starting with an **#** will be **ignored** 

  * **#** must be the first character in line
  * #NON_TERMS, #TERMS and #RULES are special cases and shouldn't be used as comments

```
# This line will be ignored
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

### Program Output

* Stardard Output
    ```
    ------- Grammar ----------------------------------------------------------------------

    Variables:

        .........


    Rules:

        .........


    ------- Automata --------------------------------------------------------------------

    ------------- <State Number> ---------------------

    Rules: 

        .........

    Transitions: 

        .........

    Type: 

        <ACC or REDUCE>


    ------- First ----------------------------------------------------------------------

    -----------------------

    <Non Terminal>

        <Non Terminal's First(1)>


    ------- Follow ----------------------------------------------------------------------

    -----------------------

    <Non Terminal>

        <Non Terminal's Follow(1)>


    ------- Table -----------------------------------------------------------------------

        .........


    ------- Parsed Table -----------------------------------------------------------------------

    {
        {<State Number>, {
            <Terminal or Non Terminal>, {<Transition Type>, <Reduce Rule Production Size>, <Next State>, <Reduce Rule Head>}}
        },
        ..................
    }

    ```

    * Parsed Table

        * Transition Types:
            
            * 0 - NONE
            * 1 - SHIFT
            * 2 - REDUCE
            * 3 - ACC

        * Reduce Rule Production Size

            * Only use if transition type is REDUCE
            
        * Next State

            * Only use if transition type is SHIFT or NONE
            
        * Reduce Rule Head

            * Only use if transition type is REDUCE 


* Error Output
   
    ```
    Conflict: <State Number> <Non Terminal that generated conflict> <Terminal of conflict>
    ..................
    ```

## Built With

* C++

## Authors

* **Pedro Pontes** - [pedroccrp](https://github.com/pedroccrp)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

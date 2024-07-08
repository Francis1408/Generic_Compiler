# GENERIC COMPILER IMPLEMENTATION
## Compiladores - Centro Federal de Ensino Tecnologico de Minas Gerais (CEFET/MG) - 2023.2

```
Francisco Abreu Gonçalves - 20193002285
```

## 1. Overview
Development in C++ of a complete compiler for a generic programming language. 

## 2. Compiler Procedures
1. Lexixal Analysis & Symbol Table
2. Sintatic Analysis
3. Semantic Analysis

### 2.1. Lexical Analysis
The compiler reads each characther from the code file and groups them in sequences called **Lexems**. These structures contain **token types** which are identified by the following **DFA (Deterministic finite automaton):**

![datatext](https://github.com/Francis1408/Generic_Compiler/blob/main/img/Screenshot%20from%202024-07-08%2017-47-30.png)

### 2.2. Syntatic Analysis
The compiler "eats" the **Lexems** and assembles a **derivation tree**. In order to do it, the compiler checks the following **LL(1) Gramatic**

```
<program>    	::= class indentifier [<decl-list>] <body>
<decl-list>     ::= <decl> “;”{<decl>, “;”}
<decl>          ::= <type> <ident-list>
<ident-list>    ::= identifier {“,” identifier}
<type>          ::= int | string | float
<body>          ::= “{” <stmt-list> “}”
<stmt-list>     ::=  <stmt> “;” {<stmt> “;”}
<stmt>		    ::= <assign-stmt> | <if-stmt> | <do-stmt> | <read-stmt> |	           <write-stmt>
<assign-stmt> 	::= identifier “=” <simple_expr>
<if-stmt>		::= if “(” <condition> “)” “{” <stmt-list> “}” <if-stmt’>
<if-stmt’>		::= λ | else “{” <stmt-list> “}”
<condition>		::= <expression>

<do-stmt>		::= do “{” <stmt-list> “}” <do-suffix>
<do-suffix>		::= while “(” <condition> “)”

<read-stmt>		::= read “(” identifier “)”
<write-stmt>		::= write “(” <writable> “)
<writable>		::= <simple-expr>

<expression>	::= <simple-expr> <expression’>
<expression’>	::= λ | <relop> <simple-expr>
<simple-expr>	::= <term> <simple-expr’>
<simple-expr’>	::= <addop> <term> <simple-expr’> | λ
<term>		    ::= <factor-a> <term’>
<term’> 		::= <mulop> <factor-a> <term’> | λ
<factor-a>		::= <factor> | “!” <factor> | “-” <factor>
<factor>		::= identifier | <constant> | “(” <expression> “)”
<relop>		    ::= “>” | “>=” | “<” | “<=”  | “!=” | “==”
<addop>  		::= “+” | “-” | “||”
<mulop>		    ::= “*” | “/” | “&&”

<constant>		::= integer_const | literal | real_const
```

### 2.3. Semantic Analysis
Compiler Verifies the semantic consistency between the program and the language defimition. In order to do it, the analyzer makes 3 types of verifications:[¹]. 
```
1. Type Verification
2. Unicity Verification
3. Class Verification
```

## How to run
1. On the */code* folder you can execute the following script commands:


```shell
$ make 
```
Build all the project dependencies


```shell
$ make clean
```
Remove all the project dependencies

2. After building all the dependecies run the follwing command to run the compiler

```shell
$ ./compiler <CODE FILE PATH>
```

[¹]: Check out the work report for futher information
# Ready, Set, Boole! 

**Ready, Set, Boole!** is an introduction to Boolean Algebra, designed to provide a comprehensive understanding of the mathematical foundations behind computational logic. This repository contains exercises and materials to help deepen the knowledge of Boolean algebra, set theory, and their critical role in computer science.

## Overview

This project aims to explain how computers perform operations through logical processes. By completing the exercises provided, participants will gain an understanding of how essential logic operations like AND, OR, and XOR are utilized in computational systems. The project is ideal for those new to Boolean algebra or those wishing to reinforce their understanding of the subject.

## Key Concepts

- **Boolean Algebra**: Learn the core concepts of Boolean operations, which serve as the building blocks of computer logic.
- **Set Theory**: Explore the relationship between logic and set theory, fundamental to both mathematics and computational theory.
- **Logic Gates**: Understand the mechanics of logic gates and their applications in creating computational units such as adders and multipliers.
- **Propositional Logic**: Become familiar with truth tables, propositional formulas, and logical forms such as Negation Normal Form (NNF) and Conjunctive Normal Form (CNF).

## Exercise 00: Bitwise Addition

The first exercise in this project introduces the implementation of a binary addition function using bitwise operations. The objective is to simulate the addition of two unsigned integers without employing standard arithmetic operators such as `+` or `-`.

### Objective:
- Write a function that takes two natural numbers as input and returns their sum.
  
### Constraints:
- Only the following operations are permitted:
  - Bitwise AND (`&`)
  - Bitwise OR (`|`)
  - Bitwise XOR (`^`)
  - Left Shift (`<<`)
  - Right Shift (`>>`)
  - Basic assignment (`=`) and comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`).

The function adds two numbers by iteratively calculating the carry using the AND operation and shifting it to the left. The XOR operation is used to compute the partial sum without the carry. This process continues until no more carry is left, at which point the XOR result represents the final sum.

This exercise demonstrates how fundamental bitwise operations can replace conventional arithmetic in specific low-level computational contexts, highlighting the efficiency of logic-based computation.

---

## Exercise 01: Bitwise Multiplication

The second exercise extends the logic-based approach by implementing a binary multiplication function using bitwise operations, simulating the multiplication of two unsigned integers without using the `*` operator.

### Objective:
- Write a function that multiplies two natural numbers using bitwise operations.

### Constraints:
- Only the following operations are permitted:
  - Bitwise AND (`&`)
  - Bitwise OR (`|`)
  - Bitwise XOR (`^`)
  - Left Shift (`<<`)
  - Right Shift (`>>`)
  - Basic assignment (`=`) and comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`).

The function employs a technique akin to long multiplication, where each bit in the multiplier is examined. If the current bit is set (i.e., equal to 1), the multiplicand is added to the result, shifted accordingly based on the bit’s position. This process repeats for every bit in the multiplier. The key bitwise operation here is shifting the multiplicand left to simulate powers of two.

This exercise showcases how bitwise operations can efficiently handle multiplication, leveraging shifts and addition to perform the task without directly using the multiplication operator.

---

## Exercise 02: Gray Code Conversion

In this exercise, the objective is to implement a function that converts a given natural number into its equivalent **Gray Code** representation. Gray Code is a binary numeral system where two successive values differ in only one bit, which minimizes errors in digital communication and transmission.

### Objective:
- Write a function that converts an integer into its corresponding Gray Code.

### Constraints:
- The conversion must adhere to the rules of Gray Code, where each successive number differs by a single bit.

Gray Code can be generated by using a simple formula: 
- For any given number `n`, the Gray Code equivalent is computed as `n ⊕ (n >> 1)`.

This exercise provides an opportunity to explore how binary manipulations and bitwise operations can be applied to real-world digital systems, especially in error correction and data encoding. Gray Code is commonly used in scenarios where minimizing bit errors during transitions is critical, such as in position encoders and communication protocols.

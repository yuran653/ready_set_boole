# Ready, Set, Boole!

**Ready, Set, Boole!** presents Boolean Algebra and its significance in computational logic. It emphasizes key concepts such as Boolean operations and set theory, which are essential in the field of computer science.

## Overview

This project demonstrates how computers utilize logical processes to perform operations. Through a series of exercises, it shows how core logic operations, including AND, OR, and XOR, are implemented in computational systems. It provides a practical exploration of Boolean algebra, suitable for a broad audience, from those unfamiliar with the subject to those seeking to reinforce their understanding.

## Key Concepts

- **Boolean Algebra**: A mathematical framework for manipulating binary variables, serving as the foundation of computer logic. Boolean algebra allows for the representation and simplification of logical statements through operations such as conjunction, disjunction, and negation.
- **Set Theory**: A branch of mathematical logic that studies sets, collections of distinct objects. Set theory underpins much of modern mathematical logic and provides a basis for understanding relationships between collections, often expressed in terms of union, intersection, and complement.
- **Logic Gates**: The fundamental building blocks of digital circuits, which perform basic logical functions. These gates manipulate binary inputs (0s and 1s) to produce specific outputs, facilitating the creation of complex computational structures like adders and multipliers.
- **Propositional Logic**: A formal system in logic that deals with propositions, which can either be true or false. Propositional logic is used to create truth tables and represent logical formulas, such as those in Negation Normal Form (NNF) and Conjunctive Normal Form (CNF), which are crucial in computational problem-solving and decision-making.

---

## Exercise 00: Bitwise Addition

This exercise demonstrates the implementation of binary addition using bitwise operations, avoiding the use of conventional arithmetic operators such as `+` or `-`.

### Objective:
- Develop a function that takes two natural numbers and returns their sum using only bitwise operations.

### Constraints:
- Permitted operations:
  - Bitwise AND (`&`)
  - Bitwise OR (`|`)
  - Bitwise XOR (`^`)
  - Left Shift (`<<`)
  - Right Shift (`>>`)
  - Assignment (`=`)
  - Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)

The function calculates the sum by repeatedly determining the carry using the AND operation and shifting it left. The XOR operation is used to compute the sum without the carry. This process continues until the carry is eliminated, with the final XOR result representing the sum.

---

## Exercise 01: Bitwise Multiplication

This exercise introduces a method for binary multiplication using bitwise operations, simulating the multiplication of two unsigned integers without utilizing the `*` operator.

### Objective:
- Create a function that multiplies two natural numbers through bitwise operations.

### Constraints:
- Permitted operations:
  - Bitwise AND (`&`)
  - Bitwise OR (`|`)
  - Bitwise XOR (`^`)
  - Left Shift (`<<`)
  - Right Shift (`>>`)
  - Assignment (`=`)
  - Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)

The function implements a bitwise multiplication algorithm similar to long multiplication, examining each bit of the multiplier. When a bit is set, the multiplicand is added to the result, shifted based on the bit’s position. This process is repeated for all bits of the multiplier.

---

## Exercise 02: Gray Code Conversion

This exercise focuses on the conversion of a natural number into its Gray Code equivalent, a binary numeral system where two successive values differ by only one bit, widely used in error minimization during data transmission.

### Objective:
- Implement a function that converts an integer into Gray Code.

### Constraints:
- The conversion must follow the Gray Code rule, where each successive value differs by exactly one bit.

Gray Code is generated using the formula `n ⊕ (n >> 1)`, where `n` is the input number. This bitwise manipulation technique minimizes errors in scenarios requiring precise binary transitions, such as digital encoders and communication protocols.

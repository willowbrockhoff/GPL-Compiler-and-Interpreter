# GPL-Compiler-and-Interpreter
Built using **Flex, Bison, and C++**, this project implements a complete compiler front-end and interpreter for a typed, object-oriented, event-driven programming language. It demonstrates:

* Lexical analysis
* LALR parsing
* AST construction
* Static type checking
* Scoped symbol resolution
* Runtime execution
* Event dispatching
* Safe memory management in C++

The result is a robust, fully functional Game Program Langauge (GPL) interpreter capable of executing interactive game programs with strong type guarantees and clean resource management.

---

### What GPL Supports

**Typed Variables and Arrays**

GPL supports three primitive types:

* `int`
* `double`
* `string`

Variables may be declared with optional initializers:

```gpl
int x = 10;
double y;
string name = "Alice";
```

Arrays are also supported:

```gpl
int nums[5];
double values[10];
```

Array sizes are validated at parse time and must evaluate to integers.

---
**Expressions**
* Arithmetic operators: `+ - * / %`
* Relational operators: `< > <= >= == !=`
* Logical operators: `&& || !`
* Unary operators
* Parenthesized expressions
* Variable and array access
* Object attribute access

Expressions are parsed into an AST (Abstract Syntax Tree) and type-checked during parsing. Evaluation occurs at runtime.

Example:

```gpl
int result = (x + 3) * y;
```

Type rules enforce correctness, and invalid operations generate descriptive errors.

---

**Scoped Symbol Management**

The interpreter maintains:

* A stack of symbol tables
* Proper shadowing behavior
* Redeclaration detection
* Undefined-variable detection

Each variable or object is stored as a `Symbol` containing its type and value. Memory is managed safely using `unique_ptr` and disciplined destructor logic.

---

**Game Objects**

GPL includes five built-in game object types:

* `Rectangle`
* `Circle`
* `Triangle`
* `Pixmap`
* `Textbox`

Objects can be declared individually or as arrays:

```gpl
circle c;
rectangle r(x=50, y=50, w=200, h=100);
triangle shapes[5];
```

Objects expose typed attributes such as:

```gpl
c.radius
r.x
r.visible
shapes[3].y
```

Attribute access is type-safe and validated during parsing. Invalid attribute references produce clear semantic errors.

---

**Statements**

GPL supports executable statements organized as linked lists:

**Print**

```gpl
print("Score=" + score);
```

Output format:

```
print[17]: Score=42
```

**Assignment**

```gpl
x = 10;
y += 3;
count++;
value--;
```

Assignments modify variables and object attributes using an internal lvalue system (Locator hierarchy).

**Conditional Execution**

```gpl
if(score > 10)
{
    print("High score!");
}
else
{
    print("Keep trying.");
}
```

**Loops**

```gpl
for(i = 0; i < 5; i += 1)
{
    print(i);
}
```

The loop supports optional initializer and incrementor components.

**Exit**

```gpl
exit(0);
```

Terminates program execution with a status code.

---

**Event-Driven Execution**

GPL supports event handler blocks triggered by keypresses:

```gpl
on space
{
    print("Space pressed!");
}

on leftarrow
{
    player.x -= 5;
}
```

Multiple handlers may be registered per key. An internal `Event_manager` dispatches handlers when keystrokes occur.

For automated testing, input can be piped via:

```bash
cat tests/t007.keypresses | ./gpl -stdin program.gpl
```

---

### Internal Architecture

The system consists of:

**Scanner (Flex)**

* Converts source text into tokens
* Tracks line numbers
* Allocates semantic values safely

**Parser (Bison)**

* Builds AST nodes
* Enforces operator precedence
* Resolves shift/reduce conflicts
* Performs semantic validation

**Expression Hierarchy**

* `Expression` base class
* Derived operator and constant classes
* `type()` and `evaluate()` model

**Statement Hierarchy**

* `Statement` base class
* Linked-list execution model
* Each derived class implements `execute()`

**Symbol System**

* `Symbol`
* `Symbol_table`
* `Scope_manager`

**Object System**

* `Game_object` base class
* Attribute type checking
* Safe attribute mutation

**Lvalue System**

* `Locator` hierarchy
* Enables safe mutation of:

  * Variables
  * Array elements
  * Object attributes

---

**Error Handling**

The interpreter performs:

* Syntax error detection
* Type mismatch reporting
* Undeclared variable detection
* Redeclaration detection
* Invalid attribute access detection
* Array bounds checking
* Divide-by-zero detection at parse time

Error messages are consistent with the GPL specification.

---

**Memory Safety**

All dynamic memory is carefully managed:

* `%destructor` directives in Bison
* `std::unique_ptr` where ownership applies
* Explicit deletion where required
* Fully Valgrind-clean across all test suites

---

**Build & Run**

Build:

```bash
make
```

Run:

```bash
./gpl program.gpl
```

Run with simulated keystrokes:

```bash
cat tests/t007.keypresses | ./gpl -stdin program.gpl
```

Run test suite:

```bash
../../bin/gt
```

Check memory:

```bash
../../bin/memvalidate.bash
```

---

**Example GPL Program**

```gpl
rectangle r(x=50, y=50, w=200, h=100);

int i = 0;

on space {
    print("Moving rectangle");
    r.x += 10;
}

for(i = 0; i < 5; i += 1) {
    r.y += 5;
}

if(r.x > 100) {
    print("Rectangle moved!");
}
```

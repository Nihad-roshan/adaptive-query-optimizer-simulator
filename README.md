# Adaptive Query Optimizer Simulator

A modular C project that simulates how a database query optimizer works. It builds an AST, estimates join costs, selects the best join algorithm, executes it, and generates a query execution plan tree.

---

##  Project Architecture

```
project/
│
├── ast.c / ast.h                → AST creation & traversal
├── cost_estimation.c / cost.h   → Cost model (nested loop / hash join)
├── join.c / join.h              → Join algorithm implementations
├── plan.c / plan.h              → Plan tree construction & visualization
├── optimizer.c / optimizer.h    → Join selection logic
└── main.c                       → Entry point, test query & tables
```

---

##  Workflow

```
SQL Query
   ↓
AST Construction
   ↓
Cost Estimation
   ↓
Join Algorithm Selection
   ↓
Join Execution
   ↓
Query Plan Tree Construction
   ↓
Plan Visualization
```

---

##  Module Summary

### **AST Module**

* Creates nodes for SELECT, JOIN, WHERE, TABLE
* Preorder traversal mirrors SQL query structure

### **Cost Estimation Module**

* Nested Loop Cost → rowsA * rowsB
* Hash Join Cost → rowsA + rowsB
* Simple heuristic to choose cheaper join

### **Join Module**

* Implements:

  * Nested Loop Join
  * Hash Join (build + probe)

### **Plan Module**

* Creates execution plan nodes:

  * TABLE SCAN
  * HASH JOIN / NESTED LOOP JOIN
  * FILTER
  * PROJECT
* Prints readable plan tree:

```
PROJECT
 FILTER
  HASH JOIN
   SEQ SCAN
   SEQ SCAN
```

### **Optimizer Module**

* Computes costs
* Selects the join algorithm
* Executes join
* Builds the plan tree

---

##  Example Query Used

```
SELECT students.name, results.grade
FROM students
JOIN results ON students.rollnumber = results.rollnumber
WHERE students.age > 18;
```
## output
<img width="1319" height="863" alt="output" src="https://github.com/user-attachments/assets/64f6c572-da72-47b1-8969-c8b8eea0deca" />

---

##  Summary

This project demonstrates the core ideas of a **cost-based query optimizer**:

* AST representation
* Cost-based decision making
* Join algorithm simulation
* Plan generation & visualization

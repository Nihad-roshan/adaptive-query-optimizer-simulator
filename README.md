# Adaptive Query Optimizer Simulator

A modular C project that simulates how a database query optimizer works. It builds an AST, estimates join costs, selects the best join algorithm, executes it, and generates a query execution plan tree.

---

##  Project Architecture

```
project/
│
├── ast.c / ast.h                → AST creation & traversal
├── cost_estimation.c / cost_estimation.h   → Cost model (nested loop / hash join)
├── optimizer.c / optimizer.h    → Join logic + selection logic + execution
├── plan.c / plan.h              → Plan tree construction & visualization
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

### **Optimizer Module**

* Computes costs
* Selects the join algorithm
* Executes join
* Builds the plan tree

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

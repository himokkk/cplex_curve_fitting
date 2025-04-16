# 📈 Curve Fitting with CPLEX

This project demonstrates how to perform **curve fitting** using IBM CPLEX in C++, solving four optimization problems based on minimizing deviations from a data set.

---

## 📊 Problem Statement

Given a set of (x, y) data points (from Table 12.4 in "Model Building in Mathematical Programming"), the goal is to fit:

1. A **linear function** `y = bx + a` minimizing the **sum of absolute deviations**.
2. A **linear function** `y = bx + a` minimizing the **maximum absolute deviation**.
3. A **quadratic function** `y = cx² + bx + a` minimizing the **sum of absolute deviations**.
4. A **quadratic function** `y = cx² + bx + a` minimizing the **maximum absolute deviation**.

All models are formulated and solved using the IBM ILOG CPLEX Optimization Studio and Concert Technology API in C++.

---

## 🧠 How It Works

The program:

- Defines the dataset (`x_data`, `y_data`)
- Sets up each optimization model using `IloModel`
- Uses `IloNumVar` to define variables and constraints
- Uses `IloObjective` with either `IloMinimize(sum)` or `IloMinimize(max_deviation)`
- Solves the models using `IloCplex` and prints the results

Each model is cleaned up before moving to the next one to reuse the same `IloModel` instance efficiently.

---

## 🛠️ Requirements

- **IBM ILOG CPLEX Optimization Studio** (with C++ API installed)
- A C++17-compatible compiler (e.g. `g++`)
- CPLEX environment properly set up (`ILOG_CPLEX_PATH`, includes, and libs linked)

---

## 📦 Build Instructions

```bash
g++ -std=c++17 -I/path/to/cplex/include -L/path/to/cplex/lib/x86-64_linux -o curve_fitting main.cpp -lilocplex -lcplex -lconcert -lm -lpthread
```

## 🧪Results

![image](https://github.com/user-attachments/assets/934a0271-30f0-480e-b086-eef5300e9d76)


#include <iostream>
#include <vector>
#include <cmath>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() {
    // Data points from Table 12.4
    vector<double> x_data = { 0.0, 0.5, 1.0, 1.5, 1.9, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.6, 7.0, 7.6, 8.5, 9.0, 10.0 };
    vector<double> y_data = { 1.0, 0.9, 0.7, 1.5, 2.0, 2.4, 3.2, 2.0, 2.7, 3.5, 1.0, 4.0, 3.6, 2.7, 5.7, 4.6, 6.0, 6.8, 7.3 };
    int n = x_data.size();

    try {
        IloEnv env;
        IloModel model(env);

        // 1. Fit the 'best' straight line y = bx + a to minimise the sum of absolute deviations
        IloNumVar a1(env, -IloInfinity, IloInfinity, "a1");
        IloNumVar b1(env, -IloInfinity, IloInfinity, "b1");
        IloExpr abs_dev_sum(env);
        IloNumVarArray d_plus1(env, n);
        IloNumVarArray d_minus1(env, n);
        IloConstraintArray constraints1(env);

        for (int i = 0; i < n; ++i) {
            d_plus1[i] = IloNumVar(env, 0, IloInfinity);
            d_minus1[i] = IloNumVar(env, 0, IloInfinity);
            IloConstraint constraint = (b1 * x_data[i] + a1 - y_data[i] == d_plus1[i] - d_minus1[i]);
            constraints1.add(constraint);
            model.add(constraint);
            abs_dev_sum += d_plus1[i] + d_minus1[i];
        }
        IloObjective obj1 = IloMinimize(env, abs_dev_sum);
        model.add(obj1);

        IloCplex cplex1(model);
        if (cplex1.solve()) {
            cout << "---------------------------------------------------------" << endl;
            cout << "1. Best straight line (minimise sum of absolute deviations):" << endl;
            cout << "   a = " << cplex1.getValue(a1) << endl;
            cout << "   b = " << cplex1.getValue(b1) << endl;
            cout << "   Objective value (sum of absolute deviations) = " << cplex1.getObjValue() << endl;
        }
        else {
            cerr << "Solution not found for problem 1" << endl;
        }
        cplex1.end();
        model.remove(obj1);
        for (int i = 0; i < constraints1.getSize(); ++i) {
            model.remove(constraints1[i]);
        }
        d_plus1.end();
        d_minus1.end();
        abs_dev_sum.end();
        constraints1.end();

        // 2. Fit the 'best' straight line y = bx + a to minimise the maximum deviation
        IloNumVar a2(env, -IloInfinity, IloInfinity, "a2");
        IloNumVar b2(env, -IloInfinity, IloInfinity, "b2");
        IloNumVar delta2(env, 0, IloInfinity, "delta2");
        IloConstraintArray constraints2(env);

        for (int i = 0; i < n; ++i) {
            IloConstraint constraint1 = (b2 * x_data[i] + a2 - y_data[i] <= delta2);
            IloConstraint constraint2 = (y_data[i] - (b2 * x_data[i] + a2) <= delta2);
            constraints2.add(constraint1);
            constraints2.add(constraint2);
            model.add(constraint1);
            model.add(constraint2);
        }
        IloObjective obj2 = IloMinimize(env, delta2);
        model.add(obj2);

        IloCplex cplex2(model);
        if (cplex2.solve()) {
            cout << "---------------------------------------------------------" << endl;
            cout << "2. Best straight line (minimise maximum deviation):" << endl;
            cout << "   a = " << cplex2.getValue(a2) << endl;
            cout << "   b = " << cplex2.getValue(b2) << endl;
            cout << "   Objective value (maximum deviation) = " << cplex2.getObjValue() << endl;
        }
        else {
            cerr << "Solution not found for problem 2" << endl;
        }
        cplex2.end();
        model.remove(obj2);
        for (int i = 0; i < constraints2.getSize(); ++i) {
            model.remove(constraints2[i]);
        }
        constraints2.end();

        // 3. Fit the 'best' quadratic curve y = cx^2 + bx + a to minimise the sum of absolute deviations
        IloNumVar a3(env, -IloInfinity, IloInfinity, "a3");
        IloNumVar b3(env, -IloInfinity, IloInfinity, "b3");
        IloNumVar c3(env, -IloInfinity, IloInfinity, "c3");
        IloExpr abs_dev_sum_quad(env);
        IloNumVarArray d_plus3(env, n);
        IloNumVarArray d_minus3(env, n);
        IloConstraintArray constraints3(env);

        for (int i = 0; i < n; ++i) {
            d_plus3[i] = IloNumVar(env, 0, IloInfinity);
            d_minus3[i] = IloNumVar(env, 0, IloInfinity);
            IloConstraint constraint = (c3 * pow(x_data[i], 2) + b3 * x_data[i] + a3 - y_data[i] == d_plus3[i] - d_minus3[i]);
            constraints3.add(constraint);
            model.add(constraint);
            abs_dev_sum_quad += d_plus3[i] + d_minus3[i];
        }
        IloObjective obj3 = IloMinimize(env, abs_dev_sum_quad);
        model.add(obj3);

        IloCplex cplex3(model);
        if (cplex3.solve()) {
            cout << "---------------------------------------------------------" << endl;
            cout << "3. Best quadratic curve (minimise sum of absolute deviations):" << endl;
            cout << "   a = " << cplex3.getValue(a3) << endl;
            cout << "   b = " << cplex3.getValue(b3) << endl;
            cout << "   c = " << cplex3.getValue(c3) << endl;
            cout << "   Objective value (sum of absolute deviations) = " << cplex3.getObjValue() << endl;
        }
        else {
            cerr << "Solution not found for problem 3" << endl;
        }
        cplex3.end();
        model.remove(obj3);
        for (int i = 0; i < constraints3.getSize(); ++i) {
            model.remove(constraints3[i]);
        }
        d_plus3.end();
        d_minus3.end();
        abs_dev_sum_quad.end();
        constraints3.end();

        // 4. Fit the 'best' quadratic curve y = cx^2 + bx + a to minimise the maximum deviation
        IloNumVar a4(env, -IloInfinity, IloInfinity, "a4");
        IloNumVar b4(env, -IloInfinity, IloInfinity, "b4");
        IloNumVar c4(env, -IloInfinity, IloInfinity, "c4");
        IloNumVar delta4(env, 0, IloInfinity, "delta4");
        IloConstraintArray constraints4(env);

        for (int i = 0; i < n; ++i) {
            IloConstraint constraint1 = (c4 * pow(x_data[i], 2) + b4 * x_data[i] + a4 - y_data[i] <= delta4);
            IloConstraint constraint2 = (y_data[i] - (c4 * pow(x_data[i], 2) + b4 * x_data[i] + a4) <= delta4);
            constraints4.add(constraint1);
            constraints4.add(constraint2);
            model.add(constraint1);
            model.add(constraint2);
        }
        IloObjective obj4 = IloMinimize(env, delta4);
        model.add(obj4);

        IloCplex cplex4(model);
        if (cplex4.solve()) {
            cout << "---------------------------------------------------------" << endl;
            cout << "4. Best quadratic curve (minimise maximum deviation):" << endl;
            cout << "   a = " << cplex4.getValue(a4) << endl;
            cout << "   b = " << cplex4.getValue(b4) << endl;
            cout << "   c = " << cplex4.getValue(c4) << endl;
            cout << "   Objective value (maximum deviation) = " << cplex4.getObjValue() << endl;
        }
        else {
            cerr << "Solution not found for problem 4" << endl;
        }
        cplex4.end();
        model.remove(obj4);
        for (int i = 0; i < constraints4.getSize(); ++i) {
            model.remove(constraints4[i]);
        }
        constraints4.end();

        env.end();
    }
    catch (IloException& e) {
        cerr << "Concert exception caught: " << e << endl;
    }
    catch (...) {
        cerr << "Unknown exception caught" << endl;
    }

    return 0;
}
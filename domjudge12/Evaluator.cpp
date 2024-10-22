#include "Evaluator.h"

// NOTE: IMPLEMENT & ADD CONST AS NEEDED

Evaluator::Evaluator() {   
}

// adds a student to system
void Evaluator::add_s(sid_t id) {
    if(studentsGrades.contains(id))
        throw EDuplicate();
    else {
        studentsGrades[id];
        //averages[0][id] = 0;
    }
}

// adds an exercise to system
void Evaluator::add_e(eid_t id, bool mandatory) {
    if (exercises.contains(id))
        throw EDuplicate();
    else {
        exercises[id] = mandatory;
    }
}

// grades student's exercise
void Evaluator::grade(sid_t s, grade_t g, eid_t e) {
    if(!studentsGrades.contains(s) || !exercises.contains(e))
        throw EBadArgs();
    else {
        gradeExercise p = studentsGrades[s];
        if (p.poop.contains(e)) {
            p.sum -= p.poop[e];
            p.sum += g;
        }
        else {
            p.sum += g;
            if (exercises[e])
                p.obligatorias++;
        }
        p.poop[e] = g;      
        studentsGrades[s] = p;
    }
}

// returns average grade for a student
grade_t Evaluator::average(sid_t id) {//constante
    gradeExercise p = studentsGrades[id];
    int average;
    if (p.sum == 0 || p.obligatorias == 0)
        average = 0;
    else
        average = p.sum / p.obligatorias;
    averages[average][id]= 0;
    return average;
}

// returns n best students by average grade
List<sid_t> Evaluator::top(int n)  {
    List<sid_t> result;
    List<sid_t> aux;
    for (auto co = studentsGrades.cbegin(); co != studentsGrades.cend(); co++)
        average(co.key());
    for (auto it = averages.cbegin(); it != averages.cend(); it++) {
        if (it.value().size() > 1) {
            for (auto ti = it.value().cbegin(); ti != it.value().cend(); ti++) {
                aux.push_front(ti.key());
            }
            while (!aux.empty()) {
                result.push_front(aux.cbegin()._elem());
                aux.pop_front();
            }
            while(result.size() > n)
                result.pop_back();
        }

        else {
            result.push_front(it.value().cbegin().key());
            if (result.size() > n)
                result.pop_back();
        }
    }
    return result;
}


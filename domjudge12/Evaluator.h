#include <string>
#include "List.h"
#include"HashMap.h"
#include"TreeMap.h"

// ADD MORE INCLUDES IF REQUIRED

class EDuplicate{};
class EBadArgs{};

typedef std::string sid_t;  // student id
typedef std::string eid_t;  // exercise id
typedef int grade_t;        // grade



class Evaluator {
    struct gradeExercise {
        HashMap<eid_t, grade_t> poop;
        int sum = 0;
        int obligatorias = 0;
    };
    // PRIVATE IMPLEMENTATION HERE
    HashMap<eid_t, bool> exercises;
    HashMap < sid_t, gradeExercise> studentsGrades;
    TreeMap<int, TreeMap<sid_t, bool>> averages;

public:

    // NOTE: ADD CONST AS NEEDED

    // constructor
    Evaluator();

    // adds a student to system
    void add_s(sid_t id);

    // adds an exercise to system
    void add_e(eid_t id, bool mandatory);

    // grades student's exercise
    void grade(sid_t s, grade_t g, eid_t e);

    // returns average grade for a student
    grade_t average(sid_t id);

    // returns n best students by average grade
    List<sid_t> top(int n);
};

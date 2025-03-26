#pragma once

struct Subject {
    char code[30];
    char name[100];
    char lecturer[100];
    char group[30];
    int number_of_students;
    double lectures_time;
    double practice_time;
    bool course_work_flag;
    bool exam_flag;
};

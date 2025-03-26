#pragma once
#include "subject.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <iomanip>

// no exam = 0,35
// exam = 0,5
// seacrh by lecturer's last name
// search by group
// course work
// type of finals
// add, delete and change subject
// (delete and change – write into different file)
// first input
// output into .txt in a vedomost' view (?) with common total count (?)

class SubjectManager {
private:
    std::map<int, Subject> subjects;
    std::string in_bin;
    std::string out_txt;
    int subjects_count;


    static void input(Subject& p_subject);
    static void printSubject(const std::pair<const int, Subject>& p_subject);
    void insertSubjectIntoOutput(const std::map<int, Subject>& p_subjects, const std::string& p_filename);
    void loadData();
    void updateAllData();


public:

    SubjectManager(const std::string& p_binFileName, const std::string& p_textOutputFileName);

    void addSubject();
    void printData() const noexcept;
    void loadDataIntoTxt() const;

    void findByLecturer(const std::string &p_lecturer) noexcept;
    void findByGroup(std::string p_subject) noexcept;
    void findByCourseWork(const bool p_flag) noexcept;
    void findByExam(const bool p_flag) noexcept;

    void deleteRecord(int p_index);
    void updateRecord(int p_index);
    void replaceRecord(int p_index);
};

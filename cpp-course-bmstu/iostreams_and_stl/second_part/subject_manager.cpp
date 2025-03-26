#include "subject_manager.h"


//!!! Заданеи на защиту.
//!!! Добавить метод, производящий замену записи в бинарном файле по месту
//!!! (без полной загрузки и перезаписи всего файла).


SubjectManager::SubjectManager(const std::string& p_in_bin, const std::string& p_out_txt)
                                : in_bin(p_in_bin), out_txt(p_out_txt), subjects_count(0) {
    loadData();
}

void SubjectManager::loadData() {
    std::ifstream f_in(in_bin, std::ios::binary | std::ios::in);
    if (!f_in.is_open()) {
        throw std::runtime_error("can't open file.");
    }
    else {
        Subject subject;
        while (f_in.read(reinterpret_cast<char*>(&subject), sizeof(Subject))) {
            subjects_count++;
            subjects.insert(std::make_pair(subjects_count, subject));
        }
    }
}

void SubjectManager::addSubject() {
    std::ofstream f_in{in_bin, std::ios::binary | std::ios::app};

    if (!f_in.is_open()) {
        throw std::runtime_error("couldn't open input file!");
    } else {
        std::cout << "adding new subject..." << std::endl;
        Subject subject;
        input(subject);
        subjects_count++;
        subjects.insert(std::move(std::make_pair(subjects_count, subject)));
        f_in.write(reinterpret_cast<char*>(&subject), sizeof(Subject));
    }
}

void SubjectManager::printData() const noexcept {
    std::cout << "SUBJECTS:" << std::endl;
    for (const auto &el : subjects)
        printSubject(el);
}

void SubjectManager::printSubject(const std::pair<const int, Subject> &p_subject) {
    std::cout << "index: " << p_subject.first << '\n';
    std::cout << "code of the subject: " << p_subject.second.code << '\n';
    std::cout << "name of the subject: " << p_subject.second.name << '\n';
    std::cout << "lecturer's name: " << p_subject.second.lecturer << '\n';
    std::cout << "group: " << p_subject.second.group << '\n';
    std::cout << "number of students in the group: " << p_subject.second.number_of_students << '\n';
    std::cout << "lectures time: " << p_subject.second.lectures_time << " hours " << '\n';
    std::cout << "practice time: " << p_subject.second.practice_time << " hours " << '\n';
    std::cout << "course work: " << (p_subject.second.course_work_flag ? "yes" : "no") << '\n';
    std::cout << "exam or credit: " << (p_subject.second.exam_flag ? "exam" : "credit") << '\n' << '\n';
}

void SubjectManager::loadDataIntoTxt() const {
    std::ofstream f_out(out_txt);

    f_out << "|" << std::setw(8) << "index "
          << "|" << std::setw(20) << "code of the subject "
          << "|" << std::setw(20) << "name of the subject "
          << "|" << std::setw(16) << "lecturer's name "
          << "|" << std::setw(10) << "group "
          << "|" << std::setw(20) << "number of students "
          << "|" << std::setw(15) << "lectures time "
          << "|" << std::setw(15) << "practice time "
          << "|" << std::setw(12) << "course work "
          << "|" << std::setw(14) << "exam or credit " <<"|"
          << std::endl;

    double time = 0;
    std::string cw, exam;
    for (const auto& subject : subjects) {
        cw = (subject.second.course_work_flag ? "yes" : "no");
        exam = (subject.second.exam_flag  ? "yes" : "no");


        f_out << "|" << std::setw(8) << subject.first << "|"
              << std::setw(20) << subject.second.code << "|"
              << std::setw(20) << subject.second.name << "|"
              << std::setw(16) << subject.second.lecturer << "|"
              << std::setw(10) << subject.second.group << "|"
              << std::setw(20) << subject.second.number_of_students << "|"
              << std::setw(15) << subject.second.lectures_time << "|"
              << std::setw(15) << subject.second.practice_time << "|"
              << std::setw(12) << cw << "|"
              << std::setw(14) << exam << "|"
              << std::endl;

        time += subject.second.number_of_students * (subject.second.lectures_time + subject.second.practice_time
                + subject.second.exam_flag * 0.5 + !subject.second.exam_flag  * 0.35);
    }
    for (int i = 0; i < 161; ++i)
        f_out << "-";
    f_out << "\nsubjects in database: " << subjects_count << "\ntotal time: " << time;
    std::cout << std::endl << "the result is in \'out.txt\'. " << std::endl << std::endl;
}

// seacrh by lecturer's last name
// search by group
// course work
// type of finals

void SubjectManager::findByLecturer(const std::string &p_lecturer) noexcept {
    std::map<int, Subject> result;
    std::map<int, Subject>::iterator cur = subjects.begin();

    while (cur != subjects.end()) {
        cur = std::find_if(cur, subjects.end(),[p_lecturer](const std::pair<const int, Subject>& p_subject) {
            return p_subject.second.lecturer == p_lecturer;
        });
        if (cur != subjects.end()) {
            result.insert(*cur);
            cur++;
        }
    }

    if (result.empty())
        std::cout << std::endl << "subjects are not found" << std::endl;
    else {
        std::cout << std::endl << "the result is in \'search_by_lecturer.txt\'. " << std::endl << std::endl;
        insertSubjectIntoOutput(result, "../second_part_out/search_by_lecturer.txt");
    }
}


void SubjectManager::findByGroup(std::string p_group) noexcept {
    std::map<int, Subject> result;
    std::map<int, Subject>::iterator cur = subjects.begin();

    while (cur != subjects.end()) {
        cur = std::find_if(cur, subjects.end(), [p_group](std::pair<const int, Subject>& p_subject) {
            return p_subject.second.group == p_group;
        });
        if (cur != subjects.end()) {
            result.insert(*cur);
            cur++;
        }
    }

    if (result.empty()) std::cout << std::endl << "no such subjects!" << std::endl;
    else {
        std::cout << std::endl << "the result is in \'search_by_group.txt\'. " << std::endl << std::endl;
        insertSubjectIntoOutput(result, "../second_part_out/search_by_group.txt");
    }
}


void SubjectManager::findByCourseWork(const bool p_flag) noexcept {
    std::map<int, Subject> result;
    std::map<int, Subject>::iterator cur = subjects.begin();

    while (cur != subjects.end()) {
        cur = std::find_if(cur, subjects.end(), [p_flag](const std::pair<const int, Subject>& subject) {
            return p_flag == subject.second.course_work_flag;
        });
        if (cur != subjects.end()) {
            result.insert(*cur);
            cur++;
        }
    }

    if (result.empty()) std::cout << std::endl << "no such subjects!" << std::endl;
    else {
        std::cout << std::endl << "the result is in \'search_by_coursework.txt\'. " << std::endl << std::endl;
        insertSubjectIntoOutput(result, "../second_part_out/search_by_coursework.txt");
    }
}

void SubjectManager::findByExam(const bool p_flag) noexcept {
    std::map<int, Subject> result;
    std::map<int, Subject>::iterator cur = subjects.begin();

    while (cur != subjects.end()) {
        cur = std::find_if(cur, subjects.end(), [p_flag](const std::pair<const int, Subject>& subject) {
            return p_flag == subject.second.exam_flag;
        });
        if (cur != subjects.end()) {
            result.insert(*cur);
            cur++;
        }
    }

    if (result.empty()) std::cout << std::endl << "no such subjects!" << std::endl;
    else {
        std::cout << std::endl << "The result is in \'search_by_exam.txt\'. " << std::endl << std::endl;
        insertSubjectIntoOutput(result, "../second_part_out/search_by_exam.txt");
    }
}

void SubjectManager::deleteRecord(int p_index) {
    if (p_index <= 0 || p_index > subjects_count) {
        throw std::out_of_range("no such index");
    }

    subjects.erase(p_index);
    subjects_count--;

    for (int i = p_index + 1; i <= subjects_count + 1; i++) {
        auto subject = subjects.at(i);
        subjects.erase(i);
        subjects.emplace(std::move(std::make_pair(i - 1, subject)));
    }

    updateAllData();
}

void SubjectManager::input(Subject &p_subject) {
    std::cout << "input code of the subject: " << '\n';
    std::cin >> p_subject.code ;
    std::cout << "input name of the subject: " << '\n';
    std::cin >> p_subject.name;
   // gets(p_subject.lecturer);
    std::cout << "input lecturer's name: " << '\n';
    std::cin >> p_subject.lecturer;
    //gets(p_subject.lecturer);
    std::cout << "input group: " << '\n';
    //gets(p_subject.group);
    std::cin >> p_subject.group;
   // std::getline(std::cin, p_subject.group);
    std::cout << "input number of students in the group: " << '\n';
    std::cin >> p_subject.number_of_students;
    std::cout << "input lectures time: " << '\n';
    std::cin >> p_subject.lectures_time;
    std::cout << "input practice time: "  << '\n';
    std::cin >> p_subject.practice_time;
    std::cout << "input 1 if there is a course work, 0 otherwise: " << '\n';
    std::cin >> p_subject.course_work_flag;
    std::cout << "input 1 if there is an exam, 0 if only credit: " << '\n';
    std::cin >> p_subject.exam_flag;
}

void SubjectManager::updateRecord(int p_index) {
    auto updateIter = std::find_if(subjects.begin(), subjects.end(), [&p_index](const auto &subject) {
        return subject.first == p_index;
    });

    input(updateIter->second);
    updateAllData();
}

void SubjectManager::updateAllData() {
    std::ofstream f_in(in_bin, std::ios::binary | std::ios::out);

    if (!f_in.is_open()) {
        throw std::runtime_error("can't open file!");
    }

    for (auto& bill : subjects) {
        f_in.write(reinterpret_cast<char*>(&bill.second), sizeof(Subject));
    }
}

void SubjectManager::insertSubjectIntoOutput(const std::map<int, Subject>& p_subjects, const std::string &p_filename) {
    std::ofstream f_out{p_filename};

    if (!f_out.is_open()) {
        throw std::runtime_error("can't open file!");
    }

    f_out << "|" << std::setw(8) << "index "
          << "|" << std::setw(20) << "code of the subject "
          << "|" << std::setw(20) << "name of the subject "
          << "|" << std::setw(16) << "lecturer's name "
          << "|" << std::setw(10) << "group "
          << "|" << std::setw(20) << "number of students "
          << "|" << std::setw(15) << "lectures time "
          << "|" << std::setw(15) << "practice time "
          << "|" << std::setw(12) << "course work "
          << "|" << std::setw(14) << "exam or credit " <<"|"
          << std::endl;

    std::string cw, exam;
    for (const auto& subject : subjects) {
        cw = (subject.second.course_work_flag ? "yes" : "no");
        exam = (subject.second.exam_flag ? "yes" : "no");


        f_out << "|" << std::setw(8) << subject.first << "|"
              << std::setw(20) << subject.second.code << "|"
              << std::setw(20) << subject.second.name << "|"
              << std::setw(16) << subject.second.lecturer << "|"
              << std::setw(10) << subject.second.group << "|"
              << std::setw(20) << subject.second.number_of_students << "|"
              << std::setw(15) << subject.second.lectures_time << "|"
              << std::setw(15) << subject.second.practice_time << "|"
              << std::setw(12) << cw << "|"
              << std::setw(14) << exam << "|"
              << std::endl;
    }
}

void SubjectManager::replaceRecord(int p_index) {
    Subject subject;

    p_index += 1;
    input(subject);
    std::ofstream file(in_bin, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        std::cout << "can't open the file!" << std::endl;
    }
    file.seekp(p_index * sizeof(Subject));
    file.write(reinterpret_cast<char*> (&subject), sizeof(subject));
}

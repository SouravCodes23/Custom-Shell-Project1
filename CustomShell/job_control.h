#ifndef JOB_CONTROL_H
#define JOB_CONTROL_H

#include <vector>
#include <string>
#include <sys/types.h>

struct Job {
    int job_id;
    pid_t pid;
    std::string command;
    bool is_background;
};

class JobControl {
public:
    static void add_job(pid_t pid, const std::string& command, bool background);
    static void list_jobs();
    static void bring_to_foreground(int job_id);
    static void bring_to_background(int job_id);
private:
    static std::vector<Job> jobs;
    static int next_job_id;
};

#endif

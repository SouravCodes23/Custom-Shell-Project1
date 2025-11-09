#include "job_control.h"
#include <iostream>
#include <process.h>
#include <windows.h>

std::vector<Job> JobControl::jobs;
int JobControl::next_job_id = 1;

void JobControl::add_job(pid_t pid, const std::string& command, bool background) {
    Job job = {next_job_id++, pid, command, background};
    jobs.push_back(job);
    if (background) {
        std::cout << "[" << job.job_id << "] " << job.pid << " " << job.command << " &" << std::endl;
    }
}

void JobControl::list_jobs() {
    for (const auto& job : jobs) {
        std::cout << "[" << job.job_id << "] " << (job.is_background ? "Running" : "Stopped") << " " << job.command << std::endl;
    }
}

void JobControl::bring_to_foreground(int job_id) {
    for (auto& job : jobs) {
        if (job.job_id == job_id) {
            job.is_background = false;
            // In a full implementation, handle signals to bring to fg
            std::cout << job.command << " brought to foreground" << std::endl;
            break;
        }
    }
}

void JobControl::bring_to_background(int job_id) {
    for (auto& job : jobs) {
        if (job.job_id == job_id) {
            job.is_background = true;
            // In a full implementation, handle signals to send to bg
            std::cout << job.command << " sent to background" << std::endl;
            break;
        }
    }
}

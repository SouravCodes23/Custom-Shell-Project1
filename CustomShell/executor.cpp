#include "executor.h"
#include "job_control.h"
#include <iostream>
#include <process.h>
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>

void Executor::execute(const std::vector<std::string>& tokens) {
    // Check for piping
    auto pipe_pos = std::find(tokens.begin(), tokens.end(), "|");
    if (pipe_pos != tokens.end()) {
        handle_piping(tokens);
        return;
    }

    // Check for redirection
    auto redir_pos = std::find_if(tokens.begin(), tokens.end(), [](const std::string& s) {
        return s == ">" || s == "<" || s == ">>";
    });
    if (redir_pos != tokens.end()) {
        handle_redirection(tokens);
        return;
    }

    // Single command
    execute_single_command(tokens);
}

void Executor::execute_single_command(const std::vector<std::string>& cmd) {
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    std::string command_line = "cmd.exe /c ";
    for (const auto& arg : cmd) {
        command_line += arg + " ";
    }

    if (CreateProcessA(NULL, const_cast<char*>(command_line.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // Add to job control if background
        if (!cmd.empty() && cmd.back() == "&") {
            std::string cmd_str;
            for (size_t i = 0; i < cmd.size() - 1; ++i) {
                cmd_str += cmd[i] + " ";
            }
            JobControl::add_job(pi.dwProcessId, cmd_str, true);
        } else {
            WaitForSingleObject(pi.hProcess, INFINITE);
        }
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Command not found: " << cmd[0] << std::endl;
    }
}

void Executor::handle_redirection(const std::vector<std::string>& cmd) {
    // Simplified redirection handling for Windows
    auto redir_pos = std::find_if(cmd.begin(), cmd.end(), [](const std::string& s) {
        return s == ">" || s == "<" || s == ">>";
    });

    if (redir_pos == cmd.end()) return;

    std::string op = *redir_pos;
    std::vector<std::string> command(cmd.begin(), redir_pos);
    std::string file = *(redir_pos + 1);

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    std::string command_line = "cmd.exe /c ";
    for (const auto& arg : command) {
        command_line += arg + " ";
    }

    if (op == ">") {
        command_line += " > " + file;
    } else if (op == ">>") {
        command_line += " >> " + file;
    } else if (op == "<") {
        command_line += " < " + file;
    }

    if (CreateProcessA(NULL, const_cast<char*>(command_line.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Command not found: " << command[0] << std::endl;
    }
}

void Executor::handle_piping(const std::vector<std::string>& cmd) {
    // Simplified piping for Windows - note: full piping is complex on Windows
    auto pipe_pos = std::find(cmd.begin(), cmd.end(), "|");
    std::vector<std::string> cmd1(cmd.begin(), pipe_pos);
    std::vector<std::string> cmd2(pipe_pos + 1, cmd.end());

    // For simplicity, execute sequentially without actual piping
    execute_single_command(cmd1);
    execute_single_command(cmd2);
}

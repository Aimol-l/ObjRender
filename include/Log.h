#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <filesystem>

namespace ren{

class Log {
public:
    ~Log(){spdlog::shutdown();}
    // 静态方法来记录不同级别的日志
    static void trace(const std::string& message) {instance().logger_->trace(message);}
    static void debug(const std::string& message) {instance().logger_->debug(message);}
    static void info(const std::string& message) {instance().logger_->info(message);}
    static void warn(const std::string& message) {instance().logger_->warn(message);}
    static void error(const std::string& message) {instance().logger_->error(message);}
    static void critical(const std::string& message) {instance().logger_->critical(message);}
private:
    // 私有构造函数，确保不能创建实例
    Log(){
        // 设置日志级别
        spdlog::set_level(spdlog::level::debug);
        // 尝试创建文件日志器
        try {
            if (std::filesystem::exists("logs/app.log"))  std::filesystem::remove("logs/app.log");
            logger_ = spdlog::basic_logger_mt("opengl_logger", "logs/app.log");
            spdlog::set_default_logger(logger_);
        } catch (const spdlog::spdlog_ex& ex) {
            // 如果文件日志器创建失败，使用控制台日志器
            logger_ = spdlog::stdout_color_mt("console");
            logger_->error("Log initialization failed: {}", ex.what());
        }
    }
    // 静态局部变量，用于存储日志器实例
    static Log& instance() {
        static Log instance;
        return instance;
    }
    // 日志器指针
    std::shared_ptr<spdlog::logger> logger_;
};
}
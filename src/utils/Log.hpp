#pragma once

#include <spdlog/spdlog.h>

#include <cstdlib>
#include <memory>

#define LOG_TRACE(...)    ::Log::Instance().Trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::Log::Instance().Debug(__VA_ARGS__)
#define LOG_INFO(...)     ::Log::Instance().Info(__VA_ARGS__)
#define LOG_WARN(...)     ::Log::Instance().Warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Log::Instance().Error(__VA_ARGS__)
#define LOG_CRITICAL(...) \
    do { ::Log::Instance().Flush(); \
         ::Log::Instance().Critical(__VA_ARGS__); \
         std::abort(); } while(0)

enum class LogLevel {
    Trace    = 0,
    Debug    = 1,
    Info     = 2,
    Warn     = 3,
    Error    = 4,
    Critical = 5,
};

/**
 * @brief 全局异步日志系统（基于 spdlog）
 *
 * 单例模式，提供 6 级日志宏：TRACE / DEBUG / INFO / WARN / ERROR / CRITICAL。
 * 使用前需调用 Init() 初始化，程序退出前建议调用 Shutdown() 释放资源。
 *
 * @example
 *   Log::Init();
 *   LOG_INFO("Starting render at {}x{}", width, height);
 */
class Log {
public:
    /** @brief 获取 Log 单例实例 */
    static Log& Instance();

    /**
     * @brief 初始化异步日志系统
     *
     * 创建异步 logger，配置控制台彩色输出、日志格式、日志级别。
     * 多次调用安全（已初始化时直接返回）。
     */
    void Init();

    /** @brief 关闭日志系统，刷新并释放所有资源 */
    void Shutdown();

    /** @brief 刷新日志缓冲区，将所有待写入的日志立即输出 */
    void Flush();

    /**
     * @brief 设置最低输出级别
     * @param level 低于此级别的日志将被忽略
     */
    void SetLevel(LogLevel level);

    /** @brief 输出 TRACE 级别日志 */
    template<typename... Args>
    void Trace(fmt::format_string<Args...> fmt, Args&&... args) {
        if (m_pLogger) m_pLogger->trace(fmt, std::forward<Args>(args)...);
    }

    /** @brief 输出 DEBUG 级别日志 */
    template<typename... Args>
    void Debug(fmt::format_string<Args...> fmt, Args&&... args) {
        if (m_pLogger) m_pLogger->debug(fmt, std::forward<Args>(args)...);
    }

    /** @brief 输出 INFO 级别日志 */
    template<typename... Args>
    void Info(fmt::format_string<Args...> fmt, Args&&... args) {
        if (m_pLogger) m_pLogger->info(fmt, std::forward<Args>(args)...);
    }

    /** @brief 输出 WARN 级别日志 */
    template<typename... Args>
    void Warn(fmt::format_string<Args...> fmt, Args&&... args) {
        if (m_pLogger) m_pLogger->warn(fmt, std::forward<Args>(args)...);
    }

    /** @brief 输出 ERROR 级别日志 */
    template<typename... Args>
    void Error(fmt::format_string<Args...> fmt, Args&&... args) {
        if (m_pLogger) m_pLogger->error(fmt, std::forward<Args>(args)...);
    }

    /** @brief 输出 CRITICAL 级别日志 */
    template<typename... Args>
    void Critical(fmt::format_string<Args...> fmt, Args&&... args) {
        if (m_pLogger) m_pLogger->critical(fmt, std::forward<Args>(args)...);
    }

private:
    Log()  = default;
    ~Log() = default;
    Log(const Log&)            = delete;
    Log& operator=(const Log&) = delete;

    std::shared_ptr<spdlog::logger>               m_pLogger;
    std::shared_ptr<spdlog::details::thread_pool> m_pThreadPool;
};

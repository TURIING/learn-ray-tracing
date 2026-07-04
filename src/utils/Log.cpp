#include "Log.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <vector>

Log& Log::Instance() {
    static Log instance;
    return instance;
}

void Log::Init() {
    if (m_pLogger) return;

    constexpr size_t kQueueSize   = 8192;
    constexpr size_t kThreadCount = 1;

    m_pThreadPool = std::make_shared<spdlog::details::thread_pool>(kQueueSize, kThreadCount);

    auto pSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    std::vector<spdlog::sink_ptr> sinks { pSink };

    m_pLogger = std::make_shared<spdlog::async_logger>(
        "ray_tracer", sinks.begin(), sinks.end(), m_pThreadPool,
        spdlog::async_overflow_policy::block);

    m_pLogger->set_level(spdlog::level::trace);
    m_pLogger->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] [%P:%t] [%l] %v%$");
    m_pLogger->flush_on(spdlog::level::warn);

    // 自定义各级别颜色: trace 灰, debug 青, info 绿, warn 黄, error 红, critical 白底红字
    pSink->set_color(spdlog::level::trace,    "\033[90m");
    pSink->set_color(spdlog::level::debug,    "\033[36m");
    pSink->set_color(spdlog::level::info,     "\033[32m");
    pSink->set_color(spdlog::level::warn,     "\033[93m");
    pSink->set_color(spdlog::level::err,      "\033[91m");
    pSink->set_color(spdlog::level::critical, "\033[41;97m");
    pSink->set_color(spdlog::level::off,      "\033[0m");

    spdlog::register_logger(m_pLogger);
}

void Log::Shutdown() {
    if (m_pLogger) {
        m_pLogger->flush();
        spdlog::drop("ray_tracer");
        m_pLogger.reset();
    }
    m_pThreadPool.reset();
}

void Log::Flush() {
    if (m_pLogger) m_pLogger->flush();
}

void Log::SetLevel(LogLevel level) {
    if (!m_pLogger) return;
    m_pLogger->set_level(static_cast<spdlog::level::level_enum>(level));
}

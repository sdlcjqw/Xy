#ifndef __XXY_LOG_H_
#define __XXY_LOG_H_

#include <string>
#include <stdint.h>
#include <memory>

namespace xxy {
	//日志事件:记录日志内容
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr;
		LogEvent();
	private:
		const char* m_file = nullptr;		//文件名
		int32_t m_line = 0;					//行号
		uint32_t m_elapse = 0;				//程序启动到现在的毫秒数
		int32_t m_threadId = 0;				//线程号
		uint32_t m_fiberId = 0;				//协程号
		time_t m_time = 0;					//日志时间戳
		std::string m_content;				//日志内容
	};

	//日志输出级别
	class LogLevel {
	public:
		enum Level {
			DEBUG = 1,
			INFO = 2,
			WARN = 3,
			ERROR = 4,
			FATAL = 5
		};
	};

	//日志格式器
	class LogFormatter {
	public:
		typedef std::shared_ptr<LogFormatter> ptr;
		std::string format(LogEvent::ptr event);
	private:

	};

	//日志输出位置
	class LogAppender {
	public:
		typedef std::shared_ptr<LogAppender> ptr;
		virtual ~LogAppender() {}
		void log(LogLevel::Level level, LogEvent::ptr event);
	private:
		LogLevel::Level m_level;
	};

	//日志输出器
	class Logger {
	public:
		typedef std::shared_ptr<Logger> ptr;
		Logger(const std::string& name = "root");
		void log(LogLevel::Level lev, LogEvent::ptr event);
	private:
		LogLevel::Level m_level;
		std::string m_name;
		LogAppender::ptr 
	};

	//输出到控制台的Appender
	class StdoutLogAppender :public LogAppender {

	};
	//输出到文件的Appender
	class FileLogAppender :public LogAppender {

	};
}

#endif
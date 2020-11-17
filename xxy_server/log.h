#ifndef __XXY_LOG_H_
#define __XXY_LOG_H_

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <iostream>

namespace xxy {
	//��־�¼�:��¼��־����
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr;
		LogEvent();
	private:
		const char* m_file = nullptr;		//�ļ���
		int32_t m_line = 0;					//�к�
		uint32_t m_elapse = 0;				//�������������ڵĺ�����
		int32_t m_threadId = 0;				//�̺߳�
		uint32_t m_fiberId = 0;				//Э�̺�
		time_t m_time = 0;					//��־ʱ���
		std::string m_content;				//��־����
	};

	//��־�������
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

	//��־��ʽ��
	class LogFormatter {
	public:
		typedef std::shared_ptr<LogFormatter> ptr;
		std::string format(LogEvent::ptr event);
	private:

	};

	//��־���λ��
	class LogAppender {
	public:
		typedef std::shared_ptr<LogAppender> ptr;
		virtual ~LogAppender() {}
		virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
		void setFormatter(LogFormatter::ptr formatter) { m_formatter = formatter; }
		LogFormatter::ptr getFormatter()const { return m_formatter; }
	protected:
		LogLevel::Level m_level;
		LogFormatter::ptr m_formatter;
	};

	//��־�����
	class Logger {
	public:
		typedef std::shared_ptr<Logger> ptr;
		Logger(const std::string& name = "root");
		void log(LogLevel::Level lev, LogEvent::ptr event);

		void debug(LogEvent::ptr event);
		void info(LogEvent::ptr event);
		void warn(LogEvent::ptr event);
		void fatal(LogEvent::ptr event);
		void error(LogEvent::ptr event);
		void addAppender(LogAppender::ptr appender);
		void delAppender(LogAppender::ptr appender);
		LogLevel::Level getLevel()const { return m_level; }
		void setLevel(LogLevel::Level lev) { m_level = lev; }
	private:
		LogLevel::Level m_level;						//The level of current log
		std::string m_name;								//The name of current log
		std::list<LogAppender::ptr> m_appenders;			//The set of log appender
	};

	//���������̨��Appender
	class StdoutLogAppender :public LogAppender {
	public:
		typedef std::shared_ptr<StdoutLogAppender> ptr;
		void log(LogLevel::Level level, LogEvent::ptr event)override;
	private:

	};
	//������ļ���Appender
	class FileLogAppender :public LogAppender {
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;
		FileLogAppender(const std::string& filename);
		void log(LogLevel::Level level, LogEvent::ptr event)override;
		bool reopen();
	private:
		std::string m_name;
		std::ofstream m_filestream;
	};
}

#endif
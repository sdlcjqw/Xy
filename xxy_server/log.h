#ifndef __XXY_LOG_H_
#define __XXY_LOG_H_

#include <string>
#include <stdint.h>
#include <memory>

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
		void log(LogLevel::Level level, LogEvent::ptr event);
	private:
		LogLevel::Level m_level;
	};

	//��־�����
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

	//���������̨��Appender
	class StdoutLogAppender :public LogAppender {

	};
	//������ļ���Appender
	class FileLogAppender :public LogAppender {

	};
}

#endif
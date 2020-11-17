#include "log.h"

namespace xxy {
	Logger::Logger(const std::string& name):m_name(name){
	}
	void Logger::log(LogLevel::Level lev, LogEvent::ptr event) {
		if (lev >= m_level) {
			for (auto& i : m_appenders) {
				i->log(lev, event);
			}
		}
	}
	void Logger::debug(LogEvent::ptr event) {
		log(LogLevel::DEBUG, event);
	}
	void Logger::info(LogEvent::ptr event) {
		log(LogLevel::INFO, event);
	}
	void Logger::warn(LogEvent::ptr event) {
		log(LogLevel::WARN, event);
	}
	void Logger::fatal(LogEvent::ptr event) {
		log(LogLevel::FATAL, event);
	}
	void Logger::error(LogEvent::ptr event) {
		log(LogLevel::ERROR, event);
	}
	void Logger::addAppender(LogAppender::ptr appender) {
		m_appenders.push_back(appender);
	}
	void Logger::delAppender(LogAppender::ptr appender) {
		for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
			if (*it == appender) {
				m_appenders.erase(it);
				break;
			}
		}
	}
	FileLogAppender::FileLogAppender(const std::string& name):m_name(name){
	
	}

	bool FileLogAppender::reopen() {
		if (m_filestream) {
			m_filestream.close();
		}
		m_filestream.open(m_filename);
		return !!m_filestream;
	}
	void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
		if (level >= m_level) {
			m_filestream << m_formatter->format(event);
		}
	}
	void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
		if (level >= m_level)
			std::cout << m_formatter->format(event);
	}
}
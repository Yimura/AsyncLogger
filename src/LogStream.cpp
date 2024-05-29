#include "LogStream.hpp"

namespace al
{
	LogStream::LogStream(std::string name, void* userData) :
	    m_Name(name),
	    m_UserData(userData),
	    m_Enabled(true)
	{
	}

	const std::string& LogStream::Name() const
	{
		return m_Name;
	}

	const void* LogStream::UserData() const
	{
		return m_UserData;
	}

	bool LogStream::Enabled() const
	{
		return m_Enabled;
	}

	void LogStream::SetEnabled(bool state)
	{
		m_Enabled = state;
	}
}
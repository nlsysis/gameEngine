#pragma once

namespace Engine
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			:m_Time(time)
		{}

		operator float() { return m_Time; }  ///invert the class to float type number.

		const float GetSecond() const { return m_Time; }
		const float GetMillSecond() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}
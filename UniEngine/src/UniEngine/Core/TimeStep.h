#pragma once

namespace UE {
	class TimeStep {
	public:
		TimeStep(float time) 
			: ts_Time(time)
		{
		}
		operator float() const { return ts_Time; }

		float GetSeconds() const { return ts_Time; }
		float GetMilliseconds() const { return ts_Time * 1000.0f; }
	private:
		float ts_Time;
	};
}
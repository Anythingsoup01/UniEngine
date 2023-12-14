#pragma once

namespace UE {
	class TimeStep {
	public:
		TimeStep(float time) 
			: Time(time)
		{
		}
		operator float() const { return Time; }

		float GetSeconds() const { return Time; }
		float GetMilliseconds() const { return Time * 1000.0f; }
	private:
		float Time;
	};
}
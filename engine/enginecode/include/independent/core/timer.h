/** \file timer.h */
#pragma once

#include <chrono>

namespace Engine 
{
	/** \class Timer - Interface timer class*/
	class Timer
	{
	public:
		virtual void start() = 0;				// Starts timer
		virtual void reset() = 0;				// Resets timer
		virtual float elaspedTime() = 0;		// Gets time passed from start to end point
	};

	/** \class ChronoTimer - Chrono timing class */
	class ChronoTimer : public Timer
	{
	public:
		virtual inline void start() override { startPoint = std::chrono::high_resolution_clock::now(); }	// Starts timer
		virtual inline void reset() override { startPoint = std::chrono::high_resolution_clock::now(); }	// Resets timer
		virtual float elaspedTime()	override														// Gets time passed from start to end point
		{
			endPoint = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elasped = endPoint - startPoint;
			return elasped.count();
		}
	private:
		std::chrono::high_resolution_clock::time_point startPoint;
		std::chrono::high_resolution_clock::time_point endPoint;
	};
}
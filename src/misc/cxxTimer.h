#pragma once

#include <chrono>

/*

	MIT License

	Copyright (c) 2017 André L. Maravilha

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/


class Timer {

	public:
		// Default Constructor
		Timer();

		// Paramaterized Constructor
		Timer(bool start);

		// Copy Constructor
		Timer(const Timer& other) = default;

		// Transfer Constructor
		Timer(Timer&& other) = default;

		// Destructor
		~Timer();

		// Copy Assignment Operator
		Timer& operator=(const Timer& other) = default;

		// Transfer Assignment Operator
		Timer& operator=(Timer&& other) = default;

		// Start The Timer
		void start();

		// Stop The Timer
		void stop();

		// Reset The Timer
		void reset();

		/*
			Return The Elapsed Time
				@param: duration_t
					The Duration Type Used To Return The Time Elapsed.duration type used to return the time elapsed.
					Default: std::chrono::milliseconds.
				@return: Elapsed Time
		*/
		template <class duration_t = std::chrono::milliseconds>
		typename duration_t::rep count() const;

		// Getters
		bool isStarted();
		bool isPaused();

	private:
		bool started_ = false;
		bool paused_ = false;
		std::chrono::steady_clock::time_point reference_;
		std::chrono::duration<long double> accumulated_;

};

inline Timer::Timer() {}

inline Timer::Timer(bool start) {
	started_ = false;
	paused_ = false;
	reference_ = std::chrono::steady_clock::now();

	if (start) {
		this->start();
	}
}

inline Timer::~Timer() {}

inline void Timer::start() {
	if (!started_) {
		started_ = true;
		paused_ = false;
		accumulated_ = std::chrono::duration<long double>(0);
		reference_ = std::chrono::steady_clock::now();
	}
	else if (paused_) {
		reference_ = std::chrono::steady_clock::now();
		paused_ = false;
	}
}

inline void Timer::stop() {
	if (started_ && !paused_) {
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		accumulated_ = accumulated_ + std::chrono::duration_cast<std::chrono::duration<long double>>(now - reference_);
		paused_ = true;
	}
}

inline void Timer::reset() {
	if (started_) {
		started_ = false;
		paused_ = false;
		reference_ = std::chrono::steady_clock::now();
		accumulated_ = std::chrono::duration<long double>(0);
	}
}

template <class duration_t>
typename duration_t::rep Timer::count() const {
	if (started_) {
		if (paused_) {
			return std::chrono::duration_cast<duration_t>(accumulated_).count();
		}
		else {
			return std::chrono::duration_cast<duration_t>(accumulated_ + (std::chrono::steady_clock::now() - reference_)).count();
		}
	}
	else {
		return duration_t(0).count();
	}
}

inline bool Timer::isStarted() {
	return started_;
}

inline bool Timer::isPaused() {
	return paused_;
}
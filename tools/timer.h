#if !defined(__JEL_TIMER_HEADER__)
#define __JEL_TIMER_HEADER__

#include<ctime>
namespace jel {
	class timer {
	private:
		std::clock_t start_time;
	public:
		timer() {}
		inline void start() { start_time = clock(); }
		inline double stop() { return ((clock() - start_time) / (CLOCKS_PER_SEC)) + (start_time = 0); }
		inline double GetStartTime() const { return start_time; }

	};
}
#endif
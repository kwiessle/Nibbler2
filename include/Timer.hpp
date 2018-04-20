#ifndef TIMER_HPP
# define TIMER_HPP


# include <time.h>
# include <sys/timeb.h>



class Timer {
	private:
		Timer(Timer const & src);

		Timer &			operator=(Timer const & rhs);

		int		_refTimer;
		int		_newTimer;
		int		_diffTime;

		int 	_getMilliCount();

	public:
		Timer(void);
		Timer(float diff);
		~Timer(void);

		void 				changeDiff(float newdiff);
		void        resetDiff(float diff);
		int					getDiff(void) const;
		bool				update();
};


#endif

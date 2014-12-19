#pragma once

#include "ScreenAffector.h"

class Effect;

class FadeAffector : public Affector
{
	public:
		explicit FadeAffector(double i_alpha, double e_alpha);
		
		virtual void init(Effect &effect);
		inline void restart(double i_alpha, double e_alpha){ init_alpha = i_alpha; end_alpha = e_alpha; initialized = false; }
		MainAffector createAffector();

		const double getInit() const { return init_alpha; }
		const double getEnd()  const { return end_alpha; }
		void setNumLoops(int num){ num_loops = num; }

	private:
		double init_alpha;
		double end_alpha;	
		bool initialized;
		int num_loops;

};

class ColorAffector : public Affector
{
	public:
		explicit ColorAffector(double i_alpha, double e_alpha);

		virtual void init(Effect &effect);
		inline void restart(double i_alpha, double e_alpha){ init_alpha = i_alpha; end_alpha = e_alpha; initialized = false; }
		MainAffector createAffector();

		const double getInit() const { return init_alpha; }
		const double getEnd()  const { return end_alpha; }
		void setNumLoops(int num){ num_loops = num; }

	private:
		double init_alpha;
		double end_alpha;
		bool initialized;
		int num_loops;

};


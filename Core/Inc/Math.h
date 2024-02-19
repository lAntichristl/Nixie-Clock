/*
 * Math.h
 *
 *  Created on: May 1, 2020
 *      Author: hardware
 */


#ifndef SRC_MATH_H_
#define SRC_MATH_H_


class Math {


public:


	class Polynomial {


		float *coefs;
		int degree;


	public:


		inline explicit
		Polynomial(float *coefs, int degree)
		: coefs(coefs),
		  degree(degree)
		{

		}


		inline float
		getValue(float x)
		{
			float result = 0.;
			float power = 1.;

			for (int i = 0; i < degree; i++) {
				result += coefs[i] * power;
				power *= x;
			}

			return result;
		}


	};


	class Lowpass {


		float alpha;
		float last;


	public:


		inline explicit
		Lowpass(float alpha, float initial = 0.)
			: alpha(alpha),
			  last(initial * alpha)
		{

		}


		inline float
		getValue(float x)
		{
			auto value = last + alpha * (x - last);
			last = value;

			return value;
		}


	};


};


#endif /* SRC_MATH_H_ */

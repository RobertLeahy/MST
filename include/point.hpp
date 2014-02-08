/**
 *	\file
 */
 
 
#pragma once


#include <cmath>
#include <functional>
#include <type_traits>


/**
 *	Represents a point in 2D space.
 *
 *	\tparam T
 *		The type of the coordinates.
 */
template <typename T>
class Point {


	public:
	
	
		/**
		 *	The X coordinate.
		 */
		T X;
		/**
		 *	The Y coordinate.
		 */
		T Y;
		
		
		/**
		 *	Calculates the distance between two
		 *	points.
		 *
		 *	\param [in] other
		 *		The point to which to calculate
		 *		the distance.
		 *
		 *	\return
		 *		The distance between this point and
		 *		\em other.
		 */
		double Distance (const Point & other) const noexcept {
		
			return std::sqrt(
				std::pow(
					static_cast<double>(X-other.X),
					2
				)+std::pow(
					static_cast<double>(Y-other.Y),
					2
				)
			);
		
		}
		
		
		bool operator == (const Point & other) const noexcept {
		
			return (X==other.X) && (Y==other.Y);
		
		}
		
		
		bool operator != (const Point & other) const noexcept {
		
			return !(*this==other);
		
		}


};


/**
 *	\cond
 */


namespace std {


	template <typename T>
	struct hash<Point<T>> {
	
	
		private:
		
		
			typedef std::hash<typename std::decay<T>::type> hasher;
	
	
		public:
		
		
			std::size_t operator () (const Point<T> & p) const noexcept(
				noexcept(hasher{}(p.X))
			) {
			
				std::size_t retr=23;
				
				hasher h;
				retr*=31;
				retr+=h(p.X);
				retr*=31;
				retr+=h(p.Y);
				
				return retr;
			
			}
	
	
	};


}


/**
 *	\endcond
 */

#include <weighted_edge.hpp>
#include <mst.hpp>
#include <point.hpp>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>


using namespace Graphs;


class signed_mt {


	private:
	
	
		std::mt19937 gen;
		
		
		static std::mt19937 get_gen () {
		
			std::random_device::result_type result=std::random_device{}();
			std::seed_seq seq(&result,&result+1);
			return std::mt19937(seq);
		
		}
		
		
	public:
	
	
		typedef std::make_signed<std::mt19937::result_type>::type result_type;
		
		
	private:
	
	
		static result_type convert (std::mt19937::result_type from) noexcept {
		
			union {
				decltype(from) in;
				result_type out;
			};
			in=from;
			
			return out;
		
		}
		
		
	public:
		
		
		signed_mt () : gen(get_gen()) {	}
		
		
		result_type operator () () {
		
			return convert(gen());
		
		}
		
		
		result_type min () const noexcept {
		
			return std::numeric_limits<result_type>::min();
		
		}
		
		
		result_type max () const noexcept {
		
			return std::numeric_limits<result_type>::max();
		
		}


};


class Points {


	private:
	
	
		signed_mt gen;
		std::uniform_int_distribution<signed_mt::result_type> dist;
		
		
		typedef Point<signed_mt::result_type> point_t;
		typedef WeightedEdge<point_t,decltype(std::declval<point_t>().Distance(std::declval<point_t>()))> edge_t;
		
		
		std::unordered_set<point_t> points;
		std::vector<edge_t> edges;
		
		
	public:
	
	
		Points (signed_mt::result_type distance_from_origin) : dist(
			(distance_from_origin<0) ? distance_from_origin : -distance_from_origin,
			(distance_from_origin>0) ? distance_from_origin : -distance_from_origin
		) {	}
	
	
		//	Generates a number of randomly-dispersed
		//	points
		void Generate (std::size_t num) {
		
			//	Loop until we've generated enough points
			while (points.size()<num) {
			
				//	Create a point
				auto x=dist(gen);
				point_t point{x,dist(gen)};
				
				//	If the new point does not lie directly
				//	ontop of an extant point, add edges to
				//	form a complete graph
				if (points.count(point)==0) for (auto & p : points) {
				
					edges.emplace_back(
						edge_t{
							point,
							p,
							point.Distance(p)
						}
					);
				
				}
				
				//	Add the new point
				points.emplace(std::move(point));
			
			}
		
		}
		
		
		std::unordered_set<point_t> & Get () noexcept {
		
			return points;
		
		}
		
		
		std::vector<edge_t> & WeightedEdges () noexcept {
		
			return edges;
		
		}


};


void print (const WeightedEdge<Point<signed_mt::result_type>,double> & e) {

	std::cout	<< "(" << e.U.X << ", " << e.U.Y << ")"
				<<	" ==> "
				<< "(" << e.V.X << ", " << e.V.Y << ")"
				<< " "
				<< "(distance " << e.Weight << ")"
				<< std::endl;

}


template <typename T, typename RatioT>
void print (const std::chrono::duration<T,RatioT> & dur) {

	std::cout << dur.count() << " " << RatioT::num << "/" << RatioT::den << "ths of a second" << std::endl;

}


int main (void) {

	Points points(100000);
	
	auto start=std::chrono::high_resolution_clock::now();
	
	points.Generate(1000);
	
	auto hint=points.WeightedEdges().size();
	auto vec=MST::Kruskals(
		std::move(points.WeightedEdges()),
		hint
	);
	auto end=std::chrono::high_resolution_clock::now();
	print(end-start);
	
	for (auto & e : vec) print(e);
	
	std::cout << vec.size() << std::endl;

}

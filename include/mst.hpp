/**
 *	\file
 */
 
 
#pragma once


#include <weighted_edge.hpp>
#include <union_find.hpp>
#include <algorithm>
#include <cstddef>
#include <vector>
#include <utility>


namespace Graphs {


	/**
	 *	Contains methods for finding the minimum weight
	 *	spanning tree of a graph.
	 */
	class MST {
	
	
		public:
		
		
			/**
			 *	Implements Kruskal's minimum weight spanning
			 *	tree algorithm.
			 *
			 *	\tparam VertexT
			 *		The type of vertex in the graph.
			 *	\tparam WeightT
			 *		The type of weight of the edges in
			 *		the graph.
			 *
			 *	\param [in] vec
			 *		A vector of edges in the graph.
			 *	\param [in] hint
			 *		Optional.  The number of vertices in
			 *		the graph.  If specified the algorithm
			 *		may stop early once it knows that it has
			 *		inserted enough edges into the minimum
			 *		weight spanning tree that the output
			 *		graph is guaranteed to be connected.
			 *		Defaults to zero which means that the
			 *		algorithm will always run its entire
			 *		course.
			 *
			 *	\return
			 *		A vector of edges in the minimum weight
			 *		spanning tree of the graph.
			 */
			template <typename VertexT, typename WeightT>
			static std::vector<WeightedEdge<VertexT,WeightT>> Kruskals (std::vector<WeightedEdge<VertexT,WeightT>> vec, std::size_t hint=0) {
			
				typedef WeightedEdge<VertexT,WeightT> edge_t;
			
				//	Sort the incoming vector so that the lowest
				//	weights are first
				std::sort(
					vec.begin(),
					vec.end(),
					[] (const edge_t & a, const edge_t & b) noexcept {	return a.Weight<b.Weight;	}
				);
				
				//	Loop over each edge
				std::vector<edge_t> retr;
				UnionFind<VertexT> uf;
				for (auto & e : vec) {
				
					//	If the edge links two unlinked
					//	components, add that edge
					if (uf.Find(e.U)!=uf.Find(e.V)) {
					
						uf.Union(e.U,e.V);
						
						retr.push_back(std::move(e));
					
					}
					
					//	If the tree is spanning (according
					//	to a provided hint) short-circuit
					//	out
					if (
						(hint!=0) &&
						(retr.size()==(hint-1))
					) break;
				
				}
				
				return retr;
			
			}
	
	
	};


}

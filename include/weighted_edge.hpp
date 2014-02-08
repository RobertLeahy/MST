/**
 *	\file
 */
 
 
#pragma once


#include <functional>
#include <type_traits>
#include <utility>


namespace Graphs {


	/**
	 *	Represents an edge between two
	 *	vertices of a graph.
	 *
	 *	\tparam VertexT
	 *		The type of the endpoints of
	 *		edges.
	 *	\tparam WeightT
	 *		The type of the weights of
	 *		edges.
	 */
	template <typename VertexT, typename WeightT>
	class WeightedEdge {
	
	
		public:
		
		
			/**
			 *	An endpoint of the edge.
			 */
			VertexT U;
			/**
			 *	An endpoint of the edge.
			 */
			VertexT V;
			/**
			 *	The weight of this edge.
			 */
			WeightT Weight;
			
			
			/**
			 *	Determines if a certain vertex is
			 *	an endpoint of this edge.
			 *
			 *	\param [in] v
			 *		The vertex to test.
			 *
			 *	\return
			 *		\em true if \em v is either of the
			 *		endpoints of this edge, \em false
			 *		otherwise.
			 */
			bool IsEndpoint (const VertexT & v) const noexcept(
				noexcept(
					static_cast<bool>(
						(std::declval<const VertexT &>()==v) ||
						(std::declval<const VertexT &>()==v)
					)
				)
			) {
			
				return (v==V) || (v==U);
			
			}
			
			
			bool operator == (const WeightedEdge & other) const noexcept(
				noexcept(other.IsEndpoint(std::declval<const VertexT &>()))
			) {
			
				return other.IsEndpoint(U) && other.IsEndpoint(V);
			
			}
			
			
			bool operator != (const WeightedEdge & other) const noexcept(
				noexcept(other.IsEndpoint(std::declval<const VertexT &>()))
			) {
			
				return !(*this==other);
			
			}
	
	
	};


}


/**
 *	\cond
 */


namespace std {


	template <typename VertexT, typename WeightT>
	struct hash<Graphs::WeightedEdge<VertexT,WeightT>> {
	
	
		private:
		
		
			typedef std::hash<typename std::decay<VertexT>::type> hasher;
	
	
		public:
		
		
			std::size_t operator () (const Graphs::WeightedEdge<VertexT,WeightT> & obj) const noexcept(
				noexcept(hasher{}(obj.U))
			) {
			
				hasher h;
				
				auto retr=h(obj.U);
				retr+=h(obj.V);
				
				return retr;
			
			}
	
	
	};


}


/**
 *	\endcond
 */

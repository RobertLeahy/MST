/**
 *	\file
 */
 
 
#pragma once


#include <unordered_map>
#include <utility>


namespace Graphs {


	/**
	 *	Implements weighted union and collapsing
	 *	find.
	 *
	 *	\tparam T
	 *		The type of the vertices.
	 */
	template <typename T>
	class UnionFind {
	
	
		private:
		
		
			typedef std::unordered_map<T,T> map_type;
			
			
			map_type map;
			
			
			typename map_type::iterator create (T a) {
			
				auto cpy=a;
				return map.emplace(
					std::move(a),
					std::move(cpy)
				).first;
			
			}
			
			
		public:
		
		
			/**
			 *	Finds the parent of a vertex.
			 *
			 *	Collapses as it searches.
			 *
			 *	\param [in] a
			 *		The vertex whose parent shall
			 *		be found.
			 *
			 *	\return
			 *		The parent of \em a.  May be \em a
			 *		itself in which case \em a is the root
			 *		of its component.
			 */
			T Find (const T & a) {
			
				//	Find this vertex
				auto iter=map.find(a);
				//	If this vertex isn't in the map, or
				//	if this vertex has itself as its
				//	parent, it's the root of its component,
				//	so just return it
				if (
					(iter==map.end()) ||
					(iter->second==a)
				) return a;
				
				//	Find the deepest parent
				auto parent=Find(iter->second);
				
				//	Collapse
				iter->second=parent;
				
				return parent;
			
			}
		
		
			void Union (T a, T b) {
			
				//	Get the deepest parent of A
				auto a_p=Find(a);
				//	Get the deepest parent of B
				auto b_p=Find(b);
				
				//	Put A in B's component
				create(std::move(a_p))->second=std::move(b_p);
			
			}
	
	};


}

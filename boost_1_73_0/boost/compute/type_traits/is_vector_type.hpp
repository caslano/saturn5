//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

#include <boost/mpl/bool.hpp>

#include <boost/compute/type_traits/vector_size.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \p T is a vector type.
///
/// For example,
/// \code
/// is_vector_type<int>::value == false
/// is_vector_type<float4_>::value == true
/// \endcode
///
/// \see make_vector_type, vector_size
template<class T>
struct is_vector_type : boost::mpl::bool_<vector_size<T>::value != 1>
{
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

/* is_vector_type.hpp
l/DJEv4g3APnwb3wObgfLocH4LvwIDwGD8NvZX75gjbev8KK8CRsAj+HsZB09Toz3I+vu87MKOKZzIEhcDQsAO+BUfBeWB7+FVaB42E0nAgbwMlynPn6vqfupeo44cgc1/kgOALWgyVhE1gDNoO1YXt4O+wC28BMGA/7wCTYF6bBu+FaDhIP18MEuBkmww/hUHgeZsAf4Aj4E8yEfeCYvEgzWsbImFTeu3Ey1yPzU23yPu7W
*/
//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP
#define BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP

#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>

namespace boost {
namespace compute {
namespace detail {

namespace mpl = boost::mpl;

template<class Vector, size_t N>
struct mpl_vector_to_tuple_impl;

#define BOOST_COMPUTE_PRINT_ELEM(z, n, unused)                                 \
    typename mpl::at_c<Vector, n>::type

#define BOOST_COMPUTE_VEC2TUP(z, n, unused)                                    \
template<class Vector>                                                         \
struct mpl_vector_to_tuple_impl<Vector, n>                                     \
{                                                                              \
    typedef typename                                                           \
        boost::tuple<                                                          \
            BOOST_PP_ENUM(n, BOOST_COMPUTE_PRINT_ELEM, ~)                      \
        > type;                                                                \
};

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_VEC2TUP, ~)

#undef BOOST_COMPUTE_VEC2TUP
#undef BOOST_COMPUTE_PRINT_ELEM

// meta-function which converts a mpl::vector to a boost::tuple
template<class Vector>
struct mpl_vector_to_tuple
{
    typedef typename
        mpl_vector_to_tuple_impl<
            Vector,
            mpl::size<Vector>::value
        >::type type;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP

/* mpl_vector_to_tuple.hpp
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
*/
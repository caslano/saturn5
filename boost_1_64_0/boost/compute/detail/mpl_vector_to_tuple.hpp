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
6b92kFOMWXBeLQXRkLRNwD7RrGzQTwmwfZSvBuIVIsHPqW7GmdnggiR8latG54VuDYJRiZs+ICKT6b4l7E8PkpxTaWhga+/Ynuj1jQUToN+tb75Fdzv8kZshrfWS4I2am2bBF7nC4aGGO70V6HNGX1wTWCwPYxTA61FnC2OQbpPGYmm5FtZP0WcwUuwkeLSBLOe06Gl0YsDqCXoJw/MDN45xunJ4uSnK7Tf+PKoIXa4LF9E7qpcHVlTG8rawIdC6cG+UObH4T6Z5gSYe0sJoMqjn2KMCuM5atwxKlIZGbQH/PxQo5nrznAtjbW4ysRryvkR11JGqJNbaf1HnXkN72Y8qCqgkMkiPL6lvBTr17PCwZpyyu0WRC2xL3wCue+4xX6Jk97OsyMIoWwQKf44m79x+3DWYdYBgrVgGaHahtQdlt/VL5lUA3bnB+2rRmuu4hImh6W7Hhwey0qbUQr2FFbojD6sqmShComASSZwuzGqKOUhlgB4kKNuJB1Hsb87gA1keAmISWxe/BcidZ49jnGyfO/cr91mNHBQplWqfe6pka2Yx8bw25bix2A==
*/
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
ZBPmoAV0W82Fiye/kD7suTtZ1o9XJstk/t1kmWxb03LIc8F9k2Xt6qfzUjrJr5Ur51dP2eQfQPkhrjJPGianhkZ2kslzDM1Lnig6ypXTg6YhrrWONEwWteY0TB5Ktp4s00kdGiY7t03asj3XmCOvpSZ9FKWTJXqOtuxEU4C2zJD1lAufuvtKummyo3Sy7Pvdlu1Yu90hYbJyd6RpyIarubZskb1F05DwpoJX0vKPbJXtAZvQMoms7jaU8Xnptmxb0YPyQ7Yb/daUy9rIW438tsuB+yBszEjDop8a/k43Bp32040BKefWldcfPhThWkD2gJrVVO4BS7uo4T2U2wOayO0Bk/Yp2gOqd4IgVHm9Cg6Pc9sjWb0G+6gEyGjqOk82C01vQKXN0S94yUbNSRrm3vcvPkTDZGTtomE3jv6ll2zkrqRhYshGgM6FZ9NwLpdmGg0T7T09QWYcW3Wg70Vw4b40XMil30LTZHPh7nJ5G9M0+Rx9Hk2TyoXr0TQZXLiCjtxkLjyapknkwo8mybZeF9qTcoo4ei+aJp4Ln6ZpSrlwS0pP58J7MQsR3mg4mgv/Pl5W/i/jZeX8OF42uo/Okc3kb7SIzMnKMlqunKE0TGbLzzGDEd4myWbLkzQvmXUXjpetCBXt3ktnuec0TGa5RzRMDII7CBOZj5fN3qcpncjqrKesjW3Hy/roK09Zn66h6UlfL20n67sYzxcf
*/
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
bWhVC/VYxkapwsKnmzELIvxV2mY0y/YhTCjQ/Eaehd9EHD1VDjHxbcn2ZX7lfdmX18jPJPKiQOnNxbfMb3h0PxMhewVvv6JeVs4Qt93qdc+pFc2QzSJumMwUc+AbldlHPEjiss6dr5j3xy6h9UvrlPbhGbhtIu3w0hn8nLAwsfQLn74k7I9kuOhdD9BTCyFY/bdf0Tf3juy9rRWBTKl6IhWZQkK0O/J42R7g+mpEcuYvKRxeUSnST5hKF4sIKE+EJLFfkZXYrNRss0j6oZrORYWWb47t3Y20XEn6MSIykEt9wbib5f2ZfpWXBYv98Kd+1fxnb8Dev2f7hzQu1K+crvm+t0/f+81h6/Kp/5civGwae6OkcX6vsM3R0c/YJpwS8t6vNE727k9Yp2SevaNV85y8YJ2SEJuZp7z536n0Vorm0820hNV/YZfDYX/nYKvo8L9soFIBjGLWvUYD3aio3bS7FR463t3QQ2X1PE6tdrVNEoVxKoNkG4gI/ZWnQaIl6PWHo1bT6V70GgYebaAg0FCu2DrnBU9mf4oz/Hv5k5xftGjb+XBZZdC9nwn5byrxK+P9D7z4/5eCnP0Gkf7fZzDXqWVPpGUtIX0+xQOAE6Amg9AYkoP5DH5JZabxrOEZvKdonpxF91Yo7nP4
*/
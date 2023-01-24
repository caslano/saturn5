
#ifndef BOOST_MPL_COPY_HPP_INCLUDED
#define BOOST_MPL_COPY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename Inserter
    >
struct copy_impl
    : fold< 
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

template<
      typename Sequence
    , typename Inserter
    >
struct reverse_copy_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(2, copy)

}}

#endif // BOOST_MPL_COPY_HPP_INCLUDED

/* copy.hpp
YiaH9Z3bR5E/qVhnQWRcf+IjCAnh2o3zGI1HkOj8tenhTaOHXLef1T1JKbjmp73PpwsCw3WMAj2cHJg9fxWTwQjdI3De17/Wmo5pORhq+uvEhjY8RpuYgvVs8jrpHuurLhJjTMZZUV7kZLUzbS/1LZaR/ypcS2aFbZJ25E0uzLdvH3UCf6LUo/5VRzEVljZdRfaZLFQekvq8qcZZdUaEZOKfMhj8GDy8VdWXKqKRebz4gr6F37ZPgbgSaHgnFvvnkEpaC00bQ3zDjUovXpgbT6fox/8EbJ1oOln09PBQlfXn//b8W5WvGRMgE00AggnX2Gjq/QNOWBtxT+e+X05b2/4hp5lFUdtf1Zk7AeCzuakdv5WYRAZqm17lEPvzY4cr7iV4fwsRDgCF1rTpgKErfF5/p9exCeoq5HT7DqDc+UkGFPxK3FFA5+O7fM2hV1DVGftHV5BvF+yzXlhP55c5vdeODQix2mtHK37M0i/Rf44BhxBvTLUCBwCYpwzoyXK7pUTaTNkbYKT0ULu4qwyoN/F8/tJpC2pc2+vik5EBbpq9Ovx9wjN8ng/SPlm7lo0Ocr8l90MA31mNRiBQdpRcXg5NDS7DhuyKipOq2guODC9a2mqJIhFSHi72/XPrvx2vT124uM52d3srZqw5DTp8VlddRf+6cP7fyf4D4nPsrf/fHqXYu3RLhfA+fPgAhPlfUf/Z/wPqv6fDj98Z
*/
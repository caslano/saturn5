//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_QT_QVECTOR_HPP
#define BOOST_COMPUTE_INTEROP_QT_QVECTOR_HPP

#include <boost/compute/detail/is_contiguous_iterator.hpp>

#include <QVector>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename QVector<typename Iterator::value_type>::iterator
        >::type
    >::type
> : public boost::true_type {};

template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename QVector<typename Iterator::value_type>::const_iterator
        >::type
    >::type
> : public boost::true_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_QT_QVECTOR_HPP

/* qvector.hpp
Cmbwkp+ZetGk68m6GBAUm3XldmOBV864VABRiEXkRwz0t3Ep3vy0GlHP2wDX2//j3EZaybmkMlsPz9Y5EvWZfJZmBdE6yVbuXe9YWJj9oip8LHT4Mmb+uSRftxpbsUrS8ij5GUfmBxzCOEm6U+ij7GmGm52d9EKGhshhZ4gT1cfno/Ow88qdRKGowxPwsBMKaGFYTC/ons58O86j6W7B3OXhUEkgG+45K+q9Eo77R2Bs0Z0PAkx5D+glbCaW64Qs5HMk/uln71Dsvu2aVkS4fLOD+jDvvQqhhLjzNAOF7xgmR2aOe7oJelvkpXMBi7KcZrYZ624wcZGuu9N2AlPwnacvFjrG3ZOgFSf7OOUoJyy7WXZn/vp7pRNcp/0yu955fedh554QB4ROt1gU+6XVwuX6OZ34bPkZHYCn7War/4u70JT6cIKVLFfGprSHB3Yftgsen3FPAjv7GRzwGY3DVz8/NWQwgU5Zpcya2w8wx5sIuFuHv2MFiZ8kHyzWnFmDlIGpoducn7lxtUmylF1C64AUY2mn8ccPAwpzNRd+BXSvR8irNo2o7I6cOH+eEigy1MukZF1xXF01N1k7dXFHTh6sj6sT7XjxsU+Pfq2QbFOdrhUhAHYdP9x8nep00lN7yIV3lIJ/1pef9TOqf+l2e8I64mWD73454BXQaSMcjonCzygL3uPbU0p8Xw9h+e39oZ3qjaXdquHUhFk0
*/
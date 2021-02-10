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
hPrmDF2rZC9DgmhyUNTV4vE2g82zTz49/ubNtzs2P70qui69jLBihd5AJPNqepUcbJkQdmE75bz1YoBnDoOFG9jt69ZbToPhJ6LQIRyLjMecWeSCKTItXaTkX4QxDi+FBxL6pXPziteUpgpSUlbrGsby2bMnMZ+jDQjFk42UV8W2mjHjg3LlzQpqRPE0AhJnyqPPhdqTpOvWhhy/AxiQ0aCoUPFGeD4MFSFAz1mUbyeWedisXGXhl0waCLeivYNt5DZkIF96IyImSzKyYJzFIPrXby7cW9JnA+olxCZZiKs5DHd8D6p7uCqmIXWq6oWGEdw57p/pJBkwQVcXwdwxgYAUJZckXyC0rfYEuNyNim5dJSJriTHfVA4xL/uBUjcG6eMr4PhlX9t2JUeH0+sht6Bs6bzeqOivNerZw+Om6oDg2L42ajQ5WhJUC0SouPtL+loY0RRsx2bdf1tNyN6PQp4/WCbEue8pcDzZDaB90UjXhJ5X3X3Qc62BVjvY81sKAn3RT8MXkZko2IBZzRAVJSonON1NbgM+9EA/E8PbEbhl7hYbyBBVh4M8UHpRfqgXm4VZl1BX+YUbVdzdgm2ywDAFkTQ4B9u4xzXtxdnXZsn3D8YPMsszAbAH8BgTpRXm8LtwivcgXzq+HCI2
*/
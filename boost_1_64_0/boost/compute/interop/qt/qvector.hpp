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
UXCTpfgvcI76izO49umyShPZYkS4GWrvIbY2NdEBAaZjyHca4MvXPwDwd4pUT8OnLqQk2ivyh8kl+XmH3oiMJvpgU3IVp0CNl+Ngeo1ym1RlJU5bsvkfzZ+fjZNQ/vZIqxn/+OhcyIkEuBnAncQws8oZycwpP0cptYs8kUZa4jKrimuTzdbLG8nUZ5RmWLnZaX69yLd7TQCvS6p3lca5fdaVrMWhG9RqTMUTRCLp5C7YqXK8tX85mhn6agI8vxlBtRgUEDb6uPdSPHzmNZK+W72R6gz6aXXplquD/i/nwya7NW5/gQJhPq486d7nSze0LjwjxUIeGdjPOhrHt6iQpSkXDpYZr8t6Q6NDCGeb1txdRzXZQxr7v3oOr+rCzXqwMbFqp08Fn/5oaYj5+XRpQVaCYxngBX1k+y1oCnSehBPl+8ol2lXf9Prx2QvVUZka15zttedvLH67JumjbLaNV5XYCK53MKDrEpodWt6jOijhjs+P2/agBf3eKBY7ANjI6g7cffsjR9vNdGyykUUOdCg0rEoK547Ll+Le/bd/4aghxiSQ+b9elqEqvA==
*/
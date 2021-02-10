// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_SEQUENCE_ELEMENT
#define BOOST_GEOMETRY_UTIL_SELECT_SEQUENCE_ELEMENT


#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace util
{

template <typename Curr, typename Next>
struct pred_more_precise_coordinate_type
{
    typedef typename geometry::coordinate_type<Curr>::type curr_coord_t;
    typedef typename geometry::coordinate_type<Next>::type next_coord_t;

    typedef typename boost::mpl::if_c
        <
            boost::is_same
                <
                    curr_coord_t,
                    typename select_most_precise
                        <
                            curr_coord_t,
                            next_coord_t
                        >::type
                >::value,
            Curr,
            Next
        >::type type;
};

template
<
    typename Seq,
    template<typename, typename> class Pred = pred_more_precise_coordinate_type,
    int I = 0,
    int N = boost::mpl::size<Seq>::value
>
struct select_sequence_element
{
    typedef typename boost::mpl::at<Seq, boost::mpl::int_<I> >::type curr_t;
    typedef typename select_sequence_element<Seq, Pred, I+1, N>::type next_t;

    typedef typename Pred<curr_t, next_t>::type type;
};

template <typename Seq, template<typename, typename> class Pred, int N>
struct select_sequence_element<Seq, Pred, N, N>
{
    typedef typename boost::mpl::at<Seq, boost::mpl::int_<N-1> >::type type;
};

} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_SEQUENCE_ELEMENT

/* select_sequence_element.hpp
ZE7PaP384uyvvxLL4aJxOjkCSqrvjI9kNjIa0hy5kOinzqB37GFmao9+LiP31mFXDW2bmsp+AVU7+EHmQj24lfH9QxXAgRbbqyfq9WCw1znvOaOjhLn4oXZ49Zv9AA2hnUaBM5QWTtNLRM7qn8s0cW/4C3db0jECMtveW/BCEQL0zNpB2OrXF0DoK+a+iU0qElml1cvgm85qGcYdopFxZYlIgSggJfTM/mf/2VNUASzy8RIFUQhDAIfpJB3FbC9gZ737gCkQJJh4rxPurAB6ZYT+Tyg0XpIxvLqNgStEGblydxJAb75IZ/Hibp9GAWgiIQIturkWPhamlmOkMjwF3ufi3G2Ix+QAKVah00EV62FwKYvimllfbFBIi8HgDXHI0Un3VQcwQQXCCGdDqwbh2rofmlz9lshtTMcGDMiCw7vRSNglGRqjjgGgNp6Di5hqDbrwMnvXDfEDEk8yyUOHtKZvQG0S+kSJ8ww37+mP33+v8aJ+YMiJzpXSmaYsBcgXd7b9//zww+GKxiJqFHeGXevPoIlm/XYjXUXOdoykUOJxeso0SQYUy0gUEEz4ihT11irCtCpIdwPvNMDosx/Rcrmw7hSAMZIx9wREJ5TN4uIjwgcKK2CwyTQlzoP0Xmh9nd4Ar8ad2K0gMiAZ
*/
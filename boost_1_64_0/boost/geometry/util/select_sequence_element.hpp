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
wCH0GeT8CdxfX0pzapG3j3JBzAGPWVim8QtFj2FdKIrhxOoWlSK91oN8BrvPYSNhXXRF8NRiDUrE9c567TtUtl6elaWPGIXwG5pzkUuHsZh3LYApYc5i/hF3yNcEGhCY3dafKz1SmTEKBkN4wC+rat6andziD1wWYoFRURB+HTTdiRZqPn0/gvawWXLtV0/UKajPf8qHbGfVJeAYM0EzId2wgzQhmumlX2HOPBpo1fi/d4pr+4nywJGQmiSQ5qoVd2e/XFsD92x6qU0F4Y8h90Bhbd0osWrybKD6e0Uno+CKWP2OPk5k72Ux7zoGL//PN1kUK07fEkRMByZsnnN06sf8v1oiLTKwm+wsZuCZ0mZ1KTYoAy5N/19dG8ZnTaD5RqlfijhC70NFuGZSDjQBvPA75mC8cGczQUrNkVClsEdE0eZaKNJOmmFO8wrrDMDEwoYSbwCbU8Oosh+Iq/SKZO0zJAtkDctLxUjKHfbopMEHH2gDX0JbD8bpqap1a7DMPEEvy8K78n5wkkUO2iuHvY0uDcEVx0nPtTLyfYc+z21SQIdK7yncndaozA==
*/
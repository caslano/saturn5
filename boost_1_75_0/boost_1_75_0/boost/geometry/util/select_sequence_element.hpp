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
zsngR3EqnB2ZvAaGpIx+dVzDQ2fEo7CT6fiUzDKrig5Lk15Vg+muqDTndWPMKPUJ+BV/YqG2LfaNkfHzbL254DS15zrSgmEAk/9A+Vbkm8EcI9faOicH+YYMwOwXcnbNimtsmP6KJBksZWJd2htitxJ6t+7CkmLy8SIoyQ9dqFsS/b0uNlxsTGbm/ug9VYoQ+rqqrNmkhM4mDtT5XR2cXmshtPZEVCE2P6TyIJ8m8LjFvLXDtqSXRaLAL7BBITPRZYNxuMfLk1JERRUuWmpFPCOB4vcFBPno4EveHuNPlFN8qAYTdcR6qIZqwMjgWUZFfoV+spPIMFydIH2j0Gp8aALl6jgUE8bgkZWvfSQB0YYaQzehJ4Ee59hHZq8auJFtQUHT7KS32dDuuFvlB7Xmc9j0cvupYVODbaqtNgfgtIk+YVeniiPzSwODIh6n49tDzNx5w9YoZIBAquOajFXMuEFwvP5CsNw4g/5s5VrCxxPueUNKigLXpoxHqynK1P3CweOGKOxYLHGO5NoDT4DGnIWTyJWPjgYIDjFYmEo4nzDvdfRTuT9RONzTOfkk/oNVI3XSnJanQAsQGuEw6wSqBOeWToxcV32TUWwH5y7X8DTyDF/xmY0XCxRpWBVX2yn/TV/Ytd5SiC3RylZhch37ysUHuyG5HhWSqwLcqZon9gp/BovCfGJugl1Yjs3JnNe8M4aFNJ0OZsfxxyiH
*/
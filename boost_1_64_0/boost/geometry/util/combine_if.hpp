// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP
#define BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP

#include <boost/mpl/bind.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/set.hpp>

namespace boost { namespace geometry
{

namespace util
{


/*!
    \brief Meta-function to generate all the combination of pairs of types
        from a given sequence Sequence except those that does not satisfy the
        predicate Pred
    \ingroup utility
    \par Example
    \code
        typedef boost::mpl::vector<boost::mpl::int_<0>, boost::mpl::int_<1> > types;
        typedef combine_if<types, types, always<true_> >::type combinations;
        typedef boost::mpl::vector<
            pair<boost::mpl::int_<1>, boost::mpl::int_<1> >,
            pair<boost::mpl::int_<1>, boost::mpl::int_<0> >,
            pair<boost::mpl::int_<0>, boost::mpl::int_<1> >,
            pair<boost::mpl::int_<0>, boost::mpl::int_<0> >        
        > result_types;
        
        BOOST_MPL_ASSERT(( boost::mpl::equal<combinations, result_types> ));
    \endcode
*/
template <typename Sequence1, typename Sequence2, typename Pred>
struct combine_if
{
    struct combine
    {
        template <typename Result, typename T>
        struct apply
        {
            typedef typename boost::mpl::fold<Sequence2, Result,
                boost::mpl::if_
                <
                    boost::mpl::bind
                        <
                            typename boost::mpl::lambda<Pred>::type,
                            T,
                            boost::mpl::_2
                        >,
                    boost::mpl::insert
                        <
                            boost::mpl::_1, boost::mpl::pair<T, boost::mpl::_2>
                        >,
                    boost::mpl::_1
                >
            >::type type;
        };
    };

    typedef typename boost::mpl::fold
        <
            Sequence1, boost::mpl::set0<>, combine
        >::type type;
};


} // namespace util

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_COMBINE_IF_HPP

/* combine_if.hpp
w76PUve95P+HavueoVT2As+Y0qw866IiP5RBrf/sdvLd8LhJGSxcVPyY9ynJO6Jq3pGMZcpg//shb/VcT5P3D95oONe5CfHDuabmeUjyLDfs78x8hx+2Uz3GE2WU/BB9HcuLFR3K1zJLrh++l6n7+KDk/9xRY/68RlJa9Mbf9ih12/l/jyeq5S01UFTMUKcMf7bvh6QMGR8YysAFNCcrJ9Nd+7zCyQ/H3AjJPzVU5ot/T5//3Pg50xLmWZLj5sTN9LyZyuUsLvLLdU4tx3Epx19qLAfnvdNRWOSH+hijtncd5dnZ8RrLkV1Y5PI0vf6sk7NSlnM114nN7nBl+6Mcap2slJfPlR6tsRzWYlc2b/xeas/zQ1m077/ybr7zNdbJMHaQf45X9bxdLeW49WiN5fBb/s3kvX2HfdcDY40bf/vVY6JM8l/ve/vzC5fa3W8tdrq/JvljX6jteJi8y++k77rIKci2O/15X7ZVyhDiu91YdDHO1QiZPKN1jeWI9Ot+UY/RXVKWY773C1+oGv/7u7pPIuU9f9/7zt9qs/mvrVC/4+yWcgwxnCspqbPmxPvtO45aBzHy/r4336ueNw2U9hpeh9WV7Y/7iH5qHUg5epnUAQ1Vo+cbpR4D3ZRPpx6rnm9eodXG//Etizuposbfdm3/SxkiTLadE8Cv5+Cg7vK+HZP9z8HP5hfmFjv8l/9uyT/xqHn+fNP1y7mnHf9XyT28Sf6TUtPc54D21CrDD+VQj8NyKcdi3+Xw2728WoZxV8szYd9l4K7e4p6/yW9lqJAyLPVdBmmTGv9ZsVqGyT2UT6/0XYZIaqHAH892tN9/pAwx5mXwS5uonpOxjKfy6CPvnAL/PNNU6/+A5J9mnj9fUOQpth/LMLWn8mmb7zIMUx4F+K8Mh6QMDt9liOTC7LTm+68Myb2UTy+soQz+qgf1eKyUMowxL4PfrpH91GOht/LpA9785Td33shdlO23fCskX9eRqvn653uxmu8oGey3pfr22vzxXUDNd4/k+3L1fDPz/ZCvenxF9lU+/ZLhO1DirFkzrkv27GGLLccfbY32/U/y32+Wf1ZOnj+vMxH9lE8fNMubGQL98azm3+ydCXhcUxTHx76TWIuq8PnsKpmmUbtpJm1DmkSaUoTXycxLMjKZGbNEWrVvQVEEtddee1HUvlPUTps2aRS17wThq+W89/735m2xfXPy+Xj380zz5iW/e+727j33nHPl+g/soWItarUpYevXQp8+dAecxSL610S+/VlR3jPBnCZ0yhNqqpVG00KrsTLnbFHeQ3bE+8TMDqdU0iIbc9wo7VmNzj1fvEuuBL/VxIcivTlOgUVJduN1xlDnO4sy2Al7w+Y8HGJM8EeTSiqi5F5+we4A+zwXdoCJLe0fdsaYbmaXhmJhpY2NOQ3MDgczm3OmaOMrwDzFwUyrKWrk2mYVx5gi+NN2wX68g2/EQ+biizL/Gvx2B380GzOyK+xPHcxAzpmiLy0Dc/YiwRwXGFnkV2pToXi6IZHiGEOk/eduxtPX2djlTOsiaf8J7pUm7ohRxWxcUdYVw42nLzFx/SNLBqWsnwF7hpXNJrPg7rO78fTZZq6fr6yl/SO4p5m4Rf0lnXOutH8sxDnQZi5JyzEXErLOArNdzP/IR0BX8OinEOR+feMHd7sivIfN3EbitoZi0Yiu7SX7OLJdYtT5zkIeOmQe4B8hMsGwhy3KfYgf70g7m9l+ZTq4qwvbXrJnxgYHG9M3AnY6PSZmOjqVY00l5gAnEVP/NDGlsUxE1TgsY4iQuRd8n7mcqWo5ZBbMJgTKWtfCJIU1Qx8SzG4wJy8SzEBlUKmfklHTbMzqkcbTDy01M2k=
*/

#ifndef BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : not_< typename Map::size >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
s6T13PmKuDipmV11nXFju5ROnmX95nIGTjrjuVXgZioLaaz8v3H/Uc4jbdnKy8bjRhusTrZtvvfJM7q7lG/djspvQI7BepzJbRxrSzEXu3L9Mq5beQ0uUV+DtWmdnsCijsuu1Ndq0tCm7GCblB28QKhG2Er4Tmn7PsmmLFgGsVCSxJQGHjfx/FP3u26MBpXjnM8x2lLZNP2qsj1o+X1Q8q18vyzf6TTZ4b6q33+7Jm39N8n5nYs/KGXfadb9JSkJk6LZVuO+ejuxr1IOZLevta3li/y/+edL9lnSQIbEtTnu8anR6alpGdLXvJS7mPOC7PM/2O6M+IQ0vd/j8zb9IGvTTvKPrIfVJKery7GZhxM1PlbeK0nOMKX/3Ca2ZU/xkhFmynt10/FH1uc5xb5MUn0/FXKTziG5T9A9h7Tpds78Gy7TpKxf9f6JpKMlL0p6Ozj3DtmUiUr5ruYYlJjjUzZK8rXSuFM5gZT+Ho9OsebrAlUZqfp+KimdHIm15dg4ykunLdOJSKYVWqZZ5zuoyRPKOg9b5pOrjWxne3faPLOdw11I8wet9zDHNfdB6jLZJQ9q+srOtP1+TPO960O236eqvivrvFfymY/05/+gXKfSCUs9lcIdYz4j+0bHTTRcv7zbfL7WYdlYc76S72NU15N/KudEkINjqsovRMj+y7lnXqaV7fmxqJpOn+AP35qyYB/pZ7+uxFeH8DPbFeooPrJVWeJbr1MWbD4X+zKzQTMOw7rqjsumYx6+9WXT8yrevL7Ib1bZ9H/aONM6fXnr9Ale9ve9HNcN3Lw+wRs9oUzPGFIlZFvnH3Y+EhZzZcDFsDMuZX4/rKx1Azp9hev2mf6TUgZeUcoYpMyhkD/C+DtA3qMaLGWJQ9ALI7A+DkM/F3k/CUdgZxyJYRiFQ3A0RmE0PoRjcBbG4TOYgO9gIn6DE7CivJdUBSeiD6bgPTgJO2KalK2nYzJOkTL0B3EpZuIKnIbrcToewJl4GGdJGfpcKTufhyU4H6/iQqxAGiySMvQl6Ik5WBuXYQN8DP1xFYbharwPH8epuB6X4gZciRtxHebidnwS38On8Aw+jV/jJryAm/FnfFb6Pt6ixI9bsSE+jx1xGybhdnwE8zAbX8J5+DKuxR24E3fibtyF+3E3vot7lPjxVfwO9+IF3I8/YT6W4AF13+DyPFOfQP7RHee7Lqr7Pg+V5RrKcnrvN/qgvyyXX0Gee+U5mOWo12G/UPn8IO9LnUcvLMEGeBED8BL2x18xGq/iOLyGqfgHTkWOvTGfVsSF6Ior0Q034O34DFbGF7EK7sKq+Aa64wH0wHexOp5HTyzBGvgb3olKXVJNdMfaeCfWwbrojQ2xPvqhDwZgAwzGhtgZm+BAvAuHoR+Ow6aYis3wQfTH6Xg3ZmNznI/34E5sg59jX/wG++NvOABJA5eB6IGDsBYORh+MwKY4FO/BkdgBR+EAjMJwHC19FBe6yHOtPO8WEury93E5/tvlOL4ix3GnHMfXsC2+iX3wIN6Pb2MkvocP4PuYgEdxAn6AaViADynx4Az8GOfgCVyIJ3EZfoYv4Cl8B0/jETyDp/ALLMIv8QJ+hW7swzm8Hb9G0/uG8twqz7OFmvcN28v1tQPWxxBsi50xBLtgN6mTHI6hOBq74RjsjonYQ66rYVJn0xOXYh/cin3NfetXkOdKed5kezi3OM5y/qRLuk/B+vggNsFMOX+mYmd8GHvhdEnfGTgJszATZ0o6zsLVOFvSMxt34HzciwvwDC7EYlyEVdmWxeiBS7A25qAPPoYDcQXG4kpMwlU4H1fjclyDK3At7sT1uB834I+4ETl3XXLRC59U4sGnsCFuQj/cjMM=
*/
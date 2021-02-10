/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOIN_200601222109)
#define FUSION_JOIN_200601222109

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view.hpp>

namespace boost { namespace fusion {

    namespace result_of
    {
        template<typename LhSequence, typename RhSequence>
        struct join
        {
            typedef joint_view<LhSequence, RhSequence> type;
        };
    }

    template<typename LhSequence, typename RhSequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::join<LhSequence const, RhSequence const>::type
    join(LhSequence const& lhs, RhSequence const& rhs)
    {
        return typename result_of::join<LhSequence const, RhSequence const>::type(
            lhs, rhs);
    }
}}

#endif

/* join.hpp
RXxflivGkEChO0myAXHjmG8hlQdeCnNbRX6+X74sh75TwfMGlD3w8LpCMTMcjwaT1sj/s0M38gYkntZMnOzprkRjrzUK/2rSK+QhjfwRdGMZYIB05oI0CuUe78yS/KTOlapj0u1kdORvmLPhQBJxyl0Rc4SLlylKml9N3UAcm+G4wAAJ5EgiOlKXiFBlUyxIfr2+1guxiuEzgWyeA/cA6a1codbJMxUCts+hk6jF0LSH2NlNkXMcdGgQ7cHV+Sf/GxFYjhngQbwF7UiFkmW0AOXhQgJT73v4CN3Y1kyfCqvII7iIALg1kKf1aqQI+1vQj0jJALZIg4jlTWZr2aiBhLV+8zK/IW9xdJV/knE9xgeHOaPGVlPICqtXw1HnM1HBQYdVSSlivsXhJGE7WEapLw34YxUhhHtmS1KFvDFQNxfcyKjfq/HHMnH57YkawQZxSkjVIGpYPRhtOaQ2Ww2kgLpYwuMS0v8WJ7yplvlYltew1RmrR6flVIwCBs42GtgHoDAKY1J2jeK1COs/H9lbI7kLvod5COKYZjuk/SYeaXgJ54C8t5epbYCPlPuO+GDSjc9R+Vz2YUVbv5TMGolK9CARACU/nAJImcpUnnxxWpj9pr0tBqvwRxRvEkSU65ap0wWUdNpAJiaxvM9v
*/
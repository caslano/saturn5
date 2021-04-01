/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_09162005_0150)
#define BOOST_FUSION_COUNT_09162005_0150

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/count_if.hpp>
#include <boost/fusion/algorithm/query/detail/count.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count(Sequence const& seq, T const& x)
    {
        detail::count_compare<T> f(x);
        return fusion::count_if(seq, f);
    }
}}

#endif


/* count.hpp
8hOqQ/fXu+LdXHiq4+CqeeOu/S8NH9SQPQ8RoNTDSJPLIcYISj/xLiK6x1bZCqsMGlYZpeZrpxETfxl9A4FNVOdE7QrX91nmm4ddFY8D+NnvJLmAjN11jp7ZORHBzbC2E8neiuyU3N606OiIR9k5CvtHXROWVDS2ONFyHmjv/aJpnkrreQBtk6uXWNx58RcOtnQLwizeCzpCkqofL8lHiTe9cAJaNHlgPu6tLgiiXHdE69+dbLQW/pLc2/8srVTT8u40SoohYCh+BxYR5N9kdVkY2CHE71+sM7sMVk5NAlWR3wAX+zKC/Rds3Tp9W564V5/J8mWnvbJdqmtT9gPlDwVvU3KansrmQiru0rX+hujlTBhbR2puchoablCY2LWQTRXATqbJDBjdSYVlO755w7V0lAwrIYIS+qUHIoJqNfqQFCIXJwvEsvHn9xDNkosUq/HtAdt+j6zwqEzc8jRPnppXwjWjjC6nBFUT0FRIOKPj7SLQStIciq+l+dMHvG8VVpVwzRmgbKkZ8KxcPN0azdMbJxxZdmnkYF8LzYf86/8JZCAAiECjVj2NRA==
*/
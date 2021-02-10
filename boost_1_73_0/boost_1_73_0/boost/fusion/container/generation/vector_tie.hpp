/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_TIE_11112014_2302
#define FUSION_VECTOR_TIE_11112014_2302

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/generation/detail/pp_vector_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct vector_tie
        {
            typedef vector<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T&...>
    vector_tie(T&... arg)
    {
        return vector<T&...>(arg...);
    }
 }}


#endif
#endif


/* vector_tie.hpp
x3Y257gwFtgUrYmDEJdgWmQnTUK2G8QbOH9gS+BWNk7XPjxIETX3XNswGH5V9nf77iWMdgn2YbLIaZkX1HRjtolr1edgxilXLehpdDNJcHVrw0oy4Q/YXuf8QchCJcsq4lVAFQWxYbe0Hww5v+9zFWLp6IHYIhMXfuI1oVL/K8pTYqgFL1t9/Iu4KuSccmAa/v+dCONVNSbSA17j9kWvsdHMsfyTYyrjoZiKcOt2Ugo+zbGVr2LaONuCURXTpiEtY1prvlpkg4k/rke09oSG0A02RRy29JF6IjBTNGq+17Jibc5Q3H/s206sMGZ4Up5SuHQHUWKWmrMZV1PCZuqAZspohp9f1QtP9/oKWEtFZLtqUU0uW4Jy+ZZrGtUy962oBUNW1iYG7qRP7EpzhpedqbkhltbLqXi3w/WR0+7CayL98E1qqh+jJl78dKXp1yRd3Xe2rztfqJpSaUcVt64+VI2ru0/5JNjuf6gQ6j9QSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAABAACQBjdXJsLW1hc3Rlci9saWIvVVQFAAG2SCRgUEsDBAoAAAAAAC1nSlKTBtcyAQAAAAEAAAAeAAkAY3VybC1tYXN0ZXIvbGliLy5naXRhdHRyaWJ1dGVzVVQFAAG2SCRgClBL
*/
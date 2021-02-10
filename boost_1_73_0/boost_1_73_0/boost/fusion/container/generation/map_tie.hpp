/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_TIE_07222005_1247)
#define FUSION_MAP_TIE_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_map_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct map_tie
        {
            template <typename ...T>
            struct apply
            {
                typedef map<fusion::pair<Key, T&>...> type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair<Key, T&>...>
    map_tie(T&... arg)
    {
        typedef map<fusion::pair<Key, T&>...> result_type;
        return result_type(arg...);
    }
 }}

#endif
#endif

/* map_tie.hpp
EkojYaGFTFtom4Pm+VwRB5lniZLAHphI2D0aYhpirTP1c7sdFnmC3rcjGap2uAq/Fev5OpI7dGLOliAzDVpCobgFhLRgLiMxpScKgoNZcZ8IFVsbb9BUGrVlDoonCXHhPMFV6TYHv5LHIhhk6LHQ9FAyVWRqEct5DYg6Esu0yFM0hDogKJIoswUFbqHcgE3kKxOVpkbgJ1Oz8TcCmaIzcGT70POP4J4poSy47Y1vvMkYbu3RyHbHd+Bdg+3eEdnHntvF1As0lgN/zHKu0HgOYp4lgkeVzR/3ajcaxyINkyLicGSyFx/R0JQqCO6iMEsKRe8Gf0QlMJTOEfzbOOYp5qqBlcPIwvMcfQwlLkSYylI3rC6A5QXQhF5mnPh4WsxxMpgKNHEC76O1+eM3uxvc2G6371hbG/kUzomhhhrao/HQ67ljZ2StUBc11MDuX3ujgdMNeu5wMl6jXu5zeaNx4E4Gv21xvaqhJq4/GRIM2fzOjTMg/xB1WUeN+l2n43W3nSfUVQ2FSQ+862DgDLzRnbVBva5z+c4ocL1xYPf73q3TtSrUmx2/PrrerWvUsLYsvq2hXG/jdE3Vs10YWd0GlbDzXdjQ9v1bb9S1arCLXZg3HPc8199J5ctd2I3nj/eNvtoz6o0OwC53Yb9P
*/
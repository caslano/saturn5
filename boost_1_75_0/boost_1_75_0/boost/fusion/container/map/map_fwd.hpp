/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_FORWARD_MAIN_07212005_1105)
#define FUSION_MAP_FORWARD_MAIN_07212005_1105

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_DECLTYPE)             \
  || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_RVALUE_REFERENCES))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   define BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no decltype and variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/map_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct map;
}}

#endif
#endif

/* map_fwd.hpp
YKqt3/1bC2O87i5uCeN1RP/mnOxOn4OcsalzTGd2ohnmdBPMzpqmMN9SDLa4MgHmbGfWhmy0yYVbgxolwR2og9u9ReC+cb3kihjgCiC/nG2MK8KIsgkjTBvg038ZwEbwCfzeowRrigFrSqayBtiJ7n4aegaeKX5XUkzpNi0fhAtTswPLYU15ldis3nXwvpC6slsU2YqvAooW+zgVPAGnFvXMpNKQWdkYIbPIOoa8BaPJ5RSc90dDzKikRB6VWddJL7kKuHNQJiMVTC9Nt8H4rHyW5L+ejWh3uPDPEOTKlnaHU9AuPIAxc6LZeEwKGY+Zyn7mZ5KviScfNT3RerbWOpLo6MZH8MqhDr1P6RM5I5t+uGViS/r4Tr9wO8O0TA8804SmhInnd+XnDupdy5UmlUW+OjHvdQDLsqIwX9BgaA6n+1MrmFpLQmsLsc5yuK560+9wkLUSrzLUobl8E8GckXUiZJ+P966ZZHpx/j5menvEPXEiYS7qdHkQcz1saRHqyJ4Yhxb6fbDwPIfgLoZ608p0rENA1gadBl1dRIPmy65cvg+fN+ZmiJWXo3tmkmsywxOYjvscq6gc8SpRKDSGXp3hpTvJveKiKBaEnevD5fsJ6GAhVx54gOi5mm2cK5PpjdAjO8f6T364gK4h7Z2ZGbSvosUc6GAKQtKkHfJ/UPEKi2H45Pz7WT7Bw5V7RAQhwhBzvivD8yX5QVbE
*/
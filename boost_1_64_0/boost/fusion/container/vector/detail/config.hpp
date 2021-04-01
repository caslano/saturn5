/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_CONFIG_11052014_1720
#define FUSION_VECTOR_CONFIG_11052014_1720

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/fusion/support/config.hpp>

#if (defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || defined(BOOST_NO_CXX11_RVALUE_REFERENCES) \
  || defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)  \
  || defined(BOOST_NO_CXX11_DECLTYPE)) \
  || defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) \
  || defined(BOOST_FUSION_DISABLE_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   undef BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   define BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   undef BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#endif

#endif


/* config.hpp
o60kSwO0TY6VxF4EXaj/k19spBTQ3/dTBHNM91LXV1lIXRUOqR+9XYoUQ7uFPd9YIltZjR5UynUGJ1mXfAAXeE9EW14oGDnKfydXJbUMcSthm/86sIDcLyYBG6k98SuLSBi5GfmMpUwZJK7o/f+xDvp25kr1GFXflvlkM1phF7LB606h61yOykcKvFdsLZ4b7Sx/QB+jCqzasK3j6xFzj7pKe1QA0Mf+HTCPSse62s2Cu21iUb3je0GS/oEj7B+Om9WTc3Yui+OTQ2v4wO7kfQylLVbdA2yY6fl5dqrcTJILUBw4hYyen7Itovo2gKiRra1OYZ1CI/jAIvCvZAyI7GljfHVWy5fz7ajUun+Gb6l3tossv/IwjtGykPi3rRGuwjWfjS1zVgkt/CdJ4ma7sbYECK4zhHCfZZLoOpoemE5zdHyNzgsf7HQND8HqeZpnHneHhfFSpSO0IvgF4C5il93lB78+Gd56ujV4FvKpMuOL71B7xI/46FIZYv3xnxTCeEJ+73x2/KQbu2T3Z7xji6x/OVgduakGzYf2GEBoy3hq7CthyD4QF0c0KA==
*/
/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_FORWARD_02092007_0749)
#define FUSION_DEQUE_FORWARD_02092007_0749

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   define BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/deque/detail/cpp03/deque_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct deque;
}}

#endif
#endif

/* deque_fwd.hpp
B2xskLLRs3/l6rgwckaocjfI2D6pxqOewGUSNzxtnmb6IuFBGA2p5I3iPZPiyxygvy2yQwIoTQd3RIw+r4gfZ878vlBE9OSYxRCNW5YtXOo8ZA8y8XfBF9zYVpgMyPWXRArGDKPEb6tA8L970kJsC+aMn34hxSy4AfT2/LmiDjSuG0yZNFCckJDYSCeSfiQ76PHKSDewamtzY+KAs9S4ftSFdrebIC2yfHhyq+wTtxl6yRdvdJ4AvQ88CWgkI6Cmttf/Yf4CZgyIxWkCBBS6jV94FhLRB4bGc5M9W11vBVfT++EFjinrTT62Y9aJEC8rmxx3jAKYBpEjJKIKEb73l4vF9YvjRrFBUFKOimNjaLPkLL+ArtCN0W+zR1+ii25Rti0HsWpkqmCj+RHIFFVEbWxXkX6KXq/63Z1bF9JGjAyBBULPSwSXfo0loNuPAWO2ToYVRVuCAdoB6UUAkS/9BG7PqaCAr66HadKW37d5hful8MkKNAWcChWFJQ5oX77WQYOxABOsUKW1TCV0Wvo0GjXeAlfarId+fN/gq8VYhR3PLpERfTJw4KE8Sg==
*/
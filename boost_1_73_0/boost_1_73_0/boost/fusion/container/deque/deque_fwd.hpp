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
V2HEv1pE2oyxsqRA4zR7uTxpg0pliyrn8WfYpE7ruQE8YZN61gC2sVGdNqpk9Qob1bNG8pTNyooh277OgH0ithqNqnlQOZD0gvk9Si+kidG2HNuTC3X6CwsFKXHbBXpChrPi136PCg3PWp+nyzY0TlPKnzlI4ijX9ex4yq1WhPrkU1R9hizi/lTFlm33YcsKLg2rFqgJ6tiqj6eDPBpnpVmitjFkpMNgk8YLEzNRbddIV6CKNbZCzHrqHCxX+qqUpS69GfzJUw7gDSt67NnaFh7Cc9Qtv8oIPUP1YtXn1KqXYIEyc5zPYms1TPOcwDZbGX1MZbeWx8VmyRZ3tT5KgLCSPikVnnHffqrg8OhqMOCgHy2LiAatBF2yXLkp3oXMlJzh1ZiPVIqP0KryDUmyxMeFvTMnY6QLqF6IlGxamkHtM80GOe2HwAZ7q3AkbZW44PPKlRZSV276ZbnOG2flprrRR+MPUeml3Opf8oqXlOZo2FVD4ZB82bn0WSorS+hJ74u15bOSt13eM0qdvJnS2C7t0CUTIrQ74qqo0rlLaiOTYEJz9mznRsTJNCR++R/pJNTfvj4qGSUgM79YkRWiYUWtfQQiSdkT6tu2rLNvPBQXd8Fy+eiFj+E10n+UpSRvDgbfJv43/7zZ7Y6e
*/
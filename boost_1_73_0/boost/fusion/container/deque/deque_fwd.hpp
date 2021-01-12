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
zCOflxGbiVoMM4N804j1xHmiQAjbN9GZGESsJw4TVgrsICKWyCTmEpuJU8QtPd2LPKHMFwbiIJxMVAgl77ssEz635XMasd6LtBYsT3wYTD7SznqRTtoCPh/D63TfJ6x5WRak5cP76FqK8zQ+VyGiiKB0houJxH7mL5LvY4hMuqcx3Sl8HsvnKwzzMTGS/DPpXkZsJg4T54mbxALyPsR87Pyu3iwLIpQI7EPeUuRheNW96acU
*/
/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_DEQUE_01272013_1401)
#define FUSION_MAKE_DEQUE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_make_deque.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_deque
        {
            typedef deque<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T>::type...>
    make_deque(T const&... arg)
    {
        return deque<typename detail::as_fusion_element<T>::type...>(arg...);
    }
 }}

#endif
#endif


/* make_deque.hpp
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
*/
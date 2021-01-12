/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_LIST_10262014_0647
#define FUSION_MAKE_LIST_10262014_0647

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/generation/detail/pp_make_list.hpp>
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
        struct make_list
        {
            typedef list<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_list<T...>::type
    make_list(T const&... arg)
    {
        return typename result_of::make_list<T...>::type(arg...);
    }
 }}


#endif
#endif


/* make_list.hpp
zxvuQ583s0Yq6R7M9LVtSEl3xOW5w/+xn7sv7j655858O0vczY/5HDbQOB6TOFZXeA5nYbpRn7/vqH8H4vX5a/rznr8uv+Dzlx3/73n+Nqv+kU6ayNO1T7v4npB6qwMabs+fE0SOuG/qUk81LP5Lpbw3EWshHiYgsZG1YqMrB8q2OtdSCT8t0T9ekpmdlZ2XG/xeO1vCqhTQ23YC7/QTEo/ft2ckaf41gI5IA+zWBJXDJfnj
*/
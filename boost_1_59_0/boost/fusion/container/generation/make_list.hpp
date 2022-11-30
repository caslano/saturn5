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
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
*/
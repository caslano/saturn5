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
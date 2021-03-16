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
8+8q0ZgNANnIc7HnZvVucfj2oRjqb0JJwrRojb7K1iLlV+iIRTpikY5YrCMkglQJfyxoiAPzN9miua5W3E05BoWJLK1sA0sQ3BXlbOwxlMEztBJ88EAo3xakQl2iBPV2EElQiaiOZml7kTqM5Qytzt7+I63eUoamGXnnkaYbJcvE5l3RNXFKuRJzQHlBZamXh3UGL0PXnbZTStegnm1kpw1VRk4nx29j7u4nv5GJHN10fAwBYHmrlOycZLIE19c=
*/
/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_SET_11112014_2255
#define FUSION_MAKE_SET_11112014_2255

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/generation/detail/pp_make_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <utility>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_set
        {
            typedef set<
                typename detail::as_fusion_element<
                    typename remove_const<
                        typename remove_reference<T>::type
                    >::type
                >::type...
            > type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_set<T...>::type
    make_set(T&&... arg)
    {
        return typename result_of::make_set<T...>::type(std::forward<T>(arg)...);
    }
 }}


#endif
#endif


/* make_set.hpp
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
*/
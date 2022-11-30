/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_TUPLE_14122014_0048
#define FUSION_MAKE_TUPLE_14122014_0048

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/make_tuple.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/tuple/tuple.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline tuple<typename detail::as_fusion_element<
        typename remove_const<
            typename remove_reference<T>::type
        >::type
    >::type...>
    make_tuple(T&&... arg)
    {
        typedef tuple<typename detail::as_fusion_element<
            typename remove_const<
                typename remove_reference<T>::type
            >::type
        >::type...> result_type;
        return result_type(std::forward<T>(arg)...);
    }
}}

#endif
#endif


/* make_tuple.hpp
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
*/
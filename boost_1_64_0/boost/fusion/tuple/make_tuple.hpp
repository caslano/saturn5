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
VhbWUh9vFBBBVl6yKTD7wM9MQ9VMuBDYQZggCjrMKMz79/rhvPrPnTN1cYFkHrpDhLtgdEJ67qLkbUKtF+HYgNINcoLOBkGnCHL4vL1fiSHbdEUjarufoOpibJoKgV06EKmN/x7XSlzNqAshw3glPbLh02PSSF8KmDvjGay7vh3uKJM4HWEeSo6l2U8tzZohKh02/XU76oZ0+GnQQNNwTqKUcoxNVhu7Vihfu4JTWXuX8yEV6KBERtB5oQFoyLL+Cgelw2e8888AksYe7INywCfkpreIA9QZgICcHpl10YgUjg5B+fa6BWk0+RAHSElQ5YLFEwClaHdWjNIii1P+7vKdiP06+yNj2r+Pxazo38u0BXezss5u5aNHzWbL4Jh81yihzH26F5bxoUKvIUw/1Lif3fFGOWR230TjhcRHpM+K35j0Hl1YfEBnJbWyBgoHqaTjUnO8d041kPsy+ehizk3Cdi9CK0tR+yT3uqrnsQ4OTm6QWhfrIXXzkFnN64KnKX0pyOJFnnvSs/F0WVTjgv8AWdT71hJ2LalIs6sOZ2XCVIIg2ZsebpTOlg==
*/
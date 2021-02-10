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
HqA5IyIYZazJs9kuSd1VU6/RihCM1SF5ODn8sPkSP+ARlrUPwUJ0X9GmCj8LK90+IRTbOfvj6ZprZCjZa+HDM7GO6Tf1S4Ao5TmhWmsKkyjBOcT/HcE0Gu7XTfo+HTegLYMjXL2d4MWLQLgkvP8N5sMa3pDBw2bwAH5pBQ9IEaKunIzkdxzQNvCJr9ijc4HqCCd+1XxGDJSGmTFczkLghcSQSqoNq9TIZRzGk7H0u95GVK2m2iTQY2gWYFkXTJCBWJEldLTkPDNgZu2gc9zWBBjNRLrjQwvIqXd1Y7j/PxPuGdZyjaicLs8VUJwoyYmWCTU8Og3EREKXL54i9wf0h6kjENBpmH0CJBKEOWM6JFRoj8ClHJ0O3p5224hnjPBhUXYllGjivbaM9chxzqRPbCJ0fRkkaXIxIW1xK+h3z9t8PFFCHmVo56enWsSwBschBnprXlBrBZZ8K0GU2xrja+mssCkDkVfGumvCs4aw059xmxDhELMxJv+yojDYBF3VlPFb82jwCtyngWompwewGsnBq8HKU7JmKd8MmNNYbq1Y+gbCGe56//1Ze3BweNg+68t8Fsx6HAK+UDcQdpGmbqhjNets7pemlQ6sH7wCQG8fDV69HxweHB+/Ojj83dDNbziW8/opPDXMHxL8
*/
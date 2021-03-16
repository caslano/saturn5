/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957)
#define BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<transform_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };

        template<>
        struct equal_to_impl<transform_view_iterator2_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first1_type, typename It2::first1_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
+hxo16W3NrSWVE4k8ShdXwDdrqMfJKySVHkk8ShdXwLt2p31H4ekFkcSj9J1BmhXm9t7D5fUzkjiUbrOAu2adqlpjKTejyQepescWGPIKJ9W7y+T1DeRxKN0/S/QrhtNPrtHUoFRxKN0/Qvo/qp25KUNQio5iniUrvNAu84851gjqT5RxKN0/ZtT1jFqxrb+lZIaG0U8StdXQLu67qvxk1RtFPEoXV8D7cr4YcVrkloZRTxK1wWgXVOPb06R1K4=
*/
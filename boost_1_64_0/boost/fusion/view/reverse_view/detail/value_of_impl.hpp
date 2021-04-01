/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07202005_0900)
#define FUSION_VALUE_OF_IMPL_07202005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
mavZwDZU1COzQdBm0T7ZZsRW/o2MlV4+04NAjCA/Q8j5DdPCM3P4StFn8rs05YOo1jBA3bMWVDC7w8MUpMPvheQjDWP/lj6n5ugjPg9iUWVVKgmLd23PZw1NVVj2tIMwj1g2X4B8uMjOWKqOAn4xm+OHMh6ab27gOAxE0YTaxuUXY6ck1i+Vl4+8q273wpooteLS8MmmkOnOlJZxGan8rPAETh5hCREoVlXNlA21LaW6+XpAE6gOdWruFUnAGo33Oy+TUiAwkgPkBza+3nj8DK3vQwL+LWZ4AmY21Y+XKmAZqSuOnUI/5BdDC0eKqwHFmpnJsuPO7xqLytTFCWrPEswEw3IPdRvoMIPx75WsXXd+MGu/M29J6cf8C+j2J5geWWpR74g2SE/DRFw+4Htr86xzkreyA6BRO62q58OdjHZDdNJjkKfBaVzTkxyvwkGBt5MUYLaLN0jWAna9wyil7O9skOM+APO4gD0AqLcilMgm1yaD587OjC1pMGpuMzZS3wQkxqQyE0oCMFFk/KwURLyC6rIAdo/HNjUok+jB5C/IFAL3hWKWPSeoFQ==
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07162005_1030)
#define FUSION_VALUE_OF_IMPL_07162005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        // Unary Version
        template <>
        struct value_of_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        // Binary Version
        template <>
        struct value_of_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::value_of<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
EWsVDkUmnNJ8gtBvurkKjwb2Za+BC0JSQJ2jtN2PT2F4pDdUArXcVJTQJw0vVX+A1XMbaY3a0JfmNOJtareskW8obOkKK1hBiSI2LUy63CVFV0QyJPd8AydmRqt0YSVAm5zpEraiv2Klj60Rt3tosj2InMorhQcHvqVwYcdWuMD5nFyBSmhlSSyOHhuZEm/Xlq7yQKAsDf9ZJcueGkz7H0pGmFMUMnHZSyw/3vhRhwFQA5o6s8LoMUx/hwz75OofJSeh5To82KeK7CVHs5kZ+/dzPFEI1OgipuHSOehGCV1LW9LIEzUdpJc7FjKXU6MnYo5bCqSHQcCf/EIb+P0tjw7ZmG4vP+HrcDnJrCnM1/wJG0UUiBnlNlEGoAAAPzCd/J/2jR8fcpbyfNr8fbLPBhidN/Avz+UiIUlOxkf38+xKuYwp15JUgPulpytkm/jpQQT9Ctvm1PB60iLBQDGz4UDRZGid6fVyUd53/0b5QjiXlKeqt9nxgsGa7p5Cod2+HLXd+AODgPZve6i1tfYbRowbepq1HX7VjgmRjAcq5g6h1WI5V0FX5ElxLw==
*/
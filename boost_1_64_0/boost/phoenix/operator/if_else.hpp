/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_IF_ELSE_HPP
#define BOOST_PHOENIX_OPERATOR_IF_ELSE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    namespace tag
    {
        typedef proto::tag::if_else_ if_else_operator;
    }

    namespace expression
    {
        template <typename A0, typename A1, typename A2>
        struct if_else_operator
            : expr<tag::if_else_operator, A0, A1, A2>
        {};
    }

    namespace rule
    {
        struct if_else_operator
            : expression::if_else_operator<
                meta_grammar
              , meta_grammar
              , meta_grammar
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<tag::if_else_operator, Dummy>
        : enable_rule<rule::if_else_operator, Dummy>
    {};

    using proto::if_else;
}}

#endif

/* if_else.hpp
6bkM+6wn6cZQXxgf4dBRPlIVxOP+l4sTDvodm8lcAKRYS/MYp44HdxV1ew0ISuBGnFpiIgkflA0VZyfsfa7RmR+NzeyW4r4s7xDPWRvbljKen7QUj+fFfregYOz+hEpEGryD/e0dSG+LesLyBrWl8a3lwu0RGE8G5D+qzRh+hDQnflRSXhglXubcOy70eg0W0aZL1LDPwv72d3vpI53ELCsUOnBiBS5RY9QuuQ6Jj8cfwCbhNs5R0WIVM345N9p88TOAjSfHmHumF3TDYILw8UvmY52G5v8kQrzszzVhm54Gx1DGiNnw9JmiHgfge98/RjfW1JxXTAMYnexrj8i1Rx22aBkrFrGnbJqcXTd6VwgOyfw/wUr22RcGOTvJKHmZ4JKcI1X3RnbmyrhPF+7Qrhy7ZVlaqefcmopqeVqX2Q/eRidORbr1sFy8/GfXU7+/VW2zriwYetfpAs2PT4bSjZhMDrCjaYyvw+RHVEqNeg1uZ299/DMVNDfVoOBdWD8+1BOw0eZetoyCIE1j4BIet4/FM/Mki/jS7v/0WS6J6jrncHbwcjP3fZkHmg==
*/
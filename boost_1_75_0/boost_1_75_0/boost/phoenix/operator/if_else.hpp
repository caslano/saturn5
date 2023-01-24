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
JFLhNcLIsDloj/RxkG7GXkO6QEYOEev/dfZHoEbECgyD6WGRFB3/xZXGiULu+6Irz2ee/fG9kGiuJkZi5UQGqVIxi+ERtQaLQv8oY//kaJs4bSzdca5FhZ+b0Mcus/kluaE4zMTiTnVmVi+aXO5L+HuPylVeNdtJsu7FmN9abFxkcfQY9vtROMrm4PkGi8EfxchdNXtgJpa/ls9tErJrSHNNkinQ10QPtGXiRcYtfZSR0x1v/+ypIoZJ8eFPFDGl+iyS0NbTGUUvoXRM7AXlqaSmnHexCmlUyX4psE7Aap35idoij3fh71tXYhIR94HC9F/7H3EWGwd8+5KIlEj/HL9n5qIxKCsiElYcuhvLbUXiyU+K4EEb9sKIBD43je6PhGUynawBfkdl94z8Gid9NX+6jVbQK+QjUlx/64uwytDct3AQdCTexLCbA6OK4CuW+E7uHfo4L5DwhfETCVoUY5QAMgtpvTR+j23PX2I/ekVKk4fWOIb0m9iXt1jWF4mF6emXX7aqKOd3dfUA+4rCQ3nlOXMV6PECFCwumbrpf1MouGYlkvPHn5SP+/adv3uTnV6Tis5JrDnTXQwE6cCKg1cT0iX7sxC92JKbzZ4khWl7JdI5DcHOd2/6GwIv+nob+voiKNXNHWUtTatRwOO89HeP/Vyr/RMK36f6s1RNJ0mPp7b8rr6jm6/ODS8neWZQIus9EBuEU35Oju4H
*/
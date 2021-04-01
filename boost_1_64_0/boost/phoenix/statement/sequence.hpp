/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP
#define BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/proto/operators.hpp> // Included to solve #5715

namespace boost { namespace phoenix
{
    namespace expression
    {
        template <typename A0, typename A1>
        struct sequence
            : expr<proto::tag::comma, A0, A1>
        {};
    }

    namespace rule
    {
        struct sequence
            : expression::sequence<
                meta_grammar
              , meta_grammar
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<proto::tag::comma, Dummy>
        : enable_rule<rule::sequence, Dummy>
    {};

}}

#endif

/* sequence.hpp
JISo4cqaaH1RzoHsfWSArNc8QUmDrOao/kCF9BbeTGgLu9yWc83Q/JOyfL9xv/tYOAzpY+yMBJ+Zvf3MKF2r+y523M4mR/BHYHIdmN0ny6h01E9XX99M1wXssI8cnLwA3/2Hs1FjJ0RbjvmdY6Qt/lzvDb7umf/8ZzyJ2eFIHU3DBCBeKFiXXBKJr1M9AR0F9bUzVkJgnjLYKYFDZ9nEIJpocKGpPZvAXdbD2KveWCSWZdOjm7z6QvfmL+QxmO2EJONG8WyMsRTl8zpXjeGQrLknnxQ9ybSWNfPLCezFGJ4+Iwa6PLj+2EJFoRjOAVER1Cp3NuoK1nEXX3KhnEicV9CB0eqxQKFWdUT3XShBa89VjjItj6OMP4VO0i6doUkuRNL/oZfYX6WZbetG/LkpfN4mWeaZ54AvYSnUXKD3vgOn5e+OmkozHb0kH9a/zIOsH8M25ANe0ceVtog+LYafG5Nmn1ZTOfoB/DUKfnk3uOK/oXirF1Y2EK1aIy/OH7BEc+XLpSiL+XGjSVbu7nMhIq+BJnxJYmriys4H34dIWXQb+KsdnE7cV57CkQ==
*/
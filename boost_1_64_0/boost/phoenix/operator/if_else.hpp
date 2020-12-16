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
84ssFse1mBpJW8O+XJ8/CKd2GsCbnvz/qX1PPtoetA52fSJja+9VZGxOiRZznR5mIc+fE3fDS3liXPsHp47pdEmd2mzogkqKS/aVBPDYa8SGq8S/TQO90GkBPYKBamHepoVWaJd+upLxEqs9m5MwrI62EbnVVuTVRVLEKb7Q0PyqN3vRr3j1SOTGoJMMl3Ee2qI3opu4JM8F9ZiTvFkK7T0ycJmqeRjX7O/VTZtqa9oZm8Tady5pyw7XOqG/1nI5t3UJQAodpAudRNj7yVPDkVRd+rXS+INpKfWoeLpWYJzrGPDnt7/9sj+W/Acw5MOTtTn/+ueyzeij8XWJDpAv485x/54pYU86jmUrC2teoEHwqFN5cAyAmEKncgGBklGBsP4FhrAGIGgrVyRSjMkrd/SRZ/wsJSZXKziXpKuginMd1KKNDOfpO/u06J6UcI5UcA5JRyHOxipz+EoJQ4KWslem41+SGBDFfkgDGeu0gLz3OwayLY2EM2VtjIRpNcb/aMraV3NBka38PM3mXzF76WtyfW81r5Xf4e9EP4sc+0l4M4u1L3EXynLDeUimcwGHzaLXbeeRSefNCVAVabyHwj57NO2+HuS3y9pRvdbGwrboXDXg7bYdqp3d3EZH+f9omV5KOzdtlHZWULwSNymJAHnxwCbbHASaz667l+UDdgyPryJxR/rPWABhNnzgVGLFmsTdbRM8FE+bGTqM2oq/EExt82Z4sls0zwIze4ER1MPbpkfJZxveAYx9p+FWoTPnksHbUkfSsXDOkbboV9MTo19NV+bjW+dbBuw4JxKwRz9nApACixVhL805BDpGtf92an9iz5gXxRIPdgjDKAbtsKzEuG7WS7bJd2wLNwtNjfTYZl+ZcCjVPePWrEqPDUT38wzC1JeHOVhC7Wp9CZHbtQTV7X6Xw0mCPI6Dx6TS3v2DdCVptu6/XlUSFh3U+qsU17WVgW2tMD99hNY7h1d01GiIeSkhTlQQjzASFtSD7BrK6kea0dbPKk9k+cPwID77SmyD192wBF8VT/VYzTlUV77B1mfrNnDluNKs60vEULJBqBcisN+myZf/CHdK+sdQhHJc4FQx7ACtE2xzKFZcfx88WDhN1dBm2DpkrMIpn4Opklm6SYrEM2lWfPIj2fjGCqDTNaDv2AC99RwD+hOWHcbnEL25L2PDwB+rGWaS1P1IEi9rsDM0WKcN7FIFdgFddJCJZUbYU7YoAcIAWU5L52g4b9l6bTLDiZZTLxfd0SviRNkk/PqQdYWU8akyGXL6L4+Ly7O7rrIYnzd+/A0+/f//83k/yE8Vkv/DK8W+PUlekmiEptaT1jg/eLMIK0aDaohX/S2YJvExNrPwYpGkhcbRnXCapQvSEkjC3TxRL2hWnCvFzzRzf0tqGHPzRvw/Tnt5OvHPYyxHGpE0zQALmHwG03krRdVEjbaZ/VPedhB7c+EK/mGet1FJRGKQrbwV+J3b+A3pus6UbCdItp4Aa2KaJRu00Rwv2YZItm4iC17c+cjKKcEDy40aX5fge+k6xreTw7oB/BYRFHBDqctu0wXPl4LHqoIPO9mihEQSLCb4VYuY7trqvqtv3d3PMoiLnTzeEms4xkKpOFgiICSx2DKBO7ZG8d6+KK1U8A5QWqRuBlLQItyOzc/KQ33ROU8V/4s174haOQjKH2jXc1f4MxxuZkbOnyOOB8dajnlW68m1xGlNrkwFOqzkuoE8lKmYD20QzA6xJtVajVm6FP/9M0xET5YdrytSP8uVwvG3K3hAHyFH1XOEON1gZUPiE0g6FqPK3aRK6uBn0ku28jM1esR6eiZkB6z75t/73VsfpF955P/rcu3PL+CC+ytMng4=
*/
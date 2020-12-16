/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_DOMAIN_HPP
#define BOOST_PHOENIX_CORE_DOMAIN_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/call.hpp>
#include <boost/proto/transform/when.hpp>
#include <boost/proto/domain.hpp>

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct actor;
    
    struct meta_grammar;

    struct phoenix_generator
        : proto::switch_<phoenix_generator>
    {

        BOOST_PROTO_USE_BASIC_EXPR()

        template<typename Tag>
        struct case_
            : proto::otherwise<proto::call<proto::pod_generator<actor>(proto::_)> >
        {};
    };

    // proto's assignment operator takes rhs by reference
    template<>
    struct phoenix_generator::case_<proto::tag::assign>
      : proto::otherwise<proto::call<proto::compose_generators<
            proto::by_value_generator
          , proto::pod_generator<actor>
        >(proto::_)> >
    {};

    // proto's subscript operator takes rhs by reference
    template<>
    struct phoenix_generator::case_<proto::tag::subscript>
      : proto::otherwise<proto::call<proto::compose_generators<
            proto::by_value_generator
          , proto::pod_generator<actor>
        >(proto::_)> >
    {};

    struct phoenix_default_domain
        : proto::domain<
           proto::basic_default_generator
         , proto::_
         , proto::basic_default_domain
        >
    {
        template <typename T>
        struct as_child
        //: proto_base_domain::as_expr<T> // proto lambda example.
          : as_expr<T>
        {};
    };

    struct phoenix_domain
        : proto::domain<
            phoenix_generator
          , meta_grammar
          , proto::basic_default_domain
        >
    {
        template <typename T>
        struct as_child
        //: proto_base_domain::as_expr<T> // proto lambda example.
          : as_expr<T>
        {};
    };
}}

#endif

/* domain.hpp
LtLOHtteE485TxF/kBiOrFi/E+0jGD9JPkfP7C6fh8NGlutJOv9lX/yMMSxRxDCSz9phPTtguSyD9UhXaTP2LuiK/W+NItoZaTurJ9+7/wzWjElearl/PAXPtwHmKOR8ooHFG+t2kyLOErtVZIULHnOLIl6p5gn2qaIo2D63KuI7o7RrIcuHYHnutI/X0h59v82I4y7YRGIf9hvug3W0C+ZZxJZs3f0tlgtYF2KVD3aV+1Z8qYgviNU91Ksjng+sBLEWlT7pielSoP8Rc/ut+VvyfWgF3iGXlho6IhVj36OIUSRdr/ZTr2EMqVBmJF2caZ3cB3K/IvzpMcd8MBaPeQDaJynr5ztWyHfhDsJ8kFj9NTHbMYbDiogieXlS5nF7zAtYU2J3w6vJtRmw4cRe/7xazs+OQN0SO/eh2wm0o4poTvIy/saVBRjDMXtfkfYqYaYn2g9yrlhAN1cUJ+Vco4BuruENNp/YyPJlamC7BvuKmPukiwWxDZ6C9kLsfEev/tjmT8M8i1jXKh/jOG8FG0GsU7gfHjMTbBqx7iO2lMX2eQbaNbHiEUPxHtacrog3xB72u18A+9hZRYw2SFsQMqsLtpfz2vi+bXhsDB7zAsyFiZniBt3HegfrQ+z7zVV+lu9nKWIfsYwfikzAOgIrSvLyWdcWv2O5XLbfx0l7+8ULFzwfmDdJt+JgShqWWQb0aWKPKs3OwBiuKiKO2Phxd1ZhPq8p4jYxQ7UAuTfTDUU8pfFdniufXf8Ec1OS7tDrba2w3m/an3NJS7uRcgvT3ZT3QB66e6A0MLM0zT2QuCXbtYf+uQWYH7Hz5uvY/yxgvtI090c2sCrSNPdHSWDVpGnuj9LB4F90mO7+yPSzvA/w0N0fJYAFS9PcH6WDtZamuT8y34aylqa5B0oAiyY2eklhK5bZHbgvJnbxuk8o5hOsojTNvZNVZ/LeCc4HJstae++UDBYgTXPvlA3WTJrm3snyi7w/8tDdHyWAeUjTvgcPJstFe3+UCVZammbfZXE3bzMxZgErLk277zJjCWCe0jT7LieC+UjT7LucTE2373I62G5aZm3D92A/ugf3VcSGLjkJWct9b0YRWcTmn+yzH+N7oIgJxF6cipXvJYDR/nDr3MkteMyHsN5jkNYnqeIf2Mey4FpM7PLKqbPxmL/CPJkcM2Bd6N9YLo8UsZmka/5ZmSJYLtkw11CkzVxulO8SP5X3cR66+zgbWHNiA1oE9scyAwsh5v1X8FKM75m8l/HQ3/8xZmbMwpiVsWjGbIwlMJbIWBJjyYylMZbOWCZj2YyJ3/M2b7AzRjJ+Lt0q2yBs39GOpGt99Stc+7U8V8RndBycGSXbxAtFKKQNlj07Q353ACamYSRdvXdXRGA+XyuitisZsyoUrY91BB+GGE3StY9e1xLP52oUI4jNmiiy8XxgS0hfaXsmZQeau1GM8pC24L19btg+YdH0KUk3IP2WBdMVN4o4Ol43vlsc05Uwio2kPL9//eGnWO9ljOISOeaFs79uxxjKG8U4YqcOjZf7OlQwiufEzvROxPVkm8kI97DS4juHyt8qVDaKLSQvhueZa7A8/Y1iLUl3ZdWqDfLZmVFkkXQHoo6FY7oAo5jjSaxs1xXY5uHn/GPIMb/23TYIj9nMCO9YS/t82sPJaLCpw3w1nbt9DX6vVb4faTHC8xxpi1MnLcW+Aht1dnCT9v2Ft7dgXsKNwkWRVrtAKs7PLB2M4rSQdv6oC8Zu7WgUbxOrsDtTvssPVoLk5dbY6oew/qxGsYtYsN+pj+V6uRH7kRtYxX59XmLsYKWJZTyt9BGeD6wZsdC3/XB+LboaYX4t7fKfQxKxzMDiDdKG3/k=
*/
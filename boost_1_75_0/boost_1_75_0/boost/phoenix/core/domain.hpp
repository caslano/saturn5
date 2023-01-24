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
OjutwkAtNCkaCLU6apQiGqU0SgBnvY19JVQmxn2yqFZeMg9zTxSdLR8KSSh9toO5RHYAguchdptridPRheVb0Nbtk/HQq406oYu0YIcM9YhR9SpSa1tFsE9THxHoZynF14siTqEYQvdTWTBoV0pxnHQpokJpJ4GlWzs0WBm3rQrAxeEB0cqAZ2qCHrGRnqahTQd6O3gNIjVXDNOmIk6FxT0Q8agDH+Ki88oAAmOhw7rCoKB9TxCUZwaU5wXoOk81RaXPc9DiQR8Ap+2QF32iR1JwFx7RKWgfp10Kg1Rm9Dg1bliS2HBvnXiauxZ4nYIXw9XgTLrFo0YY8vxMUScGSP4i4iAwqJIO4iV2Gi4gVXD3EBdQu8lS4iSriQ1imwkpLwfYDBQ/XAKBNTpwzYKwi6ZcAHgrhFYQxjcLcBbXTGohvnUIEqpAI9TBCVrZgNshSagcrIR60gKxWJYWoHVAvJ9Uk1X4zv/UoclgMaiDl5DJQ0vbSDkxbvApG0DbJnXKksGmVKUpV9diJWmDuwC8DuD2QuhUCNmBt59cpw5VgiptrTqt2iZuMh9CNtJJ5TB6JS2THzCUF6LVzO5b2hJaK06wdffAciYPTk6IlFMHlxJtaBf7kU9KOzZ02l72HhWaT8Uxrh7SwABHYb8tZnRfnCqeGQ0A/bSfHVH7mDy09OpyKCnV/mUF9E8vTe2VbFcWmnMW5WmnfkKxmSqH
*/
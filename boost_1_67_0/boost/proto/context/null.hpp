///////////////////////////////////////////////////////////////////////////////
/// \file null.hpp
/// Definintion of null_context\<\>, an evaluation context for
/// proto::eval() that simply evaluates each child expression, doesn't
/// combine the results at all, and returns void.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_CONTEXT_NULL_HPP_EAN_06_24_2007
#define BOOST_PROTO_CONTEXT_NULL_HPP_EAN_06_24_2007

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/eval.hpp>
#include <boost/proto/traits.hpp>

namespace boost { namespace proto { namespace context
{

    template<
        typename Expr
      , typename Context
      , long Arity          // = Expr::proto_arity_c
    >
    struct null_eval
    {};

    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 0>
    {
        typedef void result_type;
        void operator()(Expr &, Context &) const
        {}
    };

    // Additional specializations generated by the preprocessor
    #include <boost/proto/context/detail/null_eval.hpp>

    /// null_context
    ///
    struct null_context
    {
        /// null_context::eval
        ///
        template<typename Expr, typename ThisContext = null_context const>
        struct eval
          : null_eval<Expr, ThisContext>
        {};
    };

}}}

#endif

/* null.hpp
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
*/
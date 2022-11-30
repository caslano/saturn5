/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_LET_HPP
#define BOOST_PHOENIX_SCOPE_LET_HPP

//#include <boost/assert.hpp>
//#include <sstream>
#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>
#include <boost/phoenix/scope/local_variable.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/phoenix/support/vector.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(let_)
  , (proto::terminal<proto::_>) // Locals
    (proto::terminal<proto::_>) // Map
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct let_eval
    {
          template <typename Sig>
          struct result;

          template <typename This, typename Vars, typename Map, typename Expr, typename Context>
          struct result<This(Vars, Map, Expr, Context)>
          {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;
            typedef
                typename proto::detail::uncvref<
                    typename result_of::actions<Context>::type
                >::type
                actions_type;
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<Vars>::type
                     >::type
                     vars_type;
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<Map>::type
                     >::type
                     map_type;

            typedef
                typename proto::detail::uncvref<Expr>::type
                     expr_type;
            
            typedef typename
                detail::result_of::initialize_locals<
                    vars_type
                  , Context
                >::type
            locals_type;

            typedef typename
                result_of::eval<
                    expr_type
                  , typename result_of::context<
                        scoped_environment<
                            env_type
                          , env_type
                          , locals_type
                          , map_type
                        >
                      , actions_type
                    >::type
                >::type
                type;
          };

        template <typename Vars, typename Map, typename Expr, typename Context>
        typename result<let_eval(Vars const&, Map const&, Expr const &, Context const &)>::type const
        operator()(Vars const & vars, Map, Expr const & expr, Context const & ctx) const
        {
            Vars vars_(vars);

            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<Vars>::type
                >::type
                vars_type;
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<Map>::type
                >::type
                map_type;
            
            typedef typename 
                detail::result_of::initialize_locals<
                    vars_type
                  , Context
                >::type
            locals_type;

            locals_type locals = initialize_locals(proto::value(vars_), ctx);

            //typedef typename result<let_eval(Vars const&, Map const&, Expr const &, Context const &)>::type result_type;

            scoped_environment<
                env_type
              , env_type
              , locals_type
              , map_type
            >
            env(phoenix::env(ctx), phoenix::env(ctx), locals);

            // Fix for bugs (trial)
            // The idea is to do something which will not be optimised away.
            //int vsize = boost::fusion::size(vars);
            //std::stringstream strm;
            //strm << vsize << std::endl;
            //int size = strm.str().length();
            //BOOST_ASSERT(size >= 0);
            return eval(expr, phoenix::context(env, phoenix::actions(ctx)));
            // typedef is_value<result_type> is_val;
            //if(is_val::value) This seems always to be true
            //{
            //   std::cout << "let result has value type" << std::endl;
            // }
            //if (is_val(r) ) std::cout << "let returns val" << std::endl;
            //std::cout << "result is " << r << std::endl;
            //return r;
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::let_, Dummy>
        : call<let_eval, Dummy>
    {};

    template <typename Locals, typename Map>
    struct let_actor_gen
    {
        let_actor_gen(Locals const & locals_)
            : locals(locals_)
        {}

        let_actor_gen(let_actor_gen const & o)
            : locals(o.locals)
        {}

        template <typename Expr>
        typename expression::let_<
            Locals
          , Map
          , Expr
        >::type const
        operator[](Expr const & expr) const
        {
           typedef typename expression::let_<
              Locals
            , Map
            , Expr
           >::type let_type;
           //typedef is_value<let_type> is_val;

           let_type let_exp = expression::let_<Locals, Map, Expr>::make(locals, Map(), expr);
           //if(is_val::value) //This seems always to be true
           //{
           //  std::cout << "let has value type" << std::endl;
           //}
           return let_exp;
        }

        Locals locals;
    };

#define BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME let_actor_gen
#define BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION let
#define BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST
#if defined(BOOST_PHOENIX_NO_VARIADIC_SCOPE)
    #include <boost/phoenix/scope/detail/cpp03/local_gen.hpp>
#else
    #include <boost/phoenix/scope/detail/local_gen.hpp>
#endif
#undef BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME
#undef BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION
#undef BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST

    template <typename Dummy>
    struct is_nullary::when<rule::let_, Dummy>
        : proto::make<
            mpl::and_<
                proto::fold<
                    proto::call<proto::_value(proto::_child_c<0>)>
                  , proto::make<mpl::true_()>
                  , proto::make<
                        mpl::and_<
                            proto::_state
                          , proto::call<
                                evaluator(
                                    proto::_
                                  , _context
                                  , proto::make<proto::empty_env()>
                                )
                            >
                        >()
                    >
                >
              , evaluator(
                    proto::_child_c<2>
                  , proto::call<
                        functional::context(
                            proto::make<
                                mpl::true_()
                            >
                          , proto::make<
                                detail::scope_is_nullary_actions()
                            >
                        )
                    >
                  , proto::make<
                        proto::empty_env()
                    >
                )
            >()
        >
    {};
}}

#endif

/* let.hpp
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
*/
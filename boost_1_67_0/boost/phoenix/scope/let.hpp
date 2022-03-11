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
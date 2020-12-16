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
ny8fQMNiB9Dl9SFcmXhZfD8eQit0gXMlLy1nsX7USXgEzpd0ei6M+kiwHL2oQN0Xt6/DroPRGK2VmZCUV0+C6Tn5HnoQ8pEdGV2IjNLQ8ui/lCZoP5zpeILuWtgNopdIRWY5i6Hjoi+hBgZdgjrR4qq7+pZpKV2ZfSWRp2OdrIJhTmmfHC2VlQ6/FMZR/mkARJWlABlnNB5Be65ePnkaCST1RGtHQorb3BFtZcuPj986k/CiH9kowXefrfPgs3Jp9Q8DRigSImLY6xuvGgvwUZ3xZHq/S488yeIjtNy1l9JK/4tGQqMZGt7pwcN4CUjYXVKnjQQ3aE+PaUtHOVQlnTOPOg+ZPMoh4WAefrtDDi81HGa1QYN2/mfSOXR06exeXbaSUUh6LI8Koab+YtxHMDR8OYGh8wMPygeM7zEz4WUIPx5YNI1PcojQuXrqYgHjcH96rPIzB1lvSVvUk6nWBhW3eAwpV4YHfYmnworosolcPCgm25kBPLgVzgB1qlRnxbGTKsKQEeu0VjKID3ZbHFoZnssZV0ycUPTlEEOgLJgeSRg6DAxKZsz9Uaw+cdnN+dJJSfEZHBW4HKDvUXs6pHDXOdWy/Hj25MvHOcDlcCsvm16KPbLRSobJ05Kp+EYzi/UctLTl+cnpnWBetNjcUWTmy8t9qCtovOp3fMmpNR5a1YT5xicrWM6IV+jdiwFuOmlQ/POX2zxVOmT2F0TPv9vmptNYCnUwPSfdRS9LRrIgHEjrn/86Dyd6OeplZ0KEf3quhEaOE/jhy0/Xafgyvhf+3I7KDqBPcRc62ScpR+eXNKHnGiJhTgqZF5+WxHZIYO3V+dBc0EvPYgS25jq99M9+tBHVDen47kmMl0bqn4uGByVu3MDzT0zH3zKZ6tsdfbjhPWOt83T1PMUeJ2hZ0p9eeh4PD/oAN5NH08bjDH9a7nF8aEXHQTLrvYwPfTmdS+/ipeGs45LhSyO9CcY8vHHG3asomtXroilbFm3ZeCIzmZiYFNrgauSm4fGcoqmkChl8ijSghdJ5SCvuovO0TF46b6RCy5nvwQ9uvYVOVkmd6bSXx3RerYX50ckJQi+dtwcIjpu1FMxDegGhc0pdMI3kqUPn/YjGS6vV0+mN7Q+lBQs/HKmLgudeuOdBOdUt1BpeMvaNR69bATh6XdAVqeaPzryV10fbMBAp2mkgYajfa5CrGsTexl+JzvJtGcqn3Fmum5oadad2ba26I3sQ1HQvuqI2zXUbcZn4jIlP+B9iU1QQF3TsROV7V0bbthyt2uWnPb+9qIXp8fGZ8fa1uEllPr9Lqt4RQMIY8/0F0hxotxn7EZoAT9O4hH9TdMDYhV8l6Jvt3o/g1LTqobj6oHIdTsVc3wLaa1f8DSCNOcginwyS3xoTvwCwld78pWBZ3tSIO6zpjofh3eHh3oGdg+bOwWFzdtmoAdIYUHmx1+rNoc5h3EwzGh62f8VTlgD4bpkHIxPRGPpOQBlbx1NflVFbZWptlX3yl6IsDla5jmqy6H24tMs4ys6rR/TBDY8Y/OPzHkz2yq6aI0Eph6MnsyyePkIzKudZPKg8G42swqkeozwuN81ldKMLMKse9YQF4nq/zQvm6/2ONBhX8j4gvV5W/njCxi9MLy5Bcri/GQ3A0QtVBXoKjEtXeAV8RKogft6SU15+KTzBupq9Tii8yupEUNHh/qJD4Sj1q1B3egVPpSEIUeINDw/jrobhAb43bPSKkVH17kJLR/7yFn+FN9Q70DtqMv3g5Sbj99h48u6y35eHFZ9h291t80c4vxHO793iP8Lvnb0Dik65h+Fm/x6bD8XH8sq7y34Lv2Hl5viYj/0WeTi+bvDZTe8r1Hs=
*/
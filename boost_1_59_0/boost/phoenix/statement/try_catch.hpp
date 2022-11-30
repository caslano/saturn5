/*==============================================================================
    Copyright (c) 2005-2007 Dan Marsden
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_STATEMENT_TRY_CATCH_HPP
#define BOOST_PHOENIX_STATEMENT_TRY_CATCH_HPP

#include <boost/phoenix/config.hpp>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/scope/local_variable.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>
#include <boost/proto/functional/fusion/pop_front.hpp>
#include <boost/core/enable_if.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct try_catch_actor;

    template <typename Exception>
    struct catch_exception
    {
        typedef Exception type;
    };

    namespace tag
    {
        struct try_catch {};
        struct catch_ {};
        struct catch_all {};
    }

    namespace expression
    {
        template <
            typename Try
          , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_CATCH_LIMIT)
          , typename Dummy = void
        >
        struct try_catch;

        // bring in the expression definitions
        #include <boost/phoenix/statement/detail/try_catch_expression.hpp>

        template <typename A0, typename A1, typename A2 = void>
        struct catch_
            : proto::nary_expr<tag::catch_, A0, A1, A2>
        {};

        template <typename A0, typename A1>
        struct catch_<A0, A1, void>
            : proto::binary_expr<tag::catch_, A0, A1>
        {};
        
        template <typename A0>
        struct catch_all
            : proto::unary_expr<tag::catch_all, A0>
        {};
    }

    namespace rule
    {
        typedef
            expression::catch_<
                proto::terminal<catch_exception<proto::_> >
              , local_variable
              , meta_grammar
            >
        captured_catch;

        typedef
            expression::catch_<
                proto::terminal<catch_exception<proto::_> >
              , meta_grammar
            >
        non_captured_catch;

        struct catch_
            : proto::or_<
                captured_catch
              , non_captured_catch
            >
        {};
        
        struct catch_all
            : expression::catch_all<
                meta_grammar
            >
        {};

        struct try_catch
            : proto::or_<
                expression::try_catch<
                     meta_grammar
                   , proto::vararg<rule::catch_>
                >
              , expression::try_catch<
                     meta_grammar
                   , rule::catch_all
                >
              , expression::try_catch<
                     meta_grammar
                   , proto::vararg<rule::catch_>
                   , rule::catch_all
                >
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<tag::try_catch, Dummy>
        : enable_rule<rule::try_catch, Dummy>
    {};

    struct try_catch_eval
    {
        typedef void result_type;

        template <typename Try, typename Context>
        void operator()(Try const &, Context const &) const
        {}

        template <typename Catch, typename Exception, typename Context>
        typename enable_if<proto::matches<Catch, rule::non_captured_catch> >::type
        eval_catch_body(Catch const &c, Exception & /*unused*/, Context const &ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            phoenix::eval(proto::child_c<1>(c), ctx);
        }

        template <typename Catch, typename Exception, typename Context>
        typename enable_if<proto::matches<Catch, rule::captured_catch> >::type
        eval_catch_body(Catch const &c, Exception &e, Context const &ctx) const
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        typename proto::result_of::child_c<Catch, 1>::type
                    >::type
                >::type
            capture_type;
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
            env_type;
            typedef vector1<Exception &> local_type;
            typedef detail::map_local_index_to_tuple<capture_type> map_type;

            typedef
                phoenix::scoped_environment<
                    env_type
                  , env_type
                  , local_type
                  , map_type
                >
            scoped_env_tpe;

            local_type local = {e};

            scoped_env_tpe env(phoenix::env(ctx), phoenix::env(ctx), local);

            phoenix::eval(proto::child_c<2>(c), phoenix::context(env, phoenix::actions(ctx)));
        }

        // bring in the operator overloads
        #include <boost/phoenix/statement/detail/try_catch_eval.hpp>
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::try_catch, Dummy>
        : call<try_catch_eval, Dummy>
    {};

    namespace detail
    {
        struct try_catch_is_nullary
            : proto::or_<
                proto::when<
                    phoenix::rule::catch_all
                  , proto::call<
                        evaluator(
                            proto::_child_c<0>
                          , proto::_data
                          , proto::make<proto::empty_env()>
                        )
                    >
                >
              , proto::when<
                    phoenix::rule::catch_
                  , proto::or_<
                        proto::when<
                            phoenix::rule::captured_catch
                          , proto::call<
                                evaluator(
                                    proto::_child_c<2>
                                  , proto::call<
                                        phoenix::functional::context(
                                            proto::make<mpl::true_()>
                                          , proto::make<detail::scope_is_nullary_actions()>
                                        )
                                    >
                                  , proto::make<proto::empty_env()>
                                )
                            >
                        >
                      , proto::otherwise<
                            proto::call<
                                evaluator(
                                    proto::_child_c<1>
                                  , proto::_data
                                  , proto::make<proto::empty_env()>
                                )
                            >
                        >
                    >
                >
              , proto::when<
                    phoenix::rule::try_catch
                  , proto::make<
                        mpl::and_<
                            proto::call<
                                evaluator(
                                    proto::_child_c<0>
                                  , proto::_data
                                  , proto::make<proto::empty_env()>
                                )
                            >
                          , proto::fold<
                                proto::call<
                                    proto::functional::pop_front(proto::_)
                                >
                              , proto::make<mpl::true_()>
                              , proto::make<
                                    mpl::and_<
                                        proto::_state
                                      , proto::call<
                                            try_catch_is_nullary(
                                                proto::_
                                              , proto::make<proto::empty_env()>
                                              , proto::_data
                                            )
                                        >
                                    >()
                                >
                            >
                        >()
                    >
                >
            >
        {};

        template <
            typename TryCatch
          , typename Exception
          , typename Capture
          , typename Expr
          , long Arity = proto::arity_of<TryCatch>::value
        >
        struct catch_push_back;

        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 1>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;

            typedef
                phoenix::expression::try_catch<
                    TryCatch
                  , catch_expr
                >
                gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const & try_catch, Capture const & capture, Expr const & catch_)
            {
                return
                    gen_type::make(
                        try_catch
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };

        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 1>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            
            typedef
                phoenix::expression::try_catch<
                    TryCatch
                  , catch_expr
                >
                gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const & try_catch, Expr const & catch_)
            {
                return
                    gen_type::make(
                        try_catch
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        
        template <
            typename TryCatch
          , typename Expr
          , long Arity = proto::arity_of<TryCatch>::value
        >
        struct catch_all_push_back;

        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 1>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            
            typedef
                phoenix::expression::try_catch<
                    TryCatch
                  , catch_expr
                >
                gen_type;
            typedef typename gen_type::type type;

            static type make(TryCatch const& try_catch, Expr const& catch_)
            {
                return
                    gen_type::make(
                        try_catch
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
        #include <boost/phoenix/statement/detail/catch_push_back.hpp>
    }

    template <typename Dummy>
    struct is_nullary::when<rule::try_catch, Dummy>
        : proto::call<
            detail::try_catch_is_nullary(
                proto::_
              , proto::make<proto::empty_env()>
              , _context
            )
        >
    {};

    template <typename TryCatch, typename Exception, typename Capture = void>
    struct catch_gen
    {
        catch_gen(TryCatch const& try_catch_, Capture const& capture)
            : try_catch(try_catch_)
            , capture(capture) {}

        template <typename Expr>
        typename boost::disable_if<
            proto::matches<
                typename proto::result_of::child_c<
                    TryCatch
                  , proto::arity_of<TryCatch>::value - 1
                >::type
              , rule::catch_all
            >
          , typename detail::catch_push_back<TryCatch, Exception, Capture, Expr>::type
        >::type
        operator[](Expr const& expr) const
        {
            return
                detail::catch_push_back<TryCatch, Exception, Capture, Expr>::make(
                    try_catch, capture, expr
                );
        }

        TryCatch try_catch;
        Capture capture;
    };

    template <typename TryCatch, typename Exception>
    struct catch_gen<TryCatch, Exception, void>
    {
        catch_gen(TryCatch const& try_catch_) : try_catch(try_catch_) {}

        template <typename Expr>
        typename boost::disable_if<
            proto::matches<
                typename proto::result_of::child_c<
                    TryCatch
                  , proto::arity_of<TryCatch>::value - 1
                >::type
              , rule::catch_all
            >
          , typename detail::catch_push_back<TryCatch, Exception, void, Expr>::type
        >::type
        operator[](Expr const& expr) const
        {
            return
                detail::catch_push_back<TryCatch, Exception, void, Expr>::make(
                    try_catch, expr
                );
        }

        TryCatch try_catch;
    };

    template <typename TryCatch>
    struct catch_all_gen
    {
        catch_all_gen(TryCatch const& try_catch_) : try_catch(try_catch_) {}

        template <typename Expr>
        typename boost::disable_if<
            proto::matches<
                typename proto::result_of::child_c<
                    TryCatch
                  , proto::arity_of<TryCatch>::value - 1
                >::type
              , rule::catch_all
            >
          , typename detail::catch_all_push_back<TryCatch, Expr>::type
        >::type
        operator[](Expr const& expr) const
        {
            return detail::catch_all_push_back<TryCatch, Expr>::make(
                try_catch, expr
            );
        }

        TryCatch try_catch;
    };

    template <
        typename Expr
    >
    struct try_catch_actor;

    template <typename Expr>
    struct try_catch_actor
        : actor<Expr>
    {
        typedef actor<Expr> base_type;

        try_catch_actor(base_type const& expr)
            : base_type(expr)
            , catch_all(*this)
        {
        }

        template <typename Exception>
        catch_gen<base_type, Exception> const
        catch_() const
        {
            return catch_gen<base_type, Exception>(*this);
        }

        template <typename Exception, typename Capture>
        catch_gen<base_type, Exception, Capture> const
        catch_(Capture const &expr) const
        {
            return catch_gen<base_type, Exception, Capture>(*this, expr);
        }

        catch_all_gen<base_type> const catch_all;
    };

    template <typename Expr>
    struct is_actor<try_catch_actor<Expr> >
        : mpl::true_
    {};

    struct try_gen
    {
        template <typename Try>
        typename expression::try_catch<Try>::type const
        operator[](Try const & try_) const
        {
            return expression::try_catch<Try>::make(try_);
        }
    };

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
    try_gen const try_ = {};
#endif
}}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* try_catch.hpp
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
*/
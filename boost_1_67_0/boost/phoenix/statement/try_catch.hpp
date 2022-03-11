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
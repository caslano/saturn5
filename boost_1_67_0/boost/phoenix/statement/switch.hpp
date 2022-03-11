/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_SWITCH_HPP
#define BOOST_PHOENIX_STATEMENT_SWITCH_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/fusion.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4065) // switch statement contains 'default' but no 'case' labels
#endif

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(switch_case)
  , (proto::terminal<proto::_>)
    (meta_grammar)
)

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(switch_default_case)
  , (meta_grammar)
)

namespace boost { namespace phoenix
{
    namespace detail
    {
        struct switch_case_grammar;
        struct switch_case_with_default_grammar;
        struct switch_grammar
            : proto::or_<
                proto::when<
                    detail::switch_case_grammar
                  , mpl::false_()
                >
              , proto::when<
                    detail::switch_case_with_default_grammar
                  , mpl::true_()
                >
            >
        {};
    }

    namespace detail
    {
        struct switch_case_is_nullary
            : proto::or_<
                proto::when<
                    proto::comma<
                        switch_case_is_nullary
                      , proto::or_<phoenix::rule::switch_default_case, phoenix::rule::switch_case>
                    >
                  , mpl::and_<
                        switch_case_is_nullary(
                            proto::_child_c<0>
                          , proto::_state
                        )
                      , switch_case_is_nullary(
                            proto::_child_c<1>
                          , proto::_state
                        )
                    >()
                >
              , proto::when<
                    proto::or_<phoenix::rule::switch_default_case, phoenix::rule::switch_case>
                  , evaluator(proto::_child_c<0>, proto::_state)
                >
            >
        {};

        struct switch_case_grammar
            : proto::or_<
                proto::comma<switch_case_grammar, phoenix::rule::switch_case>
              , proto::when<phoenix::rule::switch_case, proto::_>
            >
        {};

        struct switch_case_with_default_grammar
            : proto::or_<
                proto::comma<switch_case_grammar, phoenix::rule::switch_default_case>
              , proto::when<phoenix::rule::switch_default_case, proto::_>
            >
        {};

        struct switch_size
            : proto::or_<
                proto::when<
                    proto::comma<switch_size, proto::_>
                  , mpl::next<switch_size(proto::_left)>()
                >
              , proto::when<proto::_, mpl::int_<1>()>
            >
        {};
    }
}}

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(switch_)
  , (meta_grammar)           // Cond
    (detail::switch_grammar) // Cases
)

namespace boost { namespace phoenix {

    template <typename Dummy>
    struct is_nullary::when<rule::switch_, Dummy>
        : proto::and_<
            evaluator(proto::_child_c<0>, _context)
          , detail::switch_case_is_nullary(proto::_child_c<1>, _context)
        >
    {};

    struct switch_eval
    {
        typedef void result_type;
        
        template <typename Context>
        result_type
        operator()(Context const &) const
        {
        }

        template <typename Cond, typename Cases, typename Context>
        result_type
        operator()(Cond const & cond, Cases const & cases, Context const & ctx) const
        {
            this->evaluate(
                    ctx
                  , cond
                  , cases
                  , typename detail::switch_size::impl<Cases, int, proto::empty_env>::result_type()
                  , typename detail::switch_grammar::impl<Cases, int, proto::empty_env>::result_type()
                );
        }

        private:
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<1>
              , mpl::false_
            ) const
            {
                typedef
                    typename proto::result_of::value<
                        typename proto::result_of::child_c<
                            Cases
                          , 0
                        >::type
                    >::type
                    case_label;

                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label::value:
                        boost::phoenix::eval(proto::child_c<1>(cases), ctx);
                }
            }
            
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<1>
              , mpl::true_
            ) const
            {
                switch(boost::phoenix::eval(cond, ctx))
                {
                    default:
                        boost::phoenix::eval(proto::child_c<0>(cases), ctx);
                }
            }

            // Bring in the evaluation functions
            #include <boost/phoenix/statement/detail/switch.hpp>
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::switch_, Dummy>
        : call<switch_eval>
    {};

    template <int N, typename A>
    inline
    typename proto::result_of::make_expr<
        tag::switch_case
      , proto::basic_default_domain
      , mpl::int_<N>
      , A
    >::type const
    case_(A const & a)
    {
        return
            proto::make_expr<
                tag::switch_case
              , proto::basic_default_domain
            >(
                mpl::int_<N>()
              , a
            );
    }

    template <typename A>
    inline
    typename proto::result_of::make_expr<
        tag::switch_default_case
      , proto::basic_default_domain
      , A
    >::type const
    default_(A const& a)
    {
        return
            proto::make_expr<
                tag::switch_default_case
              , proto::basic_default_domain
            >(a);
    }

    template <typename Cond>
    struct switch_gen
    {
        switch_gen(Cond const& cond_) : cond(cond_) {}

        template <typename Cases>
        typename expression::switch_<
            Cond
          , Cases
        >::type
        operator[](Cases const& cases) const
        {
            return
                this->generate(
                    cases
                  , proto::matches<Cases, detail::switch_grammar>()
                );
        }

        private:
            Cond const& cond;

            template <typename Cases>
            typename expression::switch_<
                Cond
              , Cases
            >::type
            generate(Cases const & cases, mpl::true_) const
            {
                return expression::switch_<Cond, Cases>::make(cond, cases);
            }
            
            template <typename Cases>
            typename expression::switch_<
                Cond
              , Cases
            >::type
            generate(Cases const &, mpl::false_) const
            {
                BOOST_MPL_ASSERT_MSG(
                    false
                  , INVALID_SWITCH_CASE_STATEMENT
                  , (Cases)
                );
            }
    };

    template <typename Cond>
    inline
    switch_gen<Cond> const
    switch_(Cond const& cond)
    {
        return switch_gen<Cond>(cond);
    }

}}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif


/* switch.hpp
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
*/
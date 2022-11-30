/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_LAZY_MARCH_27_2007_1002AM)
#define BOOST_SPIRIT_LAZY_MARCH_27_2007_1002AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/lazy.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/tags.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct actor;
}}

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <typename Eval>
    struct use_terminal<qi::domain, phoenix::actor<Eval> >  // enables phoenix actors
        : mpl::true_ {};

    // forward declaration
    template <typename Terminal, typename Actor, int Arity>
    struct lazy_terminal;
}}

namespace boost { namespace spirit { namespace qi
{
    using spirit::lazy;
    typedef modify<qi::domain> qi_modify;

    namespace detail
    {
        template <typename Parser, typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool lazy_parse_impl(Parser const& p
          , Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr, mpl::false_)
        {
            return p.parse(first, last, context, skipper, attr);
        }

        template <typename Parser, typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool lazy_parse_impl(Parser const& p
          , Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& /*attr*/, mpl::true_)
        {
            // If DeducedAuto is false (semantic actions is present), the
            // component's attribute is unused.
            return p.parse(first, last, context, skipper, unused);
        }

        template <typename Parser, typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool lazy_parse_impl_main(Parser const& p
          , Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr)
        {
            // If DeducedAuto is true (no semantic action), we pass the parser's
            // attribute on to the component.
            typedef typename traits::has_semantic_action<Parser>::type auto_rule;
            return lazy_parse_impl(p, first, last, context, skipper, attr, auto_rule());
        }
    }

    template <typename Function, typename Modifiers>
    struct lazy_parser : parser<lazy_parser<Function, Modifiers> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename
                boost::result_of<qi_modify(tag::lazy_eval, Modifiers)>::type
            modifier;

            typedef typename
                remove_reference<
                    typename boost::result_of<Function(unused_type, Context)>::type
                >::type
            expr_type;

            // If you got an error_invalid_expression error message here,
            // then the expression (expr_type) is not a valid spirit qi
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(qi::domain, expr_type);

            typedef typename
                result_of::compile<qi::domain, expr_type, modifier>::type
            parser_type;

            typedef typename
                traits::attribute_of<parser_type, Context, Iterator>::type
            type;
        };

        lazy_parser(Function const& function_, Modifiers const& modifiers_)
          : function(function_), modifiers(modifiers_) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr) const
        {
            return detail::lazy_parse_impl_main(
                  compile<qi::domain>(function(unused, context)
                , qi_modify()(tag::lazy_eval(), modifiers))
                , first, last, context, skipper, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("lazy"
              , compile<qi::domain>(function(unused, context)
                , qi_modify()(tag::lazy_eval(), modifiers))
                    .what(context)
            );
        }

        Function function;
        Modifiers modifiers;
    };


    template <typename Function, typename Subject, typename Modifiers>
    struct lazy_directive
        : unary_parser<lazy_directive<Function, Subject, Modifiers> >
    {
        typedef Subject subject_type;

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename
                boost::result_of<qi_modify(tag::lazy_eval, Modifiers)>::type
            modifier;

            typedef typename
                remove_reference<
                    typename boost::result_of<Function(unused_type, Context)>::type
                >::type
            directive_expr_type;

            typedef typename
                proto::result_of::make_expr<
                    proto::tag::subscript
                  , directive_expr_type
                  , Subject
                >::type
            expr_type;

            // If you got an error_invalid_expression error message here,
            // then the expression (expr_type) is not a valid spirit qi
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(qi::domain, expr_type);

            typedef typename
                result_of::compile<qi::domain, expr_type, modifier>::type
            parser_type;

            typedef typename
                traits::attribute_of<parser_type, Context, Iterator>::type
            type;
        };

        lazy_directive(
            Function const& function_
          , Subject const& subject_
          , Modifiers const& modifiers_)
          : function(function_), subject(subject_), modifiers(modifiers_) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr) const
        {
            return detail::lazy_parse_impl_main(compile<qi::domain>(
                proto::make_expr<proto::tag::subscript>(
                    function(unused, context)
                  , subject)
                , qi_modify()(tag::lazy_eval(), modifiers))
                , first, last, context, skipper, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("lazy-directive"
              , compile<qi::domain>(
                    proto::make_expr<proto::tag::subscript>(
                        function(unused, context)
                      , subject
                    ), qi_modify()(tag::lazy_eval(), modifiers))
                    .what(context)
            );
        }

        Function function;
        Subject subject;
        Modifiers modifiers;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Eval, typename Modifiers>
    struct make_primitive<phoenix::actor<Eval>, Modifiers>
    {
        typedef lazy_parser<phoenix::actor<Eval>, Modifiers> result_type;
        result_type operator()(phoenix::actor<Eval> const& f
          , Modifiers const& modifiers) const
        {
            return result_type(f, modifiers);
        }
    };

    template <typename Terminal, typename Actor, int Arity, typename Modifiers>
    struct make_primitive<lazy_terminal<Terminal, Actor, Arity>, Modifiers>
    {
        typedef lazy_parser<Actor, Modifiers> result_type;
        result_type operator()(
            lazy_terminal<Terminal, Actor, Arity> const& lt
          , Modifiers const& modifiers) const
        {
            return result_type(lt.actor, modifiers);
        }
    };

    template <typename Terminal, typename Actor, int Arity, typename Subject, typename Modifiers>
    struct make_directive<lazy_terminal<Terminal, Actor, Arity>, Subject, Modifiers>
    {
        typedef lazy_directive<Actor, Subject, Modifiers> result_type;
        result_type operator()(
            lazy_terminal<Terminal, Actor, Arity> const& lt
          , Subject const& subject, Modifiers const& modifiers) const
        {
            return result_type(lt.actor, subject, modifiers);
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Actor, typename Modifiers, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<
        qi::lazy_parser<Actor, Modifiers>, Attribute, Context, Iterator>
      : handles_container<
          typename qi::lazy_parser<Actor, Modifiers>::template
              attribute<Context, Iterator>::parser_type
        , Attribute, Context, Iterator>
    {};

    template <typename Subject, typename Actor, typename Modifiers
      , typename Attribute, typename Context, typename Iterator>
    struct handles_container<
        qi::lazy_directive<Actor, Subject, Modifiers>, Attribute
      , Context, Iterator>
      : handles_container<
          typename qi::lazy_directive<Actor, Subject, Modifiers>::template
              attribute<Context, Iterator>::parser_type
        , Attribute, Context, Iterator>
    {};
}}}

#endif

/* lazy.hpp
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
*/
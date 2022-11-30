//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_LAZY_MARCH_27_2007_1231PM)
#define BOOST_SPIRIT_KARMA_LAZY_MARCH_27_2007_1231PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/lazy.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/proto/make_expr.hpp>
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
    struct use_terminal<karma::domain, phoenix::actor<Eval> >  // enables phoenix actors
        : mpl::true_ {};

    // forward declaration
    template <typename Terminal, typename Actor, int Arity>
    struct lazy_terminal;

}}

namespace boost { namespace spirit { namespace karma
{
    using spirit::lazy;
    typedef modify<karma::domain> karma_modify;

    namespace detail
    {
        template <typename Generator, typename OutputIterator, typename Context
          , typename Delimiter, typename Attribute>
        bool lazy_generate_impl(Generator const& g, OutputIterator& sink
          , Context& context, Delimiter const& delim
          , Attribute const& attr, mpl::false_)
        {
            return g.generate(sink, context, delim, attr);
        }

        template <typename Generator, typename OutputIterator, typename Context
          , typename Delimiter, typename Attribute>
        bool lazy_generate_impl(Generator const& g, OutputIterator& sink
          , Context& context, Delimiter const& delim
          , Attribute const& /* attr */, mpl::true_)
        {
            // If DeducedAuto is false (semantic actions is present), the
            // component's attribute is unused.
            return g.generate(sink, context, delim, unused);
        }

        template <typename Generator, typename OutputIterator, typename Context
          , typename Delimiter, typename Attribute>
        bool lazy_generate_impl_main(Generator const& g, OutputIterator& sink
          , Context& context, Delimiter const& delim, Attribute const& attr)
        {
            // If DeducedAuto is true (no semantic action), we pass the parser's
            // attribute on to the component.
            typedef typename traits::has_semantic_action<Generator>::type auto_rule;
            return lazy_generate_impl(g, sink, context, delim, attr, auto_rule());
        }
    }

    template <typename Function, typename Modifiers>
    struct lazy_generator : generator<lazy_generator<Function, Modifiers> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename
                boost::result_of<karma_modify(tag::lazy_eval, Modifiers)>::type
            modifier;

            typedef typename
                remove_reference<
                    typename boost::result_of<Function(unused_type, Context)>::type
                >::type
            expr_type;

            // If you got an error_invalid_expression error message here,
            // then the expression (expr_type) is not a valid spirit karma
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, expr_type);

            typedef typename
                result_of::compile<karma::domain, expr_type, modifier>::type
            generator_type;

            typedef typename
                traits::attribute_of<generator_type, Context, Iterator>::type
            type;
        };

        lazy_generator(Function const& func, Modifiers const& modifiers)
          : func(func), modifiers(modifiers) {}

        template <
            typename OutputIterator, typename Context, 
            typename Delimiter, typename Attribute
        >
        bool generate(OutputIterator& sink, Context& context, 
            Delimiter const& d, Attribute const& attr) const
        {
            return detail::lazy_generate_impl_main(
                compile<karma::domain>(func(unused, context)
              , karma_modify()(tag::lazy_eval(), modifiers))
              , sink, context, d, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("lazy"
              , compile<karma::domain>(func(unused, context)
                , karma_modify()(tag::lazy_eval(), modifiers))
                    .what(context)
            );
        }

        Function func;
        Modifiers modifiers;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(lazy_generator& operator= (lazy_generator const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Function, typename Subject, typename Modifiers>
    struct lazy_directive 
      : unary_generator<lazy_directive<Function, Subject, Modifiers> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        typedef Subject subject_type;

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename
                boost::result_of<karma_modify(tag::lazy_eval, Modifiers)>::type
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
            // then the expression (expr_type) is not a valid spirit karma
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, expr_type);

            typedef typename
                result_of::compile<karma::domain, expr_type, modifier>::type
            generator_type;

            typedef typename
                traits::attribute_of<generator_type, Context, Iterator>::type
            type;
        };

        lazy_directive(Function const& function, Subject const& subject
              , Modifiers const& modifiers)
          : function(function), subject(subject), modifiers(modifiers) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::lazy_generate_impl_main(compile<karma::domain>(
                proto::make_expr<proto::tag::subscript>(
                    function(unused, ctx), subject)
                  , karma_modify()(tag::lazy_eval(), modifiers))
                  , sink, ctx, d, attr);
        }

        template <typename Context>
        info what(Context& ctx) const
        {
            return info("lazy-directive"
              , compile<karma::domain>(
                    proto::make_expr<proto::tag::subscript>(
                        function(unused, ctx), subject)
                      , karma_modify()(tag::lazy_eval(), modifiers))
                    .what(ctx)
            );
        }

        Function function;
        Subject subject;
        Modifiers modifiers;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Eval, typename Modifiers>
    struct make_primitive<phoenix::actor<Eval>, Modifiers>
    {
        typedef lazy_generator<phoenix::actor<Eval>, Modifiers> result_type;
        result_type operator()(phoenix::actor<Eval> const& f
          , Modifiers const& modifiers) const
        {
            return result_type(f, modifiers);
        }
    };

    template <typename Terminal, typename Actor, int Arity, typename Modifiers>
    struct make_primitive<lazy_terminal<Terminal, Actor, Arity>, Modifiers>
    {
        typedef lazy_generator<Actor, Modifiers> result_type;
        result_type operator()(
            lazy_terminal<Terminal, Actor, Arity> const& lt
          , Modifiers const& modifiers) const
        {
            return result_type(lt.actor, modifiers);
        }
    };

    template <
        typename Terminal, typename Actor, int Arity, typename Subject
      , typename Modifiers>
    struct make_directive<lazy_terminal<Terminal, Actor, Arity>
      , Subject, Modifiers>
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

#endif

/* lazy.hpp
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
*/
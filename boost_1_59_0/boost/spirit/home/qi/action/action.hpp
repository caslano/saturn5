/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_QI_ACTION_ACTION_HPP
#define BOOST_SPIRIT_QI_ACTION_ACTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/context.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/action_dispatch.hpp>
#include <boost/spirit/home/support/handles_container.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace spirit { namespace qi
{
    BOOST_PP_REPEAT(SPIRIT_ARGUMENTS_LIMIT, SPIRIT_USING_ARGUMENT, _)

    template <typename Subject, typename Action>
    struct action : unary_parser<action<Subject, Action> >
    {
        typedef Subject subject_type;
        typedef Action action_type;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<Subject, Context, Iterator>
        {};

        action(Subject const& subject_, Action f_)
          : subject(subject_), f(f_) {}

#ifndef BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT
        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr_) const
        {
            typedef typename attribute<Context, Iterator>::type attr_type;

            // create an attribute if one is not supplied
            typedef traits::transform_attribute<
                Attribute, attr_type, domain> transform;

            typename transform::type attr = transform::pre(attr_);

            Iterator save = first;
            if (subject.parse(first, last, context, skipper, attr))
            {
                // call the function, passing the attribute, the context.
                // The client can return false to fail parsing.
                if (traits::action_dispatch<Subject>()(f, attr, context)) 
                {
                    // Do up-stream transformation, this integrates the results
                    // back into the original attribute value, if appropriate.
                    transform::post(attr_, attr);
                    return true;
                }

                // reset iterators if semantic action failed the match
                // retrospectively
                first = save;
            }
            return false;
        }
#else
        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr) const
        {
            Iterator save = first;
            if (subject.parse(first, last, context, skipper, attr)) // Use the attribute as-is
            {
                // call the function, passing the attribute, the context.
                // The client can return false to fail parsing.
                if (traits::action_dispatch<Subject>()(f, attr, context))
                    return true;

                // reset iterators if semantic action failed the match
                // retrospectively
                first = save;
            }
            return false;
        }

        template <typename Iterator, typename Context
          , typename Skipper>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , unused_type) const
        {
            typedef typename attribute<Context, Iterator>::type attr_type;

            // synthesize the attribute since one is not supplied
            attr_type attr = attr_type();

            Iterator save = first;
            if (subject.parse(first, last, context, skipper, attr))
            {
                // call the function, passing the attribute, the context.
                // The client can return false to fail parsing.
                if (traits::action_dispatch<Subject>()(f, attr, context))
                    return true;

                // reset iterators if semantic action failed the match
                // retrospectively
                first = save;
            }
            return false;
        }
#endif

        template <typename Context>
        info what(Context& context) const
        {
            // the action is transparent (does not add any info)
            return subject.what(context);
        }

        Subject subject;
        Action f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(action& operator= (action const&))
    };
}}}

namespace boost { namespace spirit
{
    // Qi action meta-compiler
    template <>
    struct make_component<qi::domain, tag::action>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                remove_const<typename Elements::car_type>::type
            subject_type;

            typedef typename
                remove_const<typename Elements::cdr_type::car_type>::type
            action_type;

            typedef qi::action<subject_type, action_type> type;
        };

        template <typename Elements>
        typename result<make_component(Elements, unused_type)>::type
        operator()(Elements const& elements, unused_type) const
        {
            typename result<make_component(Elements, unused_type)>::type
                result(elements.car, elements.cdr.car);
            return result;
        }
    };
}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Action>
    struct has_semantic_action<qi::action<Subject, Action> >
      : mpl::true_ {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Action, typename Attribute
        , typename Context, typename Iterator>
    struct handles_container<qi::action<Subject, Action>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* action.hpp
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
*/
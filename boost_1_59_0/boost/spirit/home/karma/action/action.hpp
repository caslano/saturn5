//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_ACTION_MAR_07_2007_0851AM)
#define BOOST_SPIRIT_KARMA_ACTION_MAR_07_2007_0851AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/context.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/action_dispatch.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    BOOST_PP_REPEAT(SPIRIT_ARGUMENTS_LIMIT, SPIRIT_USING_ARGUMENT, _)

    template <typename Subject, typename Action>
    struct action : unary_generator<action<Subject, Action> >
    {
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<Subject, Context, Iterator>
        {};

        action(Subject const& subject, Action f)
          : subject(subject), f(f) {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr_) const
        {
            typedef typename attribute<Context, unused_type>::type attr_type;

            // create a attribute if none is supplied
            // this creates a _copy_ of the attribute because the semantic
            // action will likely change parts of this
            typedef traits::transform_attribute<
                Attribute const, attr_type, domain> transform;

            attr_type attr = transform::pre(attr_);

            // call the function, passing the attribute, the context and a bool 
            // flag that the client can set to false to fail generating.
            return traits::action_dispatch<Subject>()(f, attr, ctx) && 
                   subject.generate(sink, ctx, d, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            // the action is transparent (does not add any info)
            return subject.what(context);
        }

        subject_type subject;
        Action f;
    };

}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Karma action meta-compiler
    template <>
    struct make_component<karma::domain, tag::action>
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

            typedef karma::action<subject_type, action_type> type;
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
    struct has_semantic_action<karma::action<Subject, Action> >
      : mpl::true_ {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Action, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<karma::action<Subject, Action>, Attribute
      , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* action.hpp
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
*/
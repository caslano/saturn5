//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_OPERATOR_NOT_PREDICATE_HPP
#define BOOST_SPIRIT_KARMA_OPERATOR_NOT_PREDICATE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/proto/operators.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<karma::domain, proto::tag::logical_not> // enables !g
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace karma
{
    template <typename Subject>
    struct not_predicate : unary_generator<not_predicate<Subject> >
    {
        typedef Subject subject_type;

        typedef mpl::int_<
            generator_properties::disabling | subject_type::properties::value
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        not_predicate(Subject const& subject)
          : subject(subject) {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            // inhibits output
            detail::disable_output<OutputIterator> disable(sink);
            return !subject.generate(sink, ctx, d, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("not-predicate", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::logical_not, Elements, Modifiers>
      : make_unary_composite<Elements, not_predicate> {};

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::not_predicate<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
        , typename Iterator>
    struct handles_container<karma::not_predicate<Subject>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* not_predicate.hpp
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
*/
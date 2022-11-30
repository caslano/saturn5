//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_OPERATOR_AND_PREDICATE_HPP
#define BOOST_SPIRIT_KARMA_OPERATOR_AND_PREDICATE_HPP

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
    struct use_operator<karma::domain, proto::tag::address_of> // enables &g
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace karma
{
    template <typename Subject>
    struct and_predicate : unary_generator<and_predicate<Subject> >
    {
        typedef Subject subject_type;
        typedef mpl::int_<
            generator_properties::disabling | subject_type::properties::value
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        and_predicate(Subject const& subject)
          : subject(subject) {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            // inhibits output
            detail::disable_output<OutputIterator> disable(sink);
            return subject.generate(sink, ctx, d, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("and-predicate", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::address_of, Elements, Modifiers>
      : make_unary_composite<Elements, and_predicate> {};

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::and_predicate<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::and_predicate<Subject>, Attribute
      , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* and_predicate.hpp
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
*/
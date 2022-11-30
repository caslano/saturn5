//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DIRECTIVE_BUFFER_HPP
#define BOOST_SPIRIT_KARMA_DIRECTIVE_BUFFER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::buffer> // enables buffer
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::buffer;
#endif
    using spirit::buffer_type;

    ///////////////////////////////////////////////////////////////////////////
    // buffer_directive buffers all generated output of the embedded generator
    // and flushes it only if the whole embedded generator succeeds
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct buffer_directive : unary_generator<buffer_directive<Subject> >
    {
        typedef Subject subject_type;
        typedef mpl::int_<
            subject_type::properties::value | 
            generator_properties::countingbuffer
        > properties;

        buffer_directive(Subject const& subject)
          : subject(subject) {}

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            // wrap the given output iterator to avoid output as long as the
            // embedded generator (subject) fails
            detail::enable_buffering<OutputIterator> buffering(sink);
            bool r = false;
            {
                detail::disable_counting<OutputIterator> nocounting(sink);
                r = subject.generate(sink, ctx, d, attr);
            }
            if (r) 
                buffering.buffer_copy();
            return r;
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("buffer", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::buffer, Subject, Modifiers>
    {
        typedef buffer_directive<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    // make sure buffer[buffer[...]] does not result in double buffering
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::buffer, buffer_directive<Subject>, Modifiers>
    {
        typedef buffer_directive<Subject> result_type;
        result_type operator()(unused_type
          , buffer_directive<Subject> const& subject, unused_type) const
        {
            return subject;
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::buffer_directive<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
        , typename Iterator>
    struct handles_container<karma::buffer_directive<Subject>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* buffer.hpp
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
*/
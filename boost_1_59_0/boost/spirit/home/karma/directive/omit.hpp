//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DIRECTIVE_OMIT_HPP
#define BOOST_SPIRIT_KARMA_DIRECTIVE_OMIT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::omit> // enables omit
      : mpl::true_ {};

    template <>
    struct use_directive<karma::domain, tag::skip> // enables skip
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::omit;
    using spirit::skip;
#endif
    using spirit::omit_type;
    using spirit::skip_type;

    ///////////////////////////////////////////////////////////////////////////
    // omit_directive consumes the attribute of subject generator without
    // generating anything
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, bool Execute>
    struct omit_directive : unary_generator<omit_directive<Subject, Execute> >
    {
        typedef Subject subject_type;

        typedef mpl::int_<
            generator_properties::disabling | subject_type::properties::value
        > properties;

        omit_directive(Subject const& subject)
          : subject(subject) {}

        template <typename Context, typename Iterator = unused_type>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            // We need to actually compile the output operation as we don't 
            // have any other means to verify, whether the passed attribute is 
            // compatible with the subject. 

#if defined(_MSC_VER) && _MSC_VER < 1900
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif
            // omit[] will execute the code, while skip[] doesn't execute it
            if (Execute) {
#if defined(_MSC_VER) && _MSC_VER < 1900
# pragma warning(pop)
#endif
                // wrap the given output iterator to avoid output
                detail::disable_output<OutputIterator> disable(sink);
                return subject.generate(sink, ctx, d, attr);
            }
            return true;
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info(Execute ? "omit" : "skip", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::omit, Subject, Modifiers>
    {
        typedef omit_directive<Subject, true> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    template <typename Subject, typename Modifiers>
    struct make_directive<tag::skip, Subject, Modifiers>
    {
        typedef omit_directive<Subject, false> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, bool Execute>
    struct has_semantic_action<karma::omit_directive<Subject, Execute> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, bool Execute, typename Attribute
        , typename Context, typename Iterator>
    struct handles_container<karma::omit_directive<Subject, Execute>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* omit.hpp
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
*/
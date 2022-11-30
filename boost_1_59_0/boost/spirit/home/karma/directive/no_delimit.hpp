//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_NO_DELIMIT_JAN_19_2010_0920AM)
#define BOOST_SPIRIT_KARMA_NO_DELIMIT_JAN_19_2010_0920AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/detail/unused_delimiter.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::no_delimit>   // enables no_delimit[]
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::no_delimit;
#endif
    using spirit::no_delimit_type;

    ///////////////////////////////////////////////////////////////////////////
    //  The no_delimit generator is used for no_delimit[...] directives.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct no_delimit_generator 
      : unary_generator<no_delimit_generator<Subject> >
    {
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        no_delimit_generator(Subject const& subject)
          : subject(subject) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            //  the no_delimit generator simply dispatches to the embedded 
            //  generator while supplying unused_delimiter as the new delimiter
            //  to avoid delimiting down the generator stream
            typedef detail::unused_delimiter<Delimiter> unused_delimiter;

            // the difference to verbatim[] is that this does not post-delimit
            return subject.generate(sink, ctx, unused_delimiter(d), attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("no_delimit", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::no_delimit, Subject, Modifiers>
    {
        typedef no_delimit_generator<Subject> result_type;

        result_type 
        operator()(unused_type, Subject const& subject, unused_type) const
        {
            return result_type(subject);
        }
    };

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::no_delimit_generator<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
        , typename Iterator>
    struct handles_container<karma::no_delimit_generator<Subject>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* no_delimit.hpp
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
*/
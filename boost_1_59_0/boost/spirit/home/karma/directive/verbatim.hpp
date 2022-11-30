//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_VERBATIM_MAR_02_2007_0303PM)
#define BOOST_SPIRIT_KARMA_VERBATIM_MAR_02_2007_0303PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/detail/unused_delimiter.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
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
    struct use_directive<karma::domain, tag::verbatim>   // enables verbatim[]
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::verbatim;
#endif
    using spirit::verbatim_type;

    ///////////////////////////////////////////////////////////////////////////
    //  The verbatim generator is used for verbatim[...] directives.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct verbatim_generator : unary_generator<verbatim_generator<Subject> >
    {
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        verbatim_generator(Subject const& subject)
          : subject(subject) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            //  the verbatim generator simply dispatches to the embedded 
            //  generator while supplying unused_delimiter as the new delimiter
            //  to avoid delimiting down the generator stream
            typedef detail::unused_delimiter<Delimiter> unused_delimiter;

            return subject.generate(sink, ctx, unused_delimiter(d), attr) &&
                   karma::delimit_out(sink, d);     // always do post-delimiting 
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("verbatim", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::verbatim, Subject, Modifiers>
    {
        typedef verbatim_generator<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject, unused_type) const
        {
            return result_type(subject);
        }
    };

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::verbatim_generator<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
        , typename Iterator>
    struct handles_container<karma::verbatim_generator<Subject>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* verbatim.hpp
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
*/
//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c)      2010 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DIRECTIVE_AS_HPP
#define BOOST_SPIRIT_KARMA_DIRECTIVE_AS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/detail/as.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/support/assert_msg.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>

namespace boost { namespace spirit { namespace karma
{
    template <typename T>
    struct as
      : stateful_tag_type<T, tag::as>
    {
        BOOST_SPIRIT_ASSERT_MSG(
            (traits::is_container<T>::type::value),
            error_type_must_be_a_container,
            (T));
    };
}}}

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    // enables as_string[...]
    template <>
    struct use_directive<karma::domain, tag::as_string> 
      : mpl::true_ {};

    // enables as_wstring[...]
    template <>
    struct use_directive<karma::domain, tag::as_wstring> 
      : mpl::true_ {};

    // enables as<T>[...]
    template <typename T>
    struct use_directive<karma::domain, tag::stateful_tag<T, tag::as> > 
      : mpl::true_ 
    {};
}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::as_string;
    using spirit::as_wstring;
#endif
    using spirit::as_string_type;
    using spirit::as_wstring_type;

    ///////////////////////////////////////////////////////////////////////////
    // as_directive allows to hook custom conversions to string into the
    // output generation process
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename T>
    struct as_directive 
      : unary_generator<as_directive<Subject, T> >
    {
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        as_directive(Subject const& subject)
          : subject(subject) {}

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef T type;
        };

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            if (!traits::valid_as<T>(attr))
                return false;

            return subject.generate(sink, ctx, d, traits::as<T>(attr)) &&
                    karma::delimit_out(sink, d); // always do post-delimiting
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("as", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::as_string, Subject, Modifiers>
    {
        typedef as_directive<Subject, std::string> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    template <typename Subject, typename Modifiers>
    struct make_directive<tag::as_wstring, Subject, Modifiers>
    {
        typedef as_directive<Subject, std::basic_string<wchar_t> > result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };
    
    template <typename T, typename Subject, typename Modifiers>
    struct make_directive<tag::stateful_tag<T, tag::as>, Subject, Modifiers>
    {
        typedef as_directive<Subject, T> result_type;
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
    template <typename Subject, typename T>
    struct has_semantic_action<karma::as_directive<Subject, T> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename T, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<karma::as_directive<Subject, T>, Attribute
      , Context, Iterator>
      : mpl::false_ {};   // always dereference attribute if used in sequences
}}}

#endif

/* as.hpp
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
*/
//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DELIMIT_MAR_02_2007_0217PM)
#define BOOST_SPIRIT_KARMA_DELIMIT_MAR_02_2007_0217PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/detail/unused_delimiter.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/char/char.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::delimit>   // enables delimit[]
      : mpl::true_ {};

    // enables delimit(d)[g], where d is a generator
    template <typename T>
    struct use_directive<karma::domain
          , terminal_ex<tag::delimit, fusion::vector1<T> > > 
      : boost::spirit::traits::matches<karma::domain, T> {};

    // enables *lazy* delimit(d)[g]
    template <>
    struct use_lazy_directive<karma::domain, tag::delimit, 1> 
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::delimit;
#endif
    using spirit::delimit_type;

    ///////////////////////////////////////////////////////////////////////////
    //  The redelimit_generator generator is used for delimit[...] directives.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct redelimit_generator : unary_generator<redelimit_generator<Subject> >
    {
        typedef Subject subject_type;

        typedef typename subject_type::properties properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        redelimit_generator(Subject const& subject)
          : subject(subject) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            //  The delimit_space generator simply dispatches to the embedded
            //  generator while supplying either the delimiter which has been 
            //  used before a surrounding verbatim[] directive or a single 
            //  space as the new delimiter to use (if no surrounding verbatim[]
            //  was specified).
            return subject.generate(sink, ctx
              , detail::get_delimiter(d, compile<karma::domain>(' ')), attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("delimit", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The delimit_generator is used for delimit(d)[...] directives.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Delimiter>
    struct delimit_generator 
      : unary_generator<delimit_generator<Subject, Delimiter> >
    {
        typedef Subject subject_type;
        typedef Delimiter delimiter_type;

        typedef typename subject_type::properties properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        delimit_generator(Subject const& subject, Delimiter const& delimiter)
          : subject(subject), delimiter(delimiter) {}

        template <typename OutputIterator, typename Context
          , typename Delimiter_, typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter_ const&
          , Attribute const& attr) const
        {
            //  the delimit generator simply dispatches to the embedded
            //  generator while supplying it's argument as the new delimiter
            //  to use
            return subject.generate(sink, ctx, delimiter, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("delimit", subject.what(context));
        }

        Subject subject;
        Delimiter delimiter;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::delimit, Subject, Modifiers>
    {
        typedef redelimit_generator<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    template <typename Delimiter, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::delimit, fusion::vector1<Delimiter> >
      , Subject, Modifiers>
    {
        typedef typename
            result_of::compile<karma::domain, Delimiter, Modifiers>::type
        delimiter_type;

        typedef delimit_generator<Subject, delimiter_type> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject
              , compile<karma::domain>(fusion::at_c<0>(term.args)));
        }
    };

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::redelimit_generator<Subject> >
      : unary_has_semantic_action<Subject> {};

    template <typename Subject, typename Delimiter>
    struct has_semantic_action<karma::delimit_generator<Subject, Delimiter> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute
            , typename Context, typename Iterator>
    struct handles_container<karma::redelimit_generator<Subject>, Attribute
      , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};

    template <typename Subject, typename Delimiter, typename Attribute
            , typename Context, typename Iterator>
    struct handles_container<karma::delimit_generator<Subject, Delimiter>
      , Attribute, Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* delimit.hpp
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
*/
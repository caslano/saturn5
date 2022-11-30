/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_REFERENCE_OCTOBER_31_2008_1218AM)
#define BOOST_SPIRIT_REFERENCE_OCTOBER_31_2008_1218AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/ref.hpp>

namespace boost { namespace spirit { namespace qi
{
    ///////////////////////////////////////////////////////////////////////////
    // reference is a parser that references another parser (its Subject)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct reference : parser<reference<Subject> >
    {
        typedef Subject subject_type;

        reference(Subject& subject)
          : ref(subject) {}

        template <typename Context, typename Iterator>
        struct attribute : Subject::template attribute<Context, Iterator> {};

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr_) const
        {
            return ref.get().parse(first, last, context, skipper, attr_);
        }

        template <typename Context>
        info what(Context& context) const
        {
            // the reference is transparent (does not add any info)
            return ref.get().what(context);
        }

        boost::reference_wrapper<Subject> ref;
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<qi::reference<Subject>, Attribute, Context
      , Iterator>
      : handles_container<typename remove_const<Subject>::type
        , Attribute, Context, Iterator> 
    {};
}}}

#endif

/* reference.hpp
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
*/
//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_REFERENCE_APR_17_2009_1057PM)
#define BOOST_SPIRIT_KARMA_REFERENCE_APR_17_2009_1057PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/ref.hpp>

namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    // reference is a generator that references another generator (its Subject)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct reference : generator<reference<Subject> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        typedef Subject subject_type;

        reference(Subject& subject)
          : ref(subject) {}

        template <typename Context, typename Unused>
        struct attribute : Subject::template attribute<Context, Unused> {};

        // Default overload, used whenever the attribute is not unused and not
        // used from an aliased rule.
        template <typename OutputIterator, typename Context
          , typename Delimiter, typename Attribute>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& delim, Attribute const& attr) const
        {
            return ref.get().generate(sink, context, delim, attr);
        }

        // This overload gets called from an aliased rule only, we take the 
        // attribute from the context provided from the wrapper rule.
        template <typename OutputIterator, typename Context
          , typename Delimiter>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& delim, unused_type) const
        {
            return ref.get().generate(sink, context, delim, context.attributes);
        }

        // This overload is used whenever no attribute is given and it is used
        // not from an aliased rule.
        template <typename OutputIterator, typename Delimiter>
        bool generate(OutputIterator& sink, unused_type
          , Delimiter const& delim, unused_type) const
        {
            return ref.get().generate(sink, unused, delim, unused);
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
    struct handles_container<karma::reference<Subject>, Attribute
      , Context, Iterator>
      : handles_container<typename remove_const<Subject>::type, Attribute
        , Context, Iterator> 
    {};
}}}

#endif

/* reference.hpp
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
*/
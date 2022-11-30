//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_MAXWIDTH_MAR_18_2009_0827AM)
#define BOOST_SPIRIT_KARMA_MAXWIDTH_MAR_18_2009_0827AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/detail/default_width.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/detail/workaround.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables maxwidth[]
    template <>
    struct use_directive<karma::domain, tag::maxwidth>
      : mpl::true_ {};

    // enables maxwidth(w)[g], where w provides a maxwidth
    template <typename T>
    struct use_directive<karma::domain
          , terminal_ex<tag::maxwidth, fusion::vector1<T> > > 
      : mpl::true_ {};

    // enables *lazy* maxwidth(w)[g], where w provides a maxwidth
    template <>
    struct use_lazy_directive<karma::domain, tag::maxwidth, 1> 
      : mpl::true_ {};

    // enables maxwidth(w, r)[g], where w provides a maxwidth and r is an output
    // iterator used to receive the rest of the output not fitting into the 
    // maxwidth limit
    template <typename T, typename RestIter>
    struct use_directive<karma::domain
          , terminal_ex<tag::maxwidth, fusion::vector2<T, RestIter> > > 
      : mpl::true_ {};

    // enables *lazy* maxwidth(w, r)[g], where w provides a maxwidth and r is 
    // an output iterator used to receive the rest of the output not fitting 
    // into the maxwidth limit
    template <>
    struct use_lazy_directive<karma::domain, tag::maxwidth, 2> 
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::maxwidth;
#endif
    using spirit::maxwidth_type;

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename RestIterator>
        bool buffer_copy_rest(detail::enable_buffering<OutputIterator>& buff
          , std::size_t start_at, RestIterator& dest)
        {
            return buff.buffer_copy_rest(dest, start_at);
        }

        template <typename OutputIterator>
        bool buffer_copy_rest(detail::enable_buffering<OutputIterator>&
          , std::size_t, unused_type)
        {
            return true;
        }

        ///////////////////////////////////////////////////////////////////////
        //  The maxwidth_generate template function is used for all the 
        //  different flavors of the maxwidth[] directive. 
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename Context, typename Delimiter, 
            typename Attribute, typename Embedded, typename Rest>
        inline static bool 
        maxwidth_generate(OutputIterator& sink, Context& ctx, 
            Delimiter const& d, Attribute const& attr, Embedded const& e, 
            unsigned int const maxwidth, Rest& restdest) 
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)e; // suppresses warning: C4100: 'e' : unreferenced formal parameter
#endif
            // wrap the given output iterator to allow buffering, but disable 
            // counting
            detail::enable_buffering<OutputIterator> buffering(sink);

            // generate the underlying output and copy the embedded 
            // output to the target output iterator applying the given 
            // maxwidth
            bool r = false;
            {
                detail::disable_counting<OutputIterator> nocounting(sink);
                r = e.generate(sink, ctx, d, attr);
            }   // re-enable counting

            return r && buffering.buffer_copy(maxwidth) &&
                   buffer_copy_rest(buffering, maxwidth, restdest);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //  The maxwidth directive is used for maxwidth[...]
    //  generators. It uses default values for the generated width (defined via
    //  the BOOST_KARMA_DEFAULT_FIELD_MAXWIDTH constant).
    // 
    //  The maxwidth with width directive, is used for generators
    //  like maxwidth(width)[...]. 
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width = detail::default_max_width
      , typename Rest = unused_type>
    struct maxwidth_width
      : unary_generator<maxwidth_width<Subject, Width, Rest> >
    {
        typedef Subject subject_type;

        typedef mpl::int_<
            generator_properties::countingbuffer | subject_type::properties::value
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        maxwidth_width(Subject const& subject, Width const& w = Width()
            , Rest const& r = Rest())
          : subject(subject), width(w), rest(r) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::maxwidth_generate(sink, ctx, d, attr, subject
              , width, rest);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("maxwidth", subject.what(context));
        }

        Subject subject;
        Width width;
        Rest rest;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    // creates maxwidth[] directive generator
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::maxwidth, Subject, Modifiers>
    {
        typedef maxwidth_width<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    // creates maxwidth(width)[] directive generator
    template <typename T, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::maxwidth, fusion::vector1<T> >
      , Subject, Modifiers>
    {
        typedef maxwidth_width<Subject, T> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args), unused);
        }
    };

    // creates maxwidth(width, restiter)[] directive generator
    template <
        typename T, typename RestIter, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::maxwidth, fusion::vector2<T, RestIter> >
      , Subject, Modifiers>
    {
        typedef maxwidth_width<Subject, T, RestIter> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args)
              , fusion::at_c<1>(term.args));
        }
    };

}}} // namespace boost::spirit::karma

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width, typename Rest>
    struct has_semantic_action<karma::maxwidth_width<Subject, Width, Rest> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
        , typename Iterator>
    struct handles_container<karma::maxwidth_width<Subject>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif



/* maxwidth.hpp
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
*/
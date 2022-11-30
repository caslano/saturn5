//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_LEFT_ALIGNMENT_FEB_27_2007_1216PM)
#define BOOST_SPIRIT_KARMA_LEFT_ALIGNMENT_FEB_27_2007_1216PM

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
#include <boost/spirit/home/karma/char/char.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/integer_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/detail/workaround.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables left_align[]
    template <>
    struct use_directive<karma::domain, tag::left_align>
      : mpl::true_ {};

    // enables left_align(d)[g] and left_align(w)[g], where d is a generator
    // and w is a maximum width
    template <typename T>
    struct use_directive<karma::domain
          , terminal_ex<tag::left_align, fusion::vector1<T> > >
      : mpl::true_ {};

    // enables *lazy* left_align(d)[g], where d provides a generator
    template <>
    struct use_lazy_directive<karma::domain, tag::left_align, 1> 
      : mpl::true_ {};

    // enables left_align(w, d)[g], where d is a generator and w is a maximum 
    // width
    template <typename Width, typename Padding>
    struct use_directive<karma::domain
          , terminal_ex<tag::left_align, fusion::vector2<Width, Padding> > >
      : spirit::traits::matches<karma::domain, Padding> {};

    // enables *lazy* left_align(w, d)[g], where d provides a generator and w 
    // is a maximum width
    template <>
    struct use_lazy_directive<karma::domain, tag::left_align, 2> 
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::left_align;
#endif
    using spirit::left_align_type;

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        //  The left_align_generate template function is used for all the 
        //  different flavors of the left_align[] directive. 
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename Context, typename Delimiter, 
            typename Attribute, typename Embedded, typename Padding>
        inline static bool 
        left_align_generate(OutputIterator& sink, Context& ctx, 
            Delimiter const& d, Attribute const& attr, Embedded const& e, 
            unsigned int const width, Padding const& p) 
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)e; // suppresses warning: C4100: 'e' : unreferenced formal parameter
#endif
            // wrap the given output iterator to allow counting
            detail::enable_counting<OutputIterator> counting(sink);

            // first generate the underlying output 
            bool r = e.generate(sink, ctx, d, attr);

            // pad the output until the max width is reached
            while(r && counting.count() < width) 
                r = p.generate(sink, ctx, unused, unused);

            return r;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //  The simple left alignment directive is used for left_align[...]
    //  generators. It uses default values for the generated width (defined via
    //  the BOOST_KARMA_DEFAULT_FIELD_LENGTH constant) and for the padding
    //  generator (always spaces).
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width = detail::default_width>
    struct simple_left_alignment 
      : unary_generator<simple_left_alignment<Subject, Width> >
    {
        typedef Subject subject_type;

        typedef mpl::int_<
            generator_properties::counting | subject_type::properties::value
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        simple_left_alignment(Subject const& subject, Width width = Width())
          : subject(subject), width(width) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::left_align_generate(sink, ctx, d, attr,
                subject, width, compile<karma::domain>(' '));
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("left_align", subject.what(context));
        }

        Subject subject;
        Width width;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The left alignment directive with padding, is used for generators like
    //  left_align(padding)[...], where padding is a arbitrary generator
    //  expression. It uses a default value for the generated width (defined
    //  via the BOOST_KARMA_DEFAULT_FIELD_LENGTH constant).
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Padding
      , typename Width = detail::default_width>
    struct padding_left_alignment 
      : unary_generator<padding_left_alignment<Subject, Padding, Width> >
    {
        typedef Subject subject_type;
        typedef Padding padding_type;

        typedef mpl::int_<
            generator_properties::counting | 
            subject_type::properties::value | padding_type::properties::value 
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        padding_left_alignment(Subject const& subject, Padding const& padding
              , Width width = Width())
          : subject(subject), padding(padding), width(width) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::left_align_generate(sink, ctx, d, attr,
                subject, width, padding);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("left_align", subject.what(context));
        }

        Subject subject;
        Padding padding;
        Width width;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    // creates left_align[] directive generator
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::left_align, Subject, Modifiers>
    {
        typedef simple_left_alignment<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    // creates left_align(width)[] directive generator
    template <typename Width, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::left_align, fusion::vector1<Width> >
      , Subject, Modifiers
      , typename enable_if_c< integer_traits<Width>::is_integral >::type>
    {
        typedef simple_left_alignment<Subject, Width> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args));
        }
    };

    // creates left_align(pad)[] directive generator
    template <typename Padding, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::left_align, fusion::vector1<Padding> >
      , Subject, Modifiers
      , typename enable_if<
            mpl::and_<
                spirit::traits::matches<karma::domain, Padding>,
                mpl::not_<mpl::bool_<integer_traits<Padding>::is_integral> >
            >
        >::type>
    {
        typedef typename
            result_of::compile<karma::domain, Padding, Modifiers>::type
        padding_type;

        typedef padding_left_alignment<Subject, padding_type> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , Modifiers const& modifiers) const
        {
            return result_type(subject
              , compile<karma::domain>(fusion::at_c<0>(term.args), modifiers));
        }
    };

    // creates left_align(width, pad)[] directive generator
    template <typename Width, typename Padding, typename Subject
      , typename Modifiers>
    struct make_directive<
        terminal_ex<tag::left_align, fusion::vector2<Width, Padding> >
      , Subject, Modifiers>
    {
        typedef typename
            result_of::compile<karma::domain, Padding, Modifiers>::type
        padding_type;

        typedef padding_left_alignment<Subject, padding_type, Width> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , Modifiers const& modifiers) const
        {
            return result_type(subject
              , compile<karma::domain>(fusion::at_c<1>(term.args), modifiers)
              , fusion::at_c<0>(term.args));
        }
    };

}}} // namespace boost::spirit::karma

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width>
    struct has_semantic_action<karma::simple_left_alignment<Subject, Width> >
      : unary_has_semantic_action<Subject> {};

    template <typename Subject, typename Padding, typename Width>
    struct has_semantic_action<
            karma::padding_left_alignment<Subject, Padding, Width> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<
            karma::simple_left_alignment<Subject, Width>, Attribute
          , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};

    template <typename Subject, typename Padding, typename Width
      , typename Attribute, typename Context, typename Iterator>
    struct handles_container<
            karma::padding_left_alignment<Subject, Padding, Width>
          , Attribute, Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif



/* left_alignment.hpp
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
*/
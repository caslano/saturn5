//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_RIGHT_ALIGNMENT_FEB_27_2007_1216PM)
#define BOOST_SPIRIT_KARMA_RIGHT_ALIGNMENT_FEB_27_2007_1216PM

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
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
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

    // enables right_align[]
    template <>
    struct use_directive<karma::domain, tag::right_align>
      : mpl::true_ {};

    // enables right_align(d)[g] and right_align(w)[g], where d is a generator
    // and w is a maximum width
    template <typename T>
    struct use_directive<karma::domain
          , terminal_ex<tag::right_align, fusion::vector1<T> > >
      : mpl::true_ {};

    // enables *lazy* right_align(d)[g], where d provides a generator
    template <>
    struct use_lazy_directive<karma::domain, tag::right_align, 1> 
      : mpl::true_ {};

    // enables right_align(w, d)[g], where d is a generator and w is a maximum 
    // width
    template <typename Width, typename Padding>
    struct use_directive<karma::domain
          , terminal_ex<tag::right_align, fusion::vector2<Width, Padding> > >
      : spirit::traits::matches<karma::domain, Padding> {};

    // enables *lazy* right_align(w, d)[g], where d provides a generator and w 
    // is a maximum width
    template <>
    struct use_lazy_directive<karma::domain, tag::right_align, 2> 
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::right_align;
#endif
    using spirit::right_align_type;

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        //  The right_align_generate template function is used for all the 
        //  different flavors of the right_align[] directive. 
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename Context, typename Delimiter, 
            typename Attribute, typename Embedded, typename Padding>
        inline static bool 
        right_align_generate(OutputIterator& sink, Context& ctx, 
            Delimiter const& d, Attribute const& attr, Embedded const& e, 
            unsigned int const width, Padding const& p) 
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)e; // suppresses warning: C4100: 'e' : unreferenced formal parameter
#endif
            // wrap the given output iterator to allow left padding
            detail::enable_buffering<OutputIterator> buffering(sink, width);
            bool r = false;

            // first generate the embedded output 
            {
                detail::disable_counting<OutputIterator> nocounting(sink);
                r = e.generate(sink, ctx, d, attr);
            }   // re-enable counting

            buffering.disable();    // do not perform buffering any more

            // generate the left padding
            detail::enable_counting<OutputIterator> counting(sink, buffering.buffer_size());
            while(r && counting.count() < width) 
                r = p.generate(sink, ctx, unused, unused);

            // copy the buffered output to the target output iterator
            if (r) 
                buffering.buffer_copy();
            return r;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //  The simple left alignment directive is used for right_align[...]
    //  generators. It uses default values for the generated width (defined via
    //  the BOOST_KARMA_DEFAULT_FIELD_LENGTH constant) and for the padding
    //  generator (always spaces).
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width = detail::default_width>
    struct simple_right_alignment 
      : unary_generator<simple_right_alignment<Subject, Width> >
    {
        typedef Subject subject_type;

        typedef mpl::int_<
            generator_properties::countingbuffer | subject_type::properties::value
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        simple_right_alignment(Subject const& subject, Width width = Width())
          : subject(subject), width(width) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::right_align_generate(sink, ctx, d, attr,
                subject, width, compile<karma::domain>(' '));
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("right_align", subject.what(context));
        }

        Subject subject;
        Width width;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The left alignment directive with padding, is used for generators like
    //  right_align(padding)[...], where padding is a arbitrary generator
    //  expression. It uses a default value for the generated width (defined
    //  via the BOOST_KARMA_DEFAULT_FIELD_LENGTH constant).
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Padding
      , typename Width = detail::default_width>
    struct padding_right_alignment 
      : unary_generator<padding_right_alignment<Subject, Padding, Width> >
    {
        typedef Subject subject_type;
        typedef Padding padding_type;

        typedef mpl::int_<
            generator_properties::countingbuffer |
            subject_type::properties::value | padding_type::properties::value 
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        padding_right_alignment(Subject const& subject, Padding const& padding
              , Width width = Width())
          : subject(subject), padding(padding), width(width) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::right_align_generate(sink, ctx, d, attr,
                subject, width, padding);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("right_align", subject.what(context));
        }

        Subject subject;
        Padding padding;
        Width width;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    // creates right_align[] directive generator
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::right_align, Subject, Modifiers>
    {
        typedef simple_right_alignment<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    // creates right_align(width)[] directive generator
    template <typename Width, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::right_align, fusion::vector1<Width> >
      , Subject, Modifiers
      , typename enable_if_c< integer_traits<Width>::is_integral >::type>
    {
        typedef simple_right_alignment<Subject, Width> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args));
        }
    };

    // creates right_align(pad)[] directive generator
    template <typename Padding, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::right_align, fusion::vector1<Padding> >
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

        typedef padding_right_alignment<Subject, padding_type> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , Modifiers const& modifiers) const
        {
            return result_type(subject
              , compile<karma::domain>(fusion::at_c<0>(term.args), modifiers));
        }
    };

    // creates right_align(width, pad)[] directive generator
    template <typename Width, typename Padding, typename Subject
      , typename Modifiers>
    struct make_directive<
        terminal_ex<tag::right_align, fusion::vector2<Width, Padding> >
      , Subject, Modifiers>
    {
        typedef typename
            result_of::compile<karma::domain, Padding, Modifiers>::type
        padding_type;

        typedef padding_right_alignment<Subject, padding_type, Width> result_type;

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
    struct has_semantic_action<karma::simple_right_alignment<Subject, Width> >
      : unary_has_semantic_action<Subject> {};

    template <typename Subject, typename Padding, typename Width>
    struct has_semantic_action<
            karma::padding_right_alignment<Subject, Padding, Width> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<
            karma::simple_right_alignment<Subject, Width>
          , Attribute, Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};

    template <typename Subject, typename Padding, typename Width
      , typename Attribute, typename Context, typename Iterator>
    struct handles_container<
            karma::padding_right_alignment<Subject, Padding, Width>
          , Attribute, Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif


/* right_alignment.hpp
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
*/
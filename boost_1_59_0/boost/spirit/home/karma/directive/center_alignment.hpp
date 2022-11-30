//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_CENTER_ALIGNMENT_FEB_27_2007_1216PM)
#define BOOST_SPIRIT_KARMA_CENTER_ALIGNMENT_FEB_27_2007_1216PM

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

    // enables center[]
    template <>
    struct use_directive<karma::domain, tag::center>
      : mpl::true_ {};

    // enables center(d)[g] and center(w)[g], where d is a generator
    // and w is a maximum width
    template <typename T>
    struct use_directive<karma::domain
          , terminal_ex<tag::center, fusion::vector1<T> > >
      : mpl::true_ {};

    // enables *lazy* center(d)[g], where d provides a generator
    template <>
    struct use_lazy_directive<karma::domain, tag::center, 1>
      : mpl::true_ {};

    // enables center(w, d)[g], where d is a generator and w is a maximum
    // width
    template <typename Width, typename Padding>
    struct use_directive<karma::domain
          , terminal_ex<tag::center, fusion::vector2<Width, Padding> > >
      : spirit::traits::matches<karma::domain, Padding> {};

    // enables *lazy* center(w, d)[g], where d provides a generator and w is
    // a maximum width
    template <>
    struct use_lazy_directive<karma::domain, tag::center, 2>
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::center;
#endif
    using spirit::center_type;

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        //  The center_generate template function is used for all the
        //  different flavors of the center[] directive.
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename Context, typename Delimiter,
            typename Attribute, typename Embedded, typename Padding>
        inline static bool
        center_generate(OutputIterator& sink, Context& ctx,
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
            detail::enable_counting<OutputIterator> counting(sink);

            std::size_t const pre = width - (buffering.buffer_size() + width)/2;
            while (r && counting.count() < pre)
                r = p.generate(sink, ctx, unused, unused);

            if (r) {
                // copy the embedded output to the target output iterator
                buffering.buffer_copy();

                // generate the right padding
                while (r && counting.count() < width)
                    r = p.generate(sink, ctx, unused, unused);
            }
            return r;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //  The simple left alignment directive is used for center[...]
    //  generators. It uses default values for the generated width (defined via
    //  the BOOST_KARMA_DEFAULT_FIELD_LENGTH constant) and for the padding
    //  generator (always spaces).
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width = detail::default_width>
    struct simple_center_alignment
      : unary_generator<simple_center_alignment<Subject, Width> >
    {
        typedef Subject subject_type;

        typedef mpl::int_<
            generator_properties::countingbuffer | subject_type::properties::value
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        simple_center_alignment(Subject const& subject, Width width = Width())
          : subject(subject), width(width) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::center_generate(sink, ctx, d, attr,
                subject, width, compile<karma::domain>(' '));
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("center", subject.what(context));
        }

        Subject subject;
        Width width;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The left alignment directive with padding, is used for generators like
    //  center(padding)[...], where padding is a arbitrary generator
    //  expression. It uses a default value for the generated width (defined
    //  via the BOOST_KARMA_DEFAULT_FIELD_LENGTH constant).
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Padding
      , typename Width = detail::default_width>
    struct padding_center_alignment
      : unary_generator<padding_center_alignment<Subject, Padding, Width> >
    {
        typedef Subject subject_type;
        typedef Padding padding_type;

        typedef mpl::int_<
            generator_properties::countingbuffer |
            subject_type::properties::value | padding_type::properties::value
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<Subject, Context, Iterator>
        {};

        padding_center_alignment(Subject const& subject, Padding const& padding
              , Width width = Width())
          : subject(subject), padding(padding), width(width) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            return detail::center_generate(sink, ctx, d, attr,
                subject, width, padding);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("center", subject.what(context));
        }

        Subject subject;
        Padding padding;
        Width width;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    // creates center[] directive generator
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::center, Subject, Modifiers>
    {
        typedef simple_center_alignment<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    // creates center(width)[] directive generator
    template <typename Width, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::center, fusion::vector1<Width> >
      , Subject, Modifiers
      , typename enable_if_c< integer_traits<Width>::is_integral >::type>
    {
        typedef simple_center_alignment<Subject, Width> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args));
        }
    };

    // creates center(pad)[] directive generator
    template <typename Padding, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::center, fusion::vector1<Padding> >
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

        typedef padding_center_alignment<Subject, padding_type> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , Modifiers const& modifiers) const
        {
            return result_type(subject
              , compile<karma::domain>(fusion::at_c<0>(term.args), modifiers));
        }
    };

    // creates center(width, pad)[] directive generator
    template <typename Width, typename Padding, typename Subject
      , typename Modifiers>
    struct make_directive<
        terminal_ex<tag::center, fusion::vector2<Width, Padding> >
      , Subject, Modifiers>
    {
        typedef typename
            result_of::compile<karma::domain, Padding, Modifiers>::type
        padding_type;

        typedef padding_center_alignment<Subject, padding_type, Width> result_type;

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
    struct has_semantic_action<karma::simple_center_alignment<Subject, Width> >
      : unary_has_semantic_action<Subject> {};

    template <typename Subject, typename Padding, typename Width>
    struct has_semantic_action<
            karma::padding_center_alignment<Subject, Padding, Width> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Width, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<
            karma::simple_center_alignment<Subject, Width>, Attribute
          , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};

    template <typename Subject, typename Padding, typename Width
      , typename Attribute, typename Context, typename Iterator>
    struct handles_container<
            karma::padding_center_alignment<Subject, Padding, Width>
          , Attribute, Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif



/* center_alignment.hpp
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
*/
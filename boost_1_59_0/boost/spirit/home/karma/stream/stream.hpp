//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_STREAM_MAY_01_2007_0310PM)
#define BOOST_SPIRIT_KARMA_STREAM_MAY_01_2007_0310PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/support/detail/is_spirit_tag.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/stream/detail/format_manip.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/detail/extract_from.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/cons.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <ostream>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    namespace tag
    {
        template <typename Char = char>
        struct stream_tag 
        {
            BOOST_SPIRIT_IS_TAG()
        };
    }

    namespace karma
    {
        ///////////////////////////////////////////////////////////////////////
        // This one is the class that the user can instantiate directly in 
        // order to create a customized int generator
        template <typename Char = char>
        struct stream_generator
          : spirit::terminal<tag::stream_tag<Char> > 
        {};
    }

    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, tag::stream>     // enables stream
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::wstream>    // enables wstream
      : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain                   // enables stream(...)
      , terminal_ex<tag::stream, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain                   // enables wstream(...)
      , terminal_ex<tag::wstream, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <>                                         // enables stream(f)
    struct use_lazy_terminal<
        karma::domain, tag::stream, 1   /*arity*/
    > : mpl::true_ {};

    template <>                                         // enables wstream(f)
    struct use_lazy_terminal<
        karma::domain, tag::wstream, 1  /*arity*/
    > : mpl::true_ {};

    // enables stream_generator<char_type>
    template <typename Char>
    struct use_terminal<karma::domain, tag::stream_tag<Char> >
      : mpl::true_ {};

    template <typename Char, typename A0>
    struct use_terminal<karma::domain
      , terminal_ex<tag::stream_tag<Char>, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename Char>
    struct use_lazy_terminal<
        karma::domain, tag::stream_tag<Char>, 1  /*arity*/
    > : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::stream;
    using spirit::wstream;
#endif
    using spirit::stream_type;
    using spirit::wstream_type;

namespace detail
{
    template <typename OutputIterator, typename Char, typename CharEncoding
      , typename Tag>
    struct psbuf : std::basic_streambuf<Char>
    {
        psbuf(OutputIterator& sink) : sink_(sink) {}

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(psbuf& operator=(psbuf const&))

    protected:
        typename psbuf::int_type overflow(typename psbuf::int_type ch) BOOST_OVERRIDE
        {
            if (psbuf::traits_type::eq_int_type(ch, psbuf::traits_type::eof()))
                return psbuf::traits_type::not_eof(ch);

            return detail::generate_to(sink_, psbuf::traits_type::to_char_type(ch),
                                       CharEncoding(), Tag()) ? ch : psbuf::traits_type::eof();
        }

    private:
        OutputIterator& sink_;
    };
}

    ///////////////////////////////////////////////////////////////////////////
    template <typename Char, typename CharEncoding, typename Tag>
    struct any_stream_generator
      : primitive_generator<any_stream_generator<Char, CharEncoding, Tag> >
    {
        template <typename Context, typename Unused = unused_type>
        struct attribute
        {
            typedef spirit::basic_hold_any<Char> type;
        };

        // any_stream_generator has an attached attribute 
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute
        >
        static bool generate(OutputIterator& sink, Context& context
          , Delimiter const& d, Attribute const& attr)
        {
            if (!traits::has_optional_value(attr))
                return false;

            // use existing operator<<()
            typedef typename attribute<Context>::type attribute_type;

            {
                detail::psbuf<OutputIterator, Char, CharEncoding, Tag> pseudobuf(sink);
                std::basic_ostream<Char> ostr(&pseudobuf);
                ostr << traits::extract_from<attribute_type>(attr, context) << std::flush;

                if (!ostr.good())
                    return false;
            }

            return karma::delimit_out(sink, d);   // always do post-delimiting
        }

        // this is a special overload to detect if the output iterator has been
        // generated by a format_manip object.
        template <
            typename T, typename Traits, typename Properties, typename Context
          , typename Delimiter, typename Attribute
        >
        static bool generate(
            karma::detail::output_iterator<
                karma::ostream_iterator<T, Char, Traits>, Properties
            >& sink, Context& context, Delimiter const& d
          , Attribute const& attr)
        {
            typedef karma::detail::output_iterator<
                karma::ostream_iterator<T, Char, Traits>, Properties
            > output_iterator;

            if (!traits::has_optional_value(attr))
                return false;

            // use existing operator<<()
            typedef typename attribute<Context>::type attribute_type;

            {
                detail::psbuf<output_iterator, Char, CharEncoding, Tag> pseudobuf(sink);
                std::basic_ostream<Char> ostr(&pseudobuf);
                ostr.imbue(sink.get_ostream().getloc());
                ostr << traits::extract_from<attribute_type>(attr, context) 
                     << std::flush;
                if (!ostr.good())
                    return false;
            }

            return karma::delimit_out(sink, d);  // always do post-delimiting
        }

        // this any_stream has no parameter attached, it needs to have been
        // initialized from a value/variable
        template <typename OutputIterator, typename Context
          , typename Delimiter>
        static bool
        generate(OutputIterator&, Context&, Delimiter const&, unused_type)
        {
            // It is not possible (doesn't make sense) to use stream generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(OutputIterator, stream_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("stream");
        }
    };

    template <typename T, typename Char, typename CharEncoding, typename Tag>
    struct lit_stream_generator
      : primitive_generator<lit_stream_generator<T, Char, CharEncoding, Tag> >
    {
        template <typename Context, typename Unused>
        struct attribute 
        {
            typedef unused_type type;
        };

        lit_stream_generator(typename add_reference<T>::type t)
          : t_(t)
        {}

        // lit_stream_generator has an attached parameter

        // this overload will be used in the normal case (not called from
        // format_manip).
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attribute const&) const
        {
            detail::psbuf<OutputIterator, Char, CharEncoding, Tag> pseudobuf(sink);
            std::basic_ostream<Char> ostr(&pseudobuf);
            ostr << t_ << std::flush;             // use existing operator<<()

            if (ostr.good()) 
                return karma::delimit_out(sink, d); // always do post-delimiting
            return false;
        }

        // this is a special overload to detect if the output iterator has been
        // generated by a format_manip object.
        template <
            typename T1, typename Traits, typename Properties
          , typename Context, typename Delimiter, typename Attribute>
        bool generate(
            karma::detail::output_iterator<
                karma::ostream_iterator<T1, Char, Traits>, Properties
            >& sink, Context&, Delimiter const& d, Attribute const&) const
        {
            typedef karma::detail::output_iterator<
                karma::ostream_iterator<T1, Char, Traits>, Properties
            > output_iterator;

            {
                detail::psbuf<output_iterator, Char, CharEncoding, Tag> pseudobuf(sink);
                std::basic_ostream<Char> ostr(&pseudobuf);
                ostr.imbue(sink.get_ostream().getloc());
                ostr << t_ << std::flush;             // use existing operator<<()

                if (!ostr.good())
                    return false;
            }

            return karma::delimit_out(sink, d); // always do post-delimiting
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("any-stream");
        }

        T t_;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(lit_stream_generator& operator= (lit_stream_generator const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Char, typename Modifiers>
    struct make_stream
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;

        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef any_stream_generator<
            Char
          , typename spirit::detail::get_encoding_with_case<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
        > result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    // stream
    template <typename Modifiers>
    struct make_primitive<tag::stream, Modifiers> 
      : make_stream<char, Modifiers> {};

    // wstream
    template <typename Modifiers>
    struct make_primitive<tag::wstream, Modifiers> 
      : make_stream<wchar_t, Modifiers> {};

    // any_stream_generator<char_type>
    template <typename Char, typename Modifiers>
    struct make_primitive<tag::stream_tag<Char>, Modifiers> 
      : make_stream<Char, Modifiers> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Char, typename A0, typename Modifiers>
    struct make_any_stream
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;

        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef typename add_const<A0>::type const_attribute;
        typedef lit_stream_generator<
            const_attribute, Char
          , typename spirit::detail::get_encoding_with_case<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

    // stream(...)
    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::stream, fusion::vector1<A0> >, Modifiers>
      : make_any_stream<char, A0, Modifiers> {};

    // wstream(...)
    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::wstream, fusion::vector1<A0> >, Modifiers>
      : make_any_stream<wchar_t, A0, Modifiers> {};

    // any_stream_generator<char_type>(...)
    template <typename Char, typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::stream_tag<Char>, fusion::vector1<A0> >
          , Modifiers>
      : make_any_stream<Char, A0, Modifiers> {};

}}}

#endif

/* stream.hpp
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
*/
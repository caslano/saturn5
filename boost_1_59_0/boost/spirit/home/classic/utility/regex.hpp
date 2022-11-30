/*=============================================================================
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_REGEX_HPP
#define BOOST_SPIRIT_REGEX_HPP

#include <boost/version.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Include the regular expression library of boost (Boost.Regex)
//
//  Note though, that this library is not distributed with Spirit. You have to
//  obtain a separate copy from http://www.boost.org.
//
///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_SPIRIT_NO_REGEX_LIB) && BOOST_VERSION < 103300
//
//  Include all the Boost.regex library. Please note that this will not work,
//  if you are using the boost/spirit/regex.hpp header from more than one
//  translation units.
//
#define BOOST_REGEX_NO_LIB
#define BOOST_REGEX_STATIC_LINK
#define BOOST_REGEX_NO_EXTERNAL_TEMPLATES
#include <boost/regex.hpp>
#include <boost/regex/src.cpp>

#else
//
//  Include the Boost.Regex headers only. Note, that you will have to link your
//  application against the Boost.Regex library as described in the related
//  documentation.
//  This is the only way for Boost newer than V1.32.0
//
#include <boost/regex.hpp>
#endif // defined(BOOST_SPIRIT_NO_REGEX_LIB)

#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/utility/impl/regex.ipp>
#include <iterator> // for std::iterator_traits

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// rxstrlit class
template <typename CharT = char>
struct rxstrlit : public parser<rxstrlit<CharT> > {

    typedef rxstrlit self_t;

    rxstrlit(CharT const *first, CharT const *last)
    : rx(first, last) {}
    rxstrlit(CharT const *first)
    : rx(first) {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
    //  Due to limitations in the boost::regex library the iterators wrapped in
    //  the ScannerT object should be at least bidirectional iterators. Plain
    //  forward iterators do not work here.
        typedef typename ScannerT::iterator_t iterator_t;
        typedef
            typename std::iterator_traits<iterator_t>::iterator_category
            iterator_category;

        BOOST_STATIC_ASSERT((
            boost::is_convertible<iterator_category,
                std::bidirectional_iterator_tag>::value
        ));

        typedef typename parser_result<self_t, ScannerT>::type result_t;
        return impl::contiguous_parser_parse<result_t>(rx, scan, scan);
    }

private:
    impl::rx_parser<CharT> rx;   // contains the boost regular expression parser
};

///////////////////////////////////////////////////////////////////////////////
// Generator functions
template <typename CharT>
inline rxstrlit<CharT>
regex_p(CharT const *first)
{ return rxstrlit<CharT>(first); }

//////////////////////////////////
template <typename CharT>
inline rxstrlit<CharT>
regex_p(CharT const *first, CharT const *last)
{ return rxstrlit<CharT>(first, last); }

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_REGEX_HPP

/* regex.hpp
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
*/
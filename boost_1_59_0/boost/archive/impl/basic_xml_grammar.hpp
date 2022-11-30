#ifndef BOOST_ARCHIVE_BASIC_XML_GRAMMAR_HPP
#define BOOST_ARCHIVE_BASIC_XML_GRAMMAR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_grammar.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// this module is derived from simplexml.cpp - an example shipped as part of
// the spirit parser.  This example contains the following notice:
/*=============================================================================
    simplexml.cpp

    Spirit V1.3
    URL: http://spirit.sourceforge.net/

    Copyright (c) 2001, Daniel C. Nuffer

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the copyright holder be held liable for
    any damages arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute
    it freely, subject to the following restrictions:

    1.  The origin of this software must not be misrepresented; you must
        not claim that you wrote the original software. If you use this
        software in a product, an acknowledgment in the product documentation
        would be appreciated but is not required.

    2.  Altered source versions must be plainly marked as such, and must
        not be misrepresented as being the original software.

    3.  This notice may not be removed or altered from any source
        distribution.
=============================================================================*/
#include <string>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/spirit/include/classic_rule.hpp>
#include <boost/spirit/include/classic_chset.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/version.hpp>

namespace boost {
namespace archive {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// XML grammar parsing

template<class CharType>
class BOOST_SYMBOL_VISIBLE basic_xml_grammar {
public:
    // The following is not necessary according to DR45, but at least
    // one compiler (Compaq C++ 6.5 in strict_ansi mode) chokes otherwise.
    struct return_values;
    friend struct return_values;

private:
    typedef typename std::basic_istream<CharType> IStream;
    typedef typename std::basic_string<CharType> StringType;
    typedef typename boost::spirit::classic::chset<CharType> chset_t;
    typedef typename boost::spirit::classic::chlit<CharType> chlit_t;
    typedef typename boost::spirit::classic::scanner<
        typename  std::basic_string<CharType>::iterator
    > scanner_t;
    typedef typename boost::spirit::classic::rule<scanner_t> rule_t;
    // Start grammar definition
    rule_t
        Reference,
        Eq,
        STag,
        ETag,
        LetterOrUnderscoreOrColon,
        AttValue,
        CharRef1,
        CharRef2,
        CharRef,
        AmpRef,
        LTRef,
        GTRef,
        AposRef,
        QuoteRef,
        CharData,
        CharDataChars,
        content,
        AmpName,
        LTName,
        GTName,
        ClassNameChar,
        ClassName,
        Name,
        XMLDecl,
        XMLDeclChars,
        DocTypeDecl,
        DocTypeDeclChars,
        ClassIDAttribute,
        ObjectIDAttribute,
        ClassNameAttribute,
        TrackingAttribute,
        VersionAttribute,
        UnusedAttribute,
        Attribute,
        SignatureAttribute,
        SerializationWrapper,
        NameHead,
        NameTail,
        AttributeList,
        S;

    // XML Character classes
    chset_t
        BaseChar,
        Ideographic,
        Char,
        Letter,
        Digit,
        CombiningChar,
        Extender,
        Sch,
        NameChar;

    void init_chset();

    bool my_parse(
        IStream & is,
        const rule_t &rule_,
        const CharType delimiter = L'>'
    ) const ;
public:
    struct return_values {
        StringType object_name;
        StringType contents;
        //class_id_type class_id;
        int_least16_t class_id;
        //object_id_type object_id;
        uint_least32_t object_id;
        //version_type version;
        unsigned int version;
        tracking_type tracking_level;
        StringType class_name;
        return_values() :
            version(0),
            tracking_level(false)
        {}
    } rv;
    bool parse_start_tag(IStream & is) /*const*/;
    bool parse_end_tag(IStream & is) const;
    bool parse_string(IStream & is, StringType & s) /*const*/;
    void init(IStream & is);
    bool windup(IStream & is);
    basic_xml_grammar();
};

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_BASIC_XML_GRAMMAR_HPP

/* basic_xml_grammar.hpp
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
*/
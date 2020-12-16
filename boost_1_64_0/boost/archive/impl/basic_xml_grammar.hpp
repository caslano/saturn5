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
6m1/WsibiZs9NbHPfei8rqF4vdEZg2sWWgMePOu2+c74E5Z6BoxP6LfFjUumKcnEJDY2cXfnF+t8VBQYU9pyvaS8cleFkebNjTF7nJpzgoMev2Fta4sOu++Z9n6Ap+vETsfDsReO7kxYJMn5+vPcyzslbcOXE/zxMgUzEe48i+/2YThXsdwaWEuXXZ/Jzi6R0LvgdP+IS2NoPG+8yhr2gG63TaPiOZ9fvpTN6TjTsbaSeYGo07JSJaaUYNZNq+7UyzbmjXlq5c2+SaI9kMqx0Fpqkcb+jjuRKm/OW0oNjNzvT4hR5FnWSVwk7e+6R4XhxMc6HxML+9IsvIDSlQUtVLkPGvupr/MZ6qYFSnmNvMxYfED6yuyAqiNXy7ZPhwVjF8u1nDnx+JrN9kLzZ8Yn9RvGA61OfbLUWljIkbLdmM+xa3ZX4b1jFQ7EAcPPHl54tQOhp+OfRJrRsGDtpkxfyF/ALDzw/obF9fVPI32Zo9icNHWa79B2JoqumWBOjJuwP6v70jdJIySOnsH3odG6UReFnDmJvY8YtzfVrfblNRYYvvi66d1mOa+8Zdxu2iryZiEy/R1c5/tkhld7T92oLZws2lhndY8phy3irncZ36uZ5XX0jNVOh/WkD4rv1+xooW+oxq+tLi/OXdSwZUNMjJMKzxN3VnNt4bKmwlVJBXc58ELp27R6W2fMAmS3ptcleKRznAsJP6XeZ3rfu5K5iKE964IbPf9ZQT/vdcFSrclCq4gTpTOFn02D3t+dsE/ImTz5eWzB7K4lX7K32Ou8Hlp8VlvoPcd7R+eVaSL38pI9NRuEZpbc3xAWgLuX6OA19Nmh8Yhd2MalDMp675a+7ShdfWPQQPnijpTTNdOb+4pGjttTWb0cDuTk6HyrkpFnVjTr6h37jpWmG5tU8WyVgpX8q0LFS6N6kmGHFerf56vg1yc/usjxkFZ9eXa0T8+7Xp4dwS86+4uc2h6qLLjuU+dlPGA4tV/xSdTueqxIy8XHFyUbPT8Nh254UdcsrasQ4n7r86isRxh9VV+uf+9EobWWb25NVVqS/6IjwzHyJ7TXLGFJKFDl9XkrUbJko2DaA/qXYvGdshGBq+5VDo9fLZjiMHzpsWHUEWf1vuehxt2DAXtjs1iVDxJWHc276Ne2rkfJeyA45djgq8EIo8+xzaPGzQwvTxhotN/sbZWjoiIaFnewOC+Rwhtr+8adKJLYrBO42BG/o2mla8JJ964Yr7sfBASMvU4WhjXu3iQs2sm8pyj5yETAGwv2a4R93kMORMzy45JK7O72bRjcS+YdNNtWXMvuNDbDV75JyugbFjza1P84ZWN/yu1LeH2m9SFssjHD9x/Q9YuzGu6JEAtk6rRbblPyvmfxFVZe9TCvtKmuZRptm7Td3u0S44WPenPqrIKDFsmwfpTbN54kr8LgfXrjFqZgFtzWzB3ez8yCmCMzV6yV02RPF3IbLGhcSr9zlRDL9iA35sDoJKPGfdhF/HcsLwYuaJuRjHtHW67lUITfI3x60cp+fv9rN3WorN8OBaXdjE6ajBzC/D/9P/0//T/9P/0//ReSLw3y+p5ozUjfd4Vc//kkeYT+X2pPnpT+zf2hkyq8I8aQkjb8hayu7i7s1zysPcHF2hH/037RwtWJNJ9y0lXJ5/fzM/P5J+fvO99Ox/efbE+WnEj9KPn94/3BU3CtCUQMBp7dioEnRX+9/HH63d8fW9jjLJB/1llg/jRhI/5s/mO/qMdIupb7zNu5wxYMcg2HFxWqvIZUriT/93JqVHkDqTx789/LaVDlL0jlJbi/l9OiyntI5SnR8/Ok/jZvHOSjvscghXTP9q3ch7J/WodwIfkxwhjkGkE=
*/
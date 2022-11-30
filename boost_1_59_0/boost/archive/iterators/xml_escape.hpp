#ifndef BOOST_ARCHIVE_ITERATORS_XML_ESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_XML_ESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_escape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <boost/archive/iterators/escape.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert escapes into xml text

template<class Base>
class xml_escape
    : public escape<xml_escape<Base>, Base>
{
    friend class boost::iterator_core_access;

    typedef escape<xml_escape<Base>, Base> super_t;

public:
    char fill(const char * & bstart, const char * & bend);
    wchar_t fill(const wchar_t * & bstart, const wchar_t * & bend);

    template<class T>
    xml_escape(T start) :
        super_t(Base(static_cast< T >(start)))
    {}
    // intel 7.1 doesn't like default copy constructor
    xml_escape(const xml_escape & rhs) :
        super_t(rhs.base_reference())
    {}
};

template<class Base>
char xml_escape<Base>::fill(
    const char * & bstart,
    const char * & bend
){
    char current_value = * this->base_reference();
    switch(current_value){
    case '<':
        bstart = "&lt;";
        bend = bstart + 4;
        break;
    case '>':
        bstart = "&gt;";
        bend = bstart + 4;
        break;
    case '&':
        bstart = "&amp;";
        bend = bstart + 5;
        break;
    case '"':
        bstart = "&quot;";
        bend = bstart + 6;
        break;
    case '\'':
        bstart = "&apos;";
        bend = bstart + 6;
        break;
    default:
        return current_value;
    }
    return *bstart;
}

template<class Base>
wchar_t xml_escape<Base>::fill(
    const wchar_t * & bstart,
    const wchar_t * & bend
){
    wchar_t current_value = * this->base_reference();
    switch(current_value){
    case '<':
        bstart = L"&lt;";
        bend = bstart + 4;
        break;
    case '>':
        bstart = L"&gt;";
        bend = bstart + 4;
        break;
    case '&':
        bstart = L"&amp;";
        bend = bstart + 5;
        break;
    case '"':
        bstart = L"&quot;";
        bend = bstart + 6;
        break;
    case '\'':
        bstart = L"&apos;";
        bend = bstart + 6;
        break;
    default:
        return current_value;
    }
    return *bstart;
}

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_XML_ESCAPE_HPP

/* xml_escape.hpp
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
*/
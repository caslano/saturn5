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
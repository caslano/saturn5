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
+4M9tsScQwgTFM72iUQSuJ4vtk2y9bWApCzDKVA/JzjWYMu5YT+yvN4MD7Ms+Tp4XoQng9vN307EvIxZqphV3M5IEUf08t8DKMNTy0K05NDcOcytcTxjbc4PBw8m60fALukSw1vh+GXs5ULGV6JnRIn7RkI1fm58IrTSC3xbOcbrELcuh8+UbpMKAMXNvJUH4L5/g8cDDivO37Bp9eSg5XcUZq7e8SQSsasYeAQvV+2ozuUPj+4o5upzL78lEBpxZqKLdGp9JsVuXlmO495eDg6Dfg55iWBqGvNBUkdd/SMMSB9HuMbtUdboTqRRpeoJoqN63KlcuLrhSMXsdZo6h3DywCcXPH5CgtYhKIa602PCDb0zemJ4BbtFMl7s+rHQMrgAMwBOI0tIg5gfFEqhqpA2SDRGrlXnnT98cxJCJ27NSjoXXEM8PeiHuPAmDrUKpHwX3oqhYe0DoVICnoUqVS7pJeaIy3UCalI8BPuvklgFARfMWpPXLA202nclNggB3IGWXjLKrWbjWcfrpJCr9+9AxIXNJlAsrJYj27qySO9X4vhfT8EZd/ZfCQ==
*/
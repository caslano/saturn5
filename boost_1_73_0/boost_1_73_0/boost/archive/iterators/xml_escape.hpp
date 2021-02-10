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
SlNnrfuU0iZ1hvz7yeNHk28gYoeByWQbhCmWdq5ztKPUUIUilbE2lOfI7h4xq9Bj6ENdv5aXWXaylRaYsKa5sks7TaJBcbYy0ffDJdXB9zZ+Mn8N4BraW5nKLDyJHbKMAkLKJBRMdqMq1F2Tfz3dTSVBnLuxA3y2BAq0EE+UKMznZCWN2u6D5tJFqhmEViSOK0mJEzmDdnsfdzPyKom9PapCVsOoJ/q1n1qnNfA7vf4tRT1Y8Vtt/dmQ5MQcq4FLWQP0KlECs9DqSVNU07MxmKFKJqgA663fVqnyDSpu3MeTH7UVkgzGCqD8GQ8yCnpprLZGDJ3HEG+ro6rnpmDQ48DMvpmq6+utBqmnKE85iWf7RI16P25ZhnXrPitb1bEZDx6m49c0OUPrBQoek5i255+e/MgRprmdSUfaImgcC3QK+lQWDh6p8QUwFjAz3QgZC+LCPIgnP0In8HH7JK/PU30J9MFT6kMPHisNT3WU0AY5BUTaudvg4RY8HRcpZOKpYqaoM99Rn0CL1QCFrzHNrxUAGK0NzTrsgbtd/MaBUX6UQUYH3o8r0lXw29qHSGtuMybIkqxNCSgLx5ugAIeYstWPy/1nwayJqB08lNozRfQu7hq+XVurFN2vlV20vBwtAK1gVqi2lshIk0nU
*/
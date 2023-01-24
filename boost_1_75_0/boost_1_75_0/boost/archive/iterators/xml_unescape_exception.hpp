#ifndef BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_EXCEPTION_HPP
#define BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_unescape_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTIONS
#include <exception>

#include <boost/assert.hpp>

namespace boost {
namespace archive {
namespace iterators {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by xml_unescapes
//
class xml_unescape_exception : public std::exception
{
public:
    xml_unescape_exception()
    {}

    virtual const char *what( ) const throw( )
    {
        return "xml contained un-recognized escape code";
    }
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif //BOOST_NO_EXCEPTIONS
#endif //BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_EXCEPTION_HPP

/* xml_unescape_exception.hpp
JvAen5ggrbboQii1/QIJcUKlHk9vR3lUxish9b6AZ0l0mzd2bHWCCJJvRx09/eZxnU6qM+qDHh/DoCSQEu/+AKZkBrT3bzTLC5NjZKqy1MhHhAm4Dab5QSpfysXci/bbikYYA3NDI645k9yNpAskvAnQVQkSHTvpQtl2SVTZFycmBjzcroxQAXR1FrqS6n064Xq+3CdMR4HvX1chaaEjzEPATUNeDe6gZxm7Yfn8MZ0OrWXr9LD7qk0q6WLWZLE8hR15ikevugJPcX+8usGlfidTKhhLGjvMDduYnsanE+0Ix4PfhaMPS6i3MBFYMIS3l97LyvXGlOsNrYyZePE6kg8LsWyXMTr52x7De00aPKJT168RZPwKFLm/C/17k68A/Uvct6CHDehlgLMJ/P3k706gj0Ht8vjKVaD3TP4u0Clw6MM0XgGKu68ExYwRKJKYnW/aRZDiXdUOcZosng26z6lBe7po9VuA3dUO4YJc4ZMfRS+4WjugCRx4FtKZ1gxHe6BuANkjsmC8iZjGr8Wt6h0IiAOBOvrSSy+t5XPSxXh+cSrgYbURB9g5G7kudz8wtunETSvKgZdjS68S/KjVcWOP8JCq9DIyt4lJJNdSpNp5AFKG0aCxzCQ9aNFJg3o10kWuYxfQ3CS8KA/pBPticXqlHs7XWpNSAzi2CR1cOrCQMTSOpYxgnfHbMxZvgWPFPnqs4NTRf8apM4b0
*/
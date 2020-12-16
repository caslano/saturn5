#ifndef BOOST_ARCHIVE_XML_ARCHIVE_EXCEPTION_HPP
#define BOOST_ARCHIVE_XML_ARCHIVE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_archive_exception.hpp:

// (C) Copyright 2007 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <exception>
#include <boost/assert.hpp>

#include <boost/config.hpp>
#include <boost/archive/detail/decl.hpp>
#include <boost/archive/archive_exception.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by xml archives
//
class BOOST_SYMBOL_VISIBLE xml_archive_exception :
    public virtual boost::archive::archive_exception
{
public:
    typedef enum {
        xml_archive_parsing_error,    // see save_register
        xml_archive_tag_mismatch,
        xml_archive_tag_name_error
    } exception_code;
    BOOST_ARCHIVE_DECL xml_archive_exception(
        exception_code c,
        const char * e1 = NULL,
        const char * e2 = NULL
    );
    BOOST_ARCHIVE_DECL xml_archive_exception(xml_archive_exception const &) ;
    virtual BOOST_ARCHIVE_DECL ~xml_archive_exception() BOOST_NOEXCEPT_OR_NOTHROW ;
};

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_XML_ARCHIVE_ARCHIVE_EXCEPTION_HPP

/* xml_archive_exception.hpp
b7/rWlrLzQQpN5OO/OSSdrkv+2Tg2y+7VyDfTHwg30wlvpm8lptxU24Btkv1qtFeevxthSkKKcE4VII9R7siaRhHJvUu/8J8wIx67m/d9q16fNtBdNvmT00GXeeLs+HTdXXwd1QpCpPCEJ4oHcIXZC0uDEMYtiFyhFre8XDGYSTX9REe26T1f18Fecexzr8jHmYQb6/52QvCbVeO2DGA50izSieUwvGQa+gNfcsEsHIJXUKcgOVbqL/cJ6XAnjigfrUydacwJ9f1IzqN2MM3txRpz+myP1Ip/HmFLIrSk2dTJSJGqP5FOcQ+GojNLUcyBQ5/uxzzcZkpxWCyn7iZSvIRe+KicnRzoTpyEgn77zPcaKhPO6hcFAabpRyXqJNSdwZRjbjZsNJhnBD6lqiLEyQKTVK4lJeuRm/8IEs4xTGF0lKv++jq6zQ7gl28w2PdaUWdD9pdDsA8Xfep4bGOh8JhbLm4Tgp110MN5KaTdC4Oifp6qSOdQg2JfhmYPJeYRFm/70hScqiRkKR0Gewif9MjN71DYlQAdxpu73Szpwi9j2bhuwlgG0THstS1TlLKP3kPKwtKWiJoY7UMNVmC9vZPyNRrNnv0RFsZ+bBGApO9yS7j2QfaJ7m2SMdZXjUF0woKydNW0XORXfMzyI41EjKcZQccbLLjZD7UxsFibl+oW6dDRBZ5Wad/YwvFRFJC+WTfI3zgLDv/EZndfz9Ncc3LadAB3MaF5hM+PHeRvlRC50Q9SqM8hOepRhY0vOSNf7BAaanRJMxRYfzyHNXNTqyjE/qUoaRPiTBbBMiPrWv/Slsuu4qJsF7g372BYuv2Oc35lb/lnNXyaxx98J7wjCpDZBYW8CH5vf291WxXZ6D5m3GIrWlrgpOi1ZfoG6CZjAexdJflCXrLhcVBHqQXNAvPMH3Wh/UwlufVHjaICOapgWFIEQp3LHlHHlBTa2ZuFH1lvqnKmNVHzbU/5euTV3yyayQYadQGwTUp2E4ED8i4B0uzhx3dVQyctM9wvWEloISRgTQCFDMYr+O/rPHiv5kQs8IzNXn5u/R+XF6PVISbzzmK3xR2Gn+T1Uuo8UclUDZrCOqWtFPN+0WvMf4d5hvwOHygEFIwVOfpYzRFjtP3Udfvw+MMz3vTH3evqDpMZY84QaXOJ7JdWKV9mh067Fva2kfvkIqf3CiExbof1qPPSVu++UjN3MPqJY50lRqhWQirlzASjcg+v4xrqIQzTomXaBhfRjWJfrkCSif8tWdGfZKOfpwTdWbWBXl8vBGTPfFG3KZfgrmFmdph+FaJ6vD++VMDZyJWNetChOP0U5GeszD1HGoP/MmZSaCJyz7YF9Res+c14mhA/bX5kQi3wIf1ZJLUldR0Lz3xLdXw3h8ev9WlKfeeYm89mNA/ov+LEg9Sj0LqeB2c+rG6b6XuAuNYxlVILBQaUoxPINY4DYcfYNMzGm+NNq99dt7EzXqSJQ4bzdUhKc6PvAKGF3YRrrn9dLmOARip5VtR0EBsF+0XcmNQS5OswJo/Phxq93bOH9aBYLkNPTaxyw0wnbBPtHlQTGFpJaTQLXjq52nD46AddobALXVoZbfrTmeK+3k1WR5bhiA7OnTdTZdGtJT3YkKMvAaVXnYZx3V0hoGpHDaNlIkevMtfBTk5mU/3RXxIFMdXmUrbyHhQV7ApEqVucFANeucjxsJ6zXSTZkZ/KBrkqbFCKYudL6E6QOs/aQqnBMGlCL3fqV9zOxpvL8ZsTGkmdRiS+8AOPPrfvwOPcH/xuYqmPmjWY0l9OoBsQ0PvTjNOOqPLp96HEPmnzbifWTl4qgGGwB4IsTc/0g74nskdRsDb8SO8QT9D61asAV0=
*/
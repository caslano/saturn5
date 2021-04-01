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
bWvI5kPE1Qv+8COrHI0X3XhK7BkGKAyq5k3pUTpYTcrgXECqom6w6ndQ7VbVHQ6Zz9nuN4VMT1ITx2axgJtldvsbjV4JBL3nJ+bC27hwIvGso1LFfdOGZr6AayuYQVeiqkgpLUTX6eqSOZkswHz/rt/FrBGd4JwDxHvOOzk4zctDgFJVzPSGiw49fbNBJCaTkuKqhSphu5pAWa+Ut8xn19WhOUs0ZM23i79y6i0+dRPS8zTZUs5xIzdISi2yzY5Iwb+FEBk8ktnb5+3SaLJm7n6SKg8BTDrS8z4wnYOrffvFNrL4Nq3h8S0iMH7mEYzqcgHxZMRIwqHnpPsAvGr8bD1p5lmEAYdUPoH+c28RISoeI236aqNH7Zcb5tqurgl5wYJUGiy87I9mRrg7zy96/Wjx8g8q0H7uhQ6JSOuhFU48MQVKtMTF7uQnbBEfrpE9B5UhXaFbXuBnQiV1nwsFQwtWS1v0u+S3D/WrWGKIA8GVCh2r1acWnJhVW7gdKU0PAnDUqucK6/Pu6mcU3SScryDd5YsdtIk5gglVttVx8w7XuXJFAOrcNE9YiQ==
*/
#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/text_wiarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_wiarchive :
    public detail::polymorphic_iarchive_route<text_wiarchive>
{
public:
    polymorphic_text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<text_wiarchive>(is, flags)
    {}
    ~polymorphic_text_wiarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_wiarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP


/* polymorphic_text_wiarchive.hpp
jVq0ujE/Fa4Npg1+oTpte6/CUgelozGPjaZXwdQ1XxhV1BZrVXAwtXR1qXRb8kW7+9abtvQq18UTnjpvsFxeJ2uuVX7IvflzwGLY6fnLBz8tg1eqdI22rRf7nQ5LryrXq/XSFst4VIpjbXoaDtnr4IzFsl598MZ7iyPThg+jjU1nC13XG1kM2w8uAAa8jbHA2rjTekEwbeRfFVeGXre+1sGUdBwx6Druznu3Rqjqz8EGP1Ouh61dl3Fg+zGoV45xyUYt9QquP3e214EvS9jHDhyYzh9tRaTXtq7xNw7k00bptd68QQLojNBO20JE8c6EeVz6RS2NLnEKAY+7xjzHtPntrpc75LwLJEcrLNuo2rUPKtjGzGSxa4Gx70zBsGrk1OL1kg47NfidRGqfcHe9fbAt0Pz+qwm+0J2J+6veNer47OzT/35YhtD5L4eHxdDXmTeHfVUcRkN/cGm2DE19II5dturk6Ph4pr7fXnw9PTn9cbt5vV5n1oQqQ/LFAv5xRRaew4H4U9GNegMz3ZDX1i9NJHxpgraoCIYx+e/6J4HItlI7WTr6dIYtauiYySmFuixhyg9d5/ogzO56U9nniAMWfO9616F0yq27wbnabx1miIdlD2rM+WzOZbn18+jPfLQ3Pzo6mPFEuG3F
*/
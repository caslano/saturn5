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
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
*/
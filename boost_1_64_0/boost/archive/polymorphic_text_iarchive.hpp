#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_iarchive :
    public detail::polymorphic_iarchive_route<text_iarchive>
{
public:
    polymorphic_text_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<text_iarchive>(is, flags)
    {}
    ~polymorphic_text_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_IARCHIVE_HPP


/* polymorphic_text_iarchive.hpp
BvIr83LBdEnE5Yk8B6SVM4Nr139Mhx0M6jHe8ZNBp4lQUfkdhYY+YlPXQcK0ewLbsSUGIsG+JV5pKcsCUJKr4jhh/inrDpIPRToX0eEzA2OEOL6GZZBwG5Gkn1ZS0Nrks7cfIjx+lkBox8gGOrXymerI2j4BABRNILL34WvdgZV3cY7dIuo35e7uMwBzr2ufwLEKl3aVH0FPihG8nBqYj04uvXTwL2UAWICg0TvbeCbgybn8sZ6dNTdLvHs8VyE58a/R6rfk/1zeupYUYDlmNahaNFbepzUNUNEYOfeHzlDV1ZC9CKcLyzc5X3al0k7Lx3N9+fGCCASxdLMtZcbn5m8wvhQu8iM0ZGoeS9tEVVytH6x7JoL3feH/y+kpnW/oZS7q6tHcWnJ2DPquWQol9e2IQzWjPpj3Z9Y0OFb0SStJqAtXErqZoinnL8Q2CyI7FxwJDiz+bz4W07HU8YsfQcKH4937e7fWm/6hr6NBnvEbrE1bx7Qhh+oMEglWi3vQ1sVMRLkyw6BLcfgPUBZgaQSHiVq2MwDgsqnTlk5Onb26CK0w8caC8oGtDQ==
*/
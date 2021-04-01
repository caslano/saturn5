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
M1ZEQN91bp0DemhgV0o3LPeIhCPXk4kJdakJmV41iQSpnOElxqfVJ4Wl6mDQwj7vRGRcbqZjwfz+rsa/8ZTHW6FnOdHeSiWuYMi0xNQuRThL5X4Nb6iksseX6TL7etbdPCoypyBKFW4Brs2vErZTsjv3cB43BrKEkAyxASdpmTyMpcKiI3kNV4u5jorpCQ+9xX6rdj1JNAROUNLTZ5f/h8D67kToFxadK/rR9Bomy5qCHfE53BdDwGQKHVfHbriRtr6Z2tfKMrRdm126BZe1g7usYqESPpSs4EqBOFun9W1pbny1MC+7wQLUAYKKTciR9WpsXjShWEJ1twIR0B4TIfonpIKlpcM8FmR3yiTk5C7OrQeFkUwch0DY2Etao8Givt2iAo0iShCTlsP+7ukVcOjb7EpqCGv9DCygLIw6BhTEn3dP21cShwFtu0AURvVDSHx/FQwwEowOZffedTz0F25CAA9sqRw+1aigssqExlXjD3Kt8VVb+l+bDdUxl8iRD6F63v3VBdhz7kpAI0bSj2AxL3qCGtLDoVUMeuvbywX/B64ir6WKsdzEqw==
*/
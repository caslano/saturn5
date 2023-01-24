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
FlcbDKoYCGgSFkQHWzmG0ncetn8opuNqsMnAfwa0Yw7Egz3oDqWnLtOWUohpKD8ZLKbr1FIMeFvHji/FRwSWGvAcDoTTa0Q+YdndiHpNR7FZQ7F5KQ5O7oFe3QGAaWjyNDQLtB5eR4pmUoax+fDrPU0hISVna9AG8fMklxF+8R5golU6YHSwMWNExlEXKG38bvld6MkoT5J7JcntkyRX+lPgwdQUgNE2AVOXMDXqKeHoKlfZrTbi2UuNNduwQTylulpIC2zkIgogDJoZtDEKjQStJoqeUWb/BZhYBXlvZj4AyrbMB2tmxcq8FRGLF662g9W0cOXCZQtWryYbaKF4jJe1YOFiyi9eYV8eYVCmmDIVozrf9FBpuc2cyf8Nc+k2coy7nS2TwV7HhkAmdrTcBldhHatYCB2KadsJrARexfeT70F+NdFrnhZPt2J4Pj7qsYe04F/dtA25IoBuZKW8BNgpT02ShyfZD96b0pCGqyz7SkBAGPBnTKpVtHLn1zEOXh05enX0xUtP3nsDvQkCkDYd7IGujSrH017+wBP4cPmXAtRijznYdPnBJDkCpmW6iiEJdGYuKwRmrgWMvAqqagV8MD5e9fFhQJ4/Hw485uND9npoy1/q2khXtJA6MgaROuLryYTeslpeNHLkCvuyZTnyqnmyYcuAAQZd6QRhnx90ocYJ0Ja0BQsNRs+H/7FLIykjEo/aQqSDsS8K
*/
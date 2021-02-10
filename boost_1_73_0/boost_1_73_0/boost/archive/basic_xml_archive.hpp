#ifndef BOOST_ARCHIVE_BASIC_XML_TEXT_ARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_XML_TEXT_ARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_archive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/archive/archive_exception.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

// constant strings used in xml i/o

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_OBJECT_ID();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_OBJECT_REFERENCE();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_CLASS_ID();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_CLASS_ID_REFERENCE();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_CLASS_NAME();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_TRACKING();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_VERSION();

extern
BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_XML_SIGNATURE();

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_XML_TEXT_ARCHIVE_HPP


/* basic_xml_archive.hpp
mrcTnZWDtJyEFM5IjpY5OoB2k22vqezeRPfg3UXaSb0K4tWTG2bpvUXjj3vjZHYSnKzsUt2GIc1mMJXhSoiUJMV7C1BMzBgWZXP5JndBxasf3e8L/Gefgm83KilLYNfLB+phlOgSze/QXzURehGlt3Bxs80B27yZ2ObebHeikWGhrhV9QCly8jGBEZcJyjBtvCIodkXs7LAbdLnnEL0cyZ/pXorKT/OSb58qKJU01TOVNV2dCW9Iu8VQky/hhrdgbKsLx6tchbCTohZtf6XLANR5OYL85VqEuDPYRW5pooctoiQG38pc/OTexo4MNiaimzXnuruwje/JeL20HJWY0uO7ztMMZA4B5LxcxvJTzXiR0BJY23EYAlMTFbD2ZZFtG0zd/vBjOhwOdH8rjVw5Fa+nxAs2nK6qEC5nN84kUqxJyDilDjdjH1zrjEPUEHrh8eqA41WCDlFMb+e76SUy5k8I2QR9gJPA3jfGPgSvt2E7AciOFJ3p5VTCvafgg3U7FJgMgzucC9VshbagGTEaDwO2JR9hshBA8idkEwHk2OMH86rkbnCWnZDoQ5BE7H0rJkNCfb17DYsIXfZa0XrIrs+r2o+ZLbHc3rE4gbCvZKr5pYilTXF/o7T76xc05uNNglolNwgh9kmuEW5V
*/
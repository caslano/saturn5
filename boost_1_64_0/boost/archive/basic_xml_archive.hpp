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
atqrToyZlHslHOLRdhkU3D6X0O9rymynVP79IHE598ueOl6XpDBv6P6W0qcwlwiRpjS2cxyr/ED+upe8C/uUs99OuSJoVLWTl3SxLCkML/GFBLucOluJAnP7NNHfbM9iwJtUqOskGiTZZNC6RHQz9SduxW9ovvStyJovrZhfF3uqudgGSoV47SW8AC3FzKlJRdZl2UlA71bzB2ytv9n9VZklOcOCsHHmknzPv2kE+Q/IktxUh5Zktj6wxa8yGL+w+bU5P5u7muJnXTunGOb7rzV3Z3qG6Are2snkoYfkT1PiwHZhPIYXamMMfwIO7h6lTwMvk8lC5ILISKSG4ZVCNhvEywElj3gE9z/vNgCaUVCC+w0aAvGioY5i3ydj4x9BTxZm5Ax2+Rev+yUf+/fkbV0slntY9dw+dTALgYThk+KU9wU2jJpEsLPrBNVs/MzK312LKKVeTrws64UdSylxZK1u+RXYpYdruaDnsNW94OIwsfh7oYo5r7Mlwv28K6Ug0Z6Aduc1YJbWSSO/rJ/kYUdg38/4lSYrZe3TicHRt3Y2OO+lU033oX2QA+rdS4w3OFWm3+tJEK6/HyLC4aFp1RThAJK+00XMPTe8yOCeqzYV7vk7VIPZ04V7Rr5wz83py4YMra/JB196keKDN9Ym7tmaVd3ImktZb1qzztZQWc9S1uOkSG/lnodUsOGe19dQ3HOG5rbhnl+IuyDuGU9WZo3P17Byz8BRbEI3kgUHzEcPB34x+ec/A9qef54P8a3B/xL5rRjgEPxzxfgpFeOZf15t8s/Cf4N/Vuw388+Rz/cg/tlp5Z816aMxim0JGEU34aMX4DuSllJSSyRlam4rHz0vKTj4fxBMNGD4UY4ey7THZPeAG+5+FXPDtM0GLxtRJcHxMv4W4W8q/o7hbyb+tuOvftUER69q/1n0iJJ/Jwfl6/3ibd5/Lfl7I23k/5b85Awb+b8l//JKNvJ/S/6WOBv5f0fL+79N+9ss+Udt9As+suTnX2Tz/m3JH+0plZ/M45f8TG1VUMSMUIubIam8FXJQEjgy/rLnh2ripVTxQa2kogwl0T+q76ts3kZtvJADVReOIItZofsMbiWikQrbKMQMrpYbl4n2nooxBWMyt7ZbvzKCSYGu4uL/H9i4XrzFms78P0N/53dn0Sth7nbkd/9tiIvEr39MBNMGFG+WrzQVB8raJk7VzHPFAT23Fcttd6z71R97/VKZrEAHNVlj4jFhGdqfXTJpxDc2wmQdqSqTdYQnK52YRvCO+nbw50Vn5Dl8RhXh2ce2Ymm1C8GSinIl62GVNVSyInM9Uewc/XaVnmGmh/lvQPqGqpLezkx3+dOJF1Tptcz0aH9rpL+l0p1megQ7fH9FpRe15PSGSavJV0+atlqcnm6AOhjPAt3GY3Cr+Tvk+xSVEi5USgl6mKYtze35ru6vT0u8jH26G6+6d2WG4ql+C6XWn/Eh/99Vy/j/Vr/t7XViL1P2OjthrwOCBuN1ATuTqgbGCbK1diO2q2hL/j+QWQGZKseBnN/a7Ab9fbZM/09Zf3MwwYEc/yXJeEPcQStcSI//8kHsH/2IhxbqazrnLYl/qSZb9xRx/q9a5BK166mXm4H0lMyHfCReVuiEjKaHhAlK5b0P2Vp46OynkmPgTIe8I7zI1E3XAbEudV+r0F6vim+2czWCD3i3NfeL5cFBfx31OPcNsvW+nB43OTEcvRrhJC2JpALrfa2UKaKhTFEoyhQuny4qHW87pWxEmGzYGmGmM+BXLU6HT2KC9MRL0CVUjt9aDHlND0cPcmPKuAO+WSU0A6hyB/x4T0wR2Y6MxDmgViOPF6Mm5aA6LVyI9C7hElULs6Q=
*/
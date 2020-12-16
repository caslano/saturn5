#ifndef BOOST_ARCHIVE_BASIC_TEXT_IARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these ar templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// note the fact that on libraries without wide characters, ostream is
// is not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_istream<IStream::char_type> but rather
// use two template parameters

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/archive/detail/common_iarchive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_text_iarchive - read serialized objects from a input text stream
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_text_iarchive :
    public detail::common_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_iarchive<Archive>;
    #else
        friend class detail::interface_iarchive<Archive>;
    #endif
#endif
    // intermediate level to support override of operators
    // fot templates in the absence of partial function
    // template ordering
    typedef detail::common_iarchive<Archive> detail_common_iarchive;
    template<class T>
    void load_override(T & t){
        this->detail_common_iarchive::load_override(t);
    }
    // text file don't include the optional information
    void load_override(class_id_optional_type & /*t*/){}

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(class_name_type & t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init(void);

    basic_text_iarchive(unsigned int flags) :
        detail::common_iarchive<Archive>(flags)
    {}
    ~basic_text_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_IARCHIVE_HPP

/* basic_text_iarchive.hpp
pWSjCDl7MAc3b+X/P5V9rFq1Y3LC/pyPM5E4mzC+7Qr3yEb0hYjFSQLs94SIoQ/Lc5reXf3eZbH0H3eAI+jQU3yqvugaPoJxULzhEXJHMk26n8h5EZcvGruiieLGWc4/9P1kv2Agk/gsyTmTsAxfiC2o5Z59E4Xprr0CbMHyQBmxRccreYzQukkADuWNQn8WQyLtBzme6qBfePx4+gGId6Pr/KYstCQw6OlZJJzaR9n/P6JW6pmJ8mTHLHkbjLPKeJfvPFLRP1jDwnZOO59fV+hHrhd7Vaia1aGFehALQnqxrMKzPmV5pB+v93CKnZYfr/RuJMnjGFgOY5DxB5eYkrxevt6Hsgy3jUy3BUFXicstDis42clnPlMFnxhv5NJTL15XMrQf9XOvFxS8G2Bj1fkVeDys0TgE6RqhxuV8XD3IVP9mFlWlMxVcSlTwe+UXp7Nky8mRHAGor1JQFwqUHB3gyilvpsqry3mr9ILr+L2nkC7c4mPywIjyQbk0F46zy/k428B414Ub6xLu1V2qzlkOa68iAPWrFBTsUKy9akN5Z8m2GAidOosc7cw1TiLUNUKlZV2xQ1RmulhJ/rSaKXsGJpLifhVfq+J+vRJWzsAKgF6LTIjVODU83hG13jeEqTV7I4cQjnbY56RdvZIL/qu0Oqv/sbdH6PaQoGrvGAgty7C3xMcrjvCenrYLh91BwY4lovhCfS5wQruRBboXFLnonYzE0SzU1WJDyyDVnZg+8oC/BiS7jVKDsa5Gqd7ekN+mu2dvzOqNaa9TQx+CKmR+YlIWnp5lFNsjiCmC3DefelD8WB0t7Pc560d9q3wC1SFfL/vasj0N7lCT5d2xTwbfoY5k4g61GQ98sC0g0ydab7yG5wcdwo3l13LSS9gr6v1TCrk6oNDrKESRqVdBMQFmvvLSL9e09wXaKdB3ELSf3xAXOJyKyfuO6c0a/eRNTJdaE9UaAMpUyk60L8Q/YHzB69NYFjmPfWzfnKrphPwfyiUw+LXcFptfGeS/j6eZ3mzupfia7eWF/eM4LNSblhf2hyGXkFbqsz+5st5UX9qAVOr5q9Lzju25591pcuZBWMZddmP/SFzAUJkH3zF0Jk2kefrE1aJ5WjgFA2R7d9H2h4WvdWJKpHq9HVfvoep7+GlixtDE6Ie78mSk0AqMXAI2uHoT8hIguQqhpJjG1bghfZ8m1DLEB7Zh/zTEvN/5G4rV02dpbPW0o2wTALnlG60tXxqt5T8Asuxlea2/cx9CtT37J3b6Q7eOAar9YdI+6DV1YH2eOVzmG47pW9LNFGiTfoh8ZfGRXxNJHF8pFXTzJafq3XvO6vYu34k0UkDHQtAi7UpV6sH0ypudH6IVOSgrcquHV2Q61l1fMcDsEPNS1zn5xvl6qoynNa+wMeGk/58XntN2KlpjfDp7epaVPOGobo/XO8yVxMpclsorM6FsPoGiBU8gDTMxTrHvcD+dkwcHSpEiFxdELsxbLasGb3WTy0c81XXH2ELyEo6PU52+5rQK1oOmhVrVd6/kZadDJO8qdYjUxiSXDcH/Ug7IyUGea64Tr4a52hIym+nFin53/ce+4fw3fZT/j36Gv8/5VxvxH3Kj+f8w4X824J+JBn++Cb8/TcHfHQ3+yH1m/AoD/rLcKuOz8NE8V4p6lLbvOuW1fhAdaTlkCfCQVhO/W1KYkT7EDAmP5NNWED9VlxE650aTl2paDkQ/8CPnt6JUJIGRojPkC0ltbOtx5LTY48re//sa/lbrGPNzDCdl5fJ/E96cz2XR4P0m/DWpCn5iNPhME/7FqxR8P8BXg58K2444pQ6sF2tqL/Npeob2E06Eu1OEgtIr9lgiHKv0xag=
*/
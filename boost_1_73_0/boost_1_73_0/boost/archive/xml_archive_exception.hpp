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
lNUDUyXhfDamDfh3xpjiJfzFzDLjTwgudGSZwUYPym4wVqpq2i2GSM42zYqj/gw3D/fQuwDHK5QMHVjcFejZdi8LWsCKr4h3og7kk0RSMeYRmaeBCTm4DBusdRdy6nZN5PoePko1UxlcW8n7TYQNpSagd5GSC4c/z4aUfHyzXPL+kNcL7cblIKaUp8UyBcS6bLXydF6LrDknIrlThtqhP5Xt8lKg1SsszBZob5oG5PO1AAFtnEX4Twizi54iz++PH96v3r67+fX99Unb6n5TTz9lG5Nk/dT3dMLNHzZugtu2PaqUA5OoDTHLl5L7VXleXbL5XECpa5LKMDH3f/CLf3k8g/78dbEsgFgs/ecteaMNo2OcwmlbMl//UNnsKPw4247qCfkWpvacWspy31plzOHFnDBuB0baqg6KxA0Riwwm8U8jglJE04MPbsvqZUdTHZoBFXdmLJdZw76wCaiRtqzR2U7UJsxJ1EVp/oDc93gJo2PZTMo8qeaMbkP65ChJHkS85OvxznZSGgeSxEonfmuchehRU0+a7Xyu3e9ykuURKPPXybVInqhGhJ06HDNo12GFVYQyC4N1ZkgU+7mgQtcxaIQzbVBZPsj+HCzHvd4qk7HxigIPhbFOHm4KGlldkaTtRfBzKz1ZvgnB
*/
#ifndef BOOST_ARCHIVE_BASIC_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

//////////////////////////////////////////////////////////////////////
// class basic_xml_oarchive - write serialized objects to a xml output stream
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_xml_oarchive :
    public detail::common_oarchive<Archive>
{
    // special stuff for xml output
    unsigned int depth;
    bool pending_preamble;
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
#endif
    bool indent_next;
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    indent();
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    windup();
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    write_attribute(
        const char *attribute_name,
        int t,
        const char *conjunction = "=\""
    );
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    write_attribute(
        const char *attribute_name,
        const char *key
    );
    // helpers used below
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_start(const char *name);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_end(const char *name);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    end_preamble();

    // Anything not an attribute and not a name-value pair is an
    // error and should be trapped here.
    template<class T>
    void save_override(T & t)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((serialization::is_wrapper< T >));
        this->detail_common_oarchive::save_override(t);
    }

    // special treatment for name-value pairs.
    typedef detail::common_oarchive<Archive> detail_common_oarchive;
    template<class T>
    void save_override(
        const ::boost::serialization::nvp< T > & t
    ){
        this->This()->save_start(t.name());
        this->detail_common_oarchive::save_override(t.const_value());
        this->This()->save_end(t.name());
    }

    // specific overrides for attributes - not name value pairs so we
    // want to trap them before the above "fall through"
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const class_id_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const class_id_optional_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const class_id_reference_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const object_id_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const object_reference_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const version_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const class_name_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save_override(const tracking_type & t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_xml_oarchive(unsigned int flags);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_xml_oarchive();
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_XML_OARCHIVE_HPP

/* basic_xml_oarchive.hpp
cV/IITbLLAxS6JpsvI0dceTrhRAxnf4bMXtLdGL+8CwecUcytKlip/eqqCvO2AZrBKGcxfpwh/w33HN8uO3t+WhAbosUFNNFI7eLmP1xTRbtxO/ZB4Us5t0pi4v+R36fcutD/HCrLofs5p47JdBu9hb5s2DqjBbL+p/5jb65SE+XnLataD7RwpVcD2zFDVQQdhl6RnMqJEchKjzxFgxcksZ2H9AvYxq8Fe/lU6epu7FNdGka7Cu/c2mUyh0oElZvfGNa10dydoGEh9aFFVwm1Dyp6m4T/IDbeIpieCsefHXeSRDPX/qdcCHHVtK6JxeStELhftRhBnQ1ejfSO4bmwSoC4ww3wdy0bbCvKe4B6iD0cREZeoy3z4nkPIBn+f2QJbTA4tlNvKazuroolYNxahLe41T0HmGfaL2KvMeNUwFuiwBpOWMfRg7kaIztsLdcqQJXI/okuI+KpxpoKQPP60CIGXhyrcHnRnY06epUcjWRT9lbrJ5XyKc0kdSEO0oD+L8QUEYvF5NNmh/3dZN4uTjOB3hae7k4XKHtkKJNP0QvGEc1CudO62sYnvH3HMXNynMG/vK+WxrvZDghsWXCrgvDC7a3gUQFUQ9sxiG5VHv/bAx2xIo/FvfgaWDJeWszhnQ9pU0oVYoutaaxVpvoswlbBiiGLvb2ykFbhNt1DqrNAuTFE9rC5p4Vd0Jyvonr7iUskPZW2QZjKZ5M
*/
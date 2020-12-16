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
sMuuDufDLo250vGXfsJ4o2H+K+pItpEjOTmSjuQEHMkX9fnxOJLse7smEBd18o6a4k8lkfTpskwz2HcM1WaPCueOg2z+ME+y5w+L9f5bfJT9RyODvlkUps5X706h/F8AXvnLNuCnfRuCfko3619nwB9ODlF/glm/16ngE0PVv7+hUX9dA36qff3lnorekqIZWhFkauLnMas29DdjKDBfFQSYdhm+gMjq904seZl3GjT6CBrVL0kmIoJBPyfSmi2N18r5rBHO53N8JOCWMqNaKRyOGXQdry44AtRCjocakoLPKXtM3G8OFGQjz086mi9MPlYXyGlGz8v+K+idBVBSRJ/ZMajE0A12vnoaEJTIChLBXQuFkYg08SF+GxLicH45+X2nKDIETW+7OYRe+HBfceDXelb7ZR/T/3MDw/uJ+FtW5jvGQh1GgHqXuD4IeDp19g3ArBwNIB7ZlMtNbwOJnk6jXbQob8miTHTyonyAtdFbgybTdzDhVUE99fkqKQ8D0hIycjrhn06dUuOmF2qFnPXzbYiM8STVt4wnqwHxUUvY9UVWJVoZfS7/MAcq2OUCmlO1OWnAkcTmgQiUl8sKtH+juB52sR26f0/VK9e/l0ss/Zte8gv7V1a+2cJo6LRqayT8V+JuwMoiRHY7XJIYRzdH1lUyDjWqTkSuLT1azN61eAsPkK1dMYJlnrXKMqP69+FMYlZFh+0kodz/nysMPb//p0vs/JFOwJtg+fkGrSLi/fpSCG4j2Ah6D3kirQhbJZJS842SifD3k+4JI5G2XwiUm/EDV3I86zgc4bTJfZDGPGKGxtbmQ4hNHEEkSzP2ZwDxaLp2Mo1eSdza4XTtsDt3sFOvixrFkeEGkZcNOxftIH73OA5RHJtZxGXAWegsFR19mVNII11TCR9wQhytYHWObBrbeasv1qvdA+6D2VYAU2Y1MxMM/20uf3ia5qe79/li7v7jdZ0ipEXSudam60H065z0a+1Z7tcg6tco1sn52CXeD30XwWFN3ORK/OsghK74UvShg7ul7zsu3TzsUP3eqhK+4oTHqQ45Nr7KXM1KpUbUoVNNX7tsTBZc5pCcmDxwzHZaPD5L2aQATShq8GpAymFJAaXI4oslZH0ljbxlp1q+S9PxK57zQCUOFt+ikOU+7GL314epBZoWDJ8EhQ8XKUFhMagf/8Xabn9fd14rcdS49EeeiP4/RGM/gNpRlXAEY+UmvQL5zotKKtB2+GsZwSbikZbHliVpO/zheCRjNwoUiI02iBFXfggzPebO4w2c+B9E1pTCN/WVfaaExRK082FtpR0Dz6R4QiPzzG9hock2lf0MJ7oZyvVjdUEaI8w454Ng0savDmzDgBdB7RwsPPXt38kePuCw+IPfRhdoUkvj9rZQ7Y4zvIJvYkfr7zQUiR1Hj/TVYs5dq88kf0WvNgwk/4/8fkFE+kg0Q45xyf2mkO2ftrCp/uXTXH1Pqj6zoZ3MxWPIXPDjUIZo8PhrMjUeESj0P0U0O2rfwUnjU5gHRtgaGtCBb7EziS6vE/TORa8w9Dxafq7wNvo1A5XJ+uMtA8W/64Aycflfq8m7IXf0HgjrkgqAIsEvkndlNjU7ZvX4+v3+Mogy5RRPc/gRTPO3dKtjP4xkZ6+knMq4ZC8rh20U+FiBr0Pw8wBP6kIbEHM7vrkV230pwF+WMPBdBJzDb5vzXE6pddJrLBWsrMcclXuZAuNC8MT3cnt+zpgYXs7Xac7b77Cc6EPD6WQJIbLruKoowh29tHgMtSsRValebYgLxkidhrET103SpZ7SpacOo0tk+8996UiKMusDSSeKbpeIkkOcEkhXYoMzzq9AdVakgArwk7nYcGY=
*/
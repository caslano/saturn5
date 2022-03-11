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
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
*/
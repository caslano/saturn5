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
    ~basic_xml_oarchive() BOOST_OVERRIDE;
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
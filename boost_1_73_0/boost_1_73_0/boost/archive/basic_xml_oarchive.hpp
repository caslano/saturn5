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
jd5fdJ73ucNhtG8hfmGur73bJ5Mu+mScx0PlXS6/fjOWMuXvdrsuRr8dzdPTNtsdTU4m7GjiwhB3zx28otujtZMuyXRHgoRDFEwSk+hd7uacXQTMcXIdw33xQn/skindSASTjkvQDldKPQbbHOi9zaUi9jyjJSaBE+5MuBDtvbeACei6nGebpSajOVs1xBng8oBs/UCLyabRTBlgsT4hXlBTszJgMrmgqkV3JuB0IJ4n6wUbmxIP4Jm6/i72qdCl0Yt1qfcIZUwmw2FG9ZktrQFugN+D3eq3M8BwRfVMllVPdopISFKdD1v9mGB9tBWRwSVkP83ew+73WaBwZSQL3JNwqYymNChPxnuLOyYfs1If42llYYbLdNSZFld8TNYPe3twIeCdITkbEP3DBjddsa+z+8P2D8hMZXdy3qStRi/0MbxEKaOcysykW7ILnQXBUMbmO9gznBIy/GeSFMBHAhjifBi3+qM7Td5ezdmSI7DwgA0vXvTAEihVO+slGut595iaBzzjIoujmvRawNZ6IMu1pVRFLUvh0HSX19IzeOO+XTcrN/a2M3O2a2sbNncHTHmsQn4BmF5Aj0ASgQcJzYXy2yd4AJgdculh5iOuNwgk2ZegJ2pq+rPr7HdK6df6gzU9zk9E5auub1Jl
*/
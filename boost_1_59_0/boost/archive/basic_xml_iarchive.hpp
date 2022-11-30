#ifndef BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/archive/detail/common_iarchive.hpp>
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
    template<class Archive> class interface_iarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_xml_iarchive - read serialized objects from a input text stream
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_xml_iarchive :
    public detail::common_iarchive<Archive>
{
    unsigned int depth;
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_iarchive<Archive>;
#endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_start(const char *name);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_end(const char *name);

    // Anything not an attribute and not a name-value pair is an
    // should be trapped here.
    template<class T>
    void load_override(T & t)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((serialization::is_wrapper< T >));
        this->detail_common_iarchive::load_override(t);
    }

    // Anything not an attribute - see below - should be a name value
    // pair and be processed here
    typedef detail::common_iarchive<Archive> detail_common_iarchive;
    template<class T>
    void load_override(
        const boost::serialization::nvp< T > & t
    ){
        this->This()->load_start(t.name());
        this->detail_common_iarchive::load_override(t.value());
        this->This()->load_end(t.name());
    }

    // specific overrides for attributes - handle as
    // primitives. These are not name-value pairs
    // so they have to be intercepted here and passed on to load.
    // although the class_id is included in the xml text file in order
    // to make the file self describing, it isn't used when loading
    // an xml archive.  So we can skip it here.  Note: we MUST override
    // it otherwise it will be loaded as a normal primitive w/o tag and
    // leaving the archive in an undetermined state
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(class_id_type & t);
    void load_override(class_id_optional_type & /* t */){}
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(object_id_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(version_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(tracking_type & t);
    // class_name_type can't be handled here as it depends upon the
    // char type used by the stream.  So require the derived implementation
    // handle this.
    // void load_override(class_name_type & t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_xml_iarchive(unsigned int flags);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_xml_iarchive() BOOST_OVERRIDE;
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP

/* basic_xml_iarchive.hpp
+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
*/
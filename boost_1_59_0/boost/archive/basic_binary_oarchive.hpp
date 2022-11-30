#ifndef BOOST_ARCHIVE_BASIC_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as native binary - this should be the fastest way
// to archive the state of a group of obects.  It makes no attempt to
// convert to any canonical form.

// IN GENERAL, ARCHIVES CREATED WITH THIS CLASS WILL NOT BE READABLE
// ON PLATFORM APART FROM THE ONE THEY ARE CREATE ON

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/integer.hpp>
#include <boost/integer_traits.hpp>

#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>

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
// class basic_binary_oarchive - write serialized objects to a binary output stream
// note: this archive has no pretensions to portability.  Archive format
// may vary across machine architectures and compilers.  About the only
// guarentee is that an archive created with this code will be readable
// by a program built with the same tools for the same machne.  This class
// does have the virtue of buiding the smalles archive in the minimum amount
// of time.  So under some circumstances it may be he right choice.
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_binary_oarchive :
    public detail::common_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
    #else
        friend class detail::interface_oarchive<Archive>;
    #endif
#endif
    // any datatype not specifed below will be handled by base class
    typedef detail::common_oarchive<Archive> detail_common_oarchive;
    template<class T>
    void save_override(const T & t){
      this->detail_common_oarchive::save_override(t);
    }

    // include these to trap a change in binary format which
    // isn't specifically handled
    BOOST_STATIC_ASSERT(sizeof(tracking_type) == sizeof(bool));
    // upto 32K classes
    BOOST_STATIC_ASSERT(sizeof(class_id_type) == sizeof(int_least16_t));
    BOOST_STATIC_ASSERT(sizeof(class_id_reference_type) == sizeof(int_least16_t));
    // upto 2G objects
    BOOST_STATIC_ASSERT(sizeof(object_id_type) == sizeof(uint_least32_t));
    BOOST_STATIC_ASSERT(sizeof(object_reference_type) == sizeof(uint_least32_t));

    // binary files don't include the optional information
    void save_override(const class_id_optional_type & /* t */){}

    // enable this if we decide to support generation of previous versions
    #if 0
    void save_override(const boost::archive::version_type & t){
        library_version_type lvt = this->get_library_version();
        if(boost::serialization::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::serialization::library_version_type(6) < lvt){
            const boost::uint_least16_t x = t;
            * this->This() << x;
        }
        else{
            const unsigned int x = t;
            * this->This() << x;
        }
    }
    void save_override(const boost::serialization::item_version_type & t){
        library_version_type lvt = this->get_library_version();
        if(boost::serialization::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::serialization::library_version_type(6) < lvt){
            const boost::uint_least16_t x = t;
            * this->This() << x;
        }
        else{
            const unsigned int x = t;
            * this->This() << x;
        }
    }

    void save_override(class_id_type & t){
        library_version_type lvt = this->get_library_version();
        if(boost::serialization::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::serialization::library_version_type(6) < lvt){
            const boost::int_least16_t x = t;
            * this->This() << x;
        }
        else{
            const int x = t;
            * this->This() << x;
        }
    }
    void save_override(class_id_reference_type & t){
        save_override(static_cast<class_id_type &>(t));
    }

    #endif

    // explicitly convert to char * to avoid compile ambiguities
    void save_override(const class_name_type & t){
        const std::string s(t);
        * this->This() << s;
    }

    #if 0
    void save_override(const serialization::collection_size_type & t){
        if (get_library_version() < boost::serialization::library_version_type(6)){
            unsigned int x=0;
            * this->This() >> x;
            t = serialization::collection_size_type(x);
        }
        else{
            * this->This() >> t;
        }
    }
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    basic_binary_oarchive(unsigned int flags) :
        detail::common_oarchive<Archive>(flags)
    {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_BINARY_OARCHIVE_HPP

/* basic_binary_oarchive.hpp
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
*/
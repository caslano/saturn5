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
        if(boost::archive::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
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
        if(boost::archive::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
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
        if(boost::archive::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
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
        if (get_library_version() < boost::archive::library_version_type(6)){
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
#ifndef BOOST_ARCHIVE_BASIC_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_binary_iarchive.hpp
//
// archives stored as native binary - this should be the fastest way
// to archive the state of a group of obects.  It makes no attempt to
// convert to any canonical form.

// IN GENERAL, ARCHIVES CREATED WITH THIS CLASS WILL NOT BE READABLE
// ON PLATFORM APART FROM THE ONE THEY ARE CREATED ON

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/library_version_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/integer_traits.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_binary_iarchive - read serialized objects from a input binary stream
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_binary_iarchive :
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
    // template ordering. If we get here pass to base class
    // note extra nonsense to sneak it pass the borland compiers
    typedef detail::common_iarchive<Archive> detail_common_iarchive;
    template<class T>
    void load_override(T & t){
      this->detail_common_iarchive::load_override(t);
    }

    // include these to trap a change in binary format which
    // isn't specifically handled
    // upto 32K classes
    BOOST_STATIC_ASSERT(sizeof(class_id_type) == sizeof(int_least16_t));
    BOOST_STATIC_ASSERT(sizeof(class_id_reference_type) == sizeof(int_least16_t));
    // upto 2G objects
    BOOST_STATIC_ASSERT(sizeof(object_id_type) == sizeof(uint_least32_t));
    BOOST_STATIC_ASSERT(sizeof(object_reference_type) == sizeof(uint_least32_t));

    // binary files don't include the optional information
    void load_override(class_id_optional_type & /* t */){}

    void load_override(tracking_type & t, int /*version*/){
        boost::serialization::library_version_type lv = this->get_library_version();
        if(boost::serialization::library_version_type(6) < lv){
            int_least8_t x=0;
            * this->This() >> x;
            t = boost::archive::tracking_type(x);
        }
        else{
            bool x=0;
            * this->This() >> x;
            t = boost::archive::tracking_type(x);
        }
    }
    void load_override(class_id_type & t){
        boost::serialization::library_version_type lv = this->get_library_version();
        /*
         * library versions:
         *   boost 1.39 -> 5
         *   boost 1.43 -> 7
         *   boost 1.47 -> 9
         *
         *
         * 1) in boost 1.43 and inferior, class_id_type is always a 16bit value, with no check on the library version
         *   --> this means all archives with version v <= 7 are written with a 16bit class_id_type
         * 2) in boost 1.44 this load_override has disappeared (and thus boost 1.44 is not backward compatible at all !!)
         * 3) recent boosts reintroduced load_override with a test on the version :
         *     - v > 7 : this->detail_common_iarchive::load_override(t, version)
         *     - v > 6 : 16bit
         *     - other : 32bit
         *   --> which is obviously incorrect, see point 1
         *
         * the fix here decodes class_id_type on 16bit for all v <= 7, which seems to be the correct behaviour ...
         */
        if(boost::serialization::library_version_type (7) < lv){
            this->detail_common_iarchive::load_override(t);
        }
        else{
            int_least16_t x=0;
            * this->This() >> x;
            t = boost::archive::class_id_type(x);
        }
    }
    void load_override(class_id_reference_type & t){
        load_override(static_cast<class_id_type &>(t));
    }

    void load_override(version_type & t){
        boost::serialization::library_version_type  lv = this->get_library_version();
        if(boost::serialization::library_version_type(7) < lv){
            this->detail_common_iarchive::load_override(t);
        }
        else
        if(boost::serialization::library_version_type(6) < lv){
            uint_least8_t x=0;
            * this->This() >> x;
            t = boost::archive::version_type(x);
        }
        else
        if(boost::serialization::library_version_type(5) < lv){
            uint_least16_t x=0;
            * this->This() >> x;
            t = boost::archive::version_type(x);
        }
        else
        if(boost::serialization::library_version_type(2) < lv){
            // upto 255 versions
            unsigned char x=0;
            * this->This() >> x;
            t = version_type(x);
        }
        else{
            unsigned int x=0;
            * this->This() >> x;
            t = boost::archive::version_type(x);
        }
    }

    void load_override(boost::serialization::item_version_type & t){
        boost::serialization::library_version_type lv = this->get_library_version();
//        if(boost::serialization::library_version_type(7) < lvt){
        if(boost::serialization::library_version_type(6) < lv){
            this->detail_common_iarchive::load_override(t);
        }
        else
        if(boost::serialization::library_version_type(6) < lv){
            uint_least16_t x=0;
            * this->This() >> x;
            t = boost::serialization::item_version_type(x);
        }
        else{
            unsigned int x=0;
            * this->This() >> x;
            t = boost::serialization::item_version_type(x);
        }
    }

    void load_override(serialization::collection_size_type & t){
        if(boost::serialization::library_version_type(5) < this->get_library_version()){
            this->detail_common_iarchive::load_override(t);
        }
        else{
            unsigned int x=0;
            * this->This() >> x;
            t = serialization::collection_size_type(x);
        }
    }

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(class_name_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    basic_binary_iarchive(unsigned int flags) :
        detail::common_iarchive<Archive>(flags)
    {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_BINARY_IARCHIVE_HPP

/* basic_binary_iarchive.hpp
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
*/
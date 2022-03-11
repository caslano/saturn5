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
        library_version_type lvt = this->get_library_version();
        if(boost::archive::library_version_type(6) < lvt){
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
        library_version_type lvt = this->get_library_version();
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
        if(boost::archive::library_version_type(7) < lvt){
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
        library_version_type lvt = this->get_library_version();
        if(boost::archive::library_version_type(7) < lvt){
            this->detail_common_iarchive::load_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
            uint_least8_t x=0;
            * this->This() >> x;
            t = boost::archive::version_type(x);
        }
        else
        if(boost::archive::library_version_type(5) < lvt){
            uint_least16_t x=0;
            * this->This() >> x;
            t = boost::archive::version_type(x);
        }
        else
        if(boost::archive::library_version_type(2) < lvt){
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
        library_version_type lvt = this->get_library_version();
//        if(boost::archive::library_version_type(7) < lvt){
        if(boost::archive::library_version_type(6) < lvt){
            this->detail_common_iarchive::load_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
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
        if(boost::archive::library_version_type(5) < this->get_library_version()){
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
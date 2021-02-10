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
nv1+FwimOeoeFiuN/CrNShptwfb90XNf0eDMnRwSaeM/+L2YXy0jMVnQ72IcfyLDJ4v4ExvlmxvfbKkvBGtfAZwHSgoxGsqPg0A0w3p+cvtK/uMn34wc4oxyRRdiXcBy59Vz6ECXOQfK4+DwJHDyoWY7AxT4rXPVINSB9RYEvmubFs8ynXWHgVBja1c1vRuKeCXhHmN3iCj4ToYg1TRd/oBX1NqIHtdir+vgj8GB8No5FKnjXUEVn4OAR3NItvLeYvWFz0HE/DsqFd0fRTnDKdM0gAFAh7ohb1SqnPiMWNi3w+HntiQdteNgKEYgtmWyvtdVoKj88t744/KDWM7iHte+f8XCXsA0LO7V1caAAtGL5XRykkZSSOfEYVuSbJQSo7BW6ptKLgzKR9cGcig+W4j+a+8Pi7d9CR869QomimvpCdOvQAxE/9X3LoEQd0oBNS1iLFGGR83wIVxY0/Kxcg0I5/nJ7BKndbjbNDEow4EaijnodTLHsRRaCA4/rg6qHOKXmrfpcM5bzs7HcO7k6HAt4JFuOZLY+fTM65W34PMMmKORB2LvprMJi90r50OVhqriuF78wrL4342EJs5cIjkUU+TzK2F4wF8+2NRh7EZh2xDE+03JgoAUiZne0N/Z1fhicHH+oulS/HPT
*/
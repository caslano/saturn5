#ifndef BOOST_ARCHIVE_DETAIL_COMMON_IARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_COMMON_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// common_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/archive/detail/basic_pointer_iserializer.hpp>
#include <boost/archive/detail/interface_iarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {
namespace detail {

class extended_type_info;

// note: referred to as Curiously Recurring Template Patter (CRTP)
template<class Archive>
class BOOST_SYMBOL_VISIBLE common_iarchive :
    public basic_iarchive,
    public interface_iarchive<Archive>
{
    friend class interface_iarchive<Archive>;
    friend class basic_iarchive;
private:
    void vload(version_type & t) BOOST_OVERRIDE {
        * this->This() >> t;
    }
    void vload(object_id_type & t) BOOST_OVERRIDE {
        * this->This() >> t;
    }
    void vload(class_id_type & t) BOOST_OVERRIDE {
        * this->This() >> t;
    }
    void vload(class_id_optional_type & t) BOOST_OVERRIDE {
        * this->This() >> t;
    }
    void vload(tracking_type & t) BOOST_OVERRIDE {
        * this->This() >> t;
    }
    void vload(class_name_type &s) BOOST_OVERRIDE {
        * this->This() >> s;
    }
protected:
    // default processing - invoke serialization library
    template<class T>
    void load_override(T & t){
        archive::load(* this->This(), t);
    }
    // default implementations of functions which emit start/end tags for
    // archive types that require them.
    void load_start(const char * /*name*/){}
    void load_end(const char * /*name*/){}
    // default archive initialization
    common_iarchive(unsigned int flags = 0) :
        basic_iarchive(flags),
        interface_iarchive<Archive>()
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_DETAIL_COMMON_IARCHIVE_HPP

/* common_iarchive.hpp
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
*/
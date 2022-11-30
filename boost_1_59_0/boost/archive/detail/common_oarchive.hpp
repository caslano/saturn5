#ifndef BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// common_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/archive/detail/basic_oarchive.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {
namespace detail {

// note: referred to as Curiously Recurring Template Patter (CRTP)
template<class Archive>

class BOOST_SYMBOL_VISIBLE common_oarchive :
    public basic_oarchive,
    public interface_oarchive<Archive>
{
    friend class interface_oarchive<Archive>;
    friend class basic_oarchive;
private:
    void vsave(const version_type t) BOOST_OVERRIDE {
        * this->This() << t;
    }
    void vsave(const object_id_type t) BOOST_OVERRIDE {
        * this->This() << t;
    }
    void vsave(const object_reference_type t) BOOST_OVERRIDE {
        * this->This() << t;
    }
    void vsave(const class_id_type t) BOOST_OVERRIDE {
        * this->This() << t;
    }
    void vsave(const class_id_reference_type t) BOOST_OVERRIDE {
        * this->This() << t;
    }
    void vsave(const class_id_optional_type t) BOOST_OVERRIDE {
        * this->This() << t;
    }
    void vsave(const class_name_type & t) BOOST_OVERRIDE {
        * this->This() << t;
    }
    void vsave(const tracking_type t) BOOST_OVERRIDE {
        * this->This() << t;
    }
protected:
    // default processing - invoke serialization library
    template<class T>
    void save_override(T & t){
        archive::save(* this->This(), t);
    }
    void save_start(const char * /*name*/){}
    void save_end(const char * /*name*/){}
    common_oarchive(unsigned int flags = 0) :
        basic_oarchive(flags),
        interface_oarchive<Archive>()
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP

/* common_oarchive.hpp
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
*/
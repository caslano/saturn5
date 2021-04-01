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
    virtual void vload(version_type & t){
        * this->This() >> t;
    }
    virtual void vload(object_id_type & t){
        * this->This() >> t;
    }
    virtual void vload(class_id_type & t){
        * this->This() >> t;
    }
    virtual void vload(class_id_optional_type & t){
        * this->This() >> t;
    }
    virtual void vload(tracking_type & t){
        * this->This() >> t;
    }
    virtual void vload(class_name_type &s){
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
wK0tTsfmcFqRQm5X4hqBEqrUvpUgE343E3vCiMAa8jsKKidVPjvbmdgmmftccT+0dJxE4304tj3dmsAkItNQ8qqbMkH5Zw2HefvpuVfTpf3/k6wxKVgenGdt8Yd9dFiStcrel1CdAD1IdtkACXSDX5AnKpSfYcFQPxgp26ZmAseUbYHt0M5qqI+2guE1ceDNEj8/SkPBgPWRNOYEWlBLjGAmipoXDGM1FexTmJaW1VAADyqvyae9ECkJ/MSbKHJfVIWJhsEF4+YoOWm0P0HNHahCv/T88rdfF1OiLb2ZtdlEevIuLAa72qT6D/qiVi7ncWX5WaZZyt4SLPKUh+9gGcraQwpmlxgWlsGbtUiUjzoX18JBAPkuowOshjvTuoT/R40WqfsXyJkz6lJgD3u6yttRg45GnWsWKeL4PfQ+Ptd5TJeBCa8ERMmqm7gE4ROD/PKZaHlIfaytcHkTZvq7sV4QUOUYl+t1Zhjz7E1lqm4bZL+VKWT40fLy4q1Yt6npNnGQmOnv5tNV61ci0MKt9NxYcUVCk79BA11CJQxEGJfy3M721cE3qoASmg==
*/
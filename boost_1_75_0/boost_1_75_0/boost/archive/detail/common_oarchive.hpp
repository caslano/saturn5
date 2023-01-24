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
    virtual void vsave(const version_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_optional_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_name_type & t){
        * this->This() << t;
    }
    virtual void vsave(const tracking_type t){
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
gWi3FQRecbfQyux8tduhrEeE1xI4xW2wMjOrOkdm/1myHwJXj3rKyljWXl/y4CLR3loJPKW6zMo8Lm+6/O1lafx0R3j1LYjn5n7Yzu78kwhXEfiF1Eors+JS+Tjj2cuCvtQErqvbamWiI1cO+1ubaG8pBF7szlmZ7+N86DSzNJ8SuGLds1bmyswZr297yyrQqSXw4A+etzJPGhu/WXZA8pMJPNyyw8o0uk+iAmaJ6yGtBO43daeV+al7+46nfxXtjZpA9BL1qpU5quo8+N4fot5VBB6sf93K/P7nG9l5iSK+msB3/elNKzN9x7N/qvMRx40UAtf+bbeVSXr2QMi0WFEOFQRe8fk7Vqaq7FUf7zLRDmsJXF33NyuztTxkWEmN2C9MBL637gMrkzts8oopDuK6UyuB81/stTK39yQ0L0iRi/xPJHr84O/QT9PX7Xu5S6SjInC3nf+wMhcDYjbsVYvtUhP4wtLPwR5+bZzSVSnymULgO1YfsDKlZS+NDvhaiosJfJb311bmrws3KO5cEu28lsC9qG+gn3605ZGCejHuMBH49qZDVuZPd2wJMzyk8YfAS7c3WJk1RV7vbe8U5Ubdj3Dl0iNW5r30rad3xIp+nYrAV9qOWZkvPtjt/VC45LcQeNZHJ6xM10PPPRraKI0/BB6/+pSV2VZ6buKRp6T5l8DVf5yxMnGf/njw1XDRj60lcO9Xz1oZ47lb
*/
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
FcbHQmz7zkF34NysrQliT2p7o49Xd6WnvwYvnwXPezZfQ1dDX1IryH7QBjr2Dqp0LRt8Mp3udZcZe9jeQy3USeXx1deEQjkMpZIYI8U+lpXoLthgMxtocxz8VyFAxIwScPzXCNooidJ22B7xg7mozF2z5DzaptbWNMx4H1wjJZW2XAIseet8RYmvJTHiJhVIa1KhJlmb/Ktn0qatm5Vzd7CNse5hOKdqaWau7PKF16i5WEoKzjnpdhkop47jRWVhyjXcqDX9aYLIOYhiRjdZaEJQJDOnhujmsGJ/3eVA+NJXwnfPFxti2AC850E1/k/z3w/20SNeR2egbx8+7Fd0R5JI/IudiLX4gT+qmjtZfmD34oX9fElh2/hqcj21LVG8oeaPfsSZC0KbTZKrm4nh+ONm+ptlpen98Gzvh7U4G/151mJFdFZNhpkdaGmD6W7bJqhCkHEadDQ9J3qU1yOMqD3BXndKqN6kGdIP3CH0+iUlCm0zytQg5HmD0ZeeGKTxUlJpqSnCDaAre3DN6eFxIsMbmE5I+sGzjZ/XRO5K0KAhoiaPv8BkpDxvSHcVxYi/cmd+T5yUcgljBlIeT09gwIb08l2pFP+kLyd44tGXyTW/q8OVjmVPnMkSHhAvdaYyOGE98V7GN3WPc2AK
*/
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
yI+awLPGtHYyl27rXyn9SRwfUgh8v+ZKJxM4ya8kfKJoJxUEbsr6tZMxve87948vJf4J/Nim3zuZ2bcMp2fmS/IncK/NHZ1M8Y4/dY+hRX+jlcDdim51Mke/e2191UpxnqLcEH4h7i70ux/b6apFE0X+Cdw029HK1H/4Y8KUv4vzrJrA5Z0uVsbp6B9HEhaJckgh8PYPFFbGwyUn4YFpriL/BL4/frSVOai4NfdUsBiX1RJ4bec4K9PpGeWZcli0QxOB85UTrczLZdsNZyd5i/wT+CHnKVbmo6c/C0mQ/FhqHMJ1mzytjO3tsx/RsyT5E7j3zw9aGVbzoipxi9gf1QQ+a/EsK/NC24/PMOPE+SiFwGu3e1uZLz/KXvqkqzSfEvih475W5pes1JtffiD1XwJvpP2tzC1jYM32b0U7NxH45TmLrMyx3ctDbBt7RPsh8OCIQCvz7W16UtfOS6L9jEe4e4rGyqQWPL/U+0PRb1ER+M51S63M7pcfe62lXhzf1ATelhZhZd6+MX1c9JhRIv8Erl4VbWXCSx4990q+xD+BNwassjIbzq2r9X5OnNdqCXzPfautTM6GHxWrpP5lInClOcHKNF899bOtRBxvWwl81t4UKxM4PaJkyzkxjqPuQ7jH+nQr037n2tuv35X4J3ClKsvK1BV8O+V0hzheqQncu+kJK/PEtVEez5eJ/S6FwHdl5VuZ1z7dsT9z
*/
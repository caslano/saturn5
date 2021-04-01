#ifndef BOOST_ARCHIVE_BINARY_OARCHIVE_IMPL_HPP
#define BOOST_ARCHIVE_BINARY_OARCHIVE_IMPL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_oarchive_impl.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <boost/config.hpp>
#include <boost/archive/basic_binary_oprimitive.hpp>
#include <boost/archive/basic_binary_oarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE binary_oarchive_impl :
    public basic_binary_oprimitive<Archive, Elem, Tr>,
    public basic_binary_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
        friend basic_binary_oarchive<Archive>;
        friend save_access;
    #else
        friend class detail::interface_oarchive<Archive>;
        friend class basic_binary_oarchive<Archive>;
        friend class save_access;
    #endif
#endif
    template<class T>
    void save_override(T & t){
        this->basic_binary_oarchive<Archive>::save_override(t);
    }
    void init(unsigned int flags) {
        if(0 != (flags & no_header)){
            return;
        }
        #if ! defined(__MWERKS__)
            this->basic_binary_oarchive<Archive>::init();
            this->basic_binary_oprimitive<Archive, Elem, Tr>::init();
        #else
            basic_binary_oarchive<Archive>::init();
            basic_binary_oprimitive<Archive, Elem, Tr>::init();
        #endif
    }
    binary_oarchive_impl(
        std::basic_streambuf<Elem, Tr> & bsb,
        unsigned int flags
    ) :
        basic_binary_oprimitive<Archive, Elem, Tr>(
            bsb,
            0 != (flags & no_codecvt)
        ),
        basic_binary_oarchive<Archive>(flags)
    {}
    binary_oarchive_impl(
        std::basic_ostream<Elem, Tr> & os,
        unsigned int flags
    ) :
        basic_binary_oprimitive<Archive, Elem, Tr>(
            * os.rdbuf(),
            0 != (flags & no_codecvt)
        ),
        basic_binary_oarchive<Archive>(flags)
    {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_OARCHIVE_IMPL_HPP

/* binary_oarchive_impl.hpp
G6Jg77e0wL5mcGr/rBGQiB/Nlwi0mMeyBMpsrRsplWyuc+UqfyGIDMPhDu0jZqYb/aI6zI2K+v6OvUX8BfxN4uK+bGT6texs908XHh+couCERSRBnel1BVJDqXa+VqwlnzobLaJAb1sNC0CvKNnRzEeC7W8aZMUoOZ0r/k7/9fmPosJryEZM7RDEbHSEkASeWucOiGzEpWVkgsk/tnWiiZmPjJCTpY/jWMG0U2S4VG5kKgBgIowzkfhzAClplqtcHlNa46XH64RA/o/RGY77MXDizDCOvFwr41vhTdtyhITtKzk3DpB9hHb3ZmVAGoJagfE5qVaUm82/JBygb/cMmjyQBSTX9iJec98a21n7y6jMOyeIaQz/UYxht3Te6D5A6VCTidyq3+/eQBI2Xzmvihq0z+wXMG3aRtn7WodGrX6dwzngvQYdtU7UvATHpbMOyA267hQ8C6IFo32MXGcd2Sn8KJPj2NAltQf30KNLObAeo4aysy21rwMR9XZwuC7r7ywIGD1ygN3nI2ncTPFZIUQ+0INbgUvTpkgfTcy7XKdCRaVH55Pj4zC3oA==
*/
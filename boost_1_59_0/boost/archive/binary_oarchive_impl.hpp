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
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
*/
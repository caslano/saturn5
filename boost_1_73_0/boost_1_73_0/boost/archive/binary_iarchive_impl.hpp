#ifndef BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP
#define BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_iarchive_impl.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/archive/basic_binary_iprimitive.hpp>
#include <boost/archive/basic_binary_iarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE binary_iarchive_impl :
    public basic_binary_iprimitive<Archive, Elem, Tr>,
    public basic_binary_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_iarchive<Archive>;
        friend basic_binary_iarchive<Archive>;
        friend load_access;
    #else
        friend class detail::interface_iarchive<Archive>;
        friend class basic_binary_iarchive<Archive>;
        friend class load_access;
    #endif
#endif
    template<class T>
    void load_override(T & t){
        this->basic_binary_iarchive<Archive>::load_override(t);
    }
    void init(unsigned int flags){
        if(0 != (flags & no_header)){
            return;
        }
        #if ! defined(__MWERKS__)
            this->basic_binary_iarchive<Archive>::init();
            this->basic_binary_iprimitive<Archive, Elem, Tr>::init();
        #else
            basic_binary_iarchive<Archive>::init();
            basic_binary_iprimitive<Archive, Elem, Tr>::init();
        #endif
    }
    binary_iarchive_impl(
        std::basic_streambuf<Elem, Tr> & bsb,
        unsigned int flags
    ) :
        basic_binary_iprimitive<Archive, Elem, Tr>(
            bsb,
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<Archive>(flags)
    {}
    binary_iarchive_impl(
        std::basic_istream<Elem, Tr> & is,
        unsigned int flags
    ) :
        basic_binary_iprimitive<Archive, Elem, Tr>(
            * is.rdbuf(),
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<Archive>(flags)
    {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP

/* binary_iarchive_impl.hpp
y4cslgNOYg0tdYPrpFFXAsmpSBOVknyZp+L9bE61j1e6LfIHbM3G4aC9rEl3c5Kcrb7Oxru+VvHfGE1mLnE/O9+vo5lDva4d67MsSP0FqPa8qwYNUHRkHrG+GdWqxoQILXkJ+sweaQwpnuQA+j8h6a6OpxqGJGWZ7pX6CsIMTp+AITTlHD0ms7Upb5kAWUCeOw6XxaSAG1mcyNzPEk+oDQkQ1E1eF/LeowMPyRpI31Z/j4JB8eqayLfQmmkOOl8gvXVnMakbMXa7MiMbdY2Q9DYebvpVpxv2Nwg3PJCUkKFgO0ct5XaqbhnxNCagG+orQCJv1zE557q+1Q0YpDSoW63op8d/PaLyUsV3WC6zyMuA/BivwDLMQcrS8EVQQtGuDRIr3VjGZQSiOFLJ3K7r7XPJYYvbqay9x5P/putK7GPjxwCnWCrI+bY1OomSVU5t45DegvsFuxxMeLdwoLRHpKnhAG+4A3WCk2cnOCg0M1EFHm/swOWfxXThTAYa7CdFTnaMgJN6RWzDdWmfZJ4VjFNB7rYMq1gL2rZvzdUaBLyzEY/T5FGvPawgu9QDqTmdtVRDr7CHu5ALON1WYyyuHRVg/eLoqwKt4FdpWGfjL8ipxyu9VYq/uQHLOVx8GHxbPusEKBYAySePEJ+A
*/
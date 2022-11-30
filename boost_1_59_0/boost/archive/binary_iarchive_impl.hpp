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
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
*/
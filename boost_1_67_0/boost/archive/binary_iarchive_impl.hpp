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
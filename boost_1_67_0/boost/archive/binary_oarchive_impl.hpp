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
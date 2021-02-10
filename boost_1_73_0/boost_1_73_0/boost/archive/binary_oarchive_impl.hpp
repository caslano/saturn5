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
TzY99UpLzBXGZ0mFRbXJrZAvUmdymimacJeXqsDa4is23YjrhSzFPk51EFVWFTYWV1nGO+QqUdbKYiNSWUqxVoUSq2qaabvAUXFEGvRNTf9X4P+/V7bEDJXiT6WJZFWaJa5EY3SB+5WFVi8yi6OIbBb18BNFT7l4NC9qCauJweCQzcmrfizkd51p2CdVLyozKwz4KmeSrCznuBcsarC6hBtgOyWtSqPbslx9wb1ecAtcW/TjAbbzzlGv8A4fDl7Gb9qyQxKzXGKRXqZzJbBN3rOmKhIylMlgihlsJaSYqbVY6twUkUzppkuVl/ZQ6FKkOnV3X5Md2WpkgxhoUmKmC/zFH9C5zh3nF4uFUu28Q3Dpx8PD+iZk2xsY39nlzNklDjD7Z6WT52wjpg66MFeU0/Gkzkv8hykAJhlxVZjfVVI6k595kwcj9eMj3rjeU+fiLzKvyN00nE2bI0xwR5kkakXwvJ1MRuLXr/fWez/y5hNkvrhZfBD3u4tj+NWq0Jk4hwl4eTbGtOBdcHpeGQd+3QhbrVamoGN/U8IaTJ2ZCsNo6Ey/YjU/QlAIzVXpHOkiQCucDQAQX55Gt5++xkI85fDm58koSs06z4xsptMJ4QWVHjq4kzW7puMhLqDc/qAMbCiGcT/aNt5VNScY
*/
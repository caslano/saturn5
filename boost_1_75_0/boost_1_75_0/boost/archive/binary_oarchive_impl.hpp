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
QWcbyd6630UKIWB9y0lDc8hv1mKXkzFRtB5tVlx12kh8L3S2rRcvdDz468J9ycgv5TT6RiQ57wM9utfIGYYx9pBnJd6uXCYL063Wa9uRUuPehsXeeb6ZKDVoMzG6VlOtu8jOJGPZI5hNlrKwNlPdBHNTOet5Dk0r8mJoRppZK9SvtLfMFpUeWSYQvRBY0/GIRrKb6gtksrYNyulCasalukmG3C8RczrvBPQ0GUKwRQez+CtktdGoiIRJqdNatLu0lDwCbQyX/G3LUAzsSUO4ccZmmNPxsxtfiREJgviVpb792/uWNj4q8O73yeLrS4Xd+c1KsCM1VrqXog0KrLx2VTz3igLz0009Cx6mMu/XzQy71IJh/NmVus2QgN2T+IgZRKuUuA5W6Ys3QADHgD4Mk1w2mG43KXk+D5LRZ/mYHN8ONo1dspFQfZDjQwZKvTXJEyg4U/TZ4nB2bJfvRYsgkG9Z6ms/g+3A9tFn08d5v2M7d9X7JLPl+5VU6re4l/dA6gzvJpa/S7dd/1iEb0fwoR7PWdps475bhHcraq9K6O3I2r3a25F27+pvRxYAjG6R6coeaEY5sYhCcasboGV+iEG+mMFPXwk0sFbNVQZAlQN0kmfI9QZ1RhrbDRVACmp4L8izb970nXJrLDQZeGUHejvk/ZEdelM/ybbvTTpb99cOdGB3zHpz/OwNJlNEcXBi4WiD/XJ0Kd8KRcW9
*/
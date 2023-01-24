#ifndef  BOOST_ARCHIVE_BASIC_SERIALIZER_HPP
#define BOOST_ARCHIVE_BASIC_SERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_serializer.hpp: extenstion of type_info required for serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // NULL

#include <boost/noncopyable.hpp>
#include <boost/config.hpp>
#include <boost/serialization/extended_type_info.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {
namespace detail {

class basic_serializer :
    private boost::noncopyable
{
    const boost::serialization::extended_type_info * m_eti;
protected:
    explicit basic_serializer(
        const boost::serialization::extended_type_info & eti
    ) :
        m_eti(& eti)
    {}
public:
    inline bool
    operator<(const basic_serializer & rhs) const {
        // can't compare address since there can be multiple eti records
        // for the same type in different execution modules (that is, DLLS)
        // leave this here as a reminder not to do this!
        // return & lhs.get_eti() < & rhs.get_eti();
        return get_eti() < rhs.get_eti();
    }
    const char * get_debug_info() const {
        return m_eti->get_debug_info();
    }
    const boost::serialization::extended_type_info & get_eti() const {
        return * m_eti;
    }
};

class basic_serializer_arg : public basic_serializer {
public:
    basic_serializer_arg(const serialization::extended_type_info & eti) :
        basic_serializer(eti)
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BASIC_SERIALIZER_HPP

/* basic_serializer.hpp
x19oZ15944HU178JE/HvIDz8jb+3M9wDywsnRYeI+AQ+67nT7cy/PB/Z/SAv9d8ehLe8faOdSYz/Ns3BJvbHCgKnLMrrjLz5zIdlx6eI+H8Q+8mYc535fen96XEviu2qIPAzk5ZfZ9499eOo4zVSv75L+u+EddeZHZ/6PvwnmYRP4HTy09eZp9d82/CMbJmIb0O4e+eu68zcZ/b9MtlbbFcFgddc/Md15tusNM8biaEiPr4PQc16uPk680M0Xzz8qtheNYEXnOGvMxlPbFnx4ZxIkQ6Bv38F7Pr46YPmvXlqAW4i8Pa17jeYf456/pPr30eJ9GUI94p+5AYzKmjZu1V3RLiawLv3aW4w23c/U1n9vMhPBYG3vbDmBvOsj5vm1CaxvSYCX/l7wQ1mR0zm0rdiJHt2QHj88aobzJL5D92e+5LYL9QE3u3zyg1m8bktuw9+tUCkT+Byrw9vMEUznHZ7vCy2y0Tg6rfqbjCxR4fPv5Ap2i3liPAZn5y5wbzQsmnUhyfFcUMtwOOu3mB+apj99LJ1KpE+gVfvuHWDOXB3Wuo5rWiHJgIvXj/iJjMrhq06t1saT2iE91z2uMk8Pf9bc9ZacTxUEzh1d/ZN5vgTs+77ZrTYrgoCj/9y8U3mY+/O957uEvk0Efj+KVE3mVfPViyNPyHZsxPCTbOTbzItdfedGTlc1JeawNuv5t1kfrvz10nzxkj9gsD3
*/
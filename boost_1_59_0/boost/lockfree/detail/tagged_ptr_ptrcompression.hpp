//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2009, 2016 Tim Blechmann, based on code by Cory Nelson
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_PTRCOMPRESSION_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_PTRCOMPRESSION_HPP_INCLUDED

#include <cstddef>              /* for std::size_t */
#include <limits>

#include <boost/cstdint.hpp>
#include <boost/predef.h>

namespace boost {
namespace lockfree {
namespace detail {

#ifdef BOOST_LOCKFREE_PTR_COMPRESSION

template <class T>
class tagged_ptr
{
    typedef boost::uint64_t compressed_ptr_t;

public:
    typedef boost::uint16_t tag_t;

private:
    union cast_unit
    {
        compressed_ptr_t value;
        tag_t tag[4];
    };

    static const int tag_index = 3;
    static const compressed_ptr_t ptr_mask = 0xffffffffffffUL; //(1L<<48L)-1;

    static T* extract_ptr(volatile compressed_ptr_t const & i)
    {
        return (T*)(i & ptr_mask);
    }

    static tag_t extract_tag(volatile compressed_ptr_t const & i)
    {
        cast_unit cu;
        cu.value = i;
        return cu.tag[tag_index];
    }

    static compressed_ptr_t pack_ptr(T * ptr, tag_t tag)
    {
        cast_unit ret;
        ret.value = compressed_ptr_t(ptr);
        ret.tag[tag_index] = tag;
        return ret.value;
    }

public:
    /** uninitialized constructor */
    tagged_ptr(void) BOOST_NOEXCEPT//: ptr(0), tag(0)
    {}

    /** copy constructor */
#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    tagged_ptr(tagged_ptr const & p):
        ptr(p.ptr)
    {}
#else
    tagged_ptr(tagged_ptr const & p) = default;
#endif

    explicit tagged_ptr(T * p, tag_t t = 0):
        ptr(pack_ptr(p, t))
    {}

    /** unsafe set operation */
    /* @{ */
#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    tagged_ptr & operator= (tagged_ptr const & p)
    {
         ptr = p.ptr;
         return *this;
    }
#else
    tagged_ptr & operator= (tagged_ptr const & p) = default;
#endif

    void set(T * p, tag_t t)
    {
        ptr = pack_ptr(p, t);
    }
    /* @} */

    /** comparing semantics */
    /* @{ */
    bool operator== (volatile tagged_ptr const & p) const
    {
        return (ptr == p.ptr);
    }

    bool operator!= (volatile tagged_ptr const & p) const
    {
        return !operator==(p);
    }
    /* @} */

    /** pointer access */
    /* @{ */
    T * get_ptr() const
    {
        return extract_ptr(ptr);
    }

    void set_ptr(T * p)
    {
        tag_t tag = get_tag();
        ptr = pack_ptr(p, tag);
    }
    /* @} */

    /** tag access */
    /* @{ */
    tag_t get_tag() const
    {
        return extract_tag(ptr);
    }

    tag_t get_next_tag() const
    {
        tag_t next = (get_tag() + 1u) & (std::numeric_limits<tag_t>::max)();
        return next;
    }

    void set_tag(tag_t t)
    {
        T * p = get_ptr();
        ptr = pack_ptr(p, t);
    }
    /* @} */

    /** smart pointer support  */
    /* @{ */
    T & operator*() const
    {
        return *get_ptr();
    }

    T * operator->() const
    {
        return get_ptr();
    }

    operator bool(void) const
    {
        return get_ptr() != 0;
    }
    /* @} */

protected:
    compressed_ptr_t ptr;
};
#else
#error unsupported platform
#endif

} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_TAGGED_PTR_PTRCOMPRESSION_HPP_INCLUDED */

/* tagged_ptr_ptrcompression.hpp
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
*/
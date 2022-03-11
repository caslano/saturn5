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

#if BOOST_ARCH_X86_64 || defined (__aarch64__)

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
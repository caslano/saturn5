//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_DCAS_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_DCAS_HPP_INCLUDED

#include <cstddef>              /* for std::size_t */
#include <limits>

#include <boost/predef.h>

namespace boost    {
namespace lockfree {
namespace detail   {



template <class T>
class
#if BOOST_COMP_MSVC && BOOST_ARCH_X86_64
BOOST_ALIGNMENT(16)
#elif BOOST_COMP_MSVC && BOOST_ARCH_X86_32
BOOST_ALIGNMENT(8)
#else
BOOST_ALIGNMENT(2 * sizeof(void*))
#endif
  tagged_ptr
{
public:
    typedef std::size_t tag_t;

    /** uninitialized constructor */
    tagged_ptr(void) BOOST_NOEXCEPT//: ptr(0), tag(0)
    {}

#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    tagged_ptr(tagged_ptr const & p):
        ptr(p.ptr), tag(p.tag)
    {}
#else
    tagged_ptr(tagged_ptr const & p) = default;
#endif

    explicit tagged_ptr(T * p, tag_t t = 0):
        ptr(p), tag(t)
    {}

    /** unsafe set operation */
    /* @{ */
#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    tagged_ptr & operator= (tagged_ptr const & p)
    {
        set(p.ptr, p.tag);
        return *this;
    }
#else
    tagged_ptr & operator= (tagged_ptr const & p) = default;
#endif

    void set(T * p, tag_t t)
    {
        ptr = p;
        tag = t;
    }
    /* @} */

    /** comparing semantics */
    /* @{ */
    bool operator== (volatile tagged_ptr const & p) const
    {
        return (ptr == p.ptr) && (tag == p.tag);
    }

    bool operator!= (volatile tagged_ptr const & p) const
    {
        return !operator==(p);
    }
    /* @} */

    /** pointer access */
    /* @{ */
    T * get_ptr(void) const
    {
        return ptr;
    }

    void set_ptr(T * p)
    {
        ptr = p;
    }
    /* @} */

    /** tag access */
    /* @{ */
    tag_t get_tag() const
    {
        return tag;
    }

    tag_t get_next_tag() const
    {
        tag_t next = (get_tag() + 1) & (std::numeric_limits<tag_t>::max)();
        return next;
    }

    void set_tag(tag_t t)
    {
        tag = t;
    }
    /* @} */

    /** smart pointer support  */
    /* @{ */
    T & operator*() const
    {
        return *ptr;
    }

    T * operator->() const
    {
        return ptr;
    }

    operator bool(void) const
    {
        return ptr != 0;
    }
    /* @} */

protected:
    T * ptr;
    tag_t tag;
};

} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_TAGGED_PTR_DCAS_HPP_INCLUDED */

/* tagged_ptr_dcas.hpp
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
*/
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
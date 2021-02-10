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
rq9fvb583Rv+eHYz6AePmXscVuEfZzB9WOCjaViIHQS7islXb169IvZhR/gNvcbzvEPDTpmr9F0zFrqsWfrLs8FZYFj7ZBYo3B1dM9CFkEkpLdcVEvjn9A/wET3IJ6RnnaYIPg1n8vFQRoAIeLFCzrJKIpjHg0CnEGVo7GRR4BfmrmkGpzZPUMewpTe8/uF0Pe81KDvqzWB4fTF83Xt9ffOTEgN0VLO8YxYvWnutQMvFgXLVaJRFCnY8TNiPo3XDDnqYFTHdYmXFtFhDsF7cLi5f9QJtFjyB80SuNhsLnpnHFT7d89Q8Q6gu0wKHadbSeRihEhgAi+T9QT/74NksxkmDBpr2K4i2wgJjz3xeGWKCJxOTscY1A9aM41StzKq94TA1o3vKJpNhRYZ7oTGDYDJOuZmlZYjKJsrRfEIyAs2y0i7fm5GHIjYVhI7eI1jC5URQC4tGIW/nCSBIso/xYJpVAqaYQERGOENkB51CWHGlyXc/lalIpRxDiGYoANIyFi+ei0Oxva0x0D+fTBB16NAV24g/uOBtCCcm4MEhd/nb676GjA/3y2o4CUfDYjITT56Li7Nv/+t8+LezGwS0/PnFOcGUKUTVGlp/eNm/6X3X0aOQUIGVZSQ7Sr96Sj/3PLqzmmH7M3FohUwN
*/
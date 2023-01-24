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
NqywcTNmlRyleL4+QG0gZCr9ExjDs1o/M+udwTgnw9foOQ5mKijOsn78fieUKzORz6ZhgPuSwkCh7tiWgjcT3ymnm07s7dWGm5qtr5D595Xb4fcojVmUGhdUw8tACrssLqh7LPzY8yPv1F145dJeHbkl9pwQaaG5MDbg6eMG6Bsa3RvxVuFs1HUV6e0nUbkmupR8E7VC2iPwYnyxRW4Go3oOk5R+2IWeV+zeYv2pIAikWox7y/xqwZI15mIz3gsQUjFvWBF9HLbqS9a/TgnZt39CTP3185xBxwyXLWozraZ4VO/aQx/1VggIziJX5/rTqqfOUMzKZ/6swD92S5vi7dhk/UT/FkbS4n9X360QnBMJKNkVCdH9tXPFlCrfVU0B+cTjn3lzanJCkgzVhpzO4F8wkgaQ7f/65NGlu2SQEufmQtaVnkAjd99rgd9CcUcN+fRRCz84S1Yq9PoK3o2c3YbGU3UQFqJQHeJsQbaKRIpgpNgPmrsOIhWX7wfNc/1RO2vRptFWHdsCvyGx5p0d2/5Dm0eW0B8VZqjlEOxY9TGrUGptMM85mpHxWkJrbBeVJ0AZP7nPdGeVTgmcKKoIVgZIVw1mjAEPBvervdb19c9OCPP6Qoa/Lwdaq95hNZPnNn18vhjRrScQC2Soz8ozO3epL2uKpjhDbVLKwRWZtWY5r8/yvivIPc2VCpnKjUpcn9QP6T+yuFOMmYN5
*/
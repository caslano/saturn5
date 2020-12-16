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
7lvCONgaNoWdYSrsAjvCrrAH7Ab7wJ5wCOwFR8L+cDocDDPhuXABHALXwaFwM5wMb4R/glXwz/BueAwegO/C38L34CvwffgW/AB+A0/AJtHUPTAZfgLbwE9hb/g5HA2/hHPgX2EO/ArmwxFwJRwN18JxcLOc/0DO98Hx8CE4AT4GJ8Kn4PnwWXgBfA7OgC/A2fBLeBG06vHcwASYDVvAXNgWFsDucCHsDRfB8+A4eAGcBBfCyXA5nALXwDx4A8yHu+EceBDOhc/BQvguXAYbUL8vh43hCtgdroR94TqYBS+F8+B6WAY3wLVwI1wv9tfAy+E2uW4fvBLuh1fBg3Az/BXcAl+B26AVy7wsrAe3wzhYCevDW2B7eDvsCu+Ao+EOmAV3wvVyvh3a4d0D74FPwR/DP8H7YL04nn+YBh+Ag+DP4XB4AI6DD8EZ8FGYCR+D8+AhuAE+AbfAZ+C98LdwHzwCfwKfha/KfT6CP4b/gK9Abzx9ARgL34At4avwbPhHOBQel/q5jVfGzzLmz5L1+pqJzkNjL/kDW8JesBUcCe+CY2EbeCFsC2fBdvBi2B6uhJ3getgZXgO7wBtgd3gz7Al3wV5wDzwbPgjT4R/gTfAo3A7fhzfDT2Al/Du8BXqIfBVMhLfD9vAOeA7cAYfCnfA8uAtOgXfBqfAc+D04BM6HQ2EFHA4fh6Pgk3AsfAWOg6/BiTDay3MB4+Bk2AFOgV3hVHg2nAaHwQvhHDmfD+fA62A23A3z4EG4AL4EF8H3YRH8EpZC6l113gouhV3gpXAk3ADHwo0wS87zYR5cA6+C2+A1sBJuhVXwB/APcDr8As6AVhTPL6wPOVfr6B7/dez/9bdFWafx+yLrqdj/mG+M6rou4en4zqjK8K1RM/KkP2YOZjVmN+bQU5HvjSJH5IgckSNyRI7I8b9xfCf6/4sLck7X+n/RrS2t63xY9P+ZstB7o27mJGNxQBd+zAVTLszInLeAvWQzcwvK5pUSZlE202MGXWdZd8e+lpDacjfjHPFi4xyxcS5Y/OrvAZiz+FY60mqOwrAWzSUqfOZTXWvipYn++z7Rf/8RZq29VpU7XyixUvlGwDV3rud/blDX7DHmBeGJ3vekxk97OPf69R984+vn1h9Xv3M9b0ISr1t0+tkz1L1GkZ6XekmFNZ90TG6cIuEd8Prnlnzt63VJqF+vXr2EmEYSlppHUn5Fl34lkT2S7DdvKBO+Lr1jPkjl672Sr7np/nz+UM7zOHfqq+fKunIP4tgY/gzOx09JoSufmbiM1/KWrfeLvEz5G+Fpzlv8gXrPRbmeUKt4M6nzW9t7HGHl6PnPS5TbBE8HfI7C2GHFOsJab/XUYYm9WY9ayv1p5X6hZ4gnxrgGlPP6eklqXlk9hg0lDYlFuPPmtFoXkvldmdu+Vl273eO4trfl0FnopK6N9lTPKxM3+1MN0eVKhleoMCo9yeTGAGqTyzzRjrhk67jEwo+V3wEeh3u6cpf52q+Vey9nfLT7CdxTVHwaO6/X8f0a93rKvaNyX+V3n+fc2/IJ5T6BdVPa63nXD5RdH6sVcXdcV2w59G0fUX7OR4uhv9aDalKs8sZxTY6+VzP4a3XNWLSt2oud3Itcah18nb5XY3hI+ZlsJcm9Gjvulczz2MfHe+t6zFWkUv5RjRO8if7nr4m4TcNtt+3mu3SG035xtf00p/1G7O/y25/vtK+stp9s20+2ZuNWPad8Vgjz12Rt0OnSv2XeWSh1QrNa54yd9W+2Oo/V5zmy5mDNuni4yj/emUmdka3PZT9cqTOOSyX0Ao4e+Dz/LkVaq4pddUZxCVrfzno5N6+s3NI6NDuV/9962vN/HOZCzE4=
*/
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
V8zTsSyoM61cT6FoSgReyhqL71hkKSAjWmd9cdlviVFYxmVX/P1y8P31m4H4+9nNzdnV4CdxfSHOrn5CYD9cXr0E1scwWSHk+7yQJUxeiHiWJ7Ecqzk/3edg67M4jZL5WIpWlWXJsJTVPN+ftracB7CcKCwlt47lJE6l6F2dffuqNzx/c/PqH8Mfby6vBhdbBzvITpHNC5HdpyIv4rSadAIgcBqhKJXCmw+F5X1tKsIhmtyiYOGj+pMsfSeLquHJrLwtG5pHcQpi1QTqVlYg8+Gs4RG1T5O84dEkK2bwWBPDPJzJ2ViO5rfQLIAMd1LmrEqgWq/O+gOhewIFkE6vw6jISConhZQgyGkJspoBwUBe94lOitDn11f9wfDiptfrvA8c04PjOp13WTwWO4GAZ0FtSP/soucPOweCD8twImnsjh4Nw7dxfECYMTXjmbRsI3zKKqziSIAszKPK6bVjvg5Ted9ZfA7kkmnV3VppSO0HR+LAuxiUGP8Jtv4FYxfhzsRz0TBdIKIwSbKoc9QVZfybzCadnVkQnG4BkHjSmQXiX4TKbO8FTfGcJjnVbYwttPIXbodx/FMP5q6FfGc67r0o5yM0ouWp6lFvh64zfvZhi/8rQNeKFFs/bG1I3yGBWkplppWC6zNGsUEM
*/
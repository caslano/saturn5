#ifndef BOOST_DETAIL_SHARED_PTR_NMT_132_HPP_INCLUDED
#define BOOST_DETAIL_SHARED_PTR_NMT_132_HPP_INCLUDED

//
//  detail/shared_ptr_nmt.hpp - shared_ptr.hpp without member templates
//
//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/shared_ptr.htm for documentation.
//

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/detail/atomic_count.hpp>

#ifndef BOOST_NO_AUTO_PTR
# include <memory>          // for std::auto_ptr
#endif

#include <algorithm>        // for std::swap
#include <functional>       // for std::less
#include <new>              // for std::bad_alloc

namespace boost
{

template<class T> class shared_ptr
{
private:

    typedef detail::atomic_count count_type;

public:

    typedef T element_type;
    typedef T value_type;

    explicit shared_ptr(T * p = 0): px(p)
    {
#ifndef BOOST_NO_EXCEPTIONS

        try  // prevent leak if new throws
        {
            pn = new count_type(1);
        }
        catch(...)
        {
            boost::checked_delete(p);
            throw;
        }

#else

        pn = new count_type(1);

        if(pn == 0)
        {
            boost::checked_delete(p);
            boost::serialization::throw_exception(std::bad_alloc());
        }

#endif
    }

    ~shared_ptr()
    {
        if(--*pn == 0)
        {
            boost::checked_delete(px);
            delete pn;
        }
    }

    shared_ptr(shared_ptr const & r): px(r.px)  // never throws
    {
        pn = r.pn;
        ++*pn;
    }

    shared_ptr & operator=(shared_ptr const & r)
    {
        shared_ptr(r).swap(*this);
        return *this;
    }

#ifndef BOOST_NO_AUTO_PTR

    explicit shared_ptr(std::auto_ptr< T > & r)
    {
        pn = new count_type(1); // may throw
        px = r.release(); // fix: moved here to stop leak if new throws
    }

    shared_ptr & operator=(std::auto_ptr< T > & r)
    {
        shared_ptr(r).swap(*this);
        return *this;
    }

#endif

    void reset(T * p = 0)
    {
        BOOST_ASSERT(p == 0 || p != px);
        shared_ptr(p).swap(*this);
    }

    T & operator*() const  // never throws
    {
        BOOST_ASSERT(px != 0);
        return *px;
    }

    T * operator->() const  // never throws
    {
        BOOST_ASSERT(px != 0);
        return px;
    }

    T * get() const  // never throws
    {
        return px;
    }

    long use_count() const  // never throws
    {
        return *pn;
    }

    bool unique() const  // never throws
    {
        return *pn == 1;
    }

    void swap(shared_ptr< T > & other)  // never throws
    {
        std::swap(px, other.px);
        std::swap(pn, other.pn);
    }

private:

    T * px;            // contained pointer
    count_type * pn;   // ptr to reference counter
};

template<class T, class U> inline bool operator==(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() != b.get();
}

template<class T> inline bool operator<(shared_ptr< T > const & a, shared_ptr< T > const & b)
{
    return std::less<T*>()(a.get(), b.get());
}

template<class T> void swap(shared_ptr< T > & a, shared_ptr< T > & b)
{
    a.swap(b);
}

// get_pointer() enables boost::mem_fn to recognize shared_ptr

template<class T> inline T * get_pointer(shared_ptr< T > const & p)
{
    return p.get();
}

} // namespace boost

#endif  // #ifndef BOOST_DETAIL_SHARED_PTR_NMT_132_HPP_INCLUDED

/* shared_ptr_nmt_132.hpp
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
*/
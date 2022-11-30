#ifndef BOOST_SMART_PTR_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/quick_allocator.hpp
//
//  Copyright (c) 2003 David Abrahams
//  Copyright (c) 2003 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>

#include <boost/smart_ptr/detail/lightweight_mutex.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <boost/type_traits/alignment_of.hpp>

#include <new>              // ::operator new, ::operator delete
#include <cstddef>          // std::size_t

namespace boost
{

namespace detail
{

template<unsigned size, unsigned align_> union freeblock
{
    typedef typename boost::type_with_alignment<align_>::type aligner_type;
    aligner_type aligner;
    char bytes[size];
    freeblock * next;
};

template<unsigned size, unsigned align_> struct allocator_impl
{
    typedef freeblock<size, align_> block;

    // It may seem odd to use such small pages.
    //
    // However, on a typical Windows implementation that uses
    // the OS allocator, "normal size" pages interact with the
    // "ordinary" operator new, slowing it down dramatically.
    //
    // 512 byte pages are handled by the small object allocator,
    // and don't interfere with ::new.
    //
    // The other alternative is to use much bigger pages (1M.)
    //
    // It is surprisingly easy to hit pathological behavior by
    // varying the page size. g++ 2.96 on Red Hat Linux 7.2,
    // for example, passionately dislikes 496. 512 seems OK.

#if defined(BOOST_QA_PAGE_SIZE)

    enum { items_per_page = BOOST_QA_PAGE_SIZE / size };

#else

    enum { items_per_page = 512 / size }; // 1048560 / size

#endif

#ifdef BOOST_HAS_THREADS

    static lightweight_mutex & mutex()
    {
        static freeblock< sizeof( lightweight_mutex ), boost::alignment_of< lightweight_mutex >::value > fbm;
        static lightweight_mutex * pm = new( &fbm ) lightweight_mutex;
        return *pm;
    }

    static lightweight_mutex * mutex_init;

#endif

    static block * free;
    static block * page;
    static unsigned last;

    static inline void * alloc()
    {
#ifdef BOOST_HAS_THREADS
        lightweight_mutex::scoped_lock lock( mutex() );
#endif
        if(block * x = free)
        {
            free = x->next;
            return x;
        }
        else
        {
            if(last == items_per_page)
            {
                // "Listen to me carefully: there is no memory leak"
                // -- Scott Meyers, Eff C++ 2nd Ed Item 10
                page = ::new block[items_per_page];
                last = 0;
            }

            return &page[last++];
        }
    }

    static inline void * alloc(std::size_t n)
    {
        if(n != size) // class-specific new called for a derived object
        {
            return ::operator new(n);
        }
        else
        {
#ifdef BOOST_HAS_THREADS
            lightweight_mutex::scoped_lock lock( mutex() );
#endif
            if(block * x = free)
            {
                free = x->next;
                return x;
            }
            else
            {
                if(last == items_per_page)
                {
                    page = ::new block[items_per_page];
                    last = 0;
                }

                return &page[last++];
            }
        }
    }

    static inline void dealloc(void * pv)
    {
        if(pv != 0) // 18.4.1.1/13
        {
#ifdef BOOST_HAS_THREADS
            lightweight_mutex::scoped_lock lock( mutex() );
#endif
            block * pb = static_cast<block *>(pv);
            pb->next = free;
            free = pb;
        }
    }

    static inline void dealloc(void * pv, std::size_t n)
    {
        if(n != size) // class-specific delete called for a derived object
        {
            ::operator delete(pv);
        }
        else if(pv != 0) // 18.4.1.1/13
        {
#ifdef BOOST_HAS_THREADS
            lightweight_mutex::scoped_lock lock( mutex() );
#endif
            block * pb = static_cast<block *>(pv);
            pb->next = free;
            free = pb;
        }
    }
};

#ifdef BOOST_HAS_THREADS

template<unsigned size, unsigned align_>
  lightweight_mutex * allocator_impl<size, align_>::mutex_init = &allocator_impl<size, align_>::mutex();

#endif

template<unsigned size, unsigned align_>
  freeblock<size, align_> * allocator_impl<size, align_>::free = 0;

template<unsigned size, unsigned align_>
  freeblock<size, align_> * allocator_impl<size, align_>::page = 0;

template<unsigned size, unsigned align_>
  unsigned allocator_impl<size, align_>::last = allocator_impl<size, align_>::items_per_page;

template<class T>
struct quick_allocator: public allocator_impl< sizeof(T), boost::alignment_of<T>::value >
{
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED

/* quick_allocator.hpp
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
*/
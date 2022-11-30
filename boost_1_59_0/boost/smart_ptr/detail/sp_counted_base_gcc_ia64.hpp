#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_IA64_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_IA64_HPP_INCLUDED

//
//  detail/sp_counted_base_gcc_ia64.hpp - g++ on IA64
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2006 Peter Dimov
//  Copyright 2005 Ben Hutchings
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/smart_ptr/detail/sp_obsolete.hpp>
#include <boost/config.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using g++/IA64 sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

inline void atomic_increment( int * pw )
{
    // ++*pw;

    int tmp;

    // No barrier is required here but fetchadd always has an acquire or
    // release barrier associated with it.  We choose release as it should be
    // cheaper.
    __asm__ ("fetchadd4.rel %0=%1,1" :
         "=r"(tmp), "=m"(*pw) :
         "m"( *pw ));
}

inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int rv;

    __asm__ ("     fetchadd4.rel %0=%1,-1 ;; \n"
             "     cmp.eq        p7,p0=1,%0 ;; \n"
             "(p7) ld4.acq       %0=%1    " :
             "=&r"(rv), "=m"(*pw) :
             "m"( *pw ) :
             "p7");

    return rv;
}

inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int rv, tmp, tmp2;

    __asm__ ("0:   ld4          %0=%3           ;; \n"
         "     cmp.eq       p7,p0=0,%0        ;; \n"
         "(p7) br.cond.spnt 1f                \n"
         "     mov          ar.ccv=%0         \n"
         "     add          %1=1,%0           ;; \n"
         "     cmpxchg4.acq %2=%3,%1,ar.ccv ;; \n"
         "     cmp.ne       p7,p0=%0,%2       ;; \n"
         "(p7) br.cond.spnt 0b                \n"
         "     mov          %0=%1             ;; \n"
         "1:" : 
         "=&r"(rv), "=&r"(tmp), "=&r"(tmp2), "=m"(*pw) :
         "m"( *pw ) :
         "ar.ccv", "p7");

    return rv;
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int use_count_;        // #shared
    int weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_local_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_untyped_deleter() = 0;

    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }

    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }

    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }

    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ ); // TODO use ld.acq here
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_IA64_HPP_INCLUDED

/* sp_counted_base_gcc_ia64.hpp
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
*/
#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_VACPP_PPC_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_VACPP_PPC_HPP_INCLUDED

//
//  detail/sp_counted_base_vacpp_ppc.hpp - xlC(vacpp) on POWER
//   based on: detail/sp_counted_base_w32.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//  Copyright 2006 Michael van der Westhuizen
//  Copyright 2012 IBM Corp.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//
//  Thanks to Ben Hitchings for the #weak + (#shared != 0)
//  formulation
//

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/smart_ptr/detail/sp_obsolete.hpp>
#include <boost/config.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using xlC/PowerPC sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

extern "builtin" void __lwsync(void);
extern "builtin" void __isync(void);
extern "builtin" int __fetch_and_add(volatile int* addr, int val);
extern "builtin" int __compare_and_swap(volatile int*, int*, int);

namespace boost
{

namespace detail
{

inline void atomic_increment( int *pw )
{
   // ++*pw;
   __lwsync();
   __fetch_and_add(pw, 1);
   __isync();
} 

inline int atomic_decrement( int *pw )
{
   // return --*pw;
   __lwsync();
   int originalValue = __fetch_and_add(pw, -1);
   __isync();

   return (originalValue - 1);
}

inline int atomic_conditional_increment( int *pw )
{
   // if( *pw != 0 ) ++*pw;
   // return *pw;

   __lwsync();
   int v = *const_cast<volatile int*>(pw);
   for (;;)
   // loop until state is known
   {
      if (v == 0) return 0;
      if (__compare_and_swap(pw, &v, v + 1))
      {
         __isync(); return (v + 1);
      }
   }
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int use_count_;        // #shared
    int weak_count_;       // #weak + (#shared != 0)
    char pad[64] __attribute__((__aligned__(64)));
            // pad to prevent false sharing
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
        return *const_cast<volatile int*>(&use_count_); 
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_VACPP_PPC_HPP_INCLUDED

/* sp_counted_base_vacpp_ppc.hpp
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
*/
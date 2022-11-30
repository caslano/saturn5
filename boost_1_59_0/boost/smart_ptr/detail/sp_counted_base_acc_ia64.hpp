#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_ACC_IA64_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_ACC_IA64_HPP_INCLUDED

//
//  detail/sp_counted_base_acc_ia64.hpp - aC++ on HP-UX IA64
//
//  Copyright 2007 Baruch Zilber
//  Copyright 2007 Boris Gubenko
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
#include <machine/sys/inline.h>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using HP aCC++/HP-UX/IA64 sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

inline void atomic_increment( int * pw )
{
    // ++*pw;

    _Asm_fetchadd(_FASZ_W, _SEM_REL, pw, +1, _LDHINT_NONE);
} 

inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int r = static_cast<int>(_Asm_fetchadd(_FASZ_W, _SEM_REL, pw, -1, _LDHINT_NONE));
    if (1 == r)
    {
        _Asm_mf();
    }
    
    return r - 1;
}

inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int v = *pw;
    
    for (;;)
    {
        if (0 == v)
        {
            return 0;
        }
        
        _Asm_mov_to_ar(_AREG_CCV,
                       v,
                       (_UP_CALL_FENCE | _UP_SYS_FENCE | _DOWN_CALL_FENCE | _DOWN_SYS_FENCE));
        int r = static_cast<int>(_Asm_cmpxchg(_SZ_W, _SEM_ACQ, pw, v + 1, _LDHINT_NONE));
        if (r == v)
        {
            return r + 1;
        }
        
        v = r;
    }
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

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_ACC_IA64_HPP_INCLUDED

/* sp_counted_base_acc_ia64.hpp
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
*/
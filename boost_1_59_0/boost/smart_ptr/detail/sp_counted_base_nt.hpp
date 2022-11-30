#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_NT_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_NT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_nt.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using single-threaded, non-atomic sp_counted_base")

#endif

namespace boost
{

namespace detail
{

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    boost::int_least32_t use_count_;        // #shared
    boost::int_least32_t weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base() BOOST_SP_NOEXCEPT: use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() /*BOOST_SP_NOEXCEPT*/
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() BOOST_SP_NOEXCEPT = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() BOOST_SP_NOEXCEPT // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( sp_typeinfo_ const & ti ) BOOST_SP_NOEXCEPT = 0;
    virtual void * get_local_deleter( sp_typeinfo_ const & ti ) BOOST_SP_NOEXCEPT = 0;
    virtual void * get_untyped_deleter() BOOST_SP_NOEXCEPT = 0;

    void add_ref_copy() BOOST_SP_NOEXCEPT
    {
        ++use_count_;
    }

    bool add_ref_lock() BOOST_SP_NOEXCEPT // true on success
    {
        if( use_count_ == 0 ) return false;
        ++use_count_;
        return true;
    }

    void release() BOOST_SP_NOEXCEPT
    {
        if( --use_count_ == 0 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() BOOST_SP_NOEXCEPT
    {
        ++weak_count_;
    }

    void weak_release() BOOST_SP_NOEXCEPT
    {
        if( --weak_count_ == 0 )
        {
            destroy();
        }
    }

    long use_count() const BOOST_SP_NOEXCEPT
    {
        return use_count_;
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_NT_HPP_INCLUDED

/* sp_counted_base_nt.hpp
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
*/
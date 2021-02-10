#ifndef BOOST_INTERPROCESS_DETAIL_SP_COUNTED_BASE_ATOMIC_HPP_INCLUDED
#define BOOST_INTERPROCESS_DETAIL_SP_COUNTED_BASE_ATOMIC_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//  Copyright 2007-2012 Ion Gaztanaga
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//
//  Thanks to Ben Hitchings for the #weak + (#shared != 0)
//  formulation
//

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/atomic.hpp>
#include <typeinfo>

namespace boost {

namespace interprocess {

namespace ipcdetail {

class sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    boost::uint32_t use_count_;        // #shared
    boost::uint32_t weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {}

    ~sp_counted_base() // nothrow
    {}

    void add_ref_copy()
    {
        ipcdetail::atomic_inc32( &use_count_ );
    }

    bool add_ref_lock() // true on success
    {
        for( ;; )
        {
            boost::uint32_t tmp = static_cast< boost::uint32_t const volatile& >( use_count_ );
            if( tmp == 0 ) return false;
            if( ipcdetail::atomic_cas32( &use_count_, tmp + 1, tmp ) == tmp )
               return true;
        }
    }

   bool ref_release() // nothrow
   { return 1 == ipcdetail::atomic_dec32( &use_count_ );  }

   void weak_add_ref() // nothrow
   { ipcdetail::atomic_inc32( &weak_count_ ); }

   bool weak_release() // nothrow
   { return 1 == ipcdetail::atomic_dec32( &weak_count_ ); }

   long use_count() const // nothrow
   { return (long)static_cast<boost::uint32_t const volatile &>( use_count_ ); }
};

} // namespace ipcdetail

} // namespace interprocess

} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_DETAIL_SP_COUNTED_BASE_ATOMIC_HPP_INCLUDED

/* sp_counted_base_atomic.hpp
yq4m90vptCx+KYYi4pey6aF+Kbua3C8Fagn9Urqofr8UGjPsl9JE9Pml5PHeyi9VBpHFL8Xlsfql+DR6v5SRRemX4qhifimrJu6XYigifimtHnqmXNb3PTiZ1S/F52L4pcqhsvmlGEwWvxRRX+GXoqgr/VI0bdgvpVFGz6Qxf1IZRBa/FJfH6pfi0+j9UkYWpV+Ko4r5payauF+KoYj4pbR6Nr8URxXzS1k1cb8UQxHxS8F6Yr+UNnLIL4XHlfildFF9fqngD1Ztf4vqdp49pvPl9ifF938N+9Nk/PL8czZO8xG9Vn/QLRR4eeX87H9QSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAACYACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTEvbGliL1VUBQABtkgkYFBLAwQKAAAACAAtZ0pSMEGd8ycAAAAzAAAAMAAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkMxMS9saWIvLmdpdGlnbm9yZVVUBQABtkgkYNPX0stLTuLS19LLL0jNK05JAzFhVGk+iCotTi0C0WXJFQVF+VlcAFBLAwQKAAAACAAtZ0pSqRJ45gUFAAA5RwAAMQAJAGN1cmwtbWFzdGVyL3Byb2plY3Rz
*/
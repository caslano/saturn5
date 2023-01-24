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
/IDThEmCFTs+8L8DUWDaxXOpUplTyTputRLwmPD6xPpYQlgHZLZoM/bOHhi/BmwVVzTM+kCmGHGlZ8qXFHYyWXDq4q/ebKRwC/fSAE6HlDu1IW5PzMinv3QOrQ+VJm/brh5HNAOQZ6Ovnx77EGc077s7i6A5LvojJ6ZxaE8WHE/UnN10zZy7v0giwOkvf3YPBnh13MQnRqOaPYChwLd3fQwPGJGBSM2nsYGjTRuNFt1TTh1EBS+KxFa1PvpT/LdzYFgg8KI0KlCxs2MIupqMk4uPm3G7unfk18eypvez9hB5ezNYUCvLyej83iTWky0kMXY916IybxmGZCuHloWeAfbBCQsky/NgPRwjMPp9/NRLJBLz75JYS2hMugfv/5LE3IL/RRIL47hrzzbdrygPRcSj9srtAFFx32IkKgT99THxVkib8Jt6GW7VB/o0y0PL913AiFdMoHOW2iOD8c2NRPHlnSquyqQgeKNsaBjTTPPHpruJ+bmnourqhfgmHW+OSnartTVYVvoK/Sflc6NaUHVOw1UXLKcBspjbABG/z0pPM8m6sdc98QCHo+59HgphHRYltaiwIPRiQel/BdVNHLasEL6tvVBLeYrLW+9USUV8jwVkIChDjUJFQ/1C619svRqgU/7Wiqa1obOPTBHvtkND/0CRF0L0cDOXb5HHSsqtEnZ4kcFI0Vb6F2VtoCxvx+/WZZBEC7x6ffS3
*/
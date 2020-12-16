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
jX6bhh1fi65ptG/PkGkNOqerwFi5PvgMPf8z5t/7FGvSHF5+d+JHQmq63M9een654yO2RfizZJFuNaWRhmMWEjnPHxNdNng0TNe5t3wPcp4eJNqrHGnaRsgjTVF++z1LNG7HX7RIfU/k1f3i3nirTUSO9w0K8y7231cSzb0+24xiE0Jf1/iQaHagNIN5fd8f71j6ThyBdpw9BHxEvl1RCa6oGJcT29ZW24lMWzbEbztxMO1PeV9xReML0KXcA+cwm4b4dcxzZTttQ7MXNBEiDwnrS+QesJmmBTROQRO/fmEgmjOgiSQa75/kGGCmSR+K/krl9b6pj89M4+dJLmiifTQ7XVFxYIqVJ0nwO+GPSWJbjtz3XCF02N/ebziXA35ffaCTrMQtG3tNCj121nnmvsB66T8jOmq7NDf/Y6N57bDbfr9f6gifOg86wt+eQLquRdvzTj2yYmzNiJbX3v3om4Pbr8P7OsXT+8lxB7fvmn36+ZcP1z82urApsI6tWre363STu0pH+LOiC6w+azKwjrBad7v9Z2J2pU7xXoNOcSuQdYr5mmQdSW/xQQ18k9c0DjXwnuw/+H4PuPflNcYYeR1puI7msJPhIgzXDhkn9vN91/fC/Z2vMx0G25RPyPM0G9ro3U02nuPJdNFMpz7XkuV5AQlB4msRtEwX4/DR9YQ7zHTfA1088Clgb+AzwJHAZuAs4AvAucCjwArgq0AP8MfAG4AtwA3AnwC/DjwG3Ar8ObCWwz3C4fYBTwBfBL4B/DHwTeAvgb8BvsHPW4G/B74PfBv4EfB1oNMh/KyfrctVIiyXqw/cW1yuU6yn+nfgeNZLLWC91BLgR6wP/jGwEoiIvF5ABPBOoBN4LzAOeB8wGrid/Q8AY4C72f8g+x9m/83ITzzwbmB3INoypf84UKT/NDAR958FJgGfB8ax3mkC8DW+/zNgJPDX7Od6Z7krdTtCO5R0QdrR5yUdyzkh7SDxeXWZG5JdAp1ZL/8W5vetwAuAtwEnAzcwv29nfm8E3gy8A/gN4Cag0N/9OjAH+A3gpcANgh74TeBK4J3S1irLHeCa8mu2tVrFtlbXAPsCbwBOBH4FOAW4juNZq++/Iw52dH4Wx1Ph8MVzHbA3cDkwS8QP7C/ogJ8HrgRO4/vTgauAc4CVwHl8fz7QA9xDfpk+7XsDCxXpXw86gWuBbpFvYBrwRs7PN4B9gF7gAOB64GDgrcDRwNuAE5luEnAjsED4Of0j/v1e4GOcvoj/IKd/J6d/FzAKWAOMB34b2Bd4N3AocAvwQuA9wLHAA8BxwO8AJwO3crr3MT+2AcuZbhlwO7CS/R7gbmA1sJ774x5gDfBR4N0ir9wv9wH3inBcnkZ9XxI84vIki3i4PG9zeU4Bo4F/4vK8A0wC/hmYAnwX+DngX4GDgI4IX3tuhT8beAY4HvgP4GR+PhX4IZfvHLCE/SuB/wZ6mK4a+BH869gv8p3u4P0wESfnOwvOJW6w3nskMJPb3+eAQwQNcDj7L2L/WGB/YA5wEDAPOBR4BXAY8CrgcOAS4AjgtRzv9cBs4I3AUcBbgTOAG4EDgJvZ/03gOGAd8GIe78YD97J/H/u/B5wIfB54CfAV4BeAPwZOAR7jeN4C5gLf4fjfBU4GniE/n0fg31/hvZ8GHqdu4nqdxfU6G5gMnMP1Vgy8AFgInMD+icB5wEvZPwe4EHg1+4uBVwC/zP7VwMXAG4Sf83PcvwcBfILzkw53lPPzJOfnKWA88GlgJvBZ7peHgBcDX+J6ehmYCzzC/eRH3I5e4Xp6FVgG/DGwAtjC/eV33K5+ClwDPAa8Cfhz4G3AXwBvB74B3MH0u4BvAhvY/yjwOeA=
*/
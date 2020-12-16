//  chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_INLINED_CHRONO_HPP
#define BOOST_CHRONO_DETAIL_INLINED_CHRONO_HPP

#include <boost/version.hpp>
#include <boost/chrono/chrono.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
#include <boost/throw_exception.hpp>
#include <boost/chrono/detail/system.hpp>

//----------------------------------------------------------------------------//
//                                                                            //
//                     Platform-specific Implementations                      //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/chrono.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/chrono.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/chrono.hpp>

#endif  // POSIX

#endif

/* chrono.hpp
o8PtPbJMq+C9RyrDC3wV5e+WpzC2Gmt2orULtw/J+RfRmDYC6Ssp/YpsLzKxfmjA39GA5Y4azxPubYzZJEfxWyS3Vy6FhX5gOfRFlnMEt4sRA34Fyb0pPTICPL5+SSzGmP8J8diNb3pcT+lMzvfdw1pTVx5bj+L38ftaxRU76O53kHx1Oh9p31mRy4/69lzbGWdFLjFobbv6aJ2qaZ19tLbVtE4+WnI1rYOP9t13Bq29j/ZxNc247wff1Tyj8ppB60rpeUa6A6X7VOt/wc+o+J6LU/xcJPKzHePbo/zeeC6Cx0PjuSAeSNJZBmq7c59lONtZlEkcN3+SftvQl3gP7cBhQxfaOg6zR8l8GUZ/jTmipx/EDMfF4yreekm0lHB7ylxGY6P/mon/rZB7yx7dZpTfktKTDPnWnI9RgvLNfmdOJhuyvSmvrfAyby9KL4BN2mJq6vKTudY4o5dMPKmcpvJ5P5Tqg6vUqEsnymsc6lmlccxD+YM5zWWhpDaYd51BvzhjR1ugTbUye2+L0lz2NvbmwG57I3sT/NcIM7Ao/Pwbz+4iN50JCHu/XCo/O/h+AedhFp3HN6RCnYcJ3p/vcZb9+dVRgq7jfE7jPcA1GPf2Gb9r9L7HcPvzzNfQmHd/R+l3RH/8ewf/tqdRn9FPupbzb4NPLonk4pH+mtLrxEDothIQPCfw8u+idlLnexj628V0QH3YTG/yw9DtdBz9/tPfk2o5Fwiy42R/O6aRzUjvAJtlRJM82Us3n5PHi7XGeEEujXA2Y74EY8w4VYsxI4SeATrNdoY+O1ZpjBtwb5xl3ADf2c6NIT/8ubEnkec7N9YBtkl3nv+5sdsPn/3c2HLkB58bO3P+djvbuTHDll34g00P0RgMzGPw5m8NW5IbI9Q8CTzG+DsY6QOUnoo4clc4fwbLNCaZEUi/R+n5KFWG822wTNew55V6Hg6cbx8j/kGwYLIxh/uYaPnYE0w2xuoUkjNTOt5IO3m8MtLB45vxe/MZlVmGO1n9xsRznpPq/0vOpfnP0z9wc4nQJQXor+x/Kf3G13aG+yW4/Wh8uYf4Xub29Mm1COeH4fx0Y3y/g9LvB/tjaPyaZPDfJjLxlM6ABiHaj/rNXcT3e7/8XHogfL/JDrLzlaHWD9QOK0j+TyIJbWCm9boO1BY0tyz/O3tnAh5FkYbh6pkkhBzkJAQIEE65DfclEA6R2yiIgEgIIZwBYggIior3hYKIioiKiooIGllQRBBUjqiggAooQQFBQFFYL9YV1/36n29qru4QDt3HdfqheFPVVd3VVdU13f1/VVWKd3cZIyznUbVyJoyAH2XvVz/dLWxEGYE2Il0/eQnWz1rrXX2nvH2z+7TrPxm34nnpP4O2q3OzXYVEmeG5n2Xef+mTx+sVbI9yLD46K+LvabuyGj+HZ0exUayiHWu2/uYo3zxlXwx4m7sj5PinDNqfLgNbcJxTK9pTOnO8Uy7HO93O8HtpX5pF+9Ic2oEeoh3oadqB/sFxQ0VMp+0qP9nb19JpV+lEe05nbztOCekuZrpuTHeJlx0t7afzZ5eT+eR5vBcsyvVejoubSbvcfRxP9hRYH7yf4xRngV3Bhziu6mGOm3uE87POA7PARzlebj44E3wcRJhaCD7B43J8F7/9oIe3GN/1PK9rMcd3vQi25fjCLuAyyYfvuMKR4HJwHP3jxU/7nvsbCb/v4HyidWlOrdyXtEN+xes+yuN+w/GAx8ApnPd1KvhP8Fbwe17ncfBBzge72DwHuAT8hfPD/htcBZ4C3wB/43yxv3NcoNnJv2MCLAKd4Iecj3c7WAbcw3l3PwcjwJ/ASPAXzsP7K+fhVWYdg+FgPBgDJoI=
*/
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP
#define BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace container {
namespace dtl {

template <typename T>
BOOST_CONTAINER_FORCEINLINE T* addressof(T& obj)
{
   return static_cast<T*>(
      static_cast<void*>(
         const_cast<char*>(
            &reinterpret_cast<const volatile char&>(obj)
   )));
}

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

/* addressof.hpp
goWR8dqrXfzfZ1istOYU8cYalkBmxaxz0pgCWJK030aHFk9haWR8DuO3z0uCZZDxuV9XRWyAGchsmNXIWFsFlkvmwCzq7AI9TPxufM6vCuzjBFOT2TE7+ijxCkxLxvNc4LogGKYj43le3V1jK74fGUiGa8hOESnMDHVOwOaS4TMIMpEz7O9/YH9I9luX4Ch8dzKZDHP4h6zh7pAxsDQyH2aX1gZugOWSmTHrt671Udg7MvxskEy4ZyXqYWIm1c7imjuokmAqMh43u9sf02FqMp7nieHBPjBvMltm0cfHrIDpyHieAYWhZWH+0pq1F72IhAWRWTF73SZiLUxPZsryHOXrbo+/mRNLhvNlD9nCLgsqwxLJHJl1mLnzGCyFTM2syay9K2CZZDbMbHpaboYZpP1+Gb9oKixfsh617T/DzBJoTR53+1MPmJrMmpn76MtNYN5kfM2YOMtJMJ1kQwvU3WCBZLz2yCpZ5WB6Ml7797bfq8MSyeyZ5daI6qL0jMyJmc8q/E2usSKT5bJXRIuLs/qGwHLInJnZ+NquhIlZlCez7oNsa8LUZCpmm4b03A3TknkyK+t3IwsWSObFrFGpS1H4Hm4CmXexpYt6YvO90aPw/et0lss+iiuIzO8GyyZzZjbm4n9ZsHwyO2YtjjfdDDObTT1j1njJFkeYN5kHs0eVJnWH+Utxzfr1VXLRk6mYef7SKBaWIMV13uqUCEshs2J2rPblQ0rtZLy+mdWnzoAZyHh965+uLafUTubI7OAcV41S+xzj/YL9l0XD1GRqZh0GbG0E8yVzY2bXd/ocWCBZeWab/X/zhsWS8VySXvVKgiWSWTB7PeH0OVgyGa99oX5TC1iGtKaTp+ckmIHMhVm5LkGfYIXSmpU8rg9Vap9rPKMpuR7XlNrJVMyGNYodDfMns+P1Lc0aAQsj430xXWzxAJYg2an0KQWwFDIzZp/vW5yCpZNZMxu57pMSl0lmz2xtqd4aWI60ZrBls+uwfGnN93s3H4GJecZrZlzf/xtMTWbF+/LwupKnN5kts+zlXi1hOjKeS/7reWNh/mSOzP5+bTDAwshUzC7euNEFFi/F3V8ZEAVLkuLmHt/aB5ZG5sBreLD6odJPMj6jp2PuLIblkjkze/frA0eY2Xzj/Xrt2XhE+b0XMlzr9otawmfXyQMwfzIrZoP89k6EBZFZMrv/1W0+TE826Kf5k1FuJzfWhuWSWbO4Oxdn6vDaUchyOSBixJur1vuV+4kFxTMSOt1BUVekxm0zg/mS4X0/mUgpX7MKruV6MtzvHhJDRTlH6xaweDIrZs3NV5WFJZKZMfMI8P4TlkymYvb0hd4Pli6tWfesXSYsk8ySWcSdBiqYQdrvcI3BfWGPyPB+k0ws2dilCyyfzJbFHT9/+ADMLNFEVOS1H7GbC9OS2TGb8nFGHMyPjNcwIHraV1ggGe/new+3KbAwMgdmPo093WDx0n59xu7YBEuSLG/axZGwNMn+HDUgUumnZL36X20Hy5HMfP7WpjgHC8lwnh0W4cLe2eWC8vcqF5bcXx8Rg4Wjbp3yt4eDyBCXQY9W2QPXF9lokUjmW/y7V0dFsPCrHTESZra45PwkExWj2r1S3luQuRaf18dEfzHG58o0WBAZ3lOSieczNlaHJZDVYbYhsd56WAaZJbNfk112wLLJBhQ/N8nE19h9M5Vc/jARw5ldbR23RFmTzIatGbHm+eAi04tsMmFWVHsmWdi1pcvxu2zhq0veP5yl2nsMje4NiyXDOU8m2mU0VF7HEsnwe/rnRLSoWTFD+R2q+DVk5kV2VYwXExv1LFVkg0WDLSWf29wQI4RdTv2uMF8yvBaTiYXNu32EBZI=
*/
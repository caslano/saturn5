/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
#define BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

    // Here is where the magic happens
    template<typename T>
    using traits = typename BOOST_CLBL_TRTS_DISJUNCTION(
        function_object<unwrap_reference<T>>,
        function<T>,
        pmf<T>,
        pmd<T>,
        default_callable_traits<T>
    )::traits;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

/* traits.hpp
qfqpg+6EumxO3OzWYjOXBq7BVzRf2ePEHOXBuEc0MgHwb8d/31A22BUwEdia6/kl7C4kLa701x5Zr8lI4f9ouldb3WGHOTPe6IA35k9VL6NqsLhi32f9wE54Iqy/as4Lr8mjhyCeqF/iVMe1X4fZK1t+VPb7dBKGeagCuwOrA5EavPH/L1IVAORlPWhPEXJR58RismPI/581BzKJhXCGUSBdw+BN+8oKaIUVcGZ0/Rn/KSeFGW90MYFvWd+8C2dfT1psNVeHMxeRS7t+NZmJBLURpdOuDA3xwQRm/Z0Xos/DmHw8T39nmeTrCq+PFgtWSNtCJwehgCyBNPYLZqh9SCpmcA/WqtfaiHhY4qNuC5Gup2Hq+bSAfG9PxJqRyjkAUeeMYMLRqLJ2PPhaxA0VuXzvK5P7xh+XVg3xPFg4CdTVAX8e6/AKX9tRQATjqpVsj+JDU0hO4lo/VLIA7pdRuY3+sruBJlV1QikfdMRJjQY6Ghr7qec3L5q81tnqPLokUw2Cef8RD3L69pcUucUjIn76DqkzW7iG8mycWmxfEYQcVCBcpwh+e5vHAw==
*/
/*!
@file
Defines `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>

#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename Predicate, typename Object>
    constexpr decltype(auto) nested_by_t<Algorithm>::
    operator()(Predicate&& predicate, Object&& object) const {
        return Algorithm{}(static_cast<Object&&>(object),
                           static_cast<Predicate&&>(predicate));
    }

    template <typename Algorithm>
    template <typename Predicate>
    constexpr decltype(auto)
    nested_by_t<Algorithm>::operator()(Predicate&& predicate) const {
        return hana::partial(hana::flip(Algorithm{}),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_HPP

/* nested_by.hpp
v5xi3glwRP7v2ITonDKDrjZZZB7tGWRTW9EZ2taIy8Rnziky8dkWRSb+4twQmSjGL3mhcS3NnSNnmjVQWFwCHAVExvPye1/vk+Vlon9HH5r9vppMEQLjRd9v4ct34lGD9QRZaiIHbJ0VBtIqBMz+ErOxxXhE9O2DCFkfZjWKzx/EhC1m0dfVRzcBth/DZ5/ok/DZJvpmD6Kji+4+dHRxEv7bzvEjSGfoQTRATiMJZ5M53y165vUWzWqR51laa9/7uv0/s5G6N7Mhj/7PjUGRvQJbOMh+2xk82YpZElqIr817hxCtrBwrPu3DWAyaxzAIzxVefjcKyrbfF0AL1y8jED3Y+GncDQf1uO03CrUGGh8t0DKkKY7oRgGvK1o7cPXCGtDv3I7JRgcWkQhLwOLZ2vlPobXXIB6TxJ0Mj+cxfLFIayXSj/B3vg02Ao7TzyvYsOThREYcopDZ2qZCuF1JD/alGCP5S4cSm/P9J6UNV3eGWju2dnhSVvd/LfpaMZv9on8PVg8o/wS1K3dNldFzTSm3K83XvFpn4XbN97XAk5wVfe0QL/i5ocRvmiv6EHmGO7o/adoKWTUHuwwuQqNxu02+fZDMb/IFXDqLi8U0trik8TXYLpja2pYPDG4Lcmg2QUfexBi+Pn4CsJCvh9IdKw5JI/AReh7kq+1rPqkhGHrTQC3a/wP4Awrtf2kvUgxZY6/CGkuBNc7z3cAO
*/
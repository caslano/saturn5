/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_fwd.hpp
 *
 * This header contains forward declaration of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t Size, std::size_t Alignment, bool Signed >
struct emulated_operations;

template< std::size_t Size, bool Signed >
struct operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

/* operations_fwd.hpp
M4SyXiHXlRteT01OLUqtSB2nOut7LeOdD7J0PuglY/9GawC5l9LHfnOCu2xFGaE6bnjOW7ZTVKaGk0mDoxsbKhzdYFh16YpWDErqEQymLiZ6PAOaYTcIvZmmehIa15PkGvfo1/jNco0xj+P2N9f4R2Tb495rfHM9/xPZP0bjIfnHRLdmIz8kM3Q9v6ElSrdUpgiZFW16s8jolkdmCTIr22T2++lWaI47gtw6GUO/pHnSU6fTFj1Twv03cBDnOUJRttqcS53K6utrw2M7Q+qQFvZz6lo3Ph0myP5uGsf6WOLpUpbTOQ5DWWxXZ6HfNYT1lGepznMlhAZCLWGda9sG1/XxIcv3N41jM05OST8g18G23JOgU5HPf2z3vYOu+222OXOY2onboftyuUaUbdTd/ZxItnFtpeuI67UZ2+bZ3ntyvceJ2G7y4Fztc19vtun1jm5fabaHrmG0vD73VEUWbRnxDEuPF3n/YHyxPpVtZCPWpx+t69NXue6p+nDvcHiD3DuUL6u5ooSjloiWmGsMvfcP+7JV+b7m/JN2tROfjZ2d7b0mN/dLXUWmkLkiSZ8haD4RaxTQni79S5I0PSReaeSzYurzpKt99dlcX/aW/f3xsp3qM046fs+2fYT2j26bBL06Vui+j4Puftin6+nfqv2wmfAvMm6U8jU6z7313pZjRD9bNNd6t4v8Cus48r6MoP2j+eT49t8ssz9L1zqgHBK/yurJv4sIsc67TrEfF9nT5PnIGNpRzono1ZDs0Ll1juU3/yFDG+u5NXGi93mGkVmSHTq3llre+a+j/RP9XNjdZ/p9lPbFJTltGWQRjtPQq4BjXiN9Ube4RG+pz5sy48ypU84qcZoEmfBzsbrFVnhsaLosd9lFr4b7FjvXXW4d9+SnZZyqZTzgU8Ysylgaq4zVFStKqhuWLEEu3M5HL4f7mHt6Rx8zk2M2xjpmzbKao7SNps0S/doteukkWNhQXe7STU/7XdCBcvu0n3mWwnHYZo4T0fc39ImuY88C8olZx4a6ytj103RZrnFXw/Rk6mb2m/HRybpF6jTH8Mwvw/tG1yuNerVG1GtiqLv0vi26Pq0fQZf3enT5FC3bFp+ypVC2g56yGRXuhA6HjlXTL/pYORzLujbyWKjuUduCNEZ3n8/w1V1kOq+7e310l+N4ddf0cWH/6Lp1LSBXb91Q2XbqpfJZet0bpbPs77zO7vXRWY4RobPjtT7P+dTnjVzqaeozb0L+yajE0ra6/DHXZ+71lPXBYygr+WlZI9t594Docr2FbGlkuZaXLWlAf2KXDXnvuw1zrZ0JSz1ln9PJsmdEPEPmGHF/+J/Id1X/Zu9M4KOozgA+k82GwAZIQgghXCFAuCFyKHKJgMhNFFQuCYEEEg0hQMKhqOFQUanijS0q1gtbaqOixatStfWotlC1pR4tntXWgyoevbT/+fLt29nZ2RC82v6a+eXlv2/me+e89+bd70eniP+TlqUVn/vTD3a/V3lSfsbnFzeuq/qy66o+cdIvikv69moJZxG/50R+S9u6EvOX83u16/dK1++ayG+pi27VfvLzXL/Pcf1eG/kt7dhSu64sWKK/L+N3tf7G+9Yy/f05v9fo7zaoD9GTF3Xeh8w5kWcpsBzFJfvLt4MXwy7wMjgSXgMnwa2wGH4PLoOyrzvcDq+DN8Nt8A64E94Gd6le92vXMXnaiD77td+JXE+4S929DxbA3XAWvB+uhg/CDfAheD58GG6Bj8Cr4aPwFvhzeAd8Et4Fn4L3wF+qf2rD47PwFfVPK4hZuX6t8fAcHAyfhyPgC3A0/B08Ee6HE+Dv4SnwNTgbvq7x9abG01vwMvgOvAG+C2+HH6g=
*/
//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_CONST_HPP
#define BOOST_BEAST_DETAIL_STATIC_CONST_HPP

/*  This is a derivative work, original copyright:

    Copyright Eric Niebler 2013-present

    Use, modification and distribution is subject to the
    Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    Project home: https://github.com/ericniebler/range-v3
*/

namespace boost {
namespace beast {
namespace detail {

template<typename T>
struct static_const
{
    static constexpr T value {};
};

template<typename T>
constexpr T static_const<T>::value;

#define BOOST_BEAST_INLINE_VARIABLE(name, type) \
    namespace \
    { \
        constexpr auto& name = \
            ::boost::beast::detail::static_const<type>::value; \
    }

} // detail
} // beast
} // boost

#endif

/* static_const.hpp
MszVrVduDwF+OOMWSKTxSP9E+TDL8EmTw/FyRAEE/Z/OWpQWVJJyCPpTlypTu0PVk5H/qciCuLUI5UEkG/6Hou/fbBBMwX69q7hVfAxAv8UrvO0N6yQpslR8sYmLe9XZIMPpX0Nqmohy+slCv2K9TTO04v/GnIT8mG7FEfj8TEQjKTexdfoaxy17AiMSpDrMNHcNRE/YSJ0JKISLA2BfuNo4EcLxQANG/u27zfgZhD1DKHaXbVgmE15JtvfRyO3daRPCBPOdkR0GPdeLD9436YTEjyQg6k8qjegcITwr4C0KynsSjmTK3bzsOnEBvU2tAiVforOC/Rt72exWAURUDMRdCKeJQt2Lvaaf80ql/IMo2n+efgvDpZbCmWWJ1OAS+T1B4AVR7PQolq7wD82xiHE0oITT85OGbHoeZQcCZTkdKHdY2KZDX1nXyiM98Gvdd2s71Vj/kH6BQTxzQeRloBe5WPbSf0/ZQgRLG4MT2ZUH+bmWrr+AhjE83s9mPSi0IBweJCt+KSHYU0i7BCTCynxM7Mm0U0Tvk24NaOIIKcvqz4YcehTFa39HHg==
*/
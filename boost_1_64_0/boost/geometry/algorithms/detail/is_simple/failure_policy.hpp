// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP

#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


struct simplicity_failure_policy
{
    template <validity_failure_type Failure>
    static inline bool apply()
    {
        return Failure == no_failure;
    }

    template <validity_failure_type Failure, typename Data>
    static inline bool apply(Data const&)
    {
        return apply<Failure>();
    }

    template <validity_failure_type Failure, typename Data1, typename Data2>
    static inline bool apply(Data1 const&, Data2 const&)
    {
        return apply<Failure>();
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP

/* failure_policy.hpp
WVdQfKg71Dx+3ORjTRrHeUpeT5dZbLyohjt+W3krFrTz0r9S8/YpKwdxHpGsRD3T91vVti4nWWmTRrR25BQmxlYsi+Xcra5XXmHlpJHafG/dyqvo8n6vyvuclVd5RPKW4cfE0uzpT4G8fa28L6bylrWoP0pfr6f71Xq6a06afq5SNWcIE2+TXyK5rv5a2mtUK+FUGFo1XKLx7Ym25/FB1S6vMbIGMbJa27OiOxfOXX41wMK5y2sDbBS9STJRqU2xXylx63RKP/964JRn4OQwprOgORz7Kba4P0OUuVJWx5IPq3q/4AiRN/st+Any81P0+93Ab7ffgtsR9qQuzGeKsDssbx8R9gvL+5sJa/WbkeTNTy5vPrdRH/yow9T3VXtSHxTRaAFP+ovHwV9EkAGjMyurGCP3XvgWRwOrTI67RKdz4zS97cfTWZymIL2N/Ap5AmYmnyo1s/NkCneoermE4QReIvPzg04KL0wlvj9WMIgKsUuf4TEatSJNDaNRqXh71uYRwxuTw2qSMDZMeaSNyJn3MjZLjBLl92UpTRQXSVLpm2BT2yd6WN4+T7MYQp2uHfb7HsZIlRzvjxar5IvVbLzjKZ/puW+auuIy9ADL1q3DlhOm1usREiNr43M2Ni9QpE2S+4X7BJYeBKfIPt2/CBxFRJWw77PQyWyMmVlyH6eTw5083jvPGIoQYkcwxvfHZmwzKRYa8Ex2k5Gy3tY6vLQ9jdvyd8a1a+z8ib8Dhx6mfdf+Cp0ENxPR/LjcqxHivK9Gxuejm4genlkLcbnP40GKm9vcPzCUG+of7t+ovdUXc+S34G9KGvJc2j8sPjQyEojg9CM82Gvzzyh+eBflQz20Hh/oiOMzLnQgy/cfxmUZfP726mWc88DyH9VLc4a6fInr8h/DuCr/cYxL+XJdm/q3sdbOjzsbLezYqfgJz1G/PU/opTqgM9U7RfnAzGK5Ysv3zPi80AGpTF6eF+RlfpgXarJCj/u48EksgZpJw8wdq/tGeLkjm+bEJDZ+i7J909pelSrWf6+a4cVyEzyteB/9fh2n6BKfQ/mizfo+5x1ZXUTf9f16ySYwreDTnmnxHhFbJ8hstRbXyQlqH7Y/5QPyMFcMRRgzaNcG9PvENh2257mdkf527xNzMpFfReaJahlv7QnL6EydcevvNEqTmLQ2MKjt6Vy/g2uL2iYPIJ2n0y81a7nzw7YQ9eUHUrh9hatWp480z9UeJHA3XeTidkpsIl+oV2rk1ylpu/r3bwIxZu7uyjcm626mycd/JnOgVnph32FdjNl43P89i7DgHY5DOMzzO8M2E337Hb7Q4aGOeD2ScU0PHF/Rw2LGmurhSOZEejiAMd9XOWwJY1GaSy2GmUMbkfuQm61do4PBy+Lt2auRE/cRk6q99lAe0jhZH6VPYNn785ZJjJa6q1VSC6+NRhyao3JprMjguTEcTKqMp52iS2NlljOBSf5kh8dXRTjpsWl8WkPw+FEZ3HUQLo/PyeAug9J+js5wvGPfsSdOsTw7h5zr2WWRky37k+dmOTSG4vXWDJ4dRz1P4Nk9wMdKLNHrfXWG05Op97UBrtf7uoAT1/v6AOd61+PH9X58gMf1viHA9XrfFHD0etc5XO86h+td5+j1PhRw4nofDnBX7y3ORdq+pYxZnbhvebPqD4ySPHTV46lrhz9pfFmurSGHn49q8V4sny8cwY7zda7S53HfauI4u1KxEq/Z0veSMdeZL/Q+I2ORY4ry6rzQQSW9aLzQUZ2F0948NnTn5i9i3Z2v+vkn99I+g57cxuOwn8GX6wVKXRPPjJ74DMaps/JoYsZxX6TZhkz1r3z278UaN0qZ9TsGPnbzYPWsXE8=
*/
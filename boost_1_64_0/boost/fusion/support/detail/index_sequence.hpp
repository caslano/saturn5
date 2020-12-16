/*=============================================================================
    Copyright (c) 2015 Agustin K-ballo Berge
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SUPPORT_DETAIL_INDEX_SEQUENCE_06232015_1038
#define BOOST_FUSION_SUPPORT_DETAIL_INDEX_SEQUENCE_06232015_1038

#include <boost/fusion/support/config.hpp>
#include <cstddef>

// GCC5 has O(logN) implementation, see https://gcc.gnu.org/PR66059 .
#if (defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304) \
 || (defined(BOOST_LIBSTDCXX_VERSION) \
     && BOOST_LIBSTDCXX_VERSION >= 500000 && __cplusplus >= 201402)
#include <utility>
#define BOOST_FUSION_STDLIB_HAS_INTEGER_SEQUENCE
#endif

namespace boost { namespace fusion { namespace detail
{
#ifdef BOOST_FUSION_STDLIB_HAS_INTEGER_SEQUENCE
    // Use aliasing templates without checking availability, the compiler should work.
    template <std::size_t ...Ints>
    using index_sequence = std::index_sequence<Ints...>;

    template <std::size_t N>
    struct make_index_sequence
    {
        using type = std::make_index_sequence<N>;
    };
#else
    template <std::size_t ...Ints>
    struct index_sequence
    {
        typedef std::size_t value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static std::size_t size() BOOST_NOEXCEPT
        { return sizeof...(Ints); }

        // non standard extension
        typedef index_sequence type;
    };

    template <typename Left, typename Right>
    struct _make_index_sequence_join;

    template <std::size_t... Left, std::size_t... Right>
    struct _make_index_sequence_join<
        index_sequence<Left...>, index_sequence<Right...>
    > : index_sequence<Left..., (sizeof...(Left) + Right)...>
    {};

    template <std::size_t N>
    struct make_index_sequence
      : _make_index_sequence_join<
            typename make_index_sequence<N / 2>::type
          , typename make_index_sequence<N - N / 2>::type
        >
    {};

    template <>
    struct make_index_sequence<1>
      : index_sequence<0>
    {};

    template <>
    struct make_index_sequence<0>
      : index_sequence<>
    {};
#endif
}}}

#endif


/* index_sequence.hpp
EmE8Zqu1azpxb3H5+u7+CfEmogulJmXzcF5sVg97dlvOngjJWVmGcYoa3Ng6gTycF5TUpn+QWvPWz+3z1+bX5ovje8fjmRXeAduyApEmxMwdg46FVre2Ti2G08HJOnum/zf/i9FF9gziFKK2l6iMVUmuFp9XQdPHM+O1j+G9ynKnS5Tlf3JvUhi2cY0/htotOFWUwTrUNLtp926LqcJ5QCke/yf3cP6Ds++YF+/VH0PzVxpPtRmGObR5PCccdW0WIkQj2f/WN10M9yyzk2Z/fkdbzm2brXDW5KHN07H9ro4zWu6E1uZ/cvKL+fJ01nB+GrUzZxGoFaG2c//FcAfz7M24amVvmmDiYBNBolgbv8Pah9ohZOROi7Rsx+VFF6f/S6jMLKhwRehqytyV+TVUpvLaSM+HOTi82Xff9t/7WHd3SxVLXm4O2Q8ac4RLGOct5gVcKy84j7XOazuE/h78n0hvksnIrFAb9xycq+OJH0e+MTkZaYIerEan8eSf0sruKGFc9iUtywVLxE2dn9nK7jqbrTOULq1fYbdu79yuo3rkaHKJNm7UAnsKyJNWfs9JxY3NcllvycU+7ffz8HHU71nzRGmE7Fk4zkkrG0gadGLEuu51Qd/UHvIzobILiyqY9S33wekBll2gdsosmDbBLOtdZy+WfSvSdzbJ6ejkJlM41vfbkb6jpTkYypZ1RgsS5PP6eDefM9PRrvR92LXvPXiMCMVE4asxIvb3sexHULlaaCloWKdUOph1ccrxGFE65+I2Y+Tw8rKv82dQ2TJYx0wJq3F9cInL/jzuQxeSSSKoZaWHaXn9+bje38N9mJNlmdtVH27MK+D9vpWNJCZtmbZpXfFhSm5Kv3YJcTQ+3vnraZFENBkm/vPr0HqwGFKvXTXv1XN4A3kEtScwYbOXDNqzsUOG3MmPYL7hPp45o1u+49MpH5xpWnwk2VjDi3FNG9eMTR7Pl3ecTtJgi+Xb27h3s4/V8qDFv6BIQ7UrqzkNKz7YjHRcMnvqvfW4fVMuuOt8BPvZyBKc5OvmwU4w2iR9CutDG1WUK6zSbexoLk7X31dX8IaCOIo2wpgSlu1JLwlhErvka7iPfRFBUKGAY1xNRo6ftZg9ySqHF5s5dHb/5KTPDY/0pongmibu6Ujy+vlsuSm/9viksR6BcfgJPK+oCzGUSFigXt54zc5kHH4C8yWqtGYqbueDngI+g/ly0tRlx8lrTmavnzd8YLuE5WNO0jBvWh1u+vYY4jZjjBDecerLuk2X4NcAMao+0dtTJhW80SPJG9b+NAPf/KKZYOcbzndhTpkVNyqydbumnB/oOK3OgjrrH84JqjyH+zJURiZZcyWpTw952OfnJydtoEsC9gFdn8pSFHOpUfLsapVqZ76uC67Hkz+J62ETj7zktM2QRJ69cX5yvpgfwuP7GM9mF5XjyTA0spCNTq42V1539ja5ZLvv75e3ZexpTQNza40MVXhweoLH11ErH4mk3IfSjq/zg8v1AIPv0nd84fF47RA6OW8Bs7w4WmMgLl6LKSTGTGlUAo3jG9evb4wpzmGdanGZxGJtoUOI9OPz03ntlIPRXIPCOx/m8soLyYshbIO5szOiGq7vtbhEVIkphEjecDDEHVt6O0zveh/FXNxmU5zmZHYw9HcNAybPrqr5wYTriV/suKTMjtsl7mp2cW9+NfqawFrVYgIRQbPEnCSz2fDwfXG+eYGF+PKtPGMkJe65GWJzvOZeHUHHiyGnPKtRLF7f5Y1COE2yk8YJT9e4OozPz85Pa8LdGn8w3Qd7d1iTX93hHXeORWrX+Ivlk0//Yt7aoOB2mpBScdKQIQ996xIP4/GLeGx5piItZWU=
*/
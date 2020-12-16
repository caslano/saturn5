/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_14122014_0102
#define FUSION_TUPLE_14122014_0102

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/core/enable_if.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/io.hpp>
#include <boost/fusion/support/detail/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <utility>

namespace boost { namespace fusion
{
    template <typename ...T>
    struct tuple
        : vector_detail::vector_data<
              typename detail::make_index_sequence<sizeof...(T)>::type
            , T...
          >
    {
        typedef vector_detail::vector_data<
            typename detail::make_index_sequence<sizeof...(T)>::type
          , T...
        > base;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_DEFAULTED_FUNCTION(tuple(), {})

        template <
            typename ...U
          , typename = typename boost::enable_if_c<
                sizeof...(U) >= sizeof...(T)
            >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(tuple<U...> const& other)
            : base(vector_detail::each_elem(), other) {}

        template <
            typename ...U
          , typename = typename boost::enable_if_c<
                sizeof...(U) >= sizeof...(T)
            >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(tuple<U...>&& other)
            : base(vector_detail::each_elem(), std::move(other)) {}

        template <
            typename ...U
          , typename = typename boost::enable_if_c<(
                fusion::detail::and_<is_convertible<U, T>...>::value &&
                sizeof...(U) >= 1
            )>::type
        >
        /*BOOST_CONSTEXPR*/ BOOST_FUSION_GPU_ENABLED
        explicit
        tuple(U&&... args)
            : base(vector_detail::each_elem(), std::forward<U>(args)...) {}

        template<typename U1, typename U2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2> const& other)
            : base(vector_detail::each_elem(), other.first, other.second) {}

        template<typename U1, typename U2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2>&& other)
            : base(vector_detail::each_elem(), std::move(other.first), std::move(other.second)) {}

        template<typename U>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        tuple& operator=(U&& rhs)
        {
            base::assign_sequence(std::forward<U>(rhs));
            return *this;
        }
    };

    template <typename Tuple>
    struct tuple_size : result_of::size<Tuple> {};

    template <int N, typename Tuple>
    struct tuple_element : result_of::value_at_c<Tuple, N> {};

    template <int N, typename Tuple>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple, N>::type
    get(Tuple& tup)
    {
        return at_c<N>(tup);
    }

    template <int N, typename Tuple>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple const, N>::type
    get(Tuple const& tup)
    {
        return at_c<N>(tup);
    }
}}

#endif
#endif


/* tuple.hpp
bBDFWx/pVMdT3s922KxzzFKwqY6nvN/rsNw5Y41yUx1Pef/aYU20LDtvp0qe8j758RjrAueGO7ZFz7s99jkdNmYhWdR0i54nWNJh9XAqZdZN9TzlfXmHFYZnVUy3Lm/nXXTYYpUSkdGpnqe8b++wPkmheGZTPU9534OwjHCp5ZBlr9dz3jJ3P4WxQ3tjsWrkRVHAMfbzHdaaAWk81vN23p91WCcDtSUmrOftvNeegLFKSW1yCVjP23mf2mHl4CZEZcR6xrwQU7fF7ojlealw8pIkpNqcJcHfBPEEoqmTPnG3ydUBWY4gpNzlNIdRW8ZeDLUMKgW5X18bX3t8Bgb0F/Dm0Mrz/3J2nbF1LFX4uqQAAUJooQcIvTmODQ4gMruzZbYviYFQbxz7Jr7gcvG1Qx419A6h8wOkJ4p4P/iBEEKR4EdAIPEDiUh0BAghhCIEUigSSCDBmdmds3Nm1y8J7z3nxXu+U6adaWdmfCbdsCd4gmNCfO8DteMrKuY9jZ805Tw3DP0sCRP15NbKeFgpPYfvLpJ0xqxwirJwM6FilGG8ax6IKWXYVsWP7z1cI/wRy0o350Xkqo28eRW9Po+PEs3IYe3yyXr8txNo/0bSzVnkZCJK4xzTHVW2gDzDmpPz0h4z3fv3GnLmQp6kmQg9Nnrdcvu9kIN7aXvNnThMHFGY9+R03S39VMKXM98VMff5vSd3vky4dZ6pJHIS5me5n3EvwjSTYAPDEuOu1ZEp4zjPeZi7YcEyb5buFW2TfBFCJHGUOCyJTjutu6TfTGSmQRB7Ueqw9RVL5mUiM019RyR5xF6HoZqGzJE53j0e8lD4IolZ5s1b8UCmzIXYT0I3CFN22vc9c6A21HJvvLJnyC0TN0oKIcBWS+5niVyeZKnj+zIqd7CCgzhT7pdIHojQj7lIfHaKz1n7Ro8y0rWQxK7vuplb28tdbsu9h8gtCi/MCpGwrWVL7teIva4QseMUXNlrDu6H+MaeiS9YyUWeidiXDd7eDB/gGhfRUea544nCV7abjtfBNS4T/7zY5Wnhl2G1XY8VzsDfJPJ9L815mAmVBtM5O9gn7Ntj3ZESJ2ERQ2HuGkuwheVg8i6kwgmjKMh0OWBaRrh+a+KflxdhIrjnVmnBSmngGZEfh2kci1IlhYyJRzgmttLi+47gecJlzexOTJOWEdHFHTd2RcSZyBxuGncXxm6Y+IylWR7y0nNZ6fpVwZzw/Nr1bOL6LM2v0uHc8Vj1fD42HqNs7m6np3RdP2CjcwOZHlDjbKyAHqz1xt6byXvC84IkEYVKjvlyTM/HO09pehI399wyinV65o30cKybREfiFlkaunmdIIhUqJQYdxdZ6fGcWJRRljTpmW+lB8fE+01enwmeB0UmqjedS7gt9Q1wK6sL98CvZE7Niu87PtXkncvDMBBupF61pDpmiA6PBU4e89gp2aiWf3L+HGiA/6EOfAdTEN6U5bEQpSjSXd7BPMqjMyfnlAU8tt/hXDVlFSzzBU/C+v1tT1SJXFqm/dploj9m3Auj0AtC5g3PQwAI3E4GozS4BborCTqf7jZlzLpZHAlRlozn1lmNe6x8ykJeZFGh7BvKk387o5EMs1tcwvsiOdZLkzdlRZRmuZsKBmEm65sbzW2nWC9NfM54kgdpEYZsGW4hhnjFofHg5Vin43cmz7EwELx0s5Bx23/foPmcujwMQh4xDkMKWzrGQ5s8GctLV/hc7oHT62jpOY/70Loh/DhJkzStbn+sLsqU56AhD9QZD/OKd6zDpoxjBS+SIndiluo0YRwc0RWxIHfD2C+lrkrJ0nh5OFyEc0CyxcHp7YCmrzT5c5b6Hg9DkKMu/h9umwkc4l0=
*/
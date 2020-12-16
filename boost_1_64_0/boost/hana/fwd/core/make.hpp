/*!
@file
Forward declares `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_MAKE_HPP
#define BOOST_HANA_FWD_CORE_MAKE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Create an object of the given tag with the given arguments.
    //!
    //! This function serves the same purpose as constructors in usual C++.
    //! However, instead of creating an object of a specific C++ type, it
    //! creates an object of a specific tag, regardless of the C++ type
    //! of that object.
    //!
    //! This function is actually a variable template, so `make<T>` can be
    //! passed around as a function object creating an object of tag `T`.
    //! Also, it uses tag-dispatching so this is how it should be customized
    //! for user-defined tags.
    //!
    //! Finally, the default implementation of `make` is equivalent to calling
    //! the constructor of the given tag with the corresponding arguments.
    //! In other words, by default,
    //! @code
    //!     make<T>(args...) == T(args...)
    //! @endcode
    //!
    //! Note that the arguments are perfectly forwarded and the form of
    //! construction which is used is exactly as documented, i.e. `T(args...)`.
    //! However, if `T(args...)` is not a valid expression, a compilation
    //! error is triggered. This default behavior is useful because it makes
    //! foreign C++ types that have no notion of tag constructible with `make`
    //! out-of-the-box, since their tag is exactly themselves.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag>
    constexpr auto make = [](auto&& ...x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename Tag, typename = void>
    struct make_impl;

    template <typename Tag>
    struct make_t {
        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const {
            return make_impl<Tag>::apply(static_cast<X&&>(x)...);
        }
    };

    template <typename Tag>
    constexpr make_t<Tag> make{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_MAKE_HPP

/* make.hpp
zkHYkCx+xiTxNJlf/15/Uj72qKcuo6mPbUf5lGUrmpwM9MnyBS1NZpO26odQX6R1TOWWathiwrbi4rE8EMKrqTE8rOI3x8YvHU2zt29Qf1zJ9yD+8YT/TC0FBf5w1i870FepKIQ6BGV2GXIfkVYgX7mPiAhs7/TIauqiyGoiDVh/ZogVcrDVWLE2tJQSNy8lujTG7jo2Bl/CN8ApFLnDS1GohOFS110h5k5kT8yopYmspuLV0ibu/ISEHVgJnNhPu/91njwvlQtH8yHQv/rTWm18DrmXMKlIF7RFbGrIvVTTwHYaCQXUSz2FS4s85C9E5iwaPOElL1Mr3EojL0RbsBh1LZPDS1Zq4TBGJ79lKwavqREbKaM8UibN82Wkk0bV0s3u+x2x+keE3PLXazU2j+HEmAAcF0KglMyajbZbaZftWaqTaU3+q3zOev3cnl5A3/+yxUBmmGQzNDgKoRRRmxGVj0MkiDLN4qHv8NtJbA0voT7EVkaltMxyTY02A4/VfZXaGBZp/XY3EaQr0F19cin3ODGGmEzqNbW675peml9FxpdwbcaTKTDd9B61IybvdcpHwU9tzgPCell4X3fw4XNRINB/6GaJ3bRE7K6U2CnNgTOQh3DT89l1BM+IyZeYarVMFbhBAYpUdP4B01rTDkIYqGa7y3gI3t2oty+lC2UDptKg0Qv1T+Ukr7pOmnyJjousogh2yyPKo3ZbsESi1T223QboeGxVAC+WvSvM3rEt188lqE5CU5cvlCS1MjoHeNUREo2KfgpzdpwouQOZ/hCb136xlrelp9+eELfhJo4DR7DVeCGtTi2Pzk/kPvV/V5/G8ss0bCsli5YwYdXfrrPj2Pn+rGqxCT9hFis7rxTcBe7lUuFiNXjYGEgOHk6qGAEKh5GXE04QC706T+cJcMVwcjXYHCSuT7ydCG0D8tS9UGiw20atDSkHaUExBFn3eOKzukroxJ3ISjNCUT0yI+uzImtDKHhQTLU1Gxec7rvWLHnPbcR7agTvufIaeeXSCXiFjP64OaxetWeQUUQbvHiQiRJuvB4TxmMwG+g1UbwpSyiSL7nVTpDnkRiXLQ9+qPNFlsiqVoIBOj9D/XiCyBuXSz0Pk2ZsxufbTLVwHqfqwLmSdn7S/h/yuFsesHhlrDh+kAdxh1yi6MfPnC1zBhL/y29BwhzYk+aTdVFOKbbIlUVict9AvMR0AKmYO+92Hpq7Re6Qd2gvXOATwREUSYgPLBKm8115fFvkDeaiCV2IvyzaMgWabqVQtUCNKOzzfzk45uzNMQ+kiPJviSn/dK38O8bp5Wvdpz46XxQNfOzApHsMJoUaNgPVJ0cwJhA9rYxJXgcxicVnx/VRfH5WJfAxHYlPj3h8lo5vC5+fXCfxWTjoRPEpBz5u7TCLEfj4DLCFIJr5ZL5k4Fd41KvGcvmM4dNMH+r8eTEYetTPLxVBdyyGfPBbKMj+fkEUQzprxxLPoghC9jnTypQdDV/n4FrUMbIYuywmM1pMNoqplMX4EFtFZeBvqGoW5RTiziVRzqIdBDn4tbHikakwV5yIy/912FYJ+5m5OuwswO4jYYfNh9izglaVweqDNwjLVY/aVYAvn9bxcXCiP+3+Z/SxUHR51PdH450aR/VWanomZelBoTU6h2phRS12COaNt8sv0ZhaXJecDg1Uy7kRFuG1LC/oWXq3meU2nrSJT1nQIeczsR4XqfHPQ/nV396sCbdClRpmn+C++TyjrcQyl7Wnq+aTPP5zIQY4dwa6+g7ImcGjbirjz8dc/GqnlLK8an9ZplhWZmPBaxYL3i94wZuHBxa8rfqlQge1N/UdPy94FxI6Jo1rLSHk4KGc5Cf8tAU=
*/
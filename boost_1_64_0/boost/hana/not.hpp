/*!
@file
Defines `boost::hana::not_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_HPP
#define BOOST_HANA_NOT_HPP

#include <boost/hana/fwd/not.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X>
    constexpr decltype(auto) not_t::operator()(X&& x) const {
        using Bool = typename hana::tag_of<X>::type;
        using Not = BOOST_HANA_DISPATCH_IF(hana::not_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::not_(cond) requires 'cond' to be a Logical");
    #endif

        return Not::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename L, bool condition>
    struct not_impl<L, when<condition>> : hana::default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename L>
    struct not_impl<L, hana::when<std::is_arithmetic<L>::value>> {
        template <typename Cond>
        static constexpr Cond apply(Cond const& cond)
        { return static_cast<Cond>(cond ? false : true); }
    };

    namespace detail {
        template <typename C, typename X>
        struct constant_from_not {
            static constexpr auto value = hana::not_(hana::value<X>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct not_impl<C, hana::when<
        hana::Constant<C>::value &&
        hana::Logical<typename C::value_type>::value
    >> {
        template <typename Cond>
        static constexpr auto apply(Cond const&)
        { return hana::to<C>(detail::constant_from_not<C, Cond>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NOT_HPP

/* not.hpp
GmEvq4rqMmgvT5iO7ec3d/0XszCBRKHtVmZ0mX8ALNf/Fmhm4PvGCLRnp5LWtv667eMVS7yPUZZFZYBjfwxf6m0oESz8ecpBtuSey2HqFUmD9d6s5sr5BKeF8utc0pXdV6Rle+9/0xOcd6oozGvp54qmuz/c8xauDi9tsDtkQWBo7YPK6GI7bRTAbeEifs1cXWDitBmyUQ0+UuFQt0nHabc7w4arK43xvyWdL8dRiqRK/NpH/yeHY5XYSiWDmtX5Lrn3AEjjCQ6ZREDlqipogQATY4iuM+dnhdO5Lz6Kj9liJbMIN7NKdJc48OEpux8uuff+MvK9MIiluevgff48v8QRjV1O41QUVND/4ZLDL3APs/v+BxwaKjdymUZxXDAa/cvbiHQwDp1E2fCGRdPSOdGj8/keHQkNTFFlqXjSLJ0TPToPdtZRI+tKmaqITRCaWUc/XerZ8TRe4qfQgF1J9jehvrwY90GrsyCb3Hfx8zcMkyoP40Y4OlM7P3/tzQ8uC41fFAndF0wtq2O+u6XB+3PSj2UiAy8Qe9Mj9x5/xSn3Hp9UQV1HadPaWbd22rvrT1U8X65d6fLA7U458m4dhoXKvmxcAFwZ+56nXBm7kHXjqWCuhYYmtjYjF2hZMhlB+la2Mcxni/drKfR8ryyxg20y5j60Y7ft9M0XWAhxXocO24VzePvznMZppQdLoaYGDcN0fPye0x+/LPHDOHFpODzHfNWc8fMxsVmSBurWsmkfIJcoVuKpnk6izJIqZc+dZEkFeon7BrV8S+dMjtK0hMRXCOUYpaWk7nK2ROcTpydzkdRpCi5qKG4Sk5c3O2GrTWgpmO/ntRy9WVymMQ5Z9TI8nBxOx6Q3s3S3Ae/Y8MTYj3Kci3WrJ1NxPYwt5976PgwB98AnZLDVzeFdr+/krA7BbF5VifXdMb3xNXQ3Oc37WoggKkvPK4vL7etjrPzB8fgFzvQqaMLCF/81t+S8/9y8rM/huAOMSxAHmQ9GY36RSycW8NfB+dY1MjAhJs/oLJcn0RHB8zTq/F7q6MZYQoa6g9XPsFgAO5OLmzvndqb4nNzG8gXzvVufHuxqv2c7jldnfnn6/ro35nVvxcpRvI9i8hO7ifYtMzmU9kZ7m0dj8pF73jdYmTaW1j5yVP6Snxi/NG2pi9yT69pdkco/+gNT3vqPmzeezt/vk3PLldfjYM36t32K4grAdXMyWLffP0vfXX/3W5GvHIQb7e/e1bnNd2wZ5IHtLn7xHX7BaLRxD/D3+gR+kWvkR//zLn7C/tGuGv8hxVagcdgatnrlLs7Ve37elZFRM2znbN0P/pzFaxhunsPFjvryhJ9zH0UFMKCyTbdMz8ud7bhTGS6KWPDKR0spYlC0dgc79oDhfoq6cfBbotgAvF0GZoByS3+hHbMrI4yUOm5H4Ec7zms67lqY6Fax2GS3+wHFXKv9DP62LcAF2+4798vbWGjqw+D+BuaBHczqWr0i1QOLnraDs08anoXCqY3HSWPxqR/OxGsLE31/7uJtv+mrPC6Becpg8bHf5pTDHJnx8t1t23txECYTDYzB006DQxsv4Z5z4dC4PSRr0KCDJ1mc958Pi95qwLMW7p1f7cdgUB471Egau8UePqCBb+vOCBi1/Z6hj73cjPWl4I3RCKDPnjCwYgZWnXKtUmEy7LZxVKL2fNy2W88zqzC0mlcd32GT5tLCm6gnrAa1OZpphzp6bAUQBz5Lv5iBxb5sVJZsijct7hUHHkephrf3KX0XI777Lu/bsDPcRdGOxfdzgmnNDoetzeDQmjDyufjNzBy31qlDe6Iz2D9w2qbrGHkFpUZL3aGonY+iPu1MlCcztnH8PdnGyA8=
*/
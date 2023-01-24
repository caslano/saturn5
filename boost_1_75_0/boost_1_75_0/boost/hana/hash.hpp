/*!
@file
Defines `boost::hana::hash`.

@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_HASH_HPP
#define BOOST_HANA_HASH_HPP

#include <boost/hana/fwd/hash.hpp>

#include <boost/hana/concept/hashable.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fwd/integral_constant.hpp>
#include <boost/hana/type.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X>
    constexpr auto hash_t::operator()(X const& x) const {
        using Tag = typename hana::tag_of<X>::type;
        using Hash = BOOST_HANA_DISPATCH_IF(hash_impl<Tag>,
            hana::Hashable<Tag>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Hashable<Tag>::value,
        "hana::hash(x) requires 'x' to be Hashable");
#endif

        return Hash::apply(x);
    }
    //! @endcond

    template <typename Tag, bool condition>
    struct hash_impl<Tag, when<condition>> : default_ {
        template <typename X>
        static constexpr auto apply(X const&) = delete;
    };

    namespace detail {
        template <typename T, typename = void>
        struct hash_integral_helper;

        template <typename Member, typename T>
        struct hash_integral_helper<Member T::*> {
            template <typename X>
            static constexpr auto apply(X const&) {
                return hana::type_c<hana::integral_constant<Member T::*, X::value>>;
            }
        };

        template <typename T>
        struct hash_integral_helper<T,
            typename std::enable_if<std::is_signed<T>::value>::type
        > {
            template <typename X>
            static constexpr auto apply(X const&) {
                constexpr signed long long x = X::value;
                return hana::type_c<hana::integral_constant<signed long long, x>>;
            }
        };

        template <typename T>
        struct hash_integral_helper<T,
            typename std::enable_if<std::is_unsigned<T>::value>::type
        > {
            template <typename X>
            static constexpr auto apply(X const&) {
                constexpr unsigned long long x = X::value;
                return hana::type_c<hana::integral_constant<unsigned long long, x>>;
            }
        };

        template <>
        struct hash_integral_helper<bool> {
            template <typename X>
            static constexpr auto apply(X const&) {
                return hana::type_c<hana::integral_constant<bool, X::value>>;
            }
        };

        template <>
        struct hash_integral_helper<char> {
            template <typename X>
            static constexpr auto apply(X const&) {
                using T = std::conditional<std::is_signed<char>::value,
                    signed long long, unsigned long long
                >::type;
                constexpr T x = X::value;
                return hana::type_c<hana::integral_constant<T, x>>;
            }
        };
    }

    template <typename Tag>
    struct hash_impl<Tag, when<hana::IntegralConstant<Tag>::value>> {
        template <typename X>
        static constexpr auto apply(X const& x) {
            using T = typename std::remove_cv<decltype(X::value)>::type;
            return detail::hash_integral_helper<T>::apply(x);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_HASH_HPP

/* hash.hpp
Z/2p5m33rbQFKC27v1vmcz7Nb+S8WWOD3Jf79jG5bNitbO9a8109NBg8lRV4vpMAvtv507kqOLDw6toJ1ZPwOfrrU3D/X3dcaCq7B6gq3wZQKv0HMCq7xY2C3iNeCP66AJUcAeXPxW4IKoVHEuW3mZt+UKwcr5z/VoO+1E9kB30DuW2oYpXTLUb02TQ8J8SCno1cBlStZ8Jw5ywiL1NwG0fxKhX6hLh+UcLLBtj8IuHGB+zyn5v12XSYlLFKGWWndHyi3NWjaI3M0RLy5DQP05z1UTQ0OfVbATr8QdYm4tezQupgrGLn7C+/pPEI+yucf7b19+yuTT2R+r8EmbPvOl887Dj31DnwQqGs9nMACOZNDwboxRXs2KpwDMTFjl13bhGY8U5753edJP7DRNncBjoz23Fcop7UYGxZXRLvugSX/mo+4REXZrvmhjb9+Q2Q/KbYdmpnf3nkv8p/irkhcX50mOGKagmeXPQ+i64U7nwoQJr3U6F+IhcvtSuzG7i5M+A/Bya/wdnVTS3Ouae7RxtwEMLnZgvxe5oycXiqLg1rMfAXalaNlW0ddspZTqMctOuU2d0EMH859zCgDXif1p/s5vQ1c14XRbc3Gl/Kn/fyS+lT2RV/J7mWE1jtUwBTPXh2JYjShrfamdT+bohZRusL3v6tUnNoW3Mul1bAv7AY+cgy5WgsU0PSTni73quWsguYfMl4gwyeX+de
*/
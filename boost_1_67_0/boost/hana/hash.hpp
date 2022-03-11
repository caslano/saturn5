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
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
*/
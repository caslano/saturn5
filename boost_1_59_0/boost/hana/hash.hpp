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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_HASH_HPP

/* hash.hpp
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
*/
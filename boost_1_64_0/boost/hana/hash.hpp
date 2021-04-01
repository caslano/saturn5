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
RQbn9Y2PA0LhE8p4HBBumPaA8BOFvOD1XBz75Lc/smCSiAps6iA1pZBdDObYocqRJzuCla/+ndX8rhaZQpSoKus4SsYuKwuqF9vZV8k0+iillwcMFVn4y0NbDdmuJ2CM7BhIyycv3FID33jkoEm7VpNSDYFdU17V+xYPb1j5jsJEcKb65DBCGzyb4nPbJ/usMevdm+g6m/N+iKd3bOekvehubK7BIRpMHzLWWdD21QmmT2ZvaLYJE5JitAyeIR/ZvmYMszeLFWicONXxdB+v1ID4EpovQprCTF1wQ8fHSvPl2UZWz8CKETLBO4hZmwbyTr29+wIyyntHgkelPTqU6USEDdgeUvrP7IHFtjJMg4IWzJgQ3M4+LyyC7yhmq+jWRjDX6nTyFu5tdkFfLCVJmuIfU+KLlM74G78qfh9UYcUmcgLcAbWBjX43Hf4XXVHFDO0ulc/AQlaYO5GYBZ81R9hn/M5PWkZKs/isCaiuRa3nq3neT032/MdvT186iFd15Wtg6GfCUkgQc0JoOyxvxaVOMSCmWd1yJH3TCDtuXlbfl0ppJ4R3RwB2XA==
*/
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
WM1VHxjHx1UwfOM7vc05D5fj+cJHrwVYFteGN/wfSL5j5auPAMSEQa8+jBKbdrrd9ln/6vR9+2O3N7rE8u3GFvnYxC+Vu7FKnyAjYar3TdQo7UGITSpOPH7uLajMPRnodY0oe2vS523emG7CvOwqsm6fUVhzqgbXloOl3llnNbGi6xF3dyRegNp9+vo9OkDyOKU0aDM49d7UrTD5JRPFPIKFMU0vSmcDhyAz40zM2DRk14kWCPBVmyDoLkUnhpIvG5m66b6wlaelvlVyrPKEKXyKqj98ai0L3pBNThBenxNa/o9Q+3UrW0Mvx8SID4sRk1qh5bmTQqCCYF8eoT+Qloh5aEWmAaQI5cHjDYioJZxMzGMW+SRIHn9VVn7KdGfNE1NOGsH9T7RGpE4OBugqCeFwk8df2MdBelEWMSh1ZLnH4wVc77LhhflYmQ0Ml3nn4cHQsqTmmKOMIIWLXDYcOQv23FpIKf5/xcljE76TkhCY4CzKcrQMZcMcnegD+vmRMAwGIig7iwGbvB8BR8idNLoDKMC0GtB7uVWs24qMc1X5m8Lx6l+3d1gZSHWCBPWd8C9Q+Te3OBLHrjOCAUPotYxf/IJBmHaEk9yKXHl/zIB1w799H5eZUJ/JrcvIwWkEsaMMNkRwOYjYpWJW
*/
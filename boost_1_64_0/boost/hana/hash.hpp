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
oM+85U353FFvlcM/uR6K00+ZCmae576gvKp88if525wKSndxLxBX/+TecHnXhj85712rx8+SW+sy4ty9XSu0bfjMKfcV5wibylUxLSafYTmdB/k8Li4/Y+qfv0On/uSa83Tz42mO8Sf3YvH4Se4t4qHlMzntEKtPtb1lO8x4vU6XJes3SNC0bk/sBXJyDnOXuXjon/+/UoMeoXOa58ag+O//O+ns3/93UmJyb7j8uf75/zMt/WlyPXQePFXdwT9/egwWGWt7Rpw5l3PG+tWnmkNiVkxP8jFyD57Yn7wfdh7M+2w7cr21rjm5t1lWvrxjiTV1leU496eQ5w991v2M71c+5TuHT4SC4OPGX1wWu+KG9am670Q+Zvw/67sUFqidWPd+c6Ti+wpmHKPxad+N2G94C3n6rc/Rv3FssSlWziXHtAhCzkExQfOc8ni9Kd/7O0fE2ZWpoH7dyfmj/yF9Wzc3bmXu3NI5IRYi3MI5qbx1c+ePcvPW9rd8+haWWb5pn6UpY7Zo7tNaUzdFFm5mnG5q7kSdVxTv6Ngk72DsP6TPHzVmN3EOWTZ7Aecl2Yur4xLydhk5HOjLF8yjRigYfT4ULIkn3wwFA+Zavg/4knPky4izn3Ae1eXmk/L5bXly/MUPyyM9Zj5imbyufNIy+8593bJvTL5HDAWr33HeWTY4872EsTm0TYwc01/1nZvlnW/IuXVD+vaJGJesctx+KzPmNVuUyLC24hp5EWOzLPffdfzv6qtxO2OP+TP7ncP8/pu2U+CE+b/7jkVeohTJ/D4UVP9g/Dn6iLZ9z/zpiD/wvQhL5Mh2HNe6ntj0OkRdefH72m35iE3lM7Lftz9Bx/5sEbd+4arGxxgGYvsqxogk61fWpyuZR8pRcYET283+UM5+YBzEHMvnN8+Jcchy2LXgFs7bm9iXxE2Ujf1VP6o9VW1TLtzOfCJ0e9teQF23lrNzTDlXXWNXzB2OOJ1xTTCfOjeV25uqQ30rLN7RnDO3gjs7LpuOM3snx7Msq1wm4/UhtTvYn/0PmQtej6Oul143bm9f5YL6K6TZYjjtGJe13yXN7Ut7fQnbzOmHeVRsGpMLOv6FXGfZd17ufMMYW1f9inx+1flunqY+Ya7YdtqcbH7HuNq25LwNPmV53dxS3vm03E/mrti27ywRVr86+V7VXPyWY7JHp2WbL9u26bX1259Rj31rFOyz8g3bft06eux6PfNNxyJB+TvuL03bfFc9xnzYNueUj/5k+7+aC2I6JPe31vfLyc+s8WHlYs556sp7X9Duz+vbl4z75xxXuXYReaHL9EXlbHJu33jKe3Bz4saTa7UcflQOqpPfmpzXv7Qfmzcwrtd3z+Hoho5N3rIqm/ZbYLhijBhfX1ssT9imI66J04xX3cfVMysWSa4qX98+1uUmx2WgfGr5ov2ak9e2X19Vl3hVti5q3M+MKZEvytGXEQtf1LeWPH/HGL3feBi3sHLr28aFI3Jex+V6bZLzb3lt2fq5HO+O2vYB2w6N2e/MVbH2F+f5urxOrpu3MC9vrQ/yXFxwbpGm4fWIVkTetWtu1jYXdz6ag5FLmoOTa+Ml5GdOvJm+kOOUpdvLze0cx3UndB19JKZ8xoJyt6bNxqAu7okrllfIM3ttuaFoXUYckA+MZSDnf9W/iTV1asv8JY3LteTNNitV+WH6r/o5lr8PmVMkydp+41r6abuZyTmvvKx8bLvBnHnxQXP66uph/WrGjgOCa5g74kLNGNhmQ6yJWfstB3IlhgLrxZULyMs19c0+vavKl3JkybWMPcs2mVa+qlgXE9ZXlCO2TVEn7fj7k/2ubv+rmX/iTiAXIbm9pRwyf0E5uoK5Spw=
*/
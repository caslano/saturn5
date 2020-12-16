/*!
@file
Defines `boost::hana::group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GROUP_HPP
#define BOOST_HANA_GROUP_HPP

#include <boost/hana/fwd/group.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto group_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Group = BOOST_HANA_DISPATCH_IF(group_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::group(xs) requires 'xs' to be a Sequence");
    #endif

        return Group::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr auto group_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Group = BOOST_HANA_DISPATCH_IF(group_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::group(xs, predicate) requires 'xs' to be a Sequence");
    #endif

        return Group::apply(static_cast<Xs&&>(xs),
                            static_cast<Predicate&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <typename Xs, std::size_t ...i>
        constexpr auto get_subsequence_(Xs&& xs, std::index_sequence<i...>) {
            using S = typename hana::tag_of<Xs>::type;
            return hana::make<S>(hana::at_c<i>(static_cast<Xs&&>(xs))...);
        }

        template <std::size_t offset, typename Indices>
        struct offset_by;

        template <std::size_t offset, std::size_t ...i>
        struct offset_by<offset, std::index_sequence<i...>> {
            using type = std::index_sequence<(offset + i)...>;
        };

        template <bool ...b>
        struct group_indices {
            static constexpr bool bs[sizeof...(b)] = {b...};
            static constexpr std::size_t n_groups =
                    detail::count(bs, bs + sizeof(bs), false) + 1;

            static constexpr auto compute_info() {
                detail::array<std::size_t, n_groups> sizes{}, offsets{};
                for (std::size_t g = 0, i = 0, offset = 0; g < n_groups; ++g) {
                    offsets[g] = offset;

                    sizes[g] = 1;
                    while (i < sizeof...(b) && bs[i++])
                        ++sizes[g];

                    offset += sizes[g];
                }
                return std::make_pair(offsets, sizes);
            }

            static constexpr auto info = compute_info();
            static constexpr auto group_offsets = info.first;
            static constexpr auto group_sizes = info.second;

            template <typename S, typename Xs, std::size_t ...i>
            static constexpr auto finish(Xs&& xs, std::index_sequence<i...>) {
                return hana::make<S>(
                    detail::get_subsequence_(
                        static_cast<Xs&&>(xs),
                        typename offset_by<
                            group_offsets[i],
                            std::make_index_sequence<group_sizes[i]>
                        >::type{}
                    )...
                );
            }
        };
    } // end namespace detail

    template <typename S, bool condition>
    struct group_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred, std::size_t ...i>
        static constexpr auto
        group_helper(Xs&& xs, Pred&& pred, std::index_sequence<0, i...>) {
            using info = detail::group_indices<static_cast<bool>(decltype(
                pred(hana::at_c<i - 1>(static_cast<Xs&&>(xs)),
                     hana::at_c<i>(static_cast<Xs&&>(xs)))
            )::value)...>;
            return info::template finish<S>(static_cast<Xs&&>(xs),
                std::make_index_sequence<info::n_groups>{}
            );
        }

        template <typename Xs, typename Pred>
        static constexpr auto
        group_helper(Xs&& xs, Pred&&, std::index_sequence<0>) {
            return hana::make<S>(static_cast<Xs&&>(xs));
        }

        template <typename Xs, typename Pred>
        static constexpr auto
        group_helper(Xs&&, Pred&&, std::index_sequence<>) {
            return hana::make<S>();
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return group_helper(static_cast<Xs&&>(xs),
                                static_cast<Pred&&>(pred),
                                std::make_index_sequence<len>{});
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return group_impl::apply(static_cast<Xs&&>(xs), hana::equal); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GROUP_HPP

/* group.hpp
jPHkmQBjSZ0uoXc7LuvsMFNSP7vKR+KReEaooq7XmjNskOKAGh3CrzPupMhTpUVI3VdlgwTHnDF4/bn++R3aljp6f3L/1YclFl5o/eQ7PzHJcPJ94GfPGeSVj194rn9+X9cUJ9/TpSbvIZ+ifoKsdlOiTocx80/Vt6fa76mWPV7/6q5B3jt3nqc/xviq7FNh9lH6QFt5wbhHWLX9tmXTL7YfGfvGJnPA9TEt7nN4JdcZMWI8dh+sndS9926LMw/Rf/NwU9/at9Mmll/mPcHt5Wxyz6J4LddcscKQiGv6elSbxZ3JNZ5DTukxfUf3XLbvqM+U72gdA+bupA9sk+OQU4bM3dk6Go7bd88ZiDM+syyzybZ1WYqc0GN605hOthFbl/cehPkryCk75CjRY+aK2sX2FSdz2Pz9k88qHHJG8Gf3FLbZo0KH6cnnpcnfMIqbYv7fz+k0mR7az7U/KtbcU8bMf++c/3xusXqVye9ZjsfW1cxt8YAaPWa+7/5yTfcGcYsUeY5okPFZqkRfeamjblIcUKfH7A98viLOPhVajFn8oesEBSqcMWT5R+ojRdt1ZeQ+t3MTOfysOkiyR5nmZNnkWSFxTltW2KLOmIXPmYekKdTtI9bpf1y/vQ6vuI/cShsr6iBLiTp9Zt9vDhMjS5E6vfdP2qa9ZP5yjn/+vW/xefo+eX+iXFNOPl8fXqDfHNGgT/zqzk/3ziodwi90DE6efM4gNPkewD2uI1ZS1lm2yBo77HJIl9TksylnKcdl5jH6T4zIreTIeVImp1xmJaLPFKgSvop6xDX388XJZzfbRklSp8ue82528l1HwbGUa7S4qn6us83u2GckGmOvz6EtL7Gdc3YwcRefE+4jJ/YvmJsVDl9v+RucO290zSLKyr195iJDkTpdQvZdYI00ec7uor4beU/PgNkbmxs3tj8p9jmmQY+wubP6RPfOybPzk88Gfw6cR65/5KnQYvTn//y+kadCg+5f/vObxhFnLPzVdmz/1bZU/+oY//V7xTbpv1n3N/tw+n+/TxT+97eIf/4OEQ3knqMnutdMYjD57OdzWiBX//69YfMc+ngOeTiHPp5DLs6hj4TOKU///q0hdk65mvzGMDnOv39nqP37N4ZTy0bi/LlsS2zyvQIFuk+c3PrUOfn9IeQ99b9/Vzik8x3vLdvW0yb4rpww/rS2f2by/OC/nhMc/PuZwOV/P7u3yDo7//Xc3ildgndaT+Tfz+jt/fu5vAaDfz+Xt07i38/hVThjxNy7A/dc+7HL4b+fv+sxe2wdSQrU6BC851/P20VJ//tZuxP677HPe10/iZGlzCkD5t7nGsjOv5+lO+aMEfMVn0VJc1Cx/t/PhwcvdCxyjLnqi9yr//3cd+daXl97co6r94n6fyV9u7J+/vtv+ENXdVy2ruo1DeauJqekKVCjS+jqwT//jn57SV0c0vz338jHrvmvv3FPX9s+1wu8jzjHP/8evHL3qWDJLT8QoytycO+poLg1FWx/2hy/11Sw+oipIE+bgDgVso+dCgapwOewqWD+LlNB40FTwX5yKlgmEp8K+g+ZClYeOhUUxGnLYmxkpoLk3aaC9ftOBScPngpGk/Vx+9t384FTwe4DtMX66N2mnPe2qehvyDn7ZtcY9cw9fCrohlxXHmbbh6nzMVPB8DH2f6zjWBdYtsAalYfZljFL1q2zTYYjTiZRm5r0J+3O6KvjxGg+wbGeOBXsOfbhY/T5wdo0yU9KDu+rLhKE7dN5ov0f5bPZo31+ofZoc2BSfvJUkNaH1GTZyNiJFdqMWfAZdJ1kavKZ0uefPxk/x++MnEPK68Qnv9E+erKv5SxaH72344opY3NwL/0=
*/
/*!
@file
Defines `boost::hana::find_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIND_IF_HPP
#define BOOST_HANA_FIND_IF_HPP

#include <boost/hana/fwd/find_if.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/index_if.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/transform.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto find_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using FindIf = BOOST_HANA_DISPATCH_IF(find_if_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::find_if(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return FindIf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct find_if_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    namespace detail {
        template <typename Xs>
        struct partial_at {
            Xs const& xs;

            template <typename I>
            constexpr decltype(auto) operator()(I i) const {
                return hana::at(xs, i);
            }
        };
    }

    template <typename Tag>
    struct find_if_impl<Tag, when<Iterable<Tag>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            using Result = decltype(hana::index_if(
                static_cast<Xs&&>(xs), static_cast<Pred&&>(pred)));

            return hana::transform(Result{},
                detail::partial_at<std::decay_t<Xs>>{static_cast<Xs&&>(xs)});
        }
    };

    template <typename T, std::size_t N>
    struct find_if_impl<T[N]> {
        template <typename Xs>
        static constexpr auto find_if_helper(Xs&&, hana::false_)
        { return hana::nothing; }

        template <typename Xs>
        static constexpr auto find_if_helper(Xs&& xs, hana::true_)
        { return hana::just(static_cast<Xs&&>(xs)[0]); }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return find_if_helper(static_cast<Xs&&>(xs),
                hana::bool_c<decltype(
                    static_cast<Pred&&>(pred)(static_cast<Xs&&>(xs)[0])
                )::value>
            );
        }
    };

    namespace struct_detail {
        template <typename X>
        struct get_member {
            X x;
            template <typename Member>
            constexpr decltype(auto) operator()(Member&& member) && {
                return hana::second(static_cast<Member&&>(member))(
                    static_cast<X&&>(x)
                );
            }
        };
    }

    template <typename S>
    struct find_if_impl<S, when<hana::Struct<S>::value>> {
        template <typename X, typename Pred>
        static constexpr decltype(auto) apply(X&& x, Pred&& pred) {
            return hana::transform(
                hana::find_if(hana::accessors<S>(),
                    hana::compose(static_cast<Pred&&>(pred), hana::first)
                ),
                struct_detail::get_member<X>{static_cast<X&&>(x)}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIND_IF_HPP

/* find_if.hpp
NN+5/NiiSfovjfoedO28t+Vtnvitpb9uhzO/4ZcG9XEuH4unouH3lnwrr8/hm9vih1Zwjt9cNwS+0ifVy6L2TfAxrp/7Hd9ZrB7v1H9pDpf1uWd38Dw9I9ZL+dqF8vIz/WPPO709X3C41+nj2tsi/BqcPMT6y1f6Vf/Rr75Gvpq3dTeL/zvWCbKsDxV6XryyqKPnnClun/Kx51svfgOuncA/45mKD+DMXvV0Oj39ONw7gT7bTCdfB9+y6Z3lxjMNbgyBi3H+shaud/J+EX/1C1+WRA90hE/4f0abGP0uX+iPaAv5Gq6XDaGH1XFjDzx/PX2mTxVdBy8Pw8fwtW49vdWkjh7mN/BRinovzYHT8qT8Yvy4Hx+E68ujQz5MxP/q5lX+6zV88QddtFE/aVgz+eVz86zXz8aHD/ERfRLwE/10pvkv1ufor/8kXgXP0AVr5BEdHj0ePoQ8oL8T60oPDqaPb4H7d5tn+2szxKeLeM/u5r5X8aV78Qk8HNGKH+8AF3cZ7x7z96H+XxTv3Cj/39L3WyvvB8mbqfoe8nnRZ57nGDplG12TzN++IL/FOfmzBPOJh0f5nHGVpeGTNXzs9OBYODiBf9NH6G0ePEdpM3piLB4aQ5fA1Xz8OZ2OrD4WH/TE03+q23LzPEd/OCE4ppwuH4yzvgm+9wqO0fP0tejw7G+M55/rBvMQCY4d6SG+quhb110KD+F9pvXn/AK8d5w4HnD/TPORor6eUJeeY1UBndhG3tS77vhIcL03+LS95vHU4JgHZ7PolZZn0dvfe44M+X4Hv6oPv/waemMDnP6MLp/NXw43D2l4l++Y14vuuEFeqY/SZcGx6lvrOOavFM+2tT89qU0kOG8bHTPGeO7xN5/cONF+gUrxu5nf4HcK+IVGuJx5jusfwseFfeKp/N+YBPnZTB8PPv3M95ypfl+J6hfwrwv4N7ol2zhb2n8TMx918rieP267VD7uE6cc87AuOK67Tj4egQe2eZ6HjP97fk2ck++O0Zd8wo34KPz/Iniy6mC4ulO/6RbjnUffW7eODjLfE+TZQHhWjfeq6OunQv8tD8+Fkz/QEy+LRyUdYJ2k2zA+Cj9mNOPf/6L3+7nfCvqnmC4+Q11Y7ykxL11O4ke28q0fqM/18HoJndRJPnXBa+5bNkN8muisier6PHhs/hb10yed7nw4t6yF+ttm/XIs3g515XniUhj1fUDq5QF5NCwK78XxeucfJ88r6J7T9LFPkwcfux58zz8cT86KBEf8MKLcPHant+fqR73nfsl0Mnwp6BML/h4E/zxHai99p14J1lf1n9tbl9rs/VQ6xPpB9lz+/yf1Lp4rX5a/6nflTXBH3Gvai9+Fnp++63coHhXvxlZ47h64exW+qeLz7bOffp3+wTfw8VZ8UK4vm8bHfWI+WuOXFZHg/K3meT0flYL3R9FBXdXpEHz1Izy3brj9Na+rh+IKerRFRB3TS+Y3f6P64LOK1F9Rrf2lf5n3482f9YvCO+i7QeL8DbyZJJ/OxJ+Pqk+4Xmv/ff4wcbiOf8vGrx/R5c9bZ96tP3oVH5aJf9vjz/3q9RzrVM/SJ/imX77rbaOXB8DvL+X5g3xLhG4riNKpPv8wn8Kn1fp8dVTfFx5MG8c33Wq99Gb5cke4DxvO94IbN8KhTZ7feuKqlvgtjw+/kO6dGQ2Oo81HX/igXkdkeP1ZujlcXz8fvtgPUFCgD3C6eYvID3WTlSPfno3YlxLuW8KnE0LfGRxbvqQfPpHv/VQ/4yB6MxtPNBhvcz6nM16Y7TlX8Mk75EkZnSYP5sSNa4n630w/yvskPFsCr4qfD46FScb7HJzYjJflc+Zt1sfS+JHh9oU=
*/
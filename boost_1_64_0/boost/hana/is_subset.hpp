/*!
@file
Defines `boost::hana::is_subset`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_SUBSET_HPP
#define BOOST_HANA_IS_SUBSET_HPP

#include <boost/hana/fwd/is_subset.hpp>

#include <boost/hana/all_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto is_subset_t::operator()(Xs&& xs, Ys&& ys) const {
        using S1 = typename hana::tag_of<Xs>::type;
        using S2 = typename hana::tag_of<Ys>::type;
        using IsSubset = BOOST_HANA_DISPATCH_IF(
            decltype(is_subset_impl<S1, S2>{}),
            hana::Searchable<S1>::value &&
            hana::Searchable<S2>::value &&
            !is_default<is_subset_impl<S1, S2>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S1>::value,
        "hana::is_subset(xs, ys) requires 'xs' to be Searchable");

        static_assert(hana::Searchable<S2>::value,
        "hana::is_subset(xs, ys) requires 'ys' to be Searchable");

        static_assert(!is_default<is_subset_impl<S1, S2>>::value,
        "hana::is_subset(xs, ys) requires 'xs' and 'ys' to be embeddable "
        "in a common Searchable");
    #endif

        return IsSubset::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S1, typename S2, bool condition>
    struct is_subset_impl<S1, S2, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S, bool condition>
    struct is_subset_impl<S, S, when<condition>> {
        template <typename Xs, typename Ys>
        static constexpr decltype(auto) apply(Xs&& xs, Ys&& ys) {
            return hana::all_of(static_cast<Xs&&>(xs),
                    hana::partial(hana::contains, static_cast<Ys&&>(ys)));
        }
    };

    // Cross-type overload
    template <typename S1, typename S2>
    struct is_subset_impl<S1, S2, when<
        detail::has_nontrivial_common_embedding<Searchable, S1, S2>::value
    >> {
        using C = typename common<S1, S2>::type;
        template <typename Xs, typename Ys>
        static constexpr decltype(auto) apply(Xs&& xs, Ys&& ys) {
            return hana::is_subset(hana::to<C>(static_cast<Xs&&>(xs)),
                                   hana::to<C>(static_cast<Ys&&>(ys)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_SUBSET_HPP

/* is_subset.hpp
vfbe5uC+3jYpCSX6+Lr9/eKrssb23X2+ubc9XtZe/rQDZe2fF+9ke5A/frAZsOD2PbR/7h7Zn5ud94Tj83dZUnrmLy9Ij5ckfXcNqCspvbHxsvqdd+Lrnf/cq4SS8uVckG/nDngv4359D97PFy/Kmovf+4baEun5e+m7RSQy7LV3b4yMqXN429mmVvc1e+lTe2ObODvE37DYH7NP/yQ5nfgrhJqd95j28nxiaX9c/1ue2YP1BHeF8bcYEnWJ39wv57/l+eLBcoK7wN1Me+ezpHL+W57XrR5cC97ILmryKkxVe3kWlv4tT+E1Tu2S9sbvWwfaE7yCM3+JMh5xYM0lHxj7ZSwfrCdRSGVirfz4wHHz3/u0eWG+/bLOJsp64P45ded9hPhF/XrX4J0rT1LfI3vtTp6Hndv4/evfXp5Ee/YzSd7LV/Xfy4q/JAglzovH/0d58Yyy7J0v8vb70e6E6ezZtTeeJ/fLiX/O2dK4m2Uv/Yh998dpNzG5708+OGdeGbu2n9vJ07xXx94ac31pdcGXTYZYIn32P57jQ7G9c/DO/l5t1JQGl9H982hfUpoGBJeE/bL/5D7Wfcfx47vHenA53E/fTqQnhiae7vqT6N+Nif57Y7O+5OSJnXves/F3G/f796LkPFb2bvr+eWfgwvQzsS6b99I/+sN4euflLQfvQNsSbWj85QXrMPhYVVJzYt18eu9a5JA5Xld7VYnh2J+LxkRdkR/9p3x5e+tv7j+Wk7d78Cgn0aaq/1iO+8mkuXnKgbVxWf3OO3feX0+kP+ynifTdpN3J3U8/Ij15//gCDUlPtMH/pDe0t9cfL6yJ1re2NTTWe/93Z30k8gzc7ECeGzq877Gbab+dIxfF87i017e1N51N3GGFWvfGLCUoY7eK3beaQ/vppy+Jp5/ZfdMj6Uq5t39ZPD1xE7Rzn9Bp8941eOCGm0lvs68bQOt+b/v5xHbvOCUdDwPtie2779/Z1JnY53RXIi3+Oep+WXl7ZV1niva3p+2V5QPD0H4dp5+d2H7u7FPPtt1wNqmO9p5Emk9FY6EbEvtk3ZjY7sX5Ttr+PhOxRFpzU2v7/n1O2iNDtsePveAErZ5EWl3BXprWdTSc309zQj0wps5o+2kz5Ym0eIkXpN02mEs30J2dNzQmj11eZjxtd44VGtrb/i/OrgM2rqYIHz30AAFCD71D4tiJQ/PrvWE7hWpcLrHB9h2+c0hoClV0hSJAiN6EEOUXIEA00YtAiN5L6KF3iCiCb/fN7pt9dw6Fn8Tx29mZ3dnZ2dnZ2Z076+/Q/I1eveLu6jstHYzOvoTasN1fqN0jnYGSh+r+omyrC4U06FIp19eWbuMG9uS9ZXzq6nG5l6JJtgMv8yTNxdPd0bLfgc+gubg5pt4VXxdjs9Jb0KZxMzd230eNAXFaaqCB5s2r33kVlJ9BRTR2bVOvCy+WOg+uZJpymF21hQm6Stf0fzEeZsE+eoLrmpcrXJAp9BtgjUGtcP3hRzvgAhDHtWcUTtkYD1R9frxs18JCOBeBX+vdLXku0NgY534py8HI5W0gOVvzBHqh96i1LmjdRPlwEbd6FalXsKogTKqg73fB+HO/fG6HflIFgQVvXTCYwQEavGrCKS+mCgV5DLY3NhYRCjE5c0j5NZuzuR9wfKWVwVMd+k7UOuesXaTra8JDOnzM2nJXoVLt+vQ584wvKiIX7vOyaVe8eRqWvKhfR8HUJjhFVqHFgEPLEtUuA5+PA6EkcD38YxQfObXbCNk5IPRR08cU8Q9FmiMGgvGs1lPG8UJdqDjmKFwx5xfCC0ToFAJtLB+LP2phsRnCiAAmqAjh3wKG9vn1NG9PZhVF5nu+F9Q=
*/
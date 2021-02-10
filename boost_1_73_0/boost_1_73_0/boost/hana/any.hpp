/*!
@file
Defines `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ANY_HPP
#define BOOST_HANA_ANY_HPP

#include <boost/hana/fwd/any.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto any_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Any = BOOST_HANA_DISPATCH_IF(any_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::any(xs) requires 'xs' to be a Searchable");
    #endif

        return Any::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct any_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::any_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ANY_HPP

/* any.hpp
4rxlbzeh55rq1EG046R3zS1kMxgE1wNrw6B1gzDWJXYWneWLyKJ/1F7UaDeJqaaN+nnBxJrE3VXWxXoNBOuYipfg5gBrfK6HahFU4fqM2ARiLsOlEeHYiwHhOvm0KkSHHVzDqAkl3jUwjGRlkF7RIm2xBGZhpczngSAA9hRzWkeKFgcaLcrjr0mLA0Ij9AtdlTGNlRoCRgUUQnO8Pkaxd9E9aIACehOCy7DL5YTzrCwiqT8Y9jOdxRE0i+SnRLVk6Bah0QdtyW8VBMjUCuw5b23VGDLUCla1FVwV2+FDQR8powkz3E7uBXkBrYPLszNCA3D8IwlHkwYSeKEyWbdR7aUpm4gugmk4lTR5/CR53CKoiCQ00aaYG6JZKj9SMAEqO2cXA9ov0ZY4VNJQqXyDN28nkwtSFlA1n7K3nbGFTarqA+ikWQmT4q5Qvag3SP2XgYzGHXNLWx0Ck+Utw5I1awusacxeKqn01gbLImHTGGyP8dvO7gEZJ/ZVCPYXrQMF9jvspX9inZ513jTUw/MTCxodNNECXllz1L/onZ8cPG+vVx06Pjx8tn7dH56vXffpj+v3+8PBYRMZu313Kj4tRFsnuGcXP4MVco1EJERVK4B2AljMKhy0D5+1pAthh43GHTYHnecjv0e5gFXk
*/
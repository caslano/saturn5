/*!
@file
Defines `boost::hana::EuclideanRing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP
#define BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

#include <boost/hana/fwd/concept/euclidean_ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/div.hpp>
#include <boost/hana/mod.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct EuclideanRing
        : hana::integral_constant<bool,
            !is_default<mod_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value &&
            !is_default<div_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

/* euclidean_ring.hpp
i5+PxJQnFQDAXLwWjYIIlu3YO6wp9k8BCGajX6Xnf5UWaiuxlHrSTmnZ1bNcCi412Rh4xWpqr+5hknmkKl3+IQERtX/4Vi4nX5A4w5ua9Ri7BXpdqA0ZhJS+5HPI4n7ujAWSLCVfyP4KyL5isjFYOKJTb7QnsnlT6AogU8M93Zk+5Nvm1O4qworG9m2ClXz+gNU7ZXafHp61aUpnJMSiUuCznLStDTSqdulN94mxViHgjqfs87qDpM/h2OzXoYeYw9sGIuV8dWy17s1NPiKzECKGgGAu2TejJtpMKYlZyje/gzCysFFmepUD4lLHhUTJ4DopH380qcTD5GGO3SwNFHzk8fqTLGKfQVpLmIm85giVcAD9j0pHM+6wr/n23XEuGSdz+BRlm49k47W8Cq2eiorq+/FUwqCAPFlKBviV1qdkM2W52a5G1v06rucpoqojM9GUTvrV6qAfURzjasiN4FBgVQBeY+QrOxVhcHgX5LbqXY9FVr4EkDHRYgNzE1Cx0hyGbzya+J++YOs2Bpgy5Sai8hgzWnQnDu68tx+TPD6UiO4TAG5uLLnbgQ==
*/
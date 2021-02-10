/*!
@file
Defines `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SECOND_HPP
#define BOOST_HANA_SECOND_HPP

#include <boost/hana/fwd/second.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) second_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using Second = BOOST_HANA_DISPATCH_IF(second_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::second(pair) requires 'pair' to be a Product");
    #endif

        return Second::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct second_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SECOND_HPP

/* second.hpp
a7OkgvFS1drR5zlUAeREtKTlG5bHNvCfVKjH7Axuh23pxkmUAWm3kaX8veModzRXucaym9Nksyw0sOGoqxy+AXhHx67QQ8mITzLBURyIVUTOTxT3MHS8OPbuHVCnMEWJKN/m3FIscHPuq7piIZCDh+h+SGrqug15z8lSTevpYuoeA49Cx+j6Kg6WaJLJaFznvaZI+yGtIHFXpJPEaDFzrVWhPX2p0IkyKej37iKSUMvKIYaBQr1HdV0cU52qGsLCWFJ/XGhQkhU8JPzLJ5PyM38c6YGV9Ks4rkfspJShxoy3YB45QVVOtSpcB+8x4+G/h2GPiI2B2mvnw9TjniH/tsdd6IlRL8OdkRShGJjuUdkIH+lGvdmsHNk2nrfE8AEuDDm7IDcmIPOmifdcPt1P495mpEVmu2171JYvX+5OMMd5IGcOXKE4Pr0hWU5sJWS7Dm3CzYVjM90DdIyxyNSoktRftT83hyB+Pkl93RznjE8G2dOQtCPkA2+749eDU/c/Ljvnxm+MvPJfLiaGj8ywYhQ84XwweHN54exiPOW1GSrN3r7wy1zFMSvkujd2xs9SQC0zgil+0Y68lTOYsLckDPK3F7ZIfPO1cwRlB5HUNBkWjJsgD9oiSlK8joYXGp4frpcsZgIWOpfj1wQY
*/
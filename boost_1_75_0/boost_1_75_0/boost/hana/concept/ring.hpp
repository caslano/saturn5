/*!
@file
Defines `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <boost/hana/fwd/concept/ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct Ring
        : hana::integral_constant<bool,
            !is_default<one_impl<typename tag_of<R>::type>>::value &&
            !is_default<mult_impl<typename tag_of<R>::type,
                                  typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_RING_HPP

/* ring.hpp
Ig1D8DUtCPDvZxB8iu8W1kZHKqcojl72Fp4yL/W6lHUpbOQwHIPAA3PUit7Mq8SH0YipLjF75qDb0PXxZlYZh+xdrE0x0pm0cpMtBxCUlSD643A39vtATErRQDBeLRqA2RAPT0DHUR0xLwo6YrYJ/xYxD+DgldIyl1jFB8dQ96X6HW3YHYVO2lW4BDX4on3yPtDRA4qjXSnqzSraL8r/AjSufTtRKehUDf6Kp7xx6jpcPTedKDn1fKbjKfGR5yFBluMZ8ZGnEPetSkFPZsELYs3DyB4Wpag5VtUmB8y04P+SUnQMHTB7/BXbn4d/GKniZG3flkvCG1L8ju3hq5zsj0aDFpt08jKQb2r7Ko8DeeOSW9GxXDlgA/AAIavgBWlXcHpYgmxPUUAEPA3dGb4KN7boe1VB5be62ACGT9qXoRb1qgWdC1VHu9yQCG2D9mDzHpiG46ciGVBTVZFi8A33wiz10me0RpEwFb5dvAARuf52uTLFINnUJakgvb4g+G7EMSW5I89J7ODpcFgB2mo+jQNyQMlPDC4Jb0pxseEJnAR8pcFLAP0bJ81zAHUqZHXDWhdiJ6ygut5rILMEk/E4xM1QYDnnMAs+wI30LnYBVcxfsI/Nws09aRNxSWSfk10cxJPNtQrkRSoAk5wJ+DPMs6XQucWEFCu7Nw6P7Z6VQLsJneyfIE2ydz/QzYjzXDTsAHyVWIMxJtzFrDeE
*/
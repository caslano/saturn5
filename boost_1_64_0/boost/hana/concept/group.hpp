/*!
@file
Defines `boost::hana::Group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_GROUP_HPP
#define BOOST_HANA_CONCEPT_GROUP_HPP

#include <boost/hana/fwd/concept/group.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/minus.hpp>
#include <boost/hana/negate.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename G>
    struct Group
        : hana::integral_constant<bool,
            !is_default<negate_impl<typename tag_of<G>::type>>::value ||
            !is_default<minus_impl<typename tag_of<G>::type,
                                   typename tag_of<G>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_GROUP_HPP

/* group.hpp
aJQfmWvhyuuB8CapoGPu3zO/ac8DXFg1fTRiUEuzjskcw61QpDPULuOcQmtrHusq+xA+LrUV3F9xV80xmDNZxVOMi6QgCev1TeztAmZ3PTUFNC/5jvltu2z3fZ87Qn8NTKsxuFJJ2Uihf/Rr8ItW/um9tHr+VgQVDwRoxlShfz5Vi1f/U3uidh2jbKxT71s3z3D5nLF15ow8bIn5iZUYj5E0gwSnd4gTeCNFAwWdF8p9hlKfMyebdUKaLWe7Z1SDraDIQO1mA//xh666N+tO4Sc43qdZ2ZToXs92Xh+vmCu/tVW05rlQePk8+iUwyIcqNmnMwnUlc+OXzSuWHekXjxhyZ4ezwo/AmF2XaVFLJKl8RDoj87CS+K5ZVMHIfv57A6jR7UFQTtb/QbS+uwCIzwicAhy5uO2LW46NEW+rL09lBMn1FpTQtzkyVx/vgaCzD6DRtcozQFwD4cEYlZpdv/Fo3bV1oONy2lE4H4KzjnYpSMzlgz4ZCOiTLQ+2x/G1cGUTFyBMnmHqantxAdlUrwFC1vOXxNhdbzo192dwUnx2gW7QR6d/jOZcOw==
*/
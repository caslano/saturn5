/*!
@file
Defines `boost::hana::members`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MEMBERS_HPP
#define BOOST_HANA_MEMBERS_HPP

#include <boost/hana/fwd/members.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Object>
    constexpr auto members_t::operator()(Object&& object) const {
        using S = typename hana::tag_of<Object>::type;
        using Members = BOOST_HANA_DISPATCH_IF(members_impl<S>,
            hana::Struct<S>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::Struct<S>::value,
            "hana::members(object) requires 'object' to be a Struct");
        #endif

        return Members::apply(static_cast<Object&&>(object));
    }
    //! @endcond

    namespace struct_detail {
        template <typename Holder, typename Forward>
        struct members_helper {
            Holder object;
            template <typename Accessor>
            constexpr decltype(auto) operator()(Accessor&& accessor) const {
                return hana::second(static_cast<Accessor&&>(accessor))(
                    static_cast<Forward>(object)
                );
            }
        };
    }

    template <typename S, bool condition>
    struct members_impl<S, when<condition>> : default_ {
        template <typename Object>
        static constexpr auto apply(Object&& object) {
            return hana::transform(hana::accessors<S>(),
                struct_detail::members_helper<Object&, Object&&>{object}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MEMBERS_HPP

/* members.hpp
0XT81PEWLQE1vg4SJ4nm6a0X+w58XwRTP0z8meMlzsxPpnEwgR9B6KTXvjMPFr5zMrh43+u/ajq318H0GoHcR2snuY7Wi5lz7d34TuxP/eCGYay8OHWiOVQH4LMgSQHgOg2isAVt+07qx8sEYWDz3iKJHO/GCxbeBBryUuc6TVfJs/396TpeQO/3Z9E02Z+q4beu06UeyXvoxNK7d6JV6qSRs078poMlm84ymgVz/AsIgYer9WQRJNfNrDfQVDjbj2In8RcLhAX1Aj/hbvvOSNDTxGLOCnocpPgnicIEm7q9jpZWQcAjQpmv4xAaAjxAoVkEaG4663Dmx1SYRq6aEJwSgiunJuvvzIlC6IxT64yc3qjmTLwkSJrOu9749eBy7LzrDIed/vi9MzhzOv33COxNr38KUx9AY7Hj361iP4HGYydYrhaBP5M2v95nf2dnn0YxitbxVChnDg16i4UzWPnhaHS+l6z8aTAPpoDvGb9FXIzPR/vw1ll4937ccvoRvUZYMHTnJl0krakiN/8GhjNFmFAZphwBwL/zdThFGktwXNCVvwXhdLGGNmpISG7ip+tV67qGL+Yzf+5cjrru4KLbh2aNwj8tApjppHX9AgfjvIPn8T1Q13KdpM4EpoTLzeA79B2J6B6oPLyC
*/
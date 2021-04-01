/*!
@file
Defines `boost::hana::keys`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_KEYS_HPP
#define BOOST_HANA_KEYS_HPP

#include <boost/hana/fwd/keys.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Map>
    constexpr auto keys_t::operator()(Map&& map) const {
        return keys_impl<typename hana::tag_of<Map>::type>::apply(
            static_cast<Map&&>(map)
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct keys_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct keys_impl<S, when<hana::Struct<S>::value>> {
        template <typename Object>
        static constexpr auto apply(Object const&) {
            return hana::transform(hana::accessors<S>(), hana::first);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_KEYS_HPP

/* keys.hpp
XjT2nralIC4H/Irg9SDQU8lHBmHFK5sAgy3Poq8HPPM+qaJFcl8srXPBLDy1c1kpfYjjQV6F30auN1n7WBdgP5Ps8M8BqE+QrsCzhi9YFYzGfhAoqmwRI0+XNxtgq/9TbEqv51XgsrR2j8vXsFIzHw/IFhpfp8v4zbMx34HKo1BT7uigiLcsaAcm/ISe2zRMCbHTvWL7sZc9QgWGDN+TiOzfoNuiKIuseayxy5CPRNSODuAQj3qxZ8viGLsXTtnwV6F+fJ8ZfMY0n9Lr0VsuPXass+MhJGHV2SJ63imvSx0UOE2qxCAfUX8+cG/l/a/NYlG1TrgMfztBGIowGeKgNIShX3jBCmELUWSYTcFxhIcnYesszaSUSHMzidVLbzRt+PriAbzm1/7FKZL3G4Y6wys8aAZAzicZB8bBMum4rYhTt5qJL7UXvD053MOTW6bL3iEVM21UZDqBLqSBltLhLQo3yGkrSroLXkXM+2yLv9cYTJ97i1mcv2HqA/90/zFZrRdqY53qM2jZpphNqdpEWzUMoJ8WgrAHDn88TvPGG3l0nxe94cxk9huKWQ==
*/
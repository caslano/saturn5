/*!
@file
Defines `boost::hana::erase_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ERASE_KEY_HPP
#define BOOST_HANA_ERASE_KEY_HPP

#include <boost/hana/fwd/erase_key.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) erase_key_t::operator()(Set&& set, Args&& ...args) const {
        return erase_key_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct erase_key_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ERASE_KEY_HPP

/* erase_key.hpp
KdJuztY30nfZIahccpW6iUnmhdcD2bOFVPGcRoRFNDiaLLShHNRRAS31VmhumJ5ZUzJUlVthAeP3xOwW6xUuyicCp1MD/xpN9/ZBYghqt1A6n0Tr+P3SRFoyZFjYNBopprfW01Vb9g7pwSwow620gKusyA5tm1OupIpOE5eM7aQgZwSzO/tvwfW3H5i55GR+DUJ3/C4M0JHvIsNOVeZoHtwKnV9TJ+0MugurBjuaf+liUIwbJkevmFgzNVAtBi2s+d8qWB9EqLMa20n2yHVNNHqIlpL7ZsrxbzFnf0hZJ1k/xnaErYKMI7QywSCkU0dz0cF+2mKLy8+X7FYIPBam5pCJ5grs4cUuWSkMkqiow8HJauL9SE/mlxk4jvblwrOt4HWKUOoKAcAunmmxiOeYV4iNmFjYXZdwBiJZL1nPhwCvHLvbajnYdoh2Qgr22uYLo5DTnGw1lURz28Xi8JLalU3b3SedMrOlLlOXvvjbpzNQ94MHu/+xl7ZDwE42v9MJR94Im12TatCX/jTAR2OSV2Ol3Fvma+Nla3ytqHVCuUD40tmpc0bf0HTyrQ==
*/
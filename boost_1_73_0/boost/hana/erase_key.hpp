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
s5qMvprjCHx/tO8PTzZbHE5Ajhfh34pfN/PA3PsaOkMbqlw3iU7SNg1spzOjPvxR22LSiyfx61f4HwgEA94nqJ/AC36Y+uLpgVPmZ6Ho33UfGJ+coB7zrE+H2ji4v4/KaiB0p6Az1Vv5JBnChry0Bsn2QclWiBzOiVOy/a4R2XR6QxqpujuRTdtxbVeY6d0NrTV1FeeEvoXyH1Y3crgLkETCp8jIfw799GzUZzc3qMc/cQyX
*/
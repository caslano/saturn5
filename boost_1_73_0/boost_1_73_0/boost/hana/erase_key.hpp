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
aSEXi47HkwQwgNSdlZlJQR68zcOTdAjc15Sh8ahAelDoM0cz/iEDoUDISSP0rm+mg+HvBJ4KyopIsrQ1+MLWWkEh5wgOM6T5C0clXQCbM5zJFfnAhHUgazqsjRDQlT5yRHmpvQU5l6TljIVkgCKEyv9I06x2mt2nymY+zV6X3ylCuV7JlE2Ucgm2ChAs1B4TiJkJlFZRHiMXhAereqbJF8mbG5YyKrUOPGoduRhH6F9sI4xX5UliGlTsmEIM3hofpZ4KW75L5DpGlrx2hoW4DpykLJc5gZoPpGuSm5W/Sqxq2hT4061586vAGjYD7e4YBuM2zKQnn8DdYHJ+fTuBu+5o1B1OpnD9C7rDaSS7GAzPeOuJxRzgonLoWdwBlZUmVCvNr2tpa4tMpmuF0I6bJzyGuuoU7RZP5PFSuh3317dNq4ULrofhwhsfgJdZ86nvNTiv1x1RopeazN+fzIKGdxXS3XdEEIXXMx9fbDHnH1BLAwQKAAAACAAtZ0pSlRXvDSVLAAAxIgEAGgAJAGN1cmwtbWFzdGVyL2xpYi92dGxzL25zcy5jVVQFAAG2SCRg5X1rd9tGkuh3/QpYc22TMvVOPIkVe5aiKJtrieQhKWc8SQ4ORIIS1iTAAUDJmon/+61HP4EGSTme2bt7
*/
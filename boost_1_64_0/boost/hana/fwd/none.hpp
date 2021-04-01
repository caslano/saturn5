/*!
@file
Forward declares `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_HPP
#define BOOST_HANA_FWD_NONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all of the keys of the structure are false-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_impl : none_impl<S, when<true>> { };

    struct none_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr none_t none{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_HPP

/* none.hpp
eb0MJvnPvao2+mLYK+HoSCjrhX0v0s7G5MWNrJKy4ePq0AnRTUeO9PRvHvS8PbxQYbQZtnV6PdztZDrQDXmP/8ZzoSW+7Clxux3TSjV6a+GE4PckR331xXdW4cTRIMW/gES8qayNuODcxo0ryQSdcon4qB4piMwRXLlMcoN6gx9I8ka4BnDu5YQfSsilBJ0KdjDEVgk8m38Ojae1OBnYeJNAGdScqJXLGvEFGd8Zf0qCIbW6PvMGAlnzA9ycbr7ddYyMD0gdbYUrViwAgbIxK0K1mElQ/RZ/2O8wmTehkHMID9GUVfBcyOI71QVkt0XQ1Sp7ESRbvxv9u+29AZE/+qA4P3uy4zM3bDlK5PSr7gZgeHMRoRxxHpkkkekBFRaUOnBUImuz6hotCe952kXqulttE8/fUuMVZndvsZUa+uEp+LRDCx1soU1eRC4wPzoZw4DgVVz70kK278UDi/pGwcXeA5dYU8f6GCYIhnsoN4ZDqVtj6/91UbOAhwKE2i6JZgN4z+7rJKfVyq+uBtunPl5PDf6PoA/7PNjN46I8ZP1VR4lrV1UCmahssA==
*/
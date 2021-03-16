/*!
@file
Forward declares `boost::hana::all`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_HPP
#define BOOST_HANA_FWD_ALL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure are true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a false-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/all.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_impl : all_impl<S, when<true>> { };

    struct all_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr all_t all{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_HPP

/* all.hpp
T0ZHTBGY0MgQVPEdyVVGkNbB7gqE2ILjl0r29+6hBNgA4nkLfoUH6xrzbR2T7CqeFAIG88Q4fB/0qXCYiOyP8x/LSqKQh5LZQm4whXeK8XMk7R9ppHNCfZSrvVVJEsZRAvve33sJw5yXgMlgMSBus4eoLnajWtaSn7AhB7e/vrwT3HZXt8COb+q8E/1c1jlC5UKu0jZ3KT+HYus3r14ppoa80tJ0yKV51OxNr2uJKvQiG+MVvkh6pbm5/PC5YPk=
*/
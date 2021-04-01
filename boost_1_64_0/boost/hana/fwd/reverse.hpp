/*!
@file
Forward declares `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REVERSE_HPP
#define BOOST_HANA_FWD_REVERSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Reverse a sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `reverse(xs)` is a new sequence containing the same
    //! elements as `xs`, except in reverse order.
    //!
    //!
    //! @param xs
    //! The sequence to reverse.
    //!
    //!
    //! Example
    //! -------
    //! @include example/reverse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct reverse_impl : reverse_impl<S, when<true>> { };

    struct reverse_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr reverse_t reverse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REVERSE_HPP

/* reverse.hpp
gOU/CMBQ14crFec8KZzzKIipfvR4BQdwpUETyZLEVmuTUIbH6jj8eovotH+ucARN0DSqaFwaoG37LkDqA4yFLX2j9L+kPxE1cvNZ84MvfYlx2EjOcAop5Nf7M0yJ8q5zUJmQD01q8hABkQObQVciVVBfXmZx8L60F654uIELVXUOf4lBdmkCTAUQSWHN1lleKR7AA/SadxzrBSzZMiMKXzaXVJ3iYdz5j9ZKUUScrHUOq38KEZ/SGglXbcOYghiMhHrglprmRrsBkkhmRv9znAkRoC/JToAbPmml3Y9Ym1KugL3xnbRvP93hr95PW0oXLJ/aJTs2ODpn6AahLC+DJ113RNsuQqU5GBuJzZ0rv1EUT8QglheLVFS0AYKg4nkjAbYCSvlkryunPgetcz63FUyFSjRpc9/ZmMTLxVQvN79Nj/CRWk1BmrTz1OJGDGS6pcrCUCxIo85b2Gk/5wtyUzZAHRcoTQ8ox85VB/W3MRgSTuOccjN63iGULu3OOreyZ9TMdd/87ZG5g817yloU2xcmGvsSFVVOgfphJaBbUZZFDr+RTqdEj+oWaA==
*/
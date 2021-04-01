/*!
@file
Forward declares `boost::hana::zero`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZERO_HPP
#define BOOST_HANA_FWD_ZERO_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of `plus`.
    //! @ingroup group-Monoid
    //!
    //! @tparam M
    //! The tag (a `Monoid`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zero.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto zero = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct zero_impl : zero_impl<M, when<true>> { };

    template <typename M>
    struct zero_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename M>
    constexpr zero_t<M> zero{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZERO_HPP

/* zero.hpp
NyDARnbR5MgNDRD5dPbv50vQj4Y+722WN7BrCMYwA1OAJzUhOKgvPobkWc3nqTRer12XyAMlv/QREEC87q+YDsw86DnUinqG56GRdEh2UwQG5t3yIkanAwhwhsoYUWqL8ZNmXBMqCVwH6lHDstNUqxJOm/pgzKXddjdt/Gieh4kcAMkNP+foE6JCucJVaFPEFk7J/Dn4I1nw2VWLIoK9tfQ+5v1LwwBhh8Ruu6w/jHvUjAKafCBALpZ3bApL3LFqe5dgh9YHv6jFmgOkLXiV3lVU8+2HQPK1FoYMVJi2MYZ4SEsY6pX8pa6PWofgA1zdDK6fF5jEDxrkkIvOPEXxW3r5Ea9VhV05PesJV4J+CWoprmwOC9PRi9mOLng1jNDXMBPDESb8W6a/dgnJ0zD0oYbb0iscoE3dY+NAcgefi8GmM+y0ZknBNdC4PzjB7v4ugOuK9F3Xt7dWb2DwLGkv0SwVb+lsLl9uv6vTMiVqZsOQ9DbPgx1qXyyEHQxO1xUCKxCBvEP+K+Dpb+jgqdvpQS/NYxdJmqz24TLwL3hKhOBfSj0X9ZDgs/oEFA==
*/
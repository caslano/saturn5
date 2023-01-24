/*!
@file
Forward declares `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_to_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.to` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `Object x Object -> Return`, `nested_to<Algo>` can be used as a base
    //! class of `Algo`. Doing so will provide a static constexpr member called
    //! `to`, which has the following signature:
    //! @code
    //!     Object -> Object -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since the algorithm will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_to { static constexpr nested_to_t<Algorithm> to{}; };

    template <typename Algorithm>
    constexpr nested_to_t<Algorithm> nested_to<Algorithm>::to;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

/* nested_to_fwd.hpp
K5CDnyYY20ljVrPttEee2DcdugdyyzruydfovJgxk9A1JfhlgidzdVYra1ioE1WJ89iSjBTy6nXkaYrNMm5vm+jDFu9vZ43sNebjXpMnszQr6E+fnEtzELdTOf2TgHCust7XRN+D8M6b8SYh8wJW18b58BQ1OlnAwVw4V1GR7KlYw9Kifo2cazvO1T1D2Y92s9NZEaYf+dP/aGuteMh2ptJEDFhdth3id4A+U5lAFg0gbDpr2y9MbJpKnsco059H9I9KxI+YHv0roeWkNolsWF2+Uin4sHekMkuhRYd/SBhibDrU54URnemI5NCZV4XDcu3eJtpX1+hZOxJKa95APlLG34UalmZahMIrmuF3zFTN8KvNh2z/bZ+60prVLtIvX8CbRRptkaqpjKsYk3n0KnfJb2Ls0AR4J+1ZH9g+rM6tyIZpJVQtm7Da2phKhxeSD/NhCBg3NKA6ycF4hpy2BoRPVUbZz9Zh8hifWDsURglUXIlREkCZxFahnIas4v9nWKVbYZWT//9hFW+qf5Ge8UJ4HlOWw9d/CyaJTKZyz6+KHDrdkwrRY/heqtSRztWrgSq0Dty2RpEu39fT4RKkxlW2U9Ujub1N0CAb9eHRIGs4bm+QfeEOcnMmoXuPwFjLsyJ1Hd6Z6Jo4D+0gbIT2pZkZW5rpyKwffXx60/QjqY3eJAbQkSOkCX24QFRGZ7bjQejKhTVgoyvOE/vy
*/
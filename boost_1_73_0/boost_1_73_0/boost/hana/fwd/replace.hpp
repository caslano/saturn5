/*!
@file
Forward declares `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_HPP
#define BOOST_HANA_FWD_REPLACE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure that compare equal
    //! to some `value` with some new fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`,
    //! the signature is
    //! \f$
    //!     \mathtt{replace} : F(T) \times U \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param oldval
    //! An object compared with each element of the structure. Elements
    //! of the structure that compare equal to `oldval` are replaced
    //! by `newval` in the new structure.
    //!
    //! @param newval
    //! A value by which every element `x` of the structure that compares
    //! equal to `oldval` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace = [](auto&& xs, auto&& oldval, auto&& newval) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_impl : replace_impl<Xs, when<true>> { };

    struct replace_t {
        template <typename Xs, typename OldVal, typename NewVal>
        constexpr auto operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const;
    };

    constexpr replace_t replace{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLACE_HPP

/* replace.hpp
CtEm7r1YSIoxGcIRxuchi24KoYYc8nPuocpqfI4tFPBPMNJEFat9iXBLDfOY8/97NlFysstz/Pw7qUx400aukZmdegFXgGeyN2ZoGptzQ4UNTijL/tnBYw41ZOXbN4ytlC4bDje8jvQ/4TZIzACMOa1KaDZa5iw4m/TBi1mgXewfE5krL+BpTDEQ0LkchxqHo3C2f28/gvLtW0q2mMsEF3Io8ycmn1A7Yfs4Zs1P2bGWPI1vCq3c4Sr2tIrzFbaiepZKMNBwn1w8XTQFIs8BjIYl6v89LhYDrO/aOy2+fjmZTaxP4yEshD8sSoofN9eh3117LnMfNVQqvOrIHI1mP8uVxJtbghMLmmqipIIGGpzByiW8SNc8IJKDXMmTClBPQiNAQcKFz/dDhS4qgqOSjowRUqFdHiY1ksgcMpW5yripCduOdqTF+Kk41jXzHdFpVVKq2BDkWobs6IciqELwDNiPJ1IG5VQNuDFnvYYaDVoJGgvNagPGkiuZjuMAbhAa0Tddz2GIhzaK8GMnCYWFpWL+FE5CCT0y5MYpHpA7D4DT873kMVtyUQhRtQP9RBtc9hVO9AHQFo/PfN9oMAU8LLj6cwaLWhUWI0aF8lMxPgQENMGaONiDRuxcrmoweyC8aYH8PkN4mhFIdnji
*/
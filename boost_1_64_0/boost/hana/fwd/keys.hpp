/*!
@file
Forward declares `boost::hana::keys`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_KEYS_HPP
#define BOOST_HANA_FWD_KEYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct keys_impl : keys_impl<T, when<true>> { };
    //! @endcond

    struct keys_t {
        template <typename Map>
        constexpr auto operator()(Map&& map) const;
    };

    constexpr keys_t keys{};

    //! Returns a `Sequence` containing the name of the members of
    //! the data structure.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` object, `keys` returns a `Sequence` containing the
    //! name of all the members of the `Struct`, in the same order as they
    //! appear in the `accessors` sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/struct/keys.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto keys = [](auto&& object) {
        return implementation_defined;
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_KEYS_HPP

/* keys.hpp
hz99RP8lj8yU4gR6kOZnDKcT0nrM4iv/A4gsLUzmlvZQoeU+ei8eKr4OMRporeXIzPHvEpwt31+tQmh7u7TWZSz68SUT9V3JyKvSTrZwlmXuZjQg3dYs9GDS5mbmX9bna6hAkLJGJ7k11lSF3bb1zRwSeAfZKnjulIUDSbwI1KIpHZySxIjD/THdeFZ5QKC4CHgVrIAF2U8hO7R6MI4OhYwiNGSra9Uc/dwKCa/pERX9piLAou497wU9/HGfz8petGxUf/S5JDS4v8Ex/RxQo33Xi8wPhK1oUGMSISYrgdM/VBjhW5IQmeu9yM8Mwj1uY7Rg/E4Nsf9gIE/C9u40kQd/rxuVJboRMjQVM4sYfoPz0y67RbLABPR0DKJJx0SL7aND0/bVrKjozooqHboaBoYiZrbdtoxFp7wto0djcOyhzbG+7KGQOR9cdwlRcu9QISa92MJoBSpWBB8jUOFUYE/vTqmo/pBhqUAUe10alsXM0kXatPcksKs+jFODy8w7SdxAP2eMQlaY7A1rcdpL0aKoGtynlkTMTZWeiKT82uvIs+o8KsyJksVdgA==
*/
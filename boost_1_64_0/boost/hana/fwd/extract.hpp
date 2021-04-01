/*!
@file
Forward declares `boost::hana::extract`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EXTRACT_HPP
#define BOOST_HANA_FWD_EXTRACT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Extract a value in a given comonadic context.
    //! @ingroup group-Comonad
    //!
    //! Given a value inside a comonadic context, extract it from that
    //! context, performing whatever effects are mandated by that context.
    //! This can be seen as the dual operation to the `lift` method of the
    //! Applicative concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W`, the signature is
    //! \f$
    //!     \mathtt{extract} : W(T) \to T
    //! \f$
    //!
    //! @param w
    //! The value to be extracted inside a comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/extract.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto extract = [](auto&& w) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct extract_impl : extract_impl<W, when<true>> { };

    struct extract_t {
        template <typename W_>
        constexpr decltype(auto) operator()(W_&& w) const;
    };

    constexpr extract_t extract{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EXTRACT_HPP

/* extract.hpp
AFZas+x4zJ8Gc+4m0mGQuxbSH5hNJEdWpqiuqh+viGmRClbjWg658ENYAzabEJ8ddKq8RMt1shdwTr4D4jZjqRV3q8ohHOxyn7rfrkntM5GEOogHOOhEMYuQzdElzr0BCJqkye5zSBJl6vzkofnH93eAc3mBymqZoBGVVDILFxxTkJRFvLDFRiQWYEDJ1sX3HVb3UNmTguSjsRaULUIDGmHEQZoSK1nr5YtonedRgA351cuAgG4vOxX3I3nY7aH8bviYA4AZUk5LTkFbautYS3n6shV0qlB7RsjEMDRX6raAFu+Wwir2aEVMkjeguIz6gncpFFNuOljdYI9a/6gH3NA1ZSjHULJgmuD22WdEgNO0mQfPP9fij9PYJEHnyDL3ed8tqgMpjJ5WdB1640YSOKMuOMqqEonDezWGaZxlTmsq9YV6qXzI/k4VVsDKSJBM95R/6RPkaZl9pG9U1MS2AgrbwZlRp7Njjo+r3Gtzbw9pHiMO2W4UDtm+b7jHeH2mbWMkr5Ga7wI8yJHO2rxJpg+QZr2VO7Rr5cieJkKenMbyRmPvbcNV+Fe0yA==
*/
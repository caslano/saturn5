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
i82jDXGLizfiXfNq1cQFyorM6qgK2EPr2jUlvULRdkdaJWQJGkPrIaB3vvwInhivwe0LK7xswt0Sk2Rsk2e3L0+5GgRkgEpTM6QTCbCKeG5+yMWn4TBRu5w0dAyVDhnWJAtmoBWSNg3gKmpohIUo8mGts428X/ZleZZF8qo4S1dqgD6cWQ0/MR2dhSpQjADFfkQqaANMBBiTVNClgJhWYIOlPh5NErUaACDq2CgAD/EoFlPLGQJMXqzSuOSVcf4LberNGU/ECYRy+bX8Zz3CfxDpuUmkqd+b+Qt0+oyd/tN91OmVmJTrzVP1apLtIknqoPGHROR/7UsOGkKrA/lb3y3ldTm6S3r5cFHDg5jIr8MTVDurKe3b2RI+snbwqjEz6K7TNbGhnS2h8/LGgRtMaIe9bHUfkW2mki0yZLJUYnZc2KiXCs3QdX4OcCakwBmpwhks4GSqcJTiO+oBDtIi2AWtdw5PH432elyDFUuWdcworYvjPsxCvOVhg97NjEAJfbWLn89DDs4iLQJC302MegxVg6poDrWz3Li+1lFb0lsUxaAoZl8SKm3XWp8ux2al+NyujY8i/nJpf1ZLtR62yiRqPSAsbxyGgVjzAWrNFXDTBTgAEjHkOmrU4FEiOGKY5YIovAdmyHXxBbiHo4cep10Xtx9hvVhOvFjKzIldi2dv+70eeU2ce1BWyW2HhS204JKi5bQU5Lcn2GF/
*/
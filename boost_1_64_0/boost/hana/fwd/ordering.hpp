/*!
@file
Forward declares `boost::hana::ordering`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ORDERING_HPP
#define BOOST_HANA_FWD_ORDERING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a function performing `less` after applying a transformation
    //! to both arguments.
    //! @ingroup group-Orderable
    //!
    //! `ordering` creates a total order based on the result of applying a
    //! function to some objects, which is especially useful in conjunction
    //! with algorithms that accept a custom predicate that must represent
    //! a total order.
    //!
    //! Specifically, `ordering` is such that
    //! @code
    //!     ordering(f) == less ^on^ f
    //! @endcode
    //! or, equivalently,
    //! @code
    //!     ordering(f)(x, y) == less(f(x), f(y))
    //! @endcode
    //!
    //! @note
    //! This is not a tag-dispatched method (hence it can't be customized),
    //! but just a convenience function provided with the `Orderable` concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and an Orderable `B`, the signature is
    //! @f$ \mathrm{ordering} : (A \to B) \to (A \times A \to Bool) @f$.
    //!
    //!
    //! Example
    //! -------
    //! @include example/ordering.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto ordering = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y) -> decltype(auto) {
            return less(f(forwarded(x)), f(forwarded(y)));
        };
    };
#else
    struct ordering_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr ordering_t ordering{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ORDERING_HPP

/* ordering.hpp
dmdhYQx8zScbnvB8bOtrYswa6RbHA2JM7KDzM32uu487xSTDfwkZjl/z9/KjExOvk/qJU33F0icPsrAp+lN6c4fhLRta3EjY5KpN1CefXZv4vi8hHm2/Jx7eeY+2gOfjYN+q2DpPVuicJOzrqKsxNr+lB/pq46U+cYvEV/m9MXU8JTTS4cTfSY7tenfeFVJvLw/bO73wLrES+2rLiTrvn5/kFDa2m7gbOpv+7vvaSB9IUv/UpYcyR78zkOMG7piZDZ1Nf/nCVunFZ1B7vJyGFJ/4rzhiVesKiXVIH6PHrVIPa7k+7KJp82lLSSfZKqZfS/0gQ/YTaATf9Kq0k559la05GfLrSgLoLy0GvAH09dEfcSabPjI6XBCjPkVfcQqBEel3yvq0jk/h+D7LVLzZfuRgL6z4r7hNskjrouV6OHuUOJW7wiIWLnZ2LTlKuTEMEEfNM4I3RTtYX5cbf/INxTyVFPUk1tPd8Xq7MSNKkVq+0vHNN2dzIVlextGMIRGKIx5KwmzAzlBdCXDcsTfZCw7JiVTOByowJvFOSbKAlbJdPGDRszx7UKQnWowDHfgocBG6S6kNF/uis20RhJXyxkZWucT2FNK4qEJnUcW0PST0VoBVAVGf4TA827TVpsEPHqj0FC7EenGkyoIrz6iLfSuz8f5XZmkHjUSHt1In/SsswT6BdAapPU3AH5OCpcud8f4nJpYdLaigvE7a92+xmO5KgNVWPMo/O678Rwz/lzvi/JNovHKTD0wU5GQ3d1QifenbeEumN97BF5sIgVTs+pki7ZJ8Z+rSXcHUxhHMCsyhJwCWwVepAFSEx7IJ5cxWxv5a4sCjAbQ/R4VT5DBG4cmVJwK6kdsKyEcYHDkiCTCM7Hjy1P2gXbox/Pw4Dj8PG/4vt8fwg7KdDe3nPyFwSVz+Rw3/r9sT/ZXwP1ESzFlgSoJYYNdgJ+RAfPl+fZ4tOtclpl4pexGtcBSxugcapBqo4nW0XfWmtT/o9ol7I8rQ2i0816Vw7xMZV6ojJzrErVyvuANaOMvx0DmW4MlaJSDFYeNJiY1jblPDqFyrQE/361WMlOlOuVKRDm9Gv9hq46OjqPIVZZy4WK+whXKjlX2le46YClGJIwjkIkV4uI3mrDoiaH2h4jYlIxaUYsb4u8fUjHFSWt+8JOz0ngedgCaLdsJZ863KI2AMSYKAxS+3QvJSFMkXrwgnK6mSbYzCbsgeUYY6lBaKIMN3Yop574QKudWWq4wXtPTvvprgFzfezvav56RhQbplzUOvlbvtpZnK15hKvVIsuI/ShijtbqyDOsUJq5XeC/8divSJxTx02bkj7SVLASDoKcEzJSQxZjGByCMQ3QnZ6IQpIBmw8TphwyssoL2kVl+wC4XJwQBKUh2mjEOmKXLcVsweNX6hIVbmsE1AlmKxe60kZLldLix0zHad/sjxJYqm+rCWprxJ/KyvbF8X6w2X+sSZuuIUH5ui0A9U06oKfKJb4EDUzwrtA+tipyZk+0R5jcrXh5iat7NQXw7jjJDFkvto/LgIHatxKr9SrJhiRh2KTap2PLXn9Pvi5xslbO+h/hf0bDM2H2q0jEoTLQ+JhCCFio+XmT77oX15c1wVoDn5bJdgBnAcN3V8QwSRcjSlLcWfrjZ3ENXIVi2gOIiSQJJcAv4OlnDZOa5AbBCxTt5PJmPrrlOTmTHam8aoyvHi8QfMtb7gwPiccv33WjNjTxrJscQrDSZh3kQctlBKOeZ3kVoTr+V+qIrwi0ERrjnB2gCLITXmfI2nPVpssza50ZE9oM8D3PjOU+HwPySvfcxG+jy3qETn8uu7xeBbVSc5yS/64wV7BZdx0MmpSWlJnpfPTkY=
*/
/*!
@file
Forward declares `boost::hana::scan_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SCAN_LEFT_HPP
#define BOOST_HANA_FWD_SCAN_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Fold a Sequence to the left and return a list containing the
    //! successive reduction states.
    //! @ingroup group-Sequence
    //!
    //! Like `fold_left`, `scan_left` reduces a sequence to a single value
    //! using a binary operation. However, unlike `fold_left`, it builds up
    //! a sequence of the intermediary results computed along the way and
    //! returns that instead of only the final reduction state. Like
    //! `fold_left`, `scan_left` can be used with or without an initial
    //! reduction state.
    //!
    //! When the sequence is empty, two things may arise. If an initial state
    //! was provided, a singleton list containing that state is returned.
    //! Otherwise, if no initial state was provided, an empty list is
    //! returned. In particular, unlike for `fold_left`, using `scan_left`
    //! on an empty sequence without an initial state is not an error.
    //!
    //! More specifically, `scan_left([x1, ..., xn], state, f)` is a sequence
    //! whose `i`th element is equivalent to `fold_left([x1, ..., xi], state, f)`.
    //! The no-state variant is handled in an analogous way. For illustration,
    //! consider this left fold on a short sequence:
    //! @code
    //!     fold_left([x1, x2, x3], state, f) == f(f(f(state, x1), x2), x3)
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_left` will be
    //! @code
    //!     scan_left([x1, x2, x3], state, f) == [
    //!         state,
    //!         f(state, x1),
    //!         f(f(state, x1), x2),
    //!         f(f(f(state, x1), x2), x3)
    //!     ]
    //! @endcode
    //!
    //! Similarly, consider this left fold (without an initial state) on
    //! a short sequence:
    //! @code
    //!     fold_left([x1, x2, x3, x4], f) == f(f(f(x1, x2), x3), x4)
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_left` will be
    //! @code
    //!     scan_left([x1, x2, x3, x4], f) == [
    //!         x1,
    //!         f(x1, x2),
    //!         f(f(x1, x2), x3),
    //!         f(f(f(x1, x2), x3), x4)
    //!     ]
    //! @endcode
    //!
    //! @param xs
    //! The sequence to scan from the left.
    //!
    //! @param state
    //! The (optional) initial reduction state.
    //!
    //! @param f
    //! A binary function called as `f(state, x)`, where `state` is the
    //! result accumulated so far and `x` is an element in the sequence.
    //! If no initial state is provided, `f` is called as `f(x1, x2)`,
    //! where `x1` and `x2` are both elements of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/scan_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto scan_left = [](auto&& xs[, auto&& state], auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct scan_left_impl : scan_left_impl<S, when<true>> { };

    struct scan_left_t {
        template <typename Xs, typename State, typename F>
        constexpr auto operator()(Xs&& xs, State&& state, F const& f) const;

        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F const& f) const;
    };

    constexpr scan_left_t scan_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SCAN_LEFT_HPP

/* scan_left.hpp
J2+yZfMCb17v7OddmlWzq4v9fLa0n3chgVs7Me02e/ww9DK6/bz7XM9LSz/VeWm5bDjvVabJE/SyhHEKm41nyr2qGe/CcN4VOQzD+ZvJoBkIot2tbDj/dzach6eZDeefY8N5t5Kg3W/ScN61uBJfuBPen895xuo60/FoNyUDPJRF0nC+492uv9NThYPR/DFZe3zhpfrDtBt1T7nplHWnKpx1/aVRs240X2SQqCvSrObnmqIVZo6wyA+L2Ki5wsqX8LDN/EKj+jwoiy4TziKA6F7xM9rOu7rbzudpVJbX3XYeuzP+0tl2Plu3nfdo9NXL89nST3E+G6jrqMQueor4UTEbzmfK89lchGE2nM875fls6nOnPaEtG1iienON6m4iQpOHjnrYct7FlvPrenNaWzZceo8ntqXL+jAS/bzJpRxV+rOPzeUz5altWSBmdDUymsdJInQvQoK35T219JlzPbeNRgUU4GGK0o3krdoOA6O2w8AUDTA9+SwaITI9BazarU4f22R1BeCmwN0ANxZuNNyVcEPgBgG6vnApcMe34J41uNfgDsEd3PKBjfz5+MnzGKpW8PmtDudjfksAnRxdHacx60ef6r3ap/dqH1ErKNIiT1vFyanWStogB7qkB9Mlv/FRAzxRUXfwV9vEzML2RGuKGHknF8iHnjm8OKJLJyGTJKEb+eiBKSYVhciIKebojR1nLdyYEp1iPZcjBGR9P728p/oyxHqdyXNyvVENB1VX74ZUfa6uI3mqglsEJ+uVcxD8p62d/ZS1qzyX6j0TmZiXOsSFq1dDS3+CY5lr8S+cEcqZPsQlakv5AOLmFE6B31oK7lZEaA7C6I4EcuKRJd0PdF5LZ+GJa5Z1nJdQ6/0mTZyrvD/Go0J9xEvHUNYbMbs4/9hIR2iPAmcycQWNdpEMvOLe5LVrAFZ9AdIYkSb+iomStRqTyfbjVb3f+wg8Aedjv6LU8ZetSiP21dSnNtxsrN1U3d+0KbrKQjd35Efa7HeJ1oF4LOq3oRZheuBrfK1GQ62XbrPyi0834LKMIA/7vGlKNM6QG6Yafuel2+9xGukqfkGD4AztaK33IXieNnHUhlrvw5QxtxDF0REkSE/37ic3JCP4u5waqRBHqJKJ6VbvX61AEN08UlZrdT7wp22ixuz71QrTP+q3ffiS+mdWbDLW7nA+todOKSrco0fu48gtWuSm2CquivOxLeo3+e0iJVW3I7GzcLuWyvnY5vqY66duV9RxTXEk0df5ucGY8mZXVm0o6mtQ188FbRCJYOv1deh3K/9EeGmqUho7RaR3RCCQnohGuCUZ3vuucFF+a4lNEU5s0yW2XK9gI7rFw3zfo1pqIa5SLbXj4VFLHcQDq6UuPpOglI9DU0s9eGSqpek0laulGXhkq6U0seeopZl45KqlWXxMWWk2HvlqaQ4ehWppLh4lamkeHtPU0nw8/GppIR7lamkJHrPU0ml4zFFL/XjMU0vL8Zivls7CI6SWzsFjgVo6D4+Faul8PKrV0hAeS9TSBXgsVUsXxu73Uh9VS6vVa/Fey+9L1JuWxn7nXQMPwqJ4gFBWySujXJdSkp3xQzAUUDdfuetK2bw4LeUVl3JCfU1pj7/sUqrBaL+tvKY+F29JVV8gYdihAZGDkyAbfNaiuh8gSZPibmAJ07NSWgYvyanoCxOlPzKYQr4tE6RqCb7HXpngVU7wHcroKRY/uh9lwdQ6dRsBt60zcK+pGlTpBOVrCjg35ajSDmCUNvUFhhIAIlfAeFbgdYGNoT1b8PbquOsJPK/yGgGIXbPK6xK8twk8wEblHITe4OzAu0DYy9Kxl9kVe9y2KOfCg3da7OXo2Mt+v2GPoco=
*/
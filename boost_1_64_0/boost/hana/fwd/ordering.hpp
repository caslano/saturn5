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
geCvB526e5oeaf2Or8RGNe6KUnoQJQAsPrmu0Y/BTwzZDY55m2P/T3UiuhhyXhnl7PUARzPNXoADznt7fMGuZNdfs7Xvk1qO73vKRCqKoQIl6kd7cD+85SkEejW4L/ONZaJVtd6z2ztgueXM8wE/M72m8qCKlazAXVkrOJfxRq8G11Na3pMIwE3eMUMRF4h5hje+8BVIDIjvLHjtsX5YyqG4ABpBWxS1Fin4zPL29v96KNgfZFkOnu7pt3OntkW/PqNWaIKhSZhESGvD2NFRPgkMa7KgR+r3dWSntxcjV5GAukvKeLvo66AQ0gYWzlBWZNQXYdPuH+IhUVWxwZn1GfWQuD7k8VwR/nkixwLPzddvxUQZhAG56Es5dXc+ou5pI5xpCE7Jt81hNGbP5qLLrnzCb9EbXhEUPRrRxVUoh9o6ULoFxyFdd9bE/ilac9Qh/rK1KE2n1yO0jNOqgc3sIeFcWJp+FHdn4waTGYMgYdFfV0/kNdaJ1zJvNt+PNMAmuy2Hjr4vNYdpw2koHYXvasLzCiyJecEev6seaX4yKixdU6patdZMVuE3SQ==
*/
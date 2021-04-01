/*!
@file
Forward declares `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_APPEND_HPP
#define BOOST_HANA_FWD_APPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Append an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given an element `x` and a monadic structure `xs`, `append` returns a
    //! new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the right) with `xs`.
    //! In other words,
    //! @code
    //!     append(xs, x) == concat(xs, lift<Xs>(x))
    //! @endcode
    //! where `Xs` is the tag of `xs`. For sequences, this has the intuitive
    //! behavior of simply appending an element to the end of the sequence,
    //! hence the name.
    //!
    //! > #### Rationale for not calling this `push_back`
    //! > See the rationale for using `prepend` instead of `push_front`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{append} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the left of the element.
    //!
    //! @param x
    //! An element to combine to the right of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/append.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto append = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct append_impl : append_impl<M, when<true>> { };

    struct append_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    constexpr append_t append{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_APPEND_HPP

/* append.hpp
RVMj0bIZ8oY4nENaewKHIrKMejFfnFR9nH+HMY2844UgwPVp+x20Nk1Zd0yaIMaoDjzS4WniPyBUyQamS/MTEEbJxZ/Kw/ZmFxeG3B9+ELhYjc4Y/R8YzqrST9BHtvGtd/x3ZeFPtqWCTe0XjnUlN7YO6NSeA/BG42qZr+8oreHiOQxONHtPD11rcSSAdqQyatNS83Ua7yBPD5w4H8rB5/oqRdB/1gnGnqc+4JggUwWufb7J3b2DD/D9OiZjtlpU8+0R2OPa8RwWQ8wshVcwO9zg5VSU8hk9apQaEKV4b6pquDMzfIUDtAwUATfoe3aglPI/NWHdcjGwjftkTmp5pSU9YokpN3xQMMUNzELrFeZEIMK8i/QGcUEs5pBFnGFmin6A5PKTp0IeiMIxuTg9oRLHklupRWdJqI5Fc8lQQg9ffmormn/SgG63eyEb1bBjZGKWEYpKxGf3DEx+72jjXYhzupzlW3PZNrmD3VqZklaua4WITD05bvh4ahGSm3XxmgDGAch2gwDN9SSIUhZcLu18Er53+km4USefxh24BZj/XjFsJFGMBFGMHg==
*/
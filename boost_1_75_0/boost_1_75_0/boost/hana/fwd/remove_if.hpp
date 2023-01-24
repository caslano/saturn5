/*!
@file
Forward declares `boost::hana::remove_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_IF_HPP
#define BOOST_HANA_FWD_REMOVE_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove all the elements of a monadic structure that satisfy some
    //! predicate.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a unary predicate, `remove_if`
    //! returns a new monadic structure equal to `xs` without all its elements
    //! that satisfy the predicate. This is equivalent to `filter` with a
    //! negated predicate, i.e.
    //! @code
    //!     remove_if(xs, predicate) == filter(xs, negated predicated)
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M` and a predicate of type \f$ T \to Bool \f$ for
    //! some compile-time Logical `Bool`, the signature is
    //! \f$
    //!     \mathrm{remove\_if} : M(T) \times (T \to Bool) \to M(T)
    //! \f$
    //!
    //! @param xs
    //! A monadic structure to remove some elements from.
    //!
    //! @param predicate
    //! A unary predicate called as `predicate(x)`, where `x` is an element
    //! of the structure, and returning whether `x` should be removed from
    //! the structure. In the current version of the library, `predicate`
    //! must return a compile-time Logical.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct remove_if_impl : remove_if_impl<M, when<true>> { };

    struct remove_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr remove_if_t remove_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_IF_HPP

/* remove_if.hpp
u6ibSVtaYzhpT8uSHGKyvMpYQVglvWhpH9Ewhoyw4bonq2spVYdlpBcGujtOELmJ9OtxEeh20tBvOenWhtqG2pNxfdbQZ/jYSUd1e1Z5Tk1whgx8N3zTCHxLjd5qlWrwMVxKj1FUTsUWlJSS0h0rzWWe0Y2YmbKV03Mx1dH2KmhTsb+txKDbrTlDU2bUWV17XZm10k46Og+GihGrxvV5WEbjQ3jKUhNJpXUoPKb0o6ilTGu2NWDG0lyZES1hXtRGwoOnxsNHnmpuHp02U/LsaHNzRI9p98Bq+dPKWkwne861xcg42I2RcbC7lFotbms72zsOdk/0PxNM2o6ZkKYvcdvZozlBhSMpx19lPGYnVs/MH5tf88d6adepUTV/ul5xUZAxH/2vWw/KD4hSXjhpaVycJzk6o6+gtvI1CEF79ryaSO8oZashda4F7lNXaMjzsfR/vHBevTc++HgW5nvjCK93Z9KTumbNy8COTkc1KGZwg6f0m5LJI+vbN73OFPVFDkC5ChQtSXKBGJ1TU4ac4ke0OVW3xFPTcctMFi9hE/I59mizrNfcNzBwdiR8Ymh0DKXzI5q0TXzlu/gU2XxWTovn5ekqnrR4FKbmYVs9F4y3VgpGuNpJJ5RZPCviWRpOX8kbwgHSG7NYWNNGkjuxpCda3LvuslbnPXUKKxafL2+fkoJP20kRsSv02vVb9rlicFThrSiilRWbXXHs
*/
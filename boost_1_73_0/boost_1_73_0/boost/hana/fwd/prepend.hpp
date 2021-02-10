/*!
@file
Forward declares `boost::hana::prepend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PREPEND_HPP
#define BOOST_HANA_FWD_PREPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Prepend an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and an element `x`, `prepend` returns
    //! a new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the left) with `xs`.
    //! In other words,
    //! @code
    //!     prepend(xs, x) == concat(lift<Xs>(x), xs)
    //! @endcode
    //!
    //! For sequences, this has the intuitive behavior of simply prepending
    //! an element to the beginning of the sequence, hence the name.
    //!
    //! > #### Rationale for not calling this `push_front`
    //! > While `push_front` is the de-facto name used in the standard library,
    //! > it also strongly suggests mutation of the underlying sequence, which
    //! > is not the case here. The author also finds that `push_front`
    //! > suggests too strongly the sole interpretation of putting an
    //! > element to the front of a sequence, whereas `prepend` is slightly
    //! > more nuanced and bears its name better for e.g. `hana::optional`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{prepend} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the right of the element.
    //!
    //! @param x
    //! An element to combine to the left of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/prepend.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto prepend = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct prepend_impl : prepend_impl<M, when<true>> { };

    struct prepend_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    constexpr prepend_t prepend{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PREPEND_HPP

/* prepend.hpp
/pnZPT/vn296ESKqSHkVombUSn2PdyyEyeUPMiFN5gIIdf9D+s6HW3npg6wjL35oCvWPrYX+QrtqQsZqqysgVlydnaJAlfuzRUf89J0TojEalA0uShxrN2ZocGU5BK7s3CIbVz6nzmgGbiywiHw+7q0y+Mpqh39KL0U/OT8/+dEcYNrLs+6rk4ve95tYon8RprLJRyouvJEuSotqkRMCrU0r9k8wCjqT9+TIMC5mOzNxa8dKZsyhX7Vr2TJsXHS5ci4fx3jiZT+26MFarMyIInhkh3wyQ8s2o0sE6o+38ckOOz5m8m/Hi3bYP5mxz57iPx+fLQkDVWf2Yja7zbsndFMJyO31ZxGCwcX5u86F+ab75jn+1dtoNVYoA+j2xAtJXfJPTcEUJ8dofMusvLjJUlc3ibuemvFNTmTyO2gPq/WdXMfh+qMpLGVNlNTWuCfsfFhVhY7N4+ZIFJIDCKLltFCsZP5lulXk/TypqSIBKcoIiqltf7q3Vwx3FEbJZZP03oSlw+Y35LK4/Vv55d+J9w6IxmZO4scigZqNkgfZug9xP0i9/uNZQQuzWxzs7fju0JS8TnwfJG5fSawq25o5S4ILkpsW3FxQ7WVQIx2U0AlZULoOkCgJLRDfdyuhi6ft3EuES8cse51waWFl
*/
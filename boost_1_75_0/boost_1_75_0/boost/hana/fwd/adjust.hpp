/*!
@file
Forward declares `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADJUST_HPP
#define BOOST_HANA_FWD_ADJUST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Apply a function on all the elements of a structure that compare
    //! equal to some value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`'s,
    //! the signature is
    //! \f$
    //!     \mathtt{adjust} : F(T) \times U \times (T \to T) \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to adjust with `f`.
    //!
    //! @param value
    //! An object that is compared with each element `x` of the structure.
    //! Elements of the structure that compare equal to `value` are adjusted
    //! with the `f` function.
    //!
    //! @param f
    //! A function called as `f(x)` on the element(s) of the structure that
    //! compare equal to `value`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adjust.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto adjust = [](auto&& xs, auto&& value, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct adjust_impl : adjust_impl<Xs, when<true>> { };

    struct adjust_t {
        template <typename Xs, typename Value, typename F>
        constexpr auto operator()(Xs&& xs, Value&& value, F&& f) const;
    };

    constexpr adjust_t adjust{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADJUST_HPP

/* adjust.hpp
00ciGJwPso4rkxbIE1Hawg2b3SiMsDZSW/Tmu6RtwrnY8x04qb0uts/H8ftP4iwooPBtH8NHTeS1J+Ej4V3loFPMZtBtTLseRc49LAq4kl7MS0mndjzjfxLr31+RXgwGJzvVN2nJTvVCLnUqXPxiLbnjX7j4xVehFIPFoVLMiLcuynTsMtsdCTdAtM+sQ+llGXb6nYgaFigHbrZHXWLzxREPDBdJW57UCOWWXwxU+hydHbSg2Wb/8MXFUriJnG42CL9rn8OHrxdBr6LbYhbcWn9V6LOcx35+hREFwZTnERwLKSFuOpcF6FpD5CwuCpG9RSH4dPkCuL+ptOs3n9AcIq9bplTBV54Se0iNzcdliQj1vYjqtEGL2xXI4VWdINXMQvT+OEBFj7Rkridz7pP5M2ow62zprYRtUMNipzjqWMAYRaPS/Wq4whdbjqKN7ZYvLsI7WyCOOTe1PtyD55nTYj8i7sYFM4HppfCzyAvE70vs0WQX+AHmf2E6Mf8DV2X+uo9/mPlvZNchu4sdS+oA9g4YgwXvp3D9z/6ZwvW7PxJcX5HK9Y1z/h+5PvNIguufuQLXd+qSXP/a3J5c7zxxZa6/8c2LSseFsfM2Vw/O/3ETFUezzo1ehecbEzz/hMLzv8rswfM64nmF04qlLU3nL+X5D3UJnv8mwfOXc3yx9OKV2P0/tP+O3buPCoa2VrxG083lLH8ikeI3SMct
*/
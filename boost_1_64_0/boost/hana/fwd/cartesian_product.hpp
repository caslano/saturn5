/*!
@file
Forward declares `boost::hana::cartesian_product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CARTESIAN_PRODUCT_HPP
#define BOOST_HANA_FWD_CARTESIAN_PRODUCT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Computes the cartesian product of a sequence of sequences.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence of sequences, `cartesian_product` returns a new
    //! sequence of sequences containing the cartesian product of the
    //! original sequences. For this method to finish, a finite number
    //! of finite sequences must be provided.
    //!
    //! @note
    //! All the sequences must have the same tag, and that tag must also match
    //! that of the top-level sequence.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S(T)`, the signature is
    //! \f[
    //!     \mathtt{cartesian\_product} : S(S(T)) \to S(S(T))
    //! \f]
    //!
    //! @param xs
    //! A sequence of sequences of which the cartesian product is computed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/cartesian_product.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto cartesian_product = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct cartesian_product_impl : cartesian_product_impl<S, when<true>> { };

    struct cartesian_product_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr cartesian_product_t cartesian_product{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CARTESIAN_PRODUCT_HPP

/* cartesian_product.hpp
ZuX5f3DpLCvwN4vbf8g8iV6730z9Q3ih2bCSIVUfuR0OhetTJpAUg2TlOYfo5C5gGet1s121YgOG8GKKjW02q1wmreuI0gIGfUfbqZ8r4edYHu6kTtgU6kliGxVQtC2N+qiBDoeQu+MpygtilQ02phUcuObHsEe3uPZETgl2pF3TQ858mroskh4u/VTr3AsPis7d3TbWaoSDwzKbvDX8U02llvNSwfZAXxY5TY32m6GZhPjNpZHr2BGqanr73bH5mv+CURhBk/886QdGdTbCIYEy9g1Y6+fEQhzK2RSSq4V4lJPxDvnX0WeSsKdaSoQi2J52jVW21FKfNAcb9S7Jx3J1VMUR7XfU+5MxFS1Q8VhkY8ikqnuSoL7hF5t4sfKLQ7w4+CVdvNhCpm5YT+n0zp/mVv7epo1sM49387Hp1y2fxejXbCZZyWTkQKqczSYydBCKzhOlT7RMbqUMeYQnFcScghT0e7rUHktxtpaCGNA0jzKdqJ4gYMftvlqzdwhNnNGc+D6N3/HM8IL0EPxH0B6KFxGFIlkRQQxiRk0DNaMpB3JGPAfoGec9Sn6nyJ8t8uc2d45PF/EZIj5TlJ8lys8T5Q9r/pr25cfaVxRbS1WKliAifeyVru15umt/c9R4nR5vB8sbO1+4JITHeEJsASHe3XgEIR78KQcRYYwnxDaVELfv0ghxskxuymA+fGwa2roA9cS//+nTxPfPOr2PeTPxfXun9198kvAeHV4N4JTPQEKF8u9EqZqh9YBOSnd+eiIUmcoFTDOPNGfUzzffEWHVntNDFv/kqJUPhqiy7TzldXGEM5Kj3hJ0xqvcvXkt+BrwQUpt75SvPMiJcbiLthGg2Sf4ZknblkPzzrf+kv/fd7kfMZW+gfshVf8LBtWTcLksQ5pBX2UoACCi4BC0UAfArQEwWQDQrftNZWqwVOQHNhh9lYS+LQb6KI/u6BKJaT555LODHVH4vcAaaYCn/93od4ZAepKIzOMCis1gf7X7K+S1JAAMRtMDp0pv66kfjUt9s5Ya2tXwBGh4qsPpy/EQWk45qbqc0DlEnUssNGVbjGzDVWyhn1CJVVxHU6I5LeU5bqIprqbvnOQ4qVzn8bkY3Lc4eeNx7Xe1QStvZYtlKM3F6ZctcjPOv2TCn0n+SL+1uKhge+XnkbTwAqMcyfmH+SO5PecLmDVXoDB5M03JQ9HAMClV75kN1DNPiJ6pfht1SYZr2a/zBay7zRLeeFEbGfwbDQGiX1mw9A0toO3GidWFBQbsrPvp5T1PO2tSVmi3QSxvikZR0qEU+4q7DXxW86LLjA72Pj4iiqxZetanKev5pMAotrinlHuUN3uJyTIvZlOF0BdEKNnB0ALvo39GVc2VFTkTyGXgryNyiv7cm85S0BP+mSOp9MT/LCyjuIHPfWRQiWTqph0WAvBoYqpEupNW2rjLo8jUFYav1mvjzhj2px5BnpYiG+XSsvoskuOarpOZ4pOZJcdRSjPHJ0uR0o+SzBKXTJqi9+adcQN73x5G+QoNc1a/NNfo+ALfn84zOsbgeyG+p+Prwtc/7z9Hh3H0j37+82/AWfLNEqV9gtITpxBJWgdXeHvEaFJHgXTNpzPZW4i+lSu56zvE0XHMJ9XFI0zo9qt0v4oYguwi0tBCcFGO9Y+QhA8U0ZmCflYmyiiyyl2m7HlF27Mt8JYqC0UZBQcqNxLF6s22EmWBFOVJ2O9EkpTmvZrcio7jjlZOfFjY0viHMzP/5PN43YECQh5iF7OYVUgm+5bQBXSTDxmrh6w4MoViI8ng6PErbdVG3K1MhvWJtGKCAZY5HwISb7kyifgvcnvzTS+JPI4PUSkre1VNV52kfhpvPiE=
*/
/*!
@file
Forward declares `boost::hana::div`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIV_HPP
#define BOOST_HANA_FWD_DIV_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Generalized integer division.
    //! @ingroup group-EuclideanRing
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `div` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `div` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `EuclideanRing`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! In that case, the `div` method is defined as
    //! @code
    //!     div(x, y) = div(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/div.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto div = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct div_impl : div_impl<T, U, when<true>> { };

    struct div_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr div_t div{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIV_HPP

/* div.hpp
8NVanuPzRZ7Z7Eti4gztsKbCQYciwpuQstmjUV3bVIjT4AoBV0ECA6SYXt617eTbFnRcWMRe6dGJeYTDxTGGUhMPv5PDbXw4qVTGw4EEiXM6T/1OVL9l9NUn95cnqpMbfhnScQA60Vf1UflihbHlVliwp7YLdNbzX4RgEqkAnil+A081j/Ljr/NMAzMyXOpj1Lr8zoQuf8inncL1R86JuKF4eBI3hbsfynlXMKrWIkR+XEXV/KWUQvr3QlWGl/nr9ppu+WuKj6SkV25b0RN/jV0dkjC7Ubsigd04pK7+zGEIRoK3kpOULxVpJJA9CQLRHMFsOd2DIVO2VurswzZVy4i/4BtG+fVs3xVR+fyFkZm+WlRgJRM1fIkVeO+rWvAVdNsbp+E5yuB88A6M87Mx8G6luUxLU6xIeSrLMF76k5mYpUt0roGbqC4xlNnuVcZ4da4BTMPzCSRNESStsZpRRkWQaxcT3xAdrSprfiLbZafyEX4Dz5TL2ERQCc3lfjwdlGKeA6lqQZL7+yo+vLCoW3ygeIQlpVe+F+gJH2iQqXL6DbXYNPEBlocS7g5xhBlJkv+xiTnwkhmkEGQIG7Uj/aE0uBeuxohl0JNntjisJY0zI7GgNciThjxhY88nl8K/py2S8G5jGR9k5wNJJehHo1SUEypQCfvELEK7KXnamB9QLVPxnp2NGz00rvdjU/RXqvznCp0f0+N1+c81qfyWRyg43GeUfvZFTpgrbUMOnyLVsDGrfBRFroI/ZwhcBK6LlMNOVCvVEzRCPgI3qPpLtqWU5chZHBqb5FNeF48TXgpttyFvcOci1TfOUyLilA3ssS6jL1RnMQS+yl4EoaC36xQvl8HJ7hxMoFM1KW8HrFRR8Cc1LGuV009BKUDtdpsy6gJxNARVudVm4bCVbRQgkvYwP9SoUuBgzyptcf1PzBUeGPC1kF31qYFVHbJxxdcKvof9Em9aWqS16lHLAzR4j9BBn8de1q78/GIVqYKkjM8ZfYrpPI2PHMnDvPv7SK2sWyQoxk4QvltakVpuVdOPEkrUoZYMX+hY/poLlCexivkg4YzgF3q5hXzBU9rHxVzIxeR1KUZ5dQ4iWjJuDL2WYd7aeszsn1kiHUEWN8k9FH8NA0rPgOuq7bg+mLdpoAPn2+c3U5Ps5TuqUAskd5uolmcXajq6pUDFvKZyo5tlJMpVn1c7n5hYXJdeY56GUzOFjm9CLRZ3Fbjdfhdx3geM6nrxrn8BA0IsNB8nDSjnBPJ26rJ/hulO/hCb5oC9xQ7W/MIaspK0aJvDjY2NR9+Qt7ceMstPtB6wjHliTGtwNDjkM9R5VD9cc0G1hLEAeHGXziBXwcUno0TRkeYjX+ZupAPEKhy+pLulHTy/GxdofTmyoui9q5t071V3jUzECLJZ20qmJD+u40/66PLZizE+HnGVTireROtVnwVCBUDOiBWSaFMwYm5l4TDV08j+Qt4Ck4Sz2Y0s0T5u5aYxYiMuLeQyHkeplF/5wSQh9HLg1MshreXIzczxW6Nkr9TiwcZ6JrH8v/+SuKaWAacZoSmGwACsXNLtnGElZ7CRUHcJ121Jqnu4VncLp55JdVfaqKNishMLIeEhxAhfrmZTuGMU9by8eep3D045+qbc1nrI1GTba96JcXT4M6T9XErJ2eJoCbocPF7mPzdZziuKaIMGR6xVYrxwqxhMeSWaWPRh7Z2LeLAoNHZWfIn4TOW4/NHtQXx9fuJ+I0cIc2SoeTLRmtKE9Q/2v9qwThsEL2zbjq9gh/18C3ZGFQ7Y7AYDD/F1w3xQ+RSSa+JdaBUGg1vJKJoLQoyAPPbFNBFBH+vSvZfIx0d9lfPswg1BLsxaEbU=
*/
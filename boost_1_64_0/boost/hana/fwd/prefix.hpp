/*!
@file
Forward declares `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PREFIX_HPP
#define BOOST_HANA_FWD_PREFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Inserts a value before each element of a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a value `z` called the prefix,
    //! `prefix` returns a new monadic structure. `prefix` satisfies
    //! @code
    //!     prefix(xs, z) == flatten(transform(xs, [](auto x) {
    //!         return concat(lift<M>(z), lift<M>(x));
    //!     }))
    //! @endcode
    //!
    //! For sequences, this simply corresponds to inserting the prefix before
    //! each element of the sequence. For example, given a sequence
    //! `[x1, ..., xn]`, `prefix` will return
    //! @code
    //!     [z, x1, z, x2, ..., z, xn]
    //! @endcode
    //! As explained above, this can be generalized to other MonadPlus models,
    //! with various levels of interest.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathrm{prefix} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure.
    //!
    //! @param pref
    //! A value (the prefix) to insert before each element of a monadic
    //! structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/prefix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto prefix = [](auto&& xs, auto&& pref) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct prefix_impl : prefix_impl<M, when<true>> { };

    struct prefix_t {
        template <typename Xs, typename Pref>
        constexpr auto operator()(Xs&& xs, Pref&& pref) const;
    };

    constexpr prefix_t prefix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PREFIX_HPP

/* prefix.hpp
yV0OkdYs3/UMRbpSW0j8/2WxwaUGbVsQM7WbLEckU9p5uasbRgQD4h/STifN8fURlYuU/0W6dvgb0tgODHBxd0Ebc+h41V2dPGIAb9W4s2Vntdm+YRq1b8yFevt6An/fTVIdxRR1Mfk/dbeGv3eXnwJ/H3HH8Fca+k8yyavB/g4NpQ4WiKbhRRmBQ8V7jMIeJDAQwPuNgggk4AhXmPX+w4b3/pFqC/w7Qvyrrm8T8c/rqiO+1uNrQHz+qfOJcXNJP9Ajh/NPlTQghXs8NRT6XC0va5aHFqAqcH55DSGCV7w0iWtOjMBUHKJ1pUri3n74CnUfqpg4bPrnFceRVp7cZSI3eHJGmA8ZQjZ0P+ZCbWW0GDcQkGnYy8Xqa+Va/NqqsLZFjZy8xHUjhiFvRoLKrfa4SoJxpe/pid/xl5e/r6wuqPztYaRuZY0bUgZ44RrVRTM2Yge44moaQrd4tELvn+RAvjL+6BY/PA9dDSHG1bIbaDyD56luGEkiy8oKsfYaxYn8Xns1ofXar+SKOHx6XAOpfWfpMqLWzuM/W9cPxbUuD9s4sleSUE38GuguPWZI43SdQlPIsn/ocgc+Z7AKwLrBcVaPorjRdZ0xFqt9S1DVta6YOj8daHo9ODD/ydWG/PRd1ACzL5/5t0rclLmKyvQIv5P3ozmkRFoXWKQ0aklO049wKV9aphzeRXf3tnaZrfqPNP/Kscvr7PVA0V9xRucR6nnEr0GTZabv4g1EDQol32c6TVN/AnxVo81rSJiVRweFEz2i6So5EMJ261XyLJnkb4VIPYJSiXD/o1HV+dw49lfm/7Bqz1qhbYghZcSm3ZMwjtwz106L8zj0nznrRYuog1JEV8wYj0usGcEDrm6CsxVCY0175Qq1ptkT1rRvj4lb01aNPpM1TafXK/lOxq0FOr3uBXodUiuy9L65DP11wVSFSVwxOw0BeJWLYvTa0ZJeJ6ksqA05B0yaH1vFLPMQWckEijF5N3RLlW5RZ58ZGNT3at1IqhuGg+ws5SL9wllnT3Z1KpslfpMXu9SYq11koEqZbzndf5zC1faKc0dx4/R5TqNR2ARb4pDNETWWW58cbNqT55GQ2CuuHKrUqDXsy0deaQiJSXtfH0icVF4ex5zYqrayABG0+71rYt6K3Npxo1IaehP6T5fqlbq7OL5S2rkqHfvl5fqHVNJFCUndHha6DBmuX41LB1vhJlVI8eEgSpfDDitSk1W513G5YyWwSAqrx3pERj+GiSXDjqYkFBBq+DqFAa38ePSw8yTuhE+gVXf1Pam7brlEkWhexR0eXl2HD4u1fSfNOaJkQgxUzR9+UvPHSThyqi3oLLGwAUBZTU5GV8roM7X+BHxE3/dkbQrS0nqVL8dkzTeEqoQZpBwMg0BWEzQCu6FuYmApqxDl5Rni1Cf0ZLpr5UEu6bA6C0zClJhF7XqzatjVkVWk7kyofMcctYMfSudnQOXi2Qz+3gvUjf0JwOSFcwxfkgmYXO6JZ7MzJUnK8YpPRqrcA6hTgKWvGqWX8eUu4v8u1rF02wVf4UjhVD+l/wFeQXIOOYV7bv7gxCfRKK2fNz+/pRRydGwboKwgncQ6SO3pEA2Dx02YAWX0dwfFXatkK1c7CeY9Y7mb7h9mjAJJ3pBLsmGz5KSRmtfAzmOxztfulc3/YJKcV3MZMbcDXkjwvPJfCkMl5Dr1Gc3gRv3FlErenpylxAo5UIQCafz2haqzu3nFFXJCqrtWNbluMUGq/8q10apuU8FYXhHHG1zcflVHNvCqqjlukj6P/h23q7TxCfsp7R5Zh79UtLqlUveRozPU+OYXbvEWHlCXEtgiZja91YBaky4ksUnYD4wJXOg=
*/
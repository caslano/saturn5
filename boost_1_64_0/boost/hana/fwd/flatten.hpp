/*!
@file
Forward declares `boost::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FLATTEN_HPP
#define BOOST_HANA_FWD_FLATTEN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Collapse two levels of monadic structure into a single level.
    //! @ingroup group-Monad
    //!
    //! Given a monadic value wrapped into two levels of monad, `flatten`
    //! removes one such level. An implementation of `flatten` must satisfy
    //! @code
    //!     flatten(xs) == chain(xs, id)
    //! @endcode
    //!
    //! For `Sequence`s, this simply takes a `Sequence` of `Sequence`s, and
    //! returns a (non-recursively) flattened `Sequence`.
    //!
    //!
    //! Signature
    //! ---------
    //! For a `Monad` `M`, the signature of `flatten` is
    //! @f$
    //!     \mathtt{flatten} : M(M(T)) \to M(T)
    //! @f$
    //!
    //! @param xs
    //! A value with two levels of monadic structure, which should be
    //! collapsed into a single level of structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/flatten.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto flatten = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct flatten_impl : flatten_impl<M, when<true>> { };

    struct flatten_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr flatten_t flatten{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FLATTEN_HPP

/* flatten.hpp
xTUOo1psHWn5ysRXT2QdXQMrwKf8jkey/YpEkBUCHxIlciuvzyR9Qa2QABYbe3XHVgow78vfBbG+KS2E8t/mNPId6QUvMm5WgJecGl1mkbKRXVcG5T21N42SQU0nUU1WWKIPc5luKQ9RauYpq2Zyj3YRKVsE5xmJKJYjVYsIV3GE7K7dhg/K7RoROV/NbctJua0TEdJFbt1BUc+74Nst0bcWV3pARPxdtbDDWZcQuE0EPqEGTvJK+yiHC7zSH+k92isdo/dZXsnxON7DvJKT3qm10qTHOeVGTukAERim2ZytYGK03iTwaV0e8WniRtJavAHwsjvTZ4I+tDvBQBJaN7LexDfpkDAKNbQ7VLHj61aSIgmaAmQb5LsvmBy/wGM+YHLMwfMpPCvw3IlnC56H8NyP52E82/AYjEQEGvqv++Fy8JD/8NvA0U/sI/uKD1fE7CuSh1s5i5SDZB9l+4rp6/q3r5i8P7CRxToiLPjnEqLj8IK/hdt0Z5FwYy2mgtNN3OoXWHwsSKcHqCWr9QBeRMlwHmJmurWIzGUVcRvm10ekJTSTpSewta2SQuJUc+v1PKFxW2xwO6raj01xAeb37ju3PDPST/iVCL/cKZcD5bAPmZ4pl2fDRF/kA9p7FWlS889j8guzU9RGZ/qMdayELa7JF6K57AmdtB628YiIZ7hFvPgWL6Qmu2NN9l2P9n6l8cO3l/WppfNR9/EbhOH9k8MzOPzr/YXX1oljbdFbRQdR1xW4cPzMbTFLuivkKgvRtausIK7IVSDb2eQqhwdmQuUqqGEDFU+uyvHZvGFXjjJV5E/2w1uroCrLVebGKeG+Ms0s8nnENpTf7k731CqLigVy1+yUXwX2GG5gIkjEo1y9hCdqnXL9J/mDbzB8CASV9ifenNhoJfiNVjCPHfKQ9fsDqS17AhndlpI9/jSxg/1BdPLA8z3aVEFyU2hKgQ+CjAaf2sDg71mMr9kD1gcTwTH9+c/Ig06KXwmXL+X5kyGX5eKVykEW6hUPuuWXAPnIXnmRZGvmYBaw/f+reaM4xaMP/xif0K6k13o2yw0FBL/l3taqAvQuiqihqlcu1qq+EFV3fGDVKdYnP6DqR6tF1UfHV126iqsO1a7NVJ0WP+bw4NaV+x0/1s2d6LYmuXN1dwjusq51IE/Eh9siCet9e8/0TLCKSL5d3oexpzb1lGVaA++q6GeKfHl2GHSkyAD1yU4q3xFJmi/+IHfYSjbVeTPBikxmHaqw4gwGkHW+FB1SnB8K2gwg5ozWYcBKnwQYcMe1MRjAUIIgCiBopgZB33BTTlJLEizJjMESzufyaz88LNHw5VqAgnaPfeaBEjTDa58LwEcHWhIMoTPsFURh/i45UrV7UGRt1L7+DnyJ9p4tppXUdx0qZEE96aBCF42nUrP9c+RUDkK7HNF9FGZFWNrdRtek4Z5SpB9RoyeX1ustRUSoQ6lCXVpWUvfUq1ddJENcJy5F42d/Wlfpi9Aeg941HHoJQplY9vFOvuKnaSFjYa142VLlEulkcKvZr6UZnuDWt12P7wxR12rl6zfFDHKf7csS3uW+JST/eo0myhYRBIfWYFl4tNfjI8kHcUgroJfyA68GfccpT2JKhF0VAHzFvvPicxuN3Citcm4l6zX0Xaou6i9dyanRjzQRZ+QgmwkCFiCTPF+eyMTFmbzYoGbycoUAD1FW/ubs/mnD/FO0/f6B8BzLNqKuZyCpafL0QnleMU5/RftjWSeET5LnlYrwAeE7VqeTDO6nwbg79l55Th4GDPsFmL3OcLlT9jiRVSq8w5fnyZ2dLqfK180b6ACs67/3Jeg3T1AnOoJKIhMa+7F65sBQS7+KA5PrS8Y=
*/
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
pQz848AcfY8P5OP451TCBC1j9NJ8xrfjeBTtWuIJpKXoLKel+CznueIsn9/Ks3x+q87y+aw+20Srnw76NMt4K6cjWKSFcC0X6SC6KkU61t2GjpWinj0nztU/RD17Q9Sz9843jU/pqotNdhPS/vZzcwBeZ+70lrRq2zfRuqg9pzW2/a1pXXeJ0/rmJU7rB5c4rTsucVrLL0mbzTeNT+l6t4S1D9TZreL4RE+DOH75TcZ/8jLX02dFPaU/wrf+Mh//nYByaj/uEm8/9RKXFbWN6nB7WVWi76Npze20Ko3bKdF9oAO3040dWrfTQN3PEdsE2u70Dq3b6dP1Le0zkKZ3tc1paqdr8h3TQzlNxtDb+w5ZaEvfceEmNJ07x+f4yrnWfUfRuSY9XBN6c9lSW9NfHEfsX3yeRovpQ381+Zldt8GxVsTxmpi+J/Yl/oSON+/r9wvTb9GG8He6yPF2v8hp63OR83/3Ra5jqotcx60XuV+4HynJfyxS/1yto1+yKZvP1fdKbnt+W4hW8rnrhryyk4zhvtCx5dxReWdAF/G6uCOfZ7ruKpZt6cjthq7DxLINHfl8hgXMW6DNCCLu3uc4P5HnOD9R5zg/WqTkE6xISW6x5zh/CUhpnU1CSsdjTEZKW+5UpPSObaZY7kJK70wvQkoEFIp6FEiH/88vt8wrPt/Ffs3l9kZkc7n9qx+XG8kkXc7lFiVvXW5ETyfx
*/
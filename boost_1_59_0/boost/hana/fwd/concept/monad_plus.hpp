/*!
@file
Forward declares `boost::hana::MonadPlus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_FWD_CONCEPT_MONAD_PLUS_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-concepts
    //! @defgroup group-MonadPlus MonadPlus
    //! The `MonadPlus` concept represents Monads with a monoidal structure.
    //!
    //! Intuitively, whereas a Monad can be seen as some kind of container
    //! or context, a MonadPlus can be seen as a container or a context that
    //! can be concatenated with other containers or contexts. There must
    //! also be an identity element for this combining operation. For example,
    //! a tuple is a MonadPlus, because tuples can be concatenated and the
    //! empty tuple would act as an identity for concatenation. How is this
    //! different from a Monad which is also a Monoid? The answer is that the
    //! monoidal structure on a MonadPlus must _not_ depend of the contents
    //! of the structure; it must not require the contents to be a Monoid
    //! in order to work.
    //!
    //! While sequences are not the only possible model for MonadPlus, the
    //! method names used here refer to the MonadPlus of sequences under
    //! concatenation. Several useful functions generalizing operations on
    //! sequences are included with this concept, like `append`, `prepend`
    //! and `filter`.
    //!
    //! @note
    //! This documentation does not go into much details about the nature
    //! of the MonadPlus concept. However, there is a nice Haskell-oriented
    //! [WikiBook][1] going into further details.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `concat` and `empty`
    //!
    //!
    //! Laws
    //! ----
    //! First, a MonadPlus is required to have a monoidal structure. Hence, it
    //! is no surprise that for any MonadPlus `M`, we require `M(T)` to be a
    //! valid monoid. However, we do not enforce that `M(T)` actually models
    //! the Monoid concept provided by Hana. Further, for all objects `a, b, c`
    //! of data type `M(T)`,
    //! @code
    //!     // identity
    //!     concat(empty<M(T)>(), a) == a
    //!     concat(a, empty<M(T)>()) == a
    //!
    //!     // associativity
    //!     concat(a, concat(b, c)) == concat(concat(a, b), c)
    //! @endcode
    //!
    //! Secondly, a MonadPlus is also required to obey the following laws,
    //! which represent the fact that `empty<M(T)>()` must be some kind of
    //! absorbing element for the `chain` operation. For all objects `a` of
    //! data type `M(T)` and functions @f$ f : T \to M(U) @f$,
    //! @code
    //!     chain(empty<M(T)>(), f)         == empty<M(U)>()
    //!     chain(a, always(empty<M(T)>())) == empty<M(U)>()
    //! @endcode
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! `Functor`, `Applicative` and `Monad`
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::optional`, `hana::tuple`
    //!
    //! [1]: https://en.wikibooks.org/wiki/Haskell/MonadPlus
    template <typename M>
    struct MonadPlus;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_MONAD_PLUS_HPP

/* monad_plus.hpp
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
*/
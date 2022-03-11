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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_MONAD_PLUS_HPP

/* monad_plus.hpp
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
*/
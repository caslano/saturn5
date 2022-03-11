/*!
@file
Forward declares `boost::hana::Monad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_MONAD_HPP
#define BOOST_HANA_FWD_CONCEPT_MONAD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Monad Monad
    //! The `Monad` concept represents `Applicative`s with the ability to
    //! flatten nested levels of structure.
    //!
    //! Historically, Monads are a construction coming from category theory,
    //! an abstract branch of mathematics. The functional programming
    //! community eventually discovered how Monads could be used to
    //! formalize several useful things like side effects, which led
    //! to the wide adoption of Monads in that community. However, even
    //! in a multi-paradigm language like C++, there are several constructs
    //! which turn out to be Monads, like `std::optional`, `std::vector` and
    //! others.
    //!
    //! Everybody tries to introduce `Monad`s with a different analogy, and
    //! most people fail. This is called the [Monad tutorial fallacy][1]. We
    //! will try to avoid this trap by not presenting a specific intuition,
    //! and we will instead present what monads are mathematically.
    //! For specific intuitions, we will let readers who are new to this
    //! concept read one of the many excellent tutorials available online.
    //! Understanding Monads might take time at first, but once you get it,
    //! a lot of patterns will become obvious Monads; this enlightening will
    //! be your reward for the hard work.
    //!
    //! There are different ways of defining a Monad; Haskell uses a function
    //! called `bind` (`>>=`) and another one called `return` (it has nothing
    //! to do with C++'s `return` statement). They then introduce relationships
    //! that must be satisfied for a type to be a Monad with those functions.
    //! Mathematicians sometimes use a function called `join` and another one
    //! called `unit`, or they also sometimes use other category theoretic
    //! constructions like functor adjunctions and the Kleisli category.
    //!
    //! This library uses a composite approach. First, we use the `flatten`
    //! function (equivalent to `join`) along with the `lift` function from
    //! `Applicative` (equivalent to `unit`) to introduce the notion of
    //! monadic function composition. We then write the properties that must
    //! be satisfied by a Monad using this monadic composition operator,
    //! because we feel it shows the link between Monads and Monoids more
    //! clearly than other approaches.
    //!
    //! Roughly speaking, we will say that a `Monad` is an `Applicative` which
    //! also defines a way to compose functions returning a monadic result,
    //! as opposed to only being able to compose functions returning a normal
    //! result. We will then ask for this composition to be associative and to
    //! have a neutral element, just like normal function composition. For
    //! usual composition, the neutral element is the identity function `id`.
    //! For monadic composition, the neutral element is the `lift` function
    //! defined by `Applicative`. This construction is made clearer in the
    //! laws below.
    //!
    //! @note
    //! Monads are known to be a big chunk to swallow. However, it is out of
    //! the scope of this documentation to provide a full-blown explanation
    //! of the concept. The [Typeclassopedia][2] is a nice Haskell-oriented
    //! resource where more information about Monads can be found.
    //!
    //!
    //! Minimal complete definitions
    //! ----------------------------
    //! First, a `Monad` must be both a `Functor` and an `Applicative`.
    //! Also, an implementation of `flatten` or `chain` satisfying the
    //! laws below for monadic composition must be provided.
    //!
    //! @note
    //! The `ap` method for `Applicatives` may be derived from the minimal
    //! complete definition of `Monad` and `Functor`; see below for more
    //! information.
    //!
    //!
    //! Laws
    //! ----
    //! To simplify writing the laws, we use the comparison between functions.
    //! For two functions `f` and `g`, we define
    //! @code
    //!     f == g  if and only if  f(x) == g(x) for all x
    //! @endcode
    //!
    //! With the usual composition of functions, we are given two functions
    //! @f$ f : A \to B @f$ and @f$ g : B \to C @f$, and we must produce a
    //! new function @f$ compose(g, f) : A \to C @f$. This composition of
    //! functions is associative, which means that
    //! @code
    //!     compose(h, compose(g, f)) == compose(compose(h, g), f)
    //! @endcode
    //!
    //! Also, this composition has an identity element, which is the identity
    //! function. This simply means that
    //! @code
    //!     compose(f, id) == compose(id, f) == f
    //! @endcode
    //!
    //! This is probably nothing new if you are reading the `Monad` laws.
    //! Now, we can observe that the above is equivalent to saying that
    //! functions with the composition operator form a `Monoid`, where the
    //! neutral element is the identity function.
    //!
    //! Given an `Applicative` `F`, what if we wanted to compose two functions
    //! @f$ f : A \to F(B) @f$ and @f$ g : B \to F(C) @f$? When the
    //! `Applicative` `F` is also a `Monad`, such functions taking normal
    //! values but returning monadic values are called _monadic functions_.
    //! To compose them, we obviously can't use normal function composition,
    //! since the domains and codomains of `f` and `g` do not match properly.
    //! Instead, we'll need a new operator -- let's call it `monadic_compose`:
    //! @f[
    //!     \mathtt{monadic\_compose} :
    //!         (B \to F(C)) \times (A \to F(B)) \to (A \to F(C))
    //! @f]
    //!
    //! How could we go about implementing this function? Well, since we know
    //! `F` is an `Applicative`, the only functions we have are `transform`
    //! (from `Functor`), and `lift` and `ap` (from `Applicative`). Hence,
    //! the only thing we can do at this point while respecting the signatures
    //! of `f` and `g` is to set (for `x` of type `A`)
    //! @code
    //!     monadic_compose(g, f)(x) = transform(f(x), g)
    //! @endcode
    //!
    //! Indeed, `f(x)` is of type `F(B)`, so we can map `g` (which takes `B`'s)
    //! on it. Doing so will leave us with a result of type `F(F(C))`, but what
    //! we wanted was a result of type `F(C)` to respect the signature of
    //! `monadic_compose`. If we had a joker of type @f$ F(F(C)) \to F(C) @f$,
    //! we could simply set
    //! @code
    //!     monadic_compose(g, f)(x) = joker(transform(f(x), g))
    //! @endcode
    //!
    //! and we would be happy. It turns out that `flatten` is precisely this
    //! joker. Now, we'll want our joker to satisfy some properties to make
    //! sure this composition is associative, just like our normal composition
    //! was. These properties are slightly cumbersome to specify, so we won't
    //! do it here. Also, we'll need some kind of neutral element for the
    //! composition. This neutral element can't be the usual identity function,
    //! because it does not have the right type: our neutral element needs to
    //! be a function of type @f$ X \to F(X) @f$ but the identity function has
    //! type @f$ X \to X @f$. It is now the right time to observe that `lift`
    //! from `Applicative` has exactly the right signature, and so we'll take
    //! this for our neutral element.
    //!
    //! We are now ready to formulate the `Monad` laws using this composition
    //! operator. For a `Monad` `M` and functions @f$ f : A \to M(B) @f$,
    //! @f$ g : B \to M(C) @f$ and @f$ h : C \to M(D) @f$, the following
    //! must be satisfied:
    //! @code
    //!     // associativity
    //!     monadic_compose(h, monadic_compose(g, f)) == monadic_compose(monadic_compose(h, g), f)
    //!
    //!     // right identity
    //!     monadic_compose(f, lift<M(A)>) == f
    //!
    //!     // left identity
    //!     monadic_compose(lift<M(B)>, f) == f
    //! @endcode
    //!
    //! which is to say that `M` along with monadic composition is a Monoid
    //! where the neutral element is `lift`.
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! 1. `Functor`
    //! 2. `Applicative` (free implementation of `ap`)\n
    //! When the minimal complete definition for `Monad` and `Functor` are
    //! both satisfied, it is possible to implement `ap` by setting
    //! @code
    //!     ap(fs, xs) = chain(fs, [](auto f) {
    //!         return transform(xs, f);
    //!     })
    //! @endcode
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::lazy`, `hana::optional`, `hana::tuple`
    //!
    //!
    //! [1]: https://byorgey.wordpress.com/2009/01/12/abstraction-intuition-and-the-monad-tutorial-fallacy/
    //! [2]: https://wiki.haskell.org/Typeclassopedia#Monad
    template <typename M>
    struct Monad;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_MONAD_HPP

/* monad.hpp
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
*/
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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_MONAD_HPP

/* monad.hpp
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
*/
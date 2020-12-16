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
qzjn+Ct6kU/6j8rnpIDNJ67oppJ09G9jUfX2jsrHpoEfh9B3Fxf8yJZYWNhGo1weiOjEM2mkNNmVAdrHVZ/+UV20HtDAjVy3LDRbeZDipVQ2WI+HS9ITgrwKxSSDiefB7cwKmwR/iGEp0GsQbefoql/3FT5gnTnDi6Xa3G9Khjm6ZVuYUViB6cMjQb3dUdr5TMUeVwbfeQrPwQo+xCs3qxHrFanAbyitiw/MXFM0mpcM/rJY8E8HGH3GCMHjKsceWRXGPdXTRLz8bQQa0Pyd7o7/dnWN/y5KiP/+c2f9W8lDnTTBpaPfSErV2U8eHjEPTefP7tQFE6u4kec6Z2M6eT6Ri27J7c31W5c3zB7K9Ilhp1HLX8Z/P+9If8vc9DcBleQTL+2nv617kk/xSTzAIfMFporlX9PS7WhdXvzJqQSqhv9O5+w6cHa3cUbD+O+dPcjHLrNrHL55fV9XmR2EnCZkUTS8Fe9Wlm2/AZKfjgeVfPqrukprED47DNs32+oqE8gnubvy2VBXaSOf8Z2Uz8qfKy2Y28izp+F5X12lnXwiFuVTjmgJiNbOJzpDXqRr+QcxwhBgkwEPY37VA0YjQO4ytFj+W+9R9o/B05bb0qtsbAXE49/SHwyWNdCDd1zT9ygVtNMDo/2Pf9vBydds+F+RBHx8krzVwv8ZQgIJ4hSsW5mAg8/qk84DvYekUi1hjnR5XIjJkVfr6rm9i5PVDQr94wHfF31fXhBwDG22YAel1B6N6gdKKgv9E8xRnHqUsN2qwp9en9pYeIIK77+60XCbCq+4vFEUqGlVFH/jKNhV+JTGw7NV+MzGS0ksj4oyv/EolqRYlMVNREmIRbm/iSg2FaVo9G9Azw73Ue3fqjzPimWePlefIvXZmekI510cDWWES2AY7iQ9eCjtvuT1gRKo9IAJhJ/aqIUzLuDHvUUfKyltZyiAfE09NeB/VXbg+xL1m+l0aHu/lSMvirh+PW5gEiJOT4yxNUfKE6jydQp4JOhBgWKA7pIYE3Df0MkCjQDai+qdahyEn9uqDD5IdrFMlsPJPktQyYyq2p9sqqqSiy1k66K31Cneoi6mSormeaKoRpkiWZb3yEok74+INcx53DD9pD3ItnoOD3/DOcgmIsee+PB8ibPeWJiOVWN1bdBY31u5xNjyOrI2YHzXGJXTThtONgjb4Fgt01RVNU3CVfsfl0jUpS5snicQ9YjLQQil4pPdMhtWsHqD8fXxIlPL64HyEHRZ/vK8Szw+LFzP+KIuGhjrT99NfNkK3s52tXQi5Efdz5BfGf/dt953D+M7jO9LqrdgJWYO71Mv/rD4b2YCzOG968W3xfRVFqKbmrD3mbrz5e3qdefg+YFuXPrABNG7naHxFTyzfPgluHWEamIk1dNVYNUlnUoNnKxXV/GP7Mf9gMTKafDncXEjesmmaN0R7hpweaCnHMnPl1SwyfC+hwjv0TDcqP+J2AurH7/PIeANazwcYTgJdhzvLMsqGOQvlWNlw0G9FngDNqJPQU3B7908/NdN8H8v4U+Mh59vawSCFNKIAU4mx6LKQgaNltPQAQNz+zq5X9Ew/tF6/D/Uix85uiy+f4UHzIcH7IKKk1M5Kj5lVAzrHoGbJMo2MT5FKY0eS9eNYH8rehZFjdhFp08bLEMag7/hmAbwT4vBtxjwOxD8GPTNdUzMmqUnOIy3xf8nVcHgjMH7NaEHvUzmH3T5K4Ykg23vJMdUVStGE49OUq1g4S+tbJp+TZaGe7s1JGN/skpdeTpP0SY63KPleSKsf0s0bUxXomkH2jVN08buMtG092oPl6ZRT6qysBQo2yZfdvlKkS+nfLnkyy1fafLVQ756y1cf+eo=
*/
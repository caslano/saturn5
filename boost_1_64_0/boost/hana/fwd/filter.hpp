/*!
@file
Forward declares `boost::hana::filter`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FILTER_HPP
#define BOOST_HANA_FWD_FILTER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Filter a monadic structure using a custom predicate.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure and a predicate, `filter` returns a new
    //! monadic structure containing only those elements that satisfy the
    //! predicate. This is a generalization of the usual `filter` function
    //! for sequences; it works for any MonadPlus. Intuitively, `filter` is
    //! somewhat equivalent to:
    //! @code
    //!     filter(xs, pred) == flatten(transform(xs, [](auto x) {
    //!         return pred(x) ? lift<Xs>(x) : empty<Xs>();
    //!     })
    //! @endcode
    //! In other words, we basically turn a monadic structure containing
    //! `[x1, ..., xn]` into a monadic structure containing
    //! @code
    //!     [
    //!         pred(x1) ? [x1] : [],
    //!         pred(x2) ? [x2] : [],
    //!         ...
    //!         pred(xn) ? [xn] : []
    //!     ]
    //! @endcode
    //! and we then `flatten` that.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `MonadPlus` `M` and an `IntegralConstant` `Bool` holding a
    //! value of type `bool`, the signature is
    //! @f$ \mathtt{filter} : M(T) \times (T \to \mathtt{Bool}) \to M(T) @f$.
    //!
    //! @param xs
    //! The monadic structure to filter.
    //!
    //! @param pred
    //! A function called as `pred(x)` for each element `x` in the monadic
    //! structure and returning whether that element should be __kept__ in
    //! the resulting structure. In the current version of the library, the
    //! predicate has to return an `IntegralConstant` holding a value
    //! convertible to a `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/filter.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto filter = [](auto&& xs, auto&& pred) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct filter_impl : filter_impl<M, when<true>> { };

    struct filter_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr filter_t filter{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FILTER_HPP

/* filter.hpp
+ySye5eIFYizMyHLFBd5lxy+eWh5/mGqITnJQFFRT9tTmKjy071/6XjD3Gq5w9ye37fxNgkrRj6yoaJ4kYtp3icy17yA6FZ82CuflpGYMgm9n2kPkcpZvg60s8K2yBCUoP9vG88pU2A8hmEc59/7Z3kn5W+7w7w7vyOQxbfhDhPejjNMkJGd7l0kV6LG1utyaOOtXJfDGypsbrmD8akSpFpzD6WBfbHWZVF7JXV1HtUt1Gam2mCS7awodhvsLUFUhPm7u1raV1lxYJhFNp7oWg7xm9qub2xs7O3qOGKS93R0jTHvIaEgitJqCaPwfRs/z4WTcE9FZun0MD4wxbNDRzLXPBE3px56SMwpMnV/Bp0D0BfOKYUUHcSi/YgFSnTLbrxzoLjrIrGgycf+Dc2lrnJMWGd+BzcgLHwCZ7QBuYnmb5fvZLd5X3caffJc2GqgNDsBBNTFTnUv2o1VNXOP/GzvS06jveLZHhFEK84qH/Z/GmrUFhKlhDSVuAnv0h6vcuz9aFQ9M+2Gdfk5BDcEHyPI9tV9hYnx98bi303xW3qaX+4ej9jjGpm+5stNjL8lFn+xFl+tyuikqtwUizoVUYn+gplSiCmD5fV4hWVRUvzyWPxhevzmfTwzm9PVPrD6F/rGJ6YbEkv3/FGBZaKciaL+VFoeleZOKu25Pj3VfXoqLi3TEPxEo7bek/trS1+s/SJZJhWRibS/4UG3t9CQqoPZuy/0em5oV2VS2d5YJk5kgnQ2w9oC38WJsS7VYgUKG7R5avm+mKe+/MS4KbEc9x/hamWjDyY0bqbKZVP7S5Pb3xtrv5YC7W/pWeVMHvMHYlEDRwhNN658GfVZqR7DUa0bHhTVAp36P5ze+f/fIPhQBeFD0+6Px4dIEnZW0W4A2QU02+By1+LDyvZRr8IX7dNLWtqJNOwGpPMQDYpNCdIsCqu38cIk7NfTURaY1rK/edSaVMgdSMuzZPzvPUhEREKJQvvBx+4+r6dDYETZjBHZezosgq1ReQAZZVMS7HTLejqsMC8dtT5+ZSu2dirOXrEzFHU87saOIHacHADgK+HCKm2ztlKEDgjIKHzi9ssn5tUqN996PMoGqQ9stF20YVZxsWvodtpNz1nzElpTgA975QlCpEPRc+yhVmHguLC13ig/u7OitNiQ/8LGVBdLRLwnd5Y8Y5/dgXB//i5YiUf9sZfQJ0H77UX7858mfM4+81lEWdPT4fAPLdlun72PbsdhC1oADPNw76vrfocd4TAA9AUx+JyJJ6e2Tom+py9UMrZBwPk1sbD9I91x8V6IxdspdtecjYb1sNrfuNn+eHt8zB/GYm5RY5aF1eiB5wC4cg3Bsb7CuBSrtRT+pbQvVFOTAFgOgt3ixLkZoKi0aG58EZfrCaa0RJtfAwAaldCocXr4KII8f9DRe7IkDdjz7v0EeyoicLqFUAs8X1Y9lSr5PxsgsT32akxRiMMSn9JLF1hhlT20J8qX96Nyp72a1Pn7ITrFNFdFfhE04/xXMGtBL1xpAZ0mteggu6Irz3yUKDZge8l78p8sed8+a598hLa+3oOE4jiNMl3RrEBcsE0nEr6ANJaS3rXjfLlMkXLSo3z1XX1WkL1gSnoFpXSBsfo0BEYmqakKZd7qDe64tPORNgraqBjSmZTWRWlxWTmwC3W9mE6kavpzfbl1lEhPPFor2O9whSLGlS/Eznp8GD0tR77YT6fnz/0GHxdS6LiANglSG5kk1k9dOOYwms8hr1icA5HtxXkeWD6dAtrjMPwMOkzcbCxL1k+Zx/yfr8fDWydfGppEPAWfgbd15YlVqpLB0NFooNGtPAW3oB5n1rfOiNJacWJZ7GCOSl5EiiI=
*/
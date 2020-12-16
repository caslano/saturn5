/*!
@file
Forward declares `boost::hana::Product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_PRODUCT_HPP
#define BOOST_HANA_FWD_CONCEPT_PRODUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Product Product
    //! Represents types that are generic containers of two elements.
    //!
    //! This concept basically represents types that are like `std::pair`.
    //! The motivation for making such a precise concept is similar to the
    //! motivation behind the `Sequence` concept; there are many different
    //! implementations of `std::pair` in different libraries, and we would
    //! like to manipulate any of them generically.
    //!
    //! Since a `Product` is basically a pair, it is unsurprising that the
    //! operations provided by this concept are getting the first and second
    //! element of a pair, creating a pair from two elements and other
    //! simmilar operations.
    //!
    //! @note
    //! Mathematically, this concept represents types that are category
    //! theoretical [products][1]. This is also where the name comes
    //! from.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `first`, `second` and `make`
    //!
    //! `first` and `second` must obviously return the first and the second
    //! element of the pair, respectively. `make` must take two arguments `x`
    //! and `y` representing the first and the second element of the pair,
    //! and return a pair `p` such that `first(p) == x` and `second(p) == y`.
    //! @include example/product/make.cpp
    //!
    //!
    //! Laws
    //! ----
    //! For a model `P` of `Product`, the following laws must be satisfied.
    //! For every data types `X` and `Y`, there must be a unique function
    //! @f$ \mathtt{make} : X \times Y \to P @f$ such that for every `x`, `y`,
    //! @code
    //!     x == first(make<P>(x, y))
    //!     y == second(make<P>(x, y))
    //! @endcode
    //!
    //! @note
    //! This law is less general than the universal property typically used to
    //! define category theoretical products, but it is vastly enough for what
    //! we need.
    //!
    //! This is basically saying that a `Product` must be the most general
    //! object able to contain a pair of objects `(P1, P2)`, but nothing
    //! more. Since the categorical product is defined by a universal
    //! property, all the models of this concept are isomorphic, and
    //! the isomorphism is unique. In other words, there is one and only
    //! one way to convert one `Product` to another.
    //!
    //! Another property that must be satisfied by `first` and `second` is
    //! that of @ref move-independence, which ensures that we can optimally
    //! decompose a `Product` into its two members without making redundant
    //! copies.
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! 1. `Comparable` (free model)\n
    //! Two products `x` and `y` are equal iff they are equal element-wise,
    //! by comparing the first element before the second element.
    //! @include example/product/comparable.cpp
    //!
    //! 2. `Orderable` (free model)\n
    //! Products are ordered using a lexicographical ordering as-if they
    //! were 2-element tuples.
    //!
    //! 3. `Foldable` (free model)\n
    //! Folding a `Product` `p` is equivalent to folding a list containing
    //! `first(p)` and `second(p)`, in that order.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::pair`
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Product_(category_theory)
    template <typename P>
    struct Product;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_PRODUCT_HPP

/* product.hpp
ha0ovDJwib/7d6A0V/nXSUqz8G9KGKfgmPlz/2fEgg7d2HBjW803T6FQRNGd2kVkp7Z1ZsVYisoWW+mQRns4XOU+Ov+UlMfngb73FgYsTOUDuNzzXVLRdWbiTu6SAm2YVOqP9nkBPVob0h3K+zQTIILmSdHW44Af3ZLD+2XG+b0MQMraEDrGR3PMqGiHMVAjlNvzjqFZ+2Y+BlU3HScNoPE19ggNAkt+Wt1Lp+jlU3J4u4j8UQaxXZv6d2bT5CbymdE07+Qczy0hWyXH/7pO/6HEpmy6KZ7taGyX8VkU/2I/Dt2cxU1TBsmXNKtH1wYkRXM8Woqc+O16sg4bDfrz6wib1B99FVwtBIvv65rBgzTS9w/2RIuCnIwMGEb2SzqjCWnpBoER0JUd6aTnmJX0iQVb6wyF4FdaeJSG6YXM7nTOLsWcnVtm5zRnt+pZzq6FFrAOBd/aAL7vsODH+M3uDfjN+PH21hNqvDWs//PAX/NBSm0oYZrv9TGuLuAKM6JyMNVhMPVcjLzYimO0zzOoG0QvVMY15ZJ6MzMxtrysH2Z+gFsUDtkIErdtu3mSMvB56nOJjys822aRNojZvLnPC1sXV8hlBqovWLDY5xV2sL6kQKwJINYbWBWAakTfBab9ye7jSGOMOx3dTOPbqY1IyVoXaj8S5mnjRniqN08cBExpJ+PesVwMMvIZOT0y1Da2JaWKPdUrAcn8fVlNI/TVfQj6eoF/PEay/1Ya0y/IwXzqh3UtsT/H7S+ojv+6vmH7K/rj1n1V/Z/+GSvAb46NR/ehxuPiSejAnNHtT+nj8Zf3jng8upsfj+bsTn7qyMaLW46Xw8zf2iD/FU8eTv6x9sj6c2PtIcM2fs3jwWifGIUNWP1fU4zkdQ1Tq/h8pWLXgAVx70S38fhrJwNZTrb3CUa2skmRn0888Lbe6mdhv42vawq6DVg+E6wnJCyfaP9urJ03H9p+s17/utixafytjeDf71D4c/1y1O2PNFq/HOaviavf/LRDjr+7afzR0s//ohx/j/6l5eOvlvIsfLXp8ZemfBX920njz7UpNv7SDjX+nNehjjijDo/r7XLj5iMef2nNjz9zdiseO5z+fyj41gbw8w4Lfqx/pTU9HzLcl1Y01h4yLL86fvylmMffjxQj8kpz4y9Fjb8PuP9OmYLCcLIb/nzI8XfCm/HjD7DcBiyfCVZPCcsnbn37SMZfisShafytjeD/wqMtGX8cdfRDjdYvh4kv4+s31Vy/eyjGqS83V7+pqn63MX5brgd+nKzTo4es3/Ub4+sXsNwGLJ8J1tuP6PV75qYjqd9UiUPT+Fsbwf/SR1pSvxx13/JG65fD5n8RT9/SD0Hfhvk/luu3CkncNm1pdv22n/K4+cWm6Vl6PXq2YzvRs/yqGD1LPxQ9Gx9EnXBGQx7W2+HPbx4xPUtvnp6Zs9u64nDozaHgWxvAn35Y8GP9Kb1pesZwa5Y1zd8XfWTw9+mHx9+n1+PvO605TP6ecdvzafx4d5nHu2U4TexrmhvvLjXeU7+n8QJzn06Z7NSHDjne33stfrwDltuA5TPB+uRBvZ/lbjyS8e6SODSNv7UR/K95sCXjnaMedX9jNSTD7vx7fP3azfVroxgfrmqufu2qfl2MX1ox8ONkbyw/ZP1OrYyvX8ByG7B8JlizJCyf+PuGI6lfXSGrafytjeCfvLwl9ctRH7u30frlsL679PpV+uS40aaw/Dmilq+SwKYuyRp0+/fC5Z/5MxkyqRDHVsgdlzyKZJEbL+ENdBdf6F3/PhXTK3a/yvFaqq3MwnCi5CLns6blZ9dBEuLzb0rQcwmMpP0DD4Xc+aFpl4P0672Z721IshRkbi8=
*/
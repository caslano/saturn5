/*!
@file
Defines `boost::hana::MonadPlus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

#include <boost/hana/fwd/concept/monad_plus.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct MonadPlus
        : hana::integral_constant<bool,
            !is_default<concat_impl<typename tag_of<M>::type>>::value &&
            !is_default<empty_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

/* monad_plus.hpp
wSz8rwU83L0VD/em3it7I1T7Ixu6cz8ar1f3UB1qftyL5IP/ul3uTcLFKzGc0a0fsSicxXfuymPwfe5PvCDypsyN2NSLJit/DD/8gMW3Hpv5c4+1ev0Pne6bBru79Se32Mh9uGbRbbieT9mt+8ljK2/i+Z94G0t3FbNwBtWh8akfxdDgOvbDYA/69ljsrRYRtoHdu/MoZO4n15+7Y+jIjdltHC+jl/v7k/VqDhjcn4aTaH8iR713Gy8Im9jABwBi4d6zcBmzOGTryGswLNlgi3Dqz/BfmBR4uFyPARe3jQQa6CqY7ocrFnnzObYF9Xwv4mB7bCjQ08BibAkQ+zH+E4VBhF3d3YYLoyDgEVuZrVcBdAR4gELTENDcYOtg6q2oMI1cdiFwSgjey5uaBN4pCwMAhm03h6wz3GZjN/KjBnvXGV30rkfsXXMwaHZHH1jvnDW7H7Cxt53uGZCfD52tmPd5ufIi6HzF/MVy7ntT0ee3++xvbe3TKIbhejURlDODDt05rJDJrRsE3nw3WnoTf+ZPAOFT/hqRMboc7g+Hl2zu3nurPdYN6TU2BmNnn+J5tDeR9OZ9gvFMsFGoDHOODcDf2TqYIJFFODCA5W9+MJmvoY9tpCQn8uL1cu92G1/Mpt6MXQ/bzrB10ex2
*/
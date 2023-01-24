/*!
@file
Defines `boost::hana::Monad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_HPP
#define BOOST_HANA_CONCEPT_MONAD_HPP

#include <boost/hana/fwd/concept/monad.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/flatten.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monad
        : hana::integral_constant<bool,
            !is_default<flatten_impl<typename tag_of<M>::type>>::value ||
            !is_default<chain_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_HPP

/* monad.hpp
0pj6V3cJAN6qCMBTug6RbRKmasc+wxsC37HiLwjYGygyZDK5XkMd2sjyflh1pCqOdvm2Y5CnA/46Dcptx5Q7OvQKoUudVjKuf7GZV2EwX2iK0OwICfw1mfFtIImxUisyO3gxsG07Leb0wnALF/Wq2nlazElQwkU9JSVIgLTuMW6NOpEKAMkwoJjWKPQUHKZGSw5xjl3oQut8wIoI0/NEKofq8B0D6q0D4Y5IlxeCSL1GJZVAkUIwe8wHjGtG/wES1nykVCJPlju+RRzmmteoCwhkaUjJ0ipDWi6BdA/g6vQyi/0Au+FLVOXc4Y2J4Y1WHhFiIy0HDCfdLrVMZ+3IuJVRLAeXAvPTlGVmNncEMuE0nHOJs7M0vkyYtS5NGoVcOpEnQN49jGeTG8zBhKwe3wh/vllF35NhwRNqnlkRgn9n2xgnuULXALYl32IvsLI3vqCpl1pW7hsNH5pz0rDH0IJ7e9DrhZFjhYmVrol05a2gW2pILu2iSUWkb04zoJHBgp6Lv0X/VIP+n98x4PQgIbI1FI4/BTob++LWFHVtargDSlulkSyGDBwgPcXpdFIHxLiv/m2MgR8bFEJlC/Saf5UOte8Uu1Vfmk29Pi1RvT/Nqjaoh0xNWYMbLcC/H3gc56HTqeID74EkUn26Clq54QLx9amkbIkPPIy62HFk2q9PRR1E2DDs1HOgI1rLVjeqzfam3wMfNUijohk6
*/
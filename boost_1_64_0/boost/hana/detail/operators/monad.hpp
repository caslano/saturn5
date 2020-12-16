/*!
@file
Defines operators for Monads.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP
#define BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct monad_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename Xs, typename F, typename = typename std::enable_if<
            detail::monad_operators<typename hana::tag_of<Xs>::type>::value
        >::type>
        constexpr auto operator|(Xs&& xs, F&& f)
        { return hana::chain(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

/* monad.hpp
vKs/h+97vAd4Uv/06cPYWb2P+rB63tu/b6nTsdl36a8O3PX/oNKzFytd7IeVDU3IxuCjSX1QTuELUunTPy5oQedOuy6JA7kSx+Bj2F+ybJ9WZfsMcT8RwP2cwv08cT8SwP2Cwv2i0r3XKFuC60U9xunPRLfrDYKG0dONFAq7VdD4qmpX5+dRvqX5dZbrBeX+DVbZzrRnUuMA7fxNpefOKP8e2p/Nd1T/xf6fCpXdDOh+V+A5+6xStoH0X3KzqBvHq7KFgfxGjbs3qjL/iP31LfzXtjA/CdjC/JT47w/g3xLAv5X43w6Mh9vUeLiduN8L4P5S4f6KuFsCtjO/Ubh3EPc5AdzfKtzfMXwObdE6StR7vaQ1GCjj3apt70FY2uphXKXzVn4u/uTt18K2Jlessf2s7dfuU/PIjTv8j+nej3iOd+rvJb9L7Aom+Y0ofvegsiEI2Rr9HTg10ncEDqptO7vbKaSN7JlcwHkfZqu4H/TPNTbl4PDw2RMjwpmEAlqbOL1uSR9c8uFKBeM6NasqsU+fzd9sE9/uUZXwY1aVbpMChGFzATqJjWIh6Xh/WTIN4EVV4j0U9Um+Mp/pwO9cOk8TZU3ZdyxCWPLImgCPXMw0KI+nJ+VDy8z79TPye5n2rzEn8JZvgdL1z1V6+cKADnteQO9bFNBrFwd0wfOV33L6V810U66+0IStlgTxU/nATGToi5WercTpBikHLHW2nlXTkwPKObVIrBcIx/22vCrtIziqtvZLtez7bbRfWhrx/gLHSDn7eynxKhCWfEfbuK0W42tpYTrtmiqbRxX+az9yncuVXSVx1xH3MzPy3T9dn71TvCuifNrOU2OwSPnALZY2KuzTBezTh02zT9k+3GeIPRdqtaEq7S/sdMFXgRPc8x2HNJcVzqQd0z5b5wR8thYof7BzOVcAEb6P9fzw/o93nizsEYpEm8u5GUswSX9+4E33BYRJef1CYeui39aGbqtDzFP63e+CTQrnKmGdLZi+YBbAFXMW3mlrO3w9ljjcpkRnWkpbBmjaOQYTv7UN0ocO0lmIwZE+dDJtzYStUHrtlQEbrrKAD9xyvs3GMG2GGjvaaEO0KuDzf7XvS897/fsB4Mhxudeod5KqAvy6WvnoXRuwm1oXeON7fYpnH9V/HtV/HtV/zkT/eTdgel90D2B6v3MvYHpf9EfA5Pr4J4T1uvpnwOSaeR/Cep39yzy/Lra6dbGF6+Ijpr0uJjrPU+YhLN7afJfwMTkHsFklyfuC8q3NR1d5m2jpHxL4GndutEXseQxM+4g8wdES8bertxr3lVhaJ4k9dpHPT/ldVfRACzQ1rqV3apU/fwHX1mGtt63X+IXRY1T+0icmfsf5P7ZKygzylBNt+DieW0x4NnUh7n7U3bSXr41seDPD9VX0pz3XhvdV2HCZwi9huJH4Iyq8WYVLZqXTFzH+TMZfgrA8p5yB8Mzevs0017Z3eh3xHAvraRf7IL03mhtYqwuTd3MiE55nwx1yD4RwnQsX23BTZ22z32PNT2wEz2yr64zk27ctD2FOOV/n1bPT4Quj9NtT22aJeLa9jH/a7HT4rQXp8K8L0+FHFafDi5akw79bmw4vU+WpjVT5VXl0+SPGT7gwyufuhQMW3wLgb0RZHeVT0Y5F1Au5u7xZwNxfUcFo34lGlepEBQxS9yPzA50kv7r4DkffnsHhRIfRG9Ptz40NDg/ti/VGhUauUbjHlCG5dTfeuy++aNeVgtDvfV+Vr7u/298f0z17DPkg/7mx781cUgfgNmQ6s4g35bc/bdlF2+F/qi53i7rsj2mNWo0y6zIe40BfM9Qf51tDWf6AyPdPUW9uTLZdEvR3cE1es1Q=
*/
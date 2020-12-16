/*!
@file
Forward declares `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_EQUAL_HPP
#define BOOST_HANA_FWD_LESS_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less_equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_equal_impl : less_equal_impl<T, U, when<true>> { };

    struct less_equal_t : detail::nested_than<less_equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_equal_t less_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_EQUAL_HPP

/* less_equal.hpp
fLMN1Y/tGTA/O11wy08v1Tx/glILsN3+te6lg00rCpK2oX0+PqK1NT6/EC+F8SvS8bGPxr9dGM8TsWQvHH8XMqWECQ6MKbrdMTJVRPMK8dXljpHeDnHo6113jJC+iKIje1Qo2VT590Kt+O5V8xfvUNYSF8RW90xkfdo7RbuEh/2Du+5ze7S73YXtsFfYMM+9ZZO7sBmv5E6WQwjsHuy9GzYN93ncnpl3ewBp3y9iKQWUckCzezBeYiud/rfqbvd31o8UOcJ7F8wrhVMU3+XbMxIbFt9z+jDhHFN8V5kfG8C6l8h6AcF+cUWBiBT4do183/esHilAFAAYni8i+SY8n+BG/DwRyTPheQTPU/BcEck14bkEz1VwqP68JtxLcK+Ce0TEY8I9BPcouEtEXCbcRXCXgjtFxGnCnQR3KrgG1aIJ1wAHwCecVWKYGOBbDeOidjSc5BFjnIQ4r8XkqMZfAH/j8JePPyf+ui7RPJvx14S/O/G35j/oZ/D/EF5j2fDWjLB4bX9CuzABJETgr3c2nANTsBnwCmtID3EUUwnq6ECSmMoUNiBrHqINw/fcTGb0OfC+7KRb5uphxJXoyWpsaigSErdiTRVBp7jKJRyxpEfPBq3EmOjzXbhHuvHNRdt48YIfQMpYhyMm7dFh9C8H/2o9YpIT9FpMUrbPejYiVekwZSt3zdLLXBBRos7ALKCsn5TJJC6HLm2km3CSuys8znBfNic6XF70akbwO7y13DMAoakxckIGXJt3EPfjYvs9LxTu2UhC5IFSYwe4Y5u5LxgUll/hD20uigbpObpLw016MluUe+7Mqi260wkC8XuzeOwUncg0Nbj6/j4gVxsTDUphjw6tXpchJ7taDXJyjA3SWWUprZd75iaPsN/2jAQOT5r8J3GSv3xqygmeJFhMvK5Rr1l4baNXHBP9wOEu7beBPg7F307QoCZtYJ6ktp+wC2ZJzXA0d9VCBwAiwYbaG9ilzJ5+4wNaQ6ew7W8Ori3bJOGpKPmR/DRI0AQXUyDVHpwtsjUcI2xwHxM9gCXm+LGFmh2XENpj4+y1rthCl+1AxvnA9oB74DT9hR3c9gBw20PHz9BqPeBP+x9FeqofiDACTX58xEtH4scf2PHR/Pg17Ufgx4lna3Avu/bbaWLILwRD/t7HYshHDtyPIb/tYIbcfz8x5LNyjo4hN+xf3I9MSoOF/EjOfMsn5sw7tvzzOPPDzmfM5fD+sxhLnA59ME+KxTUkrIc1+e4LfZlN3GVHF3n2D8e9y7BuNnV0bzg5S65/4YgM6QG//SbRpSAL5n2yB06g8euNCWROnkNlb8nX4FYMudiTIktoS+6y2bAr+QweEBQNgYohsb2f+5FrbW9AC9mU60gkE9LTF+QB6C5b2majyM6+IU6EGB8AOxJHbiKtb1X+SFX+IJSfKZyKzpSrSqUozkyRZoHJI/ffqG2H778P1mb6j4lI8rD1Pc8GG/S67MdIGp86+7yBJ/FXExGewvNsLv66ll0u4lQxf11OX67zbBq+Tn4soExznTE4aHeIRNIwRAnU9Ye8e2qC0M5H6kNwMynth3AzaZJmKHQKOGqEc0aLX1aT9MLY0x2TiHEYf5m26Mx4vR2E7bJ7TMLWj31jgFLD0ty9TAyy5KutdbsgwRQ4ox534coG9z2b5+h2nqofQyFiymMHTFADEgP5psZq0UGExqNOuNLl2WneNHuI/mWtYzh+5Q6cNB7mbxar3dPaRAu8Tx5DROz24vTxHrVNXjA81jOiT/AaCi5VwZ6Dg9souEQFeylvBLunbRCr9aFE+ja9pn+2EqFHtzD5Z9037bTXQSOeyiH5aegVs6uzsLfqjx5xGVtd3Uk=
*/
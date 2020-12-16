/*!
@file
Defines `boost::hana::detail::has_duplicates`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_HAS_DUPLICATES_HPP
#define BOOST_HANA_DETAIL_HAS_DUPLICATES_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/equal.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename T, typename ...U>
    constexpr std::size_t pack_count() {
        std::size_t c = 0;
        std::size_t expand[] = {0, // avoid empty array
            (decltype(hana::equal(std::declval<T>(), std::declval<U>()))::value
                ? ++c
                : c)...
        };
        (void)expand;

        return c;
    }

    //! @ingroup group-details
    //! Returns whether any of the `T`s are duplicate w.r.t. `hana::equal`.
    //!
    //! In particular, this does not check whether all of the `T`s are unique
    //! as _types_, but rather whether they are unique when compared as
    //! `hana::equal(std::declval<T>(), std::declval<U>())`. This assumes
    //! the comparison to return an `IntegralConstant` that can be explicitly
    //! converted to `bool`.
    //!
    //! @note
    //! Since this utility is mostly used in assertions to check that there
    //! are no duplicates in a sequence, we expect it to return `false` most
    //! of the time (otherwise we will assert). Hence, this implementation is
    //! biased towards the fact that we __will__ have to compare every pair of
    //! elements in most cases, and it does not try to be lazy.
    //!
    //! @todo
    //! This implementation is O(n^2). We could do it in O(n), but that would
    //! require a more elaborate setup including storage with O(1) lookup
    //! (which could be based on a compile-time hash). If we implement such
    //! storage for associative sequences, we could use it to optimize this.
    template <typename ...T>
    struct has_duplicates {
        static constexpr bool value =
            sizeof...(T) > 0 &&
            !detail::fast_and<(detail::pack_count<T, T...>() == 1)...>::value
        ;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_HAS_DUPLICATES_HPP

/* has_duplicates.hpp
SRrAthjbk9gk3Pivx2beD2A7F9tja5lkTfqySxQ96veW6m9DxpzeBwYdhtxZ2H9YO6Z8f63JKnIVa0tS79qq7GH4vljTcePaqp538b0a7h03YUNeJlugl9AZLaV1XgGm630Gv/PWkaRt16HziIEp3xesY9/f59ZJbF9BWeo+K9vsMvu26GkXliUv3ys1+97A95rrYq4c25HY3tXsg05DRtF1L5juG/KCH/BXzdPqI3xS8/kCMpXlkrQntkXYXipPHKtp66UeqytM5auU4z7QpcfhvPWSx0FP+0zchuTpqfjkOe3HJ3HdTj0Wui9bO5P7EXKO7xeucYr3Dd5t+iLR8GDUM+wcCAT9srN6YcPMjfsWBEK+8ALZOT8Qk/um1/YFQt7giM+PnzW1NdO3rJ1ZX1PbN+KNxvrkmC8QrhmauCJvOOrHt3tB2jXGFbq94dBAYBB6fdv0hSP+kBweiXr96k85uPn0muk1tQO6Nv1wn+wZ8Msxj3d+qgbNqN9aMUge8kT9PiWtPxoNRyeobWS4b4FcF/NGApEJatLsgrZAxOcfsBseBNW2TGxhzO3rT9VucwEPe4LBsDcdmuRYNBAaTIcmvdIN+4e9kQPccrLoeCIRWfnHHfWEfDVee6H0Rydak7Ty7/fI/pjsq7FZlJH5XnmrCVqAuox0oViqasYFP3ZAxG/XiYVb1m5tV2YkkEzC7w7L6XApFhj2p0OP0b2mXeHE2s74eghdnmBgMFRjszyUMnSPDhxgVy445JGHakSaqOJZ0sZsVR/2yhG7Mooro/V2pTxyaLpdmf5A2K6IN3pAJGZfKlYjEmLlnxpvatVofM0MpXcAsSBtGmPeIU/KXbZZ0YK4IpvlgC0decsHyGionqSFmuhsMb2uRqgqoDpHPFFUB4HEXo9YskBkyC+qcjhpOot3EEnaPaiqo8EaIROiwbrIVkJJfYNyTCzhUMSDchdLK4uFFenElfq9gslsqAwJ6gwNYvAtljQaxYlIKOmgPyQaKCSNzPcfIJo2Kqg2JPv3F0qonIzEEsaPidXScESs5kU8srwg6fhWSap1E8JJxZqIkrJBMKVgGSkJxaupknokJhbUSDQwLFZTRS4a1IR+ZaQjmFSsPolWUKQTdVx2e/trbPa7cjTpEEvXHQz4Q7FURxjG5Yoi6/XLcmwo6veg8UcCqZ5Ux10B4RIs5XG5WRFi4J0vdpaV3bI/OuoX6+mQGIr9Ys1ddsdEq7CMULoDYrVYHhbWGvH7xXTGML+DUkw19Amv/T0xsYsKOTLfI3b2kqNifXfM9rglJjZsQTUJDIh1jEgqB8IhobQIbn2dOxAKiNUr5eIoWcLh+JVEMBCaj5QD2/T5fH2j3lg4HJT7UDj4jbFrNDYSQUy9fUoynMOUaoijg6M13kgkqdAgchj2zZyBH0PogINoQXpO/oUxfzTkCaJXkPWao1Qa2Tdfibw+1ZEo9UgoMBDw+5CdklKfyxDUq03gCGlWL9iFklpns2wJGTMDSQM6HJC9Wki9Q/Pl2PwajzysSbVqObm62uS+3Vb2fL4cF6zBb1GJhXYlhj1eXSR5lTJqB/6V/V7MGsAZwWJUzwPixa7PJwsLrHTuEpbUp2YEinNQxn/uqD8SjsaINhgdCSlnCEUzNjVntzoJJGyRfzQUgz+jQpVSnSsW1j04EvBhPlzA2ZFYIBiIHaB/Kx2IkDmxISG7TS0wHD1A2H4cGsHJXSgLnP+CgX7e1XhCY8+tF1nNUNLSNfbcIf8CgXjqv/0L/TiRBkKCAY3f5LGp3hseHg6H0KiDAhmMvz8lFNhEN6BEIuZBzZMFfDF3m5ERty8gRwROeUaFBXL7/DG/N4aztR1B9Rs=
*/
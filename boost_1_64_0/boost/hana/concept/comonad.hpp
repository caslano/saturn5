/*!
@file
Defines `boost::hana::Comonad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMONAD_HPP
#define BOOST_HANA_CONCEPT_COMONAD_HPP

#include <boost/hana/fwd/concept/comonad.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/extract.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename W>
    struct Comonad
        : hana::integral_constant<bool,
            !is_default<extract_impl<typename tag_of<W>::type>>::value &&
                (!is_default<duplicate_impl<typename tag_of<W>::type>>::value ||
                 !is_default<extend_impl<typename tag_of<W>::type>>::value)
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMONAD_HPP

/* comonad.hpp
v/NRIt3VT8p1v/fvO2c19nEHq9vftVl6ZR/H95gp9fvrjL5wurbZWK5n5UK97wt5jKV+xl9nMTmW+dXdZ+rL8abL++t2XMe//nFV+8XQ6n42PXLWwZ+s5GtXY1RnYZX9XhjXr3KB3tdhL7ls/+rWT/tm06lfEeWq5Rbua8ax2+sC3mrhqkPr6tZB2ZBlmVzGDqMOVS6A+nxCdethZO51FcnLr+c6/PWPvX7+2dfZ19nX2dfZ19nX2dfZ19nX2dfZ1//ulZTudKZ21B7Tk9gxKjIq0j66Y7Yz2h7VNT7DYdiEmM4d6cnlmUmJHeV3Oa6/oKkgZzydF9NMW2TGyLGidw9joYzxmaOS6K0vy5bT7SLuEos+RxBuj0uor12fNnn3IiOSKD1vn/6in630u4b45fu6UW6cROcIc+Lmst1xx0ZaxDPCiLuBdrv37wXbjcjsIrSe8S6Mvktr6Ye4tWTFpgXOhQuOfVkXi3hQxq7dO/xK8NczDb1Ufy6VPj/spzbPNLHNMyu1eX4Pixgs+3pD+n1GwV0v6EizlKmyrzes5Yc2T3cm3WlO1K6SOWZxuUW0tBgxn0+/Dh/xRYURVUcR3EcIV86ri8yOOWOU02FOzK6SOWbHCIsIkP27kXb/57ImPxlRdRCp9PxcV77rNqbHbPyZSWFz4eq2HeqwiCAZe2P6eSjpY3nlzyWioo3xrryBH/o43QRiVtxZlWKeMoO+OZfbtXY/6KTsluMMjdDzJ+nfd/hjX65n2k80J2x32Rx3+eMWESjj1rp1ZJMB1N21V3uRqs0e689V8sN+3DFulDMq2qS4uWz39l1oEXk2I+6m9HuTHm0/15GuygiQx6/T/tiPa3Xral7YXStv2/RdTHyQEfcF2vUQJ18ZaejFIlaOWeKC/NTe3cyLu1uluB2rLCI4wIi7mXZtyZr7H9aRvmXaSPHq39v6p73NGqhxybxPK7KIYnncbk6//37+y7N0pKNWPq0L/bvLAD/FrN9SZl7gXLzS5rFrLOIjeRxrobXvkEmTDG0tGspjeEUdP8U/PsukYzgX7hF7/scWcUTu1y/UUi62tUzXkUZpcbXkMdwvba89UMGkyLlod9y5Gy1ih4xbu26u04MflBjaSt++9e+j/RE3ZcQw6SjOJfO+7TOLiJD9vCX9XPr5br13a1HOpD/Qj+E2f8SclDzCmWxS1Fy2u49T3JNlW2sD1Ne/bbdVR7piMvVGeV7SzC9xm3QqRgVX6t/lv1m0awj1mC/S5hz2NpOjtAvF6brGu6G1/RGzWSfdroI5ZrouyCrayZi1tBVPvTJUjshb6Plx9X1ZoH9iNm03rpTN+zK6YCNZbtdttBbucsM2IR94VHSN8W5+Uz+cgzopNak5UXPJPK/U0SqC5JilrXa96GPtlwmZtL6/Q7Z1Oxq1+SHm1JSkdJNOQD1K57G500pRGrFfrF2/Jq44aUR3gUgdI+OMojMz82PXHhiSZNIMMpeuxm5fR1fLyH15O+1+1692fqgjXWXXW47Pk2v5YY7JaTy+xLR259LdsYdvsIq7ZZ9vr52bfCieNaJroj9DW7/XIsgv23mWaYM1LlvZ1rdatUD1uCO0eCb1c8qjtiiQbd4t0B9tnuSkm0RMGq5x4R7HtGIapF4tY7+Efp5Y9uFOQxuLfDnb1jfED8c0Z5p5TZ721/F5GV0EvEDG3YF+bho5/wMd6W6P/k/LebZL/dHmjqQks1qci1biHmMT0+T8Q0dtDv3TfX8Yer6IlX091B9jGKdj3IhRZsVNRVeed0m1Cbvct0XS78MqYiPktyQiuaXxbmM9P8w3OTNN+uqACq48Rr/XJjrImC/VZpg6dR5k6HmiQ3c5t1g=
*/
/*!
@file
Forward declares `boost::hana::adjust_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADJUST_IF_HPP
#define BOOST_HANA_FWD_ADJUST_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Apply a function on all the elements of a structure satisfying a predicate.
    //! @ingroup group-Functor
    //!
    //! Given a Functor, a predicate `pred` and a function `f`, `adjust_if`
    //! will _adjust_ the elements of the Functor that satisfy the predicate
    //! with the function `f`. In other words, `adjust_if` will return a new
    //! Functor equal to the original one, except that the elements satisfying
    //! the predicate will be transformed with the given function. Elements
    //! for which the predicate is not satisfied are left untouched, and they
    //! are kept as-is in the resulting Functor.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Functor` `F` and a `Logical` `Bool`, the signature is
    //! \f$
    //!     \mathtt{adjust\_if} : F(T) \times (T \to Bool) \times (T \to T) \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to adjust with `f`.
    //!
    //! @param pred
    //! A function called as `pred(x)` for each element of the Functor,
    //! and returning whether `f` should be applied on that element.
    //!
    //! @param f
    //! A function called as `f(x)` on the element(s) of the Functor that
    //! satisfy the predicate.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adjust_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto adjust_if = [](auto&& xs, auto const& pred, auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct adjust_if_impl : adjust_if_impl<Xs, when<true>> { };

    struct adjust_if_t {
        template <typename Xs, typename Pred, typename F>
        constexpr auto operator()(Xs&& xs, Pred const& pred, F const& f) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr adjust_if_t adjust_if{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_ADJUST_IF_HPP

/* adjust_if.hpp
8bC1rOltUn2pIKYmp4hLm0zxqm/KKNmuKqTjh/t78Koub4OtTbwBUMD+WA4gmWOxkUQxlSaSVJ5W9j+n9IqJYpoEa0I+a66vGbg8qNqklV8jM3JqFFp4cug1ICEtOrUauKaYr37F+K5+ectQWAIEm6NiCCf8nqvRVNF62YaF9Dp/5WUsMarQz6kSrVr2njBSFpdk9LOF9ZS8w2z1TkSmchSMqHTXQPikDSi0l4wQYzdWlFGY8MfmUjoMXSEHa3e2WKWWEQZ6SY/+7VQxtkj/xWodXzSWw9qMEljO6hK22JIEfGZ+35QT1IXP7GRn7PgEibTVT9Ml3QeDx5yGeS8UH9FGCp6CGIM9+AC5fIVXfVdT7NpUCVNE6bnX8o0t361mhLugOZuLdroMDpHzJWsKzyte6nh32KpVDBqQSWWiUT2PCvx8Dn21fgM7aD4r67iNq2F7KkXst7Y8ejdfGQX2R+h1cfDzD/2gR9QJy9RBoceN/DTDCLCJDuupPNp6285633sbF7nyB8y+F03N2j1XBla8jY1Hy9386QXjRzEhmsIhvyiIRF9EhsZcpe5UuTY9lagYkCjs69m81SbmnjvpyimjCFmZePheqfsX1YMFixaYtHttWNEisUuwEBL183tV9/lz96gK79WQRn915eDqT1j3MKx0BImJsfuNxD2OU9ndtCygboNOdCQnb7NommV9XpBpcf9C3AQcxxQFDon/sD8Xh8Rkvip9Vbk3Rxqk1W2JvuNWtOWo76Fv9vOvPCxCpe60xRr8by/vR+O9ee35V32Wg/Ktj89IIVCsjqlGJrXV3tcmFYzkFL2W7hKA0Q4xP4CfTNZH8Eu9We8YIyG8AE6NeJKttZqhewwlli9tp8WomjyNp5710Vjxt4R/Hv5CiEzCgxX7Tw2XroUPzurYlQ1No+TNa0yW0xYkIRzE14lAPprv+f7pnxWef5TTyVAVKW+xFi+YzHVisPKws7mSXonnxRZly5tesYNLBQEOCtSfNDdu2DkWy54+Cm8T3HXVfqO+Gc86PCNHUcSdNPTWrarvZxlgWNG6EhNlsJuDT//uECh7onaBVLYcyklDeHnI5H0QEVJV5BtQGf/Me1xUFmNtgSjFCfDC0lPu7pvMKpR/O9/J2yLnOatwffGc7Qe3/Vtu4RkXFPWfEdwnixJSAis/3tW2a98yktLoB0VJ+3m8F+HOhNj63FXUixOeosu7oF95G8mPx0AkzafHhtPSRKFtOgpt2l+vSWVPiG2KnQ07a2lssSeFHB7DVZMZjMSutNrQekOx0vdRgPHQR7eZYk0sBWBMl01yvVnNoOXtHJ1RrOdp9wZBLOS6w9FIi6gctGlLSdasOOhU+GV2Hk1mQcHYsPLrF8x+m4ZaP7G1jfd5TFH7f2GQN1yBvNhAK8RFyGzBaFx29NGos/LAAD0l2vMca2MOHw+/v4V2V5fZKXFJ5xwEd69Q+SwtYpME2zRzrJduanSkezspktcb6FbkoDGXkrlw7gPE4TTohTB83BDzwSlkMKGlHUB3bz6ZqjaGzILXxjY+OG8MowmDZ9TY/a6YCAfzPqK9LAjscjkhHduwtJnXg7By/5bN3SHESWAy46KvX4PUBmzEnphf8KVpzfY3ijp3Y3vFamOux4rxbLJj5E4GZwgYkbSsI7KYP5K/HSHo7KkVSHo/v4wN4u4jcNslqO/Urwk47RUBrXzRcX3lcPv6IqivNqw20R9+jf4bUl7RSIR+llaigT73fsZIPrLuM9ghSxDLjLHpWO6bYXf0m3ncxniieXjhtzgS7uiAQzbGS8JWKUlMDnZjL3rbDkPYkqQKzx3wrjOQW4/El2+z6tqjk7eK99wn4gtowUs5X0EjWPNwT6P5NIeYC2siA3I6ah5OtQfRMriLWj92yqUQYstNPWuKaLqtm5Hlt21I550rD53eYjrP1gCC8KwnjLNEiMBPJ7sdJBqIvu1MNBfa8G9OpTm/VHcMnrmNMX0y8ov8OvdXPgWFj9o9XxCKm7jp5WTuUTHryPAd589Nr5wzimKtYbDkVOgSDsGkgp6IhpBOQjfBROiLbiw7GS7SOmva8zfB8Z5CqLj3Lw3CVkdxfksFI7n7G/h15Nfg1rq9j8dgSvu2s9tld+yjAfpXM5l10p6z2YLpfYBKvvluc5fHqQAhxo380Oc2111Wig/L7Gs/u950bis7XsoFltr/eamXSHoSEt4mJ0bi+0SDW+uS0Cw1xTLFPzU+cTrzz5ikxzUr9QqH6FxHp+hC9PWTEb6G8cgo92W+3fYT2L/TEQqGJTOCD6QfuGhv9kC6GWVvvxLeQJ34pzBcCZCKQK3wMnB7BGY1VXmgQx5rp+Od4IKSIZRcR1IH51hkUS0t7UIsuab5ElENo1x3eSmWUtLaXvmdLvYNp57XxYLPztFbMkdfB+a318j4cTFQylvVrwgbe86WZAOZRvsCuCKd5Z2Xud2lhXy6BI+nw2vWL5QLPGuI1hHL0fZHcv0Y2YF1hejDmo+PDEwneeGSJCOsymwUTbY/PQrPe36dLG2qRIcS0l+ld09F9C/13kgczpqPtTfUI8O+kkrG0H4OGQzZ0cf198ZFv8Eu11LnUOmSGmV76jWefgtMHhbkSi8R8qc87XVU6a8G0WBpWcuxRfeWlO+lhN507mOwobqE/e1pQn8VmQqFMpFtzIh8cz5w6a1rgadbNVo3n2a6KGFYyFSn4vVOL39AvOsY0Kvk5Yx4oq72Yvj/7ekaDfcAjLKQYgJZcduC4aV2TiP0jleRSdXiAwMzwAD78ch8HoGyquMY3ydXoVbvx6XT9sooYlwnL0M2qp99xWiu7FywM//OWqOWVwQGzoGT0ewQksmANzXP28J9XEcvfwTsmxsPpIZ4htP34D3AIcds+H9/UsWnVGLD6Hp9jjdfEuUOfKsMTETJkroZlpa0wqK0x/uQLsjDtrfNT0S8jNMau1ZrYsjgJhds5F3IDb8QUhFu9U+3HPzoqPRic4byW+ttnobdFPzuFSEVrPzj2aMMH5kMpAaqmLy2Du8QnzYrrMjrJ9nguR9SsnSribvlIqYBi3A8IBFmjM+73XllJQxLTCX27BXr3Tl+olEg/510qhMv68kFhD2U3bwere95Dgcq2at0J86vEB/V1l2sj0xtJcPU+1FL6YvFniw23uVQV1sBcNo7yAVESCO7pocmXk+hOhzUZXhimyWC0cx9fhZlR0VMpPZ5upca8Bv3zFOD+b06t+25kBCfnn9Lfw3ipf1PoLutcp4N9R4VlBKalv3xrx9MR7eDGIotR07vfUp9RjGKigri4lMcWX4RcXcp82kwduHSof+iTOMT9phu3la9GXbNOG7JbVrvx6/7Pe1kq/OxV6cQFSCvEF85eFbxy1F6T/G8G+lUmBR5caeHX/4UYeldqVGjTWrWJBOM3Jfb56ALfqdERHWZ3Zj8NSptzrZMAoaLq8up/1b7V0y+1zW0TJuhz5wp+XdRTn7J6vorzxZSqWjaPF5po7EEh3MBWc7iTakuOy83mybFyWEX1ZjY3M8pgIzdjtXm0vUmdqruRYn7K22YlcvykeOvPBz/c/KGdeSRb+iOEE/Mwm0HbgWVw9200+PDbXRhzC6QXe0p7X/XZrtDdPhKN+grG0hZBefHYxH/WqcyGOpPL84a3A6PP5QYMZF+nuOTZCccIn8+Zk2HZJn6+QjmKD3+nOoULIqHYEw+mDgfa8ck2JbsDA4vGggvO494vNfNP/svnvxtWdEM7QtFV1BeWhlfgLs4GJpYe7ZQL8VxLh1fATb7SOjeFGXGSHJYDrnjCQUTtzDgOY3VHiFC4lnSqPZI8Iddok2AjpZcXY04xSV3Po/MioHqk1/hwM7srxxa1abOdXQh2S2JFqbYyVir9Ebiujq1HiATDcbxfeTMWD131zJOz8qvixyaH1D2rVH/6b9Yh9wn4BnkNOAJuFJ8VUuNm93qpz+Cni1c6P4porExEhPwZcRj3462Oha0GxeNe4wED/6QUL7GvD5vo2CjkHsovRA4cF/jVYVepjB+ODPwtnBHsndtBINFai454xtegY3v4Sq089IO42TUJSw9w9YuqaV9QCBcm43qwLAM0KjDaVFjtaFoOehJqZ+l8QLxI4HjZ02e5n2e1dBkJcEq/W4UD+O7+KsOVXTEd756lvYlwrJqtmIS3fINdaGeVqc0s47udzXbwuNjwLL7jzAcOnu3/16myv1XebyuTkjYCkLdWfr90SqeQqM2YDP+p9yYjy+iE9yA4LLg0v9FhrvFha6QXRi244GOek3JhZ2zc8iF++r1dBKhN7HWTSv/44b6pLXiPcQRO3crdqurgfA4dLgOzT1mmcfgIqVIYe2swBQFMBK7kf+Rci/+DFv3evs3F3+B6ECaiviIQrtdgxPevR3nizErIlVqHfCNWXgQFmKacut9616ZfsSwtXMYwVrIvsZr2r6g/n5KgxkO7BK2wafXCyfoXDHfmI9Q+l5FvMMCKPxSLmykmYX8tSR7wCIzonKbuhG5QY0ndIClC6/e5gFJ57CmVqPF239gPLvAuKUloQtBL4740wea6DgAB7q3VqYJ14a1/Lv2Xiog1vft6GaYYE4gVdZGgolweZC16KVt4wgQD9y9v9C9/HsAZi/gvTPBFqb9Ca9yoUNJNZUjUE7Kf28qyVtoYvIncouwbjzytxUFMHOpVQAW85aXfbK5bItUPXYZDONDSd353XFkN4ob/6iP/YQfm782dfjL153MKsvR8BApeRKyzdmm3rTaKDbZpCxL54CtOGUfJ0aSoUOey+vUhlEqRRRNT3i74nnhO3aqBYVTj6PIx9f+z6cGj6L08IxdA9+Oj4+wja4mxQa7lnTJlEzl06cxmW4ZCpQG9xcNsFMsnpT9bdEnByMbPz3b+mjh98KicBvUDA2n5LpDatGiDGrQ5wxItFjvaDeow+hoDdDusz5Iep1EhA166QBoUSMgINzS0fKM/H3+0wtS+v1x83zJGua+MW2X0XFXg02m9l1ChJszrRNvcMEZ0zXFphnHm7XDlOS7AQ8LmyZD7yTFoUhSB89eTrngiih1SpzWcH93ME+O38oA+6TS8HYjoEl9VbTTkRaTn3n2mE1nsPMiShYlX7r8HD4nCkQp+hruZW6i6bbj+Uh9ALbfklb5TrUUQlL90Y/zrA1sAa2MxEpc2vEl2xTuRzbXTP8UVtjj/+z8qvZUGhVxoaFZ85EaWqpwfIvMAkw7OIOo+gIikADv/ioMp5YGBhv05u/UApM/qIG6kc7ggiXCd8Xr9HYg0WNnV0/f17opxVM2QzLt5HcCHIyZTT8iCHNqo8yatRDKqnkySMJieCXCX/ncMGdrVCFvHRZz33SG52cO3KH2oSuYLzaWIv2j2f3Odaz+BIPeW2Qbt+XF8+PzdvP8eRmhZqB9sexm19JZb9RyY7pq0SuHGVdmtp6CJs+7QEhD65nZ4NILm9lNzyDq7fIvljZf1k+hogAILPfTs3Z6RvDjVsnNlXSxG8S7XaLt6JIRdqDa0g4j/o3RHBs8A9Ohpn2yRuosf2/FekTr5MqkxsMia61LWuq5+ZvH43Ig4SXCsa0hYasEcuRKWsMH3yyzwpLx69pBVeCD+kyzjyCIK91IonAoy6Sdx5CHwwbCJuNFPvH1jxxxxg0ysvQqeb2x1rSzBuk9EJzPyAJcys04rZ3NbuycFw/LpnpL7b5Vl6GWnXtW3mXqbpOQId3AOSpFfbIbun1+cj82QZf1Zfat0SwmT08hfvE37buUmq8GzWxhZYpdMfNz+tdHAKmi9VtsvpwOvoOAJZQTMXa9rvs4S7EPnvveSrQ1xWt+3qCKOXxJ4+jSeduf4Dud4XJDukMFcaYfHQKLRsscHlCeRSF6Dx4hNta3cVRTfPjPo8ZBXXoXN7LFPLulsZEg528FiYQOTggJFCevC8+W22tY2zNWM2MBLn9bdE2/bQWPs1bUw56ujrhVzxNMcY6EXAY89K6EOq9XhftelkOHvrquNz3P/Oee5akXEgxinA1a3+eSje4tW33ISNDDZ6j4tiDgQTPT5DgGRpszDIUPBabqUiqNFPLr2I5laEY8Jpq91aOZmn1HBHTaysHNBFaZLgqBhDjNnuyGPKI7fnxpixJct8URfOJKC3j/1BIabkN8M7S4OalfIlw+95gZ0JvllFoRS5OntIl6CdsESKi34VEcdzIG7da+NQPF0yzoJoz/ByncCFUHgACAQ0sBAID/f0JrHl4Kf3n/teMcDrKu2Kf6zz8Wi1L27sH0lOrkGapiT7ENfGb5phbCvxJbGe1p/mT+Xk7NgC/CEMMc9BhHZ8kkuqXP54ARpQWDaG7nFRsG66gEmjHD+DEfxk6TAFbcr3oOboSbITuT57W6sqqfpJBMHHCXZJEWsQVEtyYBOu1GnX+cUdUjZqVs+kWqIBuRPgrqmi2a1UpjwzdWOYbZ2s1TBgIJZiv6Yd/Ltd9MePDqRQU+98ohUBXs7doOonpFggbsNT6g4dmnt6d+/h7JM6BE/lpCksZdycRMpOt+TKk06QHn5kO13G5eO9qH23cA8q8M1c9aT4ctvi62vKrKnSuLeN8Ydt9jzQVZO2HDiCjyyUbv60LqyclVXg5EWaOjBQoHDLVPGfax6MFp1J1vMaM2xvYqJkqPhpivXSMo3nxs3+d7l9sXSaKKvrYjXuCzq4563IGfj6vJJw07TV6u9YdGqqUD2oW9SJLt4nULma7eldLlxD+gJet6ojOK2eSbk+E3076/P3aEjnenI7dqQKd5INZkVaZnswxZ0NUhmgKBQmRzDSZytzYUvUL03V4S1yQDI1Fuz4ekLFi7w4Iot9Zc2ilDw4MT4d3XQxE8laQitXOH7lb+pz/sVtePD/pQ1AhQFslsRaxuOYwvJLHCtEyxQvoT5TKwkrK9ka3mzEqA/a1e/LjWkduoYvHS7yIeu/Qz+1UGwex6pbLf6ac8Ii8eMmdT6OM7nYoSkqd/hax/Y5JlYeYLT8qEpZaG/K8MYZNX2dX4JjMVB7FxXRN67vnPGU8yPlOldeRI8Xmllo35nqK5o0qORU1Nrjo6bwa6eKHnGS7kIcWYclL9onnpvFxywBfk3yENS8ZOMGO4reLe8lX0atfDhEdw1TQCiohAq0NNNPdFbMKs5wxoD5gyRbqfBmPvXv1OWhRxZwv4p+no/LQjAspwI9WH9GHSAhUj5tIh82o5baks3k9bktFRBA5OXit92upZj3OifL3hza9WOKUA65ukY5OSYXgh4RKJkWZBwHr7al27Ysu085dtIs9a1u5XqW/5cU30onsCRnp/InScTdX9DAr71dzaNKtajsdOa1/cqFPBuk/1kLppAmaHPCRpw87eobKImFeKlhFckoi6Gr/RsnJknc07bwOtXZ2Ooe+929xqjmhoMqWIWk1i4U9zAf5q8fGt/kre4zBaGdQwR/NHBdqs4HQ7LEV5N5neiYbX9hN6eLTITy/S+OdtkxUNmRpllRrr9Qd9AopBPe4R0otPY5G8G1z8MlOUTsCoetv1tQdmuG8crX3CJ34+Tjz6Jk9wbaWqI/XkoRpy4nuMUbur6DQuH1MklR7Lv71//1ZAccvtCFgt9/Wvq8XEUT74a2/y5AqcIxnS0NfGfR/wj3V0kTRt
*/
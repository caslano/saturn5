/*!
@file
Defines `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_HPP
#define BOOST_HANA_GREATER_HPP

#include <boost/hana/fwd/greater.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Greater = BOOST_HANA_DISPATCH_IF(decltype(greater_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater(x, y) requires 'y' to be Orderable");
    #endif

        return Greater::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond
    template <typename T, typename U, bool condition>
    struct greater_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less(static_cast<Y&&>(y),
                              static_cast<X&&>(x));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater(hana::to<C>(static_cast<X&&>(x)),
                                 hana::to<C>(static_cast<Y&&>(y)));
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_GREATER_HPP

/* greater.hpp
B9OecWa7iUdsGPx8oCSytQMSZ4twPnk0MNh/8epucF5zofoJoayF/DyneW610jnJIEvMPogNLlCZC1gNna8rma5iH8bXzkpOeGCkC14T9pTjo3ZQas/lFO1SFc7MXFWIm3GvYs9I/ffZmjuNRGFJtsmTfadin5th2gPtLXrao6rIa4p3+FALwD28uc8zQ3vQtsNpJaTWV/XAtS/4ZBJbnoiYT/Rotkpu4Lr57xH5dkPKByXbRHBfkRXULkwwv/Tdl6ow+5G52+CuJqQ1JL+BmTvMJIV6fTdj1SMD8Di6rBbB2higcU0RiqjGWl2fOGF9Qp8gfbxkOlfdvEwSXvomsXTtQTotU+bctOX5d49gs988hAoS53uV0Clnbelk84tgj0jeOCXDeuE6lUCSIbuU6EM2xsCwwcjTAyZr9snsVv6iBT9pxNAdPf58vZeAX34VfzUrEBg2HKzoUARRYQQ1KCoJZsuCS7qfSrpH60+7fnCr92UfymLbVaoPTGEsPI2H/XtjDz3orWcNXU+vUep2sTL0ytNtpp2RsCQe98DuFjUwl8lnjYm25I85fO6cO4gVkmITF4BXzzzNCr35rOK5+lD3enm5f2PjA7PPAt7Wd20WTiMMSlSAjFy+8b3sGiPS+Q89Lb5GPp1B8LJn3xiOIB7VDxPSQ0rk+fWcNAlbzaW3kI0tLYkObU6n1YuoDK5Dw8mfil54TxcfsyJa+1h+6fP4cdx0ZfjhiAp5+Cd7uE/80n8xZ7505BKpMrrpJ6gvJTJT4pvArNrtCCmbMu0eejqlhh4gKwDKtl6FPgjZR+tlRsSfK0jMjviYjrgD9k+zpo5ZY6vxfCr2bHN8XoquX+bnuSGBTgWPhT8JnFU6i0Zv+WFHIV+JLnoeiTt2vviaZrz54B2CPvqtK86p8Ss1JTTHj+OKbJrTXM7SZDRZ0h5CTlV3BRBpTs7+8N4SkvMtpFDXnTocaF3IljXFkQ7LNrlvrQn7lEtuv75RH7wY5PBMMaQfPOCxVg1eZh59w5AeUqY1Z0mc5+ak03msnqhPvGu7xnzcXoKmv9w9AWeK79mqam9/LijOS4da/lM8vlyVElq42VvVYl1AWJDW+7aviPn8OfGQ4i/M4IoBRzO5PxvRW4D62bdBPc7YpdjvddoYo6EyO/WUnQVMN4qUMZXheuaoL+52x8PmfyAedqd35WwDmqW3ycRW5sdK5mIdNzbVvcQvudnnBdnrPovDkk8VAPcAJSG8omVtRnPsRDYVE0IE/wjO1Sj717Qux7LQU8exCAtrpjz9pwyx1Dbz/MzLlaNinyy9Vz8IowL0o8XFOPHJ+LFV1Cgd5Ekii6/VO/FeFSJzd90MyrF/ydrqcFVkrtYQLm/HtXpiDGGV6cbh3KMfahlvk0carjIbXV64ekY+XRVvU8Di2Y9VmSKUlTPNeY4/5bSh4rnIXOvSea5ZB5IcGvyi6ibnf+I57X4mXBo+cO4oumM/MsgQhezxift5T+WEyyEdU+XuDriPaTpVq3hoDFXtzCyzCKhFCjjF4xK8IrA0GVXhlqshR7sFGGATz3fSLmo3qZnKfvfuE08SwOCOrnHCGW8xxRl/HWVkFD1m88GRksDp5lr0/gue3Bidzl4bffJyT5tHVW77RSV0ebnn4g9n22HQ/8g73vzFiQG2isLGJ3z+0j/8thuKOf7INSOeSX/oclV9wT6uBPvmHAYaJXr1o7xh+uRf7jcb4mObUE01ciyI7tTFQhCjOKjAK29ucNr1b8Dp2VWf/aJeAni83aIUKs/tZblJDzFiEB1pi+ZquiBLDbyCeeyl6rBDeJYOyPT9o9DEN2YugrcZQAj4lsQ/daxDPNzSGjX8eLyWktWK+mp08f+YducgT5om3nfHO7Zt296x7R3btm3btm3btm0bv8HZ5703TpyO/qe7qr4VUZn5ycyIboGHK9eIQM33bXJNzuvh6pEmxO3pzdndbsndxDjZbyNH1FLvlojHHvgPaVTf3jPAx5v1tdhH+Cn1cBaZM82jGZX+htuqDHvxZOIrMqiYgu6eugv6OSvl0LVAT2y3r/hWFpJz7/SUlFcvbLsFDxz63esLKhPtbiUCQKqtl3KSbJRtCt+tW3C9i/icChyIT623IXNOBuTY+xW4tTAZ/b3zxwnxuoJFJEmRn66E0YBlXV7O1GgKBYLD9xdTk1DIjJTX7kyOlNfPrP7AB33abgl92g+zrp27L/vY1wl8oBf8fGzvEbdfCky/SXm3KvZoOy7b6Ouwxiq8yC78gHfAZk9qjrubzsolZO3svTYh5X6nINGrA8egIXMsLg8+Q0s909k+b8PwLd/ks8Opo5ac/2kUH9WoAzZAAeTBR5zrwvy0qUcm63VcBkMuiaYNBMSVxc2bRXbZXhr+3erLwVpwXf0OkPXWbnP8mTg/U1lZc00f+tS1pPaJzHndK33UlZ5IEIk1uPDWA36IQebd6pKlCcv5FQPeA5DCvkQxfBUetTCZOJ0wJfIN/8THP99Ws7lLl9xieW3tL3XI9Kpwe4AX/F6V+PaZOsWh37MZR09Lscy88FKyNYrO4/PqmcDlnC00+8g0UrI0tKg5Z5tlpfVy2hWIchzEOP0dG7JX2Tv+8bmTaWV5IUDvi/zBOorrqBV0FYpqJORRqCa41BZwmwzXGJ0p0GbN9qjJGPrOzxJ6Tuv41jkbqGro1eke9Xqiya92iNjjSt3TmlZ3RL1iO6tWZXu7Kt17x/r6+ANmnQVyC5KrMrcoF7LuY4VpAriPHbTi1yG/CuTl4Bx62S8kbEHPha3/auMI6mS592Y/Cs+CDuPLnHk+Z62dDz716ULPf4G43PLil/Lj3XBz0fObaHTF8V3VDrhvBz2OSRx9BL/c40iu96QplcEcdX/sn6QGyIvkjKWcUsJa6ll4CX0zz+27nzHcMxmi6e8K1FzawjtolvkGbvaB2N592fBDfLHkL53TC/Q+gZfecgfVy2THT8Z6itLteITnGmVBAxDThnhc/WYyD5BEot0LyujUUFSikESE4lmHGXSPkYtF339tU7y+TWrdYPtD/3a9Ne3u7sZ/ZQ/kg/h48LFhfodIw3P1200NqOHosz6H44mdWiRyZRmekQAQyn0Z3yBP96kORO8y5PL7BnrS9xp3fGp+y0KfhfYYt3/0RL85lTfH75SObAl9ZlcPuY5CZN0cwqfd1sMT1j73UNTS/831PnzkpqywfeAaJNx2vVfYINqffwCrhbHrTLyN7onsuL0CUAryJf9AyI2AXPVMubJhfaXP3lU1x172evC3hg4C0neiPbwQr1/5BX5wmy6hbubaB5wQzWSq9YsyV8aVtfjeCwyB5xlH0RzxtpoN1OzpFF5tBE8T76vbg8Ri6rt08Q3fkXcO+ZQe8BaRd5hr3NuXdfR2nl0U1tJEdieTAErf776FXCQ7/MNfwdDhtq+TWbV37FOme+wfWJFZcvecGKv2L72CcZX+D9l9n277Uuqb76aHf+Wd3MEpd7vYqpBb7T9yW+s/tfNcD7tbl0S+dbnefZlW+GVm5Abr/SyqAN1KViG3nlWgjs+KJa4pTN5YLJt/YsoZJ5SEeCoY+VpCOeRcx9rYhgGwRrGDhfFYoRS7fNyl3KajHTnI70sfIhlcu9UjGbuNNTpk2stLDT2+WpPWDhfZotjZJS+y0d6ev9zhFXa2IecciVa2kKIf4dQ4YsmH3D/mTcB/y/WX5riH93ZeIL1m7wbAaSOVcA7xHCSyU0m0bepbM4JPntZ/2d5cb/143P1ch9Sk3U7S9E7M8j0+tGIxvb2nwJSEEtyqPNUmVEr7nlItNqs9A3zddkXWXZOe+Txa381XRiflGn1i+KsBdQ9a0C97x+m6zr1qFTe6wQUnMg1TDtryHwesV9Rlphdwq013eD3fPKrwj+iil/nPFetwMnkoivDb1HUzTQnH2fb0i9UUp4YUrhl7t1MIXnLn13mcOxS0H5+aBJ5+AN5deoTkkpk4cNPsAcPwnhYY75o8WyfrUw9Ia9P23nU6mGvaBLEuCXN8oY3RODSW1+Cku78665lTvsj3+FanLIVs9jmb7Bqn5nk8PkXeJdmL34hOO1FNC5cxRhH2HIV0p9/nh2MH+1oVDY5JvWguNyIfNzOY6kJZ/V0vWxQwluM2j3+ZjPj+uCPHt+K4a/4ZzayFJ7rFp7xdWNbqta0++eBz653vEb0VeIfjFjkTS0tkdfzwtWRbY2oJ1ecXX28Y/Kz+QYxKz1DSSpt+oM0efMDLGXyK59wyKZ0K/kRWGh6KKDdoYttxypFc577LqbTfrCRzmhbmrzHa0aS2x3+jKRmdNfDAPUuOG9ZMqroJoCgbQzo/UiM7wAbcRRsPAYacZAFWYKe88oQwj2KtDbUfvMkTskS1uQ8z3nHPTfsCK5tgc+6LilKj+zkg7rK5GxKleEokm+GntKVtsNdF2W9eHeCeaJaMNTWLNedys4WfwbRZJs9YM4stoo1p0MIjn2udFV9Dg2axKNoXR42KCqWWROeG1nPzG2bYTUqOGVb37h5k1wn0fQ/dWHru6NZ6HT4gKyl/boW7+WvrYbnANkwMPdKnw7nTri68XOhW4pKzvSIvTXiL11ug2DxQH3MD+fZVTqe7Hro0en12pFNIGUJG6D+sgXzJv7RVhfmwztS/nkfP5OaZlUTO48uP5GQJ+Q/AH8jHgeHJ4EmeHbsnWRZZV7JhXRWlqko6Fm7LVm576MojV65XQBtt+MX1trEWs5vTF6dFub5ynJLRP1h2MAt7bSePenPHBjY80ErdKSONAb+ffp3pzxU2Mt4YOX43zm23BjVYrZIADizx0zJoJ/c9CeXlEiYdf4OcyQmgk3HJuI5EEn/gXpovsWuxqCWacrzHOL/TuVTXH9ecNY+Yh1fh83+sXV62PeF/pOeE2O4kjX0wzhxPxtgB/krcwtGdMOX8jWq+9njc6gU6D0zy0ePtlRvOaEG33PK6lSBbh8JSK9PGuuUN10beEfg8GTzVAcHvAvBePh8i9HQn92xD8L/S33kq4TFeMS9vPFGHDu3U1t10UAw//EDiFJ9uP1Oi/RhRsVZ8HUnufgSYSLagoO5rWE37DhhYfiPTvOF3m53s3pH+kKP0gvmicsvOAg68hMZZtz+z9+QT3n3ZkjIXVTSLFo8Rn1eOo8kjc2qZZHsyPC69CKHbJWmOKjQMZNUOWS8Lp4m23+kTpR+aRuLFam8L7Z+2Dft7+Ra1dO4HLR9z74Qsv1VcM997tUxOdhmAf2I4Po+zv+o/AZPTn0L2b7c5IS8ooT8S0N+8jdPnOK/qY4ybW9/eUorCywlv17r0tb7hz4AT45PbLgCIo/srbXsLn9zIPv2qctQ/GXeNZpPvnM7a6d4HG8tvVlg0j47JA18+jaJOu9ThH7X6OCG+WyyBnrnt1ZWfcY5bbJqLdsv44R/Yvx7Xt6v0zSe3jWW7xUDMP7jEd7eRg71TFdl8Fif8HMA/W55V77fq+ie368b6/LftbD8rbp+0GyKTdSIAfP9/Up8A2jc1i4z2L3rs/C/6yMVv2ielbL2TW3x/XzWcbzzobwHo7y/iu16EUN9jh8gXJbMXEHDajXuwSKdttHOvwumHFNrWm9Nn+5xW2l6Xd48U3c6fUFE3X6YZAF7k93LHgFZORgjihq/QU2ciuIdC3PfL0E+vHODmsIlQj/+O5Q4771IsytCfHbjSL9KP2h9ID8IO3Y7+jnVPYY9gbn7qDEQVGP3XpV90H4Edsx33HXqfzh7hHuOe+R7nHqreCNXIfd963189aDvif8PYdvB18G44bmhmmtNp8DQQdL/ogFt+bfpt+m33efcJ9SH3OfYNATAd/RP9k/ss9pDy8N8o6qDXQLxg3VDcgN8Y74gYKoPtoe7I9HDtSP8pktvR16FjAOcA50BsrObhAtuC0oHuQMD82vTn9qcHiv0l90sOJNTvpTmKs09SD9WOlOH3FvjWP7U3tjsYOwQ3xDOdUQ5wDiA3ZDtIO9o62DbcNvQ3rDuGO+09iT2NPYa5azF+kBSQSn8pv1cgkD64Pbo9HT36O+t/o5h77nnXQF74HEDqkF2w6vBasFe/XIB8wbzA3m77+IH4weBAlIDPXPso+9z7uPQQ1oCugF9+AfxsQX5AeUBQLhVy+xz2gPeQ9v7uFfbR/dPU3hvts/WLIXgDmfSDDpg37OO0n9zwXGVlW67SbGZbQ0G4DXuXEf1IDtpArVxh317wsE3kb7PY/ksYgWwZSMv6ulKtWVdRXF5hLkJcPNG4vYHS5a19GJJC9u60H8Eqw54INy2HnigcX6pCvcLWMma6/KAho7fdzc7OBp6xUoteIN5Z7JzsQTIeUTTsryIwLLJFv7iDaXU0JdhViPjVDev/Z3Fj7wfV5VVfQflncJQ/VFtPe65OXkJhvkxcpvqNigoNioqKCgqSD3yC6OhhrgEDgzQZC5UMkyyZMgUVK50SjRKVjJKSDAuLkowSkxSTChPt/CtHm6HKZ/Vr9DKDmdl0JotzVowdOrYxLv+ekahxSd1RMm2ci3cjyyIhfWO9raURtYU8AQlJnJCELx7G6OdwgoLzlIGPcQcL3zpG1wrqaPv+sXBav+T9L2KUZBSkVIwcjLSkTNME4sSkVcM3c0zUXHBaAfrXZYNWURflqq/2a4N3Le/PFBGSmaykOS0+o5kuDlK2Aa5hPUm9zW1FromkhAxD8zBdwh/glctT5qZaXEvGdBIlfJfBRMCPiuoTAe0LRSOnec+YGysbH6NJA+V0BeozBaYJNz62rUS9NkaiaPXHRs36AzmybRg+4eAPZm5H93gKoAhs4xRc4wA9vWy7ttkLdLiUZskBMwWHN9f1WW2DeP/eS01R3SNiOSkvWOSjuRMvQZjIuhSp0jv7etJMdohmOTRdpsQIk6iwOZDFzLbeO2zZIjw31YK1OM638WWpt2ZkbUFSC8VWQlI6z6lETPOg8NTcWH6lZirggFZZPYE0m9zEQu5z9Jn+m5rvmOGy98DSd8Ns0rhiHQfLOtrymnPU+rgQVdXNg+m4o1Y7o9o7QDRn/u/t9S5ecWZS05hRLS/uNYl/48trbzfhsYLi8obPtZzWm2t4vNDijwIbYsLTbUPU3Lf0D77uUDP5T7oa7falezRCqe9JMmC3aVIzKGv5ocQ54Y+1mwUuxtAeBiKuLW6mEWSknJYem0z6K0Ps5MhKa7PoYeftajCJyGLrqUaB9TFCaVPJqgcdGPvI6ban0+IZbguQGBYJBeu6NKC55Xms+6cGfrwpWmoV+6Ys6fLaqdtFDHpaWpIlWi5KpoFEeNPTG8JzN09hc7Mj1VDYK4qSgW4DKYeFctkqGj/bhlXiryblJhHYpc0Z2Iv9msup3/ftamsnjdymqH/vroMy/o4NC09JtjY+JT3TDSMfIxYNy3AQGSnzX42FQcEDpSoi9I1dbEtZmfDG3bFVGRlWjYXANMK/tVodhKhELVImaptmIjo0PGNSxUe6q1aEnPMbwN/u3v7VInQFTyIpzXyW3MUnL5eDeNGtM7HQchbY+3zLocP04lFsm9gQg60rRkWi+DYSP7P9byqe3tO6ZvgHx3JfT26RrMlMqyNLgtc3TomkwWUbv15bUtABlYK09xJFyXTT1nJNMZU21yN9Ky8JRu35
*/
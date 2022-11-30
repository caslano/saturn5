/*!
@file
Defines `boost::hana::power`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_POWER_HPP
#define BOOST_HANA_POWER_HPP

#include <boost/hana/fwd/power.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/iterate.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>

#include <cstddef>


namespace boost { namespace hana {
    //! @cond
    template <typename X, typename N>
    constexpr decltype(auto) power_t::operator()(X&& x, N const& n) const {
        using R = typename hana::tag_of<X>::type;
        using Power = BOOST_HANA_DISPATCH_IF(power_impl<R>,
            hana::Ring<R>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<R>::value,
        "hana::power(x, n) requires 'x' to be in a Ring");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::power(x, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::power(x, n) requires 'n' to be non-negative");

        return Power::apply(static_cast<X&&>(x), n);
    }
    //! @endcond

    template <typename R, bool condition>
    struct power_impl<R, when<condition>> : default_ {
        template <typename X, typename N>
        static constexpr decltype(auto) apply(X&& x, N const&) {
            constexpr std::size_t n = N::value;
            return hana::iterate<n>(
                hana::partial(hana::mult, static_cast<X&&>(x)),
                hana::one<R>()
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_POWER_HPP

/* power.hpp
yj4lljDQt8HVI9qotnarw5bPuo3kSmv9X1qDrFtYZEhkF2IrGU/mgKCxT3L6rgglAULZyebHMTwDQlHbV5bPdNfL5s9JnvdN50uvu59smv+mAbK+nzGNzoiNnt1C8OG/rL9bpkHdQj88aNsge1PhtjonyEf7dewIc1OfFY89WSuf8BBTrmruAuq7ZNpvQO3JKqBUSqUNrFtj/4bNNEKyr5lVt8AxN1Xovq/4jcEyEVnSvhMVowTCNtHSE0GxS/J0R9OZfLYgT2OKWN/k6Tc7MB0n/h4608kWmn5iZgQ+sReo2Swofy+fJhv2AdlQGxfcY79CGb+VlfGKIf+QumH414/e3sAzKdC3ivrnXFoATXSWa5adsmTr7QALLPTTptadRKHA4b7QzEKBbrMm/ZEy1bc/4MoQH34ZNbWYF6c+JTE8FDMwZekO8MISrbB1wPTjE9suDzG8RXIsaXB3IK60YWMvYmbxEaGavC0VqVLOkbl9uUuR4itFshC3dPYAhbq0ou4anKRrwMLSK1a8qMEKBQ15JOUsVQWWgqzJd9VDcRnmMz1vsx682mt4VGHxSQlJF3hVMqiDHcDvqsSR5u9vItzmqQhYGt+pd9RiVSIkL2tk116Doa5u40oz9nDluplHzmQXpb5Uf2cubalQV4DKRPyU2k7cZlApFmbRXQgSOH7GSLpy1HIZmtfD6o0JWQrZ7FTYEr20oToiz3kyQ7e1vHuACo2mZ0ba7D6wr0Kpk52NPdbOfqZaOxqhF8CwprMbHdvfR79rLHgl9cGI4tLUXZBk6+xH9RGFzl6Rj+KCfcLpiJLDOs8PJa8PUXOmyzDD0mkQnbFuyv4H2nbrvSnxz87CA8fIpW6FIijeaLn1Xayszb/kuRpvjD/xzDx3LYKZZi7L1haqwtJu9Z4uwyB2SKgNXUT6SquY2I8LafPLSlc9uYyyYVMFVlK2exB3Hs2FDjokNSooAZlpb+UzGKv3ox2K99A1rafUDqUdbngaGUaXrfSUhmK3fIWg4oS8Y4lKciy3bzBXTcrq+pNDEl5yhYSSTHFCEs3phD+x7mDWfzT3b7+Ls96+HDNL24cxLD6WX/zHv1O8ebh8Sgh/fncN97IzuJFbzGueYu6h8HkoS3Z0hR7uAJLY65g6bKwWzL9UGgRsWewH/ep3N0JwqtNtm3K64D9215gEiGOaL2NWdfrF3ugZLU+6il95dcWIiw5fgLneFcKQPP8mmWil1IbyU1RA6SJaG/tzvZsKrCuER87DCDRQIZW7oDYVYGEW5wlkScZhTSCWDDCEhzI0MrCcLocJiGGZxKQ3gL+AKgkqGwG8J0C2+hLNG0S96ByEFcuJU/kvevsd8MmlqXqxzx6IHg1fAIZyxb0gzqADZmMZ4Ho+nMM+aNYgNaWxiHBZZXQxRFcVfrx9ouk/gRzpCa/N9r/V98mEquuhi5exsJoKL2z2YYnvaSwq+kCKdxPLXI/HDP2+EROqUXYpAeMReRTCvZjrumS9p7Xh8UI0Uy+UiOistY4ExbFqFMlXM5cccQIREkpBvypuV1YYNOhimtR4ghZg7FnLDyytb5CPXQdR++a7xrrjDg/GCUpqj2UA5e31WA/2qXTjReZHnQygUw7Kh7fjC43YtD2KOfOJ5rCwjgltiK3ZBndqjdBkxObnzPhGtuqd/Fs9emoj0+CsZcADk2dh9i1TcN4jOBhR4OrpT8SHf4TADw3Berep/NhCrsQSriHBLYTiUZuOXcCDYYeeCnCYRkpxMVQ4cMJCrXM90TvUA7CtAQvrF+dtCgQIolG3IVD5EsFd2Vhshl6GJX2re4F6UPd/iGuLknT4S8B/aOr4Z4VUG/rNskxXEShJ4Cl+BCl/wFCuXZl7KbgSCxqmoji+Y+Kmp/NXJfYyk8BEVkWSvrHl4rhyCgSim/e8j6x02AxmGDQ1c1fucDNeniwG8NUCGZug+lmISoPtM15ZIgQheumHDF9AUSG43AUHsvAMXOE5ZATCWONF8ggSVUma0MkzxDKADDatOr/jDa7vjlsq5r84/8TSYrnAF2dbGs7zhtnJRiNuIZ+qcbkygLnG17RHArsw9/9sfnJbQNPUg/Yh80PEhr3JnwU5GDn0KTA39iW1yyx/y+lDVvc1OH8WZwkanoDYYx5OnfrhpoCoKBnGWgk/zeLqnOJpZGykYg82Fw9V8PTTJdAUXh/l5kwNx272+H0xX4BCF/fSaDwGVc9Rd3zILQDnC/sDz+T+gyUC0L7H/W4a+IP17zi0t8/cekWq0AiHfVIWrSc2gK7vFsMGlfagg1ucextoLS2itd9UP6uRqxrLbSyBfzEvYvHSLd9UoQIDkYaYxHyEL1/aKxapRDyCd7rUdHqRyVcRfZ0aQLekMMaxBCUUxxLW1CstUMhL6kkJiY8WAVKJS4kxCo1ikScCnI/3/TEJ6x5kZaH+LIixKrFl9/SiY+fE9vYa+5E66xr2xfWV1RxLh3e7R5JPtlwV6xG6t6S3PqFyEOB67jQR2y6ttatVqF9/9LXVXZh60jvk6cLxp8iFBlVnTNqOWfXFcwOIWmalg3HJpnJxbQTMxxdvrthn5C3h8JUaodIW/POVWuwzDVH/TOJxukaqK5Sf1C4E5DHg6hVC5EBeUEIbvWP4Rggikj+oHGDqHsKe+MQW+xsIWDQLCbL+irzRl5sy9q70SABI35GMLPh2Vl0SSIHbpHWdBOZ/pLsDs3A9zzZ8btu2bdu2bdu2bdu2bdu2bXvv97qf+f7BN9NJO1ldyZGk7UrWTLObo6kmMtS1g5TaFx/sD0X3AGNqdSQwc9oYN8+Vu8K9jnSn2uuSL55A/RCsvOGGLa0GylGC6kteUmA/qWg/adCKYvaC8ylRzvydv2+/xY8w7CNGkNR3BBLhMfUEMenKUKb0BvudmEkQYX8Dh19vipstYt4AnXipQyBzo1r4cNiQ8hsxvlF/7PPg7TnR/UDOzWM/+PO79qDyy0CSHPxYC6KJ8II6QYTIv4B6GXk25jHdt5M/vFbfBmczlDOj/SnlC7xRglxf4nHerRaOEkZFMyee1OovFsKBJUZp3W940a5rogR51/0BxPzYz8UfoAZAqaH1NvwdzDDUUDhHv2QhdMOX3hqOmPzimoXsWXbMaC+vHyCB5mHFO9beD2YdbMkioI6+H3vj9fY5yXi3J9gpBvRcFeAZ+MKXnkz2xgLRLIcu87PE5WAlz9aEnOptz0YTOtB8YgUGu3HcK4XhelGZjgy47Zu3bBqOxJBy9RpNub+0O1KxJ0hwNUj7VlX0I3GPA8S3yXHBk1pARe+UN5oCr1tOkTa2EuRM4hqe7iIxjsZHETzZCVENVZaqExIEzV0JqQnyTI4zR0/8omeYafWwsky0f0s5UMXBK+riHcBGyHDT2n5eih040HhPIleQmB4uEKaXhNMRDfpP+cig2X3fbkotBayxAF4/sKX16HMV3AH8qXcUU6zRdorS/R80BB+wo7CmIzhW2TFP1pMHuq2cEcckSR2mPwaRY1++T66xsf6qLLClwgyYscamD33UjGNtyM91osKUZiMfMI/sQZT0ADKZZj3EiYWWEqR3JRMVoaj4e1D8mAVOYbt0KJGgSGE2FbN7mtVp1mtQPPTZN29mIY96ifvwaVC6e1CN1g2pm9G9unnK9ImHvkVAMaY1vD4hkpFhm6PiPHm2GQMfiSjDxgb9wmQ9C0sGjBq0a1DAgy8jhpA4O08y74OhYeYEACUeSgzqrN8tvVg8HhD1NrET+LI3rgbpLCwl+s3dSg5+lMLGca8LDutlC9aVgvAWUOoATyzzahftTwmaQNHU5UoOWu+bTl+jzFF+CxFYxT1/+Tpine3p78scSrNGao4ph8QLxSzvTyg+Ue3CuCrQ+/TWm6rdUc5NvzQbYFstHyVU1bQZfG2cWDxUuo0eaO2JCU6jY5RfplU5Ir2jAsLeiB7OnuSqyvRErsNxHXi1BePY8eobQ1S79fXTSDsNx/0/rhvuFqhAqXpKx+H1aEhhkm4p94gxV47pdcDF2YLkRHwUWen2Wsf3H7OyUxEelFBAY9dv3EdT0OUe6n8wv97IXid+tjiV/kBLX+uOCDYBHP8sEd/uSjQ+3eQ2rH+qig+bkiNhL/aAiv3aRt/q6Pk/W7EEk1NCHQ/7eV1Jzo9gst4xjQTsFtKPQB8uzsSGsO73JEYAh+utvvWZoZUArdV/cd1EHhzvjUgukMpG2DVQf9OZgiuoq0NgaR/9Yb2hdKUy7jUvQ+uH0BNSKkMODwg3j+AWOEQlByAiw6GGs6gZoAQMVatLEZvSd60jRuT5OcLJhFH5FOEp/Cttva4V7AKpmo8iLxy7uCjb/FSo9Qp2Ylx0Ql16YEqzZZKoGsS945fZmdzzErVLfiIA6xYD3SgjdtF6ZIjaEHuSbElQBX7sdGXo0hXHf+SP3383/MLIG7aacEbcdU2OpcYe4qdUkkStk2nvaDlbzsgSY83fzjfSCl3RqBRRInvaxKgkak/p42Ly+rUhkasDJ6A/RC/p6d6l0e1073k3sP3KGjOUZfosHHdKZg1ZrnmspnubLc3XSzE0WfnakZ1I0mYwHtgEKDOrlim++sgJcUatEZ+GjBzaApTGrrZO1th1/RR4PbopfRNRGEhWRGKUTkIK8YD2IlAVbvmPKEURYcQezdnkei/8/pBxrL34iofcIXAGOejNFecJGaFLBeybFg68TSkckIsoSDV5ueDKJT0PSaGvFSAAmJXCX9sfUpxIYtfhMUJxNrHJ9Yiy7PFZi2Sb/WTv+ZFhs5lXJ0r6XwPRqyJm0c7122OlsxnboaBnMd9qwBC0w0oBZRYk4s1Pod1okT/+CQRTUnQrAKk9pVHoFutpYk4kBTbS05n6wMi3MzkFG1J40FKBjig+JlVzBA22sCRV1ppbzHZikmtbOakiI8OOinLTakswm4Nqs0dyOPZMe6ZnH8Ifqn7j4Q8T9CESDG+IC5EWtYxXRxS2NCPwiVhZkFxvWX/yn34QB7PrL7b9QxSLcR9rosWlreWApZ0VoRQ6OOyM4LLT8Oem0MZ+Rbxot4NhoAVEYyuxKlp3CHJYd3jMV0+VyPWwoKVkOkrYFK0/Mo+pi8RRk8JihXLNjhltF71mH8y3CoqTmhdy4HdEq4UlNiu3yz8Fqo1FMTL/rPmuuXGuT3+9Q/w3N9yUyVAIzvMCTxEpa1nc8sCSBxBvy5VD2sw1ngS4iHDcfXFxZpY8nlDjTE8SKVwN7twapg8LzvvPJnqNzspNr8xluurYrwMF0HJPYcWX1eEYV0LpI8urts751xELPkTv6M5Od2TmsGw2Le/fnO9fw839ufU6SF/kT4yMH/jc7e9tXedOjG3TQfVBe1WtHlAU7F9BZ9gT+lDHniBDYFoqkTflUsC9leJ92Y5a556lNxSkLfTwSuGX9lvHMtLSFWHnxEFE3xjRIdrpIrxtD/8WMdzCktd13P3O83+a5Yfy+u0gpuY5ib3OlS6WfkGWl4C0OoETlI7HFRuxu+Zy6JeyO8jiDqDXcImm19EgpF88FXvC9a4jatLIAGWl/NuMOWkIdg0dNUFLkskx9M4oecSSm5zLRJxTda0BZ2qY9bX+wtO/6H1UZhkVNdSGrpUaLA3ImEz4AtlHe30HqICD4/FfOx4ig71XdN4YcCOdyl5VAq/JIOTSk7jD4MWjZAjH53HzVkGdEAR8Xu7fLA91W9S+VMQPaEtLD6RyZl1Oie8fK0LXupxvfXHeWWR7Ot5UmdwIX+A9/p50Y8R8X/gSwxLhuRm9azTbV7pHhJSrDe9pAUSowmbW/xT82Z9tygXDBdar7R7i0/MN3pceUOTQ6ZnVKHw4Y2hKTXhQZ9650vOMLIiPpBMZ2DrTZVA9ErvamVTD9brCCo8Bx/yjfnpH5PzxEJy2+DlR5HKeS36wwRftfjRdJYfHiBAefGLK/kbTVOMQ/hxtPxUmCCrxNmBHnomuCuqK8HJyi3yXPfFl+Sx9GKxm5V2IaJT5ELVqK/FCNAs/F9QcPheiw10QuOwhXgpbQG0XkM8556NlJzdfRw/5oVpICqP71zZgTXyQ3jmN5YF7a1NYjUXfOTPQFELMi0lK4UPEe1ozeeMzpA+uwmNR9U/z0UUOrgijGq0/S7xFcc4rKDG6bmVBEMqe3cJdNoWU/yYI5LzSL3nuhq/PpBe9eKMueJTqr0qdZZHHbw8scp5WJYBBKG5JoddJaoRcGrPsR99nk2E5Kdzi0zS9+mUZC2XKdTdKuQ1X8921B+E6J0ajmg3T/PhNuQC6MONdMLx9KbfSN0Xpnx8tjtTGpedF0/3DfRofqg0Kl7wJhD5UEKVUPczIs/F8V3PLUkr2oYN1BJBVmbVfQEyIfIV/vTjt3XJw8l8DXENAjYlS75Dm8cst8qz/0EZwbySyE9wAcZZJFT6QWxhwte3eL/c914qZe+ibFpW50UouvKzM1DJPyyacNEWpcuibbWiUPyLwn0kkkUWugVTOGSsFrZeRuQWeRgwCU63rQo/ZOI4onu4ux7+hbA0NEqBRl/cZMyVy1EybcWYrWZl/oWWoHE2Gr48mo1HzeV6MnFsMz+XCxmlp4GQo9ysy4AEQ133Tx1ENaevqRzqkDrc/wiLIQQh6+xbnN6qKv7C+zszV/7keexV+/aZggNUze2gx9TRnt2vHONiKZHM5k5/CDnd0HW3XsrtdFXSswL6DOY2V0tWn1uG74YJGtn7QY0Ksdxmi+Ry+PYHL3vNWGxTF7+zmkspAzNv5VJ21WnMMrsIZT2FG5RFFb4ASkf7wWChgVVLBlwD9MlpayLOBHlB+qqLJ2PlWYWHvucpp52/hNVZ5Rc22LjghWtuxFDuZF+misfo16G2ByOlh/hbaGgqGg8jLeD9Tc6OeJ22EwWhpS6nHoXbZPl3P8uNM0Ozij612u/wT5LlZpAbrELuNwDlmLeol2AUZfGzKdy5yx1ooLBER7MNnBVXzIAFSkSADVoZ7uJOal2YJXF7L84wwL+d3HvBrgAMScLt+gjwz1vH9kweqfJQMc10hMVhu4kj/1Dugv+yOKTf78sInwzE/S8xGurzaxyad1deHP2L91VUM1+22SQM18sJGz3Mhe6wLHsJ6hRqzf2rIo1INbqxCse58L6IzoFt0ZgOuFGGufC5HY/b8m+qa2B3Ue1Wa4KNxIXZoPf8gTFTX8ILHUxumYYbLFPI2/KjpY4u4oCe9Fh9b2tVTyMtmmJFc2bgvGwd9cIvvKi/9WLgmaz9cdTEvOjD4m0q3IDJwrYya0cQxxdPhGdgFugVcv2HHyhUm/YaCtewFeCLVtDQVlmLJJkawz4RkNcD7zawHWT4J5eNPMnNvrnZq2HDvna5N8UWSE1PsXRZ04q9ZqUOBk1tV8YJV0nmp4PK2INpPtS1pWCF21Ze8tuV4XZLobYZvn2J76Buu2dM8o8sj9SIc1BdbdU8KsuAM9eZxr3/V6Ek0ycQeLc3Mw+U+rzO3JgRhTug5AcWayXe4cemHynq/7zGWe1pn7SthYIcDLH2ZRBwp9o3/etQG59wvy+9ZCnK/Hd4PleR2P/MijLanrqj24oLeyomE8FZrCWTo3i36byvloAj1cIURt+wNjluYLc2VbZR1pmG2SVFxCN4oIbj8iE/zolQ+bsUN
*/
/*!
@file
Defines `boost::hana::not_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_HPP
#define BOOST_HANA_NOT_HPP

#include <boost/hana/fwd/not.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


namespace boost { namespace hana {
    //! @cond
    template <typename X>
    constexpr decltype(auto) not_t::operator()(X&& x) const {
        using Bool = typename hana::tag_of<X>::type;
        using Not = BOOST_HANA_DISPATCH_IF(hana::not_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::not_(cond) requires 'cond' to be a Logical");
    #endif

        return Not::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename L, bool condition>
    struct not_impl<L, when<condition>> : hana::default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename L>
    struct not_impl<L, hana::when<std::is_arithmetic<L>::value>> {
        template <typename Cond>
        static constexpr Cond apply(Cond const& cond)
        { return static_cast<Cond>(cond ? false : true); }
    };

    namespace detail {
        template <typename C, typename X>
        struct constant_from_not {
            static constexpr auto value = hana::not_(hana::value<X>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct not_impl<C, hana::when<
        hana::Constant<C>::value &&
        hana::Logical<typename C::value_type>::value
    >> {
        template <typename Cond>
        static constexpr auto apply(Cond const&)
        { return hana::to<C>(detail::constant_from_not<C, Cond>{}); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_NOT_HPP

/* not.hpp
An7kDW0WqqA5l8fmXB56sD+zlQvQVs5FW9lCbeW5/bWGoOZyDk1bgOby4AhfoMagxXx9f614ptA10eeM0FWYIr+A2s3XULvZDMYxS0dN54JQuJ9ON/X/AvoFCuKPQgCAQ0vVvQt4VNXVNz6TmWQmEDjBC0TlEhUQDCAQBMKAonCSYBkYDCREG/BGxJQWCudIfGUgODM1h8MofYsttrTVT6q0pW9REWJFTQgmUagGxIqCEjXqPg5qkJBMyJDzrbX2OXNJgm3/7/t/vu97HibMnMu+rr3277fXWntn092JdPcPeJej54Xa3/HufVLR9AekgukrpfnTZekH08ulvOmLpVnowwkzwQ85QgZN8tL7gA8C1ZvEFbhLnexhv+AFRoS80A946alOXcfrD8N1bXVqtHIwI2v3psag8pNJCApW2Qyo/AFhBDoTBuAy7vKRVS9J8HFm1QuBZKeBmC/jiHkFr/zM7Ddvgf5zS0JgtQ2jCFYJgQcQXYqLfeF7hUcbuKBEZU4IuOBuvRVRTOVWkjuVElI2JzfCD+2AE2EDjTOA1T+O9Uvo7tjlPrHLqrfcpwPgpuMPSZKEQC0SGkOa8iPaeykGsD5lQ2At+Nupjg5+8DGC61EO9Etbqv62gsZbaXttulNajVLZz0hH2AdiOc2s1XcRqhXUVh4cG04OJUd7FqhIgS6vKNLexamfy6ewz2IA9QCFsAbFMR426aSJ1UvqxQzShgt75HijmWNFLMdBscb0TzCyK7OGSmOZVVI29eIYgvz0QxHnaremmMokfqy5zSyGxLIYH5fFq8mmUsB8bAvYjJtNreD/CiRNCyVHK4oDUZoAbML1tnS90V0GoZgbJRTDCbS/kIzbMA7X/pQc5RNzPazqduQTv0w2+MQUktCrkww+sTHZ4BMVF4hPCH7cGh85xQ3EKe7GklAf+k/Ui5NQxgQF94PYeIg4Hd3SfoF9DJNAXDOsioSmm81wT5g3A0wSw8xmyBH8e+0JzaBdZ4vVejzbMIlTlRGI4qjanK14DLbiQbZCnaztt5uKAwjLJCIsXOz00sAJQalDx3yY4AOVZCZYp1rVBXZfjVNxr9OSbfFlcGp3nIeyyeXB32IPG7R1riJOQpBdjpQ1JMp9Ks7fL9+kuMuR7pTjHFD+Oh2V6C1ff50ql5t8588FyHdg9gTKM5hTnrmKPClkAxTBW6svtJSvGmjPutCVMKlAU01pxzXtxTFFDLfV/LDidoJgKWIaai1dvgz0jS6Xw7dJQdEJAEQsu9OkqPCPoNKpGjFeNADKI9MLBazk95wWrQBa5Go3r1b93qRF/Y3Rz5nR3ALtjQvIjMo5M8qMY0anOjkz+oXJjG620SPEjKibgBxN4uToQSJHmUiO8oEczakXZxM5WkKO/lw2ctuislEalQ25b70V/S00PP+PBqOdTpEDLWJJl+YTWsuOS8QaS+TqhEQwDJBOBqFEkrWDKBubuYihFGjJcK+tNlNa2VY7U5qKfZJuKovXARa8aInp3e3nzEykH5mK4XWLRgdzerspmfXmS/fHXpoc0yahJZjdDxMGDLyVb741IfqWnBU3YH5pMVXTAtbHFVUZNnhao6AdU2U8GRrfPe0hZtrvtUZLtCP6QvZRLNCVrvc3DFxnd9WvSW8/fun7wDmjUmFqnijzBOHyXgMSQlp2LEc9xuyjbOfzzghctKBJ2SSlfLBwUgo4Pviqj6yK5bq7PJ6UTuKkdOjnMVI6xiSlmQYpxTeJlPJyAS8do3jnCn7crAcmgFTgpvwAU+Cnc5GfkpIyG8HfZipmwX8vDHmzIZxGeulOVK+5rreBvvajZSX3XEPNqjWh4fVWG+0JVBFXaT7ZhrLn456YQIJdXXIrOjqHhvJUSCG758LrjvmcBMMT57JqoOCE1QE+r4IxczmdWJQBpDhMmw9hFvG8OD/Ki/OjvDgfMMRszotnZpWMySqZzUeiSY09rPQ7jBADagE/gu58NkIzlSqw44H8m0mQPWwqPe3zDgcoMMYkyHNNguxPovk2nQhyzbE4gpyOBDkdswjiQ+x1FkeQPUSQ5xZhBs8yIsgeyzozb8ks6f4zPO/BxJEHsyduR448GDgywjG1ZF22jix5hRBYD6XM8Y6XoOHGO4TABXiRGjIPh82t2UdzvFPXuYIB6tf8yBxp6BzpqjlSxhyp/xyp7xxJmDNHCDTgyWIZvlpnKBn/s9/qq053LZoKfHP9IV1EcpgkbP7gDLLrOBIJk48aRMbK2XX7U8iukeO8Wbtl7emB5U/DpwY+w74eWN4JH/s3A8tl+Dz0bXdy/U1LT3L9YUsPcl1vXBJeq/awSxbhTA3NaktNqdVT/hvmhp1kbqgic8N+MjfsYXWyYW6I5CeaG9K39G5uuIbMDTFjQ7Ui7yJ7Q0fU3tAgbD7h+F5uXE3c2M+5MbP7wjAngmZbi1aYMPDNJdz88FLSoG7mhyqyQDQr4h5t2vebH64yzQ+XmOaHVNP8YHHEzA+tpvkh1Jv5oUoIvhs1P1Rp9WQGqIrnRFXaC6b54Y8XMT/83DQ/VPZmflhzEfPDnXHmh/n0YoNhfmgwzQ9TTfPDDab5YSSZHxouYn5o0FIuZn5oIAyK5ofPDPPDCcP88K5hfjhkmB9qDfPDK4b5oTrR/LCHLX6rm/lhMjkuNCC5ajDMD7+MmR8y4K72kzjzg0wr4N+Y5oddvZsfsv9V88ObceYHR8z88KBpfvjx95kf4s0F6oaI4jXtDzqo+Bk0UXgP14t7SBnXX8T+cM+/Y3+4653/efvDnjj7w57u9ofK3H/J/vDb/0/2hz+N4qD+pf8T9oer8g37w67/jv0h9Nvvsz+0/qI3+8P8rf+C/WFnHMp+tHf7w86L2B92IsQ+CBD7jXpx//+N9of9/8T+kH2iF/vDzv+W/aGe7A80Lkm2vYfV+kT7Q/332R8ORnHWwSjOwmiY/RxnVZH9YX+C/cGqcZC1n+wPB1n1qd7tDx8wDnH2/HP7wz2Hvsf+cNepi9gf8k71bn+4y8h4F2GrXSxnDmKrXYb9ocG0P0xUSxrI+HATWhtaZ5rGh7PATdnnM7sbHz6Fy7gGUo1IrBqQWM0/sUbU/ypmjQjOsTwaGVjefH5gubVzYLkHPgp8/hM+DfD5e6Q7YurfiznifFsPxPSlcUlNyZk93C7nq4JrLtxM8shjWMFsfpSE4pBt2dW4pVRaPYq2RZ9M2Uxh982lJfWQsIC9PDtixJEfUxxHRmZXz6wt0FPY2Mkwhx33depSf2FvrYdt3k+TnNys1t5JiKycEFk4fjdRP+2usJUCb7LR57VdEXcERTttE1G1BB3EvQ2Kd6fitciZbN3NidaMLT+Lbi4yoQ8iOZzogu4t7LIVER29levEbyABmJMOCn49FbLqKhD2Al488wr37x2puyNBOcLQ8czDxkAaxXl0QEcjf0A+o/0cXqu4eYQQuD0V+xc0ZaVYC8MYB53YWim2VIrfVorfgZBUimcqxc468awVAFh2GyQ0jNoh+Dee2eWq2KqLxwHaBGdnAK5p1fAUS1/nvA0/FfxP0Nfrpbt9nbk8hNPXOQekp3OufE+XeDZUvmm+taJjsnx5MC+pYuokuZ8u7lfDigwKuzF0Z0VHNuhVvDNRtqvh0G0VHfdJYkXHA9LMio6Vkquio1yaXNGxWB4YuqFL/C50va9zOcxQnSswh7VSepf4WWhgMM8K6El6FrLrEjtDKV3us13uTtDboFNv0FF+v4PG3CP3V8Ud6ngF5Lga+mnHxBNTSzoV+Zh8ySbH9ALJOX1Wndipy3b4a4W29DVkwnSoiEwaBzRTEnzhh6U+2OZvYsSFUxcjrDWb0LsiQkZzEF7Ix1TvHtV9HGZrGD+tcHkQXhYZzqmPV9tQy79Cq3T3Cn5U7mX33eE6IPifQ4j0WAMtNd+/fjLOxVdB5kIA51YsvuqNCP67YFLRHoY/yiLm81rGCoGHACjVid9atQftCNjwIuhIsbnOMnZWKAV+Zsn9dXcrljU/Gx2RgY4et6BZrFUX9oqW0GzsWncrjAhxk4hTsy6erLT3DYoNoLbsnlkFQW9zUK5iG8lVNY1cVRG+Q4LtEylBEst7q7jUPY9bPlRgoKVq2WSZJlpAzPg56mY+fKMFfH/fRDxXE9A+gMWW3vLsF8vzNCC87uWFam5yW7C8abYe7x7pjL67O4XnlxdX3hf3GeXFOU/wf03WOssy7DSLKAQ+SijwO3xCqbPblvXI54FYPvlGPqcmoFCMhazka/lrY2OvsamxFwaloN2ROulKMzc5+WqxNdQX0/nVBKO8/0a1PzwfTf3lZF4cz4RYtffvNaqtyxZQIKwVRRFaoFjwb0rmgiYErkym6uriQVBIuLHIMagCAHjxbL6HHVV5zPY5kDeYd/voYqsBXSu8nZb1MHbOWHniahd7AlIqRoGT+sdac0MSL1fVeKT47F4om5QPX9bIl/rCqetSfeF+3GndF86Ub4AbDwuBW3Cd+7WSluyjaoPvE8et736qNtR02ITXNve7D93NDwWOCP7BSWYN0ujbGehYjMeqFHdT5d99lWszatxpkHul+HxQ3OIBkQUwdjNK5e5dPDQYGnWnh90K0wAg2p1QXwC1ubka7iLjY6sEfyt9sQl+B0f//i/NC8sihPGk4aBAXNDqgUHQUF3ub3jBXifLz1Oge7Q9tvgmy6u4eYnaLjuCa611YosOM3wAK1Zm8bDLZ9L0VXFTiZz2QkluXWAl3MgMPbBpUW3ovtzpY2XRf1S6ZVP/io4SaVrutCNr7JtqQvZNBzYdmda4dsT1B7qqhb3nhb2N6jvQcmr9i9ajn9UwW9CfjBk4M/Jukz+feDR0pbC3YVOjWgPPvGiF+0c/iz6xKWV6ifxLNJyV2tAmsQe0nJaBOBQlNwO6VXaCvrO/aOVye2ocCVzZ+CU5MtS5zRjuDXB5ejn29vTpi6Wp0LHlBtTE3Q9ARhyYUlJXbb3IViLqfZXO+Yx42DzItliRLdqfjaS84zDz4xZMLM3349YkULVWL3+1HF99hO+8D7pd84KyztPQ657SSsK0XF2C/9dRabmeBPIgyqLgH2KIjioeAzrjy7RofeFKHaRpw/9hiiQdm4JK1xi7PVvgo7GGqt1v4UcT+k8IgQOkY1i55Ia/q6Q8HNcedv2LJJSGXdHLVsrQGJapQhAnUgCSakmjsOOsreYLW2hOmaWsjy436vJhtqoReAtGDU8S9notRewunoy0MPqKvajmCzs79AJRtNdES7Gc4ms6BZQVCqaKqD981Y1P2lou/ZBaEqbjkkYpGaoiDcYqXMmroN1GWxCRsqhHT5sK77cwF+0S/HtIKR5W3Y3G+TxIwdyN2naqLj4SUMwaZ1GNR/AaT32BF/Ueqm1frK23sOZLW+iGH+l9QtcLe2Vgd1uMh2bAHTtL7rUWWAUoOlQmuM5hlP0KLPuSMVT2kM8oeH+z4FJS+ynINRfmv2UnLVz1/6eFy4E8EmQAJBs7TeoHNVNSkMTm2kP9KrxnLZJduSlkK1Vugvm9S/wmLzSZ5v8sBI4w1PNw+w2LPIVgU9nLvPCX4iNH4BFhr5DnapAH48GSDhhIgQkAaENXQfHYaqRa6QWhNg+7Hw0C7G7DrajBeqecitH5d8+I6FD67YTAt3EEflAN+s0drXI3IwCv5O5Ac4fbDSzNZp+js0WNSxx0sxv4Rdw7QZeStWdG6zp34iGAa4lfctxMAHd7AsDdHRTTYFApuF6xn2Pcg4p3h+J1Kt6nAOY+MSkR5v7x4SjMvbQvwtxtBswde7cJc9shDTtAZcGPjg8c5KY9zxtwtO62B2U7W9yKIDcPI0TkY8W5dIQc223i3IOpBLzQ7SbwKkJdXfHuqhNrIeHTireJUPThOrEDRm8YPknw+RI+5+FjsyDWU7xVkOZQ6rtf/zUKeSO62BSFvJF/HfJ2AuSdZ0DeXBPyVqktihfI7kkT8uYakLfln0DepF4g75cAeXNNyNvZJdoQ8nZ2uW0V3i+jkDfJgtA2XRV3q1MVmMQQ8u7G46cR9toUbyPA3hQT9toI9toA9qaYsLclEfba2dHvOOy1swujDNjrFPyd5GPQSCOnyYIAKgJF2IjeEF486KZFnujruBeud6yRkn0dDyMm2qlOpeIYhVJnRnxh6AVo5sPCIx541dcBaPk9QsvHEKJ0RNHyYhdISjWhZfRW8HUgWu5AtNwBaPmwzchWtgv+AKLlpxAtiy0+rxPQ8mZCy2Grphho2UlomZlo2UloOYJVvHIU6hAn1gnRcgTRshNhWAQe4GjZqbqZLp4m5HoQEEMawTAWlPezgjNRGHaC0LKdvXkdJUjyfeNfekfLzkqxw0TLPB8TLduZch2iZQZJbBI7esvzVEs0z/sdhJYTygvV3OR2YnkRNnZ795nYu1lGea+IK29gVxQtn46iZSehZWcULZsF5miZcbTcLR9XLJ/aFJ7P8yMNtOxEyWAcLZuvsT6xF/7TQMtOQss8N0TLEZxz7eyBkUZ5/41q7/o2mvokozjXjIxV+7E/R9GyEzQRq0NwDS0AszV6+qOgCYGbCS2DIDQYaLnRQMudgJZ3GDscXUk4G0QJ8HKkXmzieNlG4O+8lSevtrNllEHLvcWSTXcfpvHUP9awwSRexA0j+FNQTATOLQnAeUkMOLcAcJ7PgXNHL8B5RRQ4X59kVuZKcvI7jMAZV+C95+FbJ0HoPdQi5rRMLd4+HCH0S1EIvSMeQu+Blt7hYfpugtA7CEI78vI0XBEGlIkgus3EzHjAMYJozbwwLwaiU1zQGYHFBKLbeSH/TiB6JygO7YAtvh1zK25aIifngqonAL3CANDHJnUD0Gv/hwD0in8KoFd0A9Bv20hZIi51EIBGYYbuRXsxdLYBIO1s+7WG9nGOFwJdhgZ49FoOoJ3SrQCgb4IOBgB92gTQTQSgIxxAtxCAfoMcYUh0+4Zh3q8XnePx+l+MBCdfi0VosmCSAKMjAKMjBoxuIRiNbjOVjjzQzNoKANC52gMEo+0e9go6RbvaBX8kKjuTSTwbUDIF/+gkLj4AoQwYPciA0QLB6E4rKd8U1MbmoO6lHbZeY7RDFQhihwGkD5P6aSmXFsHfVdJ8HPIe9slzBpB+mt9eKQ+DZAFI/5z00XHVfVLYUWOrabLh+pf7ZGgBh9Mndfk4u/oN3PvzuLLoZGgaAFBnIRN2ckkvjL5qr2myF/J3mfScAUidcYDUqYqoaBBWW8XjAxadpLok4+Hfg7Ey9VdTZbSZBKmpWyTAgYDtwjBhRSE1ZheF1JibCanlKKRuIUjdwiE11P3zZ6OQuoUgtRMh9RcIqdsIUnudRWzGcwakJmLwwrO91QCLD4WGigSllEZe9iuw7H152RFSU8FfOWcUHCD1x5ArQerTFj4/MAuXCYTUDSDu2H0IqY8rDtzcMY8gdSdC6ikIqacAdugS25GthWZiZr/L5Kg6JRdRtROuCwE8cZcAWr//4tUYiE9KmQiu++e6GhDrLIOSIagUAnuheKH7MGrzEvxWTDoiBfdRCNnqHBb29Whzs9bQTfjU6VY03TxFdo8x7B24i8LLn5DgvZGW0MC6FEtoQEHoLx72GjxdwKpa+fr7QQ7UGauagLsGe5+yyleyzaO7Layz360y
*/
/*!
@file
Defines `boost::hana::lexicographical_compare`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP
#define BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

#include <boost/hana/fwd/lexicographical_compare.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/less.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys) const {
        return hana::lexicographical_compare(xs, ys, hana::less);
    }

    template <typename Xs, typename Ys, typename Pred>
    constexpr auto lexicographical_compare_t::operator()(Xs const& xs, Ys const& ys, Pred const& pred) const {
        using It1 = typename hana::tag_of<Xs>::type;
        using It2 = typename hana::tag_of<Ys>::type;
        using LexicographicalCompare = BOOST_HANA_DISPATCH_IF(
            lexicographical_compare_impl<It1>,
            hana::Iterable<It1>::value &&
            hana::Iterable<It2>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It1>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'xs' to be Iterable");

        static_assert(hana::Iterable<It2>::value,
        "hana::lexicographical_compare(xs, ys, pred) requires 'ys' to be Iterable");
    #endif

        return LexicographicalCompare::apply(xs, ys, pred);
    }
    //! @endcond

    template <typename It, bool condition>
    struct lexicographical_compare_impl<It, when<condition>> : default_ {
        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::false_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return apply(hana::drop_front(xs), hana::drop_front(ys), pred); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper2(Xs const& xs, Ys const& ys, Pred const& pred, bool is_greater)
        { return is_greater ? false : apply(hana::drop_front(xs), hana::drop_front(ys), pred); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const&, Ys const&, Pred const&, hana::true_)
        { return hana::true_c; }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper1(Xs const& xs, Ys const& ys, Pred const& pred, bool is_less)
        { return is_less ? true : helper2(xs, ys, pred, hana::if_(pred(hana::front(ys), hana::front(xs)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const&, Ys const& ys, Pred const&, hana::true_)
        { return hana::not_(hana::is_empty(ys)); }

        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto
        helper(Xs const& xs, Ys const& ys, Pred const& pred, hana::false_)
        { return helper1(xs, ys, pred, hana::if_(pred(hana::front(xs), hana::front(ys)), hana::true_c, hana::false_c)); }


        template <typename Xs, typename Ys, typename Pred>
        static constexpr auto apply(Xs const& xs, Ys const& ys, Pred const& pred) {
            return helper(xs, ys, pred, hana::bool_c<
                decltype(hana::is_empty(xs))::value ||
                decltype(hana::is_empty(ys))::value
            >);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_LEXICOGRAPHICAL_COMPARE_HPP

/* lexicographical_compare.hpp
ReJR2fHTx/V0YlX3iq4A8Pf8cGh/dIfuCymxZRJCO6CMBiXvImm1PQK3GBLQ+qYaDiZufJy5TmVa9IuLkATsQu82TBzl6IjGejQFJM/KwTYgH7ynrXwSLsl6S4sRG5Mp9gWWtaamRTyMKUubFO8rM6La3bE7HpW9UquW4nW9tylXqcJZrmPYUvVEXOzudEiSxRIz1SoY7UeWgbWC0VJZ60YbO00RsHoaP5AbFZTwNA9FV+7MRwx5ciAqcmIvvJZPD3N/y5a/k6pAd4FKwpxYzFpdLzecz9TALdDZWRzqldMMoxR3HsKeG42dG7WIlZL8wN/5wMPOEUCf5dGh4NJuohWVdeXm2c2hSXngWsK6yQRuxslZEC1NQX9rhXXqA3XpZ90DfRfZv1cekC8K1/aPJKDyijb17+RhalbiCmJa3yem96KscKmlMq9a4qyU2fxROntO+h5sSHJ5CVm17VGserQc/rsOl3qIhox10ba9JZuuoINbqxpUhydH0Qq9YFi7DBxYps3YhVy/0jFkiwAE+6xcjD9rbXfbnsUQsbYdrtoxReQP+cKqBWYIonFtbRHl3yTZqJr3JHsnnUhWIc9uwHKSDtEs6t4M0hFH2b24ieK8pMKhtsp8nZAv33St4LxwR9W7q0/bHuYW1nFqzZHU3JTzBs3NAQMC6hQWQPjTiJNHecpfilQXm+fba9e6kZ0wNnKWPpUDncJIrXLKV4uIJ2f8JQV2NsA8G7bKLRzP1F9EzzL5/6HqQLX9Znoo1qeKoyY7ErohFLoTgsxLO6/ad5SHEXCdJ02ySaQ6MCAYZXmBcgZqAjv9gmXXTkPtOYiPNP7nWji1tKrvuk07MmBLSZ8puXZ52D7QYwDpAEwSFjkFv0fKyeda6uLdIeWM3kOqm5ngNsX//bT3ZMBYVh5UnPBFMKKRHXsLmoJ9VbEUrpn6ePPCoQRPrBgMWIDxIGSE3EiqbG0raILwsAoU2aPKjU0lUORL5DPxz/f7H19BxBzFwRI0VMi2bPYakyqZ9xuJxgvtkJyHwYDh55F9CXhPn4CGMWPXw6oKePVZ+SgH431WarIj0zi996eqIDE31b7IQjM7FRiFtkZwXNwJFgFglHeJuUhVOidn7gdkZ+fF87m5ujJC2rZ1+JHw18PzJPtC7PiKkr69oIOl4EPLKKmSIpSQv4rvVf9wDZ6VLOM25kUZZhoTh8qSJcAdlvjO4jlfacWzxBJn/6TLTEiYxZTuiaBqdHNHkTJahoiQHG1ru210Llqe4ExdhE+ENCKdsS2sXafe9WNE3BS4d5EwR8vCg3KNNEzvpl1ppO9rlO/UjmIwQfEyTrj54UV6DtE0M39Go+RIIdaT+nqnNd4Cv/p2MPhvE3tFDHsEgZHhqVIPEfSowtw78Uz180Tv7WWzbSNhXlugBe5luxm0llBgXFtQp8DhKAzwmFxOCl5YJ4NLOiiqeaQ9EohYw0MmNvDKBDiKjsVSYw0crN/qO5yRSDa+xClH9Hb7tCpH6HZTJlrCDA0zdPsAKyyEX6DPLYSbFcSLHsXOWcr6zsMB+7HQeg5tybZtLYV5aAZ83GDlniazuh4roSzHwmDx8sgX1uARxpRHQ5oLwL9Hb2aUwtBl9YZTo9HhoKMlsIg2pp9Tg0WNrU8Y1ifGVTb8oy3EPBRsF3EglKkggo93F/YEwxP8+Ucv2u5G6YSfNkhUM5l3lZz2cuoz5GWMwX+DaJuM/Iin8yfkL67i39d8PNlZzvEhtqjW3SFbIRiRnN3WnAPg2NrIYsFX8887fzH3IaLLlGaavia2WKiFQnimP2DUJG9/T/t0OmB+H2tolYOtZpt0vRGEp1tuYA8RAU5S8mxNAJQv1Hc7dAoHSoxh7QkM1HNiPUOWiOewirKxS2hIlCP7ccThfCpEch0idd3tHw3fLTacCaxpHxr5DL4TbbWBNlvpZcIVBxxWJFn34KymIrO+dkB9dnif0exxn83hnr6a9tAyizapbDxQCBaUCDBtwF5haLGNUZ6OKNh23uRk7avG5sBoHam3i4KoUOkduoNcyltslChV9VKQApl8QtUx/oEy+7yU6EtBqgvzWZU/HcWRsOHDoyf2xQigBSwXefZDT1+tppWxD76j5I86SbxvCNHp77M8d8X72bdjHfuzUrOUN8rs0lG7s+MefgI4msCOuDzbWN/uVJhRLF0i3gIyN5K8HcVuLHzNxS8W0zoSRNVIbywR/4Y7NemnBrhO50s3yU4Y+6Qd0TrEE+xCIzl1rnH7VVh+qrMIo9LFDlmicGyGN6kl02UlqIjvdfnnRWrpHFOcqu1uYcD2U9x1BwQnHUGnXXBmlgBSb2FcvYBD1aBRigeuLGoNml4Ed3T2npc0plVvD0QuFGrs1c8DJJVLMk7uDXjsv/CiMZJnoSDriZKT8N/Zs3PzeHpU7xx2n5k+fQ53/O8ngwbk1UfbGnKlKgR+RGmAUEotb+c8OAQrWuqjNUzZHdtCHlgXMFSoYIdIa/PUKRYIICRt39Wo2PaTsPObltaQEQx/JInqpjylWTHVET1xaDKtoHMNH/gRIprCk5NNJ75nEQjfGUn7IvlnJaNYteCi5HfN6Bmi8P2IWtwE+LR4wF8yHjVlVwvRv9W2rh21G45Qjw2rtGb1rCwKdMbDkbYpCn5Eo8Bdj0mNXSLVS9l6RnbCJ1HNBKD5zkOiQo22yq1biYGbE69nSy0jZSxTA7cDFwaiyvEUxFRaYGEZP6BhsSXYT0vA0iTGR8+zKqelSpDTBH7UoBgTUln81OuO4QtY5PTIf7CjKyXPR8vNky6vhTLNoCh33Ou0b6xZR0/lEEWX/S26+Ne8Fvm4RuYjjgUuwMSoYCtlkUNUl+ppOzDzhHXONGor3fJNtvYRm8PJ7JWTwhs4GT5yvaoR0f2XLg0VTJuMWQ46HXCMnzQtJa3nm2aN7d3xKo8bIpaoG+vN65EszpWM8bim8+e4c7d9krdYFkrLg03nuEtjSJjLoW7MGEw7UKw0OqWfBlhyNSdQlY3c6hRUKJjLI7BHljVczyIzqMGZrGjC0mlal6JEeaWvWz1xlH3QPZgvuC4WXuuynjzUWfZbW9Bm484Dv9E/SVshdypiSjl5/Xe8I96IcORZ2EJgSyXH/ctReHPXJYHLq879ywvTLStRFgGXgLe3fLHkbWDVtQpgSqs9iIxzbRTAld0ogMu/d/3Lg4vXIDcPXQ3M+Vn49G0Qq2iYczm7wi+zO7kfvMxfGnEunuWKXcuUbc1Tvl/z061h8SOJd4Ag6QdPKae3xACkgahOPesD9wmkSt7EbvTVMH2B1fmJdqEWJwBNf14ZKeWMlfH8gQgXTkpXHDGmwutphx45CDhvs1c85evdDAgCBsGUi3LnnNTbJWBv12Oh5e6GbHc4K8jj0tex0Wtt6/a+p2w0NZuslQKq+JF+Cs2BDRxjTJBjB8pf4ejmxQEftTmazSmDPZl94BLOFgwH0LOuiRdOak1pJHoLQCxSb8NkRQKzjJ8uE5NNc5cakCt/ByAXzpSaZUc04EnWiBj485jxB4Ze636XIJk4DiHgSbhI3UHJyWOMN6NGDnvrFDA1dL0s7S9PSccnMXttPt42T0wc+IE7K/bsMGb+fSxsgrttsYHiDQyhBZvvh/VRTMqfB3H7dhn+37LUwAWbKJP5KGChkg3tjTxp5Y4iaayRaoti6T/aYTOJZ13i9MzvzhkztKGpOB0Yhvctkf+kXeEHQEo2Or1kDkcyNTEZtsBabXrCJ8ZAosMZTYUTk6SQOfOxEEPFUIn2X6IVosPn1ADNdxjpo9Jq90XFv+7syxZKhM6B56IB9zPQeaJbi8XkiLLBSKJlSqhnoNh3IFM7gpXP5CyskYIZoQXL/VIhxJjfTwQ9ON+4JgrxWfYYpckK/W56MQ1D0Ge/vQ/typV40djfxPbm06a882UcpfvG/alEMIdEM9Hgm2hgrTZEK0XiLphbqKB1Y1RKMa17opibgsXhLKYHBDZmwlUi2P7Qjb6e+AsRJfryZKhqkG5hhWc6hEvJvfKhOECpGwInT0kKW81frNSl5oScecp1B8g5omHCTr1RpIJZNo2WvhyTCQFtCj7RHmNnwp+x4Nm8DleP7yvOSsvnO05/4bh4tl3BLPeEoMJZWYh2BF7m6crYlmhqHsuYlGZbkSnrBSQpq+3FImZc3M8vrJwM21d777tedxoSAxTQzYRh+DjzxissvJ1GNfYDB4h41s3L8yhGVcggijl6Nb5l/zO/Y0leK0x1U46k68sGQUB4cQDz/DMNR2Y7TJO9rRr+9nJlWHBZIGoDi0zPJ927AQ7p/oUAyPXwyPKpuEk44GihQh1pmNEoVCaY6eXi/3xcYa3HBkyCRTO8RJPpXraMkGhJ/HL8+TeFv1qjXJs6yja7rd7nyoCfA8wvvYGfTz6LOCYY3zV2GRP9QG7/WROm9UGhPJQ1SA0t4z1w5EjR3pJqeULqmfA7XGKejkz0nei7NfOc+DjjB81RcNJDykFwt7PjoFXIHLRlBV0Vk8I0+rhnHdXnDoV3npzLIcP2YBz87khuYcLCtOocSgL38XzyqO+4VlrSGzlbpkNvxVyrKKl9pzBrPMS37CCaH+BaIme2mmRLNxLxpAerMGH8K6f5IL+vpMht9caRIjbQRxGsotmCvPzxHvtQvl/tcZZqVZtPmcpd3KMMJZ7+9PpzVgc4A908kbFAcTpcMK14Ezmhtm0PrXtaSPPUIp52SqrqmPWjnTfL/rPdKLvuteHfVZO3fIYLOVly0cE61U+nlEHHueIq1pniamBzUpO8CwU3E+F80e0nPEpKP9Ui042yDpRYaDvKcKPI6o8N4nOPX/jXzQ8eLWgOX+ZRxbd98kZY7Wfbj1cHiiBciA+eAfYbyncML2jUKe9l2eaQjTd6FpTdyqgFCw/G/JepOn+U+daIYDtsX9x1UesHWGouCwYWnp5BNfw7Ou+YscBWlTwHm6J2C7zZtcHiuy/Uiio3jKS8GzIfpDU32uJUf1OR33bPLpy33w+Q6M+4H86+Pj9aVebLSXlQH/JUXy/8gb47wWSfPva5/ipJhgr4gPNSn/3CLRwYawhNeZBBireAA/1oRNBe4r7+q7ADPY4SDkwYCrgQD6jDTZARX2rPxtgEwVanS2nknoff7FBtpJMNdBsGThzBD/vkUG9CFlUFLRiO5e6Nmg7MW3kkoZILgzWME0MuJsqe0eqkB3zwG8b+Dypv6BTGDW74uZG79BNDFPwDw6f8HUPlBy9v6IYf8rHRKmNn7B7r0sjuM2GFloZ0f+LNLUPt7NUXVhtR/5h8WqBsKJ0y2QDU+Kfj0tht87nx69Ps7NWPQibM7GcBB0ZmozvfyTpPZVAAr5wu7lafPXCoLXw4dPvQva+HwmyffOl6qxMYF4YtpBO9Nxfvof5q83huKwZrWBtGMtINPfyAqxb/Ksa1weokN0w3SxA3TEFdfB6TQUeVMGfjn0NDe/DFjrPnU9rQE3p77FetFsrrEJkILwFk+U3oFwWTLc7BLvvQTWitsFb0beg29JhPpesQ8rv1H/wt6GK+kE3oDJWX/uUbezp1oeuQNoPrkMr8XeomIYwUmW9QywSFT2h+pEc66ze1d3TOGZgnusEs3OEe+9NJ+u+QqUO9VZxrvVKRH8HhSIPvEM1HusXQT2g6QraRY/Nv0JU0g09oaGXI5n9+BhnM9izv6M15fgYp53qtoRzok6fa7k6P+if9VzrWFik+GONddNlOZAkthDALMPes1l7EhzarTk6OT8EZ8RUNe/YDd2g44HsQvXPAFvqCSxQGmy7QMG0qmdAvC1V9CNcTBELXCZ2ELcQY3ToLH8Q58kzk7h89ibtXQuI9mXqJHxB+UtdY38faAT2ELek9rG6QfGXFbhx83cUviLxtxW6wM0uPUN6GMnYs+FoLHcLqYHJFvUpjt4mQ2Yz9SqGbJH0puwPId3so3u4wvNxI+GASfwQbbobNL2pbrZkiJ7IJHftyLzem0IOd7/AK1NM7Z4x7STwsruYKdHIIfK/eFz9ZI6dlgaohNcJMQwMbLHiYogWYa0spgBpUGp+eFIQwUrfC+zCur8bBVrXWfkGM20YazC1F8sQwx+pHwtROF8ufSJeZomHtVVD0eobSq7w3UDD2ttdpQ9b6Ikj9AKLOfdsSn1aDQpj5iVKRTPIVYQUeKT5TLCFQpxRn/xGq1RbJKisRDNXXFml1G9GhBdUUkub8Nd0syvjWysKJDFDdWp1HvjqJmwnNBl34ave6niQ7IllF/6fEkeWE81/w2h/NXL5xWH0cat/uEkfJLEh72yNlOZP6EsYZpb8KJk1FAPHNxHv1Bb46Omf3QFFsADGstgcuEn0GzLRAN/UAt2UGqWwXxPrbHq3Q78rHMBV9ELd68tzz5/5xYQadTNYm82d6ZYi7bBHJmCxrZ7nIOFQhdZKfbMO5iRuFdCP1LGyUah9i/uJ4I5avlGiiMdK676jP1Uz0t9h4z2hWPMmWcmUyrcubkzaD/2qwYEyrlYK62eRn3WjPX7Tv/twi0ygBhvEl5GhfXbLaV4eF02d7PWNBvYt6IJGji2EyJNuSnGwjDHQHOfFFI+7wYGxaVwERWN+zK3LDnebX86DEXjkYK+42A+1FIvTvyN5t++epd75817rfqPXvd7UYybNBe3sTMm520IqjEtVgC7hnFnSFOuFUEO2XfctM5br8cLAHEbgdG1xD1EleVxbL31iOZuMPhtaHgTYZUhwe2lf/QEE/0f6zgxL1xM+VJ3ZqGIkf8dhAGvjT9XA4Q57OSbeJM5oAT6oIU3ApZbw8mN4Xv5Mv6bsbkhfvVN3WR3AzW1HBfnPwtxLnMGnUzzuB6plg2A18oAPeqHNFEKmUUjuX8m1a2DRnM/JZgnedjMI4Rzom6oqVcO1yqT818HbUNmMzCyHi0lYKQsS1hXSXWqJWpbpaA7xZ0lFAwF2+ReaZJK4tsGyBgoU6d4P0hzXA+esrt2lCwCrFf7kbvPF5K7cJ3R1HqSt5yPp04R/F1yfHEK2Gbp8cQpUFRgnzLccw+/o5M2AkLJnlMmGtqUSrUSg3HeO2l6jgqPxY3q1OF9bNFr/4FSbJttdkeWqRfgitUkkJXgSZ15CSBdBSXvCIoZPDzKJBUvCxI7bIo8pPnBerrJiBM+LS+BfhkOfBrfKVKSXDW3W4/I2YEMmuHlp7FkY7jWaFYDLsIsn0l6Jx68tP+d62l7N5t301Xf9A11zoXB3FBpRXQsBJnawoiM9JnV0qdoEvsGWoVSD+n0Ev24SKwL1tQAMPzKlQeUuKFrUCdWHq/A2rNMOEedYKUcTdU5SfS8KbzpiuBx6bVS6OlZzHPWsrjU+3IxQWhMwUu1jscthqk8rMf5Ux5oGVtbhzwhoPiJnk2HjA0w8Sxo4CNxR+KBOP6151AlaRLRInyHPrnjKwAHQlWIk1YP49lWD+LaWAu37yQL0l8UNHMbCRc1lydzuLGuQiUZLLLOp9Kk8fZnVyhhuGZSSMHNJGWYthqCOUWZ0S6O/r0mdNrOsh0fikl9iSwrYLYSHeM2RM01OC3T6ZJWpSfxyueaj3M/JdNVZbOvnRv02F6hafbOgPsXVg5qWFDuMG8r1Q+NaDsNa2QiqYVEAnEtK+kt/My5QV
*/
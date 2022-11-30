/*!
@file
Forward declares `boost::hana::fold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_LEFT_HPP
#define BOOST_HANA_FWD_FOLD_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Left-fold of a structure using a binary operation and an optional
    //! initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! `fold_left` is a left-associative fold using a binary operation.
    //! Given a structure containing `x1, ..., xn`, a function `f` and
    //! an optional initial state, `fold_left` applies `f` as follows
    //! @code
    //!     f(... f(f(f(x1, x2), x3), x4) ..., xn) // without state
    //!     f(... f(f(f(f(state, x1), x2), x3), x4) ..., xn) // with state
    //! @endcode
    //!
    //! When the structure is empty, two things may arise. If an initial
    //! state was provided, it is returned as-is. Otherwise, if the no-state
    //! version of the function was used, an error is triggered. When the
    //! stucture contains a single element and the no-state version of the
    //! function was used, that single element is returned as is.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Foldable` `F` and an optional initial state of tag `S`,
    //! the signatures for `fold_left` are
    //! \f[
    //!     \mathtt{fold\_left} : F(T) \times S \times (S \times T \to S) \to S
    //! \f]
    //!
    //! for the variant with an initial state, and
    //! \f[
    //!     \mathtt{fold\_left} : F(T) \times (T \times T \to T) \to T
    //! \f]
    //!
    //! for the variant without an initial state.
    //!
    //! @param xs
    //! The structure to fold.
    //!
    //! @param state
    //! The initial value used for folding.
    //!
    //! @param f
    //! A binary function called as `f(state, x)`, where `state` is the
    //! result accumulated so far and `x` is an element in the structure.
    //! For left folds without an initial state, the function is called as
    //! `f(x1, x2)`, where `x1` and `x2` are elements of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fold_left = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct fold_left_impl : fold_left_impl<T, when<true>> { };

    struct fold_left_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr fold_left_t fold_left{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_FOLD_LEFT_HPP

/* fold_left.hpp
5+02ZuZYKTIH8TBRXQkiN4/r1VqIzIy+ct/rbb9d112v5+3W7c0Ij4bWyhMx3WMhz1TToDWWJLUMQ89pvjDmGf5zZtNNCpqLOiFJ4ck44i1HtD9FIZ7mXzPFFE0dqZnKbZcnXFvOblNP3P2giz5Bwoi/zEOZ8H8ca0XMPH1qc6J31ndKvWXLs0VwYjD9yoEeZpaJHHwGC9MME8umZSEm5bvc1m0xmXWe9nFrSTY+2QCV5EM0po5FcwWjJSgxKdBJJYXMuQznnEd6uTBwsxVZBzfCds5mMNaaOu81ynF3WM7TaROQQFHalqf8HwArgNR/8o/ghpc5tiei2+0yNPIojm1zbCaZjMLqHVmpMzGE22EWGx2M6BOlEnIlpdxHM215VTOqqlOgbGNqwvjAncXtJ1BqLzyp7n5wkxsoexNXRB7Ygn0PNy8njKlxNmArOr+i283pegkAL8hruKvkI0OjDnnF9SIhUn8ltORAqCY5UBdKDuAL90hKtc94ah8cMJtWodkv7NX9a/Q1h23dgv/u7x341oAYWk6vXOhb1LC6mjkGQ9hvGU4Cx8CUoZOKuDSChMVDxRhe7mFzitZNrNxzXEjtAdcEUCHKvVSmFYDRRi90EDe0RJUy0d/7Il3uWqggyQGFAyLIDpqziCFEVdEshcllNIhBZC+jq7a+qsVMTEHhdrdRkFKqNa2uJn+lw5bJaYUprfREszpVzNGoYvqosmkVF6c/0d8IoMEycsHM/TQ/hJnC4Zolw+y2G8ANV1RQF5blazlPbQnDusO4bT0B6S111qD+gPvK6O2P0U/GSQUIGf3UTjGzzTTMJVFD7/7I0DuEsp2Fm+z3YzqSy7TvC0ZEIkmDRQ6VZ/DgxooJnnO6m0RzxeeYscZ5Fg9F1jjP4erneRyGsG4Yozkv0GybWg2EayCjZm34gissLNzn1tm8I15socPxDul2SrdLut3SbffuJ+1EkY/fXAfInl2tHHyPgGiFblj+hA/eUBbGw9f0OZAd7Qo4beykkTnemkgJy3LGo/87UNieEArmPmIXu8xmYM2mcGaGkHUJtynnXdX24bBh1KIqYEjC3ZYrapdHwaCmTFsw1hOkv8ADVE9MJsJOlJ1YUy3noU+B1t6MqxG7trM5HrYyAAgs99MZ8EZyj+BrPlycbAVP+nXwTs7tYNi03MPsGczMTd/PfUZP9PfcCX+gAzjNUIL2bULn3u6+rIqqlVdEoVgJIlb7YYcQR+eBQkXfjCIlrYgGO2fA32mdCfg7OXcnPfmFcv4Mj482BinUkeOXwPZg7rsILjB4ZWcc/q7IdKI/c0x2kMFrM1n46/bTq2s8gZoT5JfXeAk5C10Yr+lHWhr17DLpt8MQOEYFgE1nF6pADAIzVaAWAtNVYBACE0gIbiTZNFsvvyhKOE6IjxCcbASfQrfu3Q9MU8/eTqaOnSNQGftPUI9UoyGSTMZZFxGT83eywZ6z/IDEks322T3L43qjKWWb5JJq2bVPkFmofM1Eo5E2pD8MLMgZgzOkCMdNE+bDaSQRUfdSWLCSm30SDivug+luf+Xc9Bz1+GrVHNywLZoA9rV4ST66ykePZXN7IV3oD5xYwun2so9k7ZJvTpfvUwg/cQdK9G/W+vZ8AytE6LmG2YPa//CDAayv0IPCI4pY6ZnFIuhmV0OYkUzd7M//AuW5cP4ecKxw/vYwXi5W8XxVTZ0Pi6yuuMYxcQORo2qh/F1hpccf9YA9iON1HDdkW87faOMK96IYaLRqMPicF4Vkn85LJMpEZEOO44YEedc9Y45S/i3Xv0HoWw/5+UFx/EcN+8i52G8Mi0aPYaf7F+PdsNOh7ZZKt9w/2m8p2+6r+jtQnHS/YS/JnQw+wz65f7EOqH0QqPYz7HNzWYwy1WNBfc5+bkvVw5gZzY4DOOV1B7SKiQuAttJFAYvTY1GcZnptAHo97MlKciyh6gp7emefAexyqmFlTjLscP9iPLF7H3778Vl2kH+fIqeoISVtrbnXiajTc6iXObubAh2dYw27LfdTDuTw9lX2TQosywAVhjNzsk+XiSs9FkwnVKPTcEzZsWGcwWA+KFmhZL+NH0sXLXYtzZmJVDm87gDwegVXk1PZImgWzcBlGb+GVsktGojZHeingZd9EPdgnJdReG8si/ETxHJfnOM9zypj9zgufhs4UDtwE/R4TbCeLXOgZgP6EbO+hGjamlkDVM78JRI2nS6UUDUqqdp+U3mN0lcqypXCfXSR1T1xv1fd4yrIn52//4AUmEoR233yMHaP7ZX1tSej3tNpPXZpArAE4hWpQSvS9HyhOxnkHg2W+uJ04AdHuCfMPRT5osrC0hNi/LPK7AwkeeehJVnae8bJpaNBS0fhpIiUJ2jOK7hrGNXsEzO6Zh9OllqZJo+j2FXOu2RmMdPqmVfSoGOVFPKWcBfO84w3SI7HSLqPw5fKZFEgJVOwrDNcYVATttcY9uye8QdLzr1jnlIQUU4Krg8sBQOPVrZxzLSP6hw2oWNPN60cIARM1bcnQQwLfjPkL4KXAToEYrTyrpoBgXGCZHsATutfHGblF6Rk4LYgu/iD9X2gRfq/HUTko3K08fY+BVZ2TjPto3N7KJmlnDbKMtvhN8AYmdOyvybf2sxK017H+3eLpTkZ0x7KoZu9JljGvuoU+6qBTl/BPXYjL9CdJh5XzmzpzmU3ISfFY8skGWADZ6MMnaPOb9inYGAGBmYId3zvIfVOt61RdRLMsU/m3Fua8/hyGeoozGoeZgV9+FuhEnbpzKnGNhPVuW1yNOZsx0Zj05IN3b7XY0Pb9lawoU17D8iGCvRpLt7XwE0RZDUZrJ6sVpGSFSx6bVmZmD5OY4jvFbPtN7pnVkYLjclql3KVCPSSAyeI8wHaPADeFLfwDtNwGSuohRVMDBYwmRwsXjLt6TklHbBWcfojE5H0grLh3S2JmJ7OFExPgqGVMU0m2JhEtAxfJCJ624VamzCITdG4RpnhcbINdQ0SLIvy+Ok4DDwOWo1/tc+tzr7eFu6WXo99yfVbabttxFFKfLOCXW0FPtLToKKxfJxeZgKF6xWQ63mUrGKiahbplGk7PWH5LT1BuB/3eoprykeS5ImGnx1WzCe11ecTB+eTjw9txJZJIziBiOYwb33hmfwHwJCeoPvfNAOWcFmv8tPxk5T4GegX+3XeB23wbdcm9gXTQasxpNudPav98K7B6lu9yCUymd4DfzwlM/nAHxeTul3MUW4yJvpw6RoHyRVK0E+PuGPp1fGatvkVNMZFnPs3fYEzx9OWb3skrrc4r+IpDyyi7Aby4rGeTGRKZQJ4JYB2aW5BKwWENrE2O0I8HQszrm8LF2ac7rwGqdmdhddxQeIZPYil10HRjqxMORwPlxYt3OK8wUULQ9HeoJsK8YjzL8JLqXK3G9XutP4BSsCFfNPDbanNvsMFa9TX2p2rWSU/lh2FCChRb2VasXistEQxr0QxWSKVSvqCyui18Vo7k38LsMb2JMG/WPpj4D+F/RkrXsslfRsTe4xLmu5W0He8LN6b0Fgn3GV9chwAAvb7eJ3zD9jzJ9bK3i633z29r9tE091iQiwYCCIfWgfN9GTl2UVCbkuVyh12Ckfe031/xshjdmZFsx+UbzqAKBPpRDMLNnhyqP8oexdJFLW0EYNmFnLZm8sXOEm1ZLuWjHJNmu9xv1KetL6sHHILqW15+e7aX5eLaQk/ZyoV6qNpW7FJS7LGsrnImJVEcX18RRdgeZZaJqXW8qQjlo8fEv1yi0tYKSuSbvGXUl+yWdNpBzWD77RhOa5zpO53ZOYcVCsP2iuYD+k/xbpajyAbYKTYSu460vP0EkI4sxBc2uqWFK8pPTz73kF6O3VY3U7XldR5ovydLH/o12FWHAC0TG/6eB2WscCM2jLAVDoydelFOqxeQXYY7pmNkpPl1bpcdkrtQ6N0dfLej/SFe+oSKbTf8bJQ54K3iJEN9GIWW7de2JEEKf+Wx2XuGV4H2ShGRjzEsLCjJBkByq1+lAv8KDGFstNDgeyGS7KzDpDddjHyXQ/REi1SYcLu/TS0FX7zAh/+hdXwLyjBP9WPf1EV/C9L07/bw38TxFXqgvV4uNzIRwltUXbz75Lywr+VIHTzv8R9p0gCdVYj7duhDRZ5bYXnoanZ6lgDDy/68cHGmeq09Uy/PtSnaR1zitRfulN4+kt/o/Sh/isq8jvFH+cZirNSxnmvGOffVJz3Mc5Kf5xFFOdUGWegqN91qdKTOoh6Uk/1x3mW4pwm4/y2mM8HKp9/x3xO88dZTHFWyTjLivksV/mciPms8sdhHa6rR9Phutofh/XpnR6sbgNvprLDd7o/DusxXhMcRY/xGvnC5izVYGcFS/UhMy3XjkbLtZV0yY9Gl3wlXc4YjS5ncHlJTTS+1zyJNYQvCfHZDYEvEkMFunEArM0FT+E+E9h4gXpoQdb3bHSXa1ZH1N21QBm9guqfLb+vR3e9Zk/ONGj2tEzUzS30Ya2XWOsU1dZJwDkKQJ6PBBqSoisK7y70XVFwaUU2mZIRCcIVdislIpJchG4uev4/sPdtFM5PacheLYesK8cnofwnoqzExefPEImA7m7IL/8hf0km/V8aEurLm6K52f9lj4rDYc3nd/d56cl5AG3Q1Mt5oLbfO5bGI2m0IpvukRHFIhVRApoSZQC9iOFGwK8VL680OTcgy/oQWvgOr5watw4TWzgF2ri6EQ+4fx5WOPbs/C5M8Tr+kuzRR5o02r7BqPZkCDdieGSMJvVoHOWdd2N85wxUD0/1d66hnLFVBiLpw2EWcv6LXpkRIvcBo/DfQuLrRn9EtzrfRqZIJWnjkqhgKwdn+mmcOlY42zEXmphgQjonRK+9nUcJiFMRTEEEPFo4jxcpwbE/FHbYeYo6Wl1pEiUES1TQKnWCmEgRgb7b4dNEjuWDPlYV+nhV6BN+aIuCPgnhlgroU0Xocpg7FfjBEM7yFSk/UjW/R4vQ5YoC+BwS0whXYD9TNY1nq5b5uWLptqNtR6KtcLaoSxQNQUVY53pqDCSv889yHyMUOMazyWUIfvwh7DgnLjsNRqCOIJwVeNPL0jatyt9vYutgOP+AWQU3tUkVRpTmfCdWuYELvL5ICvn1BR9BKr++5Pt6j9bkfBkgk7yq2GXYr/iwXxLO74vMo3vRgZlH1hvhxwJ1Pynvv8A3z1V881zJ378blCok0OwB3gQJORd7vkvQt0DBRI1zbYi0Y+Q3Y0OFnC00Upog9sYgmxARhet5hhg6T+V0nmTZ5yvA+RIwpABDh1yWi3xl+TGOsbqQcyO5Nc5NIUZtomUZUIB0LbFKZIh1q28/f4biQQCnkgvRlhSk2amtQZDupogg9UzRdAg3tUI1mm4U/l5Ofh8JsohrNTv/pN4c6HSH4zl+J4tdN2L3Od0RvJ+p686ZwAPkXXKY6Zy7QvjEj/bx/erdTHk3viHQ2qn0u7HNtOeZ/9PRNzL/mDQRiDZl0lOEcz+OlUB6qnAeYN+Eepgz6HYTKZtHXTHzFnnzKtDYcu4ISaM7k6lbp7AOfZDeC5CXLDsse9rCkA7qnEkb4EGzneCMQDgJpMN6yBu0paaduR5moG0G1wPNuBIR6oNEhFANxaW73jAHBV6kO8CJnvMh0V8j8aA9edS6F3ndXc//Ht9vRQ1vDuyUKpXTGW3kY9zo+AQXKZO0kT94gSaBF0B/gQvHsOcV7rVeqjKjlJdjfdDdukiuu0lHE+HVxMwE76mrqymwIPWSjgr3w4oUZfutUn0N6r4bG2R1h+F+BNjpGvcTFQm+/Q8poqZ7U3akwxBW/lOuNTqhdlPIqRZQ9yjUqOFHNchJjdRzT0uQPb4nqHKCqO/8KlTUcTDIJufjCjszTjARP0ORvFYwETHQ5qUjXVkTmH8n7e89Ys/ZznPprojnTelQRc1anWKdCPUyH1TJwbax7w3RME8494SkjrRxEkdrD8sscP/+lz50LnNcpTVyMS6AWhug9VcvjXg6JpLyHcmYgOBvA4S4JEGDgMuDd61fLtYbRpXqTrhpgymkk7IQycLvZK03kM00+M/lOHgaY/xpJDgNgakMcSrzRLtOa9oULaTxrf/nSOtXQ6R1wP1f7BVzSO6uDzRxR/xClAS/LA1+VRr8ujT4x9LgNyysrqkPuJ97HX0vFmAHFmCFKPmwz/uwTzj7sWtMF05AA3eS5u2wWZq3wRbVvP01oaU092tMiV5nrxQKPyOAlL4vxbIFtZKgwODRXlCDoPM0s3lgWy+E1D2NafKtWxNwJyIf44c01HBF+2W6vLZUoxHrhtgv0SRRH9hnoR1M4mKa8xpTQM7OOsl4KcTG+RhkST8apUK+Tbh8GYvLlwYX1mRnuksWF62pJJzbvPskqGM2hf23XSXtzCdFIbPozlL+K7pPkuS3yXhgN00y+iwbqiLheUAeqeOhy838gAIPLomR4g0H3PcbkG+Xs8cH1ZOm/LaA6mMS8DUCHvIB/oiAB32AbxDwrA+wFwGP+AD7EPCoD7AfAdt9gABe233GBwgi4DEfQCDgcR9AQ8ATPkAIAU/6ADUIeMoH0BHwcx/AQADKlylJaVapFhOkUs25naR2NowKMHSd5xk2S6q8Qdd5mWFZiYeu8yLC3JujanO2us3U44D8r7A9B9mg4v/xUzN/mrbgNGmLgHU+ok63NlOQQreGgChXdIZbj68c7hmXK8JmVcHLVoEdUQlz+nA6eYOHgdXk7PRkL+mzNOcdxbc1Wqi+SgcAOtpn7dSa0nWFBL1eCeGkpRsR1D9ajLtTyVVa4C8g7muku64bjYi1ohnFwn00UNhKhK7hdSsyElEb1vLXoQWMsMjPAez3IuE2XZoyMfkxodQrMCUQn8myCZX/Pa/874V8GiRXiKHjNFwaHE9/T8B3NTtDpTY3X8d3ai5JS2IYsXVtGNH10DDhG1A8fZ9ewO5hgj8/B99hTBVNTc6ukDLkucvLfxdPjk3OXLZ/58xDd7komgfUnA8Bh00DlsJ3efDAn0T3XWqPHOe1N+is1DMVKArPsyF4pH7UyIP0rLcbRiLfAR5DLzTQ+xmyMIil7pWl5gdJYiii4eIkioy7j5XNYT7pANnRjBdiyKGBbrVIJG24DvEkwerBKTQgweZ7BPtdWeP0U7MM0N+lSOxdxT6HbfMm5rFetk0/t80At81SX9ucg20Tx6wWcFbQDh+zTKyRzd+3kCYlhOCKxwxTy8+oQd0C9IKoyWQbFpmou2axehnl12abUnotxgam5pQNSq86g1SRZfR3OZbv47K+9jbW51xZn0GuzzKuz3Jffc7D+ozB+jRqpI/QcnaH1F1rlLXewXRqSdDWEmRYJWpY+i1GcczWBHB7+12Fh/3lC437C0eImRDB5AjY8J/KHmw5e4ppzCzJC/rJp/jWPZT/DJ+pFZ/YlxQBO/e6Qda5ZDmfe8l+4Vu//Yll+8pL5OtDLduKA5eNtJsFSD+bsu9Fb14vRGHO1Y4EHwp3bj36cO5xm9GHm0tuO/rw1MHtRR+eV7jfQR+eLEwKXHj3F59d8GPzwosPeUFMfTVYU2W9K2r4zYla4YZqyERkStn+2kl7cDeW2gxrBeYRExtuZNtfC6vZDCuPZxws3moxdDXuEEdF4W003H01
*/
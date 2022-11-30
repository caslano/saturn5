/*!
@file
Defines `boost::hana::slice` and `boost::hana::slice_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SLICE_HPP
#define BOOST_HANA_SLICE_HPP

#include <boost/hana/fwd/slice.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Indices>
    constexpr auto slice_t::operator()(Xs&& xs, Indices&& indices) const {
        using S = typename hana::tag_of<Xs>::type;
        using Slice = BOOST_HANA_DISPATCH_IF(slice_impl<S>,
            hana::Sequence<S>::value &&
            hana::Foldable<Indices>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::slice(xs, indices) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Indices>::value,
        "hana::slice(xs, indices) requires 'indices' to be Foldable");
    #endif

        return Slice::apply(static_cast<Xs&&>(xs), static_cast<Indices&&>(indices));
    }
    //! @endcond

    namespace detail {
        template <typename Xs>
        struct take_arbitrary {
            Xs& xs;
            using S = typename hana::tag_of<Xs>::type;

            template <typename ...N>
            constexpr auto operator()(N const& ...) const {
                return hana::make<S>(hana::at_c<N::value>(xs)...);
            }
        };
    }

    template <typename S, bool condition>
    struct slice_impl<S, when<condition>> : default_ {
        template <std::size_t from, typename Xs, std::size_t ...i>
        static constexpr auto from_offset(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(hana::at_c<from + i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename T, T from, T to>
        static constexpr auto apply(Xs&& xs, hana::range<T, from, to> const&) {
            return slice_impl::from_offset<from>(
                static_cast<Xs&&>(xs), std::make_index_sequence<to - from>{}
            );
        }

        //! @todo
        //! Since we have the right to specify the same index more than once,
        //! we can't move from the elements of the source sequence even if it
        //! is a temporary object: we could end up double-moving. Perhaps it
        //! would be possible to determine the indices from which we can move
        //! without incurring a too large compile-time penalty?
        template <typename Xs, typename Indices>
        static constexpr auto apply(Xs const& xs, Indices const& indices) {
            return hana::unpack(indices, detail::take_arbitrary<Xs const>{xs});
        }
    };

    template <std::size_t from, std::size_t to>
    struct slice_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::slice(static_cast<Xs&&>(xs),
                               hana::range_c<std::size_t, from, to>);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_SLICE_HPP

/* slice.hpp
0UaNfdFIMCBfW4EESTBHX4DhFxamDCIGxEpgYkdVTUm5bq3bKeo7o/KcwsK/JkZ8WcT/XsP/NL/ObFhuhLf5szHaY5G2OvjM7jVK3j6qDX6izbyy/GSPuon3kvuxaGPfuSX4EkaD4opAEZw2eEgpr8IxEe4pnifaWvQKv1ONisnakMSSmMcjJ5VAEUGUuSiCnkscIwk5HxNNaiRJrinAR4I7puYYjkeieYgnWWDR9PtvEzq+kPh8vTNTjlxvwc4c4SmnVgzjM4vVMFf9yipKS3a16agGxkcU6171K403jF8a/eHGG983c+84YK+8MJxhP7+N+viN8J3mc+kb05dTU5SLU6InYD0nPu0QXlNFVU3EpOJF5akPfAaCNqi9v5BIFnNW9Mm0W51w6a+sP7UL89cUZZLFcdbSsVOSyXQmzXGsxz+MphQb+I8mG9s/G3ItYVdW4uvlrqlfYzWtG4qDB89mXuPbDYxpW+j2qjn28u3P16zs09VOWZsebmtHcNJh2HsVt+buTL/RUqJ1IyBEBguh5xZPu80dHj2aaLiQ8GPkREoLs+Z2FD9BpHEss2QcE3mKkagEJxKdhSLkhe4JiarIPKCXrmQ6kraNiSx5MrwF1BJZjZnfYNq4heQSaA7lVdpZqiWs5nzL7kS4Uujy8+ZonempfaJzSzDPbh4RuuUb63mqkGhipfwmnuu3eGTRUIZFRe+6sEjFwusNcyjP014WvnB6HjHzR3A//T6zG0Ks6b0mDRwLtOlWJuAd83hSyh53mCSP1MBVGFV1/xYday2BOSJWGJ1HdqC4cy1idyQQFPDP0zyZvWf7biaz0v6rNM1oh7AmaPmr0/Ex2V7nq0F1ThgTbYhIwCFAy5UkaIwqWeJxamKpga8W7dXF6ZeShnIU4J+pYWc1pwOHhjokUy9ShZQ1jHCXM4aiPgSfMCX9IOWJ3lVB8FR80rW+vbDtpMtcm8S+s7G/9djxHvRl8y0KkO8trvqdodIQYU3bOdbuWK9NNjO5c8Q/r55gmT9SyWpZ9K6bo9Sq8peIxBypCb4EwiyIP/DbMz23gn+R5hGnW97sLO/J7r1m2vY+y7AkmrikxsJaK7OlpNFjK5qRlSHEJaCEwLV9yy6q/b4mFveYvP232cDI3uhezO0Ng9ejbRN/JMB/kCCZiPtMFCKe95CoXQpmzt9XKqp+vorVaia0sfqS6SNoy8jl1SB3eMaIaT4ERUfU7q4knbQkCnxfWOWQuV7wEkUvikVTJjVVS6yB+P010hs/iUmZLl56dvKn0buVTe0ioqfoyIi05SugrrA8PVQ+PXSqaLasDa1oXYRr1jiCOtaHaFnFd6392s6tV+8na9dBtpdUFc+5+fUS6LXWfT7S9kexyuZ3C9rJHUt6AXqG3HHCsDE2Qye8tgdc+BVU6KV82LzbqZcz1VfwdQFkwIKeuaRajqxxVvoMbe21RW0N/5TfzM6N3pPVRMe9apUvuYK7ynaCNrwKvLPTlhjiPJmsycJWNJu4DNmie3lMbRHFcv0QrRtFDpQNBwseri/KNYKTGHUF4VQUX7iriNmB+wV21PDNgCRZNtZ8eJeE5V2BNwTgz+Hzuft/362o18ax//tzYHPr6k7RDbu9owvdG8G/nXdxAuHpOUHS0PEu4FPYUl50Tm3vKI8Okwt3DikbiBn4LHiS78fA70s4Oqbx+1tCk+0dIke8sfHeGmXSeGONTC209GFPv83Ku5ny8une1TPE+4D+AfEt5sie6N7KQydV1UaVnVXvSoU1qKT/aTePKIuumsagQ3cR34X/33IaF4PsP/tFoiwbkBoto5s1NPVhn93UDhv9Z6q96Nsce9820k2ca5jGgUaDqzJ5FpJIfgYf0AtPsC7lGOdfTmO/7hk1xV0TdyQRZPTItIK+w/jEuReEm6Bo+tcDyjsbt62R7N1DtgwBDYreTPx9cfd+HpGUlLnIU6KQCVTT4aLbcdu12/A3PWnHabe477JfaZ/qnytfxN9cgCYA5uO1YoZeiTSI8XJCTP8u6tHG6RVKu5htyllF7nmxaQWi6ne+eV8gUuMKRzqqNVQsJCfrQrUL4VcoQenOSs4/Y6d/aEEjtC1L2jYri7JOb4OJBsN1YuYDgGDZgbTBGoMbe6lX2zZ2bxYcvGEMvlcdFNFpFKmsWUT/vmpnCtp+72X/KdMTTRJdiIWHlt7hmdDm7nBOD+0lyG2xiihBt5wZFf/pHrivU9iYbmvbdHFrgz/bKFaXUS34pt7VvOZ+dSdX6H+2n9wOtjCv47lPHIPBC2BThEF4WuA7g0nqS5YMBstMHqkXDRweLZp43yEq7Mk78IbVhvcno1P8W75lShaakxtV+HLlTyZfLXuQM92hbH+FaVDCeCR1i26PbmPuthjppr7geg/z1gbefEz7jfht2x30HhM+2L2+MfIXHam0a37/jip3rIhbr6Ert9htKH3C85E8AfbEyIpsqcc3x1zNmW0lt03NglisQtA03gNbF8nxz+ifw7xrX3vX72EeU5J5wrTn1zz8OeCpgg5SDeS75VJdXIgePqev2j3BtQd69477Joxi2igvonS1+errB30d98L8g7U37PdZFLdzUzdXiPfi7wef5b7kaObtAGyWb2k/eu95SQCK+25u3i+ncZ6GwCpy+vXSzaiaTty95Y7uvVaFDWNzG4A5T5uzaBMZF9owAq+7HAvkeIhq90Bq/XhXxUtp2tTMAeZwQt6d+EfSZ9weac9dnDDy9x1hwteRMafedeqKsXRbeKWA/sbulL//OM0fS6+1flfMkspUq12uPvYrR0BHcp08B+0m0nfEQV5kzeiFExdGVnSagTFIhugFiDp9PbE1ddaw4/21N1LvtJORlre5pvScXBddaGREeubLkBTlrauD5iY4IPmW2nOmj6bnTPZOzSiT7s3DhD+joKPyo+KXCmXWdGU7wV92QfUFG826LfKXSmkYP8QHMbLCdcWiMs1F4p5Uq7uLs/pV0lt7CFlDD02TFqF/D7rKcefeHUjaipI6Yuqzqk1LHgW6zf8gWnm8bz1UP307+lkI6Yei7hO74Gr7KvNr+aNI9AdMvhVR/dzZfGl7SLYk7IJADX+pHqJZ/KKftu0a26N9cvU46cLCEngzOXQwt+qo+EteCW7ZXWGVeCl/d5AsFzkpWgX5KevHlA4XVkQgTZ7YKimoldIj4DVPw8JeCYI5Gwtv9LJm6gsx6qH1Sc3UHejLamHsswalvM5ef2NgmfqOXdMuUffPucHg81NSaZ+5CvWQlFPYF1iuNv7ikNwj8mvc0WEYN7Cb7h58fyPflYVuT5Dg84vSfSnCGWbz3PrdVrt01W8NlWdX1p2dD6dM96hVlfUJcfayONj0hDhFEv5XRAjFtP+fLEG1pJk9w5ZEfIX7r9vBnUSlJp5qmUrFQJ8eefa5K4Wer93liyYOr1RWE9qCO5uABbrbQd41CPMvhJ9KxuzpDeobQa+Pf5/mlfob21EkkpKEOsoyEAr4qfVWBNsQZnOW25BAg7gzbaYyFFo598nS86pLctv0dIXArtdt7GP5g4DHYV36JYJ+FvNiJjGv7TUsUTJihnwmrDdUfZB/4I892Yv/6eUcyZyRom9xgKFieZm1CqNUXG60xqE4F0yRlqIOpeVgmcMijyV4rDnhsCc5WS6ijihXXfs2u24k/6we+PLOod+RE1XQqzLa3YHKYwcJrMlPuZg9bhe1wdRSCG8jzQ1k65WzBV/qDCb3UdhtcbPOwnE1X1NSeQPRycTx/n3K0URDdeehBcxxDElVTGYBeihDfBNPZj+WF5h2nXDJwu8DMt3G9VQWlMpaWG2B2XZYcHqN5mxA/JVeA/lR2ohjTeoVNWUivSa2+KmuhuHjuzMZ+y7DeHW1ycAbGxMiWW95NycAUgFm1xOKRzGlWrN7lw+XKJaU7zILrFmUga3PHlKvKgnN3RnrS4ax9/ny6tfHzENHM3HsWFYFM3xtOCLUmds4uXVSIzSWPzMZjzkhtlAEDh3r4z/IopQc3c9COje6e7UTGCUf9B1rYrMblTlo0GOUmjX5jIzJnYwWtaOWGWitBdlsHtZYHiVZHkwHqDEEDgnKQT5cOIrH4dX5Azg8D/ULAT+wBO2RkuJBzctrIk8qNz7RsNWFkfBL2dlNEYV1kPikmfCi98TvttrWqWV4Xt3w27mhZj7C8PhDTgK8qPS1hKIK5FKG8lo2JC1Ymq/OwOYOO/rJsYqMh6C7gPsk6CNlxjzCwpCDcuLbn1w/3WOEuQb6LO7cmf2gXfLn8rnTi46babHutncP0+DO3PwXpw+eTajYdQSC2I44ZuFqM+TXzqhc3cIluyvmgnZ86+7F20phyApBj03eS5We4LEiWbx8+oRCzGKUZRVXLQSEXG2gHT/Yjq/szkjkfP4xiTWy+hyt445gJeZAip2/XhvhMcj5pLhRYfUcfQTiShKqtzoitjXFpgfkM4jdKGzkH8MK9smk2U2zhGPlPcPjCtEKj/xHAx9tRCaSfyrF/h3Lbhs6v+0cQQDMu+G9wYk3x3oPdn2Co29xn2iJ1+DfuL3Deai9415MedTl1FQ1Qs1I+JeY0QvyGSZqwfyhXwnjSaga3kGfVJbuMV2pubdWb3YfGwXx7UeULlrwiHIXS88ZHKOJkBe+2NbvfIkGXrnqi2LqC10UXRP6kIjflQ3nMd/ZiyvNrE+yqtwTci1b8RZubfID1oq5lGrMnAV/u8eQ7gmc/XjbpX9K7rlzmcJ7WQ8vgshyw1isE3zgzstHWBK3RcGplTLSf+Ld+s4MzK90r6zpkSRD8TEdGVSmSZzmz6vIs7PeBpX2ioUbFAN5g5iFNXPx5o5NzLoPYuP1GdDWrmLfX5GLxVNnYbvTLGqRrGYLq0Jq8JGeSM2Vv/iEULwXacK25W9bPDy+5r/peoEatojadfhKuQb+EqrzuHNhIRJ6EFMWb1w8ecZN220z52V07eYpupZ8jRw7iuqcngOHAVwsDLLs9dt4umJxnGM9xRvj8WKJd0hHR4xk8xJG9G92yg0PVjesWdMP8DonCA7iHjKgVxpxH15+3696JhzGPJp6nXT7dZvtjpsO7uQ96wl/TyDSL+voqI3ftuoEzgQFCbpuwdXkAjPvZEmHblQ/p5tELFnbu2l315E1/Jur0zrct1x6EJSHSXRm2OFxxMUvFxYnAvjJ9Qqd98paDXoc7qKj6lbxEv4bvX/zpq1QxeuYU3oMMq1CLhVlt2tv3eJG4EX33Y3rt/Y7lU9cOGTihNXKxPNG116s3NRUh4p9z7NXR8PNwIvaKZ/PzTUAdtQkNE7p6afwLMuwOE6fLNM6uJWVkd8uM1ZB5CuW74pbSETtZdZIcCb+ksC4GPMSFk27NxLwYlTUASusP6XCGPSwQ/Ua4nSA39yAefgj35IyU7mypwFZ5mCZmBnJkll+PCD8W4mwHF3i9GVJ/p3xoXkutUOl7RzfQNFc2drA0Zo/Ng13TS4BQsLNwedURJfCJ2B3zhjHI+9TIrRIzmlvwvPu9x2k94oE/ULWiUNvDQD4OH0c4hajG1U9zXYi/R3j0kETHZEc7CEQROtCYmVp5rykI+c6kqVB9QYo8zlIvWdp5+K3j1xpRkUojhmTjNdD5hl83Be5Av/gb9aNf6JJhgsF7j6X5GVbZJV7lPxuRYo7cGVnsHPWxYtPs+0Xc71joOMR2RjxpRI+xufLxkAZwb5+MgjxOxKcZVlxKhlx6KbZrMZWq24Sqeya3yI2TuG/AiPY7DOshoDvosZuVAPZy254T1ykOSbpC+ZOun/5erjfrnydzZbD6j8LOsZ2UU6SeCCoHCxhPKE22Bz1wRbuZuRjf9rL+wiesA0ndF2ki5VUYpuUZJEJXNo47Rw2eVQ3sNrwflTZwLv2Wt+sfrBlVR57r6w22zdufaRX+VyH0sAvWWG4wn6EHAxk7KnvZTBEn4sMFkXM6SlaXwS10wcar8ezkGzlBzogfqCizOkVYyVu0Dirfa4D447sBNOshyzmXk/5t7ZD+/EvAfoBGzPEnZPgieXdFSqzzK/s7gQRDuHjLCfxzutrKa7MLKVtNDcgL11WNxDtitf6AzNpIxXfuLaIL8QU7CLXZ8g24c/DjN6UnC2g9KJzQYLGPF1bBo4JxfP+NcVu5rpsyVP6FGuspAdKn7z5HZDeXy5zQHBe85X7iLdh7zRfoN9QnH8IUtVNXFUF4MFj6SFe8iexBebt880LdCN4egmxJuZ7zwNLmu5sxDfwObCNxVfRn4Onzu47BmqCaS5ygwgzj3scveqvbxjz0rZo02IzXQMd5SCtquF74ehD/xbCKL6Yi7Bg4HRwRebIyb1eoSXG8QDjyRI9jCOWnWs65n5K1QwwLhV2x3P4FVJVQWlbENr/If8I3zKQjeetBJLcGkaql4JL3GL0ww3y8Ox527Rmh/xXbK/SBN2RjVcZ/WWWgGCv2cwLWsugpqaa9c/Ta6mEmMpErBVFKzNx9sY2fRRRko0rPbZEvqHj0mmkfU/HnZ8v0m4v7E19P7zs2OVuxIhAT4Aftvy8TLM8/5e22EY+9+Zwv371djlNeqwpAt6QBDtqhBcm04s8nTpWMDJHJdW9a14bwrGs5OONlVaySZ+wrGkUw8dXf6QeUcH1UfMQcyH//KpG8WKJLg0e60LWjU1wqrE4H/7BzMNLQLu8fyfuuGtiZdY5IStJ+Jm4C7QO9tuZxRdKW2fW9d/R83HPFt38tDNWz6xpEwLxhn1yhgSLWIszI7FM6GMb+yMuJyzlJGvYDZRUDULv2YGeSD751sorz4+/W8fPbdF1gq/EHPzyxYW2s1/Jwc9opFd7fLXIYZLu0JJHimrA2vwZRyF2uNOl92vexH4yaGJC5vTvQtjyUexdzRJGD1+DvjLTSeLGKE3t2goUGkjWsNSGRzcD6MMyBu6NBeSTPFZ6rV5Xdi25Wfs9rmZ4ovjMgykGa+ZiTWwJlUooO53JYQqJEdaqiY6n0yik/35JdDDqpiIOwxX3m0WH0rRFiGys4UIA3IcA2zNksJOM6f+EKqoqSrnKcsds7Co4+xa07GVTO0I7juGkII4CK4ARPcFIgjT1N036I3Z/lXBgolyI8MruhODiGLBlpdPqTxZ4wl8+jCHiW+sZPzI+23TO0onCv6wG6edT5DhXJ6x2thPrr+lcUzZViaZzUwOF7CsCzDWdfyV8KRlW3zHhyTTitV+xlYucRDBtG9sBK9gD9Rwjxr3FfPncM7XVZ5xXbyvcUBbgni5wQXdXmTm1eesntWr//k2ghWfg8UrbtZ4HTZiU2NZbA6Mp3NnQU8WU9onakzAjptu4TWRHlm4ljATMmPUE/ZXVE8ayPfbIkmZtq77x5GLXGWLbbYUiDtSgJfUra1QC2zF6sRX0SoQbUpKqlgYBUgdSG2OGmgo65jv2q0+uP007kPktaUvMrOHBQ2DE8C7mExehsU3roKVtT7/TczYjObj0U+RY5UEF53yHCwt50X9+acnmkcs49TM1tHzM9847MXHM46FAiPe09FagusvJV6/txNBg67UKXyqieUhaszeWECBSEkuNh4ZYARkWqNzvweAgvqUTt8zs34H+XvYtmDeH6SJaJim8MNAVrM08FM34Fg9T7gN88hKaY2i22nzn78RF
*/
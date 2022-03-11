/*!
@file
Defines `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_APPEND_HPP
#define BOOST_HANA_APPEND_HPP

#include <boost/hana/fwd/append.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto append_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Append = BOOST_HANA_DISPATCH_IF(append_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::append(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Append::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct append_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(static_cast<Xs&&>(xs),
                                hana::lift<M>(static_cast<X&&>(x)));
        }
    };

    template <typename S>
    struct append_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto append_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<i>(static_cast<Xs&&>(xs))..., static_cast<X&&>(x)
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return append_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                 std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_APPEND_HPP

/* append.hpp
2Bgas9T6mLsZPk3wgWFDq85yyH5Q7CFVNQ3fNcSIiXHLf9cFaUd5iyR9A5m69FXm9rnizF8vCa5XguvCEynJ3H2BzrlWZUARP6mCwqEDRc4UoPC8QUjow/tWl2EJHoJ5fTIsGlcqQfKNGEE7WuYpdNHyLN6HS1eHyHx2F53uiWH0whB7bA+HB6RDWfKAY3olfNTA3+oo2GHmxbdNY8Sai9uhnAUELrGuEd0nS1XkLRYQs9LKrI0NgAkrEfoswe6xP2iakO+xz64rpHlVe9Jx/44Z6V5s7cGyVXYXzaEksrpCF2GY2BMiuxUdLi1Qut4gABYFHuUL1QIEYEb7U5QGYP7rsN2uVNG23e46n0bb9kLXheBnWbvF9XFw5sq6RqWCrtJZklexdiukzYCOlxNCN1qp1zjWAsTGulWbjD4lUsnHezXzWCknjhsqZl1VRyOH/bcP1j0fX9EYl4wSdAiA+Mr1TTxvP2IsT7i9UMNR18XO+SQeBK9WGQwv4cYzvkG3hAteBYbI0h08l2fxcLI/epS0OGS4VjxUF+spwVkmAd3CdmOmaYjFwxOCTA+debCUkyqHBDI0dZGN4r4H7oeH+Ekz7NDx6d+znr6lPh2RZ2etv5fJZ58gj4SfxRdzOnSiyMOvqaKI/flPFkWufxVZsDrOnH8wzhx1nFOILALeedKGXbRRNm7UDfzIRnn2J0kY3B5GXW+UrPWmTF1vYEvTGCzXBuhQ/vAq10sGfIM8BUbkUwcIe2tIKYQVp1apGQMMNkEKYFM9OWpmhxXHJdoKfQXEEftKeLby59XAwep98LyHPy9jczcZIW0uWZZZwhNG6WY21wcpV2dSnDzFlkm5iqfMSadk1kWHkvsqkV5hQNmf6XeGjfNO7zkBhbjcrt/eO5TEmPp2l+7tnElvr4S3NwLvr98YvmjcevPG7ouGyu03dHU4r5q2vQhWfGvvUNcp4y1xaR48zO490vWm8ZZ+aRY8FFSkgoucOyqu36Zrc9WYCumJ5zNtZrQ3vM3XR0kvYYugmsbeLkTO3JPGxjLFyrtdEmjnVZRhFUK62xiKrJaw8btQDXowFp8c6G12zgbu+514z5j4nf6o146Xj6+K+q9Rg4mslG+Ttwiy2yZ7zQqbNwNoG9gjOkVGb6Ohm6Cagq7zKcnC3IUJARHTkLT3DN8zPXxqByxpxfGkIO6LVzJvoSzcDy8udh3pOAhIWt2acFsQpINuq1HPHiqzSTJNj/YhPb5WruLo2liaCh9MoW/VJ7j/YFT4okUc4FzBSlJ/G4M36fSfo6p5jpLI6AD15jkwn0r7CCDzP8PIxN6jXW/u6Lpw/babMhq9n4+qGr3yREajpzfKwSpuwirmAhymARzQN78ODE9Dv5e6JsRdPq7XbUZWmoWBFUrNqKrLGxrM6PIyasNyauTIK/R+bavOEq12EkdLw2+SPZO/kZ0HCRUmcTg0j20vZHmRvuBV4YnP7pgZnjjRYV4cHhRcRzuU8KFU+LyxwwK/zd3nDZWwJy7NaBEeHlG1CH1DaS1ChU6LIAed5crnsJtLzfy2+LSQDudbR1Q6Cwylcb5CT6X4+umXaZQlum112YDeXnLd0OXxxZozHhDGUcnMaoQI6ULa8TaensONvaLS3ZGD6T4ENQ53kHO4Zmebsv5l4nAHU36VvQ3WGIzKi+eRhW3EfQYs05fxsYKNrrNbZ23svmQQtucDaygw3q1T2617RVXbrTuYVtu1G3Vqu2ZnUEm+lEqJ+4BpiE8eStNkjSAvNysfzQVyrLHA2JAcP0Aq+CXdD4BuwDJQh5wtmwCcyrsvq20qBzJt5kxqczu0mWzCzWBvnPjUTRnM/AWvoDzgOZDGTN2RVjlVcPNLU6P/cossPA79dbvOirtw/8QahPibOSuVG2ko1sxQQmo8B1Zjjp/M8SlWKMCW041rrYaOtyCT3H7ZuUk6+SbGidYihYq7c42qi/UGC7N9M3KM9XfmfDgS85wsHYu15ccvmSLD4kMD/juuGy0dZheLJ8IJR+SY+FAcpnGDb1n3KbyIirYV5LYAyNTiGgzqVO4Pv6QCY2Q4A4wMxy1Pn+9d/0cQ2y4ZcSLXhaqQx96JK3Y8fCkntBD9PnyZZJXwJVPoOsxdr+YKIXIzsYGH0zp4/GTvweOnTf2Ab2WswcoOHz9JF/BtvaZBvIUvC78GAPCLmzZxV06K37AErKXLncvNleQXxS7u+iOq+muIibeEPscAiyx7wucdMWFPyJwwoBovOSN8/mRnXsJwMkVFkXO/wuYibmcxq1rle38kEvIAj+EpOOzcNBfwEP1cd5zIONCqKX6R86F7hlevm6EdZl1J/mJ1ApqTHuNSth/w41jo043sHgtLoY9D5FsO5FsnO8zucEJwnetQWsMXjB3z4Ndc2NjgVRyRVZnRb07+rQaYoJBOiBs9rgpxlS98shC37lgqNVlHe4X9e4lOnhrMM6KhKBrZpvlOobKet2oPtB/iKbg6a3zncIr28h1Oj5I8SnznMK74vt4alLUF9kaygH2fpMkYSd01vuJR08gHAyYJfQGUZlr5+BghqD3w6IuZVjIshjcRPYpO3eITOQAf2W3t1L3/h2NqL6269zPrEH/fg++7rbLbEj8p+JS7ClBKwKhDSMvkIh7dyZam0B8MZ54vKt+me4bBL7AGAzFNEAhfVJnmpyDNx/moloS805ezNT1pJYqTD2xB4Ht80ki4ybAh2mrRpP3iCDqWJl9SNlkQQfzyoSaFWCrAdSjF/Da5eq4Ac5WozjfTWavXNlgtWtCwf0k4YUXv8TXEq8hMF3W8lVk7mor+rPi9XVOsR3gvvJxQAk0X3QJIU2yZ0MjabaVnXC8CFKvRoEPcjfo+wBcMGlU65tov7sZ7pSxkY8INpo9hBRVdMK7OabjBW7RU6NAdNBYcJYA4A0OHJ9kKr9QOGisJIP9xGAquEIDxxcjVgFcAGbiuELgss8AeEfjjqLyCR3IuDFdYDeJDfdGllvFxZIW3GYIVmVOwR46oR2lm3qQVbUXUYzRcyam5YmgO3hMjRXSIZHPtJxtiMi1eZufWxl5L/JRQpyyYrUecYRx+mBAHXjMlZHOiUkhxH61sZSHwvMgx6OwJdJtEKeGKXuhsf9QHsqi1CiduqGM/TNSkgymzgfnNbLGFCdFIH64G8lIzTwlXRKGCeHSFhWZ+P838DmCUqLMo04cHLUvvYdP0/+cs+dSHggctT/5GqZDV2CN90pzempnAOGf11syiQ8UaS4+OIxQpdYdVwbL9eHoGN2dJIihbBpTRF1VJBFh7G1tadOvGuzasFyMoHmo7r5vfy4gluRsjH2yvyDRz+pCKKFZdMzpEoTYkaAPeE3c+j/YlT6IHAQe1qQoWyh/P8mMuiscDz8/z58+oezTlN/x59kaUtjfeajJsvW3jramUfrx3ah3ZcyzTkZxJHXn3BdxlYR2479nYDfMv9lyDvj9uzTGI94r4K5KSgM+AiPHkG3cwyeB6Xdy1h/wGXWtig/GTeT5ZMiiHZ4EAMYHyAyyIkRS0FUB2EbQFThY4rP5NlY2KY9aZFOYm06Fy1RUSCyPmhRylfXjCwyRzrMJsOkseHt//CVsuLA73VYKI/CZNOaL2ljkctUG6pZ7LDWbXWqEjL7bECNIbrMTik0EM9JhnGg1XPGHo0AkVy15UhYqJo2mhYnO2UEG9UY4cxEki7gYr/xNS7mD1tSVG8hcHmIEebhxixIOX1gFXtIVbjPwHuj5Ptzb2grrTiOpayyze5ePo1uXW4Pq2r4uRdciMuJAbzAi5ZuCpbRU523RD2PmCOoQiXaV5WUJiQJkN3cdX0YvaYM1M4/gAFKiA+qI1s8afzAiytowgq9shXac1ceRIpon8SU08dgCFZ/TPTngwWGMxAi7IkqD0WdDIDtGh2emIjCFMUcQKWjV0WKXMtpzhRjCHNYjLa82KC9r1yTU2JYQ1LMedcJ1cY2ea1K8DdWYh9inBgwTm2kA77y6G8d08LQ3mWupuaphkpHVZq0tz1o4uzW+uG558XoDbm1pYNS6ycWkaYK6MOumJRZ1CSHdg8O4BVamrvKQeGDTDQjlJobt9GK0z7MFKeJm7e8pU8IsD6omD56VJCvJJpw4LsRJ4P/Yy6p87DaHt7HD8VF6d3GlQFs+YQaHHBHQk4nof38nJQL9xU6Vf+db0Myn2eoYAq9MEKAHlxSrslxHfn3H8aQI8M5tHh15rxjrGXAOSh/PfKs5/byH+K5WW9rkuhj5fOqz565cwrpDP9F7PsaAZb3657ckcOa8yHMerrafkTiE5E9iqD38I+EMVKDpp4yHuRtdepSnO25exBjOrvgXSO0H+ww3wFzNwXD+sndz8MQNH0xRwPJ0g8RskkUrXSMdPplShAxDopBUEf+iOuBs9Hz2DVi17WKfZdLH0A2A4vdU3lkCn3OGKJw36jpwYUjFCZTfUEWEKNf+d1BEzs+yVLU+68ZbVz1CnD21Xhgf4xsLXcR8BOfg5BPowAgQ9BJUeg/dM/bKZSYLcJuAWJdxfCcuzkqyj2Qher5YPVWWXNevLXk/raPBareyc0mN7tMLpYn+h6YZcb+kHz5HDyQZzuOJqQ0aqXaC8kyDYFwXMHPYLUIzlcM8o5bcOqnAfRLhjTM2KKfTYV9CvVPCwe00x3HaN4oL4o3FtSbYHt6KwhKvobkoMfpkf2B5WQvx5Jb6GL23hz4tVptucYbo3cO1nQSZl/sZwh9NqCM7Bv3ZDcCas30EzPth0NlpO5fSgqgE48kpaA1BvyGgAUGlIAPjGfpScSU2I6z8GiGzq6RvDG5GwBuLf18/fY3115hDUc6mvp6/9b1EoEbxK3DcEiUtvsF4aWib9HdPEJ9G7Ii1T9fxNrG+M1yn29EE9c1X6m1SdOEV1Iso86+++a6t03ch7o6uE0SXmkfm/v/5G6xsnP3i+6l/zR+eNrrEkb3ptBP984dYNWsmC0SUWfUHz6BphdI05OQNLmpPCayOvjaR5d2vLmgzQFii/3a9iTNMrmaOcDNfLYE3F88TC9aZyWQq5UaO+C3kJ8pk2WiVkjSBRJWDywCfYt2GczAo0XKgmRZ4QE4pd8cyu1qqY9qsmauWjk+zcVmYL6L0DqJ4TworJNeLv/J9MFPfZroFF8xpjTIC/nhz0qnVO3Oczxf9sNr2HX+eI9XlcN0V7llil3PDHlk6dnaX8vKpjPTKSuQKZgZU1vROxDtBOJLZECMc/dsU7r2NzoV2r0dQv7rNqreaI+yqp5XP4dTY8YHaNdl7//6mXseqbLS6lJahD/jMDKvL7Rqa0lEtDJdhP81jWupYNrJlC7v9H+lWcn0riAdV44xzm59PZ87N+QJ0f5R/Mz+k47ptofiY6P8tmwcAXwe51kdF0GMcMsKoDGC0zkQKJ1EZJtM6tduXu4rNz0dapg0CyX4VAdDQDAeMUENga5xCILTXrFcyTQHDF8cNeF7Z9epOzb/RzZXHpWMAxxtNA+KjIGJyVU7sX+rjt8aIWszQd99qsTpD96NM9PDErmBueKJC2QF7oKw2NpWdiIbQ99mBo7fwIyOafK+8UZDHpcsWDur3xh3F1p1F+4pP3xqE+hLUZ1lohvB/Z/g9bS8fW8qalf8HLircyr5WW2uMnmdeWcJehE/CEu/zn8OfohOyuVjMT7oohsripjE/ksKGj59FC0LOopVZavXFRi09alXDXltxUbWhZc5ndJI6wDNu6Adsib1fuctldQXeDjr8JzaptHL1AkVMroV1/tez2kLO0STd8Wbx0OHwglTA8AiCXPWbZY5F9VnTi4rGjmYXHKXuKZE+J7CmTPZWyp1r2eGRPrezB25myr0n2Ncu+gOzbLPvWyTC/vraoR4p6tkc922RPuxwlW4YoHfruIauZPWQ1E31U9RDDqtqz71/ThfcHMcQn2bs1sgvc4K14kH2jdt4rxVWe1nkv6/zxZMyhpFy0shlgbqdrIGhZ1GQL5qO95UgqVd4iNUZbttHdpPa9RumfmL+eWz+4LjCvb8enOqZzcwDX+btnLezLssjyOlwHg03R1dvhF/NXGsnShz3NbwtXF1yQ6Se0ECxl3soZ3mppnnpQ73fIvboz716t3AysaTbQTOrLl4Wje0HVbF6mHyK/Q5V0KrNUKP3ANUj+maezGqvfp+T/DRmlFR5McXmpddF2jF3qGMQlCARom7h7jPvkszOu5201m0ZK0f2sdQ8rC8M2flc3ORQSd8Xxosh2qxhDFCpGbVStXBu2+NmLykLE/QYbOeO+FH9HYMJcuZrZMWtuJisyjBItZDglJ2Z99BxKSTZWXW6GR3lJuXIaU5bbeqsXWaJLKsjBH7rnhs5UhidM2Clx18YUF35RGmKNID+CjEX3GrknWPS3BpKBB23+L5CRtB3NkP9q4I7KV9gYumk5Rs5sydv0S9wlnIdhxFYP2242vc9ayu+IXzQtcY3usMBLt7v6JZdrVM8VTv1B1beYX81wBUOWaT7nCoHfp1KwRXRTFOfQkl5/BfAt2GlRvBt3GfBc2V0m7ltuMA3V9ByTvWXBa5i7PDzh6JxNoUKKh6DU8ZPHgT2UpQDi0gGAiIfG3whLXyWq/hBGlcUHVSjAg7jrRn48WN6afW0fpP36sCVyTIz9Erb2iASG8R9e0ry6ZPTRw5fpo4OwPRpvhA0w2e3DDkbcd624z20U93lhBfGb4m8B3gDc6/HHKH6dKD3W0yevFSST3GDovogY3rkoox3+we9V7XDgjct02NpOgiD42WdSqdJjWHVP39O4yZG+ANuGOuWWj6fj3oUdjY/nyDUUU4UdCJ8yvf9jjNcq0NaByoMgXhwPT1hC/4PcajdZxH1tM7GHr8MPWBIrRXqgEbjmK+ElVgqZLeUN1sw2Jj/lmv8uJOHTVcakxTX/LD4JgzUFRrVia8jJK7aCCDGbhg4/QPasLKAHqrj0mGv+3/BNs7zcPD6GpDR/Iv18kJ4/Sj8/Q8+GHu35F/QspJ//k57N6WdGzxb+LJnH/42eren8r9KzLf28hp7t/LnTPH4HPRem81307MBnS6LGjELO+P+kNGe6zFx6LkrXkU/PC7R3cPs0jkpi1/wSLQ21OONvUFqZloZql/GDlFaupaE2hbQ4rvkVWhrqO8Z/RGmVWhoGwBq/j9KqMW0apKFz42TINd+jJWAci+TXXPNrtQSkhmSza75PS0C3p8k7XPPrtQSMuZW8JYOr7z+tnoQor/MUYDW16ilIGk9DTyGe6jHOpmGcDRBtjoZxVwNizNVjXFMPRy+rMVnrmt+sPRmSt2V68A2tB22vTzpLmdSLiSeze3ErrjKhL1A/vkfGcPuiyNCJTOH3NympK6wlUZ/ktRa5wSk32OWGIrmhUG5YIDc4FjVgCKV6cff3UZMXdNaj/cpztG53OH3Ez2qEcN/HsRUfkSoBFopvckfT4r4K9FdvNqJb3VfEfR1mYBm1IGyCCPoKmpCR7110FU4BIC50Lhf3WcpBQC83om/m96BweQ6J5viLC+mxFYLrQKcTBFqouhmqfpPIrh6rrjabMoSX/GIGisVPqVC066BomgKKv97H1xhX7jqcjtmrcLn6X+dSKbnGPo6jcuVuwIxZlPFtnpHc7MoNZFJDlFqY9LtyN2dSA5TqSFa6ctsyqefex1Rn8p9cucFM6quUWpSEbrQTylPqIKUuYOihbrmlMpywkPqkHmdB3NVOZ7NmPAYfrLEZQhtjNXY2wc/Dw18ySHf01mDgJ0AwmzF5W2/NVXr7+EJl2pMqV/a8loGQMAVX3vNbaoeOTM92/AR+PoeAdCWk1liNk51FfEAP/p/YXony4D71KO6RVzNHcblTHMU5oL3woLBC+vkUR2jqroIkoO32yAdBO5mkTPMp112abqCgUp/iP9jSkgjsz9GpkRlSVg9M6b/n7HD2eQxg+gZmomjbFEOiEbo2p44dTPksMOCbWEEjP3I8iIf8CcnJE65OJxSgZZew3YLGXBXGrUKFsM2VsSL5zm+5JUvpmUD0FE+TNzs3q3YsaY39tb8hwWY27G/O4DF/Qc+w7K2/Z1p33IDqZW99eDhVYZS9FtlbCXKE7LXK3mrZW453/vDab4W8pXajvMUnRvajQ0w6azmoPPUyXdTTGdbkqd0J2LXOdFzemfuf4AQSnrCL96LP9pQzMnSnw4r2XiHzuNlEDnMTbvxhGD8PnOopspF3C7LbPD6eg/seQaDtDy/yMk+apksa4EkzdEl7eZKFJ+H749/nSTN1Sb08aZbuxe08CRk79i/AH626Eg08abZaws0fr9KVKOVJBbokB0+y6ZJm8qQ5uqQLRkq6Wpf0Dk+aq0v6I0+y65JQ4mYmxDNBVd36slT7FTliDwZmrjCJPX/ArbQ15i6Ut5ihGtxAsgKOgSCiZGjOoVz/hDrBT51MWy1tznDBzCT/8nHAuCVoNTCDfI6Ra/DrWZiMB56h7QvrId9jCfZvvnlH2R31pkQBMnK77F7A3CWu/UiDP7jASc+9wKdE3gehzbuADj7cJVoHx9GtH29JYOeTBewZaoJRE0t8xedNE43K7fhqAVakNDaolBWsbFAqefWZ8dX8WrXK0o8vY3eQGd8Le1OpTSXKe+emG2Cj+7wAG/9CGXa5At/rRj22qMca9RREPVdFPUh3fZuMDWxIdtuVo7ir8tpZlRlIe3YOILVkLT0WnjCK3+kP92+Q/QJeSBU28nApqHyYBltzMYJR1KCtiVnit+OlqXA8j41Hzoi7Mb5orNlZDTPctkpxHifNrRkjuLo+7jgdSfEwma6PO3XT2PK4Oo0lumEKU0zjn37FHXzQxqEeNm3uMtS9A5tAf6Wyvxy9DMjuamQRfk84JMySPgMFmtkQ2jDVL+k+j9+yu1YKbGRHNsp+eLUWWGIbGhsU4EwI+vuBZcrze6nBkkDfG2lbUt2xYEm6Z3f86gpnVreiekMyb0y4fdGC5LduvenmagO2yJM2XJPsKR2+9aYvVhvE78SXdZ+qnY9hHby+8U247UktWeuweuHznRaHdS38/Zr6W//pUtO+BX//Gz5Pw+cF+LwBn7/Axwh5VvhcB5+b4bMMPs3w+Tp8vgkfdT9uPnBlf4uoNdFcLSptf6WhmhN5ey53rJjZ33/5svq630X3rJpfWvbeaJ7c48QkrvVtZL93/g2eSPsr3ZrRmH0=
*/
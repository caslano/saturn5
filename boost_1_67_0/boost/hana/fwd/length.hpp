/*!
@file
Forward declares `boost::hana::length`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LENGTH_HPP
#define BOOST_HANA_FWD_LENGTH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in a foldable structure.
    //! @ingroup group-Foldable
    //!
    //! Given a `Foldable` `xs`, `length(xs)` must return an object of an
    //! unsigned integral type, or an `IntegralConstant` holding such an
    //! object, which represents the number of elements in the structure.
    //!
    //! @note
    //! Since only compile-time `Foldable`s are supported in the library
    //! right now, `length` must always return an `IntegralConstant`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/length.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto length = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct length_impl : length_impl<T, when<true>> { };

    struct length_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr length_t length{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LENGTH_HPP

/* length.hpp
Q8T+4Z9wasBKqgvolipTWeHsAuHnKAiVEqCwQ0ZZclHbJkbD8noi+jGSkSmywbp9fC+571t1OQs/UNqgfA2dp3g+KEHq6OFoTQZYxmfMhgTY+rghyjy53nFJ1w37If0VhaB8Bk+kLIq5Xzq5aPHCI6lkZUJqgvOUR6iB8Ib+bL2hcTetbZjQIq0YT4a/h86bgU++mz4DF1BCGPXqRc4bFt5xWsZMXvcoZ+l4IqHHBfkbyC+6/zZcENaQNPUD+VeWkb0yspqO2ctUzpRB2bM6TvBxwS/G0uTbbseD+lWiABSDgjxL5nHabPwBZn64jXlHiBSWrP+tPrBvP92k9oW7OeEJrAylwE5j74FZrYWups9bI0ZHMHPf9s31+bCfcMdYg6uw0DsyFUAUJ9jegZe495H+/dOgJuU1UBcFQAaASS7ph1O4fztfJMXWEYQoMpEI27OEzFQew8d/gcpKmPs9km2BuobLud0QolhMqux2Osgo8sMj3hutB4Ttw23D6NUiffm01C9rj8vi0UDjWR8j1FFt9FDXh4dD/tBBvMGHXM5oGQ5wq5L4c0JSu2FdMLk4SPgU0O33OqR13Bne3MHA1iAYH7v2t9cqa2lAOXjwpKu3awpm7HYmku8BMSs3bgX3RX4bAQ4JfyiZ5BnKtdo6622jMSq7GfLgTPWTyJnZd1ukFSQAJ1ZL1fTGCtCe5bR9++EBCX7SdjrQeFUK8xlmD2c0COpVbQ3rqPXsZPmnbFwJ9SRox1ztho7mOfgyHuzO620nlK6xVOZ41Yq7HAveY2haeWZ9+Q4i1UmCikTYdqxMsJM29RLf/4JvS9k9y5SrwUwE0QFHmrO03pdKa4+txpmZdj+iBurVwFEOaKQxA6osvwjr8FvCEfd8fjaY2lKYb47SXd1nK2izZoWv1JB9WCIgkjRpksZ+crBWSlDUpKUVayK8JCXTHULMUsCyML13GR6KgHCk48Y58Jf7tbrOJNNUakyz9D/PBNyP0yud08GSR9epjWldJD82SwdUh/pwAQoX30MY52cPHJle3LYJufM61kllL/QjMNOHnwEe3YaxmWX3Dgg4eKNyEiGcwS/keoTdua6DNPTCNpbtIiFRj0QoTkmPThlWz7SEkkkQph9JvNXKf1QbluMqzNy3GfLMk5Kq+qA26yVi8OrwpY1cge9xtQMa0YVOnLFwDehWVsYjSdKRwPBXz+nZn56xsjfOFt2f2OLsRKgTxK8NxmjEJFw9JEft3+rkZOWP5uwm2wHQ3Inb9k7QaCXcsBO/JTrA2Xe8fEV2HtJfm2MggG3ccblTnVlV12OWNiqyZhqhn3Rz6cgpUWkpIu/mPyhRywfwDWieC2vlfW9xzGC+w8V+t8NdnDlsRrQ+dCu8o4Qd5Hfmlug4KbfzzTpnMDxFNjJiA61O8I/qO9gUmEC1SjQBRwxk32/1CQlKqG1p1Ice2QxHyy6A6SnHwv9z8Aa+pcxfLjQQam9u4xwWFBnenMNUvjeTwB1jKYbTZYtyEUB5zZbLXA2TzyIuVnHjjUEn4b/6S1/BW7j6pH0mmR3FKpN79E6Bl+IZIovkwt3jhyBRgxllkm+hg+RP28bQpB3AEAIZMtef6EayV6tvt/x3MvNrKnBa7QHveWI9Z23cpjWM844g7JC35AKxj3cZpl+gPvgNDRIUDwetnTGUwkWgBvaM5b0+U1/uR1wmSnPyr/cF6+Nm7luPBIZITM9RWzIjMCq1igsyycgbx/zYAIDxWAHpMsNVSqM+Rzwsuv1LO/WnOIGWP6CkAjl9CuievZv+8WsvXbyiU0WuyvSDjhkv6QqGpb7PAiNH4UhQKiCXDEaj75FqRR2hBPWqaLlJSg+iiKzGI53/AQwomsNx2OglTR9HTV9OfOblrmRSOkd2MA5dS25YAzr9PB0ERQsN3XYOh7lYlKhaML6W08ere2rU3VFQZe8XiLK5Ba5IyHPs5jS0/qE/ayhGlP182S05Rge3xjQWyfKlJYYblRyh7MMJBXrzKAM/8NSmn0DQEM3s/KGg72a9RDyyhZZuxEBTosxJZ6YF68ZN/GhnDj0vBdqkHnwHwZimHf7Xdi6YC92J4Mj+HvDgKgdCyNHXKSsxSP0T8FXO+E5H6a2RCWWVjdPIdUFcNpBes582T6/h8XxqSk5l8J+q2IWJmPSVvvVQiW2LatNEHMtObNQW6dWv2h+apTtY6vCkYIlCZn1BiA6a4jxACPKlVyZo0mvuiMF2dZ+DP5fd8XcWoQxPpZW0E+cKml5ZKaPK1Taf91NJJpbHleDXYYOqbzkaL9ihjpc76YJiaYW3zdHUWUbGipzNW6rb+HXSFNPUiiKGZlA2IUaWzj+UarJbtp1stKKlr24hxAfL3cF1omf270JoRn21dj0tfmech1lMyY/rk4ZntKtWkuvcjKECQGQ/LddbaUJ8KoLPtv6FXz1JHEw4q9gKwQKcJO1nPXtAt01XA6ud/RjeIq/oMzISAlHALZtaOeq1YYlY2Om5DwcaWEvr/mgbbI5Cf2AmLO/yzlqGhqaGxGhO8AjoV6soFJoqT4zKXPrAtFaWxvDZvZPLW4gK1ZMPaVjv0XtBYmDTD+a9oXNwCLJ+yIk5pMOp2s4wxirYJN5mnR897ZgguC+B0HLYtuCPIrSl3OjV45gXTOr7AFD+0NlneGwyPjnXyMaQL9cGBCz5SLjIxN0/IzpPS4So6ICM9TGdMYdcXFbM+vndvDpRILEF7l1AgLRfQMEYExKwHbN5HP1AyKfnNFNC9GRnMMA54PjOFncxkDNNWyMV6mWCkwRsOv9k1QmXn6JVzISvNWqtIXgzTv911df2tOCI66jvcROs+LIGJ+1PgSPqIH52KiF/txgxqZMiNt9MHkMkbGBXS1ow2+mFRKuco+r9blP7+AGNBne2fHhrSkg6bNQkd/D9WibnJI3x7CsajtxrvKv6G2Uw+dhvjv49rXaMrORVmzDedvtJtOZqwE5PTXlISwieahV2nJRinQGvEYFAvwrrh9NhCFrTpm/ThVI+5ovJ9iNKogMc+Vbwz58rfo3ky3P+FTAAvrOPAUHzEFUiSRlzJrt0ZAj0YJ/eWHNQo57Pi6eCltAODGFiCM8wC/VwAo1nbcFYEpeYv2+rY1uUapPxWxd32xGdJzqFagZo2MBjhT7M02ckGOfpBgep1SDA755hJWq83Wo35wwgIG74m4bYhzeqoEmMJL1kbM6P/NE34mTVy297+/2920AQtnyYlaLALy2nzaLBnje7d2hvKMke9Arnpw5VKCFn4mU0tVH3WZAtxcJkUU0o5eSJwIc2sbo37MoXKkMKmN893Ys3SJ/bp5F77nCY593qBiSHSN3ojdUnC5jMkHETaSK5qNkTwdHhJRJ39xZMTtGK5mNhoLjZcWiAt2QInlRmwHZnzCCt/7BaXiicLMcw8eEZC47Tc+JQHaSvhasXO3TUU90n+/M0jZyoH2hoFi+fcZFrCZW5I7OvnWNRRHPmW5OwDSeLXZd/GWRAyjMOUxc82m+Jk509dBTXW+c4KDuxM6J9q6D7FdtudRcfsVuBlB4zmO5IJNNf7V7mcNGweNGoZ1RJ+9wk6xkbUUh8wkrSd0RMXul8ubXkpnhGiMSbb2tV1c68xheZ3CRbMTYScO2o63ojKSNg4ZDm20RGrolt8c6mi1kdeVAj/t2IUl3Vb5uQhOXmRfgr3DvkjopKIfNPl+ITJtOZHEKUzbILtfRjXyhQRo9DPJhjtEXoV+utbhOaAInCB/+9dE9zcX4ur2L9VZiM9PJHxRfjLgEhDmD5TeeCkY0Da3uIFV8fJWl92Jg9bTNAmB28Ef8q7Nr1Uno1gTKzYoSYjM5mP8VY2sUKZUtm2A7dXXLTE3UUiM6gfdMGmPBSKvpboMsDpy6BtiohxqMryRN1Nnd6zM889ya/XToSd2jsxKNmvhnMdEN9hPfALquAh0W6dE6SOmxVvzq60vsOK7FdNwq9pflwL7QN/Eoq7vsUaMJZ6z+hD8Jg9FKfPZGGm5NnIgWxbEum5/zesvW42GKD7Stm128v/clWjqy6hEtsAw4t444Et7csIGdf0vx0VMucP0ZHgRcBT06U6K+kLRw8kYpqt1kt24h3DAHoSuEtq1Aeq1usAgbPqg9HgNGleUcQas5s5howuFsHBz0AdVWK1H4pLd0UNo8FJCEnztF1W77pRo0jJPUtBaLaE7crlZe+7IhM85KdpGm+LrDGiBtGU2hgUwIVzKPDhzwU/MdmKHRaJxp+XxqNyXa44SIsxYkjY/EHVax0Qx7yuVBxur3dWY3FIbwBfTrqoi0YxYmELwHz987nfB5V8Mykhm6zO72vsRvste5QtgRRaNV/W81anoWJy88apEabK8D5vEKO+wtuahA3M09G1gorApP7FHLcMypDKE2SNV9DpL9BkGdFzUPREwL4eRFW/kivR6wHm/ZWRZB1CO+eREDIR2GCfUTKZUcjokl58OU/cFekD9Q9Q2483AldwB/7rl7N6O2okSrZ6Oms+KyyBFvz0h8cR4Ao50zebslknzsykQNeczfd8BxC7rP90e9nHs7VutEm/ZvE7L47fuiiJxzwDw3Aq7LpVHr/rROEBmNNCWoIxTVnHDc8XfTgb65iXqpOLcVV+2GeRj7i0SwwBpNpCT8no3f+khTN/owgXUeOUI58EpOHSLzpiGszmt0Uq9o5zrVZoHqlsB3BLTDcB0qDQBNuLpVM9Om8CrCJKaQSQdiXkxnUeivN+aQAAjBdTjZC1pKkLeTTBXQj6GYB+nOxw9H2Vsv0TIXXAwYxpWaM/mAUKywjK5TmWJQS7UGKu0YwiDSQoO7ULCM7HVGtNHDNhJQnssKbWTa3MAHGzwtSv/gn9m5XVRwQdb86PXQSWsknhUugZ+9TRyGM1yDlYrlh/vKwhWIMOtvdP3O9d7koUdBUArv0xeEVa+O/UGLvHRGWxW2q508x74aZMHnQsl73OcwXMhtAHPL7ahaEDN4S5Py0ZIi0p5ofHUcXyuvMSdWN6kEBXeYwidhtnNDFriWvx7wps1bxSH+XYvmiEMJ7sZRGq6MzQ9jfMKqKxxZLx0nXtlfK/WLXB6sd+uWZkAkM8FDguq/u01VSmpm+qT0s8VWHnyQpFONCRPzp0hD9Wchn5yCK4O1HGA9zsiilqrX29EeWmzMnDHa6pFW3CXykKTQEm3oc4duODQcHXHScYVxjrUr1/Ucb0we5JPaubw6jy5onx8jt/TjCUXf08KQN6uQw9vvSkrp/QMkXGKT+OCHACKmPASqXA+Swlv2xMtKbDBp0HBzFrFAuOtvF/Yd3puRgYXGZfWj6IM5J4vBiCtC6eHJidpZeZ0Z38CKV+PQW9W1bNlVcV0hXrPcwLAkdhYQIEpiwSmx5HFi9qQjvoIsJQLNKa0eg1aGTHpHfW1Qzqob0Uzl/NUrmAeeP51tRWE07WknD3gj6F8oRpvIVAqa9wfODSHtOxmROaazLbuiUJqSOJY3IQq1qmeI2yp8BjRGfMvayWQgw7VBMZ5lXsl/geniaSVh9yzPnOxoJupDz1AYms+xinMrQrek29pXW0HFVNI5GQALtWoJyQs34+WAKs+lMwSh/a1jlYXaBvoqBYbNty/cl/NZRis0+nssMiDYw6kZli28zQVx7mdXd6m66tnNJprajXZFWqsexOupfNsJ8zE2wSFPpajY+5yawMC2uQM037a3FV8R7p2lMTSzYlBbFpB1PXT0UBeN653L5NCsFrYtR9nexvCAxsQlvKeCeOe0XWyqR1s8rmgF5PR5LXdWeWQWHA8V2IoheANBQ2SxvWmH09PJkU4pkWFLflV0Iuv0G1mKh/1v9VU83/+w2ds88yVNYVvfYd/M1w0BdGuoX9LRmtwfsZG4fh30l8WGumDHbhrYEpw0jCXvT+LNCupcMjci7+0gI0MZsUIgsm6TxM0fz1ncHpwLB7GS5viaVXjdnRye9/yeae8Wyep5JSMnU1hcyYW/tdQ6cNsAfgVm/H+cshFJiXH5aezVmgKICnDIhQfGZUutbMzAqK/GUgDpvKUw8d0Ts+LKFBq6lhPhdb+CSAAZ3h64MM970EwN6etx2DOYBAxZNurel/kVuRH27WJZ5hPu9klm4z07eXToFsBY8ofzcf6wVkZJm762xH5lez/VQA5nCb7iPZ0Mtj2i+hrHzLtVJsc18cGLAePoqggzvVOyxRk0ScHbA1dYSWSaFw0Ov8cJsC8FqZeZm21ojZWfZAssp7jV2kxXFaQmihkPyk/UBqY2Nj2tfu4jaS0XrccvOoBc29mO65GUTU04nSl03Jog+iBMY2DotVEX+KOSjxFcjMbXrF7239z3670vujTp839k4MZ9zRtNjrMPX4ZgpKEDuEAseMl5uM8lQsFrIGjMBBSW6elzq0tA0cv9U3xfjJPUajjIE1u2nCntTssSrGgtrCZy/rotMFv2A2JU/QWKJcEalnXmUbgTteGW6GRf4V/W+RGq5I0mAQpSteMYkP/iGFARmg87+4lkOyBRgjHPKfF8o2lZxFmW1EQzApLMhGA7eaivmsQo9Fu5bax5pnwXgpvGuR0CI964PCl2hSYA4NJf6dpXIUy0rrb+/ptX2iBgvdGfU+RGX0zuaX2IZAEPgN/ZgcWiLlRZs43g3Mh3QRxul3fuMdvalCMU6xuywM8rgKrUgvawRHOgeDzL239EK6v31CY/zNbRxdiNduXbqfrT1izOszRLsFvQp1qOPvpgaxs8ILW1yVivojkURdizyioTnc7Gy/Jx3c0OWRJfM4N0X2hu30IdJRIg9kP7C+jotIW7XhSdxxzMvw0VG4OOka3ocB2+ZGwo2TArK1VqBkm9v+XMCCsTHDYNUf5x96Ol3J7FkX3l7amtzhXYC4/QkE+pOVe/kJ9sZtUVK6PEMDrPSDvbUC7m2SSvd5/Tt5sEwSo121MUlq/C9CbIyRo10MsAWdkbG9qVWvepRCiQUVz2+r4r9rbCM0UwpTHZ0TKkRaBDWVd2A4Z+J4z641OcenVffOV9cvC/BkkWbKQzUEACdPFyfVuWa+IfHcJjeaJmfH9CrwSkaTFjHGdXBgwp87A0uupzoENLGpQvn9AFkS/ZHusG7Z9vnloHMQvgPH+A003aOOBpFxDnQyXKO2b9/S06wtdpYVSKnGWxBMaTLPBL/kAYkgHPQRUu+WpC08LI9D5V0Qi3ytgI1CPR24gq+teVcrE4KL0vTfZB1FlTBsZkw1xqAjfwif8z9YnzDVmrAMN4F7G0WM7fgyjwGxE2IUTjFV4DxpNhkxrTpBVGM+EkmilIdTGcnGdgOm3fbxZyWrnL886OFY0g24rYGgBsKvRF4VGTKhmXxMu5IEEQ+p0YSRsxWrdFj078zKmqzbBuGoTbbLYdQPVIJNghUy9lljQB7899Cx5Vv3drxoDo7OnqiTzE5FnGR5UqIlYZplUN5o3d97meoWljoiQHr6FV0x6cb8cgo3Cuz4+6JpvLzwyANN8S36vGc7UCNlI/3VRFfQaoNTGfZJdo/vmoi6RrFDZolDx+b1+7RIYZNYZMHTC4hqCRfJooUPX0nWxPQwPva46bM4qSWRN2HtpQm0JIHm1cROOuC8lMJp0VMW8Q9NYx4BqnC//Kr526bQD6TqdiDGF3p1hOZzvYV2StO+2jjcdpPEamtKA4WOz6tbIL/g2Jm+RMHwLsr/NtAjUp7HY6mcz63e6UiI3I0m3j/f2p3KcHme0D5bQ345npfEfwRnnYxcI46diScI+tVD9gxKMpjLZEBEG6CT4hgPDkz3ToBSgZNc+7pFlMIOOXl3qRUM57IGcbGgLXtk10ollwvck9iNPBcX5WI9+7h3IKayY8Nq3iT0kcpYj8oPVyp8LPaxK221caCVajkbhFz2Igq3prEhWxiXIPfZgFbpYGe3Pg7k1Fl7H8ohF+E+wDztBgikuzIB3zV35WmIXUX3O/1suqCQgpIbWmbEyWThEV/Mm0FzF8w6aGthq71LL3Ve7ZBiad46V+y1MMZbFj5vXJT5eYTuT1Rdj93l1prvlk51OFby8dGALGxm64Uz8JocGuITZnTGcC/IGNiLVudFMyC44pWbN0mLbETjyZt6ajdrUnn/aAzLjdCqQI2wyrLVLy1yN7De8UwJIZOn9aHKqRmEnMJ9Fu9zyutCpikSIKB8Vkdr4NhqlXYh4e6Z+JHrjM7QjUOhdAKHWpEk6N6aZ0egXjgKwM8c9mOMAHYFtqIbGUhFHaOZElguz+yBFo7aOvl9tj/gF9+LC0g3Hx+BMvT+K+Wsn7FShwIXpJLmHi5oFPMDarLqwvx4tGFDFwgt0OgPiouQbWg3dhP86kOfUkXswD9tdikCVqM/saP93mGjGOVvCEG9br62huMNbkv37WndxWY2cvRAxS7Dld1asCYDa+UFX7dWPoy/M42Ci4/lRIgBdoFFFXtANuNm0ZLBYeLWS5vf29AB5uNqyMYfSymYgMv3XPxAZ3SBnRbt9DqkGOWcF/fMX7C6e0KrGni0J99h7d6W80pDtEpTKF3JtpF3SfjzsNHAOmHzgW7MyjmLle4wvLV5fv5o5LY1lyvGyZS2WJMI3DrB8/g/ue1MRTar6JkHtbDsQofigAJALnLVsYURmuDzIAKXEBH26cWZ44MUs5FsahR3yKlrOGjFWU999gRkP5zyJaMZqdyp7tfvpGwcyPK3H1CyZ84dapWMPqctmQLubpST9yqPgbf496uIZIGVcyB5K+a7GFirKUMTvD3/XJkHGa1GH79WbvjiDD7cjVL33p/CgaFMlpfo2ZSbCXV5PjIdiUsC9jd+J92iQQ3b6i6nGumqk/J9sRlGXq9up8enLdi8Y5d1BSGYW/StXE3rGXT28mYMA8xipFjQBZJMjwnfjGCH0nY06eDGH6Tf1j4i0G2CSh0ip4xGzFsK7F9yCQul0dbY0YEthiAXlzAx1DZCKArcYsMqMT3oj4ENt2DcQ+Kcm6al4fFUQ1L60QvZZze6MmZIJfJGJPVwHQmkpNGKuD6MqjaowGKOXAtgtizcmRnKw8DXvaWBrInDN/pC4f2/Jsknj6mle/XCpBshRwEqV5ON1cu7gTzzPBsMAwHreiucfbCHntLBN84ZT13zAPYnD4cQdgGssRuYwplIziG6RRLV+pHGkSt5wCsHE5ZaHQpsiBXkDGVkJgWjRB6++I=
*/
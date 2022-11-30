/*
 boost/numeric/odeint/stepper/detail/pid_step_adjuster_coefficients.hpp

 [begin_description]
 Coefficients for the PID stepsize controller.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

enum adjuster_type{
    BASIC,
    H0211,
    H211b,
    H211PI,
    H0312,
    H312b,
    H312PID,
    H0321,
    H321
};

template<int Type>
class pid_step_adjuster_coefficients;

template<>
class pid_step_adjuster_coefficients<BASIC> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0;
        (*this)[1] = 0.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0211> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 2.0;
        (*this)[1] = 1.0 / 2.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 2.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 5.0;
        (*this)[1] = 2.0 / 5.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 5.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211PI> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0312> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 4.0;
        (*this)[1] = 2.0 / 2.0;
        (*this)[2] = 1.0 / 4.0;
        (*this)[3] = 3.0 / 4.0;
        (*this)[4] = 1.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 1.0 / 6.0;
        (*this)[3] = 3.0 / 6.0;
        (*this)[4] = 1.0 / 6.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312PID> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 18.0;
        (*this)[1] = 2.0 / 9.0;
        (*this)[2] = 1.0 / 18.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  5.0 / 4.0;
        (*this)[1] =  1.0 / 2.0;
        (*this)[2] = -3.0 / 4.0;
        (*this)[3] = -1.0 / 4.0;
        (*this)[4] = -3.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  1.0 / 3.0;
        (*this)[1] =  1.0 / 18.0;
        (*this)[2] = -5.0 / 18.0;
        (*this)[3] = -5.0 / 16.0;
        (*this)[4] = -1.0 / 6.0;
    }
};

} // detail
} // odeint
} // numeric
} // boost

#endif
/* pid_step_adjuster_coefficients.hpp
4aJugWL95ve6kWxILfotAZKuY+v2ZPk4rdukf/ECbZpdYRsK8dAd5I9ZuvaAhRk8syvRcml9RP+NL1Lw9VLROThXMmui52LOnDtrfNAdUXR12Js5UuEzlP5GzI7312nkRM5SkvKRy6P3w9hW3nmdFKWyj56CADtWMh8soDdPSOAz5xB+Lch/1Fv58QL3ST/f3S2ogLSyDEwm8/GkhvqW9EvfC7ityw/RHsYpFQUm0TRCkfeSceg/PENwuFGiEjahvNvyBs8pbYVfKN2jA6u+5GBQQ4QiVhI2OT0HoonNDWw6UItLeBVVV31z3w+kqQIsM5uNoKCjuA4fQWdRlDjL/re0m4vnofjP0192cOu0KUvbrVJ3f/gYJvX+uKr0+GqB3vRObMvDRZ3eOesILDJ6fXLkbv79NrjcEiU89dnpkfFW2iH81/KjF8Oz7byqwA2Z1e+K8kLsrnbRmU+rTan5V/bjOSMR5seJyU/EGrG3+UaEOkesvI1pi0SHUwE+8cpGoDI1bSAytxwlB7CUxiiUumxayR4RwFq8QmtLFQUdFQPI8VxcWOZQsWIk7eE2+1kzMPP7zLUTxaNIy4qEQPoXWQl/na5mJoIy2wCil7PGm4gTQhbA03K3aoTOHcH9yKswEtxDARW24oRa1rKWcScq1SBz6J9RDBgfiYz0cMs3G5vQntH+P65Oz06foICVA33rINgNYW3+a6waNQJ/71BUXi/ZKNm/izQ3j1D5p1YaN6Q8SoyuzZNBgLTSftQR8TB2X3AXOxmfcYR3qRJIYO2wfayJ9h0yuCTq1AaGZfP8UFHs/H9ihW963ozBeLwwzFd302ZDYJ81RvmEEupmzwEowkb7ASjj8yaQrnn1/9mTemllcBZ92Nqx2vO/7TaeB+8/7TvwTihySCH8Ys+il+77rJZBKQW4Ds1IKCJuL2ruE3ywL5gnIYjfQe3iEzeCldnly/Xll/cvhpWdy9tUmgfAJO3TfTWkUPzXmGl3fpTr4Rheh4TSbbXcivM9FLL1GM5mhH+eskTIPW3zHYdsVaJl5e+zdtIfUm1eUQGu+Qz4pefgI1qbS6ZmnkfBstX6ixFLplmpVmjbJsIs79UixcepYMzn5NUJnbN4OZl42CsH++tMOiHQ3pfA7MIV409rS5rusaeBBXxO6TkwISV/xULX8ppEr3F0WSpDbpBiP/67oc79r0ay1iha0F0zy1BA+KplAMMxQgjBgFXGfqYJ1u3UDdQgqzzNRTkvsKMxmp7zllEW+bYVto7/TCYDnbqkViO31RjjuwNBU4RWHdvilqVTg6RZq2KccVMemnIIg+kfZXsHz81mf81bpwnvO3P2KHiM2vNb35ez9pIToW0GKtKjMdSZlkjbfJJUzV043MmLYrUmDCFny/z57Y2HDYc7z9Y1o6e5H3mtiexgxtsVZNTbF+t0z3E9AvtU/1ioDtQBAnChCCl/5C235HOg2pGnpAB+5zjS8ptV3bdcTeGSDEtYW2ymWZRCg0Wt5IoUkrHDdq8pPCjxHRjMtywBp9lXFrYJjHksY9U3YGpx57zsO5yoKL+RrwAlo3MO6Knp7/2BIz0Mfy+EU+U7iJscBRQ7jcqgAsNmi/bZAoK9xnYRmIz+TXoYrQOYBuRwEsWgUuDGmxzJwKUe8RFbFApO4WS1O2HX3aV2E1/ofpVoVroNemn/TsN1kfJVfx2Va6NQTJYWTqADr4klP3KGPzIB4Hscs3lrK+lb47iYk2wlVIHi6AFkLaaNPFbtb9dLLr6cM/pBqsCmER8oW0sgAlTwiiJrITCpe5hWD64BnBfPqtXK+KOlrPDRKKv07bQA8iuZgLCAkQT9NJGnrEjFHVhbKsz1VDM/w4YexFZ5IyrUTvlg3iE2S4Ee0bClintDxh3NslyL94NZk0/kFInwv6qyhT4qDbIlQd3l7giaElOe3J/Nn3fqZ9BRaQktZQS6ZgS6lN7QbzbVSCP7fR4W/2Otqhd/sUiTKip27FTvLzhKogqkcJohQTRRtn07qMgIrQXpN7Bj0BS7uIl9dCObUQJH7gSkLjphIn4HS6ulh5Lg+5GT3mSNMX6kXvEqm6AR9PwWLTOdyWBiFSo66bqgTtj7EE5qy/K3KCvI5VQK5uNZCk7UU9Ao//Gs4X3beS126Js3WcexiDRVPHiF0ehI7TsuntCo6MYWXZnaRa4fYLDESWwB3dD0GgkjOOvMDfwdxLGItiZ0r8cTs8bC782gXKj1UnLO/ypJOZu87tlhNcjGEUH6JN5U+UJE8uYtELsWHcoXkAD+g8VRkZywAtKWftOeWuCkuCqCB+JeNAhmWVPn4Lkayg+xddoBKBv/9PXP6HIzfNxFAhOaHvCFt/hBB2GXzW9i//+j1C5taDvl1fQepgZagQgRmkDzrKHrBJrxBZhmYaEVhCk4Jne9NjW99OmHMWhVZy5cMmpQUwNukgYNXTpXKdc7KwmCYZLzhWyTSRYEGSW2AgQQTSCa/HDNxBFu55LQDW5LpRGMr7mcX/7TLU9SXWmBjeB6J+eb9tP33ce32VffX7XkjPAXJeZzjWKTh2aJ6cxfS2JW/s/laInpAsv4DDfBkCUSOvWiEWt6VvUgEm3tlwdWqPHCQ0hJdxfC+626OC8j5iacKRwNBZ4cgHuEfM7go5IdA27Ce5Nrz67iON5fw8XX26yxK08ySvXPnGf5mh61c5D3Pou/lEhUhvAX2nkjpgfxHTFtmT3tew0s5bO2Yx6jluzQHRWm8nmieUnd8OJwTlHOtfiu6rn4UReDVBx9CORRmQ2EomH1Kz1sotFDHl0RtyafLwF2WqeFFypzH6FpVCBg0V+E2TVs4Koj0Hih7GpXlyIig3G0YjWAFCA2/cEWzdJtlGs7bTsLsr0zj34eTmvHe+MUcbkPTSOEmqBy9z3tV3GjLwt/pxaYdGV2tyS/qHXSxmtgwX1LH0b1r88dEKGRVZN6xAwbFG4ap8OQnmgZISwc50uJIrPEYcq4ikv6EcKUbQliVVcUS6Qdt2ogTSkviP/HoJmFlcoIk4JVQJfxvGi4Sr/JtYI1cyDPFMgnf4UwlNhF2+2Ea0UAipZuCzyBmyrXedrHH3uv9VFJdDCkZjiquo9B69uvG0+FtmrbQ+RqGqVmRfkiV2+FWdqmaJ3i8r4nDMgUAUwcipcbfLsuNaByLmYqizo4XtW0T2K5IR/eVEgt2uHJvJjtAnwu93MH9rFAtFIyAVC44c/ZU53+JtyyY1tf88pu1H+79AYIiu0MDBvUE5yeb1Ooe8sN8/37+wuUAQgA/AfkD+gfsD/gfyD+QP6B+gP9B+YP7B+4P/B/EP4g/kH6g/wH5Q/qH7Q/6H8w/mD+wfqD/QfnD+4fvD/4fwj+EP4h+kP8h+QP6R+yP+R/KP5Q/qH6Q/2H5g/tH7o/9H8Y/jD+YfrD/IflD+sftj/sfzj+cP7h+sP9h+cP7x++P/x/BP4I/hH6I/xH5I/oH7E/4n8k/kj+kfoj/Ufmj+wfuT/yfxT+KP5R+qP8R+XPvz+qf9T+/PdH/Y/GH80/Wn+0/+j80f2j90f/j8Efwz9Gf4z/mPwx/WP2x/yPxR/LP1Z/rP/Y/LH9Y/fH/o/DH8c/Tn+c/7j8cf3j9sf9j8cfzz9ef7z/+Pzx+/P/uSc26oYFgrFeh+4t5BbHuTrY/O8LLQ7/ofT6buSDQ2/YyxDRcJCo/L4ajIbUBaK2m7aapXQnPOB7EOfWBZOeHn89YtuHTNqVcwg6Sqw5wn00UullIozQuOqMZqyhUo8yIi0FfQlmro41iasbdkBI8AHMhsxbgzzSWZ/7ZR2OmX4eh1tsqCRofEKS+saMbbGAzmT80rraSiQosyEhalDe6l3+vAtQrF2jWdo2sFOwDqD323hjJJQgASVbY345spXRGNRG+qklnt9X8VA7Xgl2M/s1ikbHydaLWg/ouboKdl2zZ3oIEbceuXl+BWaMdtW1N2EypwVIZnUexD8yuA7d9fre/dAXQA+XoSmmBB9WnQB5SgOmKneg0kTqDBu7bWg7OZUYuemESUlRXlr1uDKXMFPjjsv6hxobXsgSDk3kEqVDS3px7foCtfYLGY0Uf1qPdRLgQ48goZYX/CgM+Ki3Z9qhrOEIoYB5AWM4m9eBMNUjVhxHeaLSa1/xcKGmnybtOdTRk84LTM2lnvHiJ8jsr76GAik+R2QjFajdjZi0UWB4KZ1Hndu95UDps4X5QhtzUGReHLzMnxPfd22d0oHTfweevx0Fzekk6ndKQF4SEILF+Qc8utwn2XcMPlPuP/NssdfVZ3AeSWJKRnLdz2Aw2taCWg2FJuleVcvmF/5fGIq1CYEt1YSXu7R0nY511Qwznp1q1pjMW6TvEeRrP2cY6T5fjh2uu/zxXysfTkS9tkYjS5xaJZPjrGQc1Dw5wb9QLmgIVy1TrkYN8MJRFdZrYM72SiVz8BeRp49O+Mg+wxvXHQZ6v6Fxm1jo4kB7xzocB+1Qhm+i6mEfD70X2Cj9OaEKw9C3cVTMQPBR+ssTDiAV2wFiXO6fvQXfP3vzf3LWER1z1bROFdDfFQeXa/yCyTEqUbpSqj3irZon9L6qX+UtG9U34I7HbwJOSuBXw/RdNJIhJTDPRrK+frkgVmbgzxz95WXgeJKihReEbQZPB9nxPFxXzc939g8wHHCXUa6sSTA4lFEo5m9RJczIllsADQTaoSTU8OJk9sUEWTHrcLn4Q2t36qMzhPdp0bzVZ9hnOeWh06ypk3IlTqfeDtlTTHnjM4NGkwaBDyNEt53Vxe8VSRn5nefomO4bxPGeK+5Fw3L/JgoJg7/kM/R+HDHU3FMULp1vfMl8V/hPk3Ij/GVlbe7mxVJ5AdW6iYMGIfZLkI+EhxraPAUHUBz2vIF54CxorPnSSnoPyzDmlOijEyATjpZfmeV3BAc12B63YBhDUyd8A0wPQrb9Nj1IrlTHLvgfGvHtDyRyEN3FqdM4OxebrGoL7ic6o7rBZdTY7QOdbX6NlmlLs+tUW53cD6HjHFpmwSrtaD7dT+hbdKFzqcvKUmYYNAAj65tktNoSlnsgooVyfjm5/JvBxaA8/RWu6jiEiIue/Kqr/ZZ7/EZeMe/xk4u07g1DJ1GgwZaEMlhGdoJGc+2r7809Zf/WQmssL7aIa6ExZ7vnfxu+/i+9DasLPwFOFfqw5NkTcr9kV5G60+NqDvHv/Ic7kernb0wV66BaJrIDUJoDg+1ADvfaftuDvt7l8IrEpb3ncWbl2PUGxl/nxcxvoGZAKVyCjeRY87V6LF+KmkhDZXeBM883TYarxXQPpa7KU1ShiafvY8ixEibiRpyZ85ZSI9qvXwu2k/yde6zSnsnrtb5zQL/ERQRiI/N4YsC8GHyQy615CQjMc5g2XyPyMp8mEJoxJW9uKi6nT8DlXDj6d3vmG04gLQy2yVd6FSzdMeniaSvKb056Tyq0ZwvA21GMpcxZfQPPjlA0NmHIdppSanoFOH6uxGG82PSAR7AC/gDS4jnU9QS2ZDGcKeSGUqZJrZ4y51sAjH0Lz6GvmLLs5laLgF16DetObQhOiTvm4EqE8054Dj4ZxUbs0ebswAbGyqoso4JQ1IYJe9Og/8nWquf56BAMLLkhiEkrbALLsgbziEnnNY5cmkyUhZYUu5rGU6i2LKzJQ++z1wucMkkBmeT7FPo1Mfg/znENHxWW49TbZ5SzXk0Tw+qtur2Fm06/9t/cJcMeQq+6YXCgZoOwEzl3NRrkuQa05EdJLR7vbjkQvey+Q8FhjLhAmnuQ5GXdxEanWGtF0yiRwVAUrXYMWpqlgqx7DtLyq2ON4HzV+t7WuzDhI00gGzIifa3oiKPxMWnsQtceD7wGTt9yTobzU/EMaILF9QXfKC8vny6R2YtEgoezniI6NS9MmPnjxowCf8vMrU3GmAIDqU/HWVhBQ3/4cl4JUDgYL2D3QqW7HBZuE53jFdfE8C3CgttaKMP7NrXolmBTcmSA1KSXAZVYjp/ixdeD5O2rzXuPAt91Rc1u8p/NA5kaAcdCYMMSycSA3mEEcjBcEzrJBNCxzVAY+edKFjLO1ZkL+EFafgZisp6EGuJbfgACLP3TVwl5IVV1yWjyNSStTzoXkCM9fBJZbgSLbZwos9FSLdTKiOUWsYIecm+4OQs2l2cup+/8B5DTnjA7nQyrmjczMUvsStht1NqVJaYW1Ybsb5fVGtVvJVo5HD8YMi79aH3u1q5if+h0yewCLCiXaQLt0+ohzuUz5fOps2NM9Z/gfTVkDSxEWhRgijJUUnNi7Q0jJMZlNZi4Xc0hb1yf6oURuQvbijhLWTH1wagTDJMYS2YbZigTMczLXIP5XDYcP8wt9hf7OEAoYT3AlEoAX4MjlLYvEByogsfc79EaCh91Uf+Y1Ylc5z6gpssjomck+cpOqOvRwCTwqDh63mEnLM5rlAyzaSce7C1mnZ1xiG6/7vaIhJApwAop70kHUIjvwApqqZeV9vzoCir+G1zRYYxjE/D0OEifuHfAbWDPKuy+9H9IMQiFlXiOUlOm+s4GUjQEkd4c4o2UnXFTstQhlxomwo0YdWYgXfMOT/NnAdP/ZXi7wOGm4u44tsMOgKkgOvVSAFML9spEpL+sdJgfdbtFxhtveA1O239JdRvCLNjO5vWhWp/cOmQ4rZ8d9mzFW/ZGFWvZiRL4RCk58KRBnhRyL4qm7jKpFQA4lOgzM1bhs6ggIMl3cfCmSIlOnNPuGtP5X4k9Wtf1w6pjQlySsoWOgk2yDZTzH54SEvao37ZNXW62tjMbCra9j3GIaZjXL+yIc3vLu3SpDAOIz2cG8c71N4cVKPWJei2hwsTbwkbyzYSHNpywq3qI2Jiosp6BQICuAijxcRM1TJKB0vT6rps/u/Lm8C/hjQx8+PRQBDLKMPSQwDCrvUW4qGiDM5fh706Qn0rS6LQOmPVrHbnM+ifNkR+K6RHtSuaCVVt+ihr+tlqRWV0mBMOqqIyFb57T2d3LbIHaZGXS/CcInLhcXOcnp5oqMVXx+l8zdLu9HazvHlzo274kWlWAyE6RoIceKc2BsTfmLvoC3WJqe4DRId5c5NSShYl5c+PycGNTn5bzuhWWbY2GK/16j2gAUnztooMKzJxaE1MQW6xeTatVCdY18NJR1CZOndE8kDf0fGcZ1tkiemowfi/Mi9icMxh9dHv/EONTusuGtWxDLfDLiUVfLdgZ3I9O2WGjTbVJjpBPa1KlpxoZcAO6ZefRf3o5RpO8gZ5zqEpkuk3Syl97dBqU83h0x0DALEfw7YlITZXt8+wHswNvjc2ht9OouYy7FdDmje//jFs67naWe58kyWs1fZf8vrnQK/AsdfYLl2trEsZPWbdAuNW7gSx1aVtV1UgrTYU8MaXgWRl4egYGm6kjB8bR8D22vPit5hPqBx1hcZ9M7I74BlNh2kRK31Ec0KmdQ7hMQ0jeenrr7rxjacb7X6ODGE3T9yyhT5dLDUIrlyxMFfZt/bGo8pv/WYZqCtMxPQUCU5I9qj8pr0by/0S52PfJl7LdUSNPDBE6zs8w9Wiz76TPpvpw6eqoubBn4TthR1vmpnJT77JM27qVHnsByEWMFp+B7BySdvQwDZ8VsrPiJz2xvaEamdCWDbNHz2behsJaPWnWD1EU
*/
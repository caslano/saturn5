
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
MNRtOy9K3zlk5bwouv1Om6qkTIBF0jUdNdSnzcBF0pXEFOwaO5qpSLum96VXbScqUPVgc/D16bEDRZ7o8jJH8kTDQb1X/7mQjypINnrCEvxZA/dTbzZcSt7SNzMV1xI8M8GAOgsDzVQwRrWYURPcxqzHWs57DFbq2xJnxXmm8Tevo86f5HsGeuk6COIv43xPjQP+ZJhL2gDMvpmN81DdwRAqJIpFMrcxoX7lV9icK3/EX7x3+hbT4ZvCYD7ZJuIkloKTGBWcnmkbf3rlP/C5YeUBfG/oNAkffI7A5WkC/zVFRSsPLlR+EZc7zD6IxRAH2dnpZg3yw132PhOEDcnQLtvX8ghxZTVwCzsB2iiO5XWzBDILgiNYMOdP+q4gg8XU5AOb2d2PudzAQH/FX4+mBrwiyEDtPHYC7s7vu5xYVecvUIp0GHklq16mIHsdzudcrcoO3YlXwHcbUP7IwZOrSFAcRsZVdOHrUbX948oBwddrwR5jr94YvaSKFOoHnmfGfP3CJe47a62kWZ63SNo255hOjBpPLkt7zMEfTMKLM1+0xqrv9R0wu0KvXnTa1cv047iuGRRndzqueCKYRNnFdWf3INLG6t0mpomvF4f7dKwae7AIav14Q8h9lPtCcEazuJMK0RND91Ia05Tzp8r50+X8GXJ+EsKW75Xz5/NNXb1g4wODGOTV5GO6et87YqMu+V498eNL6G8YrMB4tOwt8P8DGNbJZQQ9AIBDS5xdfXRURZbvTndCi4kdPqIRgpMRdNTojAqjYGAMSocMS8LrzhfOQMLsMtrb4h6c7XZyRhLFTgfe1LyW0eXD1UVRV8HD7rI7njU4MAbhmHAICMgMvZrZxbOMPuwoATEERXvv79Z7r7uTToL7T9JV9err1q37UXXrXgy4YYbaMFNtmK02YMANNWrDYj0ex+VYIcw7aieq5QuJIqhVMHFU65z6NToK80v3hrLb9z3zLCnbUOWZZpe7SvcGF81qWBhaMKvBGSwSVRUBe/hCIjRZ0effx8fzHUv5eD5+o6iaV40j/3yvopfIMmfDF4l4vqIXyeR6/nReZsgZtqop8Hj6YAq/fN02PL9EeBumcM35ARtOhyb6FLVqOczMI3B/r+6u4Pve84kEjnZxlhl3kW4pFhXSgmuL5S0RVMZIDX8Os4vSd4MTZ7U4Q25+jTDpF6Q8RqQ5BpqEBb1TrdyBUD+1rwslVyWlq3bXrJZlwUn6v3x9NHkWpC2kz+Vx0Hh190JuH29OtchC2U6ZlOHPxxSxx/yFIwEzNtEOQR3kqNpy5i+wBVHXr2R6FpPn8dMTJK02Xxx6sMIfW2crRirz8UrKp3JgVtaO1PJBguqslonBn6Uc/IRqwi3TYFsddBIdXBBuKbQABCz70wVL+HLGOjOLdDRdLRgMTKJkgOqvwx0Ox0DcKJjekZbrQGwkajY4mTjUtcLTXuLZoUZW8FJg6cIdOfGpMIxCUSeCO6V84dlFA8kq6SzxvK7y6Yng/BJeaII28RTOLuGmjiR4AcItE+Hard3BfsN0aQoSvD91ovfxiHIgGYYqSQmQjwhhLjYNZiI4hppitoyS8GlHBbfN7fXQVI1xcOFDvY4yWeqJ4T1FsDzcXGgLleEcaZV0ChGartd9ddTSd68zY8wUmTFmJrD4MsbWyQ1zDJex8jcqcKGDHaJTw3P1scm2qOWLXx416HtFjkHfr+HlsROR9fQ4BjAhGrlxtHajHCVpCnu/PGqq6Z08W1QKjZW/5XVYbmekzEhsg3gVGreNJa6xGIm79afQ+VvwayzYWRVM3FKQxb32c8gxvIHpm484gW2Ih8vBuwXvCrEeq+lgiy3Hu44jCFHFu1qt7XJ0abUdPsSi0FCtGlr7wW1226lnuSmGD9yle7qDcB2f2ruo7HawUdVQPVhE0K9XWzjG7hUaBletr7nsXGJR+KHurHSEF+sBC8fu5dyQ/Fh6B7dUYlKP5eCV+mq9jJqhAQE6EnK8lHcCFVYY/kGmG+ca4d0MWXfkBxYQr7OAeBUGUGDKtweNU5H4AQOsF1PBejoJ1mAZAdYA5W4JXKaPGoP4sOo56XjXiD1gQrT5BE5wmrYSUF9JAhXg7E0HZ++3AedMF4OzN4tPKPLCzbTfxuw0hM39I8E4CV2jMQZxbxLEfx5zLpGyfydjv7tbZ2QPOsSemo3jqCJbchcFc+VvVhonmHtqbHLL6f9xnnaSxqQHGisIdB1ov5hAGKaIe2Zy2CDzZFyOCKsKUUPSzh2i+XUiYQIhK2C6hXP+2t7gYqYpvvAcHPUjrIVcF21ePi4TkpsvaGy+cXxn0F5SXuOQXMUBKnZCUNrTbmRR0/FfMZFuGEKkF25pJ9VBEuIcg57JbXbYXhuTCyZqY9q8LOr/BHF/Hg4Ke4YU5or1yAm/7VRrT8jhFfMpKcDukFE67J6TvCTTwy3LbMFb9L/tz8hDTW4JD1CEhYmClxdsJzVnBpPAZsNoIxQkJJAccCWzLdsHuItvWpCBRa5MY5ErkywyNoRFJj+NT5AM0Wtmsi3FeslxiNJghj4FIWPUn3eLfYi6REPtw7OJHLHuGOvtqOjliGSnXuPgdLtomUVtj+O42ENLhJWvPQkO1SUiSpJZ4eeRC0cSJe869nDQu94S5tclnpMMmDf54dWmtxdMfZtAKnBJpPM0aCGGnXnK3GGlYKYkx7wEeIR3M713/+Z1ECK5Gu7WVznBK+KO4PnI9A6cz6XaV8q7Zrl97/FpvI+sludJ44gsf3G2vFMzTOLEAf2D9/9IkI5xcyyVpTbk02irDWrEQRkrEilHGFnWgVqG5lfJ5v3FdhlQRWOBC/GcGCL6EpRrLAfOdTnsSQ7HS1DSKebksnVgt7jXpSSOw1OfgcS6e4L0T0BSFN6ZkA6srV9odHtwHK5v4zmC6bokr47Kk6K220uwqWFacUDXrpxiTNSBZw7dHNfxF5QZSQRd9fS7bZy8ROpkxDCc7GYZ/X+4/4h8HGOAAxCI3yxKk3M1ALcjdZGl30qpAycfosjazMcjG6SNiLJM8ih3a4R3eLEt+BjJANuYUP5Af/os7erdDDg3KRKkyONYbREfqy3iY7VFOFYD5Lrid7EoVEZ1C2yhWXp9at2skesKm1iHw6C66uSpryHCDjIwsA5m8r4nD2aKbZfkXzXQpP/aldm5asuZEZ2rJuNpzHwqVf/OGH6YyLI7ckbaFcF4FAKQ1FWItV6h6E/8/DzHwzwkPxEthezvaucM33abnr2fHYRdJ+C7r+maNCuxIVorAiitlfe46bZS1uHiQ0Nsnapc3lRbp9lDbJ1uKlPki68UWyfFMk4b0dApg1o91P+uYdDobsW5hGXUyC98So88kluyx7EXho3R8ZZho8vecEN/eaGdkqH8pGFjtb6BVtOyibRq1iRr5g5Xc0nGmpPMmlp9vlrpCnc4faSPlt+gv/vL4wm0k97IVa4ptlSrTKudo+OsETiHG8H7YzKNYFOy5s3D1XwhY82GZM2Jw9W8P2PNacmahVQzPGctPAuGrhR5J/yMs1fpb8212ebkO3Nsqy7X6v3w8KNddQLufHBn0sMqbfLdomh0nT88xAb1kxzuhWBaWi5tUF/Jx2huUK8WdYVshUpjaMw9f7T/7cF1/5XqplR8KN8wXkUtvvAsv4EEoUYIQo3zRFXh+SP9ewa3EUhv48Z8NonV5uerk9AMAHGKVplqi0ZnpgZuzBlsRPsXtzEOqmRN4OZMdT/NTut8u5ubUielVpyYqeLr6RX/PlPFjNN9NL3iXWZFBtmQFZ6n//luc4Vn0g4Vj/kzLOH3snnB8GCySjb7v1fIZu9Cs+nPVtuV4o22IfZVXY8+OZq9mX42bjhB68wJUhtqedMoptffsv2n4pYLAuFxjdpJ0v8V2j84mn03WjO9EmyKDe+VQN7fNRP3P6N3vEffzW9qpFE0pPc3Mj9bpb9pz8zPot9cAj8bbN99S6Jo5Pc8GGvrJ8TSK4tEXa6Y6RVVTSKU6/Pylduw123E29fg2MInrcuLbVb/P5z34+22+sCdiT8F7hADiT/Rlx6X2uRsVF0Ng+x52mfft20oPs1sGX29x4+5YOJT63dpqdv6OG7BuaT/tEyIJdsfODj6eTQtIuvEifqATQ9RZxZy5ab1+IdzvD6hy7csXrTdyBz2RDqTfz0aT9PzT46Cf+jQxL+uswOXhH8vfE7frZFg6eNg0xhqoxo9l7S7lvat6mpkIQeWrm3PSYxbJMqKSVlat4DvmeaKKPLFOPFEt3H1EErJOyGtLjjduZo9fnEs5ef4fEGf2Ho+0ckNszzTtt341bA3EzxG9qc/APV+4zdFGbfI778ecYsY+yPyTcr7h4tFo7zPzK8TK52BO0iFgSNXRuaVzqG4bNozh3f2yXW7GGyuTtsNt2M3lHY2OwO3x7OS+yNwm4hR/l7Kv43y76AdU5krHnaKmJibW/JOSSc0zlrXkYHI0aBD+JwBBzCTlvmieAtdVdc7+oS9TjGezxsn+MVwuSYjpsIELfhVkSVVD3rPeaulG+LlNVzUL69DeG6Xone/9HkCluJw0jBV35EnvbsWf10EeI8XVbiI7KI+Ff0myoMhQtZY3KV9+XWRcREVpP1D6/KXy6BRifpifuW/gqs8+E2RvFybFbhV8xzG84PuKWA9Tjb/PewN2PzLaIK+Ts/hW3lbHZNi8AyCaL+nx0G8bn6x8ZF/vD0lWoNJ4eV7VVhh6+Mu0HaIqUv7Ih+EcqSBbH21/jENFI9OmXAoeoxnQfTOy+8xV1Fj0xOq51yko+Xv4tkiIUIw8fHbSK6tp3lsAkLERLkTL5wXQ+/t69/rCubDE6LXGXDV0TdlFTTYvVmUSd1UOANZdQSz3L9Cpp0yay+yu1+8qELm/NLmc6ueEUv7aA57h76Qgm3IGmN/PpK2P/3iyefY203y8nKN07i8nKr3Xy5X7v6vhq7cyq/kylW4sHJlvB1cDfRVAa9cCeThjWhbfQKxWBuH8ueFh9LvvzOFfzBuMKXaIk0C4PgZt6TT7g/PtAWvka81+LYr5ILyZN4zngJa6s98ScNc6Qy3LLa5WxEdNNyygn7BrY//hWs32pK1yxcr7BG750PzgCF5XTAZt8r8Kfxt+ztOPisrDsC3eN0Kn5UYVOTJVYYpYkNO014+feBx96CLVnVp7wiXrBkexLXvuzaDvHXbu5dg33/yWmYZcH2sRWdmA/QxCZDLteiM1PRYLXpravoyLboLUR//hzYDIjFq0Qok37zAyTFa9BhCRO6RpTladBmSz8nSbC3am4V4e7LUqUWbkGyRpQ4t6kSyVpZmaVF4qNDLZdKuRYuQfEAmadh4Ga7fQ3VNcn5I/2/Cz+EFRgmfnx2+pPiYgZnTE/X+HJKR9Si1igvnzVv5maWEHq2Wntcvh9bpWDFgHN9sxiDFAZSe/kJOq9Px3LSNcr6b11mlR2RpNtW9uF7CajOmL0t/J0vHWKUubXOTVbpell5m9TtW29xrlf5Sll5u1c3VNmMVZOl9sjTPqnuFtvmYVVoqS93WmPO1zVhfWTpFlo6z6o7XNu+yShPnuHSCVXeiiTrGLX2BiVpG+koT9Yz0VdAuPblqdBnl+nHHLRtQ25bwZ9i/RvaMwRkzrQxRsAl3xBtmU86W3rnbqHpZNkdE4r8V/Hch/1X472L+W5M9nGj200HxWOH/1pQPPv18VPmZ3ee2AXUU//NlxBr014hYSWz2+s9wzibkbABy+PxnOacNOW1ACMW/lnOCXAtI4PWv4Zy/5lpYeJ//NOcoXAuLrfhXcc6PuBYW2Ov/jHNu5lpYVJ//Uc6ZxLWwkIr/U85xcS3A3uv/Fefs4loAu89op5tUQ60NcDdrvYmc6Ozs5LxepJzV7wD8dca8rqd2Ut6b0n7c9PSTo+7HgF3/Lm10EcUaTv+g9IC79TEC1qzNWMfgNIR26KEpBhIkmbThGxFFieLd6SdtV/+brbSoG3qAqXMgAlRX++cD1onjeJc4NwXVDBRqQxhw+moliw3HYQq7ZYCIAPeX4S1NFG1XK36EIIcrpIFIIvhjuL9fEcjR2tCw9IHfWKOfJoxxv7FXCVyh6Hk0J4SJgWwQI8njCr/tMVsyR7yFk754o1bZq+e/Zmmw/viPbNZwcaaXjAWgX9hGOsChz5mPT7bsmtidfVlx4Cw1PVNKJQxJsbMsz2ZAFXI6Zs3SI4R1mZAw8ErRiVj+Ibl39KfOF436YJvlq4mpwXlIf8Cem76/dE+wWq3sJfVFrTwHB4dKMV5bkkTUg+sXhKboe+kFUv/UvJfpr4gqxhC7DFWC07/VryBw+eQit7wCif4iYubo+WlxgtLpv/3IaPGoGN/+nWh7mGkGyRFbQVzbGIGmSECQYDmfkeM9MRBOJNytEY7qrusPbLUWyjqIZbNOJlEc1erMj4B7BR3yKVtgWsCWfM5GmLYRQtZATvD7adJA0tGwPnFrmu6S6nkqw9cfvUpf89hpYRlDFTPIwntAVHcr4t6J+TXuN7oCTq/e1A8Era8RT67lRzGlUZBMn+L+h70qmu8mkVVdw/59DMSRl8OMPYnD9XrBlHPUIWg4v7YOlohFNbS+uOfNc/q229hbj5RL840maP/OyEJoFmP3ctfm7v3nlxMJePo6gC43okTdgCGdwiWaUWHTwjwE43G34mrb/cZXAWe9/m9fmBRD/BZ4Xq+otcb4jewBdLwS4jr1bI3E2AV2ZPI0aKC3yaHzNKpHngBqqE2rZIG3Xs7hw5cSiTBzGlswRzIhwWwusj84jvC6jXOe2soodVQ09xEBGW/Uve5Fdm2xEjRBzraiGFdVtClj2CwbOO8eiPsnFmwfYVey/SPjb109CTf12I7AC3+5xGTSY26RpMzEFG/ivVKPK1gsiSdjPb71zaf8gVXvNZrR9OBtMTS2sw2kwWatCmwcxeOz88DB5YzNtqtk24TsAxfgAfH/Hz9vOYjRq58N1ffzOEZAlz6mf7RjsUH9dafKh7Mz0wet8pje8nLyTPGQXt5XlNx0x/SHqXD1H8AK4dVMcp3QtaJttj0FjMRZKpiktuFD/e6zFsURU4rwUuquyAfBO+BKsqJYTPbC0VrJl0zaC0Vtj0//zZUw69zOk3epDHKjfvAdcwXcrRUIZ7ljeZLQr05ZEYtxkgaGsSf5Z0UK/5y6hbjKHZ9ieEt4eGVOsXiJujTmbr3dLvfdTfI1yD2FJB97TjB1Oax6TmAAbiqK58A/1dIYYuEVwSSAzXRj+nlwQHFAj/cW8WD/i537zwqvZbJ7gN+m9OECvS0NAQlyCPDX1XwHqAqjlcl7Ee9OlNUQiQNOld5bg/dFktx5dES0Cv4u/ghHtlqpVZ60LsrYSHUCGHYWHO+zKTuKJVE2evffa/Rt8nsv+qThUdbTGHIpE6ZQDi70Pb3JgEvmFewJmzvS/w2yeqyes+QrUP37L7I/RIf/E7B3fADeLlXUY3rxi0YtvuPl/hVjQBA4jP0pYtU8Jkg2zb2JUF5nG2iOVKh74VdRSkG8+AQ63og+lfdt4jhwUd95ugj/lvWnOC/sMS6gf0KcSmp/zfEiwKOvjJH/YVo92mp+ysRYl2/hurje868ZJKtwH7Wn0zbLvC3y/830//fZUvm3IATNyN+b
*/
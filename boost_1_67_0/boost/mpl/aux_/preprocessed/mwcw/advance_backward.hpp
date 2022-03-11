
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
ZzW5hTpfFdw7c79K8L16v8eHsaleZtWLiW+WZYFW+x5HF/vAFXKvJecmkoQuAynlM4Qu74iuW31LsWWrP3nPIFdsxQOsOy6rUO2kgBF4VtcP5xhTLFMD0fdS4gj9VGwEO5PBHqmw6M3A+y2ss6eCftEda/Z+nTCUPaXsIiBjbudISliqj871Qxaf35wMDdz2ZOT9mHuxF8L7xw8s2fLg1PSdh6dTAejRbu72tE48O9O7PVJ63Mh4HDY2Z6VlhMwndT/zPU78nLenF1ZQXHbrEfUY7rvu+JPDo0Wf6L6S5FfXc18abOf3b6V3zYb0G3uk9VipJt6YbEdPH5pG38gju5uWX8LSEVfyEaEssNlTvOtsBjHadnGl7R/ITp2xVJl9lZNY8VJYFh+WPz74/dKLCKbMQTmuKq9i/Z0ifjfA2HAU5vmVFYHdalqWmAoPaheuuJ53fni6xrSmf2qFvspShsD/eFzQ3mSKh/RQP11WUMwSfz031X/efOA/preRn2R4JjDzsZazIqlWmipz62Iw0wGs7jH3twcFpa11SptQrC5lyA6u2hMItEnfRAqeLJuEOD1V8nwbVTcM/mQ1+r0Z9FxaANf12OwHlrBvokayVkhPh39ksYeZkIj1CFdzKt1R8ov/xdSEMdQvGPs4VSFHOgKe4sPDSW1lHZ5M8aZkamf1+A5xFusXz2GsuXeOs2xvhcUdVvJzeIMG3rh7cfv4F5tiGSRVxHv74I5/r3mi4oCSGKdaLius4uJe7LGESn5+xXo+09KndVrGpQeS7V+1wLzZV4w1lTLasqIRB1lKIGL9bc9824QWrOVHKNuAsMQNVbDG9ji289Kn8OjFJ+IO7TBA+FIHc7/RM8fCrR+x5D3m60WfAkZplslPWgOEwp7fKWbs3DXvY5SyJsAT/x75w/z2ncvZsy8EXPjHL8s5zGwGgr8HHZrUYyXsvfMdSInQfO3sLkeiim4Vooo/G+nirDfu0Yemh5LSb2CNOjYFZvRM9jGJScXCJFgiEXKBQT0kSKA1aW/U1vy/n+1Z+tPtGqJVcyoxaHjpgXtilrSKdTijWPOAgJFY//BRS2tt1/MIV95bu1WS1bLVxVXg/HXkKAdENFMs0ZjtvJBZb0dmS2TwrdynhJsgPkwZOxV7+30un5nvXqNGp1D++JYsneVPvOcoSF9IiQWZuO91UkUmrP0rav+u/3v8czMk41IhczSTRNOgTHm89zQazleQyIvO42utQJGFhjPvyxGzQZh5F989Ps3wNr4NB28OBK8GyIyh/w6rMB4TjuyRcMbf0r1lhFs9db5zDd8Ni9lxJjlBv660DTfFGjL5RY58Sj5lFKuMTF4BCHIej7yuRhxHat/ySfgG0omBBH0nWUTs70j+oWcZ7TTfLa1JXDXr/volHNVuNOAz+Wzw/Mk44QpeC52oh/A6hk2a+eJTwWrRJzvaQca5YZ+FZ/v+FH6tb5dBfyWGrJMWsAxLmevFDOYBlQtYxiXqXrLZBcRzi4M4Gc4MGUoB/APvIuHpHfUgic+iaZD+8SPL8jssmXvMuqGxpPC2+44tDXb4+0MhR1iRfSW9mKjD1LgsB1hjGh0QkV3z5hAL5hrCgscqh0miVswvaCOKVmWrWF3xCoa2s/H66NN4tpBH8jTY5e+n26U35HNO225RkHuShwMpkDYpnb4o/ypi+Vyeg+SMM/vKwJQdwPZg3rnOLsoVcijjMZahsAPYGc47N5PvPzVVPIsECFpNjg4FbB/bHMT7R7s+mHfnOhC3T3l0HaV7//x1+KbHh3Bx4Rf0sm2EH7GNK4r8V64i26Suf3uKyeQRz7+f2nqEb2S3L43TKF+5+VrcJxbeUiQPXNQrhXqchcD1+nk4HQvXzPicN5+aNb0fqqIux28sEA97fDag0u3uC4kf47eeFDvmENyQ+74q+DMbjsBL6YzuTFqlWjX2PBOTgWZ1nteuJjtcA8P700svwUnRha/rMcsXASFY15RqFaFNS3V25HJHCUmRxcjT9uugKW4loycW7L4X1Oosua9nI1/zwqRImneIIFYDCo3PXhkl5QiG0tw5UgR87aRQrpEMJGW24NyxW3k280D54x3ctfyWOiCuU4vPEI5dzGk63MCEOZGFDvb2PBEqZqHRCFLQFdiSaDAe4q83HuItMO7rXbLlLaHpFROaodaQcRNO96rO2uG4C6PEyGxavYJn72Lx99pVb0BdeUzqc1MZVfDnuqfYxjkvOZi76I10cK3GLt2qShWBOb5hBNmqZVX7mzNg5ZszUNbO8F0YKlgxPSVxax+NNbRjVuHWGrRnEAuz50vVjGCnUikOkEFepsuda01/1wpOOI/dyblwB0strPjwYbI6L38DtPZgovZ8uFVF1k92Kl3JdnfPFMM/SKvFuDa+4wcRBxad6CEaPkw7O9VLx/5Hzh5AQ88dz8gYkMfu118bj6730n5vnPOzsOgqRTtx7bDwG9wdHKmwmX9j21OvVggomjruo6/pTPuItfMsKPTRnaeVtF8K28Jeiy7p/PG74pBTzPNxQx/TMWGoch5oEzpFkHT8VAc1/LpNzm+SDvPDOAw0GZUi2EwawOtmgmWFedyV3vu8pexe8+a3YUZKtuiwC6PfoG4+CPTRsYUy6aNA3cAIQ5KVugXnkkgV08Ey1NXyRz+M80Cg0UZ0kX2y/4Kb7chYT3DjL6mXii2GGmGJ53d3H+8CqubrVa4bK3XhUInJk6fnHFxTjgPXM38uoZ1kv6EO8XNL1Sq90PnL05pTaCDzcKB5P+bDWv3OAdyppYF1YWvp/NHhM8yO1V6re/flDr2kuQnH1vU3PROzJUPTy6TWQN6iHg4CcY00LKKyB0X2dMr07xgggCf927NzSPLpofZS2LrL8CMlcGuccZzDodcQJ5w8g2Ineyf/E/R5isTctZhJStEp1sShxjHLiNsls03M5EBI2E4Az2zo/S05huUI8CGV5MqqCxNQvcMHi5h9FOYuCCF0cR6+A724hrsYYKUmR5RVKWrKZv9eG70CCjAtZBqD6NGhu4B2w7OLSdN113I/iFSqw6532hS80yM1thI4rDwb0MkWDoiW+mW+HxDcXN5Z24nnSdO24C3TOmcoBMwKtSaG5j/PCMDsDG/lYplW5e4wNs0hHrviNN79u8Ors/zS+KWrpAQjfz2HggNTRCufTun9ugORZT0Xy+D7oLP671FJ6DTP+JouLCgiZuS21UNKBhkA+JAsul+sAALGnb3/ewsGxkmaqjFV+J4di9t/VscWK3xb9GrzsJK8UK5e0+NyMFGDl6c2SDapbxfDDAbDjg1PmAxy6o3UzIBN6n3pqmU9EFDcjgNYFPu+WqrM1sOQyznjPQWwTH3BSNDZvTTZy03KWSrFn7itwECsMhd3fvQ6re5W6m9hO5Z1BWhQk6HzN90fm/XRGWFVTmuVsfg3MsCpvu4W+LeoHdCBbf+3lAs2PEUguSpjm3Kbb+MuKYIbjWr7wOlnH8rSz6TNBf0mrOLzBWATH3dGDvw4yIziN9cMTx6fHDOq2RnH7965x1MBP1yHFbC6/Oln3K+OCn7jxAudnXmXKDFtR3b5lUw3MONjjvfocn6T+caltPXczl+HkAqaW4gl/1VomeFha6Ph2Z11xRwywrQa0V9vC0+pnxzLW0c6fSzKHf2T5p9Oth0x7CIDLDO4heN/c4vjdU/oDPXM3eQJyj0DidiHDNiDCxIChUxK7thIWV7ZL8xQyDmwQJzVo1tRCKaAVoTwDcilU210zLTql0nf/Pzot9nPlbLrLP++CQZMq+WuWCCNXDplryT9hrD18/T5E7qvGYv89m8TBf1bL+rpXR64ykZhfDbXZjfXyP0mhcAzaq2t7E9hXswEYZRxyClhwkKLsPgd6b5+aCu+GEbhyaql06cgno6F56ubB78dxGtC79djPSQW/F/mghjNkcG44eupP6MR1le5gz4KvkSLK0l+OpSsUhuELH8Ek7ORM5zvB9+RVB+1X+oZRUi+XQ61wXdZJvuI9di94HXvWCWSfHtDxjSNmf3+7anPq0HOeobbw/il7MU/EOyHgWvJv0g4kdQnTHARdPr7t2c+zhwuP+L3bxujyoEpZ1gPqTESaql53M4soLyTzON3YniJVCnCiqFGLTsNW9upZbiUmWbU247+mTQ7mnPu6r/vmspOZXjjQ+qu6XVAVgmMlcWKNfGanWgt/l7AsnOAB95/ZupgMUvFZvzi+Os6ImufT3fBeLNk1hsV3aB+i2W/vja8SpRPXOQ7V+eDQSpqVgZX+A5yue6gBALLfAfZCxVtgKe5jQ1/bz1s7AQNwccABvPE9Rsyd/f2OT0D8BiUNEtETHhmQ47MssIIg416jJQcc+y4bShFYlmu5PUWbC7kLoo9OCzZjUkrV7av5VTJLGx8L9mBj0JIQgKYqlcbpsIa+LEl2t3a9pMdvYsOEP6F49StB0qqnq0xIBvPgphFa08LuWm0cMSB7lKnRZ98cdMgkVRVxCXRXLMSCstYU83S1jgfLvwq4gwraZ/CdJLmviqgNZgnYY8m20cbNU40MAY2zv08xjKIiRbBnTyX5f6hQbjlS0o9RnvF7vD9OZT9AD4o5Ze0/MeemK3h9rywu4+RZHEsAnzEuUIBg3KFzgrxQIfJcvMs2lIWuSSx3hm7OW3De8DRqMcAWb7xahqW29QEclIWXYfakv7dlNY0rJHOunc8TA233EldHllu/Rbaki2OWBbb2Tq5rcFlFfOjzMWHTa6FSdSbLIFP2DA/z7CAZGN/6hreVzNodX/cmjrW1eYdCsskZmMfXC1BmXpG/+DvNVtUQqHK2eKfdezFQujTiln6lHG5tiRj+Xg9buiH1BbG2d2e0mWX3bOCMjwLM8agjK+VYyoQ3vHnlxj1gpyjO4jujCyb5JDpTq3WWNCsRWgUWmsO/kVHK6UQZZ9SKFOtNnkhofYj9gfnKI1WsqMblRu5Av5uEJUCdmpzOgkME0Lc77ZEss48BwaCCBLuYe3Id/CA02hsQV9IcZMSmfsbr376pcJ23AjwTKGR+uDZHgPs/K8LD4gW5PMei0QwLWqY/2jXW5E6pLqbVCyBtEclpIb2tC/uXAxqRcWB8k2x9LhdS67RDTGb1L4rAE66CP5v7t5Ef7yTarK8KDnq7/eC4hrVvEobM4lgMlgqpOq78/tkzEP81c+7o9r5D/uBws8xAGmllZcGmbuxVzeRVBTa6PGfWzDPYdB1EqYnOP/jNvDlqJ4QucRwpmQyNpFoR3J4rqkwKwB2ByWXJ8zz8L9R0QbZ3q7bIQ+iQitpIRtLn+G+JEhnU/tDCFS57xgRztGZ/xn6oRNbqxwP4okP1l0SJZIqbkIRzS4PNa38vYOTZlHbFz/PmiVjAJXFYJnUzIlPkU7OFHZxnVEZpqgxN37RLbOix5hGg6Gbvu91SeAv9pg2Ds7zHWik/VjYc86dJQ4l72MFWc4dqo3XuICLc2fFR2mdo52TE4E2/LLZbuU2cHoAQafa+DzIVppj7tp+Ihld1UyWvfj/k8TXKzGhC7RQoDx1cykvdIQO7iwXMzHWNJMg/FoOfvkxI0RxQQjFvCyECvnLYpXiP+jk2LrpY9O6WfsnN8B2F6GMbfb3w05VCe49PR95BRkO+o54xezb9/XTr26fdyjcbMm255CyQln1pmhH1m4EsPtBBjfLBfRZTknQBxfstn/RQujRGnV2Rp+oKn7BItm3cHPkFbu41SCpjMvm+fczkILLLamg1EVv1do++11Pd0i+uMDRiYuNc3RA9D9Uxq8ppm0BQc0RoKei7Hn3iPLJDxT6rfEyCLRSJVd+h7vfrRGnrUooEL3YyuMtrI0nehd82AGvwQcNPy5Bq+Q1ommjoNZx8SzlDJ2zHXD/t82W2yilk6ncz1b3FHJzrHz5sEg619ZnURbNu4KHnOlveKrtZXsrFXJ72A44McYlcQ7CAbLI6Ohc8b5hoZlwi7gMi+S+gBbOeDZ/ivPK2MwAi3K272V73mfyo2/5P48EcVFJO4HnK+mDU1p6i2G+4pX+uEOD9fgwXX5pSjAo8B6k0SwX9JjerTq74S0jU8s/VDQ7k+7ee3rzWZtLjEuHUHY2jOmgqLunRH5Ebrs7RJ/Y3Nt4yJEQZhCdlZ/GkpjfiK77SCpnrnBddfGVJeCEud8lTF4hLlpBT7U7uFAQlIFNPEwKQjkpiAkn7nn1jZpZvrihcKZJ9g9K3PTTSKxLDJ17EhlAsQI8UQztYfCQxy1XVadvZleDE0Xy2GzkiXfKLj4LL2wMCAozOLGoSrcSZ3c8mSPLu2d1z+q+Rfu1eXjAxd9bcpUF3vYcB6R3eoW9BpkJoCatfSyQImjwmCrAQuRKfPeot1i8vYf2OO3qxB9c14wEfmOY2bku2WJqSbmVNjvYWHbI38U4syH/3bxBpiqu+3aDo6ElOr0AsckYdiDh/CtVlvlMhx3dQ/m/64C7AAIs/dOhD2DV3IYjiSZMQVv0u5sMJjGKIoCrZ0pCKQJKv2Tf277lwJEYc/u185K/ErYaRdPYt9pH3Ti72pJYdo6b571zahs39m/hYHq7kklsYScZn3tlZzyfe0SnX651vPfrXqyIvTwPbiL7U22F22oTSf1sSiF1J2iF42EDu/byw5RmlhGFPvIfE4MaoR+nQwEbnoANEWmanGXhDT1taFwQIXrMAimgFPBkWdCaJ7Dcqq9NfBfSgYXv7rCoABAHOjWJ0oMoxetxtUsMwgCosx02urtYmJKAIfVUzCROz7Fn89NDQRlb7GKy7TxTOH5jbU50PX3foLDQdGnoaS3NLDj+lLerlctToUm8q4X4cBUbunpOIUOCogn8hoXih9Eniefr5D5LOOW9elXyHivles6Le2tkz48/dcY/P16djZfZfFEtps2PZVPqixhJTBvhVOKmy6Lk0rcZ+JK0JxcPJrled77ETA3BGVZAnyvFh7BIMo58p+kb+OoNtdTwKhF1QEpnvDWyg2HwtmwI85X9QLasDwunDzLAXatZJCjewuODmQE1yBowXU2OfufAdvXrbUe19oP6BPef/L+Faqk+Uw39VB8PZxmuk07a++x7/aqI4tGxkhd+95NyX+vX0e+fF7ztTKMhS5Z0xrxQy95sn8W6tQjOf7ws2smATEEESsL717bzzuWQeT7wUCSWzCbx3VeU1fdTJcfMwYuHYvzfecWyTnPkjx31IxFDBPsLD2uczwnqdayUm9407ic83Abd9yHItKNyvVNaXpS9MW5TXYL6akgghcnK6irDzMne91roDDRJ/PhmBqao1CpLuPXR6zuybnJfDSZYKsjKY1nrZijLW64zJ/9Celhx3uNblrDszETogXrcWSH+7EULrNKF0gGYfISdjkQGJVdgaQMj4mZ5TvhsZjAUgUdxjT8RFUsWgQv8NxOSTjfVQQl31wvmfgDL5Z1lDDTE6qeT+05o+LLNQWi44iqQ8M7pangvodZX+F5AAd7xFWY2qNPDZoQlUjSAuljWjqaOvm85jKIO/9nhndX9Vv7PYnQ2SNDI8G21R2qfHVN7ek35aEpF6FsNUE+bT7HmMGIUQ1ijZQM5Y82lHo72eXW9ommz4hyTi9VVdqSCxH5K7+rl7m7U2rTaoebHkgD5p+ANQw4FVdbp8QvKQ9jw3iEUsvqFNF2kWFegAh6YUrmVf+gKJDgEl3RQu07AbxRUhwDwbyxTF5p3CrYz15zvDxOX37cm/bxyf4a+Sz3uH0gDeD4VcLTiBko9eACnTDMDHhLH3s3czGbOHzNZdKFVNf4dxEyblOUtOExuBH/O0y7eGRAb6vde/WaXOJseqfjgwjzRJtSMFHhhZ9+vOw49Bb1QCe12HTkE0RKwkHlNTtDzsKhufPGT1Z47+onYwMZ6TXox2IBy6rGGf2cVyHZKw7DTq/yX8ZUM0x7yG30FDLDmDOK076fl9Dp7OyE+b9cQG0mUfU5fJnbmGAL+TGN3C5uOZwP60q5OZRN1zfsrmybbmmqzVtDUwxqjHy/bmpa+zLaoB3kxTNvJh/b5ANPOKF/snvCnZqxWts2pO5yI2VD7bxX9esHtH77+jIe/ECnd2wyv6vOT0Dffzv5VIdL4CqnFt8ZB980J3xnQRPvONG4nt34ozLPOBF11RmgjrW2CfvLFzd3gJIK8oVKj6hRav99wBSJtk1BHBPLm9umnkD8nCyqrQDSYuFkguWyutU3cFM4oemVYaFxDP69H8V3/QnINabh8XiFU/VwBgpEEtXyp+VEijyKVdZVPCnFgm4PX3HSE0WyVfCZXUfzVZE3INpd0XEmwQC6wfBD0yz1aE5AiUycUAn9KZSPG8jlOLB6DfNGKffu9Wqk4cjDukVil8wyGJhDIAD6CjIPt2rTDAyJPgwlWojgXsdwnsgweuxB5Okfg07hezmoYn9oW2pHSyZ57j+mUpwv7ibujJFyycO4a/HM4q+sHhvoc+nSKJOtA0/H994c1L2hYByS95amH3BidaotF4RncZszaKfHaz+4kd1tXDwgui0xurcZpvmhyji5gP2sux30DKyyZZbusGjW7mVuJLPY14NWH/iD5t2jsFsYwO+qp0HH5qIlt5eqYmZz+wh05e6i83z1Lu4UJGxg/p75RldgS/fT653rma2RcEBs3lK7WicgFnrlsofxL0bpt5fdSQyJJ4JXJdGxtplFubxvf7rxJTjYZ5NikAXOb9A726oo1xZnCPpX0+MX9iuFMu5RjVe+wfsK7GdIZaofnUCexpgz2CIhmX06K4onx9cr9MjbjiI4W/PJq0mP25ztcsagGgRl6jqVMiVuihH5vVvTrFvOOoy95Gg+s7qP5Yr2jT9oFsrFUVWnMN5ky/pj5KOtz5kUs14n/few584zh9kCxlHdx/BKeSszeucfAZcMZ+J3wX3twBF/RXlDa5MWz3Ydpd0vFk8xWcl1sf7aDq30+P2bzvcNjuW+NrbSFUoogXqm+lRje+5oaRral3R2qwjjW3InVYrRhmx3xg11mf85/CiTMtMI/B46zvSJ+oY7wYLwkw95DaxT4qerGz7BsvZx9KfUKuVd3jDLJnVEAlEy17ND5xgCK7RKTE8Rb/XLmK7Iv+3Syz5idRkFd5vgXpBErhGR7m/mFCa3DQ27VzUcKHFj8jwUD4fL/939FIDFOd/jxSe3Jq3Hpb8xvQIThbO8eP8Mwoyk=
*/
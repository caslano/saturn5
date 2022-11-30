
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef state2 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef state3 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef state4 state;
    typedef iter4 iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
{
    typedef iter_fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
VS/riU72jnJsqwYbY6aMR8bCOdpERBMnrV6eWnRz1rA8+JjUDGdLRLlyIdzdmPTKoCq/rJ4jNNbJU7rUbMGJWQYqaB9427i99VHXu/cGKlixgUU0PbKASWCji+LcIfVbWWDSEWXXK8IzWcmkW7yrJ2eIXUstdvFlirXJavgGA08GZVQRilHgl+25CvQ+O1iyI/b7Au3QBxGMaIKMEOxkoqNE5hLlecAsyUtVXAjXQKliGgS3QhUZpRg5Eq1Mu0NjGrruPASgxva6yFc54FwLky7hLHv8h7zV97sTkvkf13UZafjDxOGyvhB8BZ4Ku8l2x4pWSSSUvwh9kQ00ixIEpnEjdhr6urWg57789AYcrU1TSRNNfORWeK6mZG/64xxbZYGPsGYLVJ5U80RzHl5kaJhqn+FDw39q5cKqmafBsOoDnXR1FdqMQfe9wUw6x4aBJ27z28gZomq4kGV0tn3ruldvSiAZpm3CL+oYAQ7Uc8tnGl6T4umI9DUi7pUFKT0XvfnF+z8LaZmgCa1eElOuZ8EIobhBLMrS38NBDGppHUDgudpsYZjGs1evfFytgxCWslMRepX9o8AHWPsZ9kU5F1TVsy+dZGaYOxuTOX8fWjnCZm5/dijuk6DNHdOKyxc8/kQR+eYkNJRYJfFnBB/kGocLSxSz3GKDsTUFyIllClIujmZCPbgtqVKdpJoxmPCJGxGQOzXXDCZDjAZVlTFlJMA8/6Ni9CvWDw4E1p6sEKrc/GtcQDXZzeKWsoEdkSOLHgfeCIWGmSuLqi8sMaXpKEeZQT+naOgmkYVKEui0gAWlkJwZoKMyPcsDzPJ0/cTa1nSakooYomHBvHblYWO20w/EEq/gwtPw4U/HVQOJzPDCK0dicl7P0xCQD6nT5ws5ax2zFcOYB2Yp2K+W7TpEupX3yfBPtZLtRG339XZ5SNadK+/YWpPtLOP2PhGhMedLWwIpkRPZiHO8zFvVce0ukTGqwdB47RqGHOQUEYCq3T408BaLJgZ4RvN1ZcTk+zad/xGwQ74IUJwrUPdVOhfCCnWTpzAe2lgaEB6gwYV2ERYesdSsSw3FRZyn/xLEzKXFFAKA2+0uvH6IS3YQjIbGqnKaa0KNWTM1Z+vCpVnBWvIVRGmXpztL4IS25u+lzm9KiWwqtWRbpu8YecOLmo0CNjBG6HBhqXGN+8lUi0bPdUucJjOPON1vZhbmCMlzTNiN0zA+lm9hkhexiwTS0oi47s9r9gsnZebYd/YWP/Y/rUc/DT0IJPWALzklux4qSxIr3NWoaS7myclNRCUrEtjGtXZ36QzLKHJqSO8rxL+s1tKgO/S73wkrTM5UtoFR95ed5d2Rd1zH4ujOKWIIaiuKRpZiffITdhQIrGvyngSNHQe/7OlzSe/0cLFiNniLFDhGojAqBWqmbq2EGGOU6comStaVKp9LgAs6cf2BuRSRueLUREKgpxr6u1XhKHXmiuaMjRLbmL9ofmfV37aEwt9NQ76GpWRvbjao+WiuQ26QGlZbbLniHgUkxh4lzwETFNDOTauVZkGdLFXGPoqe7YUXVwHaCNiTusp1htHuc43r1bHD4EJFML7/bnm4KDrg/CUioV1xZZSJL4GseL5rOvnJqx30FkqgIhJkHWm5UeQWZrjL+OL7siGCmSu+9jffHiolyyatb1Tm+NgfGdv0BdwPwE9IChDA78cX8MUVxvJkiZYsMKPOHTUr/jOLKPlQRTcai808UNUTbUDXaQoJRCWrUyZd3PJUbOkCEBrou6MmrsVyQVFqVfno4xMxGBlFO2KlbhNwO9MSVD8n1ZWluZ8hhXZUonjAL87hwk6ccCxpOMagfKATpzb5ISGHPVyuWjhEsJyeFQSVtwZeYApA8GsaBcOejV+weZYLSP+CRx1sUz65Zx8/L3+q6izmaMMeDZ7YIXwggMiFX8x8flffYKRGKUWLpH6LhdOmndpTsmh3EQrU8n0ajQ9Mwjff0JhEJ0W0saqTTbt/I5M6NyE0PL2oADuvKepsp0HroOUuE9SPtdF0SosQxzp7wP/stmZIpR6vVPgs6HT6TcZ1AFDO4i/16e2zZ3W0iGwiiAz1TKBs0I15Hj9Y7gDOPxf/ehjQbjY1+XpW7m66tb0AREdCleJxjji6EEns226iSmDEExmPJtxsqtjy2MPkYGYVeXrvHrXMwy2YhuCW4vTqwqT7Eo9BP5LxfLYK3eQRd1dnokAcmLQnWmeWarMJPKx5bDihrecDyDrUFoG/GzgMWiGYrM7RktkB7M8vspBMW1uovbOlkO6ORypKELCdBnRT6PjxRdItGw/uSl0cjObH2m0mDinIGyjCnfRhlA2axKVtBcHBdZ6FqLA3q+aGa2I0UeNrMUugrfe3IPNvOGZkbUk2RjHQ596Y8vbHdcBTyoFh4UzSMDt2x/Bxd8fNSvD4TpFlBQD6Mq0VDA7aLhft1YDN8n43teebs7bF/yCx8cHGqK/cMBeMKLtSpOCdZU92kwUMpL1HkyhOu7aoDAfvBU+foBbS+y/clN/8dYJ00itJZgw2cGxuwUWqSUDdTGAAWsMvvlI5YBvPKKg+vtIBQtTivzzk5E+15fyZFAFxrseOx8TqE3PzAv7A+pf65/qH+uVv+3cDPpJb+Q1RxnL52Yp2HC7WjpicixxfXZcB4DAZy5+MpD7GQylvCiYRgUI7hJn6vvdn+XAKXwv2DvN2/xDfR2bl3uMnLKRLLHlZDgxjI52+aJidDa5VAkRkDq0Fw0YJhpHqwLpQOYxwnSfMT4RP06/JuhJzQPaRuoJOY2+g96SUpLQvONc8WtK67ZFuY8qmxm7BB8yrGnIrj07EG+LWI9CrdD/z/ONhx4ikNxg64+GDWftj4ZLWOcGYGHXoC4XZVeuuvWCxuZVk1/HApaF2Al8L1eBW0RlIBaWUmOhKSXvasfCu3HKKnE2rQ2zB/poXHXKyxFW2XOWooEYOYl8fPmOO3wS/8MrFn8Xf9C1MKysTQx1FNMgJPfO43mcDq+Cvipii5abhoMD1gPFMgsXgbVp0e2byfHYEh7jrrU6lCSg0sGClSgu2hRTYtJo7gRiwb6uApSfMNjanOY9hkIWVkzGWfBCNdwxwF+ByIq2j/Re8wsk9Th62nwBw3evoK86+6pU9RmXROwLSelotBZfPIIrEEw8UHk2DU60YCBslnwsdg+KPxIkPda0wSkINSCFiBJOQgOR4RsOSR6WxjJsgK6HOAVRnhhb0rv41hjJyl3IQRps/D43kjTmRArW5I5wUJINKGTiuqh0/k7nT6xwWgOggifRhGNuGe0B+RsJIYdYf0EM1CyMKJ9Jk0ncbCvN+4Vkwr4j6Zm6aVUMV4Xp+qjEvcRgknKnLbiMfhdd7fFxxtfxnk8ntt75wPdCyiPqBiDgqfpU4oMRiAKVtrB7FQLATFglKYer+l3h2xREupM9h/QulDB7QLDvihV2vsTcluN2lrJdpB5CxpHPdFtaZyKWRbqaJAiMsXI1FHCGy3U9Gm27Mq6nNDl6dGJ42koIw2+LzTXtvZcIsAZngmga7hpqIuSLuK9vlwXXqUsIe98EhLrBjxERaj6jmx8Ig9EJHvySqgxlKkelxS+pjBbYJJspOGpq7xs6nObfVWHVN7fpZ7u5SK+5seJgIIleTIXXQFum/cUCOXQagS0Er+ErrLwEOhg9wNphbIfj5IUwfZtR71355Y/nEXuaNWGdCfjCP4UKkf8qhozAnMNijylO1znHxi6rOaO/rhbFRRqw1zYSD3ag3LNcoHGrShrm31qB1eLAdo7OI0fkxR3WCzjISNzGcXAgeVTUAmtYraCh2AqjDSTAFbLwthZgqb1xi4X017cfyMlvlxfjPV/0PC9mdkjEFmF56DicUBYsjOcLppE/5JYcDDLaP1WEZJerqomjFOjWX5Niy7Yy16MpzYv8Vw6K16kinJIX+hSdR98i3edngwg0yQ/iXDtIP/hrZzN0/Ljp6LE60OsU0T9Z8YnRGo5nCKVeMz9i/A/NFaEIb57iS2lAwnBow5RVFRVizdG7JhB/e0sVHW7aDT0jCkD73dIpZR+zg9TAGSWq5Bu0MOlt8uLRiXlgV7gza+yhQHz9kj+GgJftwXtmBb+ACgIsfQc8xupGCeafDZTIyebH77PjM0gZEtB/OD4EvDpjnKQi7FSF+0m0ezZPuVwqISN62NaolUrHjBsie4GQRnWZvKwIJuSs7WzSbvscq6NUOpUsAB3V9q5glmOZOwQV0k+kp2HQjnTKTGdSZ0m1Ld8gvXn88Ll8krT2f/1KcXU0Mfr7oZZGXCo1/6wPMuq+iWAqKrsHrNU6eKffPUcarAmU8v5lLeKCEWcirrSAH5rzcn1cTEpU23OGOjfuyUpddg0Rpztwt2JoCyIBWcRROx6HIp4bAg+a9Lqbq0v6kzJoYuKSKZuXxKjMUNlbBl7sXHgBKnOScVHnpWp8/HXL4PJ9qZscYsMx7jDRTqUscnhJPRtfKYi6Rt8SRml+QhP89xiCExvvJWPU44VMywpMaFed9sOywsbTaU9m7PfSdsk230iXNTiqZfseWXIFZk+0A2sQ81eUC/BBXp9jlSyHk1g+97SKL1WXI3Mv0CLkMq4MXEg6Xl/PgnxqT5ntbSwS5qvOsNm/NfVT/5Z+EMPt/mYJ4UTMwtZOl0oOBsJMevt19CSoZeH+QHIW2+V+L3IIHmORYmg47AuUi44DX64krCUfjjn9YFDz3Oq4NwtfXe6E1GIzXOhEU8s+emrSQUPRALDymnWhgkj15+lmpPzBpIKjXvcSw72iytWEQnBX1P6Utxh3AFDaIyZWM+Mksn5Grn8OFkpUzs3Xbefz14L2Xh0P5KvenjBE3HQLp8v5q/RNyrUSIjzBWv744lFoELpoCdqCQ/NO0hOX8Sn/PuET0FTgAHd9OzLKCd4DAroXHplIuTNKzV7c/KI67XM1fEYkVTdfx1MkmDGrygpvMWpcgOBQ0aWltnfY39ojVAr9VgyDT9lwVg0APWOEYZVLvHM8mBPJskiKn8Vp1VLDRlUvWU4bFOJ9h4tJZIAcnVwdYHlLgpRy6LLcDYv29jJUFgVkjFtl8ilMfRgmFOJCFmc2JlA1NMA/5uZU51wD/Hzy+egwDrccJgPHbDZ2lyWq7UH8ATq6ENqDHbAcYcW8K/o2fMX7e/q62BR3tGregpH4nzMdmKOAoyOfsHRC5IJIwFWFYBO89sp4lmcq2gzn9wloxL2tCmcXzhY3kuJAinO61F8ulJHBmez9vR10ngEawfLqIVXO3JdwpN9aaIbS68qbl2YesxnNskHZ5AlxLZf5RpxRhjN1l+aXp5qe8dmbnwzptTLMn11PmRN5clVx3HvgmjcoUdpoq0/wVSA3/lrqS2A+6mWicRdMJoX4Mrh0/tFcEuN9x3/sHh8zdrs7HR17tsSogFWgU6LyY2+77PYWZWUndBjzWqQpvQVRlex+7U2hu+B9YL2oqOANICjFSioII6+HAF/qbOayDNIyI+Z93Pbuk20ZiW/r7j4psAQNQj7W/3vP3eRAUX21tYtjNMD/oQ9dsItT7+lnA9agIIsIMWlvw3ncKi6feiNIqMuk3PgDY7FUI7yNIfULElX+2Wei8TMMu293Jsn9QQ8xDQJ7oU7PJS85re/dzsKbg7AKAKoLOAPYRATJASjnb+LBixTIJpjxQZlSikRz2RMG2HXFIqIGEyz2EpzAgItZ4pnbNUbtotWpYWHrdsK3s0IKCvq/j78sR6il0bVVTUaL8m9g9MwQburvC65OosQmqdoqW5dmL/g2P5BupXqc/hsmNTzsC5UL0i2urKfKzEV7AltQIICuj9hu5Fq8k5x495ocX5LxZhfU6c+scWw9ZUtiuajsxgigZ/2XxYcnwP/IzoAi8gArHYd8WYpq51ZQK4iLEC4taIPBnjULANdhJ4sV/kgadK87vmPhz/uySp1GV/nVP5wyg4N+2aMryKchAvcaobzOuKsi8xBq2vXAOKXf2d8dDxYUUaTkdSooC8iQohJx5yicxMYqsjiKmLkOekH3LWyeLv7CnuqYhsSIVj7gJcfv8s+VBMvAoM/VK1kS2+1NJkyLWV+LjmDFpgdj52kB1NX3r1dMfcHt01Z/eyuKgapMLXSjLxPimPMSQxIfXVVXfXNdJ6h4MqzQJah4kMHj4SZSlcyALqkIWAAYl9rQfKhsJpqio8GgC+m5AUbaVHlLsD4521sINyXwebLmsWLE0MIUXvBaAd6NYVNFcZx199/X20VGTBqXYsL0ImDTctjAaPdNup2XFxJ0VgkiiiW0TAm5oder3oMkgDt8ob45Svi2FRicun35t7WGYJWSs3ugbYy2Cuc/leABz8LyL4V/nFsJ3Hu0k5o5e3iks5PEjVKnL/FQFrD4JIeScIz75yvgeG2wkRUh2TaVQnOxlV2w+dK5XAKc510C9rpG9BXwFZ8FsDSJb9iE4d+IFVuKRWnt0CFSyvywV/OLkZooQ83bNkGoT2oykr1sC/GT/erNwXgxmhJr2j3XrIzmm6qitMKf2HXG3kkDgBRJOp5PqSRHccfXOwgvTWFwSQhzcpTaiLaxTkrr3WnHaQrXYLs/E/gS2VcKsU2bvpx1uMhY5fHC596xcvSxhI03zrRbjjGSQPvxFSkuNbLUyy1EnNvKizTWJB8yJi4Q/KQti19OPC6aUxc8tVDKCs/AXLvWLF7PZ0eCi4BHE2N40kAnW/RsuQENCnloVinlaWJ4yLcrMiuxvNFvuGDYnSDdaVZy1cZdoAN7pMA7pkAcurJE4N5SCcqG9K4T6vnu3IvQkf+p84u3AVibo90gZn6tdnDE5ewMCIWe8jqcl0umnE1mrTm75RtP+feRxzkuQpWLHDs7KKSqUE6oQD55+X2EpnC4ihULAtBe5YDZwyuSq4oCZKH2hpKN4tch9lIrZ+wfC39Zxb1aKeYBNsSHOK1txHSAuxhh8fQ4nHf7t9pA4pfBT/x1uw3tWdUTDSbWR8bKNDUL141ksWcI0r7uhBntgJ01ju8vY3SY3prkd1GPIkGnlpDn1iRygFsJsHHtV+K/xYy2b83YD5F+Kpm7+sMIWqhgh9jWd11qNAZkf3HAdf7BNRkp+V+QYAUFAywo1b53OjQtdZoVAyfuK24KGzDfK80ixkcXPd1gGeD9BcW+6fSUcVH8cELzpEjtQdFhUdiYYLxGFaMb2GieXLOhDAVEogIxaFb28kwlt3XyFmilw4etzJki5Juve3R4eh5z1IshhW5IBvKZyyoC6JN5yg8aSg8jWpeZTetRjFjst74K/rzp9kMF60tKCD2beYcQwZO2g2/rV5oexHMKxbMX3pgL393diHJT66w8fKOofH9fs9ssRcGNBvRtN5FyLh7a14LfnjvHpnMfEYvBEWAlQWfoEmhfSuXozWCz4ppBLwH5LQicTZ5tZiVJkUo8RF86eXjdzVUqDh8pab/SIgBcfi+CDZwYgrWnEWGaNIEG+syQmTR22jrjiARdCQDfvzPaYlSdsoKns8kaYeiE35vMXV+7nU32sc8Ix1FpKLRZvcvPTXN5D10/IxhdDOmKy8t/hKegIEY3/SM4PE6WcsHu1c3r2X+gnk0i3Hto1ZbTq6TIoQN8xSaWrwdWRZ85AQ2gW3NDz
*/
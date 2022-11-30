/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_09232005_1454)
#define FUSION_HAS_KEY_09232005_1454

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    struct void_;

    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : mpl::not_<
                    typename result_of::equal_to<
                        typename result_of::find<Seq, Key>::type
                      , typename result_of::end<Seq>::type
                    >::type
                >::type
            {};
        };

        template <>
        struct has_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template has_key<Sequence, Key> {};
        };

        template <>
        struct has_key_impl<boost_array_tag>;

        template <>
        struct has_key_impl<mpl_sequence_tag>;

        template <>
        struct has_key_impl<std_pair_tag>;
    }
    
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct has_key 
            : extension::has_key_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence, Key>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const&)
    {
        typedef typename result_of::has_key<Sequence, Key>::type result;
        return result();
    }
}}

#endif


/* has_key.hpp
QWoDtVJJN77HBSBQq7yk9CF1dOhmndN6sJ2LTH+oZKGfswf7jNaDvi/rF/QQ23ug4Pj5U7OOzh2oFzz8LiXxsDb+mn9SllZ3sONJq3kSegPRl9QyXOiQVlBtmTOh6dE/ogqq+JhqLYuPVX/DTCKzfsuoMqtXQnbLpcorve6o5amJQdvbFHzdlNyl+x2Ctsf352o46uuThmwn+Luy/2kifkodYRmi2xmZfkhimAor1XBOGd+dYBUsEj01oK1Z4U3gkoE0sWzACCMHSwfYiHHAP23MsQroYZW1sM6XFXWQZECi3bhI8NTg1O1G1UuG8B16lGH24g5dk1BuR59nmVDujKY+HMUNKldaGtmu9zU2r0ncrtecr3oUJe1r5IS7poMmwW2XOhnnfhxsNbT4McllK8W7K9dXlSnXV2EUO55WcsbfmOKh9fb4o0oleG2M5lxCrlR/HX7SiPuu+Pqp0qe29Gii2LX3kzwmkyPl7GX6+PsBGpRfNe7Rn520nnvVbZcPzygv/4oG76dwe9wu6aEShL8BKu8iNpSu10rysAZ73ON2x79URuuXxdfPU07qgEH2HU6IkviCOx4jCP06Sy8p7ku2S05i/eGRNtSf7iT36SP95Up5x9l7qVWafWmvsi+tiyf7NaJmuHwRYGUYgzf+hIgZLbezgNhlV9JwFF/rA6snwu+PLqETzZpFWWw3dO8O5fwgDVD8f+qePzyq6so3mSEMJDAJjBAlCrajZk0QMaiBIZLEMHnGmMxkfiStIYk1smkaY4wzBNs0BiaB93IziBTR7vJ9u5/dutbab3/UImqXzfAriSgEbTXIB1Ww68SBLv6oAlpmzzn3vZk3P0Cr+8cufF/Ovefce+59d+7Pc885N4f3vA8DHSXumIO2pXw2h95ZmtA7TUNXRmllSTSdQgN8348FHZvqu5KMdcod2rXiqGLxF56HKlQwMLTEXZyo496FlHm3WZ13jTDnkvTQ+kH3bV3TYZosUuzrvsRcZnV05lVdmAGMzZWJ0/CtMA0fJ/4Tqez3EidjY5x+luojTfvPHRu/7+IveBq1PH9J3hzpXk0dGfu4vRxgS50kstI10ljriI61fT1rAAcJylSkkrOnEfCEQ4PAy3BiUKeFfT1lqA8Zno3jWpOjAHJgQ3eg3Y0yCjsuNgpxexX9LJqvH6fh9yINv9fjlTU8yfobF0MVVZf4Lke9kHilSeXIjVokJcm2azH9LOW+WFHDGkkvGE11ZTeiQ/zk79Ur4bZI6y3/pLmPMSa8aJIbc9ENRRdGsBfN5Ov31MLhSfQ/1lYSevo3guIANUfusVhgV5/BRkMCzKIsFE4rPD1SbrHgPYr1v039VTq+62ywFLAyA54NxvFc8KiCLjMjphiXN+8KVP2F42BBm4Cb0t5cchZbeDS/N69NmNdY4IStP38zHvc8d+lI2or9EXjD9vxBVt1sPQRVyWZpbTpI2NvcZg+dfz5aV6yW4jZ9uhsq/J9no+/KWBSHtVC1/r/DBiBvrQYnLw4rfJzWF/JfuyAyrrPlZcPAgQ+AovALcBhhk1nHu02m9RMXIhFoM9P6Q6hVwAezS5XAGq3nTf3od8J6vruI9jw3qWqQBaQGicMsQe52vHsV/gZvhT20SQw7aQyHq3AAR4Wuy6xvdb+P8ryH3g2nK+NXYTw3ylgjgDsRHcATyiPyufFvuZiTNgy02ffUoX5sNv7c1S3s7MCY9yr0Rmt0Rl7H27a1tyIaEAsiryvtRO8jxifKwsaMSzSSwiEC6b9gQQdDDioPGTn9vS2C9y7MXYRKnC1KyN+bq1O5eqci39ywEQEOH07k9fJOIyKOKJWsLFpkD7sl0VR9JH3rKG3GdHydQU+8fLGKrU+XzhTTH0Lk5B+3pNCXf2eLOkGeEBLtPQH5GiCdL9PuppHbe3Zo9mHKtEokexJps0pyJZB6HiZ0fRya1iSaV8mWvCNmS67R7FiOx9Z4fzAvp7Alb8zTandobcm/RLtDuT14OYU/GM4zpT+YL9Pw0KxH//aY2tw/T7LnVJoMjlRqi2tWo1ZquC5aQ7CpNbae+3ruJrQrEV1O6PpE9MLoQqSx7vxqK5FGX+0x5XzzUsy+M6ZJWZ1s3/l1sZqViuOT7T0n520WtBXU9m9hs9rg6OMWJUVLF5I93Tx+faO2/IiyT4IfOWxUrJD1eKgmxaXFyssiHVUswxHaOBk9Q+9LkLyw2bVue2jen6BxMlCjQrmzQx0m0qpQenkDy9BVa/r5/28NJuoPm/hUVEWnwE9GFbue++6/1P7620mZLnJeRNLkNZuUX1ljv7KJ9CFu7ustgQ0wn7h8c2heBvRVuLQ34dpD0hf7EsIa1fu3qNpDjN8szq8U+aF1BGnFiFFXCUC6Fo1hmlAfhnjOxauM2la7YgljVC1h4lQqSP8FOFMtbbm+eZewbfkqFi2k/8e+gX31DJhDAmYpKniwq2IHviRp5VHDQ+oBWFDkUTlup9NJR9OYn7CT3Oq/jh2EnVHoi6dh/6H6LzNEE+2KOh+pTDrMPKV6FLgzibSRk/CKAUmNZLKeU3g6HxaKQ/M6CtxO2KCpPqRX4fKBc1tB1HP0a1478+TBNxyOOY8ORD2m+r+W82gYrVr/0Sf/Gv/RO75UmETn7beYZsMf+b+qxV/4+tJe15oVnBJ/7E+FiBeE9Vr0h60eV9fepvg5nfr305r3sV/+RZw+NNKlf9HQ/z6Z/qSEBiRLq8vXzIfKBRwGzRI1VdE4K7VWl3e9n7ye0H7sBQ1/awr+v9XQ5yXT60c09M+fSaKPjmnf/06mS69pvz+erpFP3SOrw3PQwDuyq02vjpxuAzrr0EWdiHEvCN7LMFln22VtRt49kRQ2wUTmH77Sji+MLB+HUxTkv8VAl4fFaG3t+xvuT8F3FecCs+xcVtbQtoC7kPmxR5EbOcPWYrS69V1NdHaIZ/POdFKyRUqytpLwFWTD6zO0pYWNZMPru9yt5OH+bl7Qc/mY4gbOlcjreoWX8lmmtvmEnq0WkcXZdOpjznbdMV6c6ORl6GKtQ9/V2TaDWmdcoUHzVIv+ABYs6dPgLAc2z5WHePPM1aPswNaIw90V9UGnUzhCw0FG/o3NvMV1belRNynKVXSnE05yCm5ExUHCKPLf6WK4lfCOtpyom7k09Ued3KbaQPsaeW59rBhvimKaUxVzZxSpjxVyS6wQUm/DfmAa+KkyY3a6Y+VkpijnrC5FOSdVpNKLprYKJTohbECHRbGC/0NxmGRrR5nlHt+UncKf0gTZ1q768XiKbjw6Ie3AVvKbCuRJsgDHvmcaUJ26dLZNiVXyb3XJlXSmquRtKrJVSBeEWLWuTa7WJ7pYtXwmqlIU3cmq2+PFxVFvT51JjqBeSRilPicfzFPUBL/gJpzqcLbXIYeDoc2v8s44yMmKemeVU3UX1uMlux8a41NUP5dlLmoVdP3kBl5uLl9GPOFKAdeWloD8BkJk2h9q57Pwz+LmM4bX8YYRgSxDHEbZbmSOTDS0d2TJdsCYZbuZOXJkew5z5Mr2XOYggzmHRbZbmIMM5hwFsr2AOchgzrFEhiOlowjt5e5YLovLRwSyuykhuxtcX6E+eQc19bn7Z0nzr/GQdv5PQT+snf+T6aKW/vlTSfQJLf1oPB0tcoxokNM/7C3q24XuzwXvor5dnTiFea9lm9Ya6OG1XLbBa6BngGa9JCxcrPvsBCpv20PLzTphD9uAWrolwXcMfbvwVRvBl6YfLi6BkHdeMXos85qL0QOud2rxO0hN33nZnCnCnp19V6QLye+V/SAmv1t3qn2qIKhPcPVbWiGmVbDut/QARhHpPW8Zwlugc/TQlgV9fg1ZNgMGpX52R+FRj7yd4iHx9UgEDkr9w6b+O9JI6To3tPXXgoCIojScaMstBaYdLkv+YJVloVRRhohCqa4UcTdINbcDY2woqWIl67fgHFdaItWVD261tEA4+K4BGmLZG9gGRdst+L6C1w2Va4WA/lO5uwHC7RTOPyjXtACvTogte8NrDpinQQznUbmuGSL5u8PXBMwB+jgNnhBAmyY3NchNzcBDrmiFijTA71McIT8bn9I+PdvkR+1eciFGdykj/ZYbp6LfZx0Gl0AwU5iOwSIIZgl5GFwOwRzBjMESCC4Q7Bgsh+AswYRBEYIlwj9isAqCBkEvrJaHLHYIr2ZD5VgAkFyxcuohmAH/IdhAwasx2BzDtsSwrTEs/vJXC/disBOCeiENytlq8VI5W8uxgNVyTftqua4jfPVIRTuWFs4BkqXZgEmAL0K5DpJUdAS88COb/kLviWdZ9/QuREOovm1PCviO2B/aLWb/KePbXksOf+PpWK4l9K1t2EuMckVnWC83wSLyrzhV6g8/0IkdBmrVDzUgZfrQGB4tw5cn4scBT3Zz8OtRP9U8jzZEn1r4auiy44Kwbu9aiOw2CnReNXrYePD8fHaGjULgwny0sLsmEpkvBM+bg+fmo/UXmidBpY3rTkQg47Ep0q/1WY0sODD2cNpnE0dCR4af0XnTJl45HPKmH9l9/ED4zLG3gWY4Mnz8o2NTjC/rswKDui8ikSPD0Ty7KccY5QgefwVyHEHKxPmdS6DKCjmO4ZFXj394PHjkleNjx8f2pJI/LX4kQeqEspGeJvIVxhrF7I4lXAXAesy7ACXb1S3eHDbXzYJOOyurojVjX88i5e7jq5qvJ4qQaH/dS84M823NhWPBs3oZlq5UXvj+6rtyRT8DXYDVWd8w9ZfiWl4qLi21d+nl79iBla8Cfjyz9WPvItTXcMDg3c3STDtq9ewsmwi+ryrpfB583xgMGTPOc7WFs/JtmPyOKlYeNODqZkR1D14J//KsGNd8YKkfZ2mJ3EJc/wG4Zpw17SjTE0eHnRSexg1NZY2yw45cI6Uu9qDLuiQL+XXZ5O+4gOmb35Dp16+X8qUt+aXN8DPBWbca6pVlPdNtQwmB9XPvYuDLyj86G3B9dBZb0c0mWCh4UtX9OBY8Sc34Nm/GCXn+KlYKGc58obCGIQ9c0+ScJnIVg+NN01/X9ajiu0eT5aU9vZeSlTbzXrq0Q/QVLO1w+a6DxLB1WcBs9WxuIJdmbPf/Srem/UQP+dGGVXnqCGy4uDFOomxUPXgmdnUFPTDmy2S2hnxbffAsHOKr/L2i4LsOsN+ODYIqrdymShkCCRIiNL8sPI0fPhXaFOtI2szOUOGPBAE+9F7FVUgrudMARC35ELTV1+Hn94pstj7i1kfqqG0OKG3Tq5EZfwUzsLvj7y/xU7xiKO1HQuLHG1URl+bLxUDmgGLPhEmnkRhBuZS8iH+XZ45p9lPsp0n7rdZ3NPQfJNPFkxr6ncl0tMGN0vOT6Xk/1Oj7TGee+qjVfT2fo1RxNvN4oyRvHGkG24byf07NZOSnIjHBe9oE76VI8Jw2wXMpEnTqNAkwkpigSJugKEWCUW0RoymK2KvlsDcFB0GbQEiRIFebIDcxgYltGsIEURvCbUPc2YOyFKj9rSm0ZS38UMUo7xd8hX7yiiH4rvcX/44CV/cVl1RiIOeifRK10VzQIbmSerQbxg85kvdMavpHxhPx+3nA48Izx/+wOasrjU0bRJ8HLotBMmTvzhRUrB4OQXbTLtgL2R2hid8ji0wgK/ak9AamNfjQ9NbmMX1W6PFxQaBZMj9oHXkojWwTa5jH7PSfz+oysKvCaew4D86B4Jv5I/ojdv0f9IedtaGFqLhtywLu+SP+XnOWbMu6u2sGm7nfoBOasM5GfAQ3FnkVT2f+U5mFwzC7rfCfi3TPcIRyttEnDgz7FuIrsehbwaCa34f05wSh1TzHkIVYB6CNZnw89R/O8W9K4X9etUd9KRIZrCiRbCWsplyuLmcVqPm2wB4yj3PvjXUiq6mqddhDTwICYv69WbJHZBV22WY3vVCDjlxcq1mdZ7Xs8bCKetlWD9gGdO9i2lHXKHkaWUWzbGtmsD+vbmF1rbKnlVW0wxGe1XTK1Z2QyCt5vIMVPsnmYzVr0Sl4XY/s6VnNNvaRshy9AGB64dH1FNu0nvRHnkAdb2kbaXpvlKLuZdij5HBmE/5lT5DbGRrhbOPWqFMa9ii5rCHHEuwJ9DXRJG/bHu+IBs7H0FlMOyoNkojAKIlGANMkcRqA6ZI4HUCGJGYAyJTETAAzJHEGgJmSOBOASRJNANBJG4BsScwGMEsSZwGYLYmzAZgl0Wx6oXLOalmcA9EcScxhleSdpnKBLC5gleSdpjJPFvOAXCCJcBirXCiJCwHcIIk3AFgkiYsA3CiJNwJYLImLAdwkiTcBKJTEQgBLJHEJgJsl8WYAt0jiLQBulcRbARRJYhGApZK4FMAySVwGwCqJVgDLJXE5gGKPJBYDvK1OEm8DuEISVwAokcQSAKWSCKfByjJJhMNh5e2SeDuAckksB7BSElfC59ng82wARYAiwEqAlUCuksQqiFZDtBqgHaAd0LWSWAtR6FWiCyD0KtEDsB4g9KvK7wL8LiRrkEToXpWrJHEVgEZJbATQJIlNAJolsRnAPZJ4D4DvSeL3ANwrifcCaJHElkDXfYG1970IJwbh45+bdgyiXaYkraNuNbieIryPDfop4ucR6nBSP48MUGSARzZQZAOPbKTIRh6RKCLxiEwRmUcGKcLfux1kFGE8MkSRIR4JUAT/Dm5B+4YmaTOCpBu7tkjrDq28AL2rxeQF6I4iTgEITqM6jcAADXALj7JJ68c+Y+D29yZJaSed2Q0oEbG+0Z3tP2s0rUcDPFXfBP26hD67XxA8eIkjb7e04JvRn3ZwU72HdWTenVt8z/1dq00bx+gw3s9dIH6fWxsPoPdffHvdHhiyoE1A6Pu/iUQgjAPREQiQ945+YqsLVaP96eM0vssMHk7Eq0GThN4olUzSdgsaA4aCwGcSK8keJ38cZYZAAAOeyPhkv1J1NDmvD312Ckp0WVy1gbtKQi9BNjgsb+UpXPIAzjqhT14ErLuEir2rJDIeXkk21t458HlL0HqdjWcc9n0LYjcWjoWviMOmc6x/+Kz/cITNIbfZZTlOaNNxcovTT/WlI/Kv7qe3zMuwwcfhDLVx+4VIpGsaNrv/sQtoKgsnZfrJNHo7gMLvgsPzxEE8PNt1JGpL5O0A3uFd0ebjrQeNoTQbO6M2nPQ8NEdCZjNWbH94HVr04xnhHOvOhUm+8HTh0fzuPLndkjOvqQAAOvlBz746udvF7+8f/Jjf2D9Qzypc9tD+MR6tqLfu85lQOVGxdMrBy70qSwHLdrudHmwh3P2ahkrxDqE7j3XXyw9UZTfB3DdTqoE5x6OT6koHbXqpYqVpR7Wh7129VGMD9JS+E/OlugrTjsP+/ellfY9UQL1lfH273ZK1BqYsmL7rdcF3jRkHYGOeE2jIMKDII5CbrWuA41CNy7RxHN3k7miqCJQb0/CR7lIZ/lgP9OwpPD1oLJFqRGTVP7amLHCH8FX49XF+Ygp+sHouXfg8ydXxbSreYis+UlrMDhzNztBPRpUms0N79I+hhpnLklMrN1WF1o6qym4WpP0KaPTFNXY2QTZf+NEtph03YHvhSAz+0Zjxgdu/P03W+/cYPM7QgVEyAi5wwB8L26c/Fjr3WyggqIc+6/bY0R4u9M+jNIyh6esqdO2WG0v8e3P1
*/
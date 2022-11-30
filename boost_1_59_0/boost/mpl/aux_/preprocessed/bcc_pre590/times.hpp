
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
6ZgbpAQ8tro/sjBpwJo3IVr36SpPxHnHeY7mXCkXYoF4xLOnFp54Xr8sD/faI4nWuVeW7wVHiXuCkWI+2rvmJ9H4MvG9/C/QbzyGgRtlwr8M8ioGhIc0MorWEGas6kYs2eNaiddb/hDHFrwMYoywZVpb2NlWVA97Tyu2rz4nuASVHmm5oCC5lnTesskBtiF+n8SqnTTV5ALb0BHMMXUE2dBo2M0a2GHt/nHndfx7j+u8jiNeEoOGzzDe2dp1mefpCsB3BKlnlmjjynJUDoS+BKdS6FR3OETsr+pQZTu7I0dWGQWeWbOdru2QK4iEdhr3VAe15RdIjDJSuY7jXdLxzre6XCqMEZf8+KEvHN1DjDA8twDgmXdsW9/Ytm3btm3btm3btm3btu/8d/E0J21zNk3ankVTVmgquXQtbOY14ivVLN9MTWjlzna3k7cftcOp+8nOhSIbqcDmEHi9CbmtHkys2Ab3PDABujSoJHltmfPiG4qt1FKIn9B/n1Mu1WzDxESUcoBjv1y5WhGSXVmyNyNylPH/VFKuLURl2JcygNIaRLTG6HrEHsZP2fnQIDkaYJCCbcqyDKZceaZZNfjMKyYLsDmmK7AzDnf7kwVVCXeu9yby8T1EzHMfgAOSqu7O/yvU5v7pksnr/Zdn2rlEu9cCVDio4shI7qOO+K/rn5sZZj8ZGwIWGselyecS1Ugh8nQzI6TSkItiXkE7bPN4+E8pqMv8wV40FCS9NYstXtcBOWdGfya61Gb6hDk/zdUAWvOEvJdcAtNHpt9OHEUkd0IWN5g1vS4G0Cu8Q0LalXsS/578YGH3E9056KR5SeFuMJMp/eoRg8TSg1+CDJjHastml5ffo21imy4633Qc1GR7TV90/raWylHRmpPGPL927Md4i8AnM88vSsOT8oFKWvPIVB6JepWXjU9SlRcFz7zzk4lexYGOnOrh3kdMJZYYhisY+eENOgvh290ZZhWVPIxTT/YBDfsaaJCubnX3Y54yxqv1dT69HLRp+qFCNhCrf2uzbVT8lPzMvIpPLR+DSPthQDmRhi1ZOA/bpBwidSzp2jtf3fUuKwE3/A3ZpRdYhIpj8iGto7s+j07XArNYsGnHb5odpX0ojggDHgisASPl08ATpaHcwnnwv/7hX0HBp8becLwC9kL9GkvEu0BrdCGDsEtY+qBZy+iXx5MjJM9UAaTPMdGzM6J2tLZ2mxYOJHxZPXKxgLnaNPzQDTdDkHLM8kbJAtY8cGFtQQ1wo4v8kJ2mEB1siPYtHHPGZSgRr+TteFKY54B4XVVb/Gjk1o5/ySLroBFsK8EUuf+SO1OQxe7jo6MlLINmBkt6yfkcc2hqWuHVbbbuzkW9Rg3ZUj5Z6bEL1WI8ta9pvUsuTyR0pPe16cRSe1ndrOctkiL331AX3zU3367YvfUojuurDFqwSyGA0A+ogl1MF5QHguZuqBKKYsOpRpGRHRk9KOBgpB2oa4e3v9AoXQ7KHgFgc+5UvPJpQlNzicevfkYTZ5+/Qs1rUn8RPB5mCb2/32GHDkRj3rrWplngEYsOyQl00NdjqfveaQSJ+KzUiOMAEAy+jZfloyIIJxPO04bkhpbo95E6D+nTWvqN1C+Hh34uOkEWfC3hZr/QPM2e51kfOq9OGEfntRk8KSwHpcdNHa4NMsZ1fzj1UPCSej2fZmEmKAGDhOf1kVPtqPGkbOdCbBKoKvl4EQe/avnC/QMkO3aeN5xRFFi/dgJ2xd+6wXrX2VEU9mFQFJCiYKyYWDQhv0wl83m/eDVXse68ab92QnZv91yxfWYF2vEGb5XfrgN3aR0pEK+KN2ZORoYriVvRimcwEepRq80RC9J2UBhFYVdimIRzzIeqmKPis1ENjUzvSAQNU5cc6Y2qQ0OrvrddI4LLYpI5xByXNiOLk61saxlWNrGmBugO2QqG4DnPq/wgYWaC/mtdmptLUIvTFBynWEKGcrCMHodkQiurTl4w8c4/oIVzgKK+e54Tx4904qGKQo/AfwMPH6toIF64XkELNYy3SZTYlF7nysb8cSXY1mBeMCGJdsqET0AtEej2/vi9F2u9gQtNFO2Ihob+vRXq4O4CxOH82g138qy9laNaq37pI3C8P2fd0sI/HrDF/DLpr307gSSX2WW1eh2r+3eNaKqJTZ8Ix0Tu4kFFE3E9dd7vR08H4EYgdcN7Ictb/ya6Rq5ejrCzOhSZ9GFAwTzq5TFfY3LQTmoEtNhlScgdW2A6E/lr3iCn6JgIgHZM53qkNEmxjY0EJSpFDbUfXTZBNjafUV2Ua/qqq0Rx/2932ee0uWw8NPWtg4Haq7WbomulMaAzEzPKcRj6nNK9Qy5KTNVVf2syBqp/1YsDSh56ipW7CPiJJNWj69w95Xd/wWRYVuKfFqzBGUTToiitbBDEEOJOMjDoGSxh7qGupp18qM2/UwqFCubbgUhQ17bqtJnyjJdCRw7C8L9qPnrqLuvYt/e5djCSi+xCp30vI82p4ARTkAPBpaV+XliyAeWNlDTsoGTKIKfyvfru0IPoqUZffD7KI6YGpUwr0Hcb3AYNzFTUzpKN9wv0NHR3TwM8C2OHIlyEnOiJ7J6p/+vVEVlR7KZf17C/l4ILUvhXIEYATseaYUAaVYTNDUfiKXCV9LssaoP6KUiM4+D3C1tClONJz0dg+QDFcmmmFGAW5rsLi/NSgbSAc5f8ggU7gDJpI7rYLOsLf+sOOZRXSKsmNzjuI6gVH06R1jJbPRgRa/Lieh9eGMiljp3IotzV4L9Ch9Ap2IoGRbUwTcCdAUAKVrqUWbjBVwFfdMojWse94KfNdcwEKTmStbHiFt4q0m8/ZjVtZrlsudT3bUlrvdae/salTfmzqf7Npv1Z+FQxW38Kfj3CfmQdVCl8sEdMv/5r2TKkO/rCRrbnGcnuAWg3S/QLd7ETCtCz2P8ScRTQ3DMq2j36f1zgLG5Kw3tdRuY6k118qKK4uAWMj9dOrNvqQzUmiY8trWSQKm1PGqDANIVBCejWLsnhddqBxs5O4xscBKzXy7efq/W5FVrCyE5ee4Fmu+oFroeolzCGio6IpCRwc0O/B9nIF98mL+8Y6GYZyN3vD8lOQEUdqaODidHwpDFCkUQZY13vOMF1ADJRgVaMJf+ZaCDSLbKlZe3/TrBtP02vsSV7e6q1worb3YeNy4xyX9m2V/1GKHJKfEmjKXpahxhb9L6WOqpmwLtgccDsWQ4vx4sA0WXDydHvAK4c3NFxfMcYLsPm9TnZgxkuyDBtax6kj+4UCSmNP6u4oXoQlhPnbCwlN6FxHW4/zshZBD17AqLu+K9b5PPVojX74/dWDzXCK+dW7KW94+6Cj0mrqd1PLfuwxtOgW1beF1XdWYa2mzwSJY3OFq9zCiYAMhuxk2IzIZ8LhhB4jxWIyXIC/pfxRW6Qnb+8JB0OxBsrLZFTFt0BG10KkmEIO6txwcqkvyfoJDxJrrrA0C4+0eWPKwZj1PBdPGaENPZECwWeftdWqx0Agr4hbDBgQ2NKuRGy347CuSmrz1HW2+DyW+wo0qPnbraa+WQnabZKOXSri7exPOoNR1yvGFbyqI8amEXxxYO7FHtXEaBOVUT8TUMR1Ty+iiSt/zk8JHX0GPB6+TyfJOIYUPII4eFOxsI/EZ2vfQ08gbPRzI2PGF7VLKiy8aCF8zk6mHZTsL26fP/h9sDSZE0aziBPiJ1zj7y0I7KEbMzWF2AMkh2VDzCquz+u0qPZBENM3/+pDo6FgykhfxFf3xlybygXljR6ZAcubKYxT9iW1gpeSzz79uL2+iZo9tj2ZIG6MZHYKMwQUmWNgwRhHrBLvhFyZXdHKbxpxxFwU2DNhsUPZlvEEM7a16srPvhhiIMK0wXZo3ZQT8cxZyaNZl/w2YZHQFAE7U2wYglFc+CWQCXbWaivFlX9W5cAe/s0LbgLecYemtP9lCU5yzrHOBJjaknnwvW0sVW8XE/nF/bv2aV5ij/V8/sCu9QVkT1gvGW5UDWX/W7aJvPQyFjGNj27bHC4kIHS0W0xGg16LXyUU+TvoHA9PSTTCEyYVGltnYrfyMyAzRupOG9hhx0RK2gO2SpeG0UOlmta54hPXu82nlniLu9ekRAEbyDrNmaaIzRDZSEPGo4UIMO1bp/IcEXMNMRm2arCnUF3aeLOJ5Nt4I8DJTC0B23ve8lsQbdYXkzzZEP83e+iT7tzeOiiz7hbiKXFb+jK6vPhwzX/FOh1/m8xixvkPlDreAw7fA9A0lVKeV+bbQumrS0P1upHcL3/qiD0amLZqkQRB8SrYEPPlJFxWb2P0aQcRobrZJm/UXBTfN5+mvLoADWSvT7NGEN/Q1m4VSNRwDSbL57lsbDV5YEzd98nAJrCge0gHjhx0yji9akExgQmE8ViIiUAI5/EU2vsvwEe9U9lar3cSOYhWCfXRf+a/nS7jMg5/rgb5JvxMP2HDkd6KZ2Aujd3+9RMytWTsghThK9/d57wPpHL10Ju+7OQP6bEv4vGNfyqnBUeoRgSvJUDm3KwqrKvKPoiqYRX3tPfLE6J+UtLa+DRl0cu/ybZnMF0jIhZzcDzigGLXOwz04XrTrnDsiufyUpqa6y6pGsrXp6XWJf4vB31eaHl5hHN3CGasGemzRADKXDvBMHKIptqY05djVpjiqNbU1pEQFpUtuQgeJXQ/vP/SBM0pmyL+BRwTlGEbrFSRRsldMB5MYdx6ebAniDiBpdcHbQkOxltG5z7hnfOLcxr8wW/RqSZjaMY4PLQPkugUK0zskL2HN3E+2hqIybkahTFKWbQGp+fz88xYBZq1VcruEZsL8ecrLHZFOQpN+tuVJe5pfI0K2sjxsuLp4GkVgY6YAsSI6fYxA7sSM/j6Hbd3KSJT624t4IxsdgUjClfmXuVv7LhYxV1w4IR51AKDuF4jvFIy2UITOZLASpDmtok0PppzgHoxCQNmRbA2DQQ0qA/9WvDhlCi//Rama43J4wH1vbYH2bIOWmobJYuLZEYeDLHrLqydiOAWYwyt2xZJ2JgpLxHHlRptKb2HmCsWAnKpeB6v2svquDoig65sL72kaK5lxKNRgMWaeWC5qxJtha0NXxXS74ABCz70w3LXYGEwr92rd4c5AkBSQDSvHuOQtgVODWgVT7WHmSunvygORdR3fi1Z3qJlIGpeTk9I861/Icaf+uoOmoNHmLBT/SMwEzEn/syWdrudgtakOIke4/uSRDqG2KoW+2y7K42Haqvzz3ZbeyUlRhUBtaCHJVBJOQz9tandVqEzpK1Ud364IbrOW4njT99sOjWrc0+07bDc1y82eaP1qai1MK6ZHuY6rVjfXZ0hrFy6jn5ibopu+l8trBUXHcrY618kInOBibtVbthZlAn8ynMc858CEA7NEid0dqv36ZSA8kWUB9CxYSlIAozHiP3Gc7WwUlDFiIaBQ+3LdQjfeYOKsLr64S7qmHRBEKyx30DvCG8J9aeHZOEDnFcux41bef376Ep3dMSoraIFL2R+liVAoNLqM2+v5c3Tb0JphTpJcTay8430mJ/c+vpCyeD9auGDb828FS+p8b6lxLT/xIoorjX2sQX7w2xF7SbsDRntFYiUTnD5+ZM0E9K9ZxWFFr1s9deGh5yVKqwtrnm5MxRg0Eugg24+upQPzu3Rbrpnbhg6LlLuXrIKK+uUqOzFTJl6z8rrbMmQybSKbgH5nJvnB5A1uC50T4IgBg3f+qUmyrWzsafyLXsru+sRkwcw8oD9+q0eF3sYBGHgKYgFtL/7uUHrLeglubwCUz+UeIFPQ37yQKuCYqtNadEjkpw3RzecaarvMnOFpJEfQ4B/vA8PTwuhAONwha8I1UEb8riCmqSXm8uDyegtQotvducFjS40NgrjnlBNjswyOInTSnaEqfMBC9YpYZKYidRsJRpt4nFjKP87p8gu6BrrAcZWP/ium0e3lqK63eDrpJFtm12OkQdbFyqrfVHXBc8hSWw3xM7TidI/mqNa1mO2yCnv3vkhRKb8ZGVnFBEBmiHizk++OdtQtCXYpStkeSMTjBg7qNPuLZrtUf+V/hjkT92EkCwONSI1SMtOql0zwPbI402e7iviWtxE/YKcZatwGXKsGHpj5iIKNssOwqxcFFLUVQB5b5sVC7ElCXT66Q04sgE/xs5GoWlPdYDvuLNmCNrM6gAnqfmC6cNN8qRWNu7GrYBHFzEI+FspmlBc6FSgyfz39jICSNbHnP/Hee7qK2vBXWWbFs86ibcW8cY1v0N2Mtvv8XM223qe3EagAkCBTZt/nEdfJxDjX8AKUNHS8EmsfXp9rCRgnAli3NdBqxDnc1TOKmcf+Qd0NgvSGCxCKSqNmjZQpBEnl2H+QtTIwnbLRKBOF9YJsK94v7T8Asfkj4/PyHaI8tApNSr0A0FLHv8+C5VkHQwQAvqhnrkfgZl3vuxG03aqFHpq3WXxAAKuKV9/np07Eleb1ldnFfcruztJkuTBQtHgiU0/ZMIa9gLlRnA0z9/SjNw1ajTGJOWEIbY1xfA/0A65qC31aMMtYf3x8rEjQDNbwBFx8yWzZhhuABE2aXqFyNfJpneSBfrlvk4dzieNasBNGK4hxtJlVhnJ3PLI0vpBomuMHt5JqWukbYVFT7v8yKc0kBB4yRrBDhGOydZrYj4gg6iyev8TwyoRugY2Pt8UeWiyHtgSVgkAF8LZ8W92sVH95PYiyhV440ytIXwGe1G7hRm5CXTlWveJlA8C5Gpn5/7EIy0Y6u4izCi0IjOk5jwEvzcQ0T2LJ8m+4KmS4h+uC8YoGQDj0T8LTeoD4hTjyzvDKpUugKOmHbUNreFNJAd+WNJFztfC0wwCqBHHNGlkXRjvbEjiYbdRJSdr9fXRJ/gLOOISM8tqKMTrHTClsLn0heeEa993jC7h48Ee989ofA0Xv/X/HgmocXdQNBZEbHVtW+kLuDHHOFhWo24tdGqOky6x9HMiI9l8c+l7KoDRGE+wJiPlcX7MnawHDwk3LEkJd5ByzwwCo3BlM0Hvc3NNxJpk23BTi+Q0AYMKqdr66UWmLzsfwdpbJqa4nPKc4bXgcm0dT30hkysY+bnJdFbqsXKhNtu87Hrod7mMIS0/iM+d4rUHPo4k7gCG9Jcew9PZnITFCTvZ/CttVz+PjuzSM2WehVQYy31r1EuA57QBIK6kencIyLBx5q/0Av1j5zT8HXmjzWBLAnvWcWS0PxiMTT8sg4Jfic+HcpyP0ywpKFEfuBfGcZg91kGGJYjOwuZKby65s9QQYTv25xY2+SnPoyL+Rj0hvgYpDyXmXcV83RLyY8nuSEU3CayPBzJlajZCGdoiwGaQBNE5hOBPBnLONQFTF8Q7mbp8tqAYhcBNPF2MxlKJfohnDVJ/3mfb6j3p/mUYD4soM1WtvjZSZkfe16/wLlQE4qdaIxjCiHFPwVlG9YA/Y5fsbez85zcTP1ocZW1qNUQWc+uOsb2yvDbyjrGSq7Efvj28H9xw7h9DXODe7YCkwAD1u7bI7KTyZ2CteyBGE4xg4k/LloZoG6xBectGeLaT01dUjVX3CrruZEj3/zqDr8nujEWzzbVoKpbAgP1RlvKKwGdrehntLBDh0EYE/bIVonGVVT5z+i6A7rsNE8GVBaTQ2m3/TYd
*/
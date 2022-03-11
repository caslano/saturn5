/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_04052005_1141)
#define FUSION_END_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct end_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_end<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct end_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template end<Sequence> {};
        };

        template <>
        struct end_impl<boost_tuple_tag>;

        template <>
        struct end_impl<boost_array_tag>;

        template <>
        struct end_impl<mpl_sequence_tag>;

        template <>
        struct end_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct end
            : extension::end_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence>
        >::type const
    end(Sequence& seq)
    {
        return result_of::end<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence const>
        >::type const
    end(Sequence const& seq)
    {
        return result_of::end<Sequence const>::call(seq);
    }
}}

#endif

/* end.hpp
QGKNyFT0B+IdpRI5PqPGyzQ5z2r5iNZXNNns+qcztOgHvQWY5RollPydtOgEtLChYSfZpK5vqNjCOrLJ3mgkNJvAXeAPkooz/iXb2ioiXCevxSpbNU+sF+yLU9bdVuHgJMU0xokuTSDDNl3dmIwFKmpi+Jdn8EUTCFkNRhDy0oXSKSqRLkMAAa52RmwS+rvb8j/70rSSa8s7qUq6awZBEZi2HzZ5AWVK7vHDCDtSTbeNnjP3+XxNpTI3Iw1WbpgbGLdU+q64S87ME+kGB6Y052njSpE6butNp05flFL6zc+KqWqH5rSGUw848jxLcIws2cGG2tabXyyqmBMBA9oLSDxDTKy+bYrhkWZzbetusDkXFoKYifDVLDrIglu4IyQnGD5vM2b3VmtGrqEMw694W8oJ2Fi3yEJ/7kq+a4ZFezBODCTkPna6Td4bO38u4EWQwYkOknSmx1rrDiZRnhATn2zrATIFcAVyRmmPqO3pvZFqQzLowYkbg+d6gD/J3vROC56CNOSMuU0IT/XE1zG2EOwmhSo49a7FwRWokiNSz5CxqffJJQ0eSyQkDZ+xyCMrpIAmrSjbsUzBOEt7aFSI84p/2us4vkdtjHuSLeEWbYYjG3fmQ6owt6OaUJwyPnIZhk8hlyERpnk1qLWht2lQbaaUhgrg/Sla3r58mobxLL9jvLqBA8vrPjFWvsHWMPq2a57a1oaRgiME2+7w59pHGaKk+/ldXrL2rku7ltDaoKJTrGFpDatAJTlKglmhZMmb6V08gZSTO5gDX4xOPNv706Hf3lW+bXq6kyiJMmPRXmkeh3YGoMfr1w0IXpkqGzShRcfvWB+W3G3DDlwAACz/04fRTBAFGwwY6JmW4DBF4fajc/rkNKo4scVgZuQ5QgqTWpYhvO3LD981AKoJY2sXWfSAwp15B/yRAnSrVlUKmvcao1y8Zf71zaR9Zgz1yHwbP6V17TeEHpA9/SzxQ664tKBwk/E/GVVJxRSfHjj9sbDJ9KWSYY7FccESbwnrKDBu1hg/EHple3DSSjdzbgZcPtOI1ZKP0EKx/AEzNxY8Il0NZjGaxY0FjNp/J2zVHTe239a9pxzsWqoVx42ieHyDoffYerMPXVQEw1bwfIcrA8RGWR9Drb0tk/ISL4NRJUozuIRaDhyHvpq6Hwvn8IAxurGuKFrZHXacfRqQV71bBaejpSVWN2sSHhfgy/qrW51oBu5TSFVNr80tNtPvVtFYX/KqligGm2N8GmwBp7c54JoSbJnVhsmazXG4htarlYXmjA+tfI8+Hd/umYcvIfv2lFRp6dGi2OFrUTqfZgyvyLvHGJYHw/gWxdqP0XHdlKpdydArk9Uk32joYRd8rvSnGIxqdtrpPGMNcQH6BLpbM9hCpfl3fVFmke9++Oxh79Q5BSE+vZ4s16CcesOgvz50qxbNCi/uzAyd0txQEirCQj/YmL7ZZEDInBqvx+S06o3X1AE97XtJ0B4nukxAF3MjywSMU5X6fv9eFP8RutMklzAO40z3wGAuQs+H1ykAo34648rxYG6vbLShkaSUmbw94hKkBzj4k166Wj9AgV9zMDgIJ52Ta/2BLWhqHmzdwSxdbo47FXTe9eiCZGT4WenMPDe6lVl2/7TORUPQzzgTX7T76zGfVdFMri1m7Fk2y9+K0ELKxbEDyCuc/YXyiUXR5VFX6h6qxex8MNmKh/dFsG1JFDod+U9nMmArgj9a7tXXGBFrN392KsPug8vAzptMga6nE2AS9cD2ccfpZCwZwfFuamOle/n5Qtn3c60FEpXkWGB53XIghSLlY24Hvg1vn4lxNDNg83vn+mVoA0ctTt1sOlGwbSz0ICdQqqE+BEydvN/Bpefuhk0U5A++1chBTbLvgVsLuXFRLhZjGPT0HmvKNMwARFCVqttyzRL5dx5zozGyPHk+2jpzz8RuQcHEssgA2T1sWW9oB6MNyFQsNA4TAJNoL2o6RctfzDCSM2durqGL4cvcY8N8V3QexUbxaSMc5po7GgAjwW+AHm2hvv57hWe8kdoQa83Q2SVpyVCVO7wFT3WC9H66cAuwbmMLNJ6kchx03A9i11TNYOqSNbVlrsuMQE+rz+fgchI0Sxje0Sjzsr0OcuX3kcvt1dvPx+JLb1Ph51K71J+B3MHjKhZPpV1aYCgoUjK9TubJfEPEMsUgWKV2QBLQq3ggKmArIHDeS9/WoYi+n300CZ0MggAEOSy6SuRmqocNu81uNip5ukP1HnrC4P2oeMJA0hXYkuwlu6iQ/Ko1dFbLijx7vfjE/jct5/NELtLTVjtgGbv23Wz8ClX1K/MEt/2jCLpijFNU2sLwnxbNK/ku91ZJYt3619qj8SFwx1B31dZNHKxkcpoOtwk76vja3bbsNJQ3aZfScp880eYfP/6pueIVIRoDx+8JKcdv+7yP19xjmlofV2kncOvK3if/vWN+rPcRuYnN0Yodfqs+/mkSFCjp/Kc0Rzl1nwIF7wKGHxHj4ehxYtbt0lXbRlbvfitMMF4HTx3P7Q2NP9lbNStfahvIbdKGuKd52mMh+PIG+JO+npe0lxFSkcNrumZ9HDFaPHREpqqHWOgo2fqSMdB/vDh5Q3URXds4z3EXtqO49q/VZCrbMijLEsErcbYJX5U/9+seGz4Yhz/hiGYnc+cgM9NwZx05qho8gT16hNmkgd/ysCQXqO3tl/iQMIclHIMwpZwEeV7zMagjmsiu4SeAzhAaSafndIW1CKqC2/y9x9kNtgyTG4hxnXwUuNhDzpVebhCU77jGgb+03vTPKwWfhz3rgkxMFs6tO4EJnE4BQ6Te85L8qcEp61MwMkL2Kxke74AgMY3BQ57P/G0d9VTlUNikw7mLw9GqarB04ISWJDuFMv1SkoivdY3ByXXHlsh3q4IRkRctlppLCwQ8D1DGWhKP+NSlBkp/IkyGy2qaeKrMxmpkvLNaaEsCXWO0n5OVUwlo9aE3uSXqLWVc7Hg26kax/6o40qVV5PtKRs+tALfrl/cOWEuBabhJOnA04bOCVSa65KUstaCFRuHH9UFdLghwiW+YxyucMR1I1EGW4pOIcabimccWBj7omtt9I3IKyDNN/zTWQt/24qHnRqh0vNYlAvq1wjg7OwF7stbe9QlCtpvmGF3Vw79AAIvNaXlDD2JyTCveKbKrvoiF3diFTGgfPy7GOi78BbFH2x/D38aLj8GHnEGLnzSx2qoXDwfnhyIj4bSnJSzjZ05vnpQTVVc7bw0sMvK2uBAprYXfQTkXI3imjlxtQbD6tzMA9rZL+vUJf/zt3VL0cIdorYQMjLSAUgRov5L3xMcpzgXbFWbMbKGvYUQx0CgFyuYUwYKO4aiHS0O8n5bYEsvCmN7ekRhpoCNpTlSRqgAaypwF3Sw6HGYbA2NsQwmaLpsYCN77o6GPoYtWLCyb8QJ9f/uqUnpjcNQsl6PY5rH2KbdTNEES+j6849jwnCsoYJgpqSX1SiK8eXwgmK4A08PYtEK4EqrT16uReNGIaUGwIsT7dxg84Qh8jYkhjnUQzlaaFGz9lYhNqiNPpaY5HN97EAxudxWMzwk7mWj2pKQT6gPSZOuODFHAM6UvkA4bq7UqbZBaIj+fDLXlmwznCAjsm60IhfC5bp+/hzJIJ3tqx+dppw8wW1dq5/sruSEQeHaTrTOhdKU7Bj+ppXG5tPOnzEsn/56lRqKt+Qjy2zvCl/Xu5kE+bAkFbTuig0P2dNbLrykZjYUWOaXRTYriAh+9IVA7lpjE2JMjotzX305I5A4034AG5eYnIKM3s3wHd2hCSwCGrtxWbOVLoHW9maY73QKzpTBac36Y2lxQclASm34pRxmlyicvpVz3NNebYKPAgbBRwCApYKzKDFTuT/mQHTAlPliwfD8k2aCCLDAvqo2J+H2YqHZsAlHSXRFHhMUb3dmX3QOilcn7t4HzFzDWFKzTCqtDPgaSUf0C0elOmlDA995HQQCPhgyBDwHutVXcoyW0JqmIbgFOhAbLyIhtTCzr+ufiJo72M0gMC0el8dCG5WDsXmMzujcETHjP9UHB3t3iS78yZk0jQEmqDy2k5oqclRvyy6nx6zvxrh8Cr3/0kYa1Q+nWMX1+rEIocKxgdkK/pagbpirxVXqN81VRwatNo9s1mTXphNX64S1UzGdpvmZJTcxEDQBBZfDqyS0UTkmARVOrBqXcokFwaaaGlBfly0VEUma8N3KNWWJ7aqAekMW1oWGUMEvNa6f0CmBIrre5rZVxarBFrNsfjush4/AhpdF+OtRT+BoZ8EH/fXjaPX1hSvDtnj/+gx7VJ3zNZCix+2kb07eBzfwwuMx7ltyPhpjihbU69Yu6w3ruuhFvC+iSK6f+BZGn0gaplXzt6wNf3vyEHrEC9zsXBeIM/qe5O4rUsII3PpiWZ7i9B9wRq5K+AxtyqjVozZj6zErTJjJh4xHRj2jr4WVCn5Cb7BiBx9TSTdDlLwEV5r0qeHUs4TfSz0nJKsjiun7nViwyFTWxOh3SnlNyZDpNwfRhe82DJN/1vFk50Q4u08GSMdQoZzO9Kkf0XH+6T+g99rqCty5rh2bZnecUks/KLHu7044ubtqgrJvghp8+ZLI1zd+5Wa48LJ6fL8wl5H8ixj3BO9L/YLs+M7qt/d0zZUsIy5yLmsl9mi6WCIY9TTA9PLOSVpanpOfTesrWS7JMB6oonTisNzx48WxIkqrbg+kAFUuDJZYWeROe5u+oS/1I2ELNsPpDKskxSkoV0+myVL6dUXh1/o68IZJ+NGi6i5HZlw3s8odrLLs5NQd0JtaHBSinqO38IZDcn6guOb6/07daZdDkntVceMlqi61/cIcoXYOZIHxtRUsCSed08lmkyH3Vu06ZGLg7vbei3vXVUKvErg9bIqaCRLMtcU8SPHzELw4UJLn5n0MuglxXRePx1L0kaXcnXzPfZuuOma1d66WqxdCGbx5OhmIVtWBezCCtcoZGFlKbs55q0Q3uorLl3ZFf3MflEz+h64nuJfR3ivhl+f5kSJe/W7lgSi/k4LR4Xr0+fyZ86jLe3tBRVVf8prOyRGYDc61QkXG4bflChbFCk5O+r4W+OHtHS1Zhcipm4B29Iut3uqvE4+1iCXbIVEQroqtqHrVVSJQh4LBabrb29BYt6NkLShGwWiEwiQl44BjBlzfCuCx5bjRJc2sH2cY2RBOo9AGMv3mMyaNTIgk9REX7AMQ0g4J1jGzR9a6f4rMIniqjxXq50AI0G1sm8mOC3XEGOXUbv9oRv2UzV8ot6PStdCg+OvIiUb9aRDGelJSeN5e8xa6BoHzbmZzHWNzfsXFj9w8tpuJn5g6JJhn7VJPQSxxE0Ob1QYqMEO4ZZkjKse0wRdQ1nbsSmY6hNDbmvu1GbgwIyhlwLCHo7NNDc6MklVMkk6faN+q/XlkhddXd72QrVg3yDaJ+dCMQ54AV/lnf3ZWKk2jaHXRbBJsL7TCFmi86WgLGjEGvjwyEl34OwRfTVkfxnS5r/S6xr+/OjbYPa+stulzJRihUkZhqnTOoWzY7pJBlR4xRQcOYb8KMijC7eiRotHfH3kNHuhmO0WLCmN3C7kSnUSnolVF99zNIA+thBkocD9E8Rt62OkaWP5k0O1H9i+plw3igeoqJyMSYN579+DRv9rqs1X0PBeXTydqkUeW95ZCJgZrfPFqMa7jVc1PCfUxFq5My1HL3Mi5dvVzBc4CMU2zUgwUhX9SLNKK7pl66/4SzsvRtNz01VujTrR9T4A5y5WZimOY3ZE8fBpZgCWUpavHSyTM1Ns0XRNyixNUs/q0wlCSkjuXb3HG/s90QIcche0Wh4ZXuxD6mlZ2kvgVdq+7OWs+WmjMiu5pq67iBuwH5ltEHlnQm28z1mHZWrkkyHrJy+fIohCjc+szVppjPJbqlcWSwdDB395GaxYsveuhV4G27e5aOaQA9vAjU4Ct8OoMjYUDjOKd2JwHPbFmebHwVuVymvmSfMLs932fsvlNN6em/JM4V2rK4LOHdJPAmRC5IYhq6N5aFCuyc9zniZbNMxEWfHQuapLb0zOA525WuXDpLjAIqt0/v7Mzibo51Go8FuKEJDAwWyYJvrSN4miUVI+tXBhia/XQS2cTfpRWOmJ3hmtRBfwBKp/jXat/30t2E6TYjv5qlYBo5x8ZfUswUMxyTQeCIG0s9eHyU1C2jS7NFIFCcbc9/EyOimz9eVE3b5oE3ZYzHHKWjm15bBuo6ouYE01K1Dh7+AZQaAGaIz2BjbA7fU+YaptTJ89c1hv4Mm+1aAyDSQ1HOfEnfQhhKtOaDywE9RL1nvyEj/VLTTiFG43s50AORk0NxLIQ1ha/usLyKDl+VXTsot1SgvNn2BZnr4EwQ48TEWM9gEUpp3RQZ5Ox2chFALHfmoBo/qtVKNOGpYh34ANMLZTjGNM+hn48/fSD5ehDfnA3Gi8nS4HeX6YsXcufxtIWytoX9k3HIuZo2SZRJECQoe6uVqIYUY2fmvGnJj857krUIhXKMlDhmjDE6e1MNGQ4S6+PapiKXfHMXrlwjLI56XEHLoX1UxjoSpCuw3e2jEsn4EJ4V4c33cVKkWJ/iJorWHsiieIwnLuYnmXwLq5RqRqtZY4XkWM1WZtloKXgMmyluBdczCMORsHCmuABT/om2E3YnfiC9sKcp+5RcxohKIdiU1pbn6al/nFtnx9ugtfCqZ3CMID5slk21GHKItNaIDTGz1udq7koLbXR4CZuFtg83kzp7kucD20TqIdCRcAxGlW8fu4XQJvVcIarTIcRAnBx2qX0uy/jcxR8h6FDUprFatYvQ5vTpAFSGZfY498c4CpNDupgOyFc75CKCLqdZbAbCa5B6aSrZPt6TDHJk147suJzm3xYHOgl8qI2p4JRJgnjBknYCttSY5c16ADtzsmk9Eshx27nV87AupszEzl3YA/hSOFBoZpdMnfj3dXQZorUh8fMwBHUGwvsHQVE+bwLCG5xT/+mMsV0uEcKV9HwduWscr4+sYiSSAT4uTSGIwwJt0mezqNM3eVfODgvrT6VLx1EPUFnon52nUucSwIHfAikHXC47BwUHL8vBb7AtErd4E5IzUkWiqD7i1kXg2rI172wKpNnhf+NdjYviQq+nb71fkFYruPge9vCloX7NU7BJu6EsoWDzaSId32IaNoSw9XB8n806cTre5BiNrwa/0JPXxgVSAQYNGLntN1BEJHk8DA1Ip2T1XJxhf82Z7DMo+BGKYWDYqo7D85nd6qTIUc/KQ/Pm5nlAm8+F3FTmPAHZy+6ClC2zy1g49WnM3G11MH7R2Lz6zzabBcU6Mp4k9hs2btorlqj0xagieOudM1evYG1Gw3WJqkLesRZvwDwyPhEJ34uIyqR5jTrk5Aq8BRD52Bdb+6D0D+Hm+TF8dg01B9KdmSfeqI812wiHbranjjdih/KAGYUq/INzcPP8P8b5aPSn95xWoOHDPzWHvZSlFNexgTMjkykBZWXJo16oA/OURXPAUespMqc+iqareiD7x4DEETJnNTriocX15BTbn6Rl+ZU2SSgz3MqmnA6lVykbFo3ueDaL9mDeCyacn+7tUDPGcgmF8N0Uc2h7kmi6kWqTlUKQGi7dg49gRmttAB7AhdOg+7qupx5Glfg85DnWqbdjpMwkJFpE7gMIHkkoQ44lo1uD268AYsewZzJNBf+WpImG8PQroPuT0UpyZtXDqzfwmH0C+YMv4MTNht0AO8U+85xoC9gopSnPotP3M3cXTpZBpmtHm2f//l7lWdKfAAQD6qFspNXqyFInLUQu+VBCckL7SYLmSmGMw27tcJAeElDObUg4lOYkkqGcVxpFdslWoydKi75WI4zfBp9Ul2f+FpnS9ZuajwcBSqPbsgjTK2ujmQnkVOyGhcSCVLY2QKZFVXfdKWjV0ofnzeBVUrQuczbIJ6GGbH5rIOJnEOtFdpWV6JZ3XiF3GC+AtMmCAigzd++Io8qo3yegteXhcXYGMzLZPLKOF7TNWpqziZuWjsttTnrHxtoVIm3CYwEtBYtFqADlWUkMUJ0I4c3v/jMEkk7Sqhz+ZmQnE6sdSDdCqCIhSYv3TTVKaHs/L2o1mgY+TeApg3KMfFIoNjNEK8krVrpI2ALuDAH20iN6UisedMaP3vhKGze4NWbuitAFLhYMG/MBpHuoRygpMf/jAHMqjXGmaz25ho12p4KrnG9xoOUc8vAD8KQTQmYs/N+vRlVdMFpKzstsPqHoerP+nCRoKEtW0sL8wv5DIChgjHqAsDBAyaUb6RMD6zxWm33moPNgURfOGi2b2c0eFK4NVVvNKVWJWxqoi0fEE+sOfxCkNDe+5msjYotTj7+yHLtfpv+Udnz8fLZgt7149tzQnnhuywauuyW++sL0pZWvVHtY1waVsyo/kahuhvv/9fnGhFoupg/1D3mzuzaSlVd+//ojaoHP/0Lha9mA18bMJdYuTarTSS+B+7FrLT9LHuEhuNVJNjhhLsL69BSyxK2/WUGIBWUtX+hMfVcC3i368uPluH0QBhIJuAh0+1Lmjsti+BcrgG3N89ZjC7K0DwjzhbQRmbVvWUbgIQOx/MboxUoGQc+cV2+sBkcBmyh5tiqPfnqc0o0xKs8T4EqltQKjjO/ThS5Q6R3R/7XA1kq5hEzITn/H7eufy4mlkypIVdwJSJCROwQ535whiDqU6tBbjEbkqgvncViFbC+2HEMArF1Dx+r0jTT0WD2GuRV0EZ2yfQYyICGpVN8oZCikZX8rU5cdJQicaAV07zngmXoDMHGiiQt9OOTY3liiB3BA5EjuZH4DfFV3cqep3bpmZybJQ+2iZjhZx8qUC55JnWJBig3XD9G0gvsuvEeWwwckM5CpJH9xetO6oipSE/p4USd/Y8sQyv17erQ/AvLorbYU2xSyNFnl8BYiFmmmJ0r56hSddx+haXrg+JUXLM1fAUc+ecWpcg8UcMwUgXCKI+dDs94vYDVGCSeRW5EeejkDE/qOUW51BfsP+hvA1QQsb2UPQm1CKQVIwioKaYxoBZvYDCwYrjb0517s46iycXi2ybHTVbPx4qhu6W/EMerh90NQJOjyDpykCEXIkJKzl6FKbAi9f2wEnu8kiC3Nm6fLtsFMWIUlgZPbc9xUIVkSf+xw+V0ItCbpnyg8cCRK0hmdnUc0h+HKuJ4p6ispnOw=
*/
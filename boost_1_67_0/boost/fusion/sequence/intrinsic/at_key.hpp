/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_KEY_20060304_1755)
#define BOOST_FUSION_AT_KEY_20060304_1755

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/iterator/deref_data.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct at_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
            {
                typedef typename
                    result_of::deref_data<
                        typename result_of::find<Seq, Key>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& seq)
                {
                    return fusion::deref_data(fusion::find<Key>(seq));
                }
            };
        };

        template <>
        struct at_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template at_key_impl<Sequence, Key> {};
        };

        template <>
        struct at_key_impl<boost_array_tag>;

        template <>
        struct at_key_impl<mpl_sequence_tag>;

        template <>
        struct at_key_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename Key, typename Tag>
        struct at_key_impl
            : mpl::if_<
                  mpl::or_<
                      typename extension::has_key_impl<Tag>::template apply<Sequence, Key>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::at_key_impl<Tag>::template apply<Sequence, Key>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct at_key
            : detail::at_key_impl<Sequence, Key, typename detail::tag_of<Sequence>::type>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_key<Sequence, Key>
        >::type
    at_key(Sequence& seq)
    {
        return result_of::at_key<Sequence, Key>::call(seq);
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_key<Sequence const, Key>::type
    at_key(Sequence const& seq)
    {
        return result_of::at_key<Sequence const, Key>::call(seq);
    }
}}

#endif

/* at_key.hpp
VA7TaNx8m8JjeCEiuPpLvLwmDgtNXgiTsZ7mM6bCTRq9IuyRWq82k5Q65FBn56NO2rn4y7xF7vaLFJttLqm8Uxxatn9KsXsVJKmYCMtpTwQzI4QJoF0XGNBG0oxZ5K9wtGE6cQR79E66VEuXlt1O94fQj7n4cYS+YM+aE51uPjY3+TGnlYCKsVC/AgTuOoZjbv8ULy/io6nxZ/unOtqyINOw600R/UxoPz5wXPtJoFe7gxqpISjvoIFoztnSp4/zXEw6zLjv4kMrEkd4thrhYhfG+Ljn42OcsluMsc1UIzTCF0+32/h8Cl02zVtMn4tEav+BMdsvneYtrOakOzhmdg1852lXOC3U4p1kc3dcBzhYQwgonn4BJbklI8Sfhp97SHf5Jy+iT3e7YtbALRreq1YzvzpErLuD4VnHrkHqe0Gdk4bZ0RtzpHe3f6Gkyjy1U5tN6/zMZ3gNoE4Pba2NKDmPmAKMJAzz4Fq58x6PjRGmzCsKZSr2XDCWVD5LKX1mebUL/Rtwot8yWpVOHxZfgLZZCxCtoeiqQpY0w9BRqoO2zrDb5L9/2ovRWBmubA4pvnAYUjm6Yev8rw2xSq3wScZqaAG+nfIvPguKQY54NUlLJFVuFBfP6f8F24mv9/+Cx6pHzHJSS/0COwr3w53RK0hjCSzHL40+sS3R3SKMTxLJdGmTxpGdZxwU1Ci9uVsc9y8Iakv8C0r0uzlKMDK1NmjMpBml/UhpZYm6Radve//+KX52D9CG+Ofl6A6xF5Fy/rFcWo9/LDpfd5rW7RTfdnHRTOMNOBWQAlgdBEI9XgAPZqMmT8VuJB/MMMQ873oyrlQ8eSg5EOg69a/lP39/ZjxfbvKxsGkWheMotI4A7yjdEWgwIp2BnOtpTzaXJOVcPt7w0t94Y00zx2vukktgWxwIfKuNCPAmUs8MkSDCf3mZjOORE+fho1SaOioJnNQb/Y877OiHyHKE3EZdlC/+GPxfeGgJDHygI3Z6yv+WEEGQzuoEROkGO2Dm1AUrRIt23yksMbwK00ObcC56+hsbEo6C8pKOgnLOOAoqjKmioclbcgABMc8jjiuE/+dSEC2nvMZzbnTbQgOGu2M1a+xgHdI5vOIxFbuXh5vtP01hxCt52WnlI6etB+TE1BQLpB8czMse6TVCz3uL7VbneKr5jOFPCpJsqZiRR9urTIzlNBKZ2iWRqQXCE7r3hE07L8g5bHqcFM/L+Ov3C48b0QoTvULLkRf5GbXCTc+otL+itNFxDTgqUngsS/Lkts9IbKiOLWCS6KBc083GMg9Q9fWhOIK/gh7s6WM7ah7WGowrruNubqttaCsl8ayq5cjnf9Vr1G1t906Cg7+8+e6vEbPhbg/D+Cmvp59iFODHbu14Xx8qtsnTs902XlYcYD0hcZtj0xY22vmwgvueynr+vq8RU3IRzIpBRJWB0D4Yu/3NR7itXdlQOesN1byRT1RQtNF0Ar+D8tRD1FpX8D0flY+Kp5reDJye8livYdUgT/7tYSAKmmlS5IN1IOPRctiJfwTDF+dW03uxS222m3FklFF1eBGHXuMjKFc+SjsrhevgaUwJ24034MdTI7vuSEGP3+JRBkXqc45inpEXmWKHpLl0U7jUBTyNUqcVyv3coyqkHN8fxfdleZGpKjHjAzGCxCo1ipPEbY46G5x+9Vl5UuBq/Ro0tnpfd/RKjgopYvYvGrL5TP5VO4ivbFmJTRtdCipeNoFZ8CXTX85ks4veIzZHpXISHD99cJgTTcrH8hPQSRbGpdfsZKeWJjUXEzlIzAmW/QxWT18fCZPL/RNZ9F5OW2teUwO7SCv5Bdu2wrwwz5R7vzEMlUwvoi2TCZy3LyhrCxHoPbt0XbOceoUZWzUCGEJ0r5ju0bic85THRjphdqsW2m2EN2BlMd9Y5H+dV8wCwQpAeAOv9bu14SAFn0+vjEOGp7KOyfYvhaZtBm4ZE098Ap9UcJolUpIc/6jf6AGOCi/GO+TfT7JMPu1uv826yPkshKo4EUuOf+IqlOlmdd2r4GsDZqWnNo4wRpXRO97EbvXHHZu0izFQu9LwJMZ/SLCFLszqimpG81GXf6JSZ/pxAP26UmCi/L2Mv/811VJzxEiaEYzuwrMgCJ5vzk/zLqS/RfTXQH+LjYeY15tmuKFlsQq2Q15DFTRe51x2yK8HDMPkcw+H4AjIrO69L2YiyD/0iTMs4BfIIXAzG0gejDc1MM4y/DqecLdfbyKCUX7vU349VzpirfnOQGLfCKSHelNGLXafKHflk95Ko70ElvzQQPqyO1QT6AtU0q4QvAzRapG7aiMb4K/IkFeUQwnlMLwxpTElEmI3RhPoM07cdfQqEnKhNXz+K2M97+vrAaJPvCSzISjvS0m81IJLgI9n0JVFv3KhWWOFp32Al/YB2ZBGPACAXwZr1sRi7Mjvy6OecKkw/hB8NFWNtMyutIXmCGjojX4CJ625wcZUHOfLrT0uG4fRxvgyrzKfGhHmoaHGXXgiBktomrfZ4JKdIunWs1GhvOUGLWewGMZbbhzjzc9lc7fPUqITgPRz8RkTNO6O6+1qnNBeLxu7GTUYtrrb07HxmliE5zu+sZkdrQLI2hWSZvvfcZnHgghQn1dEDQP3H62NTULJ0d9pSRRdppF5zUFFzBWXFFcWuOnNWp6/KU8bY0qI0XTNyqDJzMAcKxeoV8CiN/gV5sMH8unhP125vplkzEtePrK/zby1Md/N8E709fV8CCh2q37BCwFFZZikgj+zKe9oodUm2mWgSK6NQ6xFR2EWcqOEQ3H7u/KLFewoTJ2GPlMzRo0QOemXLoVtpK4qMhY4WSAbCD95glaW/qlqW5rb8MoEjn779FLUQHeFBJ9/9LylOiV7+Qze81EHVH2dMOmSx2lGHY6ZgoCDqKyrjwhWfnefz4c+Gcvv8LI1ONXM2hRVjYYlUc1J/fmJhPyjoxIm3c+utCadOYAvqUscu7Jp5FnGwTRafZIcDWfTAjr08rMuoLSiffKbBDfN4viKNgh6q9IydAItcJEd8hMcHErWutsftMVlbIi/Q9S4279JtQa/qHLlV9aGTqa1zKphHeXL6R5IgiDgPFjoMF9IIQmkxpS1YdHEDtmAyT9eJ/bOJDlRMrNanKxXdBE/X+Sx0dQNGozEdPkMT5JY6glhvGyAC7WhDwltWMWHnFNECFfyy11iIkRk0PiIpKS99QoRWsXXPdaV8yCAODHLHdztKWTEEA/dEa+38JpRHRa4w+OLHddxjPrQY/zqPA4bHwhv4P1dHk7gxljguI+Ph0+NnhXmfHr2gdkF4+zTOmUYV5OkVxEqfix4CiAgEBG4E7DrfvBLICmRsnOpqPC+ZNdH/ZaH9Cg1ME360AxzuIU2FPMR3tQQl8XQbwhNfoLdIycm0g9ysQcMLS8Qgj+3ltNoazgBfIls5g98LMtiDgxtKOJjvgmiNI96YBLwBorhxxvsChWZy0tXmbfIoz6L4bEkn/hhiu1W2oNnaz/Bsd1J7UqzWPowwXMzMKA5Apv0kVSpm2mvFJ9i0ev9PHu0oVZFrqAN27jQ5HY2KuWKzbLeeQ5SSsz+ADefu/2HLIV5dw1wPVS1Am1ZepzxPNLkLU/TIh30Cn6beGccpq6fm1BPGwpJEHhHg1CqhqgGs4xlNrJqMtzMnnJO99Ob9QtoAcg2+KQe0zyd3jT4mfPiz7j8qqQdj7L1xex0dzsb8Ojxrl7DMHvOykX7maGG4g5fn7yX7gcbSn5EYuHai0x5O8T/KkyImr1icFebvXx1UvcyhChgMzIastNgR4+PAJM1Ur0u1RJgaq+TQDCzI4ahIL/d08/GlWRZVEiyaPkl5yI9rPF1IkzZn6aEym429Cmhspm/K6HyrM0SKsrsmsdajO7KpzU4dDqt5QpRMjefUZwtTahttKVv1BnBSfEVLqbtwLjqM1iW1tczUySvLBtUWAYvfoq/k6VxoEsbxaNMieltXhLTG3AjcRFObIyX3yOt+LEUVAGyU/9HaJfhf51tPtdYXWN2zFZ3x89S4nSFeHoxPS22il09gTiPKJcDgXQJ5SihcoSeww3b4P42+GXWgiqrvlASxN0OMPmGon8DHrDszqWOafMydTDjAPLgVGeagBdRc0mfSZlDV+aNTWxAYcQXm0NdpCPq18tiSb9UTAdVj+elFC0H56Qe85z0X8byfogL5Jw4nVc6zjWdS/ME72KS11P2P+VyLE49s+KBLv3eBNhXgKXT5PRot4OT19Dm0/ZGLv48cYHXvJ43a+EL1n34uHKPDBbQY7eLobBOdGzXhiKJvIZUWro8nUr8USpzVFLd4ySV7Bo5gXk/LUDyS9WvAbab66PUr1X8S8swX5T0QGNgA7sJ/IjKmkudp42sl788piiYly9k5SI6VBnv6401LWwF2yGHpanPR44l1IqVJ/QbL1ncPo02tWzJf/Ubxlm8foCSLo7LMf+kwTcWYw7QVZgPWsCKdVrNk2R1PHbJ+ECsOMvAfPFiGpgv8MBUnhkdnUuHhjai+2wttD9ong9r0/ooV22maPaaY671lEUnfPvFUGL1ced4QUXCC1pPifR64w0e77tUs4j0ZO8W5ROsnDpgPohmM+Dr5UCUuJF6+ELsWxZ2ADjdlAhx6FxAVVz067gps04cV8EhNXVfGzJvT6+htnfFoO+xmfrZOVGaYMRADuxbOO5mu025IY652W45gXr4K/tupuE+uxd+W0nf2FXweKUVKCg/rbTiDWV3pRUvKPcgKbsNbsU39hB8C9/YGfCPlVZQonyx0gpIlE9UWsGI8hf0dX4yNyuVt160AcLAzlTctHgOezzTBsKe3fK+w4ZBa+e3BvwHeeV02MR5zOazW62bg73n2TOIRlro25S2VF93KWXNef75MSvPy1WeXxihb+16xlAIjWgmJefsPZR9aFtK8hsG+cdwhC4N3yonbcyrlRfU9GxGOa5Vb5GBHkN13EM4Jk8KQbvm3w82y9uvHW6Db55/HmMSb6ZHz6dHxV3AJP6KL2mf+58M8mL1MiTwXXCHOCqVSdrd/ghLZWekqle2nG+31QCwuBcB70cuUoDF44OMKUz3yy9kwOJeDuH6TXuvsXLeKRNN+Af0q6H9AO1IkXZGgfznsZPAM04x9F5gHc863cvigbGP6fY8Sh930TAzGYWLJv4xfZX6tedCJz7O6MTy4efSbco3zdcNQOImxGRqCpAYMQeBzffcyXJol/zqM9MG3+IfC3mpucWMPDnj0pOKO2yeS0zNg8Rma1u+WJZHSf+PQMTFa9NxlAXrTA4tNIV3P+Sf59KG+jmcUfE3MLkUe6D8rCFGupDsfVTIkGgkG9bsNB0g3e043IpUfSj/+CzVcPWHHNnjDFedAPdT+YdcT12Gyw/KMZ+ZOvcCUZFHVZkdWYkyLz/Jhf7+ZC5zKdYhn2GsqbWb3kf3aTCElu8n6XKBZd520YIoJ19ykvVOq+w1KEXw+XRbMsSDKYTfGMNmez0jq7NnAjTZyQshkLv9Y7Hp0cfI/v88bax3LCWh3OgiRWCnB6Dzz+Gmf+wxleRDJEmzkow1kxzjJLDl6aPla5SkYcUyHBeMOkIL03O4XienzmELuDahTk6aE7N+Bz7Q4Xlou8lti6aId2j8D6efXz3gsY1D9N5znm7K+UmEhOq5svWR04b/MWwONLcKHa4L31Usv/3YZVNOIsARHbXKA5DJ1Qi8lC+XemyNKXWRFTA6B+XbM1Js8p13IV3rMEvZEWbFInafB9WHfLSJ5HhWjeJEu58KX/fmW2NJwk3NAAUwteqtyUP8zTLeTeCM7RJDzw6FOTqYlsjQuEISxrxG2tn/ClxsgzyaEj3ZasCXxZnpPwgJzqWuPvI64qEjrcd4N9uYAvIck2zQ11dRx1w6lr0jtkhHQrPj2qiZ1YLwRBRnvqg6BTad8vPOQoyaeIoGMDkUCFqzra7e3VEBS5Qqn7vDj1MH+dMlNpvS/q6wW/TGwRwxEHMR7aB9xzA72+FCR5wh1oWhEdKmGPZLUunYbGkZL08aynLsPZponRypqsO7+uy1a2l2Zq9lrXat8RDjcA6oRqpTAZiwgFqslvVsiWQz3AYVtI2Gs47wrHZT+armTSBzBNWBasczGpiKAOXQIzaobZNplWe1lnagWQlITr5OpSC6SFt0uR82OZVjx3Z/GaX2MImjQrExqmEFx9ZtaEEOOg8DjqH5GHD5OTw89AK3qGKYRKHSUSjzFI5SjoQ69Nu/GUZggF1kW1U3mUd1TCO7PwxPUnNfq/Tb+5XFYFjM3ZQjJEK35cJp9aZQq8uuTcIx6dcfkSjb7593SiuLlNr95ae0SYluplWnAjva7DebPs7bWlPEJlqhAQOknzLTVSpjgV7o64vmglfEUx1ZDSOcOgJkUtZ5ThrosaKIrT3rbBa5IXsL3pNgonzgvLhFsc7DFsUJJh3Q4vNiFsUfnhezKNZ6zCOPzLhFMcTeCzbNhNvCvlmMhb5l+jInKWIfmNkP5Twrb6A8bVaew+Ip6cUfkIRmpsmkrn4GO9RAuZO7x6uOY8XkThI4z2yj/3zd6HJDu7GjW5esW5aDTOBGWj8m0Ztl12h1IIce5SYBIC4/GaDusJeSAvTf9Oh/ISp6InJ9Du+L+uTaB0nnwDnX19Y51zGcHy5R+Y0Mvc3zXs9UqOBoaKCfqZL5uqM/5rK8aZXlVThs/gdcAUmP0m5WRXlagaH1vNksPx9mNomHCuMSntIaNHaLYmKSKeqlIxo6Bmu4VPxHoP/RXNEzQuNgq4TfcjINGOKaZQ+4GTGSOWByrtmGVMbvK5qJGVZRK/DGNaP4jVeIN1hrH8stUcB8byiIf3YeLUlVtLrNtDMT/V+pIOvnw2RX4lrATrdy0epBkWKVMUk+APBIOLyiK9nb6nhNWD9o7DvTm2I7x5J1Us79B3zvh6veCpdvCbzTmhqetcWcN++426/DoByw6y7/I/AzcHdcRhcC77rbQ3ZrJsxlBu39QCo5wtR2x1SsfaRc0uIsVnA1S8U2ql0psPlstDm5PrS0xKbnh5YGbdq4UOsRPsxp3QYbSJtTVO0MVJ1YNiaib4u0SmUXOWiUHyG58GZ0mPxxJNOWX3WCroWrEmJgxbZU+lm+5fH+k6Hbj5AixF5wKFd0DntJb7W8pP8SupdeXh66l15+Y+Ru68UdnW1ZYtbOwKwTLan0NjFrv3/WkWXjdLfQOwP6tpYJYtaewJdtjUnFgq/1M9GiCM2Qb/nSLc5wVqTSCFcdjQ6nlObVrPAtiNsD7CY95O6Ai5Go2u+vOuLuAGFN8vOUsoenflVnftW2/FmdsYwC77a9Hqm0U+6cMPp71bzhWUfQWQXok204ftkHZwHV1u72d/Fj1pZ4Ewdm7WwZLao+DOxtu0K163YqVc/nDGFwJPYyBAaWAA4s8dM6cA6uH4zeaF0W7+SX78x/F5UPbKLkba4STugKlzqi58eeiQ5TWgy8YEO3H4XHU+tR9yr4H/DAuCePOaKOhVt7w60nVDo/e7wAj5kdvMqP6lmV4dajga6WVMrX3/qWdplIDXV+5y+XbamiXArafNDv9HCpM7CpbQK1cWjTN9Qql4PCDsmOIRlN0hNhXKB0Lko3JHyLC+lucVgRL6NF+dEAv1PP4vljOipWDdANxQD4i2Fw0D/D2lcUU8cxs0SV05pc3RFGhwn2d8ull7MlyuUzsNb9NxqZgWbEioUwY7wxF3Z7FdmdCqj0SFmxEWQtQd51tWdQ4kVnSywfRroVc/mEwpnaFRQr8Ax9oWzygvLKM24js/yuoJzDdxapO/ldlUlPjg/K3qus++qmeq5nCxtB+LKVrSoS/+IyGW+w8gibunw5nsu5kyNrueOqc1ekmFbPq5KKG78tH7rq7FWsZMqVoLw8oSLxm5Q2KOvp1tSQkeJeNRdguUAIpk3o5nEeawc2mGaoLiJYu59QDJZ4pdp/U8bHbG27+w3Tt9BaM9Tah0WzPkzKB6T9Rda6Nxrr3jI3LwgO2kRmkbz/ODpChlYizOCUUv6/+S7TFofnayxY/z+2Q81y72VMBKs762T/4V6DtlFPKSPzqzE3oKpj8sm7esG/h014XwUOcqdhmD7ILmM7tMvNqPovM2JR9W9nYLU01nFM/X7WQoK5cXoOFcfGFminWAfRQ9WZLaajOtv1EjPMbf/JTBXvtGaVig00l/I1zA3BbDUcDsIMd9M02r2vu4x378K+/Idewzhl1BvBwujzgkkFg/Kyz3tNipD7VX5DaPKHHwAyUEe3NhJsEDFyhvBTXPTYW7BLEYflusXHDWrsmFkyE/x9u2XkXhoWE8dfyB2UJyqoHkCi3C3/bQfseM09ZowjlMroweVdkLD14iv58LFeoydAo6WrfBtj5sz7MDyP1Nk9TB14sKv8CGCcYNOItdJVMO5cy2Hi8tb0GEDrP1Qbw8v0Y9o/b5NzqPGiu8Hwi1+3fwOuWtSU3noo2ptUiSyu3G65Isdtq4nox+TQn4KBlpeBr+QfKDVlYZZQlg5k2jgiWFQdlTntmbb19+54t3lzj06X1p/YHmMPRIDH+mcxxO70gsQqPE8yf+BBY2In8wcuvljxB/Yxf6AOcscd8vZ7mT7wbQy8+gi9wfuzRP7AoyZ/4MGGwumgCRz4Z28yf+DBhhK+8Ve+YbE7Pi1nvpJpq2N6vjrFzldrMTY6+tNssZ8OkYozLZDz4Yrc8U3CzVQZpbSkGoh5nWB31LeE9c6w/lZYXw9vhn3YF+p7wvqHdXWRqj2MV/RENhgej8YYHrGm/pKXR8kWW7MDrqtHgL7/ThqeVRJY3ox91D8aFGFHRHqDY9cbzFFYzOyB5Ucw3ufeBWtWDfgidzXUUqURMzkgv1lFb2xyNDyxe32z9DtYZzW08+klo0LrexkVmOSSxNRbw6jmVbJOXvkDbL32J1FN7iFVJ041+TQjKtleyUyimpTmoUwlzrd6TYLEzU2wqB3E1/VNTDV58aUm1eRO+dnyONVk43vWYGl0re/+3cFm6cJp2AEeJr3WMCm/iIcJh8fRKFHxmzvkpGaacQOmgHLK7xYnDhOnnl1v6L3mIPlAqkEyisrMl9UQeYsvZzOv9DF0meQ69ow4bYAgBJrvNmOmV3EpSrE/sCveHlN75cGfxQyHe/F1s7z+Eq6mGv4Qn+unYfj/7GKFlbc/efg=
*/
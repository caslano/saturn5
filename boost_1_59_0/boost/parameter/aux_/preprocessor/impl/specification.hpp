// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP

#include <boost/parameter/optional.hpp>

// Helper macros for BOOST_PARAMETER_SPECIFICATION_ELEM_R.
#define BOOST_PARAMETER_QUALIFIED_TAG_optional(tag)                          \
    optional<tag
/**/

#include <boost/parameter/required.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_required(tag)                          \
    required<tag
/**/

#include <boost/parameter/deduced.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_optional(tag)                  \
    optional< ::boost::parameter::deduced<tag>
/**/

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_required(tag)                  \
    required< ::boost::parameter::deduced<tag>
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/parameter/config.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))

#include <boost/parameter/aux_/use_default.hpp>

#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , ::boost::parameter::aux::use_default                                 \
    >
/**/

#else   // !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))

#include <boost/parameter/aux_/pp_impl/unwrap_predicate.hpp>

// Expands to each boost::parameter::parameters<> element type.
#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , typename ::boost::parameter::aux::unwrap_predicate<                  \
            void BOOST_PARAMETER_FN_ARG_PRED(elem)                           \
        >::type                                                              \
    >
/**/

#endif  // Borland workarounds needed.

#include <boost/parameter/parameters.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

// Expands to a boost::parameter::parameters<> specialization for the
// function named base.  Used by BOOST_PARAMETER_CONSTRUCTOR_AUX and
// BOOST_PARAMETER_FUNCTION_HEAD for their respective ParameterSpec models.
#define BOOST_PARAMETER_SPECIFICATION(tag_ns, base, split_args, is_const)    \
    template <typename BoostParameterDummy>                                  \
    struct BOOST_PP_CAT(                                                     \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    ) : ::boost::parameter::parameters<                                      \
            BOOST_PP_SEQ_FOR_EACH_I(                                         \
                BOOST_PARAMETER_SPECIFICATION_ELEM_R, tag_ns, split_args     \
            )                                                                \
        >                                                                    \
    {                                                                        \
    };                                                                       \
    typedef BOOST_PP_CAT(                                                    \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )<int>
/**/

#endif  // include guard


/* specification.hpp
2NKqMR1o0S01rZ9cjfXkTl1ZTFJZiorvz9h0Pya9oLRw+rQoQG5Zjg34YZ5vi0uNMEQDqb+K6LEBQ7BJuLJ50z8nPoFMsY+vSwmdn4PgIBjjU6MMDZfzhaGAwR7RsHvYSmEcqxiwp5WkyDcJzQaiJpVcBxDzLFh19YsOHSBi0Vl6lDc03p9FMGsA0u4wxgIN2lFZomPe3U5PnuSOM3YW/qkkgsns+9Lgf7kFW6/7I3EZObaWYrcGIrIrT1KkhFpraNq3hH3wFfgyZIvrf5s59kyE1w5QMqUSLQFEu6zgm2H41OFypljI+SY9O6MPcii78gIYtSeOYyA81kmxGpGz5YsKoI/QXnwfQw0qFVk9Morzl8CD8qoppYbP776XvQw+cGJsXWKUgMu9b6KVXTjY6RZBf4GXzeW711+uYFlZvoMOqkW+qwKJj5c9mCtpGeJOns2B2GI1iKpqRs2FODjzsQY0BhD6Bve4gC2tA4+d8GFvQ6tvcZhK+DvoyXwObE6pKXzHqIc0LPDt/HfcntMxdUq9iCC3VScXcu/TTDzqjL8mw3Zt1+20lMtebKJDfg5mzeTaSZAbbyOkSR1Rv4CMukNM65o4MaJkJGRrYDVmNbW1hOLvaZpuVp13Gds46tooqGwTVORU0FHHqhKjbSOLpmfHKPqT8erWxNpvozWmWvZH1fn2Stz37/pZqw51WbYGBelpnp9Xa7MtO0NFKbwZIaaWXjH9Z0a3QUNERDapq648Vo+33HC7pANsg/IH91GHo0PEiuivx+khI1lnypPRM9KBMWeVCQkKMvzo6myx6QACLP3Tj18ntwdqziIjVWrdbOkjXu/peKOtU613G6qybCvUXCTv3sYODHFu8C0KTvDs6/mDRw+F8Nq3TveUG4c2ki4btnchG/XsLrjWQM4/th1dcudy+wL3ZMk+Df/4nfdC6LNaVo3fjrNDJrDSYirgI+ImHQ9XpnD5fNfD2R9vry8PY7khFSv7PcVae3CuhkVxnCAhUNQOFKOr/dr7155huDO+S0dfU+wZsAzA/S3TaI/iUfWa668S2yeVzIQd8KILq7FkJazy6vRfaNnFRcXEzmTok7w8npBnANFLm7idVazOrq0dxu/Qa2L1uBloLe3Hm0QNnskB17pj/ilI6nBaRs0o7KHLq9gcnNqeyqYR8Bc4xNtDbRt/MTY6ZNvNVS2A50moPe2I93gv1ZFh8yEvm7z8iHjVpLlRJcO5XvdnhxEeUFV5mcU6VUWCpOIxIdBU6IKV20Wv4isGr5sH1ULVDleO9sYnbNp7MtfX4SG863om9mRo9mTXmied7j9z2VUQURCvjsemBXV0IyIyGMvw8DAoL6NBetCwYvq67AIylKCk0PFkVJ2SkyQmcpbnZBtkoXeOWK+gQ50qrVKqzD9t/Joq6JQP/Tiq6PeCuaRGr8olQH98lHG6hkwk+DxeSKpuxuYMK6lBg+whvWJMHXe/RVBEzjvJSbeMSNaiuQb0W+Qy0rBrIAk9lomxzqaDv1CwIBFZpOCp5Gn3Fh/LIzzvmFeR8MOSGiZxyP8LlMZmWWLB2nRt1O3edm5P0bp8PxtSMVjaK965hDtr3tlhgAA53GpAoTrxh3Uz9GSsUQ6B9bmlO333Kc0w2y7kfErYa3ug6sFccGOqK9DSYilN0sOCoecev+Z3TfBvavm6IkFLrFNc0yIQFfWdDbBegt3u7oZuy/znZgUjLR36PpuXtH7jX4SbOtC9/Q1Fh4rfmzXh/wIpOlbcDVr2whjdYdPfe5L5I2CQbHdM99J9k3BxIUzSdhwM1RWLntb0abkN1huDzH8CzwC7l2+49A6eUfrcPxcN84H/7GzD2y2nrhU0KHInd9jDx+o+13EBDmXOhNtGo8oWjvhN4N0mRSxMw3+NlOh2bFxVgu5OAeHbts55mJ0b5EydrkGzyaq5ks6lni0pTeIi9SSgTNKbCfZAUhoiWlKp7eetoJQNgQX8xyFGcnEyPIL1hwdGaxWHxoxgWBbRNfTIq0KI2aFYkwPFSg3rfTs8sngwplS5fOZMRCJh0D/xcyosiOarwUQ1iYnl1Iisj8xa86wdTDt6VDmLNK9K+HP0uxRafEZbKuggSEIAPcH2W7C73oHSyi4Pc86YU83K0kPcXESOWixj02m7JZqCqJ6YE2nUEk7rQ6NcqJJubDBrnZET6yePro8M7AkezE3ZOSQDz5xzZKSILCe/XHrrI7zmVQJiDuWpBgvMl7FGfS6uzrja7n/tEHnDMT0o1llpN2+677W2+GbnG/bxKME8M9g+TDuMOSFWN2YNfWbQbEuhq5+bn5tPXGDupdbbUOVE++19y68ywsMraScNmJgbxqMXt+OqYAb1NnFklU5zmPfxL2Sm8bGJyFhblULPo/UWJRY4zN1rYRx83f6vtwi4V+s/0pHn+HAjfmnSH1lT8E7i2uwTfRSsWtRbpzD0UscSeFixfIFLZAVRQcg9qDGewbsD5ilDzKjaw1K32TD7RvbnJIElw3DqA79yNDzlkpOFQWjcarDSkSLQXmOkydsaQbMcpw/BPFa9ltU4q36Tqv6x6MH/aADmRBeiWwx0AjBauNSFkywvANCBU+1rcM+W8ntnU3Li6eNHzU1UIR+ExC8ucDsnoYvJ0U30dnZ8B7ODi8jN7Pg2ejvnx6mT6XT/72dPTO9RtM0tsWiLN7ogsdCyiufzWml5uyqLiPwELJIyhuEsnnltKkT1y8qAKqmiUZjm+VOrPdg0+vWFE2T7TS5ZaHmCl4Ix0t2zm9mR9bArIlH3igAPXdHsOx0GvmjdonIOHfUe3u43Hd6OIh4w+FDzORzx0eWzPTUZrXKfXIvLmZZK5GcHOn+Dw+khl7e4J3990xzmELrkIobTSrr4WltjgPNmBAjfH0lU6/V7+MVQiUBCWqhz0hok6xexisz5FcUULrtnxxeY9unZLIIdrZfBgf3R9RiScfHF0d3KenLpDG6Rt8C+FDdTsBPvCJOGOb9kbmCLAmWdPCHkQnacFKo3Ija4R3Bb7py4Zg8BBaR6FyB4LmBG/JxKiXHrPFWdBwqUc4AupbjMoZcexMb3O1N6JXyR/gekDIg4UnErDHUQg5saUFzZA5mhj3NYfrnMLxEa89PYNO9rM7mDb8JTcPCPHKjUx875B1KLfgreXiG1PNWuPmfHfv3owReSUGUXjo14MrfuJQNvQfbYyyDPd9jKQHnAsEFLAZ9RDsUmKkbnCTCTWaES+d852s9Dl8znkUK/kkNA0oNKMiRWSo8rfMwhh4IFb4opAoQrp2DLzzoVtuhtugv7+lDgA297UlBSVplX+1LJ09ZTwOJ/5Nfq5O+vLyFppKdZsuC/dnavG+nEqX1l8S16R6cpL6t6k6cueAZSLlPv8D2B47NGveHT0C/noKFoQtSGAqDLix+r2FcYUO9trq4Qpn2KSKhHiZ13wWmi3OtfBgjIL3YyvX/2T/8U0lQsZPo7KrmkOp/bD3r1sz7FcWutBJeIfA1AReziOG3ZEXWVrhIiIKLuH9WON/iKL4h0llHf16Odkh8jNId+ly3Mtp48GDTPCEkRBCywnDQDuUp+mQsQEnq/Gw93R1ZTkmukdCaFXtoQ9YAXQWJbA4skAF7mYdnomp/5PUGXJid3a3wwpE4R4hEC2MLhXF7ngB3UciDSuDz7y9RdouLgkkx6s0bLyIZL+WDI2DFakdHZY6m3aiAzmqZObymJ1qJqsglRRgUdLZas7tTJTeFFGm6GWFPkPKC9hUEJgbwB4FnQ2nVowBK7GEHSi4Qog7jF45fFW39KVjMK8KsA8DbsQ9xP/PcuHPJQ4ER98eF5Xstf7uQo6MOmIAyXWN91uhffwd0W0sUcqYV+3kA7gd497mAAp4bkQk7di/oiJxTyIDJvd9CtYXd7zl9kKFG5vzWoBWtvFRN8MZZqBPKzLqnv0hVW6X9gT/LNRubnuPj9eGCX5ybwPOH7TWGWRbv48sLAYXcXLxuadVbHOh0SrHFu1GEXokg3EFwt8qleWRFuDSEDY2KyaBnJdMwtJVc2aTWrN17+c5ONUj8gX7wrPkljc4jYLEqnEJoKq6UoZ/dq/+rSvHADGRsoshVrKV2V8Cns3PWHjx1/e3M3viccCoZCKsOLYWaqbTo/XziHNvwIPpvNXhv8TPh2HBgL+90pFSZ1vs/hD/ooVaaJwjLDluZf9xV70l3S71AeykO+u2IBZKMekCe4IXkgM+uZqElQVRWbg53VlfxQ4hPXTKyrwgliMjBy9r3JOarVFOat3EseuMHJ5HyI6DkRH6t97F/akzWdgqdR5Xq/uYNKH/uaawhQDmhiOdQCY7wOCeS3R9uUt5hkFNi5c2gSiBSXRgB3cRCpfxgEGL4hwv+VkQlFZIZ2pPPfYgNaLwIDy7ASWrVdEXsRXxemVT5C9exH1xLK87gb9+bN7F8x61WK5MqQ7IKrSbE+4qcUSJLxH3osRMRwKfvDWm6/hAON8f5KzwJp/ESCK/+tzOqAjhQ4QwLkBggwmccDgqUBDOwEgbqFgZC1w6eCuAGBtA3o0MnaB4LAcrYL2echbDe+/XbBd6l0tdRpaXmwq/ys66ysrPj0LoUV3GWpfnQ8jz0ylBo08gNxrZYm9Ic/VoSkoY1m0aObur+RH4QP5ma2MlaTF5iLqCSmlcVucEc+yPPOZcOGKejtJwXNvpVShsKngZ6M1mFoCEotK/Czi0yuru6RTnnuLgiw9U0NoJwQXxDACYTCvz2I2/1NWy9QtV+WJbyRs90IHSSCMEqELGrX6G9AgHuiecMfrNNFvqAH+rO5JLBM6nwYXJeKsapwbbXhoFB8zeBhtInLCCa+rUrs2Qj1vV2BdeXrXMz/zW6axPGkPM7SqEfJAQxN4B0ICEez22myPPiSnZz4KCu4jMorNX4yGt65ClrH/uOKmkHmnJnW6hiPXUSvnow7We5I00ExniI4TkpaYdebLujSUr7nBjDYPNaRfMMZfzrK2AkJ84LXCYZtECL0IEd+ib2MNK4cR7xzPdqaBRQpITU/JskdQ0pqHIFpppcGW4kWIMEY64Zqn5vn3u5Az36bKULtEfAo+ay4MfF9Hkg+E000/xStazR8N9bNBzgPTDUFHOajNurHjYYj1NWH00qr1E9vSBhte/X9UJp3ku2z64Ooch2yHMFXwg3IiOU0q6oUiOvPGP6VxKAIk2sjTKOQ0h8hvQpn3QoxWfLUrIXnoswMiEwiSd9zNleSSugFHopajj5Hx8yhTWMXR/W1oNwH2IAcOXWKhFVZJ2ryNHWFspc6Rf7MY3ixNU8rQB//y47hCA0/9C1WQhmH6618COCc6PGtBTHpEczJBJrse1exde/f5Y/5BU6qBKkIitiiESbDOh3mH+jRoFCpWkRWoS6pH4VrOfC8QcIfIEqmKh8fg+7Co78j3IxvjE4H8ciXt1U3bASqrmlvL2F0dZ8qxv2VLJ2hr3z+c5Zn16MVtw4vjtVkDjKvlBl7cwTsHXWQFE/QnPDJ+HY1BVgqojEjg3EXgxjZK41yGQunseosn+RhkF8VGyVNquNysgi3jo13ZP2oBmzNmjEEM3lV6SeJyALVE4PrjKqykrVSsQSJcZCqTe9nt7cKB/RIky8NcmjpvqshxJNF0mchBEwR3B6L+fX/fqh+aNruZ0YVVqJ72FeIYOtKOjt6M268tKCRYlM2OpEcbQCyjJDWKP1W2ku4VkUebJPaDXU/xJIma75O5xNjAz4RpNhELDV2aPBt9XVeFOdxuXM0LU6R24Fl+kFc8CxGCxcZ8wms8lF8ML8acyBckVOxeKg9ZvfcLoyJGbbxJ0cogrsZNVGOJK97Vbm822+C+YPRM8wC4xG8JoVy/PpeJSlc0svWypXOiPgZBJtoubEiTUEVyl652i+sBEF6OIfJmVqVwHrEOwPcfnLDzXN4MggAzA5Cpg+dskB15qwdf/M2i3mODse3lRjCv5QYe99X7Eaw0dLKsX79jOjFKLNgmgV5PRnV71XlOjUoYQjgJql8KCjhsYhOHDpjqpfpyWJ8VFdp87ZecWak5hbkbuOWOBuKd6XNsdE2y6QbGg6QbhdOiP3+soI6l8mos7XZIEoctcCdRdGGbrP2/zbmbGzC6oYF7u/CCpSGzJvcaXhbx+wUe/109rbbI8ZOjvfMQVBR9ak20TTEdZQOuAcBLhH0TUcm9Rmy2CiFSdaQd1dUuvCojX54q8TaRFabMBvpaVqnCw1nZ9R9N4rDLCp8LKqIfQzIRow9n3uXpw9vOfF4qqBuy3i4YCMAn2oFekE7kVPRf34XaSjcEQq7TLdLKjAXQnSY4WXpN2qKVRstPwelZ94xiJGjypaK7U2PcDfdwKQWin3ht5t5gkEUgQ50p9bJmNTNZFj+mVbveVXHiswM5qBOobp0cYAWKscxaaf1O6awWlGjKkVuj1ghJ1UylalSR8aHqorM6WiSDmMBlZlLTpZ7hD6yBQ8Vl+ExYYxhiE5BI43IpfpXBA8K5wbEf1flgyauwU6KA0Pi9og6Jn/aCOxXNKCeHGI/9C2P3ranbktv5FvHatvtm3f7jL7UoKBzaEJfn6/3tTbirJ9pqIqRxGtZ4ViEizZC0CstXgllhboHgibHgqUCWeb6z0MsUIkA3z6xgY6ejUSSU7Fx8TJSR3bxotbcssgehfHFEoLJLveb7BVHU4Bqggbt9uFpl/3Veixf0apxJV44oPibh7mV3Lnf6QQkK14kbMKVre08ojAgjY4iNCpG8futg64VQAUvvUGmYHSKipVjNd85uxKjaXCNjFtKq/wy8LVLd4H+Q2z0QY75vi7EL8X2H6tYY3VrPeyZjV3r3IiQIkSNK946XEurIQq4+lJojUS+Uws+RZESc0pxU9lSaMJayFrU1FZeBXRixHNykbl4WZwGcUNYDfxqGUMyOrKbdkKmuMjoMMzIKzxp+JHHRwRDpwR7rCsOkwvHWbODHgFVJbFL2FcsOHnGzxKQvqIsz8g9DCe5aPZQdZ4sYML8acIdpkgsZP0kvk3Vi8ZOTquxczNnJbQ+VpdPboW5HFMD3WJEdqXh0s4bnVMNUIj25sXo4mfs7nldxivNG5LyMWG1GWF4BrdRuw1c4c5OK3JJzwXuBa8KJYpqoAVJnkBTn2wXBi8EBiQLVFgp+pOot1wb3mlua8p60N1Ma4b0RUxrlykKsUlI8GZLT2kTKYV+HZ4GzBYszTqfpXnUkA8MUK7cDVbuKwvCQMDPiwAMvlNS8NCxe/gZvdQ8kOr8Z73XntJCXEOIdKPtsE5dE2aKS2pkuMKoiXBxzmuDqbfbS6ekwEOrwikeng/lA2IkhlJ4FuU6UWedyLxzWbvOGQYEjMjmUBkTlzT2V0KVVJ+1pnwhWRGP3tSaehsFmO0QTIs6km31z/EAr9h+CwchVcMpCl/QvWrANJMMiz14ZiMSuPcY5hIiiyGPKMwoodY/1aloqlHRXLiwt849xi9jWEdRVZjXPUDZ6Jmey7d3ClyUFw3hUEgG7BBUguPuDLbACo2PxclX1FtReRTrQ/jEiw/mRxlHEU24f7dOTkc4Bu38fdDtDyejq5bbTEKAq0M2Qr5ZmVfjcjkjbtf31lNUOGHALFwLHW8RvTO/rvZYjDIWE1I/Sme7VKL16BNN
*/
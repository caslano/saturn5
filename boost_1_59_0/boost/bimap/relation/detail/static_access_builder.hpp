// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/// \file relation/detail/static_access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCESS_BUILDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/is_tag_of_member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>



/******************************************************************************
              BIMAP SYMMETRIC STATIC ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SYMETRIC_TYPE >
struct NAME
{
    -UNDEFINED BODY-;
};

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER(                          \
                                                                              \
        NAME,                                                                 \
        SYMMETRIC_TYPE,                                                       \
        LEFT_BODY,                                                            \
        RIGHT_BODY                                                            \
    )                                                                         \
                                                                              \
    template                                                                  \
    <                                                                         \
        class Tag,                                                            \
        class SYMMETRIC_TYPE,                                                 \
        class Enable = void                                                   \
    >                                                                         \
    struct NAME                                                               \
    {                                                                         \
        BOOST_BIMAP_STATIC_ERROR(                                             \
            BOOST_PP_CAT(NAME,_FAILURE),                                      \
            (SYMMETRIC_TYPE,Tag)                                              \
        );                                                                    \
    };                                                                        \
                                                                              \
    template< class Tag, class SYMMETRIC_TYPE >                               \
    struct NAME                                                               \
    <                                                                         \
        Tag, SYMMETRIC_TYPE,                                                  \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_left      \
            <                                                                 \
                Tag,                                                          \
                SYMMETRIC_TYPE                                                \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        LEFT_BODY;                                                            \
    };                                                                        \
                                                                              \
    template< class Tag, class SYMMETRIC_TYPE >                               \
    struct NAME                                                               \
    <                                                                         \
        Tag, SYMMETRIC_TYPE,                                                  \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_right     \
            <                                                                 \
                Tag,                                                          \
                SYMMETRIC_TYPE                                                \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        RIGHT_BODY;                                                           \
    };
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCES_BUILDER_HPP



/* static_access_builder.hpp
1ybEmbdLdKIQMzxaU1oQI2stZWSdkqfaFn7CFLyAkN0hULCyZjByPMHVglWlTFNDfQUtLWnfcxEmeGN+Y8lk3SgTceals7uw/9o5QFYXFDDA5XWfJtLu7FbnQ/sMXdwFC6u6tVLKm4MWTnwD6fOTUvym0VKSXAyhWuh1mKJxwBRIDaZESYPbZqcsX5ce1bcdvXWJnwwiBxGfYnjUgD60ThPZyjZht4dHN1/zrURwEVVWZ2Gl1JuyKouwNMCqgoBntB2fu1Qh8+k3WasZZsxcFWSPQ/QFUy0MRimpByoIJjt9kaofYGnM1/43und1mAhSlRvurO5xtvExSjGMg22NAIeWCosAwS4VtJ4ECxrzYXkud7MZCPpuRbnX5T+M35rYV0YScmGr/VJIiJoSdgI/hvETEpmFpZpwsM+57rmumML7luNymBnRYkho4TRzoyd+FUUxE4yH4iWzUk7n1jwsBhusKPL8VMx+499BexbMHll82lB6mBSfySDXQLE4j1hZ0UZpeXGMeQcxk7vZLTq5rgyY64pcajybP5QSwrCwVAMlVFiQpAAgAf5TioVMI5c55nYFuxzjslr874b6j6bFIwLL3MdvXpbPkR36Vm3Zcz55tKAKMyay67+F/U45ZOrQUmYZMtrOse55t6MUrM4gLNgfXDfMkkMOdGK8c2gGoJoU9fmp0B5La3LsUA1lOcWHyrCLxYQVlBbc1CbukBhGNeFwYcqHZb3n4t62mKscx2gGI1gcH7QVaNm7gB9KNtQrIzxsrWBfxPEx5//bVCPZ7PaBciwyKtRk5SPisgWBBFved/XLqnTlqgaJQ4v5tUQdh3csazBFNTRjaapQyU+WoQLXueQx4gHgXbkeJnfXoE2V9Zzwz6zIAGYtwc76yi8nguDHsJxdpwScEP/i2IjohcXOZmAEzpHJ6iVq+IEznxIsThEmwwcqyJ76SFDR+IgANNKq5O6u+wrONwIVangbk8zdGE8phyMMpyIIph5NtaygA28dHl+S/aIVtyzK8QhctlxKFUUZDgohf7acobzt4kBikVerncL7uoT7gWY2faaCu4hgcXl5WFya5VNLfB+GC8w5HEFmUURj50ymLoJFK+FD+UubNHIHq++PNjsOt3Doei5DQJATYQoxJC0cuWaIYZsYVJbznSC+1e2AiHZpTN8GN0avrLzQ6blYVjk7HxaVJOKhIV6WHbXE+8bX03TFZFUdyb5LHRy8aqNAlIto3TBHUszRbhTd7duWkSiWeQe+OhULwWwwwWI02bvbw18DAypUE0EGbBFDRR6Sn8wkRJMPw8UTNi3gn4FSKwh7rGdGvdEpTWUes3g56lBhdjPWjo1xK6d78CQgJUn4FEo0TxlOK99jwiPQroYxj9FY/+dhU2BObiK49DcMpzLNGAGveSBMp7WZllhIqA38LhYL6AJQWexOcCSwlkzcsEa+MPj57CEl+4wENbhqRjHY3lp/rKqH4XnS+qvgcsIoSnCCbbUydQxBLrX9GqYgaYR5nWc7Rm9f0kanqNL7qQxhpmmOK5hCipMPQJTvgAfNsqd2RRYOqKOhOLLReCXbyb1hL5D3fcSeGud0fv8zld7nIYkTTWig1Vo2HHrjL7Ay2qfYaoaTAuO7lQ2S/EV5z4ttMBRlmF8xMnealn02bYmDuNpejb8SaOFyfSgcuHHS8Gzn14Drfxpvsnmc6TfeXYMQ19A5Shkhdpg6TIUPuRNmgyBj3Nv5K1kJpChmgNmLoSIDHBvLUoZiMmWgaOA7FsQ4sp8hMnIuAlB3kfma9yY5oyhu/aXQX+MbVbqxGfBxnfvWmv9bruLiJsG67shBGbGS2bj+NqwvrIchXzRvkpOQL+3w4ZpQkO0aj6WKUM3vAkI4WOEkwkziOQzYxfp9nI7ls0HBOBtHLaaM/zDm2K+SML8tY+5Xy24zM2CJihoyqeh/C5X5tTF3JZuw+u7nTSipJzyyDyE03v0q5eB0JnfReXvmtZ+iS1WuvtrsmRhbCLEoJWm/9968So1v2euUEZQAzzCmmccBqjku0s7GhyMYcxDiWHZXSV66aa2qCpejw2sDAwKiVLR6JzsjqxFDydpzQHI1rrkVy9QWivzIi6rr3D8jvcNRk/W7+zaVM+cDRw5Qn3s9i9EBplYo3qhh/EL4X98TX8N9vvt2Yy8By9WNpaKNXtSgMepGcNLgL+wHasir6S+UbF8taBPVMm+Froog9UJkNoy8IaXHa5wJqyWG/yqs/HOhavQIksrOP6PhVty5KYpWDkasjawMJJdN8e5royFABYw60gZTlcGnS6bv1iHTcwiboYaLSsfE2WKErcndcHAUQxnO73SeVrtVs/3XlC8Fpc76wATCh8GBIw7fSgzKHfx2sWTLAXzGKyDqYBGjD/ZBi4geCe4R2ADwdHWZW+XJwGEowy4h4kgW2eP0B6JsJDQryu+oOaqRsZSwkCdxvCCAjemVPSbtdauz01iTGaIrgMH3XZXJrP7PfCZpFFku5fEBmSXHdsCNUZo/lSjfiAE5dahNZsoyVbbG6/7iJO7OT7pcraXgxQGXt7n2vdLE/OmarFIr68khZ6GQ8YQAxH7S8UMUkyvG7NqEVdfjIPRGEXRgA2F6718V9QTPlE3M3Nj38tNWMPFarYYvWNGOk8TYuhtGjVyARDW9hAu6cZEnC/7Tv9ixfr+8OSYPSe2RD/RJxjWdKlPmloet9zkGKpCfMgQwWtipEm6ppg9Iy8x44nDaSe9bHVLa/O92FoIceyonOH8Oni8CeSPYS4EDucNxyZMk0wbJIh8S+XeP4qamZOwQZkNwygg42v/w8xDSvMrgSPrAIQSqvTmhCAQPkctM95EBTVwTHqXXGMvmoYUE0cs4HpL3XV6YP7o5fAjLNLs4j2uOYX8F20rp2PJ3mb74GlsnyLm4CCC2vkxlF80Md6YBywzK+DuyMDE7+N7vkuJbToBDkxcTR4Cz1vTdnLUH4fIVu4+eMoJ4RRNH8i79OOQEAljcXO4O//rNhVe/1TxnAEI4kr9U7TTe97DhYZegSTPrzjz9fYlxGP5uo5V6e56QZu8r+/mH0T1kPClYyLGdGlx9ilKFHU4bK664moDeKmnoc3oNeTGugktTBFU0JsgID406vFbbHqTEnbdWSGPjrTevcL0WXISCT9VHOdarNtHqGraEnB2HgGb8/Sx8htl/YaITfe85LdYU9jQ0Y5uAGU41Vx4rfrjkXpt0o/8NLnlk6Qw8Ks93fIJssQ3GxpAF1lnugivHP6oJ5Q4F7frIMJtAnmLPR8Kq94QKn67mOsCDBRYmXxIMJXSKbsxcU6N0ysgUSExLcu/Q1Ninm9RWZ8he043Rke+TE5FiUBNlcNTFqoWi5QMylKAHBWJvUD1SsRftDZzEExWowxYEym2uMVTwoiLbfCQAFN9KCI0pDEmxjZkDweB3EnxcN+KYOEvVP5dbJkhcaZdosA4pnmBxJPKzLTaVqbdiBFYVA6oOj5xxc514HFtVPzYJu4rI9vFMjIVHmQYrZgyLHomXtuaQJptF4+znUEPT554r03d5sxi9ZsUtIA8edQws4RQohaywD8ELkypaXn1je3COkLrDwS+GkK0K2olw0Oy3CRD5HysCMa0UsKbBM7fTEJhjFAXhiB2Jo+GXX//d1CTdFFkkPAcq17DZPpSTj3QCq/SXSkR/FyJwKdtwlpY1tRozrjydTgzW+SrLeT9LWrZ/vyzGHW4hzEpbfe3DiaGUsQh/GsAjmxqO5Q5g56qdCc2njJjgaxqjiujrgS8hpw2kDOlHvzta0szLCqb45hhhwo9xDX8zf/QpwMEMFcpl08QQHCffGlWjShbiwxoDDb4ae2fRWtulFf/dgDtd/30LJj2hTfqhzC6UoJuUGDI3HDMguMFQRyfFhu/41O2mb3C0PZBVpDjl8/pSbGEF4dfuWz4f5aVFQszwQhwWgXXP4maBrHGER4Y9/13ITVzvXlm4w9rxkZeUvs6PQkyVd9f3FxZMbvUP8dzWi9Qc0KI2WpwyGksZJdxs+qxuOD3iuk+8u3drO9wRp5AQ8tb7yBVLJU0RCYOeE8lodmcI35CYbvTuanywij6YYn23/url+275TF0iUkEAf8e4jGH23hnYrKFogIDBREvzug0mvfEQXJSz4+toxSo62jhcs/JlAxmMr+3ONWp0C4Z92Umjg2fGeVBihOVfnLc5Td4f5IXqf2Tx9ey9xnOcjYAoIPFplg9M1GyfurqAN3yLCslGRwg6AlfCpUWX3LecNYatV7kLY5LDH75jqCLw3krTGh1WxFal9ChZOUL61vX7GCOXse+bZrHCgw93hKnPWbBUHLx53VGoZ5AMaKvOS/gEL3l55f+hmSXg5o4wx9hhBV9Gfjwc0fYdELEwP/XcLR3RznW/7SRJBJKJOFBnVFFVJVn1B5AXIUTMc4wtL+zXIHKDNHuNkjZxBO+XMgqmYyuCQmbOwrCkLXwvCDVmHH3wQB2Ch4s84VL5o211/LTtXmDZM6CisCELOWf7O1xuI/D77vIwVh8YNQLpTO9LurF7cWPl7w2LHpSayt+lH0G3tKiy9BHR3BubNqCzDjGRHVirXdi7TpzC9+KbHmJC2niAiI4MUR2V8B/COnQIgEqcJWlxFsNq2qDxtHCJTUUfZNLRK/irpuCARhI1TIMVj6/coVDGEIsen2qwcHgvuw/pPzeZdRw7Is60YpeuKucVDOO0guD9Ps7S5IXJtd6my/n8dfkckgyUazhLPKcGIZbRgNHm+fXh+rrDCZ01eAgd3sOmOl6iqkuB8zXMR001fJhoWYoW5ZSY6FkkjHcHr0dCxAoPF7QjDERwr9eqzVE4hWW/HNH4xgUxBIpqkOF/Qgi5q7a0meOFnDLQy3ic4/pS340U+eQTkyhAeTXXiNUMUCCa5SaHcg1hsAG1yTBZ36a1et8tuk93MMgJKE6SyydOfkCXWu3yVGZxy/9DxyVNDWgFDjX5R+MDICENWlha/2U74fIRU2rczR81L0+q+X5SN04cz0ej2+4eYH47yYj7bIWiCDE6T1B4BjN4jY6IFc5S3O8uLFlxa6WTj3UzjkvZ67MU+wlsYV44duSEAoKYK9FvfLsNtMZB9r/fPWBqkpTHbPAfsMwHVcK3E3frNZXia9duVruH63cINFaTs7a+PZ86Iiy8ZsTV3tnAIIs9p4O7AlMp8p19czZSn3t7rJjleRF7BcfDEh+OSj9DkktvU5ZKAPUD//UH80OxZcdKDRaT8NHatK23EtdiGF9EJntMOmbuKu591/J4PXgGtZ2XBPEI8fEWXLbxAVuqmPDEn8EgrdMT2UC7CEzTPAYUxMuJricbC1ffGOOBK7p3e6eNKnXmkHs5t3lW4iiKjRJODEwQ7sD3k087gQRNcw6nOc/v8h8RMVpT5OuVwvJbPAco8DuR7MDxTz3QfEzVbT2ivVtN618aYhtmM4Dige/GubsFDYIMIi3W+/eR3LbrbvY5tth0HAN5/hbjp9R+rZ5T6tI9fsi65q3/B90wG/H09ZQhgtSQ1t93UqaLGXvYvObigQ6tg9U63r2GRhQsasih0TlXK64fx0jWG4FziQ4VNuufK5FHY7J4mV/Fs3XEkmhIBMzJbsbJfYJn1paBb1xOFuQ8GfCfqYKUcJoC9LYq8y5v8El4bDsCCd1EMaYBKrX27+dTNUDAI1/OyJQsZNMxN5nMCeWm8zngAREMbfrQXfW6H80eKbfdDql/c1ziZX6XTUqcvmFsLJb7EUbPyFkAIpb3P2mz8tJv2/B/PdVfJ/Ql8F1aC+4rlRQsAwEFSQgFLHlaoRrZDDQSSGTLDsPeGz8opB24WKKqqpltu4odYdfOcSNFz9uJtpaaG7wxwwjJjGVaInwR0rIvEkEjT0UsfeE8y7fHR/LSVkurgIArYc1oQCsuWS1SMWDNTGCCIAllEaR/lrYuB81hSwy7TErBatYBJxJLMNxwjt9Qdqe33KZb2fr03cPxS7Rdz/ErlK28mauQEULj0XEEMHVZbLJkvZcrn07o+X6h8PCYFzAvBApoHD7CdWChcf34kmWBFfIJq+IKWdlEs4p00ayN86eMo+bBKb7q/ngU47lGA317lBKbTBjTwfg1yyh0i6kUeO/MeDj/9VSqe/+8BePlIayQHsIAs+jsZcPRC2Nv0DFc04PSjJlTwNCyezheE/pHoAaaqyGVGeT6rBw8nj/gf2ueeZ4LqCDLtVCcrMUHjWBO+tuGBf+a2bslPwODiDH6DKunXGuM6VYTFVN0ckbeKYI3/4CdekbhulGAQSWb8hh40tKqCCLmndENrP5jEEO+ZAsbGNQQSybc7hgyKpDw0b2vdG+Hl3J3obXx+ckM8PmcEpxY34K0c1mESK5h+5MYhBIdIfJ6CzgxtN6xibq9VUPcxiNj/KTjWt1OtEKHpfVbNcoXYz5yBq1yM5+PVhj815IkBQBZjJakUiqoxPDpCVcrlCMjBzDHUH9J9LlE0qyXZa+BYT7+e6bM2+CC2c6dTOYRIQLxBBAUkXINQ2LuwkjqUBCQa3LixKBo4V3xq0ccqozRZqoWP2UBJozSGwQ2MM6zQQjh5CNIYfjxQgpYesMYVUIBD0KM9LnQi4qg628Fit708qW6qDi2jZcW+qvzAXYIWclq2ehKZNTgtDAFR4em/cH0/eQNC6uUOmloNUoWtXgGAdwGYqinUE9eeQwzDgQGiulDMGElmaqkODiefMYNE56da4F+armGds3SveNZRYQSa0JiBndaP5ABPl5WVgNjgCauqGPiK4KQcubFrse8gMpJjd9+roQpmzBvR2IZPQKMfeiocWvFMlYrPQ0K/kMN8Fr1INtDpsrgrrdZ7hLwOXqK9TKCaj1KqcHnFEgt5ljyXBrJlEpy39hKKWAlhH+BQ+9WggEjlFBIWL0M9jy9DFyjhcrVlF6K8jLXAgmUUITiCOp765SrdGZDbIaTeByYz4nH7VcOJqBal/Btma1wYzhVywOhvld4qTLUV2ft1wFjSPG9gQqujLQwVxYM5b0Q9KP2nqiS78bPAP/ucQCaO0PbgcEXHnM56I49L1ym6vwSifeHcs0w+TWkhpJKN3e3JfA0KooZluDmKg211E9xGEJRR4QFzOME+wvqA0H8wJOFuOTAoVvSJ9oG8vLwtvD98zSKicfprOIpIwjNhPIFn7/IGI3LXinEdMDu3JrgwgfNuLtK/GeCBS/EBCRogIywqAlcFA4Z1gI5cfSo03cTGcRqD0PHBFuT40gstG49XA2/0s9OLGxQKJbTFBdp4q9UUcV/DkfaN4g5BAfAgbhaMXgNq4CVMcSqxYztIIGjDkOZ87HOxgeGIjx0BPFWmQsik/IyJqckD2Mn2h5hlqiFckKlO7jszWsrgiwM1NXVH4ghsE02YXZWGEAl2wzCp1nXB8J83Q/E7HdlkJgwW2AsHzBKZdxjWof98OgvALlbaBYNV1OxF1lx+g6cEPphsFPBoTl3qK7uknv7+KwUh4LKSNI4A8mvWKPRQJvAUgznBFh2LzHU0AoNMZQ1dFld35ktrDmmkbmAeAzhuCKsCfqP4wldlAUnHZFL6yAc7bB5IXoQTcAfRFBDop/ZdDijKK3JjsxjhG0MTZvMqBlJolJMXw18nQVi56LS
*/
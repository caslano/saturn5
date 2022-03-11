
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
HCm0IJt4OjV1HO8g+878Nf5D84uiNKDEOKI4KQ9xEnFEzbCVKftjJ6DlMMuBQPv+75W05gamHK1clxnvV3SFTFExOPxi456mMa2mZbVzUBeOoE4ddSNt2PKtEx/o8EN9Y2gT7WRPNDjJF5jJG8DnV+s3eVyurTOdGQYzFY6CGPNGC9+QXUaQlo0VW8ysSaGaGD5zW3r4mQ2Sm65MA6qbp+tNnv2R9E2ec9ht6KRjT7IpCza2yWEjnEaIylyFxaA6Ler3i8tU+ZKXZXLTJBcIndukhxEQfKykuUHhs4xiJkVOxsf2udm3lny3xAbijrCJfs31MrVRg7fwPtoQNBAwr/tYPSVgGsVMsKaP2MaXbW/jJ8UZNGy9YVNkit1umYfxNF99hddzoibf9E9XdkOlnxqWYHn2/DwaJPVrdT1q3X2jI6rjdQ3+AYB3gk2uTv2tOIl0t3iBtItic2i4MRpkkBGXUfVHbJfNJY9gK7F3PEV4nRCdXnC1C22/9oAGPVKfREZ5yShaXWujt07fMnJFc6N727z6Su6m6ULxj40uYzll6xqKOYK8Q0yj5hrJZTySVGlxaKv16qFX/W88B8Z2a72zPfc7JndgJ7hXjpz6ll/KgXt3TZJVRKFynw78Uh8UFXpy+piDcaCDuntRpyofVfjCwoLvJ6uxsxRAZcHEwtY5jAsK3z2mXXATQKgwXRa7cDbjZNhIucZjdlK1BlubG/Bm5438gNi/mS7u2Oj7yzTaUr6QvifFMU1mYiushnlCeQnG0v8R4DzrAT6pNHJ1OAG97LlfZE9qryu82XbF9lxpaWf0Syu184UJBJkKjjbIX4iyrqU1QUPRubwpCam7A93HFEtUpYLKOil/TNs4k8SScU1k4zWwZ5qnHRrisjJ2MfdUC/U4F2908sPEnjn/UP3ykv+yUVbQlLDxGtpsO8Hmr0jI4M4meKfEFtk1yeL+GVTK3sc5bH+wTp+e0B+3p9g9wtsu9UBEQ3tUALJk+M2S4UHMS1d5XgaXIB6d4tYOtUmoQU3QL17pzYKvkhz5mjJklPx+FolIsMCcPOsQQtnq0mXHk1dnBfbHPQ/IT62PGu+H/Bff0jPHx789X7/1OAF6pNtB3Q8QYnCk4E7/gXoZw6PmFyiMm+k7sYnh8OOd533I4bZEDQ/hkeqTsc3vtKhCPNvoN4MQXf5DEonSNrVh92WO3fPWZSf6beDT07ITAx/cC2KhgViJtfTcWOhdxLqsaWrd4tMQIxSo10KoTl+FrCrE/ffFQ5Z7jk4ovghb95jGk9ga/KvfxxaaU9i6NH9+7nTnwQmKszBrdEpuisQUM+nCxm5Aacr4OOZ+wf14wDmx/fS/0VT78w5g/uGwwKRjSa8n6lTb8ib0lRR7OPZum64xRa+YLrXdiMQWjW1+C9pxQ6T2jRDNHxR1jdSn3mHUhLhxDvQlWE97kwh1tA3fWg7Mi29bRoSNNrJLH73e5nkEatfexWIfN53MvGCMtqKNX2a8elt/vkEH0+Rh1bpUI/y9b6P2YYyL61U4q2+QyqHOwHbop7Gwly0sSG/BbMx9Be9Nl+B3lliXuE8+7WPg/arJH5490hR60/QnQvmO8CoV0zUmmVhUfMY+5icsMOvafwfIBWnywOmgQCWvrBIiyCjP4kS22A9TXmBBSarcWQT6Nz1w+ekh3YmBAp4CWrLyT7eOe3OCsp3B2fcdrCdwpJGI+RnGMSLgMYNs80PfYIR7+ZbjyVlMV5eDofukMp5kKE0wHME6/swOLVf8WcLCi6D11+u/mUyJxBvI3gO9bXUT7KTkQ9OLJOo9VGyYkFfQYw5uq2QB9J3V25q/m9iy+U+ajo8SJYvPdfBpIafC/SddX4SWNArPJfEQByVJWixx8Ks2muSE4LT8AamTsjxL9kjlwtZIh44qNREw/vgF3Q5MbFMdF1+3jKB0tlP1HpHRp2L4F16vyvkf84Ftkl+GukyhicJ9WbAy5m1jlKZKtCIewDrv5K1MeLHuTNm5uh3CPtkU4bpMbtHVQjv6vdpk/s5i24zrlwtnVbtqrLqLWgYvTo0MNBzd/JIld+OnvPJxU+kMPuUDggfHFdg8LTBIV6GmmD0vutxLbk+5AuMTStYH6eLK/0vxO4+cRVHI9ZCFJF/aqvAPiZ11Yf4sGmMad1OMEMZRzjBg5P7FdT/JfrXVkId1C8d+ssiEizkzffmANTzDxLuB00bV1a4f9UhE5ACSpXjK+Zn2nrFRpkfSqriuXt2dJvHMYrLqSdXVEoTBvYA1ER+BTbFmAnbnnvackYFLn7x5fkXjgqfHYvHpgslFhRvOowzRxpzIs4wXy8uhGjigK0VohO39N3dsFEJVYyaeANq+vfyeYM+J32zwNmzhPu+XK/ftxp6NzDN3C736AUfeF5orbZxvrif6LGe56d6ka2iXHuF5MfT5pTO46Mjy7444ZM1tlAjYQwl3FvQ1QfEnaFU5AasceprQDB7qTvT68GDvmBU4DgZcGD68NYemVsj/fNR5aHVRr4VMu7CViKmwTXCpA1q1o0UbyMImdPK4QuvsZ2j5lR6duN+jCYyPV5zLmlIvwKUoipOYJDlHiYtpSB5dFdX0R5Hn3My53JNrUl0Epu3Fd/DCVmqKuotrDpQPguXj8DOkFICF8RtwqEWpPOqEtN8U00OTfPTilMDk2TCycZR099IxpcNsNDWZipJAi7Kypb5oAlElhcgFlTMT55a3Dl9D/rLeTE0R6sj/5tUtA83mxfEqohexzNYbvdeI1jQuGUnknnzb0oV7oVLP8R6y30A/W32Efcu6576hyCdMOMQoC+tnF04QEbRMKtldfr3bf/P9opxAMGnV6DEqMU5hKETZFs/kFxKsKdhs6gbftMn0TV+leFYYoIp8mVvHtf40owV7Xre6bPZpodNoqSKfyba/+OPSermSfLHmInz2lgbu7dDDZ6NXS7Qn9tdJMeDxMIgqGR9PgWztVEZle3XKY+B6Xn63JuvAxmU5kOkVifEPZFo2/OdshoV84meaoK6A2rliDAt34yYFxSJmn9juH4xXy93CuDHx3nr5yvUyQ07Q8XHNPSQrE21Yq2JpbzDOgLPyTq6PcqacAPxZeIFSV9UQyoYk5zGXCqFORcUyHD9WhTO7udPu8uGFewFMXWyi6svZLYt/HLAaNTHMZogq3Cio+5Xfm/c4XCRemIU5s32//OlzRpJ6WrDjr//TsExrQpglAfKCaNqgG9g6P3umXi+vD57ny53P2SQ06gMIgjlfgn1h2wah9gTsERpnXW5TXkrLGmxaZ1tWmVOkI+LgpHA52aBsbyjWoN8ynZS5yHnj+7xyNCIepK0Qtmj0EmzH5Q5aHPA/fILrMbKTux4gn6h8KUzLczmCM5Cl60s09ayrm6ETs8JHRltS8PM1h9TkH9MbtWfo6lXxtv+wxWzNECrK3FHzYjZGFqbOUZ875+lqnhI86iY17MXQdZ8AHoU9mAqzGAeP2Z8nHQQadFTpOjJ457aMHUMP48OKPLNTD/KZ+3mvTIKZsqVeFynWAuMVaMifULAjjwf/TIj8oSafjJMlwUq/A2nzZ5JxL2tUwAYgq2itl/Mukzz+4chsFziSGKIxzK9Ds3pOs0da64S4ec7RGKiwRCTJ7eJegqcOzyYM48SnOqJzz8qQNSwleJl1M8XimKUlT9ZC2nAEam2cH1kfWJGpYBy2kgafha11w0uIoI+5MKqM2AgJf9D6DCrumnxZPhD0DdVSWiFpTSzVVlnRc/dN1QIuCD2RRFH1JOmKU7tSJCVn5THQi/rvcF4r8OUdhJEn5NmELNd2AN6LRAu3Z055cNsCGiCSDoyy+4TGsMv+wWI423jC0Y0mxEqs1Gn8+5HbzOgC24iNZBoNNwXuE/+ZZLrIdHRtbtjYuoo7cViS21PtQLAJp/O67rWivgDB/Z543ufWM3cg+wpHXB0QtvaZ/rXYSbTSekHKKqpXUrBhlYYhi0YzNVd5Lz35JadCSYC+WnJKXkW5vshflVyQLuc9SxI4M8jb8+pqoFVlsIGsHVSpQnR6xHShab9l54yMxLhiWkeJ0QDNguKp0sNh2kK5cK8D0KHz1GQAGPb1s0s85yg+CnQUc1guap4wv6553v0JQp+4lV3OuK2zdcOMj7P+2DC6tnvOREe2suLXxL29BlFUiP6FhD//LY2NBQcdjC2kHa9WIBkmM0i8J23v3yr0AW6Ka6RCYu1x4LO6vvI3RcOh6Fc5M8ccFkU095wlJa/uri5nTl+ShSS0cWc97q9EhapCJBDLXZxppplP8Eb7NavOAnR5gelGv5ytGmHWxfXdyZupzOAZTB7H7zu9BxGMRhGirGv1tb36zZdJjgitz4H/9H36PKatjGWZbdMSFgcyoHL09z03BrLpQu55D/84agmaLj+nePiTKBzopaHZt6NwnLhwLXYHzRnQftzlGOiebJ9h/BMPYMz5V6MhyT+viE7BIj8GO3B7kFFfhqFARS2TvDvmZQy843bbsPyLM7Of8CYErPjbS/+q051HPsydZVrJSLhrUqHP5zjRqAoKgLsc22P9JYZ6iO1Z+rlRfVFpd8U9uAl7Za32SCWfnPi8IqKgbRcU3ifM7zh6LnGrDps1wiLyrjt3rYjLWaotkHJQT8zHtTp9hp9iOxp7yO7gMKjcpQK1Y6RLmb7oYIHsjHZjg7ylSDywvzvjbf9IJ1DZKW8j3HPUZeTg3rNrMBFzxJDbkVxfoTG7Y0ZQVfyCCXtR6cL5jjHTFYe+jzDs2X7tJaVlldqBt5F9BbqzBnlTKm4jRJ9b+l5jmd3Sv36tc9Q6xxDh0BQMCT3C9J86dRa5lflfWXT68FV1zqXAEkej8o7GX1mHVRh6UwhIukI2QjkygPIlQrVRmBQd8dNqaYWU/cng/a9JFbmK26aIGQEvqkYQ+Qzq1fA3Jm9gl/B2zboYtWGmwjy+TQ7Ldmb8iwqtnWcA3D2irhpn7cjO60YLcyDt1MM2Rg2ZdCCV16XPPustV+L7q8e16xiOmIJMxjECvNLyKf5uepxKJZXLUE35yBko7RIDZEQhV+sK12ncA1hNqC1reeA2k9BW4DZqODsGtrZFiode9MJaoqczb9akpY7oBIGJNAsWnoT0ppWVLIOr/2iQRsTi3Bn8012m8/YYQheaoVzz9hplFtYUimnh/dLoLpwNZksV94zOka4DtBugDWDze4aeym75+tr87wT4kM5N97v2Lc1gJp3A2TON0JtYBQ1iqqpQ5FVCzH+mPbhtsZpxzGIjwYcVDvBt6Dab03eyryB29NKj+QdqIsUVc8LpQWUdKHDO6CTXOod/G2WZmmo15S5LkAKqOcu3VPQqohtVBcKKwyri31iATbPbaQZWvQRewdiEoFMp8w6VvyoUECGl1o0IoLk9TY0hM5ChiDpsxTkws3v1rz2zxGXZ8l4YnpkazZVuHgIX9tEx/8NKfZ89xpCc1W3Uf3LxY4DEP4BRX9oWSvslGNPxOHhkYGufwCGlTVGNwQ4KbktcbY8wIW5fBXUujZn7KvDxefHrdXIwsa/oIiEKRlXCgsS50HGTXCeJb4ZFw7xTIseagLYmkIlHFD33nzLvrB+xsX/arCR6cdVc8K8xjrW9Nh3O12CmCSJqPH51gqqvMrp7Zl21Rc8z8cfvFtsysAITciARZ/TtVo/+MGlNP0NnWG9jsU2h/R/VJbKJCYlswc6OyljOBXxLWdbjDKmJpiM2x9zXUPelTiife7AWRlD3mGDw4zRjDZWqkiXXHfz77/ydl5LMaVY/rm+xhuxa29XYyxdZ9bLSO61j7GMeG0csNXtqbwX/z6Tj7xMH5FOvnJ3kOwuP6M7qpG293eybajfk1n7f3wzcVL8HKrQ6hEjvCLXJLgZlWiUe3xIMCOrCV3Szdo5xkCLpUaAT68FoIhBNI1eoyqoa3LBX/+pYhNwTIoo6pzXzF6dinqWchp90B8mfRn38N1W5cLPdq1lxR64ik7X3p/M6+EzykeLFhElmlkdktOJ7RkypqW2NLsNaLi/0FO7X0R9vWgOjXyq6LIUkC9OxM3ye9pKjMoOVoEeOcXE0Y7gxtj6oZvKoXqWxwJUupOZ9eddjFNP4Bt6ke8mTkDbIzbMr/WfT5yTPcZmdYNDCYbf1AO5aVbFZpMqsADKnACYNMh5skoE9A9a62J8IQ9+Ffl+X80Kl1Itg4zddTL6kq0xFzgphYJVyJZUukVwZ7OJFXapcT1E9J7P6M4GHlwQNT6ym8CVMCQOk5i1wzDPPA+z2yuzjGWueWuHIvvlL8BpxocO8qLBdEzajg8hqir0lI7ZcnDY6eTOiURmQpgLbDUxfBFXvdVWiAUvhb97Sgr1kabWNb45YV4WtbEnfBNUz5rhaJ/HkNlg2frd9xz4Ouh/ajXHB2bBTcy78Utg/zoT4qfcNv9SV8V3v88njk3pmKnnyJe8KSpbggHOqB3QfFB8w005wkWiQmgoMeJUnwX4drOswudvHvfoiGoJII+uemGmlSb0kTYUtW8IkpGk+YFC9FLFpHg4tmVbPGqEP/RJb3qjWqsiEZUEjNHo6gvVzzhvoXXmARdngSD4TlJ4rGMku1SNHq4Q2bVMKckuVF4USSzobp5WfD4cAXrKNxbXE52FgfXn58nLmOTA8uwqSOhIEGe+fNlPfpIUJcu38u4kJIGsRXPsoIXmKzl+NZ5LPyrcWk3wM59AqMMQt4Dmjr2kzw8a7pW196/IaydX0/XWh4Yr1ueu9T+ZC1C0YiLvgPqZ3AXbdic2Bi7kiDIQaDNbtk97F/pdph/DfJxJ9Y96vvzEYLQG+1AL7zjPopb2BfX8gT7gV1yh1hIz2PqGAh+mNgZfJWVhu3HFUi+woGo4KoQtuzsx7lhycfXL91NRl4ruuX9Xdy454IQrzZtZR0MjttgfQS7yQFcag3L/0aRsV13AZzn77GBP/Vqw9ZgfrjjU9ne6Q4Jm3PJQBmz/K4KOKI3IlRd2zZBfJeA9jGhz4t2dyS69gsKgO/XF93FtyLpVdxCp/A4ZxkesgY4yz90cpU/7qWpyrRess10LsEm+SBPodStPSmkX2Uun5jTua2RxZ0zuPTyxXlgAd+nH+zTnvzZM3Px5qTYgxAlem7Dnx+IAd17Mn79pPlCMp8zyohWUty/TqE2x0/uWTmEdccdLCypmcfdZ4JnY6/4ZfxRZvtfDy9EnIE3HS/MM6FNTYgiM7e3SK65jFpsews1zZhk/fBWFr3izry2NnQpidX3dGxJZ5El58lpCJTATWMyx6PWyAYLB3b3qPa43FRblT5o2JIFKfihrehw8LNW263vuKU/WPWgXqmLNMic8rYitiKWy6O2YSc/Kcg/eexv0h7R03p3+CJiw0SbJqBYVzbyw3lXCy6BivvhM+a3IugRl0CZOsTpCb53vkBMj2o6beeRHikMbHf2MhrhvQcgVRupgt5UA94uUoEjGNM01YG9F06w+h9ZGnnb9AxpelNZ4iLd4GhCkSyK52i8W+lhxb2hYX9ffyuds+ySjbzSVCs+kD7uRLNRdt8mDShGlxz7WyWpC3f9fdVUY3uIroXu+oVxZni56nZM8OnhFqW+d70RARtM9PfshdPRIi0ExDuxuskfKKYVD8e7zolpRMUJYb9vk+AEFyZ+LY58E92Zt7bAPWJQxpewpZIwJ3WzEB+uQQIZ4gej0ot0XtHDq9uH35aUWV2my6MenD2jvQ/zAv1DVLCQtyitktBKRq0gVKXF4qEkdmj2EeE4aWSR/j37y8OeueDN/cx2TJGepfsm1Vokz0owSN3UZPrGWZTP3TtRly08IrF/SHMX/WUZ23V9hEs6NSXJVxh98UH/6CSf/RMItyCt+0znFh9iZ7CDSTsBUHmKALfU1u9+aq+1uFxT6kc+e+s/8y4waGIwkEPz+T4z986ikU9nrkMK8AI8nBYjgfci3PsmSVhUNXsXaqTfAI34q+1ES80arR4VceFkcyUTVJCoWD0YYwD3OjJgS7jvy1EI47lsekDAFqsJBOHanq1OCQ16lp3I2Z7VPWnuUU3I4okfzq5opG21rE28bwsLjxScQj2Xs/98GoUIp0Iq+o+xMADSzy08Ylq5NgnSXi8z+178GPTbxzObY1La4r4peO+gv0PZ0J3KfZ+LI+G/Vzsvy154VTosfV93OvIFNxi4ubaGFxiRvCL6ofdKyPHkLzm3l8dScC6F70W9QKomXkjSDTurItJ+036i8Uf9AaIhHzQ9/ChG8fS4SsaVB9i9NeFBFMWVchXMC2mRXfVDMQdZNHpgXlUulHdyU5Gcqjx5z/BuOWV/TcSlokrUlfghThI8l6gYV9acoUGi+TsKpQl6gUuF8htUoBmqTWrG/KWjTxeaNztL4z8NOkEr/7WjwsN6qLWzWe8+v2cCmjdoyML2wCjRf43YZaLTaYc/B8cW8nD0w8HAywZNAnWsHsGps4t7RlvCdNR0J3215LcbYlbYpbHHY6IlPMMVuo5J0LE1kR4o1cKdCfsVmc4LgDs9e/hqqhTJi2dK316hsEFj+O/riQblqEpSHrrOMdZd/aQFpaCDnpE3bZs3CsWuyWx2ktDJAY6JxRXBBPIewecXZP/4Edh4W8ZzWUNkTibFs03Z5XnvJJgaJf6quypnROEQNhb1Gy3pGtbO9hd8BsIzTv3LqDcC/uVNmiz026Hh5j8L3CNq9+iCl+daEMzTOmo2zxpk3EmTiI2Kbdgma8QMj+D423is7f8kb7nso70wcE/zk6Z3XE9L8Q0yR2C7zoaJcwzeEo+CFLs76Lh83I9MNJsSOKgSrHmR7RG+tzdZnKp5mwhp7/lvZdiOqmtFpQq75KtE3pOmqt14pvgs/Xqy7onkBEqs17/Bb1/aBRgdXCtp0t6HtDroVAV267/WnO52z+bKMehS6d9oj1kUsQTN7Z7FiKIZwJ3mdg5oIUNJShu3Vn7xaabY0r7kT6VNl/Tvry+LrPH6YqZcE3wBnhNLoLNFnirdupfCcD4pMYzZkt8Hwu1TC8WxKkCPKByD1HRlDqgYqGFA7A3wOlBwwaxuokSNQapqnKQpaRGtXqJKT/7A+tdsL6D7vzGbtVMRSTDZMLBZJNBTYGGp9FAzMq4XRXhnPDuYt95El76CSF/PnndJV0O/x0tWN7zSGov9gfWt7UGokr+B51ZP35tM2tWJ/wyG9JCHE=
*/
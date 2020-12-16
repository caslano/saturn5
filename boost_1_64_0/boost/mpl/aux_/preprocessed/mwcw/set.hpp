
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct set;

template<
     
    >
struct set<
          na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set0<  >
{
    typedef set0<  >::type type;
};

template<
      typename T0
    >
struct set<
          T0, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set1<T0>
{
    typedef typename set1<T0>::type type;
};

template<
      typename T0, typename T1
    >
struct set<
          T0, T1, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set2< T0,T1 >
{
    typedef typename set2< T0,T1 >::type type;
};

template<
      typename T0, typename T1, typename T2
    >
struct set<
          T0, T1, T2, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set3< T0,T1,T2 >
{
    typedef typename set3< T0,T1,T2 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct set<
          T0, T1, T2, T3, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set4< T0,T1,T2,T3 >
{
    typedef typename set4< T0,T1,T2,T3 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct set<
          T0, T1, T2, T3, T4, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set5< T0,T1,T2,T3,T4 >
{
    typedef typename set5< T0,T1,T2,T3,T4 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct set<
          T0, T1, T2, T3, T4, T5, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set6< T0,T1,T2,T3,T4,T5 >
{
    typedef typename set6< T0,T1,T2,T3,T4,T5 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef typename set7< T0,T1,T2,T3,T4,T5,T6 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef typename set8< T0,T1,T2,T3,T4,T5,T6,T7 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef typename set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, na, na, na, na, na, na, na
        , na, na, na
        >
    : set10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef typename set10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, na, na, na, na, na, na
        , na, na, na
        >
    : set11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >
{
    typedef typename set11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, na, na, na, na
        , na, na, na, na
        >
    : set12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >
{
    typedef typename set12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, na, na, na
        , na, na, na, na
        >
    : set13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >
{
    typedef typename set13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, na, na
        , na, na, na, na
        >
    : set14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >
{
    typedef typename set14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, na
        , na, na, na, na
        >
    : set15<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        >
{
    typedef typename set15< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, na, na, na, na
        >
    : set16<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15
        >
{
    typedef typename set16< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, na, na, na
        >
    : set17<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16
        >
{
    typedef typename set17< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, na, na
        >
    : set18<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17
        >
{
    typedef typename set18< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, na
        >
    : set19<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18
        >
{
    typedef typename set19< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct set
    : set20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename set20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* set.hpp
Qfy/MC+79fF/K75+phFf9zrE1z25gdhsZs7UdH9u9ujjs/W2s53y/ofYHtCv+barnXL/B9vut+9+0dvuJ9vbOOX+b7A9cZJlNor4j+ocOfd/g92szKlF+1qmo4ktmXV+xcF2Wq65T2P0fWHXuadD7D4j2G5Odk7/9Kyo9yyotz3Hwbavke3o6233xwoH2yUNtk/OzsmMus6yy/g6vN3yXGMuQzPu59WwztP8uEZb5XEPH0dou/zrnY+3zvtGH3TKmS8mnTPsq5Evpjx23U123EHPGfXnu4jpF06XnzND/vVM0y8fQW+S9CZLL9fQS4igly+9AukVBvSQCHrx0tshXH52Jz1z/YH00gy9tAh6u0lvd+ntYehlRNDrLb29pdfH0PNF0OsvvWTp7WvolQTpRb+eozyC3uHSO0J6R0LyCoTxp4Zdvx5p7XqTa9a1Xj1SznT5Lx1zpLd6bXqkdellnVkrgryCfId4N/R6EpFUJAMpQSo2dH2AbnGLW9ziFrfEosRg/F8wLS+v1Xn/7Hn78f55+wVB8+5nG3v2xTvl+pscGOcwfdJfp6jGOfbczwdld3fZTdScw+p6u5a9mO5RZ8+FTAsdP2tOamVDvWK+D5o79++/NfdvX/9YuOLQu+Ycf8viveZ53n9pp3vyr1j3c//4TjvOcdslZI5bojGHp1p6u4eZw9NHevvATWAS3An2hYmwH7SvXxnh+j1lp5euvyfMjXJtfdWGbbOufn2bh+POwWnfNfU13DffId44dxztFre4xS1ucYtb1un434pXtnr8b+f5S/jBGv9bJrVW3FjTPybwWvA+/6UN53OyjPNLDVsTs+p9CedEsf+/b3JQLLbN9v8vCbKrBkYxZo9m///yYNtttv//gmC7bbb/f2q2365lc73b/z9jklE3czF8DNaaRrP//62Tmrf//2y1b6batyAr0L71dv//Eq3l/xTZGlkuv1fJxEDdG/m9Vng8zV9v3gIfmPV5VNLmWdRxEOe6ZDV8Holco3Av3pvva/R5FCkPwCp9Hl/bOT9zAm3i+xW7z8NqxxzaMJh6WeeOyImwrlnv9fHe0dZnkeN4D7o+wv+gj3CS30fYfeAb79856IPqjXbOq1n91IiD1r2P0BfBR7dPyLySfcz5IS3UK2+h3oIW6CV49H8SPiS9DnBL6fUKvE//s+D7Yd63l7m+Uc+q2WF8o7tqXWIiHK35PNM1n2emMZ+nxKPnMPxUdiy9ImNeztaal7OD5uUcCPeDh8P9YTZMgafCgfA0eAAsg4fAG2EqfAweqvWug+ByODjQbj074arQdssnO68j7cFfloqMi4tujaQvzvXPFiNFV8dF5aMtvzrO9dMaftpS7p+FyDKkFlmLxHu595DxSLHX9d+6JTYlBuN/5kL3b7Pxf/J31phd06uV385+Ldd8TaNn+7WKoNf4FW3o1ZivMeIxX+u0ynitv/Le6bWUoNd0QUM3L/h1Ltrw2oKg17io8dryRnb7Bl7zfh/6WorfnzFvV2KL/tdmTMn0kfnH8IsMtnX6p1sv+v0c5xl+jjSHsX3lSaHz2Zsef5s+g0UOdqsb2e0fld1A/kOHOfI1je1G7ZsZKNvZDrZrw9nmg4lmToVpf5mD/brG9pvl/7HtJzrM8/dMCGs/Jdr6231f4mC/W2P7UfuYbNsrHGwnNLYdtZ/J7pcDOzusjQlj2/qSNLdf5jvYT21kP/rcmXbd1zjYTmtku3n5M+26j9nQYa1MI/vR59C0bVc62PY1sh19Hk17TlaG8vFVyF8yX/kcy4/227YeeP6Eji3xy7Ukp6Ptm5tA+7g4rqKQvWJVgQIGIZvBXPicVd/jVV/juWLm1+zSjL0=
*/
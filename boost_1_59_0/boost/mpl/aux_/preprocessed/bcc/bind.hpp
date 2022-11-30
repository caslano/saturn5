
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bind.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
{
    typedef T type;
};

template<
      typename T
    , typename Arg
    >
struct replace_unnamed_arg
{
    typedef Arg next;
    typedef T type;
};

template<
      typename Arg
    >
struct replace_unnamed_arg< arg< -1 >, Arg >
{
    typedef typename Arg::next next;
    typedef Arg type;
};

template<
      int N, typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg< arg<N>, U1, U2, U3, U4, U5 >
{
    typedef typename apply_wrap5<mpl::arg<N>, U1, U2, U3, U4, U5>::type type;
};

} // namespace aux

template<
      typename F
    >
struct bind0
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
     private:
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
     public:
        typedef typename apply_wrap0<
              f_
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind0<F>, U1, U2, U3, U4, U5
    >
{
    typedef bind0<F> f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(1, bind0)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(1, bind0)

template<
      typename F, typename T1
    >
struct bind1
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
     private:
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
     public:
        typedef typename apply_wrap1<
              f_
            , typename t1::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename U1, typename U2, typename U3
    , typename U4, typename U5
    >
struct resolve_bind_arg<
      bind1< F,T1 >, U1, U2, U3, U4, U5
    >
{
    typedef bind1< F,T1 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(2, bind1)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(2, bind1)

template<
      typename F, typename T1, typename T2
    >
struct bind2
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
     private:
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
     public:
        typedef typename apply_wrap2<
              f_
            , typename t1::type, typename t2::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename U1, typename U2
    , typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind2< F,T1,T2 >, U1, U2, U3, U4, U5
    >
{
    typedef bind2< F,T1,T2 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(3, bind2)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(3, bind2)

template<
      typename F, typename T1, typename T2, typename T3
    >
struct bind3
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
     private:
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
     public:
        typedef typename apply_wrap3<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename U1
    , typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind3< F,T1,T2,T3 >, U1, U2, U3, U4, U5
    >
{
    typedef bind3< F,T1,T2,T3 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(4, bind3)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(4, bind3)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct bind4
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
     private:
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef aux::replace_unnamed_arg< T4,n4 > r4;
        typedef typename r4::type a4;
        typedef typename r4::next n5;
        typedef aux::resolve_bind_arg< a4,U1,U2,U3,U4,U5 > t4;
        ///
     public:
        typedef typename apply_wrap4<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind4< F,T1,T2,T3,T4 >, U1, U2, U3, U4, U5
    >
{
    typedef bind4< F,T1,T2,T3,T4 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(5, bind4)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(5, bind4)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind5
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
     private:
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef aux::replace_unnamed_arg< T4,n4 > r4;
        typedef typename r4::type a4;
        typedef typename r4::next n5;
        typedef aux::resolve_bind_arg< a4,U1,U2,U3,U4,U5 > t4;
        ///
        typedef aux::replace_unnamed_arg< T5,n5 > r5;
        typedef typename r5::type a5;
        typedef typename r5::next n6;
        typedef aux::resolve_bind_arg< a5,U1,U2,U3,U4,U5 > t5;
        ///
     public:
        typedef typename apply_wrap5<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type, typename t5::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind5< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5
    >
{
    typedef bind5< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)
}}


/* bind.hpp
ORTt+OIkOeZZGYiYyRB4c61yOVRnKpCwnUJOKD3NfxYlRFI88N30pCzPH7GJ/jzKiYCgGvDjFDG10Cvk9vTBKRTvp1PGYTRta6qzsoERUBKzgbyrohY7haGSG2tfRYi8ppv186Yv/viIEjDQvVL3Zdp+gghK29dPIPcNTLWeA6KRailHYfBvWDxvu2FVbDNeBpdVTkIldUz7KG3wXX/1UbRqGJvwzyfM/w7IF/FGYyefZ9871aAx+gMGmhdhtQ5TCSz24KFvKEh6UBf4mflWpmiyWXJTy8Jai1dIWvaYkVz9/RQ6QA8akQSPDR5oNQHoX8jClg+3SCqVY3A4rp12tpI+EpADUccZXkuTkojGLzXdcMzbsHEZPLAHYLA1COQRMCWxEpRzgDN8CIxUPbrDv0gcKJrL1SPjI/vy3PifRa2oWnYSJYwYEvLoLK3V+64ksOj+3SxAtdZw5DZFhskWTR027Rg3X1NMrShZEjdeQcmM28GzLiR5YH0GUjTRaAdMU1p6ZWzB1ZtYG5NsKd5s4FZRfz4eXSPT/4B+Y183ztZlhjBkM9DvU8BeYbJozpo5xGqY0griAneNPG2Df4MF604J4QiSu1HE1R36zE8gjpG8CxK0jKfJAZK3OR2ACK9/87N5w1z8XCOXoa55sjGp7s4lh3fOuwaaEc3R9fQcc77oQfXrvaoJfSsq3fgk4ni5ONrSm7TlywR48GqapBathD6Qy6FgRBAg4+BntkaGuMrCRQQiQA0kYeYLqAQJkckDjIni/+GvlQc6bzceY48NeNb3/a6BeGX98D1exQCnt75Lw7P1Pcy58V1UVCrvZ5RuGJxv/PrRPDc64f04Lq6ZrMKhvU2tZ2wH+MIRU2GETxIi4p4nO8rxHsbuW21JSoXlm6gtWZZW9IjHg1naUvFKsJWPII+JYLX/J/Aiy36dXUorCYwfvMtl+Q9IESttuOV5XpxCnJ1f6xDl26GziZIpvxtkm5fwXP1FT6fjdbxA3H1Ooafd7hPfsN2pcEl3DYqFGCAGdNFM4WBK85gX+LD307HFsUuNXpg5bjamEqqvjA+eHSIAaZ+y+IRAHglTHttLigwhgQWBXs6rvqHAk6Z+T4oop1S3/4e2Y5Q/UsOsdP03/rrRW2CqvtePxCIi+azHfl3rY02VAXs7TGUL7cWRDbflhz3Y7e7XQsxJ6ZDOS/FuBzL5OLCTgPP9iTeLSIGR4DOwQgQd7g/ePeeis3wvp9eZLROUuGBV6054O9hNqTG+5uLVuw0Pz2Ol+N+JyJ6/82HG9Ha1XPE4CAe4ReLdPW2GoRP3R8C/MFTvKvJWs4Qa972iOCu6NuVhr3JttB0+RrB2KcptXPr31cVcE5BJVeoQk8S1X5Vl6VbzqaryJqsVoSCgiUUzZHB7j43Kz0YlkyzWN+/8EKV2O8Td8xCF0CffMpBRmulOnacEQBEKYiIyOf/uw/52B2ZJeC+k27OhZiSnFcNB+rVBtoGuZek809oFM0tZWVB9dG2NBwBj6GTA20njxKi0drqk+/DyK1rHlaM3zhGuFX9zpXHuAVbj5civQMAb5I4V+HsJp3JIdj1JdkT+Czyt2bzXqm8Ob2pYgokgs9kAzQ2ggojqPMqaUXmGNViKjk5wuy6+qHqhk3ghicQigGcS7SW1UebqvNzY6GPNu8a4yx7skXxnpzH4aG6kSyEETH8aiVp7m/pUlpf1gVPk2USs7FUDjEaamyIb5vx1+XlhBHWGLXn2VD40mbmAaGKXMJOkkTQV+ADkTyzYUMooAWFIEJKI5FPLw6vQ9zOg+9DkHyvCi7dqUYxt5bSVVzbjRI2+G6ymIfp718uNUUK9pqjD1RvK7y6HGx8pMw9Cy83hljv7XSeyogkrN6NKdjWRoQ+uOWnOvzd2AdGIwp30EyyKLHGNdZecvnjP1XVPB33XVzexUEmBYp8l3ABCp3MnYIbLjGZ83MAK9Jy8kq7OYZfz71bDdggu+j0kdzU0vBPAmnOv58Xho2U5WMdvTCi3quh9XAVa56fBV2gbe1YjCAYo8VAmwFJN4n6Wsd8vOI+anlLMgWrTQEel9sDR1Qj/E4Uh5wSDvXaSMFECCoQiH0S939SzHNx2xiNv0L/eQBnCcQTggL/V4/1jCUPyp8lX+FTdszodjmLRHKO5mDOTtBg7zq9oGAw31U5DiehRa2E62XuxdFB8PXaUMU04bXxmEN15AnkfR5iyEMyakJ1tWvrM1VemSyLCdr5GDw5X1lVDu6FmvqrMVVaPswZWHiVbUtlFiJcJgqvZ1CFmQQv0GfpW1j10mGF8xg/8CBRHS/Gt4fc1qNsz+NYAj6mSER+HtL5yeZr39sfRuVp/dI5tJo+l+asBeeT0Kap4ckCL2O7iLIhvyDUI10irfauoni6nD4PUmOWFdKOgnV30WQvPQCWzcUaQAaLsAU86+FCherDGCb3yfYjbUM7Z/2evSATmoKyxU8zpC339jN7TuEzVYiemjIO29rpy9yNRD1eSsHaRN7EHiZqXksxLAbTct9+eDDMoaIbcKTbeOizk2GM71KZE0qwaFdEA0ek21Obuk0Z63nTvP+VVMPRgRuazp1iS6HhLefEQ9foTROMizx72jXmYFU3ghgrKPzwQWmAt+W4tM4HwRah6hgCXe6BiL4EPlkqZXIfHpIoe+a1PxJXV2/5Ggyzm0ex8osKXaRygBw3YWDYlF8z7tALZR8JkCWHeP4Miy+O0x9uoQ7zVcCpLbFQ52LboyhsBOULmarXG5zwlb4QdV38dztT/Wy1F/TxQJHfil0MjzQz0GsxmRRl69rzI7bbvmh/7mZhZz9hRfm5j/m/4RUDPwkEhsZuz15n9GXQ7iqROEbtTIU0ZhAatxpC2kOoF5QmRrjB2KAH95oYDHtXCKYkwEUfaDrXYVyJ9Vv+zp9nahtsJrrwCgIC5mVoqU87JkyKJnhr5EehpWXfussZQZEggUHaxamcnCvzAQZMfcilK0vvE1JKOFbrmPop2u1eISkDtGC3cH7YZTYIBQ404hu1tl4QSF5izvUZvwiO11ZoKB6AX5sS+90OjX0fCm6iLFAyneYBAvRTJ4kDra+0mLwyBHrVfGv9839+BYGY2kFq8/BJuYUjR8gmZZ8fpi6M8Ubeom0b/JsxqvHX0RBqE2S7vAlbP6nupgbVRq0/XV91dqLE9vWGBsr5ZlBSz4ZzSslzlp0lOBiDgcvOjfGwTMnLYu87Nt6jyPYbMFdum5pgo+oJIel6HqKdgoKXhWpNWzPRppgNad6p/LETUj9Z1JmO8uWz7gtuLLSM+8yHclkA0utlnAnG9aRvtJaOJRWCW/9haFnkdaVTcTavoLNmZcHuwmWVnejePmqJlEPgsUL4dZmODT3/gqtexRhdunuetkkxJc+657GGOBxPoCSBXn+PI7YIrwvY/qeLoZqkC0jP5+vhMmXAanTAtVEyV/Y6Sp/KpEMuUD7TykS0uQXhdR/ty6E6GDBf9Axgz/60/qco3dp6XgWYM6zWDT08WWFw3f+wteMhJv0322UKgwkN37XM9jbmNFE1btwYJC9z4cSaUgcIVQoLyPwyY3LkIh3iKKou1C9wuPC/MX8L7Wk83Ase2c3OUpC5ZuNIaBR0rV9QDcN7EH28vzJV3dFKJa+JcGWcxvz6HCQrNvea59NmXmbG1LSJsEyOQn1d2ea7ayBIdbeuWM3SLVxJY+oz1FxedFSk5T+P+illVeZfYBKqiB/fRMG4gANvc/xe/2ww7bIfbnpwhfdc5WR92xvF6eWlVoJOv9G28cV9IvKclquEd7aiDoOnv4lHCPPnbJwqamD2LLKP9gzZjvyETC8MUwfTCX261KEriuCtSHVxp6IkxWXNvuvFPp2vHUShyz0sbkdzzrcxwFY1keqU84QPhPF+lEWS7i7WCQGfPTP3s3DsG2OgOC78oEC1rDs780WuA3scxUInzKD/aIoTZXn79zvGlIrCVHt+93rRRugKqIBhzUvEqdbRp0DvQ51X71QAR3nBWT8c5wXq+gY8zPbEt9sgfJ4evacR/FktuMIwX0BbDA3xpFfaUaGBAtxyZ+CDMXr9HbnKYZiPJqk0ZJVyCHSS1h3IK/OZThrUm/FvS4CCxfmHx09MfOLbBBMRJd+uKV03y+kgKdZkqLYhsakSzt3IwfqVJ9tKdghinHQJsELkrThRQCijxnqNyiYmYvozVwnU/h0PG3GDuNkDHItrGqgyILMCYK1NQNrLl91gT7i73zqa0CMm8UWRCWKhPQy0dbimiugstlp29r1duIr63hDsXnefI920yY+umnpqH1/JYQKrC6udJ3RpUxy9HC58JOz6f+49Rcm+/6zuFs6J6ePx0cWzLT3NbbLjV2xz7WZCWJyRA0hOr8OQgoPcvkVf5QpikulLSE+PosrLl/pkXrFln4ZJjT27EFqXKKbo0ZufU7WpK1cU42x9tu2fPrqt9zI9hqf1iffSPoxCs3L/FCEvJzg7KzAn3Txyb9R9/ZPCA51EbwfbQ3FDfPy3kBDvcwLKTdDdUGG26qLfzf9UwfYkua/FH063QOfkofShNL3exM3duMdA7g++D159hEqTQmZ3RiYut55/xUjPfvVfuJkiTO5FhY4kkIhX/1PYrYvHCJjjMbXllITMiEdj2BhJEkWPNyt+PZ9hfMZq10IZ6B/qhe3ufa4lZi76p/ibUuaDEk9FT0FSPer/6++v9SwrY9r7YP/xVbv4jx/wpFZgSUTwz4sesqPL5mmSAfEcc/EOL3bRZDtkc3FP/1v3it9PvVLzdw2D+fLr3WsBcYvJY89dpFKYFh75wdjkgYtCMh1bIm7+TlElUfRYPC/ddwkTjZVWdfKmOC3OSHyRs2y8SemdcegIMSL0V8L1rRhk0GfwUWHHQDyzcKJX+Tk2MvJvazo/2nRXEooGv/3yTQ4F2eExdwo+Cc8sSVv11CCr6upZFOQyly0CvUIDqas+wOSheNOeoE6KOifd/1F9RZF1kF/XNcMGyDedfXvgRHAYa/ouGkiycL59iF1g2nRKX0+zRIL1nYEtIvrI04Rtkrq1BtxP4d2PKvvF6vBdjyDPdh2ysfol212qCTLr8nxWmkAGEaX7ykTJTKDv+b6CVLY7W/lcz6JF2JJEBo+umgcIHVhSEaEacdb59h6yux+c2EjHd8hTEWPuBIAxifoFe0zOwO6AvR/OytYHjbsSd0bp9jRFUsM6VGgBuKvAdnZ/KQ6T4RxkXKGNHHYA/4HFmRALIbSstSdgfvma+l6DGj0WaCCb2Aw8R2CnZd3FZt+ZaazbYrAKEZL/3HKmf+DrTeSyfRhtx09h1B/9Uy97VKyb+vLbcauqFsT8DboL/HRuLNtQid2dWQCRewaqgp5xyY5HYV0bybLLzG4X9QxPmSBfL61G8d3a/YFuXOzhAdJre3399T40ndjopF17Fwri6Tj4L9gG1Dtq/7OpXkOcO/TsEa8hVOHu+b7R+lvKfBMXH32RLz0LmoSbNYtdfu/trc0+8XPmWFb//pm8jfTWHDDa9uzhTxJez+bmLDr1eprWnR64K2rN1mvk/fuV6SKySOhujXYh5idZYhS2i/5YlwaLzeLf/2UtIV04KFXTfQoBnLYmIJZTkkxbD0lXV40OJT0Ur/xPMw/cefSnexPuPtgWBkmcnYWNap/grB85N5aoN2u4W+hkxyuSHTLp1aXsHcZK/v43e3xT8s8qHf8tpLcUpTcpbtIYWZdQT/eCv1qX0Bm6EwzGCUHV5cFlUzb+/bRbQssj/tqlSI4I1Otm0aJ4UCIe5B6U8YQBMfnN7Usd6AGjl3ez4qbT+wsis1plABMgF/ezdpPstWvObQybqju/TxWafw6h9QuG+vss6dUZUBwGqBWQu7yHAemzKr7KEw9M5HOBPJ+ljlGP0+33K/D1vUB+kfyWt76ED9WP8XtHEQG94+4r7HwIWowrZ8Q7imrRGlWn8al8xwmWoaT3XyK7fItTAvCa6qzgv59RtOjN66+Ixy4NQ7RBKqY9WHNRPvkByy+Euxa2sx+dzQ86cftKeEY3wi4xQjLE1/aJMC9QLntkfbOcS3+djNegFvDUmTfjQWDDAiFyf0OEcYIyCJn0JROpE4wITNit4+Xg+WaUCuiJwO0u4CiGMxjJKecY1jcboVu4xcnin0vEiR2sl4s+NQPkbsc13jvO0kr8l+IvlzZksbC6yNdvTMqMvHl9z004Fa4I//HXXKUzjCnrwwH2owLb2v86EBTCnMfMBEd4dUkLT+fhm+KlYD9vsUqCu37yZZL78gegrxWQIMWMuid/WeciV1LbnEy1JQxvmWOTraLg9dyucmyPQZoW+sLfZ36ucJOUHj9O1VhmIAM380HqyTlypXdhNl/VmytFneEOXryuOBGxCThwtmGZH3Cbc8gd/IGaD+fRJf0kjxzimvKhr6tyKzjS7kf5ZqZEaN162Tyd31ICXWaG768wdlNOvc8qEQvuySMKV49+czexOb/fBcKFqXl6uUssp+KD9WFTF8VsmtvkvclfIVZ6zPCOtf5pX/PPKVcF4GXsfhXiaLAZ29dRHUvzgj+XqKhMN46+JTeRe67KnHX5I5rG038wImGo+7Kg7fyfzRpmuQsrrKA4XzJ3a81Mt1rwoD8pomyidHVLQB2wOjOVQE5D7NgDZB7yxz2u/E9GXK97UFjWwAkQlWoPzM57GTYaGghBsqGclavOJ1eGzXtMD1StOOU2FgPiZ544LdOHBfC3OsSHF7Ccj+msa2mkq2x77G3sCI/6jdDxPBJ43ODAIofVUHPMEm87ZUKef9QOLbAkyzvnSpnqalt6EHfsfTdXAZC7yLH+FP+/zHqXb7QOp99Jmm31H/6huCsB4YYoDAu5opnltvj2HYDmxQTPRX9shMx3Pt42dO2id9mUoNGSZpdejFR85NuHQcIGIaATIZ+w7KjRojVP3y0DLjYhlRaT8LFqmPSSY2Dw6/XPb8wWpuPYJachHxsVB7cyt+KyroAhj3ApehxjWHczQj6aKkJE3f275OW6d3E5w4NBfSLvm13p9SJwchU423XYlUjMAABAQAAAAAAMAABMAAC4AsNnOxgwbqtqqqlSNqmqqoYOqO1RUNaY2VaNVQ8MONQx6UIGqmRmrqoA7AAAHGAMWLI3EAzBZmBzwSmCVxBXhdfA6S57aAQfQwKOkevUBA3Aa6/uBoJX2PxC5yXZ2GIgNcvXbgQNs8tbuAYA4lfXqAQKQqq2ICWIBIRYI6QAAAAAAANEAMwT/7/dZu8JTmmTNlpaLsT9Fu8Ri6qG6ExoQ3DAzRTcmUc1OlkN0EnodrRFZviZ2Z8tI7q9bKlIeFQG1nC+T5lvKqEKs92CdqNRwY41oLKeDZ9FfariLPRmTPONR73eBeuIIbdO0o6uUG1YOIo7KSFL3mqhp6EptNYzofcpOh/LqnikPGLFJlVFsk2cWYovE5NMl93zBkitx/3PE5ItDN/m7QpkrJ/l8LZ6kUz0Qv+GJFgyjNRB8hlivVNLwWml7Kg8HztiHbSjuOq4DPGoYO8pUNXMj74O5PSBpMfpe5rmRNwHplz9YwFIfntnxmgBTAwARwE+QGdQDtPZ8yJmkMsoFwyOx068q6qTjcXkSlmdbBx1v0hE0bZeP8d8bz5ks
*/
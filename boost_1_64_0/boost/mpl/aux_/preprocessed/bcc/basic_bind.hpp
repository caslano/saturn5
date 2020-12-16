
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "basic_bind.hpp" header
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
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;

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
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;

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
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;

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
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;

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
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;

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
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;
        typedef aux::resolve_bind_arg< T5,U1,U2,U3,U4,U5 > t5;

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


/* basic_bind.hpp
92zr7lq/vtDJpVN21sj7jJnDu+lcXV1v3zjUt2jV7OYLZy/29NJ5eZXsnBMyw5Y4tLy8VF9gGzEwOiq2wZpV81tdvXSoq1/n+t0KCwt12zYs63Xx3OmOxRtmdQoM1AWGhjTov23jchx+UL+fd7N6LYXOrp3DAj3CblceDN28aUH36IiYegnhCV6Fs2a5XLt0tMfcwrnua1YvaB0aVK9v2YHjjU7sP9VkcKDXYOuUiCB9M5dmBw8cabBw1qKGjikxfe/cOj7owtljbe9UloWtKZrrPW50fJvC2bNdD5YedL976/SwuIj4hmFBDQcYs2K7l5aW6k4cON30/LkjrXeXLAzzcmvadOns5U3CIyNdhS5uXYpWzmpmzkgIuHDueLvNxXP9QgPdQytv7AuKC4/zKN2/39WcldRncFDjIQGdGvcKx+u/PTuWDx0c3GTonpKlg0v37XPZsnFxz907Fg9MiExskjY6pmVYSKNBF8tP+GZnxPnPsCcNW1+01PdCeZlPXOQIz7SU4a0c9tj+xcWFwvVLJ3tFRw6vv2v7vL7+XRrdZzTEdL1z89jAiisHuuzevmhAyfZZQetXr+g4ISWxw50bRwdcvXy4W8mO2fjCkEvQtcvHepoNo3pNSE3qeLXioF9lZWngiX0nGy8sXOjh3bx+q7Bgz4HjkuN8zpcf9M7IjOzs36lhD3e3Bg0CQ9xCrlWU+fu0aNTO3aVevYIp8QOKigr12Zkjevp39uy5dtXitqiiMDi5huwGQLU3o+hOQGUuQgVKUHy7oebbYCIZyGoaquQgTD0aRWSG+mTDDMdB9UsRZQaiCkTWdiFqf2S3GBBQgWrfDEgpR5EXoUr1UD13mKovinIP1CQUKhkH1b2ObCxElZhh/lsAGd6o1oPIljdU5zaqpBSqEw1TqQBEnQdMsOoZjCpdCnNfC/jxR1UkAC5uo5oGA242o/juwIy9oJ4XURUXUNz+UHUjVLkAJuYHUwtAlVcCEqxQi3AU23mYbjhUpxQwYoUaGQF/22CGC2Gmt6Hq26DyhTBlX8BeGSAlAGqwBaoTChgrBzR5AMquQ62vAS4nQEXXAC59oK53AFlpMIttgAIPmOdBQJ8eVXcC8DMX1b4b6nsXcDEDqlWKqg6EKd6GGS5EFWVDJUoAVeWAVgHqfB6mqoNZCYAQd6hbNkzFimp2hypfAPSuB8ysBRxlQGX3QH2uwkzGAUovArKTUe1FUNOLqPK1gLpiQMsWmHc5zLEQJuIFE48GPPhAHSsAudcBX0sBLXtg9msA2wWA3QmAImbuxYD9DJiSADhKAMyXASqZ2q+HGoYBPrwANwEwkd2ALTNUej3gcxzguBIQUwSYqoS5xgFKCwDTJwAV3jDvO2gGrDB1B0xoBiAhFDCuR5OhA4QZofpmwO9BNAcOQO55QO0umMQ1BoGATgdg1QdwdxfmGg5o1rMmCM3DHqi8O0zsDpoJHUymEirvD/OagCZvC0wzDc1aOJq+uYBLb0DNQjQNawG/JYC5q4CDOJhLASBqDZq7u2j6fAE5hYBOAc3VUpiUD8xxAszbgSYzDaZagmbTF02mH5oNce4W5h4Ns78O0xyHZiEZzcs1wOoMQNkFND1lgP67gM5ANG9rAAdGwN9gND27YOJX0UzuBszPQDPgheYpGfAWBuj1Q/MYCOici2YgG01CEWA3FM3bVTSDfoCzzYDSMjQvyWgaPNAUzEUTeAGwm4CmrxDN8FLA7AlAVhjgKQ5N2y4UxQYUwSyY1lmY6jlkJRnZaAb1L0ZWOkGdR6OYoqDOehRBc6jSaBRHJcxgP9QgC+YnABLCoaICU0EUfQVM/zLUohSm3ALmuAHRzkFVukGN7Mg=
*/
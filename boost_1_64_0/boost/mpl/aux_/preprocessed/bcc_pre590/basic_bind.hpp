
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
2k/20rCJRVXj/BX1Au9t49ocpr1VXGxF0xyflZrhrwXuY+DyUFLhtx+ZuAfD7b4qhklgmRx1mGsxxq3jTWk8t4+q10bSMcat4nyik/BLP1WPUapg/a2KKWvw9lP1yhq8/VU953K2NMebYU86wIUb+5EcaHNk0wXOQTansSaT1fquB9ucZHyOzulvc+TQDOL1EJPjn6GLfHaohcszwQ9zYajygj2knRxUd6jvjnBzpBEffj3SxRM1NeM/deLyHPkBJo5tY3y/DjRxNdrhxiCdgy8saZscbOJ6sjBniMqxFhJgXNziwMCLdBmq4nxeNx+YyPl3mIbJucLDVb04VJr1I1S9sufB0apeWavxM12PXq0I20gV45rYzrvH2Bw1ksT4tspxfQH749smD2nKc5eQZqNMjkwzxvMNXMY11gWrOKeVSIMCS89dLn6mUMdS/ty7Ik2PBTtI0zEqZpxZOtbH5IYXwZ7I42zM2f8oDuehQGKs2uYF/YoJNiZqSLyjxMY595rjcRPdPJEo4JS6OWjahV/LHJwEsHIbC/YmmeTAMg5/Vrh4hj8r3Rz4U+SHKp8j23jWV0u91oZPDvQlZWUTqssphfDNjz2bHXg99d7jzVweOYxTbA5KBxollI+pDl4mJ/tPJxg4DNiMnWhgvIEHsGkWJvsgJxmY2OIglmjGsycbOI8cAYsamNp3OcXEMtNzWe8gTeTPGh8XX9W0N2XFVL2wCF6tk6cWFsGrc/LUzrrwV8zBU8fk4w5c/datd+BBgQGnIYSj9oWnuzjYRyPhwNS4PdWBi10UMR7txHU/Nro58KPwR5PG4Q4kr+zy35MMwdX5A6kQDhKPOekQDhKOy+dMjcMdUvZjs6ZHh1Q8zvGcMXB0PNnNrIHl4GZO0wvH0L3h52ZpuPxOmK3p8RmHdR9zLEyPy7kWLsYZ1bg8LZQj4/J0m5OVvUGMN7s5cEaE8QydE5xRe6atj6YahV3vLA2T31zzVb2ydmWBrk8l47RiNy6ws3UMtiSBnWNjXheT43mhG6N+EdYO6zjleIwdB3qKgiJ9jev5BsYpywqsIw7DuQMh3LjAwVH34/+5iSdic8z6/0KDwzGJsZTFBhYcbKw6gnddFMYVfVHmXGxw0EVCMcD+0D6HN36TbekSTS/b0ksDPbb1Ki0rLFLXHku8enTgIsahDYwNzcCWWpg8v/4KFyZWObFfrzRxjFdcZejV+X7LDIxzEd73CweG9/GzVyt4RXlZJVd3ePYaEwus91h7bOIcGPHsdU5M7ldyvRvPMAHvv8HmYMZDjN1YHoLDFXbjRidHfhve5MJ5xg7Gpp04jQVmRLrcYuFy7+RbGcNJLoYN5zYbC/oxt1uYrKNWqJjcrZHj4w43ptW1d7o52vz9lW4Omj/BWWVwtAEE9KnuaoGDoRJ2626VB9sPtpkI1qHco3LQrIqQYz2zihv2nHslhhUVWM+s6qXfgnGh+1VcsfesUfUowLla8inC84CF2/aVB3UOL4BvqkkE3xcPmbhaiBHmh00OR4h4/hELU7MC9ni2OTIrgPOok4MChHR+zOKocSnXsD0ezmMOj22bHERtsPezits2EuY8aXHQ4ERlvfCUzrG+7Z9WccVW8mtVr9hEnlH1ShvyrKqXXQPGnnNg9WkRp89rWMYRpxgb13lWfL1g4XZc/EbnWHHxooordo51uh52DoH9VsOyOE1LYC+pGOwZwXh4gMHeqNmRhX/XuziK/fF3Fq7ahbG22+YE7dqrJsZlX6TLBhMzbbXo/7zm4gl7eR3v9FAobVqvO7n4Fi/NNdWiz/6GxUMZgjsb3bjsbYP3ZigPRR9heMvm2TZYxPnvQ7hoa8VZ0W4ObLE=
*/
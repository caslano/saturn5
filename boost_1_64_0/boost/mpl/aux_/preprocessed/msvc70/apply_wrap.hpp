
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

{
    typedef typename F::template apply<
        
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap0<int>
{
    typedef int type;
};

template<
      typename F, typename T1

    >
struct apply_wrap1

{
    typedef typename F::template apply<
         T1
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

{
    typedef typename F::template apply<
         T1, T2
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

{
    typedef typename F::template apply<
         T1, T2, T3
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

{
    typedef typename F::template apply<
         T1, T2, T3, T4
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

{
    typedef typename F::template apply<
         T1, T2, T3, T4, T5
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply_wrap.hpp
u2dduAL6/MUn6y1UYYu7cOeUCX00zWjbVQ77Ij0ILA201pNdsSUoRQr5mQGx1FSZsKAId01HhnUj8cJSTt/czUNs9q8fXQo1WFCCHeWzmqBLVxd865HPopz53CQLWveDxBnk+3X817cUjXIlE7L9UNAJWtsbdwJ/dSOo3M/bY64+qgm4yVcrX3NprMxJKNf0bkDBm+8g+YNWq+T379tpU9gxVRl4484YQL6QIstWnI0KMsEKTW9St8wX8t74FD7bdUOPGW5TShmjlJzQXPpiN61wG/VU4XcxAa6ulUae0w6187Sox+sEzDdUtIHq/DtjFmLE8jAQBodt4kYundJqv/72/ZcFAvJ+GIOiK4EGAlXM0dTbEkUu5BdxsSmsk3TBDGYSHeKL6Tv5Bxs0z16tjdzMvVv1SEK/rgm8CFrJZki1JdAgZ4PAO671bjGGGS+B4Q2c93OySd0dGs+roT7D0UvtRmXoWXSupIBc2mfh30fQGwZJ6HhtYEQxDKn07HXW1jiD7R8oPXQ5ItuUxURR+GcjZkP0m0mqpRDZg62/pC84yyphyWv4+RO5fQ==
*/
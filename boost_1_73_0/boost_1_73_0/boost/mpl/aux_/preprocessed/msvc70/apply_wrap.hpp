
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
WCI8ogU7R8hwxithQeTGgqpsWVmYc515qcowg1zWUU4eJXIqwNQcLMy45ekc0ycoKPRj0+KzbUbMKssFtFss08tn7bkOAGfQO4N1201c6wZtGKUW2m0IOv3WCRz9L+4PYPsN4A1fuQAIej0C3uL3hHna23SKCaC1DQ/gZet04WslIDjZYCfDwcXNkAlHXPe3wHAKF5iSnBrcgym9Wy+CymifpqTee6n+9STbY7tdSnJKn2+xPveW/l/nbvdIfr91TPWwlELx7GhuC/F+9lu1gE6rZu8C2vSv7K/qJmRw3O90oKymv3N233tiel9U8rvic/W/KfTaAeciR2k3DkjrBYXMkNtKI7kljq8JsV+H63KO2MyWhp5slxBKXmBtvhiyXK8N4hwIlUSZ6lVpyR9OB8X662AIU1UUXGYR857A8yinZ4wgL0mrlQDH0ff9w8tRnFyN+4cu+Xg0SXwi3iFpupFdH+gedT5b1UTAZxb1zpDkUwNTJG83zVzZJgsXdSylKLWyKlUiYnfxcAJcKrkqVGUa7g6JnY5P+MyLUuAR8dLu5/gntGicjBI4p/HhosGG4/i+wZIf4yEMGvW902Df7q7oP/T3BKG/Y/X3t9gvUEsDBAoAAAAIAC1nSlIoC50/bQEAAHkCAAAeAAkA
*/
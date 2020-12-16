
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl;

template< int N >
struct fold_chunk;

template<> struct fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef state0 state;
        typedef iter0 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef state1 state;
        typedef iter1 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef state2 state;
        typedef iter2 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef state3 state;
        typedef iter3 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, state3, typename deref<iter3>::type >::type state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef state4 state;
        typedef iter4 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template< int N >
struct fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef fold_impl<
              4
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , typename chunk_::iterator
            , Last
            , typename chunk_::state
            , ForwardOp
            > res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_step;

template<
      typename Last
    , typename State
    >
struct fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , fold_null_step< Last,State >
            , fold_step< First,Last,State,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_step
{
    typedef fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
    : fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* fold_impl.hpp
KBc7YR6GYz7GoxGn4RwsxgK8GQtxNRZhORbjUzgXn8N5uB9L8CjOx/fxZjyDC/A8lmILjseF2A6X4FBciiNxOSbiCrwBV+LNuApvwVvxTlyNlViOO3Ed7sb1+ARW4Ct4G36Jt+MZvAPrcRMql6/b0Bu3Y3u8C/3xbuyP92Me7sCb8QEsxZ24CndhBe7GTfgobsEq/CM+gW/iHvwQn8SPcC9+hc9hHT6P3+EL2I7j6UUMwJewK76MffEADsVXcDi+irFs10b6C5U+Rd183v9/tP9Q/b0DzvsRDb2YdgkX6/dl9EEf9OGXD7/K9T9XpBfi+l95/j9eeWY2UrneNz1qVlTAc1Ophfl5pue2+HyK8vkY9eczi/PSzde7yv2DD+T+gbp9wDiCB2EsYTQV6lVrTdfh46dMSc7JT81IliWRl6afu5RrQJ63cHat537fBxeqb3Z3r620r02cX0vebrpWuvOxtGXDCt7c6rfqI8OXK+MrnF8zmusPpbxlO9QR1PWHVXKN8wR2xT04AJ/EUbgXx+IzGMJCDvakLoPgrN91fjf9Jm0kf0/tIz2D9d8N+qAP+qAP+qAP+qAP+qAP/4/Dr3L9n5FpLLhA/f8fV7Xvr5Lr99PyTO8pwrRgpdJDo/5f2io6Xrw71qHHrHVo76pRZ+6NPQiWOnM/qUdPIO301JyctNT02eo2nx6eTE9LpimfRtt9qQ9X17fXMS719nb16dQbuVTH7O67936rOmbt+wLO6p7/d+uYD5rum+R7/uGuR7a8vv6tE3/aVrv1urud1SW7f9+nsTrm/QTz8cK41DH74h6CQZ6Hb43d0BeDsAt2x17YE4dhMI7CvpiA/TAd++M8HIDzcSAuwFBcj2H4B7wcn8ZwPIBD8BBG4FEcjjU4Ak/iSDyFozDiF9ap6e/i+33Vo/3adWgh+n0wfdAHfdAHfdAHffg/HH6V6//0AmPRBbr+/5icSp9a9CXg0BeO9CeVssJ6/c9le9N19o31E7dY0hgjaUQShgUzXZVGTnae6cX9+TNnupyWXN/bpRUo/d/Nl/sZxYRE0qrWSivPlb51vNpdsdJpmwBrv0PybL/dvQn68rLrw6ZM8jZI8tZPytq40pI36T7HjT5/1OVtfSZDo18+P+arsqZjet0Jt3S4q2TazZpu06G+jzMzJzNPfR/nsw5MK8jPNaj6ogryZN586YvKoQ1FgCzHmJqhbAdTO4/qlfKOeYf+zgI9tdelpuG6ZOb9TtbFsEp7XU44WZe2q2zrUszemW7ZLC70o/SfXpdQJ+uyx0t7XaIc14XN8ntZlxQn67LjIukHpjnHJfrj9GDirlL3x1VstJ45DAaX7oNOWt10WyLlvEEbJU4d2u2E6hhf2FP6BVTfx5T2OnvZDpXkfy7jO28lPVS3D8qTc4O6H8UW0qdfkGy7rnIeClpjW9/smzOb3F6a5yBpn1UvadTJue4kIYk04sxpmFu0FVn3kRKji2U6oLxhmd5FeWWgnIsZV/XPJ+Nz0LKfOJQv5STlq9Hu6rxlPMyh3VWo+j6y8/vC2vcNL9z94gvVH5i793N/q36/LlT/Xu7e//3edH/ZO/77eWfe8XzVWLqx9sic05UXvh+vlBW2/k5qHN590kGe4/PB9uiLluf/Fku8MRJP/fzfCIk3UuKNwkCMxH44GiNxjCyvhFAty5svy/PGHFneFXI/exz64HjsglfiZRiDY3AixuBVeBXG4vU4CWfjNViAcVhs9w4f+U2EgzTKYYikP1TyP0wVr0ri9dGI11fKoR/2wv6qeDVO46HE64UE9TuY+O52Hi9U4g2WeGGqeFGNxOsq8bpJvCA8Lc/aGiUe31XEM8ePRmUwSrk=
*/
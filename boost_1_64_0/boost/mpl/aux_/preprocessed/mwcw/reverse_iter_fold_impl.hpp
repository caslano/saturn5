
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef fwd_state0 bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter4 iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_iter_fold_impl.hpp
joB9dH/tA2fDvrAM9oeXw2Tlenn3H+d4dKlDHLospXNM4tAZM+IixaJbHYN2jj83HXtea8Wc+Y+QimQgbnGLW9ziFress/h/cuvj//ac/d7+ef6M+zWY3k7nM+zzyUl6qd4PUNyd3xxN+AF8p5l+gKbnCpvz4sscbJYE2aRWUcxB9tvV2DBRfoW9ZLeXPTc7MDZUM6Ow2xofAvOHg+q1VPVKUr36aMxa57PrFRiqtrhezZlz3dZ5BMKPPd38Aut6/siJ46zztZMumHfZW2f8+ceju48pz87xtP+8kkAe1NMaxua1IWPzAzVf9yDo1bp7W68kgt6h0jtMeoOM+cFJ0ttLeub84JHSGwUTYRrspTG89PV9xE4Y/SOlP0R6R8E+cCgs6hjdPJo5POkqPN7o5wxHyBXAuG29zhfgkCvAzRPQijwBVdw7Nch3iLeDO051i1vc4ha3uCWWJSbj/35tN/4fX2eN8zFZv/w/cL48cJ4V2fslB84vC5xnxa3x/jWB86xw5vyOOt/7R//5fun7JYesO5efQa8zotfrDb6Gmcacg0UOfoHqQsMvYFuJYgwftB+Uw1r8miDbtKAZtvvJ9ngH27XBtjEcnV27zlUOdutMu/rwolmvrTorh0B42x5fwLY+6ObZzXWw2y3ILjdWlHbt9eGdFLx/THaXyLdTl+e3q/6NrX/Hrlut6vah1q6/p7rV5qtu+oxUu3Zfu+6U78CL/grkIo53K4i8Rr2P2lasnAFzrfcilyDWfJUko9+ZptJofkWnSG3yeFo0L8Xs82TlC7hMfX6x+txT/93QvRu7HBPR5GGw57AkaCnr9trjpSt8hetWnxKo++ScIrZTK+ibbvVNemYBiRmm+9vQ06x5tPOAjP5O3Vz9bewzuYU+e81xCtk/VXNxkB7G/pb4GtlMtmiqJ2TOE9UM8n1Wqa2H6XubKt9n7cl2W2Pr+7TnYfXUzTBc9RqKbNyDz8YXqFd+5uSTs9KLCtPzc4pyo3m+2vVT/wVdb5GuN1b36zHIi7SjxLgel+Fy9ddtbp7ZHKf9YXX9io20d6+u/5O+LwtydX3rmRzD74v1PFqMgTzqVcy5h3Mj5NfQe+fz3jGcH3Cy87PL/J6N2bi+wllqczpifc9SG75nU52+Z12ibXuE79bqkO/WWqf9F939D/+T/veLx/n97MO6luT2eG9Q54kfjlv9dL/P131+3+pC5/y+o+TnToNe+cdtvZoIekOlN0x6ww292gh6vaS3q/R6GXp1LdTz+Fqm160Feqke/QaFj5n7WoXRK9CxT8dLguzo9yL80MFOV+m9ruPlOn7PsFOMJKk+c8Ps+3iz9te6RXP1boVHwtvgSHgHzIR3wlx4t+p9j+ae3au5jffBi+AS5Ul5zOx/fW6Xmf0Yph0XG/Wu9Oj3D9xe+aO78/dC6VlzIbeGZ2iO3Ey4GyzRPnhnw4PhOfBUeK7qOQdeCs9TXunz4c3wArgIlsK74YXq14vUrxfDlbAMdqYul8CN4WWwKywPxI30WwYeFmZ/wmP1+R+nOX3jYCo8Xvq5SILuu+HS3xiOD7O/4UYwH/r/p8BtYCHcGfrgnvA02B9OhUNgERwKpxvXK9H1xja6HtTnky67GbKbKbsT4QCYBQ+D2bpODhwNJ2vOJ9fRfa3fGPDXJu7rS3V8hY5/0jGk3/R/G2bJjp4z/nKF7FwJt4RXw+3gfMXrroEp8Fo4Ht4A0+GNkHE29ryeWmQN0q2j19MTGdLRG1Vcry3ieetbLG9lSmc3ntdEPG9NSudWx/RyucdKkUXIMqQWWYtss4HXk4KMQ3xIOVKFLEdWI1uywXlyJzcG6Ba3uMUtbnGLW9ziFre0d4k=
*/

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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 2,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 3,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 4,First,Last,State,ForwardOp >
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

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,First,Last,State,ForwardOp >
    : fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* fold_impl.hpp
DXwNvgePw0/h6/Ar+Ab8Fv4CXibz7PrAGjgE/gqOhr+WelZskjE1cKPkcwDMkXTHyvN7KuwJp8G+MA6GwXg4Ac6A18CZcCGcDbPgXHgDnAdvgvPhemh21nMZAwMjDer5byXf34JB8HdwJKyDjnpnlfDDDOrdfgn/E9gZPijpeEjSUQnD4cPa+1X0BRrUf6Y4oQ/9sCu8Bjqffy2EGy/hrpJwE6DD/noJN9zA/hoJ9yvYGf4aBsHfwH6wFg6Fv9XoCxziXd8zou+Q6HtW9D0n+p4XfYc1+mJb0PeK6Dsm+l4VfT8Tfa+JvuPQWV4t6HtY9D0i+h4VfQdE32Oi7yB0ltcQ7/l+pegbLfkepbHjWAt2zJNw88UOs9ixQOxYKHYs0uhrakHfNNEXJ/qmi7540TdD9M3U6AsN967vOtGXLPpWiL6Vos8i+lI0+swt6LtT9N0l+raIvnLRt1X0bdPoK21BX7boWyP61oq+HNGXK/ryNPqqW9B3s+grEX23iL5bRd960Veqva9a0Hev6Nsl+naLvj2ib6/o2yf6kkzS7wpnib5OMMHx91Sekz+G4fAeOBLeC6+Eu+FVcA+cCvfC6XCfdk3kod7/7h6Uv3ePwwBYpX0/bCFcpYR7WMI9AuW5S5+k9/eL4ZI/ETAAjoBquyx0hK9tIXwPCd9TwgdJ+F6a8E0thA+R8AMk/EAJP0gTPnCY9/A/kPAdJXwnCd8ZSr7R3+U93+6TfLtf8u0BTb6ZW4j3RQl3VMK9BHvBlzXhrS2Ef1rCPyPhD0n4ZzXhK1oI/7qEf0PCn5Dwv9CWewvhP5fwf5PwTRL+C+gs9xbCvyXhfyfh6yT829BZ7i2E/0jCfyzhGyT8J9BZ7sO9h/+nhP9Gwp+T8P+CznKX8KEG5X6NSf6+w4Fy/KV826ZIuF3yfjjU/v2uukVy/y+BPeFSGAaT4Ai4DEbDZDgNroAJ0AIXwhS4CqbCm+AquAGmw40wA+6AOXAXzIVPQCs8Cgvgz2AhfB/aYANcB8/CYvhveBPsgs0lMAzeAofB9XA0LOXfBLgBToG3wdlwIzTDMpgMb4cZ8A5YDDfDDfBOuBXeBX8Et8GdcLvzOSdt+rCXQf5PlPy/WvJxEnR+f0m4K7yU2+UwRvL7Gu2a5pr4jpn0a3LP0lxXL9d1b/E63Ejf9IWO9E1f7Hn0NV7q25rhpypZexoJfrijKRoxIzlIxV7WlP6qgym5rKOp7A6O8atGQjcwX595/OXIAcQxt//4Btf8/nBehE4qx0jcPNd8f1sTYW9j3j3imPt/gN8589CHHPohAmsUwb8R1uIXMJ84YCSMRZo5F7iRefxIM/4p+GXxuxgpmY8u6L6meSX+1RuxE+Zw3KBcCxs5DjJzfRnz8pFYJB2ZiF8lPIYkmdEtaw/sg034Hdre3nQCqcavCr86GLzJvi5BOFKjXN9EPLAU/2j8DsAapAMvhInKdbBBCXM7cco66gn4lcMg/CphNDzmtr5B4u3ECU2TyX9YQzyBkzmHfz3HZ5EAGtwbsc+x9noN5xJhAzyHFE8mjjvQUdGeNRKIh98xcJeih9/J/LYhlfw+jpzAfxfHjfzusNm1dnvEZtf67VmbsYtrapFkjpthMQxexHmknN8psJLrjiJnm/iNXyO/w7GjTDmHdLiTOOFpJCDRvv57DOdjFH9+J8FI/K2wnuOd0GhN+KP4l8CEROKGKbAMsa8RDxO5BiovsLFIElIXS3z4n0BKOW7i+DAMmEJav8Am/GuU48XkI4yCNiUPOZ9osFaErDmvrhkRtITrkcgtxKX4yxoSZfyugIeQOmQm8Zi3yPr0sr5EwFL9OvX7trjWmji8xb5mfSMMLCc=
*/
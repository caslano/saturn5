
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
lnr0FzgZfgKnwiqYC4/AfPgZLIJ/hdfBz6V+fQFlbZy8y5f6UGNt3FYpl21SLnfC9nA77A93wCHwPjga7oQpcBe8Eu6GBfBBKa+H4WL4CFwCHxW/ZAfIe3eYI3acA0mLC3+LX24Wv2yA7eCtsBe8HY6EG+E02ct7OrwDzoRbYRbcpqxVqxR9u0WfulatneS7veQ7QvJ9HoyGHeAAGCn5j4KJMBpOhOfDHNgRLoKdYDG8EJbCzvBmeBHcBLvBe2F3uBP2EL/wt7zjpozFzhC4RdlTvAW8W/xyj9SXe2Es3CHt6E44Hu6S9uZ+OAs+ABfB3fBG+CC8CT4EN8JH4Db4KHwKPgYPwifgIfgk/FjZW/xYgLznhtPlPtfK6bDYO0H8OlH8mix+nQQvhlPEr1Ph5XAaHA+nw0yYAovgDPFrKlwL0+AdMB2WwQz4MsyE78Ms+CPMhi2xKwdGwqtgNMyFfWCetAP5cBC0wARYAJNhIZwCrdC5B3ueaw/21TX2on6bcNrnd2AH+K4Sr6KWeK9KvNck3n6JV4FUS7yeJr9DPcW/vcS/vcW/fcS//eE4OACmwoHi10Hwengp3AYHwxdhPDwEL4N/gwnw73AY/BUOl/Z0BGwBR8IQeDlsC8fAi+BY2B2Oc97v8i4Vzja535dKvS6Rer0MdoPL5X5fARPgSjgMXif3/WqYBtfCDHi91MuNSLXo2yT6guA60fec6Hte9L0g99GLMBq+BAfAl6X93QcT4StwItwPZ8PXYQ78I7wGHoBL4RvS/r4Fb4aV8Fb4trM9kveScJtJe3SWlGtDKddAKddGMBqeLfdNY2mPmsBE2FTao2YwHTaHs2ELuBC2lPsoCK6HwdI+tYK3w9ZwMwyD4kd5t0ibauLH4+LHr8SPX4sfT4gfq8WP34gfvxU//kP8+D2cA/8J8+APcBk8CVfAn+BaeAreBn+Gm+Avyt7wiQXu76sDcl8dlPvqDfithC2ReMGIpcbe8JHKHvJlEq61h3AVXoarUvSW1Qh3SgkXUCjp1RoO8TJcnIQ7xyRcuhIu0ZCeeTiLF+GykVIJt8Lkvn9S6vke2BE+BS+CT0u9fgZOgM/CWfA5OB8+L/X4JbgUvgzta9rlHQPsJ/rUNe358hwyF3aAFtgHzoOO+KW1xM+W+DkS/yqJPwf2bhTgcZ05a9F1a4V2nsZ6od/DOvP+id6tK/pvrTU/1Lvhb269eXhS/aw5d6xZOkYeq4a41i41/x9Yc759daB/3flprjtPGxvoXHuezEYZxcgWpAKpQgKfow1CpiIlyE7kXeSk9v3zgQEjkVykFNmLVCFNXmCfA2QMYkU2InuRw0hABeskkTgkBSlGtlT412z5L//1n77OwPz/9ML8nqc9/z+GNf6DGDuyHAxkLMVwrPy8VKvVtkfAV214pnKEYet/+Z8t/jn8b+Qb8r/4hIRJE+MTpjkCcGlhctvRZ5UwbACQbBsxVcNIOivflDBJyfHJk5IkmMuO7wlzmDBiR1JianrRQuJ3kHx8p/5PSf8C+X//t7T/D0si5aSkSexgmDRs4qj4MY6QTn8UO8MlDJuItUNN0qpwhkkaNWLcqHEj7GEloH1/hNXKmQrWs4znrL6nzZeZbBsjU5VlFlk8j485xjsXRiFQnY9fZaJrDeEqjboYmvU8f0PVlQ7VscfkhsYx6upWlLdRV443Z0uH4d8Y/Lvd5t/cuWyjR0R9/sobGs9hfj8avUadjI171qnO+ekYaPTdIdIOmiJp16w8lJY38yIdPpwj5aXq3Gii80N0xrrR6XmuiVFnOlTHbIMamZYbfT43OnM8n83uKLs0Xdnp82ptZCy7j8hroru8UoLe+Fe3Jqc=
*/
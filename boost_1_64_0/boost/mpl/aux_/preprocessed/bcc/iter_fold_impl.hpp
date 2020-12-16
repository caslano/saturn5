
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "iter_fold_impl.hpp" header
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
struct iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
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
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
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
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
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
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
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
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
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
struct iter_fold_impl
{
    typedef iter_fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef iter_fold_impl<
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
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
fIG824D9Bpk3zaUfsFnwd14CdPDzDvLmOIV5Cm17scPD1PeWwwdxkogv3h+PTqrIDYy7jnE3VOA/+NDdmeRF/NWWTWyl4OOzyakFyD2JcShXUK4twy9oc8SQi5rwD3CjsHEy5dI4/J1YsEYRG634MLxkriZvQDtQDgz65yD/zbQ95GRMeJjqwN+h2+Qi5xYjJzlsYyV+5IfuLGDoubYJWbHpPYX4E+WyNPJkHralXIFsJzBmi8K1nvPdteROxvsS2EnF+GeAPLoU313NcTT6y8an8JELCzlHb5+Cd6W4NvihF0kOccHvIvzHSx/wJmO/VGRNmg4f9DmykHbsFhFAX/A51kFMUX9Mv1grPMDzTOxioVzWQEzWMVaAftC+qAy/gOb1bq4ny8HPwC70S6DPU7nIRH1bM7GJjfzi9+gc/IPjZmzSEce1ayq+Dq102p7xARdjw9cDtH1I212cP4T/9LYgO3QihH6K4ZHc38n5nCnkAXKmbyk+VqDuVL0EfXvagHP8PP6+En7PbaWGl90l2B9aF0DjNejeTv+uifgv9j12NSJGkKvRjXheNQ77jsdWz4E/C3gNfB2PzT6B/gdZ+Do8HE2fudAah04z7einBtr0fwvebwb/cfpvh863GLcT+IJ6/K0IW4h5QyX4BfgkuE/A329L8VH42QbuWdH4fgRj4VPvMt5ajs88gX7QegDfTsMP6zm/FH6W5xP31KcshYaVazR23wqdK7Hr5cDKI7ErY/a48Bvs9zfGOxGaVfD9jh+emvEfxvkj/G6aDV/QOy0BvSjoX1wf28ntOciQSz7PRl5k2I38PcT8xhRs2kLOE3kLWSbA29eU64nHpej1hibyAriz8enj6NcA7W+nMtZ87Ejc+LHNm+TDIxjPlgi/dsZOx4c4/wO8HD0NfmOIM2i9UIi8s7DzamKIvlcvxqbV5APqK6mvzYS/SORp45z61Vj8cwo+mU2cNUFzJjbhPNuFb1BPge/x9eQ4bD+Iv91Hv+MoK+ChAHt0l+KXyBIPf/Yi4IzziZgbI/cieDvfyRjl0LNh+6XQo/2SFmjMJQ8lMZeh3445nMPrZ9jrXGLku+hUwQZFM9BtDraMZPws5MiGN3CyoXf9EmSaQxux5BPrCQkUeJwObEIifan7gUVxnMlxDDYqnIk/Ms6d2CASO3Vhy9MnYQv8ItpLzIG/mVJBLpkGH3Hg30HZRrlN+Ki4JmCbsxvQeyr5EJyJHD8i1gEoPyiDvyJ8YTK5oI7YbMPutAcXYnt4OGMa9sFnbdhooACfzIQmPKcjw7Muckk6elhEnobuLfSJgEaSWJthzCxsWjWXGPPCM/WSdujNYIxmeE0BXg5t5PgS+X4+BT6WEKfQ86HvX8SSz4qQDf7FA/XJeeQ0SgZ9zgqgFyGXwnXWQx9w5/iAw2MbPrUzkdxGaZ2G39N+0lTGnode4HcC430zH/pZ8IBdmqh/jcxB/MxL/5PhvZx6WwT+20L84JNdU/B1LzX81ReT//zktIn4CPViYLFN6BK9dKKHi5G/ivq7ZdBwYf8MfN3J+En49mz8rAb/aiGnUldgTzfHD+Fj65YAX057EjXyjqGePhnbY+sdM2iH1yTGGAB3HPXn+PA3gGVkYQPsYWWs5YzZjN+/j+95qFPFehM6mOcmf4I7QczRsNH3Msgb6P8jdLFL/E5rJHbB9WKvvypcd8lTp5OD0qbjQzH4DTgr4KESHUZEM04r/uikr7B7EfZErgsZ89alxKdY92KMhTbogdueT97E786h3J4JL+Cf5of/CmzOuDctg49ZyI3N7dBdR7m9jJhH548Sj2XLyRMOriXkP2c8dTa6R5YXsW9SJbHCeXc28EI=
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_fold_impl.hpp" header
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
struct reverse_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
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
struct reverse_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
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
struct reverse_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , typename deref<First>::type
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_fold_impl.hpp
yjssOircvh76Y0vqoT+uC+S9pjBlh2vaLTkGLMcjafisbAypfzPq3oy6DCdzz3Lm+tfXjDccGRKnTHweEsck87IdTO8VBcqy1Tlelc/b5LOTfP7Y5nOhfK4ln1uXt3zWj7FyvJV5w5SRd9F+k+3qWUG7XZU2TDP7vWxjj1IcGzU1bUqMZmzJXG0bp9lmM2exHSYzBE0IeZn2h6SNjU5QLkM4SOWSRt/OyP2Vvn9csw9ln5rWeUlthyKj5wSZ1mx+1CT7KpH9dKSV+R20k8r2sB/P3O44zW5t3gij5TgdgQ+zzR2qaLcnB4hsQ+dSbEPbdqampk7yhE6uleS4i2Cras6vUcpymuuwAoPjM5v6ZlKHcNO4+lJnzX6JnW09Jleb6kTV6unbmdQ29uPxZyj3s9X028B8XD1433+GtBemw0EdO1DiWb1EW7eTxMeH2Lc5ROrq4N3WXIADUoe9hHeoQ5Kjtg6SiezL5fdpc1pVJ62p++j+fYFG1yLxfG5Qz1wH0ujKWyDlnSHXRlNxJ+WNqa4vr+kC7wGet9gde9r5pKLjueaybtNa5clX8tF/B+jH29wlDUiabOO10r/g/bCmzMoFhzx/Lsn8GCXpK5NjX/N9I2U3uMa5p15HxVOeMN02X97OnPEI2eZD5XrUycm2/MrdT1wJvpfst3mh9vtUyj2pAfVR2z19PeS7S7a31MGuXprzOdx09uvq5dTeXKhjck1ylPAueWbV0NYrPDI+JIhXi+//DEn7LrIpmc27yKzE7tp6n5ThqBwbhwjvKWWoqSmDaajg+9+H2lwTybGsjh2s384Gx6y0qfQLSP+4zThx3h3MmV2Ssp63vMNTS1PWaWEPdM4p5bAtp9G1XZaUoaHsMzc5l/KcdWUw9Tw/yDunNfX936EMsazbX6s9zYlvyza4SajMMedUW/K3viBX4v1l3Dbqn61Ly2AwzwjPc9kmKynXCuLG1JbvMu25H2HYPum/BzpKwaRe8+V7wNtFUy/ObvMl84O3T0Ztka7fRFNOyUrXluZKOUdJOYdLOfO15eRtOW4kZjHlz+SSzCtTkrJqt194rH7M0F2dzSu7UJblMFeuLYPraMqknFAM1RhFJx4XA/FxUi5P3e9E9OWqz3dp/3qsQy4HzetQLuWLakP19yDn2VYZlO15yrO6jv1xIW2Eek05XdLF0/EUSLo1JDgr6VzkPngB6bjtDOd2lv1FvFzbupvj5TCV9lmzveqrbbFc+/NLlfBQ5e2jUJkrR11H3CzTf3IwpTlvkCZqmun7SS3rts7mY3+Vsq009/4JtWnHQs11Gs8y6QTleNqjWe6qzfUewe5ad6MMZnNPvv8KLf0x9WX/Wl9MLfV5YXQ+Z1LOJPJUNvBVVymrwT2mB8skEgbzuaqb0f6VOsl17GJZppzcK51TP+vb2Piu5gKfl3Msl7BHucZqoK2v3ICUoH+0pO2c8bsscj0jx1pd1N836dsMxirl1lVfH+du9te47D8GvpL66F/ufaB9aPs9Wqg5bkF3n0YBdeVz7G5e+Vkp30fSpsU00pSPfhFz21uS+/6StWeW8nA+6a6V6LRUfvVl0Bbr6zYzjJRyLNZlG1emHuDwDeXW9l3J76vszit3L3OhveUesjfyXc7AM5p6a+a3cLvPb8OGNzHlGxtOK0FPmyluljlOOt/st019zfe9/m1E/f0g/03fxtr1zRn3Hz6kuXadmWB7rJKT7bHaQ849aWty8X22SUBT8zbhziZkBtc3po3zB8492/ubpZxsltbbxXLulSdOyTEulJf9pL7STodGzbTre3Cxuf+U1emOmVDl4blNne9JnRtKnevjfuqc1lytMyEsxlzpkt/TyX4=
*/
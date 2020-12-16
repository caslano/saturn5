
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
j4UDYQc4CHaEp8JT4GnQDuPgADgEDoanwxQYD8+BCXAGTISz4VB4JUyCy+BweD08Qz1n5DnJQW8wZ2Sb9N8O2ALuhN3gs7AnfA72gc/D4fAFT73ynA2HGdS7VsbuH4BHwwfhsXAdbAXXw+7wITgUPiz1Vhwhz9LyjJ2GDVC9o41SzYmKgGNga5gCO8Cx0v7xsB88E54OJ8Az4UQ4CZ4FM+DZMBemwUI4CV4Kz4FXwclwOZwKb4dZch3kwKfgeXAHPB++AKfDl+AF8D04A1bBPPgbzId/wlkwimOaDdvAubAvvASeCi+F8fAyOAxeDsfCBfA8uAjmwaugE14Nl8Il8EZ4HbwNLoWr4DJ4ByyBj8Dl8HF4PdwMb4JvwVvgO3AF/AjeCvfC2+DvcCU8AFfBP+GdMIxztBrGwLthV3gP7A7vU10v9pfMr8MNcr1shMfDTfBE+BjsDh+X8/gEHAG3QM8aC1LvQIO10N+Qet+U6/AtGAYrYQx8G7aHu2AvuBv2h3tUa31USf3tpH71Wh+vSP2vwjbwNfVcqJfN8xL9qSpnl3It/ZRLDbCcQ1UuqpY1Nkrc7fNTrizA+ioCLFftp1zf/0DeJMengceVrNxJwcWXrNxJVu6kQOJRh2PupFB+TbpiqZgDK8HKsEpsHxYxn5gVloEtxsqw97HQBVYMy9qszdqszdqszdoabjvk+f+mFKUryKyH2H8HW9Pmk5V8at0aMXbuGpcfOmz8hPSEiWnECWenO502lz7ghzD8uHPhHaHPCTeVOrY9JTnAVJX4j3tpY32XUVmmTxy1HH++WvvqFoxDGPnL9R/XjOSYO0QytuI65rxZWZl57Oaz/v2RorkVn82xc6Pxa+STSFIgsXS1pqBC6l8kmoIFWAb1h2311p+Znd0rvSDngpwsZzpnGgSyJn2j5gtdddhyCgp0MWONvoA6PXFxV7/PKfLExWNr/h2JgbTbZ93+O6XdK6Xd23zb7SyYU+hpdmDtHvN0cO3e79PuA5p2a6+hUImPJ8v5HIVNo90lT6vanZebWejKmuf/XJq1z4mfvJx8je97xPcz0mdbsWzlWtL5JjLfy//8FrM1Mz7hYs3PnCm6CK9ehvbozrP6nEZJ7PxE6Zt2WI7Svm3e9im9or0W/ed29Gmnxue14rO9+GwrPttv1/rUXEcB5C/U+VSdhyaNja+BVJXPGTkX5WYfimugsfE1UObru47XwHGqayA3O7Dz777XRUjs/DTpl0FYAU7KnvG2TU69IscpCOReV9t5KBZ/g8TfAPFn2+H1p5x2cVcnX73F15fiyy79HovdFMk59/WVk+03Z6zbz1SVnx4S806Wk5UifkZh5yn3lxo/dLlyUdkC9iHHojlP7zfR62ty8WGr0eVl985N1/wuBXOezo/Wamw+Va6jfO91FC7Xkbo9UyTO31ra0wqbQT32mvbk9s6ue3u4TjXt+amFS4OkzQeKf6M5eBk7628OXvIxxnPwHDsbbg6eW+fzyjEmaxTtPLRrFO3j79IjzXQHwcfbjePq5voLYx2EeZzcWNdgruMw1msEr18w1kEEr8sw1jUEr8sw1jUEr7Mod+kdiiuT/3i9U9Tyhya+ULr83usHmutrJhyvfH5cRdPF5520d8jPT/bd1HLmyOn1p48w08t41t5/ypvrcv8R2nhaB5tqbpeUO8agXHtVuWop16KW+hw2eXaHi6TcsTBbyl0qcfpiicvPh53hAngavAIOhlfCqXARTIdXQSe8GhbDa+ACuET8lmDbxO+d4vd4uFD8The/F8AIOANGwzzYDc6EPWE+7AMdcAScDUfBQjgdOuEFcA5cBOfC62ARvBVeBFfCiz3xbXm2hsk=
*/
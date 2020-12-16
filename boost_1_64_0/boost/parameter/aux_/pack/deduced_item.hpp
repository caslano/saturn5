// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_DEDUCED_ITEM_HPP
#define BOOST_PARAMETER_AUX_PACK_DEDUCED_ITEM_HPP

#include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { namespace aux {

    // A typelist that stored deduced parameter specs.
    template <
        typename ParameterSpec
      , typename Tail = ::boost::parameter::void_
    >
    struct deduced_item
    {
        typedef ParameterSpec spec;
        typedef Tail tail;
    };

    // Evaluate Tail and construct deduced_item list.
    template <typename Spec, typename Tail>
    struct make_deduced_item
    {
        typedef ::boost::parameter::aux
        ::deduced_item<Spec,typename Tail::type> type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduced_item.hpp
8zHPg01wG7IHqef6CAx3dmx0o3V+bEajdYbs1EbrHNlKfm9A7OfJbuLafqbszsbw58raz5RtNtxZG3y27H7ilL7WOmN27NrQc2aXYHYMroLmebNN/M6FO2El3Iw0Os6dPbw28rNnE9YRXqQRsZ9Du22ddRbtgXWh59GegFugf33rz6Udsj70bFrnubR56yM7m7Z+vXU+bdN664zaffw+hszhd/QG9/NqB2z4YmfW7sX+RvgG3AXTrg4+vzaX63zEPMd2zdXWWbZbrnY/z3bv1daZtof5zbm26sU1Aynn91RoP+N2iXGNcNat6qy28dt+5u1+rtNgM7SffRv3VezBNyiHzjNw07gXfTE6NLxDkHxkA7IVOYT4B2COLESuRXYgh5ATSDIDoWORfGQNsgXZg7yBRNNxDEBmIDXIJmQncgA5hvgHcx+ZihQiG5BtyH6kGUkdwjm2SAnSiNyB7EKOINFDsYvMQeqRzcgu5CDiGebzZCBzkFVIE7J92Jdn4X759+Xfl39f/n359+Xfl39f/n359+Xff9Pfv/r8/6K6qqx/1vn/29J4PxxsjHsZR78tOHvBgpnz5hZMWjA3izWslxbUM66pzukvTMYv80w0GS+Nta1beZkBscwUtTYkxKGK+pbXH6UQlocIy84hRlgqq1kviz1Z4+44j974tpgE98NNXXhfDfhbMqKiwOZ3YM1MHfdZl6LXstUp3dt8xe57AIlbciZpYG98vYdACsxT9x/1rZf9N+O0nQztjjbjvyS9FwEngC+rL/e47YXh8DdD77Fk7UeyRN3/oW8lto14tVc6NToMJer+fT7D/mNqALOozgy3+kaj7n/Dt0Tt40eYZL8Cj20vwVFd1D4+6n6Dul+/oqbSE3TWY54X4yhcJzH9MUn+6Hb++Dh/VKK5Zmeped6u6Kaie3OSWs+30H5W4m9lT6hi9M9LJPzQkGPyuzRY0IvsrMQHUkL3eTTKQGdVBuRspwSuyVc5f0HyAjOdR+iIbvuArmFXpQHpwrVKF7Vm7xaVZsSza/D5KWmyqKubBLAr8nPy5UBXXVad9UTl6+NpYddRYddZNiuqwq3l17r28ude9rSuzsMI1guaaUt4XdJW9tJxpi201+cE2dS5XxStFuwZhVBYmwNpVDGiJKg+S93Q8dZ1w9cNfWYT+qLauO8tZEuLRxOlTrunm9ZNQXehSgHOOGA7/YL6iuLlYmcP5cC4f4O6X1xRw0Jodays3D/16WefJWn7dRUlBdZeRltUPVL38K+GFXQVJex3YmwVUF5RVU9YpkjdpOylWXs+H8CeuKn9NONQaIRHu1lXW1PQwIGCcgakzb3blHvtlJ1m7LTT7UCl3g9wlkrLJ7w+KvlQ71gxZ6WvsruHby4j2P9stC19VhTV1RP/5aWrzfA0BoeV7oZIyr0a7hn58IDZRom5JyhdJM3Lq+vqVTSC43FZd7VeWtnbIXGXtC6tq6uorsI7090muZ/usYVFMsu4/8mn3HfNj2A/F9jy4oi0hekxgUJTloxbbaLqWOWaymVgbavcL8FgGfej1q7lSNOY6Pj42Gh/3PDA2YBq74FAWDrIXgLnqLg9ovYTi8ZuoeX+2tvw4Iw21nmnvcWPjTadLvH98SC+XWyUP34W7tn1dlp6jSdteheLnhmng6ZeVFTj84Q6Pi34/gmbO3cRpl7xwffT2zLmy32/f927/pgEf1x7ay1yRXJw+mxoK+mz7u5A+rQ9ffrcpPKhUqVPBnYbEQnLuodt6WMPzxvaj4viMwznsz3h01+5P025fy32jtjcrw7j/tR2pvtdWnS/jc39o7id285yf2AY90ssnbUvqnxLaW+un47ztny+aoajTY4=
*/
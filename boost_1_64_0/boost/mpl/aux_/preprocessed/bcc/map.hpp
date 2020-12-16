
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "map.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct map;

template<
     
    >
struct map<
          na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map0<  >
{
    typedef map0<  >::type type;
};

template<
      typename T0
    >
struct map<
          T0, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map1<T0>
{
    typedef typename map1<T0>::type type;
};

template<
      typename T0, typename T1
    >
struct map<
          T0, T1, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map2< T0,T1 >
{
    typedef typename map2< T0,T1 >::type type;
};

template<
      typename T0, typename T1, typename T2
    >
struct map<
          T0, T1, T2, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map3< T0,T1,T2 >
{
    typedef typename map3< T0,T1,T2 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct map<
          T0, T1, T2, T3, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map4< T0,T1,T2,T3 >
{
    typedef typename map4< T0,T1,T2,T3 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct map<
          T0, T1, T2, T3, T4, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map5< T0,T1,T2,T3,T4 >
{
    typedef typename map5< T0,T1,T2,T3,T4 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct map<
          T0, T1, T2, T3, T4, T5, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map6< T0,T1,T2,T3,T4,T5 >
{
    typedef typename map6< T0,T1,T2,T3,T4,T5 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef typename map7< T0,T1,T2,T3,T4,T5,T6 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef typename map8< T0,T1,T2,T3,T4,T5,T6,T7 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef typename map9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, na, na, na, na, na, na, na
        , na, na, na
        >
    : map10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef typename map10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, na, na, na, na, na, na
        , na, na, na
        >
    : map11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >
{
    typedef typename map11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, na, na, na, na
        , na, na, na, na
        >
    : map12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >
{
    typedef typename map12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, na, na, na
        , na, na, na, na
        >
    : map13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >
{
    typedef typename map13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, na, na
        , na, na, na, na
        >
    : map14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >
{
    typedef typename map14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, na
        , na, na, na, na
        >
    : map15<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        >
{
    typedef typename map15< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, na, na, na, na
        >
    : map16<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15
        >
{
    typedef typename map16< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, na, na, na
        >
    : map17<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16
        >
{
    typedef typename map17< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, na, na
        >
    : map18<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17
        >
{
    typedef typename map18< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, na
        >
    : map19<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18
        >
{
    typedef typename map19< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct map
    : map20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename map20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* map.hpp
CjTjY4Yxiw0c5RrpZxpTXqMUtWlBD75kOmvZySlukG5WhuB/5KAMDehMP0Yxg+Vs4zjBbH3gefLwJvXoRF9GMpftXCCeow88R37KUZ82dOVTxjOb5WzmIKf5l0fmmkNeoxgN+JD+TGQuq/mZa9wzz3hRlFp8wEDGs5jNHOQcN7lrfobgWfJRjgZ04VO+YTm7+YWLpF6QIchEDgpSmko0pRN9GcYE5rCW3ZzgMvG3GYL7ycRrvEElGtOBfnzJFBaxgQOc5R/uXJghyEgOClCWGjSjHd0ZwhimspA1bOMk17lvkf0pSU060JexLGAjBzjL36RZnCF4nNxUoDld+ZxvWMUeznKdNEv0kafJSiFKU4W6tKMvo5jJdxzgNNdItTRD8AQvUpjKNKYDgxnJNyxnJye4Rppl8oXneZVSVKQF/RjFIr7nEH9yi7TLrX+eJQ9lqEFj2vAJAxnLFBaxlh84zQ3SrLAueJJXKU5N3qETfRnGN3zLRg5xnlukXikGMpKVPBSjIu/Rjc+ZyjK2cYTL3OKRVRmClyhEZZrQif6MZRYr2cAujnCeG6RbrQbwAq9ShLLUpgXt+YT+jGIWS1jPfo5yjmuEa4wF9/Ikz5OL4pSnBo1oxYf0YxRzWMVWDnGWv0jWqvs8T35KUZ0mtGMQXzOb1ezkCGe5SvCdNcNDvEgRatKC7gxjBpv5iXOkWSd2cvAGb1GLprShJ58xnlmsYisHOMuf3LbeGPAUOShOVZrRhcGMYz6bOckf3L7BXJKVQrxFfVrTjRFMYymbOcZfpN8oZp4lB/kpzlvUpimt6Up/RjKROaxkPfs4whkucoPUm9RIHuBxspOLstSlHQOYyFJ+4DR/EH8vr3iV8rxLD8aymF38zGn+JGWzY/Ewz5CTktSjOR3owRBGMol5rGA7BzjL39znIvU5clOat2lKBwYwnumsYR/H+J3rpNmqvzzJs+QgD6V4m3fpTD9G8TVzWMNWfuQXLpKyzfriUZ4jBwV4k1o0pR09Gco4JjOTJaxhH2f5h3i7esW9PMlL5OYNKtKY1nRlIGOZy0p2cIgL3OC2HdrgNcpRl/f4gC+YwEwW8R07OMFfpN1pjihIddoykG9YzRH+4I4f5DJv0YyeTGIdJ0h2Ob9TkuYMZCZb+Y10u40ZZXmPfnzFIrZwnBs8uEe+UIFWDOFrlrKfq9zzo/6ShaLUpSO9GMp0lrGbE9wk7V65REayUpDS1KUzQ5jAAlazmWP8Rep91gxZyU9lGtKabnzJbFbzPQe5QNr98o4ivE17+jGJ1RzkJFdJe0BeUZxGfMRo5rGD30h9UL6QiZyU4G2a0IWBjGIq81nDdvbzJ6l+Mr48SwGq0JxejGEB29nPr1whPpQheIxXKEkNWtOLYcxiBbs4yXXSHs4QZCA7xahHZ4Yzm00c5S/u+ll/KEBFmvMRnzON5ezid5Ij5p0cFKc679OXccxlA4e4xp1HnW8oRE1a0oXBfM1CtnKamzzyiznmdSrxLh8xhIksYw/HuExwzDHIQF5q0I4vmMIK9nCW4LhrKTKTh7LUpT09GcciNnOE69x7wjxTnJq0pAdjmM5SdvIzF0hzUvsUoCzVaUYXPmUUc/meX0n5VS5QhLfpwDBWc4hL3H7KNRyvUIbatKEHo5nJMrZwmPNEp9ULHuZ58lCOxnThM8YxgyWsYw/HuELKGWNFBl6mMOWpSSt6MYKZrGInhznNRa5z+1nzyXPkoixVaMyHDGcy81jJdn7md5Jzxp4MZCEP5alPJz7laxayg3PcIPVv6gTZKE4dWtODMSxhMz9whIvcIPV5+5GFPJSgCrVpTnu6M5ixzGE9+/mNf7njd+uU7BSlGk0=
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };
};

template<>
struct or_impl<false>
    ::result_< false_,false_,false_,false_ >
        : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< T2,T3,T4,T5 >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
wdY/0N7lLOPvWZp+ggjLK/YV1AnDCZf4m/8K6tYSLrE8hmUJ/DuDkDmRfaGz/oTyVzj6FCpV1sUy5gMjWH8l50QIJ8QTdhOOEqbztwxVveByluX3Jw34dwkGrdL2RVRKWMqyMOb34gmC7yRr/0RtsVRZ/66q9n6KxrEsCwNZthvDUN9nUSTL8nR9F61k2Rn+fZlg68foBMsisRSvEDL4d+Bqa93kMOyPm5RtV1vrKpsJu/n3cYKtz6Oy1cR3jaPvo5A1jv6PEtYQD9YpJkQxfwkr9IfEOkfWIPNlaKv37LuW4+B5Qs1Ia19J/ZVlOB07sSwVzzCfg876TzrC8kwcx7pZGIO2OtR5qnrUhnXkI2E6oYT5ApYXEZYyX858IdYcTFxYdkL591TSC239LkWi676XHHWwO93NMZTl0xz9MGVjAaGEEMHfNw2uWEe7XOppb7vbUVe7kH+XEfyzrPW2Q9BZf03jWJ7F8jxCMaGM4KoPp5YsM2dZ+3LKwf7MH8HpeAYvE5ZKPfCm93DdYTjq64RH4UqWp+I2vMKyo1hKCLqFvF2v7QeqKfOFOAzD+HsCnmI+C6OYz8dMzJF+os6st9Uzlz6j/sq53kK7I8JuwlFCKcFwq5+hLSGcEENYSsgjlBAMdPwXQoggmAnZhHzCCcL5Gd66697JO3kn7+SdvJN38k7eyTt5p/+v6U9p/98rWqn+/7vb/yt1/4MCKFOWep9R8m4mROqAtCP0VerZ5VrrfQ4fH70wzcRggFR/dDTiN8YmGSpvwy/1QWx1NaU+iLauG3+S+p1O66Zr6tSflrg2kbg2IgwgrqnWuE4ZP3r88GjiJr0NeBQ/Ts9eL7VfMPNxKclmXX1w3h1YpjSpB5gsaZWrOr6kliUC7tUL1sRBn0ZSL1Zdx9l5OjVQ1XGOMy9KNUYrtRq19X6T4mMTWVlzTpHy7qmNpGkrW/5b236YukliKvkvOe9Ruv6efL+Ea1zWFXJVJ8hVnRrP6wr90XV/rlVdHk/rznha98d5nRrP6wQ5r9vleV2hkh7K8qI5hT+2vK7Kvse3Tyk+N+BEnqs6U9e27k+oQe6NGELwr6rta6uRvCtqjO2wKdq2S5XtmjjZrotsF4qNsCva+mLLle3SZDt1X2wt5J1SK2yBrTEY22B3DMa+2B5HYAdMxk6OeMlnnW2cxKuexCsQW2EDDPNx712F9j2F9h3FMIJ2zAJn7yNcvouQ9w/ujWEg7xp07xS07xP07xLCBmjfHzjeG7ge40D/rkD/niCSkCF9lsg7AXkf4GrsAzfK/VHK+nXl/MwTOkW6GhfBvTJ9dTk+ZfhSfo9TPS+3d11m/5vl9VJW72osBc/K5S+h9MNiL4M/SnBW9i59slDWri1nLySEsewURqGjTF1bnh4a5WeIImQStkV5y8K9k3fyTt7p/236k57/E00zr03f/41Vz//95Zm6gTz/BRIGKe1716nafU4ePnR0hKU9lrW5M4+R7vQnb3sOjGEmzeRo9/kVP445+TiD7vnaV56v50lb4yQcTFyKXcQl3Wi2xKFmJW1R+2Vp26JKnHgWNdnjpG/7fslJO3FtG9w+dV+7W9kvaSnjZdvStEDOo7ekaU/CMKWcIEvOw9HITZuoHoz/LO0D7c/W6wKVuEl5gS2NafbnKC+QZenKMm2b5xwpA5gq6T4JRxDfclfxJeHdK9vwqztovSbtJe7O095Ve+cAVXvn+Nk0q3TW5wP5UXqPLT+059df2vGflnKbU4RRSn6sV52fpXUrjYVNs0xxltEdDG5cW5q2m86vJbl27g6UNlHqdvy68q1TTuI5hnge/as+nmmJVxM/27WykXl2YY/b2GBXcXN8NjM=
*/
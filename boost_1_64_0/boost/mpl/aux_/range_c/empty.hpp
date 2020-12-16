
#ifndef BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : equal_to<
              typename Range::start
            , typename Range::finish
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

/* empty.hpp
cQgmYiSOxqk4BufiOFyKSfxbixNwC07CL3AynsMpeBGn4iOchspxYToWwBlYGWdiPZyF9fEt7IqzcSDOwWCch0NxPupxASbiIhyDi5HjpfKewXPfFfhvf0/gZfaV+1e+J+C9nHc7CLGEmYTNhJOEGwSnFbz7scL2XoBtsA22wTbYBttgG2yDbbAN/++Dve5f3/4/NuLltP//urguo211uNxz74GFsCt6ePMsrLqp/X9wtCfzmtpFOaNqsPxtdBl3RDcyJxTV7bToYdSsLVnYSH1GOzGWxT2DzLbl6u+4qtuFu8l9y1hJeyTW82a8pintJNwzODon7VR/fkXSKmlXt490kvcX+DywpDWz/aL6fYKgjHWVdQmLVrXBynkfkjn9/qaFNlgW2nhZalOV87ZfOW1TldO2Xy/r+63Zt53KeRuvSEObqqPrul48MH7O4/nNmjSb4/Ru+Zx/pzWnfZByz5U2KLKNyrZ7lFDc0NbFOBSR70IWRWcshqWxONbAEtgYXbA5uuJALIWDsDQmYFl8A8vhMiyPyeiGZ7AC3sCKeBcrofKsvjKWxlexMlbBNlgVu2I1lGeBsr2irIf6WWBNWY/ash51ZD3csQJ6YAP0xCbohdOxAS7EhrgJvXEHvoZ7sDF+gq/jEfTFE9hM1qsFfo8tMRVb4S1sjfewLT7Bdphf7uk6YQeshh2xDnbCRtgZX0c/yYeu2Am7YQT2wEjsiets9wj/o+8RruYeYLLtPqBtsA22wTbYBtvwfz/8Fdf/MdF//vt/yvX/34vrMt6VqyXn2ftlHfYS6nOyvL2s6Rq6U5fO/oEt/AMCQ2JiE03v0j733ahILgT0McZreEcZHxQXQxMA83f1lkv8fQl2hN6EhsS/ulyW+AfFhYU9913eYqr4lQzTxucg9wyGSnwREp9b+SzxRURH6J8bn3p96afALC69xNWBUIjQhuCt5G3WuKLDRuiseg9YucdAXIY+ENRxTZS2NnNyyzvy2Ii4nNyyxBXPrIa43J8ZV56isyqa+m/INl/VfTgwLVTukZj32XBD1WeD+h5Jtwi5R2Ia1xnfcxtJupMMbadYF7fM99xO8jvlGzV6JSJd5vulD2sYvzOkfY/XVzJyj+T9TkIT8sOvUnb5wQvZIUPDQnXPLwNTPrzGsmIlI0x13I4ZlQXpVPeLJG+0/VlkW5aNTHU0jzHCeEl7DKGpN+tU2ZR2ZUsy7A8Gx0SFxSVKuh2sqKfktRKfpe8OqcvXYpqVZZjWOz2zfKPBWAbybZsL8i58AzuWhR7YjPU4aWk9DK9gGtelrRX7GPN1kfFnrMtR0zum7pp7kZHyPrKsGyti9s5pUKxx/KSMR8v4fc03p55o3n9Ok/iGy/gFxuVbO6r3Zs2/W+ZI2Z8j35T2xeurkE8ZdV3iJjJl/LjMGyXztWSeM4QVjOepqvoeofxOX0++kWca95C+Hkzj8p5usmncy1iW2u3qkPQPsEXq5kZCC8o0pZqpTKntyvvV6uppVf3MU3RU9RfvL6aY1FVtmbtq6m+6hf2RfJtK7tFauoeX83uitvdhlXul/773Xpcb7tEe2JA38c6j25tWlu1Z942kq9df3r1YS/fUje9dyHmUnF8dVb93Id/ot8dx6IhJ6IzjsQ5OwPo4EbvgJOyOkzEKp+AwnIqjcRouwem4B2fgXpyJd3GgTs6rsK+kJz/6S3puyPeJbmJ+vIUFMQ1L4R2sjnfRG+9hC7yPvVXfQQrQyfkUDpV4HLCjxPOTxPMzOmIqlsbLWAOvoA/+goF4FSPwmizfj7Bdlt9Blp8PW8ryv5F7xt/J8r7HOngBG+FFbIk/YBu8hCyX/JfzJTmPUpZbm//rURk=
*/
/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_TIE_01272013_1401)
#define FUSION_DEQUE_TIE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_deque_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename ...T>
        struct deque_tie
        {
            typedef deque<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T&...>
    deque_tie(T&... arg)
    {
        return deque<T&...>(arg...);
    }
 }}

#endif
#endif


/* deque_tie.hpp
xPkYha9iNO7D3qjUGVURT7xLPqbHFXrSk570pCc96UlPetKTnn5HuhHx/8TrGP9/pYn/kyT+f414tB2+gs8qfeX5WuL/iY7i/ylXuR+gwEHMX+Ig5i9zEvMvdBLzVziI+ZdpY36Zf7UlPjdvuPT/dZXYP9xB7B9r3UZrP4Vkc994iQ5i/BDrNGyl1A84iPsjrxD310lS4v6gvUfvnzhjTcmjR/c1aTfypX+a25jlM5LPjmTTxtxM2pi1fVH1wtY4QNqcR2JbLERfvA3boavE/03QD5ehP26Q+P9vGIC7sQMewkAcJfH/ZOyEJ7AzfotdsIXE/d2wKyZgCA7HULwFwzANu+FMDMdyjMDaEv+3kPh/FUZiJfbEndgL92MUHsNoHCf1AHkYg//EPliNcdiI8uuLftgPIzAeR2ICZmJ/nIyJWIkD8RUcZFu/QAHo9Qt60pOe9KQnPelJT3rS0/9zuhHx//V6/r8Z79TzakjfiZPdiTVZZroxIzM321QvcFLTL8ABiSPHErv54ijcotQLtDbXC9g+vx95lfqAWNxg93xAooPn94c66Jc81TJdZo6xyP55fdr0bZ/XZ1j7jP9frM8RaGJ2X3mugO3J4U/LcwO+6jibOLy3KQ6v3LLVfUn7b7/w+Pmbu/x+KfNT43APFykTKSsltSFfIhvkGWpfjMSeSC6LwygcjNE4AnvjGIzBTOyDuRiLRuyL92I/3Ij98VUcgG9iIv4TB0rcPgj9cTAG4M0YjkMxFodhOo7AeZiCD+BIXI+j8AO8BU9gKp7EsfgrpqE3+ztO4v7xSBlzL4K7JRaO1GNhPelJT3rSk570pCc96UlP/2fphsT/2RMzr9fz/8c17/4rkzj/VVe1/f8lfEZ5f10LS5zPms2t/7891rdp+7d/vl8T60udQJG53T/VSbt9oLSxS7yvfQegTaxeYIrVv97c5cn9F73e7zfv4YBjLR+9IG3mZNkvZX9Jtv2iNZc281a4TtrKX5C28mhmaotD0BdTsB1mox8a0R/nSxu5q9wj3wQ7YAUG4kvY0a7NOEWPk/WkJz3pSU960pOe9KQnPenpT5FuSPw/MfO69f93VBP/L5R3xytD7cSniMmPXWphjv9Zs238n3rFd8d7AttWjzhbM1wpw40N7o2+qmv62z8puRtrUsftsY4LMY/bYBkX1tM87i7ruEjzuFzruB7mcUnWcd3N44Ks4yLM4zyt48LN46a5WsaFmccNsY6zbHNH6zjLNtezjAu1bPNpF8s4yzbvto6zbPMa6zjLNi+0jpNt5h3vDupXpjh4tqLAwbMV8hyGtt5F+mjQPpsgz2DY18U46NMgT/NOfFmX3XMUJfmF8t54f8s45gthnO3zGGx4iPSPoB0XavecBMuTeX21ywu1ff/EDjf5UvL99sbeuJlpYhtb6rWysjXf6cQrfaelrqq9ph/K1MvuZ9H2K1kSBszHPlufL7G7D8XIPDZ9V4aY5wnU3sui3U8p2xDLvSsFbIH9uylKupnHuVnHWabzsc7LYmzL7KxUQ9WVMqspZTahmbUuMO86l5nnbygzg12ZuV2nMmvooMw8fmOZmesbHzfVNxouLjLWH7K9i9ey9ftzfUv3S98crpbjqJQwz5uQvaTusYHUNzbGjtgUe2AzPIbeeBcz++BKbI5V2AITWEZL3Iut8DC2xq+xDV7EtuhZQ973gO0wCNvjBvTDl9BfWS+FehNGYwAOwA64le9EIO7Ejvg+dsLj2Bm/wyCsQfl0QS8MxvuxKz6OIdiWfiDDsAq7YQYFHY6TMAIb1OachNuxB76NkXgGe6KxDuc9nI9RWKeueu9US+yNnTAG47APpmIsfohxONyTLyY=
*/
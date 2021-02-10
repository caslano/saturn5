/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_31122005_1209)
#define BOOST_FUSION_BEGIN_IMPL_31122005_1209

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {
    
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename mpl::begin<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
eWbwFj14990uxyNz8OqV2n+KF65bpUmt/uKZeV4hTe+h/aHiAtc3uBrATus+3YM3ad1D32qlna8Tek7TN7hbUJB0G5DyIqVHPGk1O/2hWm9qcV0a6A/34PD4+GfYh/cHh0cunDIpeAWx4XLJ62sXTnJ78lvJ7u48zT+5wA2wyntgMCmFBq0Kc8tqDvhciYxLzXNgGnKus1oscSMkmJJDISoOw2gyD8e/u3Bbiqzs7GxUA7pUTZVDyW441Dzj4qY1s2a1AVWgBbSfC23QZmOEkh6652B4vdKdGQqCVVoBu2GiYkt0xwyUxqz1L4NB1tQVZjLIVaYH2RYKrzSrR1nNMZoV24BaGzAKGs1dIHkXVioXBa0IER6um2UldOnuwkKHMh+oGjSvqs4cqgqu2xQ4xB1aLknCGqMXhhatpCZvt6VaPRBEWDtDRVNLdIewoFyuEHgXGpnz2spbILZeOpQt5K+UbBd7DkpiVNDzYwjjHiyZFtqFqzA5j2YJXPnTqT9O5hCdgT+ed/YuwvEpckOg1xr43brmGqOoQazWleD5A+fftdMdLzmH4Ww6iiZJmmBk8VkwTYPxMDqlzD9A7/AY/mgkEfzHHvQqsSQGwJH34cg7wAPapZzpTaq5oVrjH2ml0XJ8DmP/MnBeNr/Y
*/
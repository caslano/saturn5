/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
u3/2nxeUzBYufB9Gs/AkmkWrCy8sCvcOd5vTlX85Xa2Xc3gfztZTb4m6lPj6MjFO0/jtvt9uoZrJUF3bCok9dK89d3A9fzuPP8zT2K4q44Qdd/CDZDqFcJbEuIxPljfJHyzgwfDZEXbh5tFyGp6erecTC9U/9P4HUEsDBAoAAAAIAC1nSlJkbXMsvgkAAK8VAAArAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9VUkwuM1VUBQABtkgkYK1YWXPbyBF+n1/RxTxEclGUvd7ExzpboSlqxaxEsnjYcZWqWENgIM4axDAYQDIT57/n654BD8vx+mGpEgEB0/fXlzq3LXryh31Uh9nR734W8rvAB9eGaFy630xSfZ1gsfhM4QeEt7h+h6hz2lN9XpzSd1F9phOhWkRZb/h+sfgOcbesJH+dM/Htgm/xJFBG+p7bbEt7t6ropHdKz169ekln9MPTH5626UIX1uQ0rUyxNOVdm96k8uTvK/3pU8ebn9tkKtJ554jhbGU9eZdVD7o0hPvcJqbwJiXtKTU+Ke0Sf9iCqpWhzOaGeqPxh8HwlzY9rGyyiny2ria/cnWe0krfGypNYux9YLPRZUUuAwfwT62vwLOurCs6EG+oMuXaRzas
*/
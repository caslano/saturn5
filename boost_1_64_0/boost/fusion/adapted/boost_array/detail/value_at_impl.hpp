/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_27122005_1256)
#define BOOST_FUSION_VALUE_AT_IMPL_27122005_1256

namespace boost { namespace fusion {
    
    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
I6Q3HpKyly8RpQ88cTYUJUTdOBrZ02S89w2wCSh1AklE1aWs+ukEpqbm48awKEz2EiY3Fxvx49TMk454ztc73uec7g3hBaxaVmx9FKjbl1Uk3I8BoPDAj0VEYtjcgWf6bP5Nd9wvuCiaLPrVYzsz5+fDQnFtob3+AedVoOxWrkqlkyazRB52yHufoAi1c7+etJHC50wh5O5Mmm9wDl7NdHXQVb4s3fWEk4Q3wyyZtGLlwAaXDlpII6epdKauAEIFnKXJnMAnR4yz4jI0THJqhWCN/WVOB1bWUml/km9HW6Z9Apc8BL+JAfDm7lNwCXv98nPTxFFaVbgtReH+gyuSRaz3LYvUy28aGHZAyJ9RmpqHe/RvlzBQlISUTNeOajrgptUON+rkU2Y1YHsp4GHAKMzTa7RSV1wj4ni71H0BJO93NTmbKMyyo9B4y/GapyBAS7QouN90frFfi/U6WZw7ck8NvZv2WZtXSwX49bXhBZ95CsdvNBLKB907N2AnotVR1ZMW0FmPYfWc7wh8QP06yKtowGmm7PiD4tfaD1V/5RureVrXvXCl+Au8Gw==
*/
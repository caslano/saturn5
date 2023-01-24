/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_AT_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_AT_IMPL_01062013_1700

#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {
    
    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<std_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
Wmz9Ds0zRvSloKxQkREpz25IlX2KFYf844sN6dQLLQs9EEGKkkMnShaHVDE+MuWoF+XF5qUgdyybx0Za4Fz8fRzWp8gkMGt2TTyjYpRUcW1yD8327DxhuEeTIRoIMhpvmmdsRvG8Fs6qWXg6C4epUkt1eB8aicPd1roIJuCSkVw4FN3hUJ7DKFRdT5gHnPsQxqIqT716Ww5APOPgzoqoU8fiMrhohLY5vYKG93jkZwM0YMYoYt8Mxr7sb7Zs6BzO3AT9CvN+SlXzDnADp2yBQwawBncpDrb0cdgdSkakN4z9G/P0sI1ftHkdkZlMQMIU7sC5fNUXDu/EGIci29mHF0BEPBPqRQM8TRFFPTzHIou6sLCtzT3XwrVJcyxb6bFHFF4bORRrfvW+cKmiOiuiSo6oz/JOTGKJM2IxF2lVtUNalRHpqRpY3RbhafybvW2UIxjvOJKF2XzA2gm4OOWQbmh6LEtpUP4CE9MoqeKP5kQwL3X3AN0sn+2JnujXQ7Wx1V76vVbw3inpBqaabf1cMuNkuY+NYc0TpeuLJXNIbxPUwDaY2rKNgZTCeuCbtLXQIfecw/pidj1L/1BfO/c4xxaArfdbLVpN+ke4evie7Dzvt/ptkvz32rAMeP+vvqYl+e98r5RkoXkL2LXWQneodm4in6Q+/xdbLDZAP+cyxoATjHdZGvZFpgW2SuCMozIBT9O7rE3gX2f4JjJR
*/
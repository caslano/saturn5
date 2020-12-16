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
b6jO88FYpct8OZbpBr+C5Tqe6o89sFKX+CdYoqt8D9br8t/dH9N1jZ/AAt3hc57ujxm6wfut7o95usJbPeNvlS7wFExN4/wbTEnzeY9n/Y3ewfX5jef6Y1jqNc75P/2t101+ARvSvbin7W+3LvAxGGROhSe/0B+jdZ2//GJ/jNRl/stLzt6nnI21zi/G6/y/nDWM1G1e8G/30i2+7GX38tnMuv64Cet1m+f9x/XTdV71NwLDUq/vjwswVBde64/bsDl99nXPhkHGK/zEG/4Wpjkd5x3jdLzp7L3lnOgar33b90hX3/FdxhjX6fDYd62b8RKvxiTtRzd+hym6xQ++Z6/TnPd9Lzd7H93mLT9wr/Q8vAum6wIfiim6zOdhlq7zI5ih2zzkf+6r87wHJuoin4RJusqXY4mu8yNYptu8xYfOpM7wLlilC3wolusyn4e1us4PYaVu89YxEIt1nvfFbF3i0zBX1/gmzNNNfhULdWwxELtigS7ydzBeV/g/mG5NylsORH7QQMzQNT50sOvr0pCBuObjAzFLx9YDcRHm6iZ/8En30pltB2I9luradgMxZnvX39E1edCwgRinC9zEGF0aPhBtrE+f7RqIE7FBt3lo90Cs1Xk+FQvNr/FdWKBbvH3WM+sSn4F5aQ4/iFm6zT09nl8X+ATM1VW+BjN0g9/EYl3pNY5Jutg3EFMxKI3zVrmBGK0LfB+G6Q6fM2IgpugG/xcTdaZ/IP6AobrF3x0YiJyu8Y75gRipS/wSpurMDtYGm9M68+lYo2v80U8NxKiR7suf28l9dYcP3XkgCrrCj2NCGufbd7UmafzT9ghLXL/OD2GZbvMWn/Fe5mR4TwzVJf4RNqT14euxWTf5BazVHe4Zbb90gQ/FKl3ms7Bc1/hOrNEt3oSVOrObtfnsQDTcq85f/pxzosv8MObpDq8rOB+6sPtAHPb5gSim+bzlF+1Xaj5krDOgY8+B6PvyQJR0hfN7DcQKXeKt9rbXaZx32Mc6p3G+/CsDMVZ3eMxXB2KjLuw3EC+iozPj3RfrdIVXop3m8yH7D8RqXfzaQJyElq5yYcJATNvJs/HNBw5ERRcPsi+YqWOi79o3BqKa+hB7MWkgJqc5Rw7EJZMHoqwLR1lDhK7zI8jqNm9x9EAM1hneCxld4tOR1zW+EyXd4jdR1HHMQHRjrM7zvhilS3w6Juga346CbnF+ykDM0UX+HTq6yf3HWoc0zkvQ0m0+5Fv2VFf4BmR3Np+/8G37mO7FXzjOexlv8FHfsSa6xku/6746M9X+oKqrvO/x9mUnzft+z16k5rXTrH/qEwfiiO/7vK7x9JPsu27wztMHYpEu8S8xJz0Pl0/2brrGK1HTbe76wUDM1yU+ExPSHG6iqDM/HIhvYJEu8+9QT/1jv7eYn56Hf3+Kcd3hX//UOqdrnqoxVrf4uNOtVRqfNRBXo5bWlj96hmcynucXsDz1z32HzvTOaX7V2T/Ld003+Zqz/Ztu87fP8X3UVb4cZV3ne1DSLX4fFZ2Z7fxgmi7xaZisa3zYL/2+7WI+f+lXvhu6xLvO8duky/wQJuk4dyCOxnhd4YcxUbd58a+dz9T89/OcW52fa39rzoauXuTvETa4b+Fi97zEs6Xr8Ih5fkt1mQ+5xXnQmTsH4k9Yots8+V5/C3QsH4htHnA/XeO/Yp5u8S8e9Pugm3zHCmdslPkPDcQ/MFbnH/bbgKJu8DMta6WrT/jOYoXPdvjMp5wH44W/D8T5mK4zTw/EPpiqS3wCsrrCF2GwrvMjGKXbvPVqZ0/n+evI6DKfh0jz+R6sS8/P72Ojzjxjv9DRJT4NbV3jO7E6zedNaOnMs35DnrM+rtk=
*/
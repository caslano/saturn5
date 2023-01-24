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
tE85mqVUydUqy6EpkxWdAe2kHGNd6u4qVWwCydA8wLEo9RypNB51dBENfCur+aZsm0W9IxkUPeKxdrvQ1Kb/B1xTZ6+FVHkh8MAaHvi5havvbBch0Eioo5KJEIpKbabv6oFOpVqzTaog4+9nYX6qqHdURnB1SFvlGmE9XjRfFFGCYS0QViBoycOwHUqDZptB5RW5oJhkx1ow2gUtRztqqkD5yi7AE7MLArd9qJeRCBD/LuiBWvVFMGUCtb+fWDx5rBfs+uB9ki5XZkzb1MH6f3jIue61D9rPdYvuz7G4b4EZ7w5ZWVZFKo5FPcTB0BIM8UbD2ZCkD7+pH3RmGvxmbpBpENRg1e71YoyF1futt/z8oK29MOR517drrB2AWS9ayOo0DjRBcxSECPd2wXXvms5Qfc7cIN7QkOrJdYLqcXVx/v7mFe9Ki643Ovdd0Md6GUIsJszIHutAm0c9UAzdKNAjlRb/2C0U28Jja0WuLKyWwjiqZL0ppt4vpsEU0+AX02iKafSLUU0xqimGY1R2iLNX8CKA7GH6qG4XCKDK4S6lSYn6/ON+HF3vI9LRZW08kS3wslepz55jsZSzgCxlcg6iFd9zPltSErBljRFeo44fSTiWG4zADertQywAibxgg0tx1yAmL2gHa0R1lu8JBFLTYWq+ILCnVRSHpsN40gFxn3SxCGTDVbiMmCxxI8+3KCbagGuO5sqHT3cB
*/
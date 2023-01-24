/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>
#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std_array_size<seq_type>::value;
                typedef std_array_iterator<Sequence, size> type;

                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
hsiGyaHLTKm9l9Mvk5+c+OCvH4OpE1VBm8FgmL8CkSj548kWGEFXsyqUZHbdY3Ao4PRu7lLl7LnxsRYL24SIpxCm1McXLWbaCc0zex56oibD16tVBXCb0fPkE3u9W+FVqEdOAvOY3FOPYYu2FR+SLkY8Haaa641lN+laDeTHyhy+OjO00u2L7pTfEkftPsj0DqNclBiZXnZ1B8S7epRAaLLSvCNgDBMtehHR7QOKVKmR80ElqgfGDTueFc/TEFmqDf7+HEh436IyQCodLNQRTJ41HtRZ0JwjymBykZFO2HEXQuMWIhCH71+EzYJ/doLmFDMhqLoaZFyPjdA705nYUfHjtlh0wp2JwuxoPrWVRm5uO99i17O8DG9LUMpq5puOsmOd/qm5uAw/SUcYtI18amws9ngOMuwOIdtBfoic91dNPo324go1Xz0lYKNUtSC/mI7e8e1YdtJSElxjij/O9iYdz9IAqcWmlyzT1LfHB7wtvcGCUqNXq8+q1WdihXnRWD76dhnLb6dk3NJq6kRctPSZPPxrM9gzTjSMEu67HbJzmfYuwu8IFQpTriZl1KWFlUBFT8L2z+T2uPe3Kq0M5Mj8nE/y/q+fMyDP/JzD/WO0mqv+8/vTvEvM/MwVWoB3g5OykmFORzHlW32NDi5wMNwo4xjsyJ/w4nA17SW7ZtR64VTqvdfEnzNfk/O/W9rR0dUmr7yzSvzld1wl
*/
/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply
                : mpl::int_
                    <
                        std_array_size
                        <
                            typename remove_const<Sequence>::type
                        >::value
                    >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
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
*/
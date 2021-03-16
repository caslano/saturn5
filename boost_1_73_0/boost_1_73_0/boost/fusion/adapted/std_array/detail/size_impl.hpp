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
nQDnKlk+WG+wQWBDwErBysBqwaJga8EeBevtUayfR7HCu4NlwSnBqdvDmm2Mc6ZGvv0s/Z0gr/sFtUgbbrE4dR6GuYPbtWvCr5NTn6d8JXmycHBOcHZwVmQvhyFLwi1be6/mg8a29n6C7Kqv/auLKL+HK46HR3zpXzWUloPGRW/jAMvR89XRza607erSCnafXevhHb7TbTvc6NjhNcsOEdoh1Hw+uiwc04uHVweawuGYRm75jXAs+yA/tL1d3nU=
*/
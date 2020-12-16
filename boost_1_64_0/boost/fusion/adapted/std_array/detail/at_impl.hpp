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
l/cAmz+tC3CvfcCpD2i/Zz7/A/sA6QJ+ew9AByD+H8qMeH8ICy7y/dbx/29c/j/W40fvmS//dI9/icNvi/f6l/v83+7y1eNf7PDx9/CVn709zv6f5+vj94z3cl//6P4Cfv6Zbh4vL07+T/PxuPj/hIfHwcNSDkl7OHKgqA5DoXXteHZx7OiTuefW23oCiYf6Qx07fh1+jvb8C6cOOW246UFNDjOcKCesa3oGgzuHlRBSuihQJq4c9THWkePHf8WB80uc981rnHkSZ1uxv++W2+k07/E9gbtbAlu9wUB8ZSUo/areEqBKiXH1fCetRXxxEhrdl98c4myeeN7dHGoQy/un83hRrcW61OGjWyfE033ffK3n879854SYiuPU2lvfFHp7yEaWmvv1s2fjvW8+lM+i/iKpPZRcTsU86iyhto5Dh3U/oo5wkP77psvP3r+9UqV2g3t3V1Kqdsffx7mKb+W3hFb5UX31q+WNQpyq+FQ9n9pQnQe9g+RTl4/vIHEuWnoIatEE75vXYeSYuDe+RuDxDSpiUK5kkBU9unfz8ltUG2YuauPe3aJi9j1ds/a6XtWZe5O5R8w9Ze5FeZqMsrA+Mfu2rE1nV723ntrV+dOpyaqkfnoL2aczaEi2FCcv3KFCPZ66RQXT1ZkJ3zffkJPTOXXEz9C5ne6knO+hQD/60rN0mvNNqPAJNtXN3tGpa8RO74+8b97iYZI7QptyTnnvBomJ3jcuP1IrVwjtitZ6f4T/EL9vmjyakBm/cFOrctHsfJnd48phTu+br3hUmFfArLRnQ4vo2HQn6uX3WrYXMsMvz943VR419Ukt3aMyh/dNyp+HsOJBthmjXtqD1606oUzqZiusCYHNGNl66X0m1oEX78hqf/1Ah9SDVs9R5MaqqnldlfzkMumFSydgPjA/2Rih1ifXSJTQE8nVCzd9tHd9cNencf+emnaq7oObh7I650Rip3UjVe+fbwIV9+4W4tjKXpO6IC7nexedu8hAe0V7xCbrIh7+rNmNeze7eCnnA9PlsZH+6XQDV/1IhTeQ2ed6CyAcbJ+++Ujd0gWf67V3795jT/zZC9pf1fuhXeWUCbgfmILHRpjSNa798CYnc/BUPe3psfrno5zoa9d/F8u1qOd5T0e7pZPzOHffGWw5pWboXk50TzW2ylcNul5yA1u7ImJKPGN8qviLmu17jPeB+UGYoXZCYomrK6Op55rmjoZ7LDRRz1j183QL1UFBPdXQ041yVLR0aKjoXu6V8l68E9Wy431c3iTgLUo9Q8dgQGZesX1ZR3aMzvd4a/fuyXVh/rh08SuiEkze/8CkPJroQfKL62jdroVKMPO+m3UDemt2hYIT3Y9jdWK+J+1eU99NqepzRVfubrqiwDkV2pSKPN8hrpR6pt0eMw0+sPrSkznqvrl/wx+EHxifRwpDRB2GDtLbW4oacMT+EbOO4SiDo4JMHMiFQy48292b9gfmDf6+VEPJIf+SfGR+ekWe5Q0a9FxU4XTj7MFNbpy/3ufcMa+q7rKquhM5XX/Pt9MeKKSeg9NH6im43nxV39/TXVVVFO0foUi7x576/T//buF/42ahyT4y35Fb2ad0JVcnt0S2IN1qPCycdd4hYy45C8lXm4yxAr6QsVO+un94nn5blvaP8vRnZeHiHNgd572ebKiH0j0c9VCnXeb8I5O9ovfK9USDVfjuDnJ5mvGnVtkfk7vfWmOX3d+tn7KiOXHJh6d3G4PF42/LJGSI9eDCGnnq7q1m8H6+io9M8mK+ymz9xhz9eoYuy8aTubh/i/5ZsX9K31wqSfvn31RDj5TsV3OUkA9cq+4/OHpSGOjJTVzur+u+ldmV9WT+lko=
*/
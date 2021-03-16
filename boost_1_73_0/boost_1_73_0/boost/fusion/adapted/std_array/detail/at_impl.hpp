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
ek+OHAjGf627LvWROL5rCpBTfUSZ9WN/xI/fNpiMmtKiGU6+RfilRk2+/kipKSJiKjrixVsqIuJbG9RaM/ip8EqyhiZe5hVjwFrI8jEpPxh/MNfvJPtzsifM432kidH04mPKlHWNgC7GxxhDdX6lgPyfLrdjv3ZnhvJrd4pyPgNsDth9YIvAHgF7HGwb2A6w/wZ7D+xjsE/BuENLsmm6YolPR4vXFDaGYx3MsmgWs3GZGM/J7dnwAW985YEiLnQ=
*/
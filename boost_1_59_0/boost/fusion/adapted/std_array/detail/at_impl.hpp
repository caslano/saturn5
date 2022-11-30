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
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
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_31122005_1642)
#define BOOST_FUSION_AT_IMPL_31122005_1642

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template <>
        struct at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<Sequence, N>::type type;
                
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

/* at_impl.hpp
vxT7Qe5J55iI+Ru7E3XjE9n91OuZzXbSW8Jwn51BGiXaV1MvQG/C1pwW+1qrDaEoovzejK1XqQvV81MX1vE/sccug59Yjc3+L7G5ArOKo2WuDQskDmrqFIvkIZ1W65slV8v53tH41zgYR8yUSZm+Qtw4UxfnMwuK2qtsbB6Lg+PFfTguXQpja/Tk/Ag1axxTt3D6Et7m3Td+FC0nLPq7MlbkoyerMx1Wzf0h+g260b/VKTLC
*/
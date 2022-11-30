/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_27122005_1241)
#define BOOST_FUSION_AT_IMPL_27122005_1241

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<boost_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
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
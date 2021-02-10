/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM)
#define BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<nview_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::begin<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif


/* begin_impl.hpp
t7NRPLy8Gffj0WQMKZcy4ekvyEkqvUlWqCX4FkOvmK0o/VQkorLiNzIHfc+Tu4p5JFKNXTstuIFOUuc5mhA2OD+9PKgSyyQMdl/FlRYZdFKtVOXM8XkQUBFq6iiviFjGHT8HCmDdFv2NsYKCJ5QUSYMz3dSLDXzcqaaz//WyJdJrYbRp7ySBTiWbxV4p0HnDuT9glFGdtn1Q3kET3C5obhD3CflbSQsVXTKfgH/L6mPenu75u/DAP1BLAwQKAAAACAAtZ0pSD5U/KiwEAAD3CAAAGAAJAGN1cmwtbWFzdGVyL2xpYi9nZXRlbnYuY1VUBQABtkgkYK1Vf2/bRgz935+CS4DWDjQ7TYulrZNuhtN1xrokiJMZwTIIZ4m2rpPujLuTHa/pd9+jJDtJsSHAUBm2JB75SD7+cG/v210t2qMnr7j6xrhwryzOnf3ESfh37Ti+o/oDqxvcn3LSo3uTu7hDT5vcUbsyiRsvR/Icx085upHY5KcnljexPEICM7Ec2sXa6XkWqD3s0Is3b17T93Swf7Af0YkymnMaBzZTdvOIjtJK8lOmbm+7nt9FxIFU3m2gLjPtydtZWCnHhOdcJ2w8p6Q8pewTp6d40YZCxjTTOdPw7Px6dPoholWmk0xA1rYkn9kyTylTSybH
*/
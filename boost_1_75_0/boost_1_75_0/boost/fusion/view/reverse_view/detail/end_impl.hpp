/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07202005_0851)
#define FUSION_END_IMPL_07202005_0851

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::first_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
hdJDdq4UNTifAW1fydxuBrKLte5m/6MHVT5s+2aDFih1APwRngeo/IqJaL1qB1Isd6jMf3Ipz2St7tqwVEtYCGAZUXkE+Hv3p+/bRprK2sdlv8ceheLtX6E/466wAYm6hU9ERys0+9KS1nWHpS7pTE8rIdG0bfMVHqVqZKuND/9Zn2hIoT8Oa7bdBrxt/s432dugUfumSuRv/I3Iolr/5j2BoQ8iX5B/NOW8+XXQzCf400J+drLGolgAh70Lab30wdmp75T741cy35aNRoYkV6/lxGc9OV4E/vY4U/fIVbmrGp5gLmdM6TXIL8kr0czV+dOMLpnCPDrxfN3j06c/T047Dzh9C/DbXWAk7713crcWXzfofnriCb+DRykyK+Z/HikmnNV/ccoSu+ePaUmMuHPbrGnQO5aFwuPCBUGsOX35+p8r97tLDphvoscyWlS6OQ9fDlir1b9MMMv56Gr/F7voq8YUOSLhldRp/l6W8xMPxftzRn8/pDejQs51VbE7Co8CpcudL8htObz69kP59iW9QcLZI7c8ghLWLHV7HMcnK3YEoMeuJ278wnZUOgce+aCjUcrChbPiciy1Zl5/oe2ApqjVWZpS/t3DTyyZrZs6cr9GX3QAU4Gl93rylb20DGNadZTe8yWRYMAzyIug359She1zCldsLZ+6dC83vavJWT4gMZO6f2NqzGyMGzH9F+MlEkDo96g1hVwY
*/
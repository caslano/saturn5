/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_09172005_1156)
#define FUSION_ADVANCE_IMPL_09172005_1156

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct advance_impl;

        template <>
        struct advance_impl<vector_iterator_tag>
        {
            template <typename Iterator, typename N>
            struct apply
            {
                typedef typename Iterator::index index;
                typedef typename Iterator::vector vector;
                typedef vector_iterator<vector, index::value+N::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
EqjUuYUXeXs5Bk7b/gbKPYNLe9OiJaRFb73CznDg0f4TEnJLthu6RVxVPnOgE4g4QCU8Rmt86RdRcEyxS2q+Ejr7Bk1fqJb4Bb8Dfu5vg3uDUzsKxfRog7SS3BS70bixNTFaq65xJS+YLlhr44pZWdTbSA7OEV5B1yN8qKaMIqGQoSAztS/nqt62P4YvjqLcv9Jwv4y9o5N9vqB5sYoUJgFNDF+Doe38M0KsO2VeGNKUg3WHlLGbbh7TcCijm7/g5pcUaS9T+UR5QU2z4MGlMKjDT7N9Kw4xKebSxAe769l1WXmpB9sR21cPAtp151RGAX6r6RgclSLyT7TApjL/MvyX293nVPS3DCCIVMikla1Puvgu+K7fd9/NRPBOiVvbjO6KK9NJBZuYshAPb/oxZPYA8S+qwlfTEsniVBxlZ2C/dJBXL3yXHXV491TkNs1iYvatjvseRUTrwnkSc1gsaetvrzbRNoLD7cO51p36hw3YIDkLJMcQKtYhKtr01BjejxFTPTsJWBHE0TTWLpyASUIy75gUPixrtZ/d9xnBvjmPoqjnqqVyX2J4pg==
*/
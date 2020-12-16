/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_07202005_0857)
#define FUSION_PRIOR_IMPL_07202005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct prior_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename next_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* prior_impl.hpp
2TNtEgYbDHACpLV95u1CttEAIWZb/A/SUZubDDCY9VdqydSDwhxbDTCOxV3N2yoLjSeaM2JD0ei5bTSXX9Y+DG2V/nYeYUG0UczSLzn0rzD3Njw+KNJmZPi1Oo31LwYYz8w6etUUYb6dBgiCtH1Z8qWguF0GaBUrbfn6MnE0R/sMMCtGWrDr8V40LgcN9D2G4Wj3qncsS22iLWXmGrEmvTDPIfU4XcAAAxVpI2/uvkHjeVg9zvObAfazuMcD91Gc/6iB3hc7Ai1uaAeqD44boCxIyzsmVSVhTrSqzE4s2ZCB2kTLyIye6UYLop1gNjfuXCWyE9FxW1Z0r0b1obVmed5bcHYs9XcKz8uZHcqz8pYw+xkDlAJp7d93e0/jgjaNWeL1kdMo7qwBDMz+43iXnmpHu8qsuqtRFVq7v+O5MMtlRd0TL4T5zhvgFxbXu+/mC5RL0ACOGGmvV15qQP1dMkAF1mbMJ/suYaHLuL2n+Goj0b6s6D6YcrmJBtKONVuSieLQijLr5XYME2a7ZYAmMdLijWWyCNPdNUBKg7SfD00OUn2fDPQbY6PQDtZ1FBTm/UvmOTpZnjowYp7SeJ5etKLMeJ5BNMyTjOcZiDXC4ezS6i1MWgAQeXfRt0bKc4yyVeaJ5i9ghMUR86BZH5SbJMwdb6R3rY5FKxcIXxHmK2iEMcxKbj4aI8yRYITlirTPI2a0EeYsbIR+KaW1WaTECrOVMNI11w9oVmPP98KCaG2Z1VEmbKc2SxphB7PEF3/WolxKGaE1syltR/1J44KWSpFWvf6zH4XpyhihKYvb8D6/VZgHLTez2d1/70DjidaOWedhb7YJs5c1Qgtm5kHrb9N4ool5H4dW6eHpXsJCaJkjNh4te9oaNYVBOSOd609Ak7/JijVomA2tJDP6jT80t4YF0GKZ8XdBBdHSMztqatOOatCIC2sYlMcxY8bHzI32R2QtTUTrf+D+fymXqka4HCPt96QCtAZd3xnhSWTbnITWNUP+4TS39Yxwilmt7FvukzU2Qi5mWxvVykvz3twId5llyjO4BeXS1gibmBU4+uoYxXUywlqQdv7dEdlfZyOsUKRVObGzpTBvVyP8wOI6HfcVEuboZoQAsxanTNOF2bvj9scskGEjzVEALRjpbzLaN0lPKU7X0wirQdpz1/OTNLdoLVJJu921zzKqfQBuDzHS3N082b/aztjgYCMsiNgUZWds0qd7hYTphhthT6w02NWukrDAaCN0A2kDnWv6CnOMMcItZnEPlicJc3mi4+Z3nr9NWAjtXKT2qWgba8ydIMw+zgjzY6T9659SV5h7Io4nizvwtNR/KJfJRpjAbPiVTTepzam4rbA25w5L/ET1TTfCX8yyD1qsCPN4cT/I2uw5rkll6m92dC6jNrWoQeM510jfWZ6GduSOL1YYLDCCP420qY1/8wmzrTJCutTSsua7s0xYeKMRIK20eT3TPaRx2YP1sbiCk78/QXkeNsLsWGlTkuoaqfZjRujD8lRWFrokLHjSCC1BWt5iDfNQm6eMUJwZVKjTksYMrV5KaTs2H6lH9QWN0J3FTe9SsIcwP1owhTSbt2RnyvMqrmtmoTR5p1Mut40wjNW+IDGwV5jvsRHuR+Kmo12xrK5NbT43QjOQ5n3TvaEw+wsj3GQW/vL9dervpRGup5L2e40mdhqz90a4xuzhmcevaHv4xwgvFGmfD1QrQHFggsPMtt8rMlWYLtYEK0Ha2zS1cggLoc2JkXZiQ85VNNapTdCNxTWunakZjQuamfVX5lMlmiNIY4IxLG5qo60pKQ5tDrP0Wex/U31pTVCMtVkipvYLyjOdCb5jcWk2Nqe160hvgs6RGmY=
*/
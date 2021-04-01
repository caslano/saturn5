/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM)
#define FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM

namespace boost { namespace fusion
{
    struct single_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef mpl::int_<1> type;
            };
        };
    }
}}

#endif



/* size_impl.hpp
8IhuJvGdqTvUowhNjW/j2x5lZYS7yBIoJN/A/jlsNrIQSspxpAxYNh3+o4bqZS7D5AEQ9pTxgh8QQf1EWR3AcA9crFDImKJCoq4NC1B0RjTJt9leXmbU5zHtfZhvoIyWImSuVpAmVVptQTgXsAtfzZUUpcK35OloHhG3XThpopDc5nrhmwi2NJWcsxYVpPWckPmnEsOksgKG+Pq5esBQQ8wEtPFJoAVK8XW3WadQnlOLq2IGlcgWnRMgcfc8NCVjS9v5RwFNN+HNBA2AeK3YGz5zk+0cGsVplefym/FkJxqPh4H0dSqazTcrAXNLUBYhtyl/Bo1/uNzU7oCsXTUklrem1HvwLsGtd/czHNRBZI+ZPWSrV52gowtuwMsLoDylhXmeAijEkl66NoucHi/JI0kwqGdHPj9mtee2jzzSe/rawt0f4VDH8E05NmEaMcFQmbzxO3KpbU6PTimXuwpnKxb7Ptw+hKbBooJGCnjJeq2VGFOAO2JfgZ37GaL95lGO0kb0mVsqr/42erYMDDKRfTet0PFycUIcL5ocCNQALEG7GLzKCK3gqarRXw==
*/
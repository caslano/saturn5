/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM)
#define BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
DXQldq8lWxE3Gyhvruc0gPzyeNtAPXPHp96FKgN1A4PcVaHdXpLtQX2nd1eomVurd2Vq02qi8ogsvUHyV+CcKuwicM6ToBeQlBNTaxRP4f8ZfNkBvDRBlx2Ayy6wZTfQ0ghZmgFLE1wpgBW5rzyMC5T8tbBKcZe2BMqi+KrI3t4ntH8BnzTO1zPatob9uMjAXM+k1Or247PJAfWsyq13P16ZjFDPrMoN9mOXyw8NDDdYtoKT8oU/DWr3o/9F6HZPFnvC3D0V9OV4t5LR3oC3QrY/A3y/RLhy5FsnXBkCbswF+3lJ7jLuV7ukwTyXPc2hirrALq5lINn0uip/krc2spczsjPUnVt+DUM9XGwNE4SJuK3BH/iyibit0ZjZ8LUjWM9wrOVfNQkJ1fshvAhM/TvXp8zi+pH3gGttU78eaqOhYdbQXUC+cunOJLWpiV/K3jfY6fW9OBDn50p9QlldMg7w9YPteY94853LofZPTZ0nMXmAqTY/dAdU6OBlOZeRFY3SlznyhWFKP/eDBP42Vr6JK65YTkz3qHKd5shQN57Oyzth0yamBPa/H2xbW+wx+UsPYUFHMXN5EKgd1G6w5+wnu7aLHSQAATaagoeL7SvnWRKZ65ZH+LC5lg0PF5lbIsLyxeo4WdEEX48v
*/
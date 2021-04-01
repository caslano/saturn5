/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09242011_1744)
#define BOOST_FUSION_IS_VIEW_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
wPuUddm9kILb9n8H/yoAtPElAr4czbeAsjHXsT8vM0gCwIMR/WTsUIN2IpLvR39BbAs9WL8TrnNDsVOMFoxLPFWQsxxd7Ksl3dGZghqWyGNNA0a4Z9FIrUSP+/Ke0eDGi8htPAMsHhLAFfJhIhkKVVvntcSqRxnI+o/zfwGhm5W4bPiICpwlKZrFdV9ap8FjgjdRFmrxfN3uY6RWg+7/eTfn94vZMSP90Oa9ThtXBBfpzmxpXaKytAV4eroQjDVJ21leQ4z4kfTN8b72ZhnQjd1sJvuZ32XFtPGKKWNO+jbm3c9jlfkFkk/Sr9ICEW8SWcVSt0qe+KBAeiXT6GXcg8RDxmXSkAljFuS89MRZ/TdZWPvNREfRDT53++k1ylX5xBBdpU7ieK0W3Yz/Ui/afE+p0A18Tua1eEG+BqlsbXCjRdNr0udNFoxSklkKDwSuKtTCyC8kSkxCwlJyShdRi4/i1zHjPJI4D7wfQxZk9HcOWD+Weuj0kgIOoCbQ3Ya3vG9Smpmlng7a00OxJea05SPdGvZijU93jTZQLlNTisCTg3XkpipX9jVHRg==
*/
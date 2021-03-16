/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_03202006_0048)
#define BOOST_FUSION_IS_VIEW_IMPL_03202006_0048

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
8bKk7uPGgN6GEODtBnN19ztFlmS/Tg2w/Tw9wHYz4ffKckaA1/zQOSmaWbL8tSxLApxDvViWtOZmjiz36ueSMpsCZTZFKYuJwKYAmwPsZ8BWALsD2Fpg64D9DthrwN4B9i6w48C+BkYOH8Z6Wgb7Sh71U3buSX0ku32fqZfrM/WUjQpvHeVbcDp4/LokZ8e+GEmuKK6cV1pVVbqwWElMiRJlk+AwKsp+YcIaU+/3BIuv6f2uc1RLF0IJlw4cW04=
*/
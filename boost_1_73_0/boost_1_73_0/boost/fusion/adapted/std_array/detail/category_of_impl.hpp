/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700

#include <boost/config/no_tr1/utility.hpp>

namespace boost { namespace fusion { 

    struct std_array_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_array_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
zqODHOleqcnSzfef5Uj3eJp3LxJpThBp3kVsGE5wltZ3tmd258Z9n+x2eMRdH0iMxfizANmBLs5N1O+szq31KaqMw1dJGYevEi0ja3TF9+qMrjbSzfKtvEC2j8a9MpoxWBNlxBhq/uY8Ru0c8Wn4zWTHk92iySiLPJfB2m0189V45KvxIm9MAZsOVgU2H4zkNZlPV6xw8pSpwTLbdDYh/7aTQf+2C+HYJ5TFQs27GwZzM2qgpV10lOwOfrQkJrg=
*/
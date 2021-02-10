/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_27122005_1044)
#define BOOST_FUSION_CATEGORY_OF_IMPL_27122005_1044

#include <boost/fusion/support/config.hpp>
#include <boost/config/no_tr1/utility.hpp>

namespace boost { namespace fusion { 

    struct boost_array_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<boost_array_tag>
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
p3oQG3XoRpOVuO40IRXSejPSgwha84Mt9c8ugtPYn0+9B+iQ1rhp7ZFY038bKtVznE3r0rb0g/XDcgpmJuJ+c/2Z+8mf+cnCcqsbspXGHnnJZTQHU7AVUYXnqjRMvDT4ajx6seeBO4sDPBQ+RT8nDz3UDo7G+h9QSwMECgAAAAgALWdKUhurTJRCBAAAXgkAADcACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RJTUVWQUxVRV9MQVJHRS4zVVQFAAG2SCRgrVRtb5tIEP7Orxj5PtSOCLZjRUmuueqoQxqujkGGtGfJElrDEPaEWZdd4liX++83CzhO0lbJh2LZu6xnnmdenllr0YGDX/YYloaDV5+o/kb00Lpz8kvxD8bqxw5R9ADNhxwXtL6Bqg97r4eoB2/yeoBu7RW1XOd6H0VvoFvoIPVPXzsvIr2lk8az9R+L9bbkt5mC7rgHw7OzUziEo8Hw1IQLVnDMIVBYLLG8NeE8qU/+zNj9vSXxgwmogOXWM8Aw4xKkSNWGlQi0z3mMhcQEmIQEZVzyJb3wAlSGkPIcYez5c3f6yYRNxuOsxdmKCmQmqjyBjN0hlBgjv2tg1qxUIFJCIPyES0WYleKisIgeQWG5ki2MDoLl
*/
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
JKkERaSPTQSeNEtRT3XYVOwHx3pcuii1zQMBd2ov3VYlqYVsI+lYT4gSMahJr9m+PC/BkuWNdhzdHF7U1+H55aQu42I121PnJXAMERYfxuZAvQEXnEf2DEhc8Xmiqey6mA0EVj9+uJ2EZM0kULHPG0M6uFmNzhTwzbb4QWAX6fEq2VPdmKXdmBOc13VsxvWv6HoQMG06QWWTMX1TylH2wXLG9MuBzoahfjDrOZnK0Wzfq8Qk29TfJpskF9wMOaGFbaSciFbkhXDgJM6WfFFHQHOAIHnwjHy72nwm7JDZSBYm5D9sIJ+28RNPaHQA7Eivcc+G4Z/uGlRw9414MNkcmy4n3tVjmJwoK2zBA5L4ctZLzU3s1S77etWSXHdeiyI+qlovlyshSiVkGjKXdWqYQ9kN4C51AJ/1a/NtLP0j7dMX9QqW1q+W7LOLx4jP9F5fmgSYejVNd9JGj8iack28uHTCOZKlHoWLrl3ysN1SRQyIEKtjWK1ZhGxxDzROyy5KQkHK8h+ShHMJ7qXEOJ9wDYxzX5UQJODLGLepOEmGEWo9iRGAxl/7Kkr8UvIO88QiOgLgyPSHLYR8n+u+lc8g29TDk4z8zdl5PmdlXNthjpDd60iTqMatQxLM7iOnDcG2ah6DmqnAfhOHcBRESn/5ED95MwxeCV9e1lEAzPjyXCefjaTVv0pmzMQgbqSiYFB9NYqWHO6rUQTdcXV7
*/
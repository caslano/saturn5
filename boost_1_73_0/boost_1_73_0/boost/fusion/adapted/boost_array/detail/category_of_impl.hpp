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
7U2lY5P1E+J6BSlm7tbXRYu8grvtXsFgZIxZYSlrsfekrjDdc2aVZqB5feQQefSKOiJ3Ub06In7k9ZY0+Gfn4QJhnIdhYZyH5N5i5yGNEtl5+KZw7rqmwL3OtZVHBDsPVffowZwJvYc9MKvKc6Y7xN2yVgLvYS+simZb9wVxhxQLs6JS8IpK4z4coKqMEpQGh/05llq2Rnra2+G4SF0dqRyOzjtc6y97mcWQriw6Xqsaw6/RWsVOzrWKHR1VU30=
*/
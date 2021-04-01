/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940)
#define BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_tuple_tag>
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
qsPvG1PJUR4hpGuwunnsAkc4Y6/j/cZxuv8o2f5K28DzEQMOXfFzl65R2dKFBDd09YsQeEd0vnM4+mK0uxqeyK/wUfZUTzapNky1Pq5NMgkcvLz5aa9HshXfBjBg3ksbN15rLhxiloiMlZuvaRhFkshfXV0n0eXIfCRRbe0516prOOO6R7fmXC/3N5JgVO3krsnANPn4IWvtHwpDueQ4y5H6o3nOa9BdGR+8JOKLKsy+J9teUBFKP5zXLVe7e+RkEL93dhN7DHU2mwzk7X++2jtujVMWU5MvO9sVSR0rmCKnWAZWOcyZt7zDa0TU91VMfOEuKA3nrFA95rNTJm188EAwKArHU/ivBYYIDCEBFNCbA1//J90XnH7QVccRka7V2+pztXvIGbmMTPGtKRqDSQ/B/QgsWKgxACb0Tl268EPxCXfyZ4pLCtW9X63xzDir5y0jKfCwCuI/7slb+OykbnHDlv6oTkHlGAPwYCe4GNwJSpsCIFSXg5otI5JxwmTx1bO6tm9YoKN+LJqhpINhjQuwB9sXqi/ecn2hO2/6xPmB2XAEWGDVmG6dew==
*/
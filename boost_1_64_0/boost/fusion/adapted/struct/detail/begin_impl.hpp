/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };

    template <>
    struct begin_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
Kyc8fS42vJw2PLBUp2qLvcwX03ZfH+ZFymmwlHmEvJRICz3MumHX36bCi1De9rZ6gGlczDMjC+EyUf+bPGdNI5TlTlW6bKJOm25D8jt7mayONW14tQKfB4dKmVjjU9qwzXoYja5nkREtNofLiEYtrOVBWRlrq5fW+kE96/Y6mXQUz6vzvMVNcIn95WJSeJpZJ2tNr0v6QjJsqlkn8YzvUD3LDUtbTgPKH59+f+eCw6U8bWkLZBQVZ4sO3Ch1o8Y0/WSLvSyXsnxo55OyVdV/PjPtQeXwOWUodcfhGXVINbb1HzPZJ5n9jUM3TTAjmB3SyVZglhdWxp3yuSCsfJrTHt5C1u/L4UaIjaCXQ+WTNj7xPHl7PdKy8zNy82rX/VmT/ueb2/WvfdqK7azYbAcndKTMsMiR81UepmFYY2+LVUzr5zyvswdupOj/fsVMq7IqpxMadTqpJ85q60aNIWZYdAGeavCZ0g9mvscSq+0n1MITX9Xr19O72dO+oiHvEjLtn8KNFlsWrzrTnlNYHIy+jI9U2lV9NXXjZ2cXKbmp8jR6q3uekmlvMI15ulDal7T7vzjzlBuIRmcbx1Vmnljv/Y48JUfIU6o9T7Z63qYRx1w8w3Wt+BMbAy5pVdqlwmSqu47NpBodmyxrpt1pOyqAINWzgD2NbAfMD/whO6E2W87fQpOirdyXMC+dJN/8bWe0o+TXzLyoFqC6pOj7S9UWqafLGl/cMbSxy/gugUsWm2tmfBb5cHjvuVMdZcF+pqmKaXqVaWryuiNNhdD9HoXOb7f2lGBPk1NnZCjdA7uq7zCFoXWKtkfaquHG42+lKj1mGQ9T+cnIstoLGcI8zaNdRHZZSufET4gwrkrCGJSG3U8ovsa+Z1YuLCNmZmDMURiQWVRxZP2T1MWm9mulnmz5XPZj08bp302AquWMadkOHWwHmY7zWLZj4F7Gf+JVOgzZeEU17dWjpo20jhgv3yPbgVXfmhFqBwgqFD/tWh1r2vI+hedsx4ucZ/yzinXm8yLLFMZvzmXaqvjThpRMnZpdxOdJ5vPhVG4aki+eU9TzMVLi2WE6T9MGF00bg9GClo9/0+kyJjrsVczjG7mJ+ZgPN0nq6BvKf0bP3LSRyYOHDRufOGFCtPJmkEUvdLqLfOnEsZCzHQUd8iX+EPLlFvWvumeo0n2DR6e7yiXdaWOHRqXPOt2ii7jfW/ax03x7PlRZt7enuac5lnHkj+/3gZPMvDS220O12lZUfmQQ1DK8XHrU6Phr8qZ+n82a2etle9oczOc4NwcuFeWy+61QuSADWVl1mb/GxZrpZv6sZaHS49nmSA/b6Tqm50TOFVqCFyE9Ae0/IxAQjam5GX2i6HtryvGC/mYfYJ8DKuFutcOvnqEs7Ta7eNhZ7sPG8W7jxVJGb6s0ZRXqXpaHN6KXy5yHsh2aNqcDabQtzPZwpp7LzSzJyHMfo7EP5lxG+SllH4rvId3l88PGQk694EWzamwZbsR7ONBMjy2+267y6bBNlYHswq9pC4PP7DYLi/hb5EF97/OO+d1axl1a6gLKo92HLDBN5MqOmjIuDQ1naurislrKuMzR95W7jCUrIoy71jnK+AQ8qwzlU79v63rclvCyVc/HmGWTF+QvOFbg81wVdrI598kogGb37OLsAlOPuHXMELleJJnpK8jNog5Qx7tl3eDaI9OJ9x2HtO9BHM/ib396l++bde3Jmrj5LBCSV5l43+o9hsLohPe4AH//8j0zjMWhuq68h+Rjb23HLZvjBpscMFrxvgz7GUlzH7EHtlOFqzINLc3F2VHIgZZ2e7UZwSDeEG0+0XaT+VxphWefGfpNccmU6Vjc5W9o59h8zt8=
*/
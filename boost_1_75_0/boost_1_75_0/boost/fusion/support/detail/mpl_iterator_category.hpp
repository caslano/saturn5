/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_ITERATOR_CATEGORY_07212005_0923)
#define FUSION_MPL_ITERATOR_CATEGORY_07212005_0923

namespace boost { namespace mpl 
{
    struct forward_iterator_tag;
    struct bidirectional_iterator_tag;
    struct random_access_iterator_tag;
}}

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;
}}

namespace boost { namespace fusion { namespace detail
{
    template <typename Category>
    struct mpl_iterator_category;
    
    template <>
    struct mpl_iterator_category<mpl::forward_iterator_tag>
    {
        typedef forward_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<mpl::bidirectional_iterator_tag>
    {
        typedef bidirectional_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<mpl::random_access_iterator_tag>
    {
        typedef random_access_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<forward_traversal_tag>
    {
        typedef forward_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<bidirectional_traversal_tag>
    {
        typedef bidirectional_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<random_access_traversal_tag>
    {
        typedef random_access_traversal_tag type;
    };
}}}

#endif

/* mpl_iterator_category.hpp
RZgm+EwM5f90jtX7+Z1jb/VHvwL6P8PPbtHpzaKB7qv8JtQd6bDIVrYrZow/wCwIsCX5bhaCKxn5qd+9pBKZQJ0Mqjnq4JcceotnGxU2Ogx6myG284PDONhdqTTjeiD+vm/hFqjev1zHzJvVAs8+bRW+GJVccsitEzdLj57chSf5ju76GC4gMXSGNusYgXKzQJxjOdqarjcLtaqmXYg6LYrNQQ0Wxaaj4OraJaj0uexSS0O/MMbSQS+oxTrmUblJUJfuFTmnK9m6r2T2zSQEddFcGfiu5FswIMXoLRiS1B2vYZHBdlulsxJZYODWBToyDTHiBfVDKiOcx7yG+pNm74M1qr+tUoPiya46i4Q2zPROQ98sPr0Y0fDdq8c5Y/Zm/8icXkW0n7/ANvj97L9Kc4qMiQd1O0/IV3PDtvIiXAxUEfMQqby4Sn0FWDeVF/38rkDYmvIi2A1UAf61oYyzUL8C2vWMAkS08dN3Cji0K0icEATaJKYXGRPG1NMxSH8BwsOa2m1wl9UlBUi8J+pp+l+djQbx7jDcnT/EbPp7S23P/mhHZpqGwi8WfhyWRF3vXnr0rKPuKCAe5VZkfFlya6332jRd8YBNoMA6k9pKFmpB3fENKqDoXDRS8eo9r+TMlhh2bGO49qLS1YhxqL0iUg5q5j8v+M17fbJhMMh9Cyk23aEfpaLpMPDcGdVZ+fcO7+j4uh0ExVImI8Re
*/
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
1/RL85meN3f2pXXTVB3j7zDLSR796GEr3wJIAF4riZJ02axaA0DyJ21A8noTZYJ4QsN0xKeACPm/5unt5mr9SCvBOtgieIgfVm1H1xyxZ/CQpgHLqpomYIaiboa1c6jpi5DWgG5WWFzV9FrTNosu55MQqKLQndo5XaTpBH5PEwKfKtbFvxs2+JTux50Ox26EaBQpV/AwjJc0G16FgIYADJEMtxAzE5ILYC453Dq8dAvbI4zO0qzAhTPkVQIeAirgtgiOI1q2nzWnwX1MR8X0Lu2+B+wDPuA4iWGH9NWNE4UwqkZNLgbFzexuI97tmtEc6fBalWhNZokHRhMEouhM8TbDmbFqlj9KV7ss1W2TO+yb6kIGAFibhsU8qxtEVvsds4zzJX0sg6rafefBR1E4UtOEm1i7WQPgC2r3i44begURLgKZsKYTYq74okzDYR2WrN4UBU+XUYG80K3xdu02DRVTCAwqrIEYrfKwoxSXv2z0u9K1JZPwTiJOLu8wAbWpsyvgXAcLII6kYwsi7ozNFq65YnBEfIPr4QBfWh33QoNlEGVaESGUIQYjEAAa9M3DWZEtROtZVNSTZTo8ELDg5IgNj/+7bmszuGsgb87utqUukOAv49Fq1HoGIDMDQRsWOlvSgi4yzJVw3JLO
*/
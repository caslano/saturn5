/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_0906)
#define FUSION_END_IMPL_05062005_0906

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category,last_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
wP7fX8CGMqdEQu+xonKJAvtQnNbghS5OlinirbDMNd7OLlK4B3UDq84yV5KqDNVbAyLXVntGwpyC34xaSwTpZ51xRYThRJBT5vjnEnCaYK9CDfzdJBczYRxaQ2OdQ15dnezWCcY+spd1sbWxGAA50P10fZDyB9ZaLC7N3KLYd5eEvU0Kul1GjlCbByCy+sv84BRVsLYcj4s+f+2Eqdoajd8S90hytW1Y7xD/URl+/r7vry1jfRH6P0NCBKITK5KjsIuE793Zoyz+zMC/MF9BWBsqX+zl3JQZR9+4iDagbTW1TVTZcwfYc3qtBb+ZTNMhzsH67IQw0BsrWN29Asmpz6rcMS0qkMtktgwcI/oJmpP1CD0LJql8LlkJS1SQNySJg0YadCjX0FveZfgQPpyHMapm7e84EBEFQiuvH7Whl2pU1735q0Hd5YrUt46osPm6OiVvsjBFGnZtPI3EY1MoelQhDbLGsj6/59yLL9UYKHSsud/ZFTV1WBfAg3FCYTCYOXHvZtOZrBFq7zXEbD/trJRV/Nbmgsg/eXsZgjnrvS3n3dUkb2g2UlKULA==
*/
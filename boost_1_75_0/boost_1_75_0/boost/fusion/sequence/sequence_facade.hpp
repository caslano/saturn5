/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_FACADE_09252006_1044)
#define FUSION_SEQUENCE_FACADE_09252006_1044

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct sequence_facade_tag;

    template <typename Derived, typename Category, typename IsView = mpl::false_>
    struct sequence_facade : sequence_base<Derived>
    {
        typedef fusion_sequence_tag tag;
        typedef sequence_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;
        typedef IsView is_view;
        typedef mpl::false_ is_segmented;
    };
}}

#endif

/* sequence_facade.hpp
cN/Nz0Rp0gV4KqKFr5RXEoep9qfncSrkb0UPDh5VDcfrH3iis2RagcUvwEJfaVYzZNRXnjZIValthjwvaUl843TT4oO5epDlHe1tiyZuWzTxLbrHT2u9UI7H8jZ1Nmsb6GhgJLse39qRyfKgvLuCXArkYaeuRQH9GT48F4PSV9gdNz0dXcSqc2ERi4fqcd/tarMRT5Pv0isStCEPvY62NPLnZJbMuFSzkuBGi/Lnla33WHyXqfb355pNMdsgT0AF4R90wzKdgqHjdKr99FzDXOMjC4+YXzntRlAoWhuARq7swADkf14z+2h1fajV9d+YfbSNgBza0lHWPGNYmnNVvjmi2aDt9Mb/fQxSbz4FAgoIibMJQcBjuNgHzOWSTOaB8YgiyuynNHNRozaafSO5TJa4HdVkibGjttsHymohBtlPYSGtt5/SGQTDIUqsvBBzOWHu98+KE1CsHZPYRyWUK2XVWisfwcW4l8vKp9BTGZee0e1bUnRKlN89iVYT+1+vof0iCdd3wVVYEj5ADyZFfBK7ZJVC4W1W4SPcpoY7pT9/s5Q2Q1at5qaYAhw7KfSmKAseF9AI9jYoLTKw7B5Ytzdgb/qc8vD7lLHjUNOsU3X3NjSFf+vLiZrBnTr/IkRu9g9l3pNR/r1pDvDvk2Ye4SUj+tFI/SMTBbvcq4ymj/zbMU5NTDljk2o1Ddh9yhW83BqJ3ZaKnqV6WT35
*/
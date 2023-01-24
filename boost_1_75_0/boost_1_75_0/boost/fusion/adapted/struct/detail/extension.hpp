/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_EXTENSION_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_EXTENSION_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    struct struct_tag;
    struct struct_iterator_tag;
    struct assoc_struct_tag;
    struct fusion_sequence_tag;

    struct assoc_struct_category
      : random_access_traversal_tag, associative_tag
    {};

    namespace extension
    {
        struct no_such_member;

        struct access
        {
            template<typename Seq, int N>
            struct struct_member;

            template<typename Seq, int N>
            struct adt_attribute_access;
        };

        template <typename T, int N, bool Const>
        struct adt_attribute_proxy;

        template<typename Seq, int N>
        struct struct_member_name;

        template<typename Seq>
        struct struct_size;

        template<typename Seq>
        struct struct_is_view;

        template<typename Seq, int N>
        struct struct_assoc_key;

    }
}}

#endif

/* extension.hpp
9RWiumShRbVyoUV1SThTHd0kqm8z1ZuJ6kiF6oMK1eOhTNXRJKo3M1XA6xNUYxWqcQrVpBCmunxPU6gemUdUPyKqiyosqssqLKp3aUz1gSZRfZOp3k1URyhUcxWqxWdZI1o3iWo6U9WJaoxCtZVCddN/THXp7qZQ/etToroiDKlWLLCoLllgUT28iamOahLV1z81tdcewtobRnnkBik13KXUMEeObeFNquE65rsl8a0pVMMUqtUnme95u5pC9cAnRHUlWZoPv7aofvq1RfW340z1ziZR9TLVAqJ6h0I1W6Ga9g9TDW0S1WuY6mVE9exXFtUQherDx5jqJzubQnX/x0R1N/XWXIXqx18p49lhpjq4SVTLmKqXqN6uUB2kUD29nqnamkS1x8emlN0t5wx30Jzh8JdWDX9/qdiH9ixlM3Y0pYatHxHfe4nqGwrV6QrVF/5gvt1NojqOqfqIappC1aVQHVHLVI993xSqlzDVG4nqn19YVI9+YVG9oIapvt0g1V0K1c0fwlmwxwG5/7Lc3iGJbu9jSRhCdM/dK73rjY/WRGsbvJuNWXx9k68v8dXL1yK+juPrY3wdzdfhfB3C1wF8vZWvffnak689+NqFrxfz9Xy+tuZrFF9D+frvaroe42stX3/m616+bl8drW2oi/3H69iyhIB1LAKrnMKwbL/j/vdV7L9H3lVgilpRWqqembimmdQR1zTfOyRM
*/
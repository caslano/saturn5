/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_IMPL_07162005_0132)
#define FUSION_VALUE_IMPL_07162005_0132

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<joint_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
/TlQiU4ILnO5dxJTIENsaDCnHkNoVQjdTIZ5aIz9msAp2RWOnfXhYD6c2gEU7I5hAdK94a/e9QrRJo5mH4bxYeCcCAq9vc58YBcaz7XSSKZVhL1fJo3GOKF4rPmGHCBvC/KBM/THJ6S6yA/xIC1zEiN1044sPxdsHrkCK7EUOF4p7R1ZlD4nDuXlw8jgUA/i1zTcM6BNWIayoMzpZFh1WFsemdZGggFVik/yuoMYmwo+03Hnyzs/GJc89GuG/r7/ng1BOvucoav438mybqBmPpiZYWIWvGGpl3MIuZO4ghTkCgntPI3d3yNYUU9y4OHV6v32Wf7waayJUCNztXJ8HtS7PDbTy2jadAajne5LusXZJEkHTtDimDxX2hHg0QAmiADWsn2lW6vM67P3lTyOiuExtjHirC37L5rCLWYtz3jaDquzSwP9j8PzwLtsMGsEHRXSjP4kqM+6e8nJ06hVB1gnpw4EzJhOx1TC6qHmPv7n7xx7Qdx/mr5ETUswcYqFcrBlKp+olILXgMA9fIh7Di7QzC9d7gVi/OfX1Rmej+foRcP6eGojWVDHoA==
*/
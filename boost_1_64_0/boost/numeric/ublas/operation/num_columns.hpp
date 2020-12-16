/**
 * -*- c++ -*-
 *
 * \file num_columns.hpp
 *
 * \brief The \c num_columns operation.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */


#ifndef BOOST_NUMERIC_UBLAS_OPERATION_NUM_COLUMNS_HPP
#define BOOST_NUMERIC_UBLAS_OPERATION_NUM_COLUMNS_HPP


#include <boost/numeric/ublas/detail/config.hpp>
#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/numeric/ublas/traits.hpp>


namespace boost { namespace numeric { namespace ublas {

    /**
     * \brief Return the number of columns.
     * \tparam MatrixExprT A type which models the matrix expression concept.
     * \param m A matrix expression.
     * \return The number of columns.
     */
    template <typename MatrixExprT>
    BOOST_UBLAS_INLINE
    typename matrix_traits<MatrixExprT>::size_type num_columns(matrix_expression<MatrixExprT> const& me)
    {
        return me().size2();
    }

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_OPERATION_NUM_COLUMNS_HPP

/* num_columns.hpp
QLldqVI2KnuUI0qLEu6N9g7yxnpv8OZ4Z3nv8T7j3WxDzRETea7CpUu9sEvYI+wXGoRDguy5zVPvafDMUDp4P1ev1rzaIn2NvkFfbx4xNzjbnT/T+jLcPv/AC8K3wlXiRvH3YrpnBnJeL0+Q75FrlC+Ugd5Sb4jaTf2FKqhD1RvUTPUW9U71fvW36np1h/qW+rH6tRqiddN+oQnaUO0GLVO7RbtTu1/7rbZe26G9pX2sfa2F6N30X+iCPlQfq5fqHsNjLneecD5zvqVtKHbbr/DxfLSQJrwidPaIHq/nMc8+6U5vrDpBnaauVDdgNL9Qw7SrjL7mOrO/9bH1lI1MlW7e58W3ROK52jPCM9mzwrPeM1CypVelr6STaqwWr11qXW4NsIZYk60sK88qtNZZW2m9S9iUkw+ERfJx+Q39LeNrs4P1c8uyCqwHrA3WHquz3d9eaa+zt9pn7K4OqXLnZrH4qZjtWee5QrpJvlcWlB1KdzUGc7tRE/U9+ijjSWO2ea+ZZ6210mxS5+aZLm4Tx3jSPLo0SiqSfiOtkxcrSd4z3lHafdoybZ1Wpw01W6zp9s20XfWEJIEexWz+UYgVS8UvxONiX+lh6TOpozxYTpVvldfJG+TX5cPyn+XTcldliJKsFCof6MVGuVFp3m/uN98yr3OW0bIa3PpHCqM8Ozy7PV97J6q/VF/AWH6pnlSv0RRtkpau1WpbMUO99HN6mHG1QRpdP/ZmfpDmQetWaKu0Kq1aq0G6OvRyi7Zdq9d2aXu0/VqDdkhbp3+kN+lTjCpjoJllTrX22ROd5XRmW9w34HfzJzCvTwr7xG+kc9LncowySin0zvPepKZqH2gntAizn+N1xjgznLXOTqcZrQ6hQ00q+Dv4T/keQpzwgPAHQRFvF1eLz4mvio955nkXeBd7l3iXeVd4V3mrvNXeGm+tt8670bvFu91b793l3ePd723wHvIe9h7xNnqbvEe9zd4W7wnvKe9ZL1HD1Y5qpBqlcmq0einm7m39fX0V2l9t1Bi1Rp2x0dhibDduMSvMheZW86w50lpjXWUbzkrnRecDh0SFkAq0rwf/klApzhMXiIvFJeIycYW4SqwSq8UasVasw07aIm4X68Vd4h5xv9ggHhIPi0fERrFJPCo2iy3iCfGUeBZrNtyzVn5T/pPcTrlKsZWJytvY4zeqI7RmfaCRY/azFlil9mBnA9UOMSFsPBP4r8XvxTDP5Z4F0klJUMYqq5QNymmlJ0bjUezGt7QPzY+tz23OSXXmO/scwsMTov4yn89X8VXC88JW6IgDwkfCtWJHj+65S/pculOeL6+QH5fflz+SdymNykzvVHW1NkSfpj+tC8a75jRrrr3B7ueMcL50SKxbXi9+AD9XmCSWiAfQpxGem6AZHel26feSIScoNd6XvAe9f/IOVkdDL76sNqu9tGu1uXqVfrXxc+tp+zN7rnO38xFdoykhtImkP/8n/lv+HH+14BVMYaTwgtBP7C9eK4qiJsaKaeJNYoaYKxaK5eIc8R6M98MY7afEZ8VNGOdXxb3QAGfEUE8HTzfPzzxXeq7zaGhRjqfI8yvP855tWP0NnnehuX/wtJd6SpdKoqRBR8RLSdJYaZJULs2RFklLpXXSHmm/1CAdkg5LR6RGqUk6KjVLLdIJ6ZTUKDfJR+VmuUU+IZ+Sz8pEqVZqlFqlDtp5i7JfaVAOKYeVIxi9cvUR7K8u2pXaKK1ce0R7SXtP+7OWod+p1+i79A/07/VrjFgj2fjY+MxoMQTTMG/CzrnNfMisM8+YkqVZydBVm61G63Pre2ghwXbs+fZbzjvOUaazQ5jOWyslKOOVfKUZ+rcrxnYW9O2LWoQ=
*/
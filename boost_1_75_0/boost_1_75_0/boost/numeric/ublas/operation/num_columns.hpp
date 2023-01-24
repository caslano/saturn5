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
PI07umoXti/g1zVe8Kn8EvEYronP/fV40LuzkKsGFy9FNZOaUj2KzX82w51jtDRPejUKwmrEhmZd/XPBJ0dPhyJkmMkndh8woY7Pbk0V+Hf7C5tXv8RNFk+rsaMcP0wn1m/KusoxIyYLlpM4yu5sbz34Q0yxX8c1OQc2//JX0phqD0ppOPGtzMKvKwr43ymvY+iJ0v5FFrn7cYEn3XuOw39yv766qhPguWh7TkigST/b+Jyqs0zf8W0feVroOCZBDNzkGAlmdvh6BiPKx0IJzKN4yffxsHsm4QZNr49unOMqYgomn0sF/2gWQXwQCmVZPMrhmYarML2uts3m6h/+Dycq1Jl0kFDizTQVCU/AZXR8zfU9tYp+WixO+6I31GDQzINMwSEi5X5XW52Qc0nG5MZqpVGe31iKdnsuTDWP1oDf2XFePQPi+fI0LISrJihKKioJt3x7bk1+d9A3mvVh61QUXP/A2yDkzMHZn18TEGEbDjfJFNFVR/ltHoFTNusLZrP8Lrewxqp+BiVdMX4fyk+q8VAEbH8iEzBTi+VTApd2WHiopxcj6ne9H8GtZsFRL8KyHTqUhHwcn62Xfi5tIdLO4L4UGUTwXjDfdp+y6O5p7sVGZGy7tXPIwkxHsS9DdqT2H6xNNnwLpzoYaLatMgu3cL+s5+sdj7p2M63eD9ldfTwpRQwSpNN15sua6Xj4CbnaXdNh8AM8/BLO
*/
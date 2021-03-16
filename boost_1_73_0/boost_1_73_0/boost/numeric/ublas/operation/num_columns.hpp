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
OHwlhz/CcGE3gHs4/DGGz8XwKA5vY/wYh3dwWPhgZbnQXRvke6k+E5TJv1VmqVuDqX1Qnp8i/eMxz6nMw07mgT45Cmn6I5041tZWV5RMrC2vE36ICP8fjH8O4h2yf5OUrGVsLb62EjLaCtH/gmX4sUW+lSQ/+4r466uSilq6gpYO05OV4a9OXZ3+Jgse+a6pT8dc+e7JRqt9hsA55PLQPlQmnQmWp79RHtVW9qs8aebCPKu4A25cK0d56b7FOAQ=
*/
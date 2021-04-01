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
dgYeGIkMCzQ+0pU6W/4kveofOhcY9AL1Zkz/wYQxP/LUhn0TDdAA6lsdl9ms0+TXXyleeRJLXVx8sna7907j3gV62Jkr/5l5m9Dl3UYWgntMrjlN+QBerPeEe50NWtxdjuQY9SCWxoXt5RDiMWqHs3FFhqVg8Z4UR/tw0kh1HFTB53HhSY+elR0RGa6TfzqcLdJdiJ7g8hrjp/+YW2gigt6A62H6t2ERDAHTYQe9B9/du8Jtz6vG9C2IwADBwhHrbhzdK3Kf9jdsCqYJ40VKrhpaAE9WHzYU9nVX2hEn46UwapPWfvFONVWmerCUP7s8MCXGG8wrfgoglt8dJ8jQUy2vbzhNkKTUigyLTx7wD9+uG/omfcpQCs+OJN/yl4m48LLlYIH164TgBOSPTE0jYR4XcBo2Hb8kvRahQV8qcDT6gjYNj4ISM7WkrneJnVTlJJe2VxDq/TxHq6c0bc4LrqIXOQnWgammltgjMbEXLNh1cLqkorIzaWlBWLMAcb9JlXidTZQKGDGVbMsjUGN/THd6fiJN04tKD/MJrDczVpSVEV+mhhLHKd7RNg==
*/
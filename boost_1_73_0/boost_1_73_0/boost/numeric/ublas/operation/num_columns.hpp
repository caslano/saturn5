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
B36YvpfNr9Nxq1y0b023hksKZbhTwW99cX/3Us0x+pzt7p7WiVqf+zRreBmaW+yPcILltqk2I/7mscUjlm6LzXeE0uqoPqfXZiGxlywi8CWJeabLum6+KvOjUqmctLl90nZ8pNluE0qZZd2GDz2BHTkoeA5P2s7KrQW4JGIU7joWAT1+GdrJh1oEUdRhDLoXXCIP6oMf/tz7D3GS8qblbKbtiCjD2Z7wR49cZbL0mkoAzwTt+oTdKIi8t5x+Z0NCaVLhlUnlQSYVPHP3acoLvNKdaIwXdRtK1xCcq+nQO/0Mv7Ax4m3dDatEpTQQGLSTlv14/Ka7jQ5RxgavYwtH/vXCderutwJIltMBvY+DA5D+pHawE7Ys1IIVsZDCtggwvhyOX/WGcW84bFM11krUkajLyVi8mNHdzVtS2pDhRMKpekIIghfn/dk87k+n8a+9X8bT+FXv3LuZ0giFoGpOFmfmJkjqekV/oP37FdhhugW/q2FScCarsvWfNau9vPV8zEpqqS23QPy5ZtJgX3zclxg87LSnWA+V/MjTZm1AEOJjdb8hexB32OKMrS1xvvkOhmIiXwiNahq8WKi1U2raHIdKTCW2oKaIaR1GVeyRGibj2fzY145rxciIw6RTKHJ5M57MY3xFJKrdDSAj
*/
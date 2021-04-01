/**
 * -*- c++ -*-
 *
 * \file num_rows.hpp
 *
 * \brief The \c num_rows operation.
 *
 * Copyright (c) 2009-2012, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */

#ifndef BOOST_NUMERIC_UBLAS_OPERATION_NUM_ROWS_HPP
#define BOOST_NUMERIC_UBLAS_OPERATION_NUM_ROWS_HPP


#include <boost/numeric/ublas/detail/config.hpp>
#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/numeric/ublas/traits.hpp>


namespace boost { namespace numeric { namespace ublas {

    /**
     * \brief Return the number of rows.
     * \tparam MatrixExprT A type which models the matrix expression concept.
     * \param m A matrix expression.
     * \return The number of rows.
     */
    template <typename MatrixExprT>
    BOOST_UBLAS_INLINE
    typename matrix_traits<MatrixExprT>::size_type num_rows(matrix_expression<MatrixExprT> const& me)
    {
        return me().size1();
    }

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_OPERATION_NUM_ROWS_HPP

/* num_rows.hpp
1rBo6UDVVOhVhwbgairPApsZqGDi4jw2LdHeQjaCcYnCBkWtZjvjw1SmGFVAoxwokYxvcP2ia/oPeLOybsgFVdwKUt2aNym4zXnKqgyPYdXgMiYN38WQbzNIdFuggs6gWziiBr9Cqe6QKNefcetTfugfZIeJl/8vEfuP6HRAgKpT6tmUL2al5DjPw0IvNP829gOMvVtbHa+56scQEbNPmjAGz1wxMQd1r1xBWMJzpA1wSeCiB5tvRg8N8H4DkN8KdS5W/yDyAFyWo+A+CwsIap6UdzV1L7uPwByt6CZNJHBqJ2hOz/k4+R3Thmp+h9aK6CoFd6XIu8xb885YPgo/Uf3j05RjZ8lSI/6TArIdwks1dorKyxy01ci7OCOYNXMhQBfcND1k0zDjCDmM0M8ikhf2DtydI4UcUCKjwl4DkNFbU7gLfnf+/ziNm/3onAeILpFR0rCPS/nm2sDHjew/SYAt4gyRpq65Dhl+19HtM6wVpA9N1rlhUqf55k63Maa2PNw9ISETj8oNt+2nXtdtq/rFgFwhsxR5LUf+iL8X/cbiuSr7kPc1es40wQ==
*/
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
/B1ex9+p+KtVr0nOmfG79dk016/ZtQ+B/ycn3Y3O+bAHOxu0WXx4VYDfTt+7QzZRhYFchfTTy+JztGgIH33A8F4+ztFSu7CnvgDnOx9s1f42MzTIeNMaHyHDuZQZ+Soo8QBkWkiWfFj3o/INtcaxJfsoxutjoJe8lC3ZJ4DTNmsplPMp4Ph3vQd/mGx/BbiOJ/lZgqG/VF4N3udQh88jDXQVxECT2Jb40/Vf4X0Rab+EtNCb
*/
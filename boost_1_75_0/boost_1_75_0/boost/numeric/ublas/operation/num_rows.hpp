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
FZRLE/bJ1kTdGFmV+RZ3aayl0bt4P4Rnd29M+2pUiHDA8lMuBOXsuumIcksjb5b/EYxmJ3RqiQkQ49ePx7TmHLZVGARlo2N75jPl7I7IrLo8Afm47WaaXeBZjHnnjxaY8IfYhpfyD2bQ0ZzAYkHmngkL5q1vPLfT43jb8ZVK8FvfNMUFikmHJGwfL9UXMrUglyBxwvLImQOL6PAEsZ7GO+5nXiU3Jnm8IfUeV2m/3aQ1yTxJu75u3v1g13YcASRDLXZXRCUMQTsF273cz+J3cHRFpfPdlIOnArAq+UMjiOkJfcJz1ceeYwz5PoON+K5S2PAnbBQ3MpLEcC1pB4qrrmuY1stvL0W1WJ6OGWGpZa3hsP2JupOMvS/z8cj6MXl04XKS91gK9ciuaYXetZua7EKGWhlNhe+DJYcuc9+cPL5tVB3dliA4hRh569BCPR76pDraNYHjla36/fZvTR/iju4pXnWSmFV/BnOL6RzPfrJegeI2Pzp6WnbZ6xxBBBvOGWgT4c+xpL8mEKXn0vA26LSAD0vrzb7jA3v3IqjEGmzzzpfjIgYtPZVXP55bv/asZZQ7kf/WdbUDgd3XdszbataRmGPw/OALVzU4yJHyc1O5od2avCYajl2LU9fNuMSPyC55t4TEKnKY9d19WBh2iuWe7hG/ro8CWTdcbhEjuRMbVYZcymOuPhIkHAH/FCeM5E1F2MXAMHdfnh7p
*/
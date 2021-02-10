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
bIGm5AmOmHgBwZpJJ5iE+Qo6IJAII3jiBD4QWcozdxSfj/uz+Gw8+q0/nQ3Go5lHO1MSq9AbtIVAvN7sbDA4hDXHsXB20Z/O+7/XmA/oNs2CLTv6041NTlFr6frx9sI+gDHt984vrkZnc1Q62m/lG5/VfQpxSmbcEE1Y/xvnvDfvRfAjNYSNbJoj0EULvLXAzZh0/5UY7RIzyPBDYtHdr8azfh0RJ7IeW3PUj2aH8GsoyD0g8DXq2Z/uyeMyUxrbdSgrsKHiYHFD2WppuiEAj3cQYD6f1CCu2jzO/Qy9q/lrvPFpVm7TPq3j88El1pOrsHsKYNafTt7ij4lmptTpgunmxq470uf2zHfAotF4Mh1fTvuzWQQnwwP61KTbnLs1r28UnHCNnveTnuZ/VZwaHl1ObkxdhkYReou7uZym/vratqrSi6lbVcMpFxrUaYByS6jKnUDSj2tjN9Okj9W20flOmeFvmhj1bu2Ekm74Ys1uDAQQL+Oe3nlH59xOAGgSDV7/AlBLAwQKAAAACAAtZ0pSiuW6VyEMAACNJAAAIgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTgyLmNVVAUAAbZIJGC1WXtz2kgS/59P0fFVvALLgLN1V7smSR2xscMFGxfg
*/
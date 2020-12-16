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
3lu/BrO2W/8Mu/kKY4cVa19vz4K2rXU+dUhxCClG3s7iAPFP4g2e8Z6bPR/Asn3pOem5BGMSod6nvaC9rnXWu+uD9dv0pfo2vYcRb8w3OthDbNMeaWfahfYd9gL7cfs5u94+YL9tN0M7Eqer8zMnxpEcy4lzHnWecp53XqdtrXTXSk++H38tP4x/gF/Ln+G7CxOFAuE2YYa4UlwuPSFVy3UYU4LR3KY8a/QxZXOYmWbON9dDj82wOziXOf2d4c4kprNDSC3oCX4rX89/I6jiQTHJ87HnjOdlaQB2wavKAeW4ckbp6O3tHekd4830lsFOLvI+6l0D7dBBvRo2LFXN1KZri7QHtce0p2GbftDmo5+PwDY+r7+jhxgPGK8Yy8xHTMlW0eNYO85OsJPsFDvNnmBPtjPsbDvPLrCL7TK7wp5jV9rzMBqL7SX2MnuFvcqusqvtGruW2qaqEJIGyubv4p/h3+RThVzhc+EMfnpPFqeId4s7pc6yKo+XK7HnvsNv817lNmU7VtCflDDorCQtR5uvPaR/o/dDDc/b7zrnaP/r3PGM4VcLe4Xjwg3iVrFUni3neQu8xehrhXeOt9J7Yf0YocnwOz7X1uudjWznLuhoamtC2LtwB/njfAeht3A19l26UCbME5YJHwqdxEeYDQkhEvMRrhIShVnC/cJ0sVh80vOp5zppuyTJi+AjPOINV2uMZ4zJVrm13JrikMYQksB01bXCZE8/iVP2YU4szACvJqnXajdqq7U7zErrXeuPVrh9uT3IFjG6OXaJvc8+YvdyrkDr9jnfwIaEsHMPx3/OXynECnOEJcIzwu+Fb4SB4kTsbF6aLj0rnfQmqiP1EWad1Wjf4zziPO284LzmvA3t0sQuCULZZc19noc9bwW8t/GSKl+nvKTc5X3Mu9UrqIpqqOuwkzppKdpUeC2faOe0dvol+gN6tb5Jf1c/pocbPYwY41pDN+KMl439xqdGd/NKc4h5K9bKe+YXsBO2FW/dDA/jTus3Voada39oJzl7YC9C2dmxAz+Lr+WvEyYJ0bAV74qJnjnQRqpUJcXK5fJB+Sv5UbTngHJMuc6b6H0RNuxaNVndpv6gKlqilq0d1L7SCPyoy/UR+hR9pv4bfZW+2og0F5ivm45VYp21+tuH7QnOQ7TPMaFs3C7BntvPhwozhC6iIz6G1XKjlCHtk3+QByjXe5d731TDNUcTDMXINKZi5a8wXjX2GJG26mTDbrhl/Ip/gt/GH+G/5qOEKwVduFkok+6V3oBm/F4S5fvQ7gp4gy+qz5rh1k3WUutxayPm9Yx9A/NnQ8mgUEImC98Ld8GPabV6vaQesi1Xw/adla+C//KAkuUNgV3uovZQ+6j91CvVa7FXvaqlDlcT1THqOPUmeJ656gy1VJ2l3qH+Sl2EWh9SH1UfV59Wn1M3oQU72vjbTepR2J0W9YR6Sj2rEi1c66hFalEap0Vrl2oxWn9tgDZI4zVJUzVTi9WG6gn6aHioE/V0PUefrt+i36rfrt+Nkb5PfxAa4rf6U/oz0BJb9Vf01+C/v4V18Qf9U/3P+lf6t/oZ6I4ORqQRZXBGtHEp1kp/Y4AxyOANyVAN04jFukkwkowUI82YYEw2MoxsI88oMIqNMqPCmGNUGvOMBcZSc4W52txp7jEPmF+bXa0eVh+rn3Wlda0lWF74psOtRGuMNQ4jnWnlWjOsUmuWdYf1K2uRdb/1kPUoRv9p6zlrk/WitcN63fqd9bb1HuxIk3XUarZarBPWKawT/FUFu6MdaUfZnB1tX2rHwM8dgD3I239P530NP7iH08fp51zpXOsI8NssaOZEeG/jnJucTCcXXlypM8u5w/mVs8g=
*/
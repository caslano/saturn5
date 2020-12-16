/**
 * -*- c++ -*-
 *
 * \file iterator_type.hpp
 *
 * \brief Iterator to a given container type.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */


#ifndef BOOST_NUMERIC_UBLAS_TRAITS_ITERATOR_TYPE_HPP
#define BOOST_NUMERIC_UBLAS_TRAITS_ITERATOR_TYPE_HPP


#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/tags.hpp>


namespace boost { namespace numeric { namespace ublas {

    namespace detail {

        /**
         * \brief Auxiliary class for retrieving the iterator to the given
         *  matrix expression according its orientation and to the given dimension tag.
         * \tparam MatrixT A model of MatrixExpression.
         * \tparam TagT A dimension tag type (e.g., tag::major).
         * \tparam OrientationT An orientation category type (e.g., row_major_tag).
         */
        template <typename MatrixT, typename TagT, typename OrientationT>
        struct iterator_type_impl;


        /// \brief Specialization of \c iterator_type_impl for row-major oriented
        ///  matrices and over the major dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::major,row_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator1 type;
        };


        /// \brief Specialization of \c iterator_type_impl for column-major oriented
        ///  matrices and over the major dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::major,column_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator2 type;
        };


        /// \brief Specialization of \c iterator_type_impl for row-major oriented
        ///  matrices and over the minor dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::minor,row_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator2 type;
        };


        /// \brief Specialization of \c iterator_type_impl for column-major oriented
        ///  matrices and over the minor dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::minor,column_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator1 type;
        };

    } // Namespace detail


    /**
     * \brief A iterator for the given container type over the given dimension.
     * \tparam ContainerT A container expression type.
     * \tparam TagT A dimension tag type (e.g., tag::major).
     */
    template <typename ContainerT, typename TagT=void>
    struct iterator_type;


    /**
     * \brief Specialization of \c iterator_type for vector expressions.
     * \tparam VectorT A model of VectorExpression type.
     */
    template <typename VectorT>
    struct iterator_type<VectorT, void>
    {
        typedef typename vector_traits<VectorT>::iterator type;
    };


    /**
     * \brief Specialization of \c iterator_type for matrix expressions and
     *  over the major dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct iterator_type<MatrixT,tag::major>
    {
        typedef typename detail::iterator_type_impl<MatrixT,tag::major,typename matrix_traits<MatrixT>::orientation_category>::type type;
    };


    /**
     * \brief Specialization of \c iterator_type for matrix expressions and
     *  over the minor dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct iterator_type<MatrixT,tag::minor>
    {
        typedef typename detail::iterator_type_impl<MatrixT,tag::minor,typename matrix_traits<MatrixT>::orientation_category>::type type;
    };

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_TRAITS_ITERATOR_TYPE_HPP

/* iterator_type.hpp
os3bCbnasqq6N+sjllgXs4wjZhEeYtTPz2U85Chj82cbrnadp1FGrX8eqlaIv09Td3/8Mk19W/MY8V4qy1g3p7TKtRHN8g1gGcxYLum+n7bZ6xc/9/npfOQIoG+aX1wEmAqoAOwGxL3HVV0oTvZlUMehZMneLX+mvNYFhoorArZv3wref+d38dX0nGXItTOvsJmXue9h6ARX363uvRnEfH2U94/TrrI6iCcwrx7G/F7lXyyyAqPEN3BS8UfAwDSfuCRtIFrDZ+hizvwjRv759lgzPmDKhw663gHK+w5YIc1P0/vr91D5LkP5wnTusU3q6IT3Wlqe/b6L2osRkfDeu4/aqU/ce28dxZ0X994bTfmkx957Rlwe6jOowRIbkPd4or0vUCo6IF6dNU2juGWBfd4LrQ/9vZ37A1y/RwnPI3rpPXx63uhfYA0VJ63W4hJvQEzxVlphP/bMAGsBXQkXo4pwiwOdxcPWa9Y1ordnvfcl/wBxGayvsp3tgLLF6utbKWk/9qWJY76xsTozzxmBLHEz9jPbYR/oQ/GONUqM9YwWX/RcKTKwOO4Ba7KV3lLrPH+2uNxfKL7svxI2aWFxsW4nzQcpPnGHweeqpvjQuN8u+9Iue11VBfddFvddA5U7U/UT16WC4rI4Lq6fiOdOmr91+8vpR+7tllBH6LH0mZWmzYil6Y12LK+uq5d0XB7O+6tE11bFcd4XEW2Q8t5t14fyrq0puYziX0Z8Jzs+OqekphouxHwgzd8PId8sxuO+rKysqIFBkTqEZrS48vRepXS6fIoz++JjWPVt9X/PfyH7apl86xpqaqpr69VNECXkaZ/A9yni271Zvseovobs1YGPsR+Ve5eyx8s27mlMp7jJjGeOPb/oSniUnyHvPo8p63qfKt/OtzZaV1NdVRatLeGPscTlN+5OpR93MnhvvkPGbcZ+zUvW+9YMMdczzNLnxnpM8Nkb7zfG7nHaCpxYWkUZJ1HaFqQl2u3otdPXqRzfs4aLUmuH5bPtX2op/k3rIrHOynOtU/yY2Ej4wbg9zRcpDrZlRr3XUty7qF2p9boVoDSuP+e53+qEfdD1Ypgly76PZOSKrKJZeJfP4z20pWsDAW9W6KbQPHsPrRFpu+bZenna0oflJlor0r97cPoRwJNMj020zNCn6d5GvuLS2Avj/HZU4J1H+D1C0UCGdzCh479QepN31RZSX01A3/Ic6S4zzvtG9d3bhN+en/U84Gny2xrnEM3lcXNSe4q7mvES3yfOeYruJ52H/Ct4HbV0fOiGUC1dYCvTjqCWBRX6XsWlU2SzBXj9o9NHIP1uRSvp0MzGPbXMf3uF7scLQpV8UWk6f8d6HNKWV8T2KJcOVheVUr9w+jbAk4qeN131RaUBr8RL7EdRqfa3A37v0mdCRVjO+vqHekkqn3s/cj98m9+Len7+Lj1fJC6mZ92ve1v0fvmyv+k7iV8knqPi5r0fUFxu3LtzOcWlByLisH/8ab8781GL3vT+pHxNueDxmx03Rw3xtRZvewt8En9UltQ/vkL5PuyHLS64Sr1kpNiEeNKzoOXK9fHOCoz/+Vq2foG+CwRlfBHi6gGrKP49KVY+WqNz2ur5+lvgS39hyxLzOzlfy9LzmBMioTpwDfmVLK1D2j7mC0n6QSgoZwafkiVOPwF4UtGHKuKng/jvoLMszarkPYFlS0NloQbkpuYfH+KHV9py61+2AnLrDxIPnT6zUu0NgMi3bCkE18gjm/kvAs5fZHmzlr1sxq/V8bm3L6H9Bo7fifiPZHxkRRFu9Y3zpzLpD1airhLPv6JE4+xOwDkOnL+SLeCKV808OiwQ4m8y3lqxL9wqFPOXTKAvXMA=
*/
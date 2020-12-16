/**
 * -*- c++ -*-
 *
 * \file const_iterator_type.hpp
 *
 * \brief Const iterator to a given container type.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */


#ifndef BOOST_NUMERIC_UBLAS_TRAITS_CONST_ITERATOR_TYPE_HPP
#define BOOST_NUMERIC_UBLAS_TRAITS_CONST_ITERATOR_TYPE_HPP


#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/tags.hpp>
#include <boost/numeric/ublas/traits.hpp>


namespace boost { namespace numeric { namespace ublas {

    namespace detail {

        /**
         * \brief Auxiliary class for retrieving the const iterator to the given
         *  matrix expression according its orientation and to the given dimension tag.
         * \tparam MatrixT A model of MatrixExpression.
         * \tparam TagT A dimension tag type (e.g., tag::major).
         * \tparam OrientationT An orientation category type (e.g., row_major_tag).
         */
        template <typename MatrixT, typename TagT, typename OrientationT>
        struct const_iterator_type_impl;


        /// \brief Specialization of \c const_iterator_type_impl for row-major oriented
        ///  matrices and over the major dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::major,row_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator1 type;
        };


        /// \brief Specialization of \c const_iterator_type_impl for column-major
        ///  oriented matrices and over the major dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::major,column_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator2 type;
        };


        /// \brief Specialization of \c const_iterator_type_impl for row-major oriented
        ///  matrices and over the minor dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::minor,row_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator2 type;
        };


        /// \brief Specialization of \c const_iterator_type_impl for column-major
        ///  oriented matrices and over the minor dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::minor,column_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator1 type;
        };

    } // Namespace detail


    /**
     * \brief A const iterator for the given container type over the given
     *  dimension.
     * \tparam ContainerT A container expression type.
     * \tparam TagT A dimension tag type (e.g., tag::major).
     */
    template <typename ContainerT, typename TagT=void>
    struct const_iterator_type;


    /**
     * \brief Specialization of \c const_iterator_type for vector expressions.
     * \tparam VectorT A model of VectorExpression type.
     */
    template <typename VectorT>
    struct const_iterator_type<VectorT, void>
    {
        typedef typename vector_view_traits<VectorT>::const_iterator type;
    };


    /**
     * \brief Specialization of \c const_iterator_type for matrix expressions and
     *  over the major dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct const_iterator_type<MatrixT,tag::major>
    {
        typedef typename detail::const_iterator_type_impl<MatrixT,tag::minor,typename matrix_view_traits<MatrixT>::orientation_category>::type type;
    };


    /**
     * \brief Specialization of \c const_iterator_type for matrix expressions and
     *  over the minor dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct const_iterator_type<MatrixT,tag::minor>
    {
        typedef typename detail::const_iterator_type_impl<MatrixT,tag::minor,typename matrix_view_traits<MatrixT>::orientation_category>::type type;
    };

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_TRAITS_CONST_ITERATOR_TYPE_HPP

/* const_iterator_type.hpp
yiuXtCNQfp2fci4n93XKNYY7jXCHiB6OfJd43fLMjp0VKKbGHYWdiNcgW5am0HMhyuEmS/d7eqIdY3dA4rVUwp70xp5Gp3mS5gRmpYwEPk96FB/LM8yTYZZLM7HnAYW/x8O4CXlyNQxbib2U5zXgyfRc7gKxxRPrw/qKOfP5blku68/KVVk9OF1ZiP/zHW26y2f0HZe3jtb6nXiubE2yswlz0Se+30AiP/a3sUqDa5x9zW1++Q0Svx/LluYXvy83g3B62PXrSM/DkadMtzhPgXFW7l/jb7TWpz0oLg1uZXydrtq4QY/5hPEemC9xIpZP/JL4tonj+4F/TaBRtA3mE9/8xLpiVv2zPyBQT2M+RwZU09j7aSeVu4Ndr5cozxy7Xn+k9FzG1/n7uYz6eU1AliduTuH+u4f4rbVtlzYQvwZRJoIuc1MwjfqRcDVvj3nPbhlqYMvxA8TrI3GD8HF+mibA62pFY54DbSeaHCsoTqL1df/faPf9VirvUOCrMmyh52uFD3GJc1k2t3lMlq8NxnDKUdRYOw+kudsrsrmdL6hW/Q/Lebut81hX0PXrQ8+lwEhnHHqX8Lxn1ndjRkAszsiX/lbQBXsXwZZF2qakjwhbPcKwvxd8PkP6JgHZCjN+MfBfkvgZxTEdjnHyGGcRcL6POO/yq2C+lBXReC8zXifG2wa8VySvwMqJ4WBGOHBBOBhuJv99oHlV0oRXliXmr+skxmi+d1wRDobCrQY3zbPbGM3zjvJEnpPwLNv7B3jeC6jh8DXADwE/AtwC2Ad4HfAG4MdGuB/wE4Y3AT9lfTeY7C5X3gv9SQWN3br5FTV09XArxKn+FGXVVdGk57oFPocfOceRvkhxEecdsKRTEB7rZqxzs34dJbw8865Y4/2Tz/ENhGu+R4iG5nCmsRPyOT5Gw+yMchMNzaccZ5YnQd8/wZd37g9IXPRHQOn7a2vd7nlPru/r/fLHiM4KrECq0vWZF3JYDM36Uej5W6xVIs27RtznWyrOD9wev69a667r57G+vonSvxVYg9OwJwJ+Pq/QdPk2L45z1f312H+X0t/xS90/j+cZXVaUkcqn+am01PV8wnXX86nMB9CHrxHO+kCifj+M57NldXTeiTm/RiwV94t86PY9rEm4QXqy+Jn1iFjhqbW8vk3iCVwEF/DfJx7Cu6ivfncS7df8IZFr9bKuEp+1joiVniVinnedCIDmRawL7vO3sfXzoYSfBUu76zz3eWZbvXiu/jWV8dqAD7r5K6JMFGJt8VNrCtYW3bzX+a8Wz/rX2/P48MXk90oW6rpfniD65wLN6d0XE20P0rs72bhVQC6pqa2ury6pis6DFBKRnu+PLCQ7Z/u9+chN8jnoeId0YjlMpzrOCFyAvl3jWSPaoX+3+2839IMaqWmiZDGdaki9epd2ZR65xOPKgNLhPhHLwCcMPlvAh3UjzYdlKkYDfMJ119dNvNkezVO22z05pAvXLq6pr0ZjyHmNZO4gnW9pXrV2u3S5SdlwZXO7XEB8b/P5Ra0vVteqGu4DvWZivKHQM45619j1YVz9Lk7Ai+mvddFKugs95qf5+CKJ9zneC9Dl6B6AvhU4J5Ae0zkSbH6fIrol/Ex0rMcllnO5vxfeM+mIO8DvmAP8jvk+4GcMbxnvj57J3x/0rhi++F/3rpC0qb4rGihOy2P83M7xTnr1TiG5kDKTGy8zCbx1/5u8OZ7vH+kMOSJ7qaz4vcm1EwX9JrPf0STAcblfd4t+Z2gb2dKSqtIF9n5YK9o3ljGx90U/ovk0fP387nt5t6RmP8t4lM8DSmYXCGM9NoDSR4jBzIt16Ji9v0xHan/kSnfT472Yg3q+TfbH4bA=
*/
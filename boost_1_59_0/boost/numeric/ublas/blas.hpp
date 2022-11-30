//  Copyright (c) 2000-2011 Joerg Walter, Mathias Koch, David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.

#ifndef _BOOST_UBLAS_BLAS_
#define _BOOST_UBLAS_BLAS_

#include <boost/numeric/ublas/traits.hpp>

namespace boost { namespace numeric { namespace ublas {
    

    /** Interface and implementation of BLAS level 1
     * This includes functions which perform \b vector-vector operations.
     * More information about BLAS can be found at 
     * <a href="http://en.wikipedia.org/wiki/BLAS">http://en.wikipedia.org/wiki/BLAS</a>
     */
    namespace blas_1 {

        /** 1-Norm: \f$\sum_i |x_i|\f$ (also called \f$\mathcal{L}_1\f$ or Manhattan norm)
     *
     * \param v a vector or vector expression
     * \return the 1-Norm with type of the vector's type
     *
     * \tparam V type of the vector (not needed by default)
     */
        template<class V>
        typename type_traits<typename V::value_type>::real_type
        asum (const V &v) {
            return norm_1 (v);
        }

        /** 2-Norm: \f$\sum_i |x_i|^2\f$ (also called \f$\mathcal{L}_2\f$ or Euclidean norm)
     *
     * \param v a vector or vector expression
     * \return the 2-Norm with type of the vector's type
     *
     * \tparam V type of the vector (not needed by default)
     */
        template<class V>
        typename type_traits<typename V::value_type>::real_type
        nrm2 (const V &v) {
            return norm_2 (v);
        }

        /** Infinite-norm: \f$\max_i |x_i|\f$ (also called \f$\mathcal{L}_\infty\f$ norm)
     *
     * \param v a vector or vector expression
     * \return the Infinite-Norm with type of the vector's type
     *
     * \tparam V type of the vector (not needed by default)
     */
        template<class V>
        typename type_traits<typename V::value_type>::real_type
        amax (const V &v) {
            return norm_inf (v);
        }

        /** Inner product of vectors \f$v_1\f$ and \f$v_2\f$
     *
     * \param v1 first vector of the inner product
     * \param v2 second vector of the inner product
     * \return the inner product of the type of the most generic type of the 2 vectors
     *
     * \tparam V1 type of first vector (not needed by default)
     * \tparam V2 type of second vector (not needed by default)
     */
        template<class V1, class V2>
        typename promote_traits<typename V1::value_type, typename V2::value_type>::promote_type
        dot (const V1 &v1, const V2 &v2) {
            return inner_prod (v1, v2);
        }

        /** Copy vector \f$v_2\f$ to \f$v_1\f$
     *
     * \param v1 target vector
     * \param v2 source vector
     * \return a reference to the target vector
     *
     * \tparam V1 type of first vector (not needed by default)
     * \tparam V2 type of second vector (not needed by default)
     */
        template<class V1, class V2>
        V1 & copy (V1 &v1, const V2 &v2) 
    {
            return v1.assign (v2);
        }

        /** Swap vectors \f$v_1\f$ and \f$v_2\f$
     *
     * \param v1 first vector
     * \param v2 second vector
     * 
         * \tparam V1 type of first vector (not needed by default)
     * \tparam V2 type of second vector (not needed by default)
     */
    template<class V1, class V2>
        void swap (V1 &v1, V2 &v2) 
    {
            v1.swap (v2);
        }

        /** scale vector \f$v\f$ with scalar \f$t\f$ 
     *
     * \param v vector to be scaled
     * \param t the scalar
     * \return \c t*v
     *
     * \tparam V type of the vector (not needed by default)
     * \tparam T type of the scalar (not needed by default)
     */
        template<class V, class T>
        V & scal (V &v, const T &t) 
    {
            return v *= t;
        }

        /** Compute \f$v_1= v_1 +  t.v_2\f$
     *
     * \param v1 target and first vector
     * \param t the scalar
     * \param v2 second vector
     * \return a reference to the first and target vector
     *
     * \tparam V1 type of the first vector (not needed by default)
     * \tparam T type of the scalar (not needed by default)
     * \tparam V2 type of the second vector (not needed by default)
     */
        template<class V1, class T, class V2>
        V1 & axpy (V1 &v1, const T &t, const V2 &v2) 
    {
            return v1.plus_assign (t * v2);
        }

    /** Performs rotation of points in the plane and assign the result to the first vector
     *
     * Each point is defined as a pair \c v1(i) and \c v2(i), being respectively 
     * the \f$x\f$ and \f$y\f$ coordinates. The parameters \c t1 and \t2 are respectively 
     * the cosine and sine of the angle of the rotation.
     * Results are not returned but directly written into \c v1.
     *
     * \param t1 cosine of the rotation
     * \param v1 vector of \f$x\f$ values
     * \param t2 sine of the rotation 
     * \param v2 vector of \f$y\f$ values
     *
     * \tparam T1 type of the cosine value (not needed by default)
     * \tparam V1 type of the \f$x\f$ vector (not needed by default)
     * \tparam T2 type of the sine value (not needed by default)
     * \tparam V2 type of the \f$y\f$ vector (not needed by default)
     */
        template<class T1, class V1, class T2, class V2>
        void rot (const T1 &t1, V1 &v1, const T2 &t2, V2 &v2) 
    {
            typedef typename promote_traits<typename V1::value_type, typename V2::value_type>::promote_type promote_type;
            vector<promote_type> vt (t1 * v1 + t2 * v2);
            v2.assign (- t2 * v1 + t1 * v2);
            v1.assign (vt);
        }

    }

    /** \brief Interface and implementation of BLAS level 2
     * This includes functions which perform \b matrix-vector operations.
     * More information about BLAS can be found at
     * <a href="http://en.wikipedia.org/wiki/BLAS">http://en.wikipedia.org/wiki/BLAS</a>
     */
    namespace blas_2 {

       /** \brief multiply vector \c v with triangular matrix \c m
    *
    * \param v a vector
    * \param m a triangular matrix
    * \return the result of the product
    *
    * \tparam V type of the vector (not needed by default)
    * \tparam M type of the matrix (not needed by default)
        */                 
        template<class V, class M>
        V & tmv (V &v, const M &m) 
    {
            return v = prod (m, v);
        }

        /** \brief solve \f$m.x = v\f$ in place, where \c m is a triangular matrix
     *
     * \param v a vector
     * \param m a matrix
     * \param C (this parameter is not needed)
     * \return a result vector from the above operation
     *
     * \tparam V type of the vector (not needed by default)
     * \tparam M type of the matrix (not needed by default)
     * \tparam C n/a
         */                 
        template<class V, class M, class C>
        V & tsv (V &v, const M &m, C) 
    {
            return v = solve (m, v, C ());
        }

        /** \brief compute \f$ v_1 = t_1.v_1 + t_2.(m.v_2)\f$, a general matrix-vector product
     *
     * \param v1 a vector
     * \param t1 a scalar
     * \param t2 another scalar
     * \param m a matrix
     * \param v2 another vector
     * \return the vector \c v1 with the result from the above operation
     *
     * \tparam V1 type of first vector (not needed by default)
     * \tparam T1 type of first scalar (not needed by default)
     * \tparam T2 type of second scalar (not needed by default)
     * \tparam M type of matrix (not needed by default)
     * \tparam V2 type of second vector (not needed by default)
         */                 
        template<class V1, class T1, class T2, class M, class V2>
        V1 & gmv (V1 &v1, const T1 &t1, const T2 &t2, const M &m, const V2 &v2) 
    {
            return v1 = t1 * v1 + t2 * prod (m, v2);
        }

        /** \brief Rank 1 update: \f$ m = m + t.(v_1.v_2^T)\f$
     *
     * \param m a matrix
     * \param t a scalar
     * \param v1 a vector
     * \param v2 another vector
     * \return a matrix with the result from the above operation
     *
     * \tparam M type of matrix (not needed by default)
     * \tparam T type of scalar (not needed by default)
     * \tparam V1 type of first vector (not needed by default)
     * \tparam V2type of second vector (not needed by default)
     */
        template<class M, class T, class V1, class V2>
        M & gr (M &m, const T &t, const V1 &v1, const V2 &v2) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v1, v2);
#else
            return m = m + t * outer_prod (v1, v2);
#endif
        }

        /** \brief symmetric rank 1 update: \f$m = m + t.(v.v^T)\f$
     *
     * \param m a matrix
     * \param t a scalar
     * \param v a vector
     * \return a matrix with the result from the above operation
     *
     * \tparam M type of matrix (not needed by default)
     * \tparam T type of scalar (not needed by default)
     * \tparam V type of vector (not needed by default)
     */
        template<class M, class T, class V>
        M & sr (M &m, const T &t, const V &v) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v, v);
#else
            return m = m + t * outer_prod (v, v);
#endif
        }

        /** \brief hermitian rank 1 update: \f$m = m + t.(v.v^H)\f$
     *
     * \param m a matrix
     * \param t a scalar
     * \param v a vector
     * \return a matrix with the result from the above operation
     *
     * \tparam M type of matrix (not needed by default)
     * \tparam T type of scalar (not needed by default)
     * \tparam V type of vector (not needed by default)
     */
        template<class M, class T, class V>
        M & hr (M &m, const T &t, const V &v) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v, conj (v));
#else
            return m = m + t * outer_prod (v, conj (v));
#endif
        }

         /** \brief symmetric rank 2 update: \f$ m=m+ t.(v_1.v_2^T + v_2.v_1^T)\f$ 
      *
      * \param m a matrix
      * \param t a scalar
      * \param v1 a vector
      * \param v2 another vector
      * \return a matrix with the result from the above operation
      *
      * \tparam M type of matrix (not needed by default)
      * \tparam T type of scalar (not needed by default)
      * \tparam V1 type of first vector (not needed by default)
      * \tparam V2type of second vector (not needed by default)
          */                 
        template<class M, class T, class V1, class V2>
        M & sr2 (M &m, const T &t, const V1 &v1, const V2 &v2) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * (outer_prod (v1, v2) + outer_prod (v2, v1));
#else
            return m = m + t * (outer_prod (v1, v2) + outer_prod (v2, v1));
#endif
        }

        /** \brief hermitian rank 2 update: \f$m=m+t.(v_1.v_2^H) + v_2.(t.v_1)^H)\f$ 
     *
     * \param m a matrix
     * \param t a scalar
     * \param v1 a vector
     * \param v2 another vector
     * \return a matrix with the result from the above operation
     *
     * \tparam M type of matrix (not needed by default)
     * \tparam T type of scalar (not needed by default)
     * \tparam V1 type of first vector (not needed by default)
     * \tparam V2type of second vector (not needed by default)
         */                 
        template<class M, class T, class V1, class V2>
        M & hr2 (M &m, const T &t, const V1 &v1, const V2 &v2) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v1, conj (v2)) + type_traits<T>::conj (t) * outer_prod (v2, conj (v1));
#else
            return m = m + t * outer_prod (v1, conj (v2)) + type_traits<T>::conj (t) * outer_prod (v2, conj (v1));
#endif
        }

    }

    /** \brief Interface and implementation of BLAS level 3
     * This includes functions which perform \b matrix-matrix operations.
     * More information about BLAS can be found at 
     * <a href="http://en.wikipedia.org/wiki/BLAS">http://en.wikipedia.org/wiki/BLAS</a>
     */
    namespace blas_3 {

        /** \brief triangular matrix multiplication \f$m_1=t.m_2.m_3\f$ where \f$m_2\f$ and \f$m_3\f$ are triangular
     *
     * \param m1 a matrix for storing result
     * \param t a scalar
     * \param m2 a triangular matrix
     * \param m3 a triangular matrix
     * \return the matrix \c m1
     *
     * \tparam M1 type of the result matrix (not needed by default)
     * \tparam T type of the scalar (not needed by default)
     * \tparam M2 type of the first triangular matrix (not needed by default)
     * \tparam M3 type of the second triangular matrix (not needed by default)
     *
        */                 
        template<class M1, class T, class M2, class M3>
        M1 & tmm (M1 &m1, const T &t, const M2 &m2, const M3 &m3) 
    {
            return m1 = t * prod (m2, m3);
        }

        /** \brief triangular solve \f$ m_2.x = t.m_1\f$ in place, \f$m_2\f$ is a triangular matrix
     *
     * \param m1 a matrix
     * \param t a scalar
     * \param m2 a triangular matrix
     * \param C (not used)
     * \return the \f$m_1\f$ matrix
     *
     * \tparam M1 type of the first matrix (not needed by default)
     * \tparam T type of the scalar (not needed by default)
     * \tparam M2 type of the triangular matrix (not needed by default)
     * \tparam C (n/a)
         */                 
        template<class M1, class T, class M2, class C>
        M1 & tsm (M1 &m1, const T &t, const M2 &m2, C) 
    {
            return m1 = solve (m2, t * m1, C ());
        }

        /** \brief general matrix multiplication \f$m_1=t_1.m_1 + t_2.m_2.m_3\f$
     *
     * \param m1 first matrix
     * \param t1 first scalar
     * \param t2 second scalar
     * \param m2 second matrix
     * \param m3 third matrix
     * \return the matrix \c m1
     *
     * \tparam M1 type of the first matrix (not needed by default)
     * \tparam T1 type of the first scalar (not needed by default)
     * \tparam T2 type of the second scalar (not needed by default)
     * \tparam M2 type of the second matrix (not needed by default)
     * \tparam M3 type of the third matrix (not needed by default)
         */                 
        template<class M1, class T1, class T2, class M2, class M3>
        M1 & gmm (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2, const M3 &m3) 
    {
            return m1 = t1 * m1 + t2 * prod (m2, m3);
        }

        /** \brief symmetric rank \a k update: \f$m_1=t.m_1+t_2.(m_2.m_2^T)\f$
     *
     * \param m1 first matrix
     * \param t1 first scalar
     * \param t2 second scalar
     * \param m2 second matrix
     * \return matrix \c m1
     *
     * \tparam M1 type of the first matrix (not needed by default)
     * \tparam T1 type of the first scalar (not needed by default)
     * \tparam T2 type of the second scalar (not needed by default)
     * \tparam M2 type of the second matrix (not needed by default)
     * \todo use opb_prod()
         */                 
        template<class M1, class T1, class T2, class M2>
        M1 & srk (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2) 
    {
            return m1 = t1 * m1 + t2 * prod (m2, trans (m2));
        }

        /** \brief hermitian rank \a k update: \f$m_1=t.m_1+t_2.(m_2.m2^H)\f$
     *
     * \param m1 first matrix
     * \param t1 first scalar
     * \param t2 second scalar
     * \param m2 second matrix
     * \return matrix \c m1
     *
     * \tparam M1 type of the first matrix (not needed by default)
     * \tparam T1 type of the first scalar (not needed by default)
     * \tparam T2 type of the second scalar (not needed by default)
     * \tparam M2 type of the second matrix (not needed by default)
     * \todo use opb_prod()
         */                 
        template<class M1, class T1, class T2, class M2>
        M1 & hrk (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2) 
    {
            return m1 = t1 * m1 + t2 * prod (m2, herm (m2));
        }

        /** \brief generalized symmetric rank \a k update: \f$m_1=t_1.m_1+t_2.(m_2.m3^T)+t_2.(m_3.m2^T)\f$
     *
     * \param m1 first matrix
     * \param t1 first scalar
     * \param t2 second scalar
     * \param m2 second matrix
     * \param m3 third matrix
     * \return matrix \c m1
     *
     * \tparam M1 type of the first matrix (not needed by default)
     * \tparam T1 type of the first scalar (not needed by default)
     * \tparam T2 type of the second scalar (not needed by default)
     * \tparam M2 type of the second matrix (not needed by default)
     * \tparam M3 type of the third matrix (not needed by default)
     * \todo use opb_prod()
         */                 
        template<class M1, class T1, class T2, class M2, class M3>
        M1 & sr2k (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2, const M3 &m3) 
    {
            return m1 = t1 * m1 + t2 * (prod (m2, trans (m3)) + prod (m3, trans (m2)));
        }

        /** \brief generalized hermitian rank \a k update: * \f$m_1=t_1.m_1+t_2.(m_2.m_3^H)+(m_3.(t_2.m_2)^H)\f$
     *
     * \param m1 first matrix
     * \param t1 first scalar
     * \param t2 second scalar
     * \param m2 second matrix
     * \param m3 third matrix
     * \return matrix \c m1
     *
     * \tparam M1 type of the first matrix (not needed by default)
     * \tparam T1 type of the first scalar (not needed by default)
     * \tparam T2 type of the second scalar (not needed by default)
     * \tparam M2 type of the second matrix (not needed by default)
     * \tparam M3 type of the third matrix (not needed by default)
     * \todo use opb_prod()
         */                 
        template<class M1, class T1, class T2, class M2, class M3>
        M1 & hr2k (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2, const M3 &m3) 
    {
            return m1 = 
              t1 * m1 
            + t2 * prod (m2, herm (m3)) 
            + type_traits<T2>::conj (t2) * prod (m3, herm (m2));
        }

    }

}}}

#endif

/* blas.hpp
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
*/
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
//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_OPERATION_
#define _BOOST_UBLAS_OPERATION_

#include <boost/numeric/ublas/matrix_proxy.hpp>

/** \file operation.hpp
 *  \brief This file contains some specialized products.
 */

// axpy-based products
// Alexei Novakov had a lot of ideas to improve these. Thanks.
// Hendrik Kueck proposed some new kernel. Thanks again.

namespace boost { namespace numeric { namespace ublas {

    template<class V, class T1, class L1, class IA1, class TA1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const compressed_matrix<T1, L1, 0, IA1, TA1> &e1,
               const vector_expression<E2> &e2,
               V &v, row_major_tag) {
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;

        for (size_type i = 0; i < e1.filled1 () -1; ++ i) {
            size_type begin = e1.index1_data () [i];
            size_type end = e1.index1_data () [i + 1];
            value_type t (v (i));
            for (size_type j = begin; j < end; ++ j)
                t += e1.value_data () [j] * e2 () (e1.index2_data () [j]);
            v (i) = t;
        }
        return v;
    }

    template<class V, class T1, class L1, class IA1, class TA1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const compressed_matrix<T1, L1, 0, IA1, TA1> &e1,
               const vector_expression<E2> &e2,
               V &v, column_major_tag) {
        typedef typename V::size_type size_type;

        for (size_type j = 0; j < e1.filled1 () -1; ++ j) {
            size_type begin = e1.index1_data () [j];
            size_type end = e1.index1_data () [j + 1];
            for (size_type i = begin; i < end; ++ i)
                v (e1.index2_data () [i]) += e1.value_data () [i] * e2 () (j);
        }
        return v;
    }

    // Dispatcher
    template<class V, class T1, class L1, class IA1, class TA1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const compressed_matrix<T1, L1, 0, IA1, TA1> &e1,
               const vector_expression<E2> &e2,
               V &v, bool init = true) {
        typedef typename V::value_type value_type;
        typedef typename L1::orientation_category orientation_category;

        if (init)
            v.assign (zero_vector<value_type> (e1.size1 ()));
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type verrorbound (norm_1 (v) + norm_1 (e1) * norm_1 (e2));
        indexing_vector_assign<scalar_plus_assign> (cv, prod (e1, e2));
#endif
        axpy_prod (e1, e2, v, orientation_category ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (v - cv) <= 2 * std::numeric_limits<real_type>::epsilon () * verrorbound, internal_logic ());
#endif
        return v;
    }
    template<class V, class T1, class L1, class IA1, class TA1, class E2>
    BOOST_UBLAS_INLINE
    V
    axpy_prod (const compressed_matrix<T1, L1, 0, IA1, TA1> &e1,
               const vector_expression<E2> &e2) {
        typedef V vector_type;

        vector_type v (e1.size1 ());
        return axpy_prod (e1, e2, v, true);
    }

    template<class V, class T1, class L1, class IA1, class TA1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const coordinate_matrix<T1, L1, 0, IA1, TA1> &e1,
               const vector_expression<E2> &e2,
               V &v, bool init = true) {
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;
        typedef L1 layout_type;

        size_type size1 = e1.size1();
        size_type size2 = e1.size2();

        if (init) {
            noalias(v) = zero_vector<value_type>(size1);
        }

        for (size_type i = 0; i < e1.nnz(); ++i) {
            size_type row_index = layout_type::index_M( e1.index1_data () [i], e1.index2_data () [i] );
            size_type col_index = layout_type::index_m( e1.index1_data () [i], e1.index2_data () [i] );
            v( row_index ) += e1.value_data () [i] * e2 () (col_index);
        }
        return v;
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, packed_random_access_iterator_tag, row_major_tag) {
        typedef const E1 expression1_type;
        typedef typename V::size_type size_type;

        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            size_type index1 (it1.index1 ());
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
#else
            typename expression1_type::const_iterator2 it2 (boost::numeric::ublas::begin (it1, iterator1_tag ()));
            typename expression1_type::const_iterator2 it2_end (boost::numeric::ublas::end (it1, iterator1_tag ()));
#endif
            while (it2 != it2_end) {
                v (index1) += *it2 * e2 () (it2.index2 ());
                ++ it2;
            }
            ++ it1;
        }
        return v;
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, packed_random_access_iterator_tag, column_major_tag) {
        typedef const E1 expression1_type;
        typedef typename V::size_type size_type;

        typename expression1_type::const_iterator2 it2 (e1 ().begin2 ());
        typename expression1_type::const_iterator2 it2_end (e1 ().end2 ());
        while (it2 != it2_end) {
            size_type index2 (it2.index2 ());
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression1_type::const_iterator1 it1 (it2.begin ());
            typename expression1_type::const_iterator1 it1_end (it2.end ());
#else
            typename expression1_type::const_iterator1 it1 (boost::numeric::ublas::begin (it2, iterator2_tag ()));
            typename expression1_type::const_iterator1 it1_end (boost::numeric::ublas::end (it2, iterator2_tag ()));
#endif
            while (it1 != it1_end) {
                v (it1.index1 ()) += *it1 * e2 () (index2);
                ++ it1;
            }
            ++ it2;
        }
        return v;
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, sparse_bidirectional_iterator_tag) {
        typedef const E2 expression2_type;

        typename expression2_type::const_iterator it (e2 ().begin ());
        typename expression2_type::const_iterator it_end (e2 ().end ());
        while (it != it_end) {
            v.plus_assign (column (e1 (), it.index ()) * *it);
            ++ it;
        }
        return v;
    }

    // Dispatcher
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, packed_random_access_iterator_tag) {
        typedef typename E1::orientation_category orientation_category;
        return axpy_prod (e1, e2, v, packed_random_access_iterator_tag (), orientation_category ());
    }


  /** \brief computes <tt>v += A x</tt> or <tt>v = A x</tt> in an
          optimized fashion.

          \param e1 the matrix expression \c A
          \param e2 the vector expression \c x
          \param v  the result vector \c v
          \param init a boolean parameter

          <tt>axpy_prod(A, x, v, init)</tt> implements the well known
          axpy-product.  Setting \a init to \c true is equivalent to call
          <tt>v.clear()</tt> before <tt>axpy_prod</tt>. Currently \a init
          defaults to \c true, but this may change in the future.

          Up to now there are some specialisation for compressed
          matrices that give a large speed up compared to prod.
          
          \ingroup blas2

          \internal
          
          template parameters:
          \param V type of the result vector \c v
          \param E1 type of a matrix expression \c A
          \param E2 type of a vector expression \c x
  */
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2,
               V &v, bool init = true) {
        typedef typename V::value_type value_type;
        typedef typename E2::const_iterator::iterator_category iterator_category;

        if (init)
            v.assign (zero_vector<value_type> (e1 ().size1 ()));
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type verrorbound (norm_1 (v) + norm_1 (e1) * norm_1 (e2));
        indexing_vector_assign<scalar_plus_assign> (cv, prod (e1, e2));
#endif
        axpy_prod (e1, e2, v, iterator_category ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (v - cv) <= 2 * std::numeric_limits<real_type>::epsilon () * verrorbound, internal_logic ());
#endif
        return v;
    }
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V
    axpy_prod (const matrix_expression<E1> &e1,
               const vector_expression<E2> &e2) {
        typedef V vector_type;

        vector_type v (e1 ().size1 ());
        return axpy_prod (e1, e2, v, true);
    }

    template<class V, class E1, class T2, class IA2, class TA2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const compressed_matrix<T2, column_major, 0, IA2, TA2> &e2,
               V &v, column_major_tag) {
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;

        for (size_type j = 0; j < e2.filled1 () -1; ++ j) {
            size_type begin = e2.index1_data () [j];
            size_type end = e2.index1_data () [j + 1];
            value_type t (v (j));
            for (size_type i = begin; i < end; ++ i)
                t += e2.value_data () [i] * e1 () (e2.index2_data () [i]);
            v (j) = t;
        }
        return v;
    }

    template<class V, class E1, class T2, class IA2, class TA2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const compressed_matrix<T2, row_major, 0, IA2, TA2> &e2,
               V &v, row_major_tag) {
        typedef typename V::size_type size_type;

        for (size_type i = 0; i < e2.filled1 () -1; ++ i) {
            size_type begin = e2.index1_data () [i];
            size_type end = e2.index1_data () [i + 1];
            for (size_type j = begin; j < end; ++ j)
                v (e2.index2_data () [j]) += e2.value_data () [j] * e1 () (i);
        }
        return v;
    }

    // Dispatcher
    template<class V, class E1, class T2, class L2, class IA2, class TA2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const compressed_matrix<T2, L2, 0, IA2, TA2> &e2,
               V &v, bool init = true) {
        typedef typename V::value_type value_type;
        typedef typename L2::orientation_category orientation_category;

        if (init)
            v.assign (zero_vector<value_type> (e2.size2 ()));
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type verrorbound (norm_1 (v) + norm_1 (e1) * norm_1 (e2));
        indexing_vector_assign<scalar_plus_assign> (cv, prod (e1, e2));
#endif
        axpy_prod (e1, e2, v, orientation_category ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (v - cv) <= 2 * std::numeric_limits<real_type>::epsilon () * verrorbound, internal_logic ());
#endif
        return v;
    }
    template<class V, class E1, class T2, class L2, class IA2, class TA2>
    BOOST_UBLAS_INLINE
    V
    axpy_prod (const vector_expression<E1> &e1,
               const compressed_matrix<T2, L2, 0, IA2, TA2> &e2) {
        typedef V vector_type;

        vector_type v (e2.size2 ());
        return axpy_prod (e1, e2, v, true);
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, packed_random_access_iterator_tag, column_major_tag) {
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;

        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            size_type index2 (it2.index2 ());
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
#else
            typename expression2_type::const_iterator1 it1 (boost::numeric::ublas::begin (it2, iterator2_tag ()));
            typename expression2_type::const_iterator1 it1_end (boost::numeric::ublas::end (it2, iterator2_tag ()));
#endif
            while (it1 != it1_end) {
                v (index2) += *it1 * e1 () (it1.index1 ());
                ++ it1;
            }
            ++ it2;
        }
        return v;
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, packed_random_access_iterator_tag, row_major_tag) {
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;

        typename expression2_type::const_iterator1 it1 (e2 ().begin1 ());
        typename expression2_type::const_iterator1 it1_end (e2 ().end1 ());
        while (it1 != it1_end) {
            size_type index1 (it1.index1 ());
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression2_type::const_iterator2 it2 (it1.begin ());
            typename expression2_type::const_iterator2 it2_end (it1.end ());
#else
            typename expression2_type::const_iterator2 it2 (boost::numeric::ublas::begin (it1, iterator1_tag ()));
            typename expression2_type::const_iterator2 it2_end (boost::numeric::ublas::end (it1, iterator1_tag ()));
#endif
            while (it2 != it2_end) {
                v (it2.index2 ()) += *it2 * e1 () (index1);
                ++ it2;
            }
            ++ it1;
        }
        return v;
    }

    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, sparse_bidirectional_iterator_tag) {
        typedef const E1 expression1_type;

        typename expression1_type::const_iterator it (e1 ().begin ());
        typename expression1_type::const_iterator it_end (e1 ().end ());
        while (it != it_end) {
            v.plus_assign (*it * row (e2 (), it.index ()));
            ++ it;
        }
        return v;
    }

    // Dispatcher
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, packed_random_access_iterator_tag) {
        typedef typename E2::orientation_category orientation_category;
        return axpy_prod (e1, e2, v, packed_random_access_iterator_tag (), orientation_category ());
    }


  /** \brief computes <tt>v += A<sup>T</sup> x</tt> or <tt>v = A<sup>T</sup> x</tt> in an
          optimized fashion.

          \param e1 the vector expression \c x
          \param e2 the matrix expression \c A
          \param v  the result vector \c v
          \param init a boolean parameter

          <tt>axpy_prod(x, A, v, init)</tt> implements the well known
          axpy-product.  Setting \a init to \c true is equivalent to call
          <tt>v.clear()</tt> before <tt>axpy_prod</tt>. Currently \a init
          defaults to \c true, but this may change in the future.

          Up to now there are some specialisation for compressed
          matrices that give a large speed up compared to prod.
          
          \ingroup blas2

          \internal
          
          template parameters:
          \param V type of the result vector \c v
          \param E1 type of a vector expression \c x
          \param E2 type of a matrix expression \c A
  */
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V &
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               V &v, bool init = true) {
        typedef typename V::value_type value_type;
        typedef typename E1::const_iterator::iterator_category iterator_category;

        if (init)
            v.assign (zero_vector<value_type> (e2 ().size2 ()));
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type verrorbound (norm_1 (v) + norm_1 (e1) * norm_1 (e2));
        indexing_vector_assign<scalar_plus_assign> (cv, prod (e1, e2));
#endif
        axpy_prod (e1, e2, v, iterator_category ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (v - cv) <= 2 * std::numeric_limits<real_type>::epsilon () * verrorbound, internal_logic ());
#endif
        return v;
    }
    template<class V, class E1, class E2>
    BOOST_UBLAS_INLINE
    V
    axpy_prod (const vector_expression<E1> &e1,
               const matrix_expression<E2> &e2) {
        typedef V vector_type;

        vector_type v (e2 ().size2 ());
        return axpy_prod (e1, e2, v, true);
    }

    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, TRI,
               dense_proxy_tag, row_major_tag) {

        typedef typename M::size_type size_type;

#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, row_major> cm (m);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_plus_assign> (cm, prod (e1, e2), row_major_tag ());
#endif
        size_type size1 (e1 ().size1 ());
        size_type size2 (e1 ().size2 ());
        for (size_type i = 0; i < size1; ++ i)
            for (size_type j = 0; j < size2; ++ j)
                row (m, i).plus_assign (e1 () (i, j) * row (e2 (), j));
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }
    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, TRI,
               sparse_proxy_tag, row_major_tag) {

        typedef TRI triangular_restriction;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;

#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, row_major> cm (m);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_plus_assign> (cm, prod (e1, e2), row_major_tag ());
#endif
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
#else
            typename expression1_type::const_iterator2 it2 (boost::numeric::ublas::begin (it1, iterator1_tag ()));
            typename expression1_type::const_iterator2 it2_end (boost::numeric::ublas::end (it1, iterator1_tag ()));
#endif
            while (it2 != it2_end) {
                // row (m, it1.index1 ()).plus_assign (*it2 * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                while (itr != itr_end) {
                    if (triangular_restriction::other (it1.index1 (), itr.index ()))
                        m (it1.index1 (), itr.index ()) += *it2 * *itr;
                    ++ itr;
                }
                ++ it2;
            }
            ++ it1;
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }

    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, TRI,
               dense_proxy_tag, column_major_tag) {
        typedef typename M::size_type size_type;

#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, column_major> cm (m);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_plus_assign> (cm, prod (e1, e2), column_major_tag ());
#endif
        size_type size1 (e2 ().size1 ());
        size_type size2 (e2 ().size2 ());
        for (size_type j = 0; j < size2; ++ j)
            for (size_type i = 0; i < size1; ++ i)
                column (m, j).plus_assign (e2 () (i, j) * column (e1 (), i));
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }
    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, TRI,
               sparse_proxy_tag, column_major_tag) {
        typedef TRI triangular_restriction;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;


#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, column_major> cm (m);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_plus_assign> (cm, prod (e1, e2), column_major_tag ());
#endif
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression2_type::const_iterator1 it1 (it2.begin ());
            typename expression2_type::const_iterator1 it1_end (it2.end ());
#else
            typename expression2_type::const_iterator1 it1 (boost::numeric::ublas::begin (it2, iterator2_tag ()));
            typename expression2_type::const_iterator1 it1_end (boost::numeric::ublas::end (it2, iterator2_tag ()));
#endif
            while (it1 != it1_end) {
                // column (m, it2.index2 ()).plus_assign (*it1 * column (e1 (), it1.index1 ()));
                matrix_column<expression1_type> mc (e1 (), it1.index1 ());
                typename matrix_column<expression1_type>::const_iterator itc (mc.begin ());
                typename matrix_column<expression1_type>::const_iterator itc_end (mc.end ());
                while (itc != itc_end) {
                    if(triangular_restriction::other (itc.index (), it2.index2 ()))
                       m (itc.index (), it2.index2 ()) += *it1 * *itc;
                    ++ itc;
                }
                ++ it1;
            }
            ++ it2;
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }

    // Dispatcher
    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, TRI, bool init = true) {
        typedef typename M::value_type value_type;
        typedef typename M::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;
        typedef TRI triangular_restriction;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return axpy_prod (e1, e2, m, triangular_restriction (), storage_category (), orientation_category ());
    }
    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               TRI) {
        typedef M matrix_type;
        typedef TRI triangular_restriction;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        return axpy_prod (e1, e2, m, triangular_restriction (), true);
    }

  /** \brief computes <tt>M += A X</tt> or <tt>M = A X</tt> in an
          optimized fashion.

          \param e1 the matrix expression \c A
          \param e2 the matrix expression \c X
          \param m  the result matrix \c M
          \param init a boolean parameter

          <tt>axpy_prod(A, X, M, init)</tt> implements the well known
          axpy-product.  Setting \a init to \c true is equivalent to call
          <tt>M.clear()</tt> before <tt>axpy_prod</tt>. Currently \a init
          defaults to \c true, but this may change in the future.

          Up to now there are no specialisations.
          
          \ingroup blas3

          \internal
          
          template parameters:
          \param M type of the result matrix \c M
          \param E1 type of a matrix expression \c A
          \param E2 type of a matrix expression \c X
  */
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2,
               M &m, bool init = true) {
        typedef typename M::value_type value_type;
        typedef typename M::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return axpy_prod (e1, e2, m, full (), storage_category (), orientation_category ());
    }
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    axpy_prod (const matrix_expression<E1> &e1,
               const matrix_expression<E2> &e2) {
        typedef M matrix_type;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        return axpy_prod (e1, e2, m, full (), true);
    }


    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    opb_prod (const matrix_expression<E1> &e1,
              const matrix_expression<E2> &e2,
              M &m,
              dense_proxy_tag, row_major_tag) {
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#if BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (m);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_plus_assign> (cm, prod (e1, e2), row_major_tag ());
#endif
        size_type size (BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ()));
        for (size_type k = 0; k < size; ++ k) {
            vector<value_type> ce1 (column (e1 (), k));
            vector<value_type> re2 (row (e2 (), k));
            m.plus_assign (outer_prod (ce1, re2));
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }

    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    opb_prod (const matrix_expression<E1> &e1,
              const matrix_expression<E2> &e2,
              M &m,
              dense_proxy_tag, column_major_tag) {
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#if BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, column_major> cm (m);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_plus_assign> (cm, prod (e1, e2), column_major_tag ());
#endif
        size_type size (BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ()));
        for (size_type k = 0; k < size; ++ k) {
            vector<value_type> ce1 (column (e1 (), k));
            vector<value_type> re2 (row (e2 (), k));
            m.plus_assign (outer_prod (ce1, re2));
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }

    // Dispatcher

  /** \brief computes <tt>M += A X</tt> or <tt>M = A X</tt> in an
          optimized fashion.

          \param e1 the matrix expression \c A
          \param e2 the matrix expression \c X
          \param m  the result matrix \c M
          \param init a boolean parameter

          <tt>opb_prod(A, X, M, init)</tt> implements the well known
          axpy-product. Setting \a init to \c true is equivalent to call
          <tt>M.clear()</tt> before <tt>opb_prod</tt>. Currently \a init
          defaults to \c true, but this may change in the future.

          This function may give a speedup if \c A has less columns than
          rows, because the product is computed as a sum of outer
          products.
          
          \ingroup blas3

          \internal
          
          template parameters:
          \param M type of the result matrix \c M
          \param E1 type of a matrix expression \c A
          \param E2 type of a matrix expression \c X
  */
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    opb_prod (const matrix_expression<E1> &e1,
              const matrix_expression<E2> &e2,
              M &m, bool init = true) {
        typedef typename M::value_type value_type;
        typedef typename M::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return opb_prod (e1, e2, m, storage_category (), orientation_category ());
    }
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    opb_prod (const matrix_expression<E1> &e1,
              const matrix_expression<E2> &e2) {
        typedef M matrix_type;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        return opb_prod (e1, e2, m, true);
    }

}}}

#endif

/* operation.hpp
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
*/
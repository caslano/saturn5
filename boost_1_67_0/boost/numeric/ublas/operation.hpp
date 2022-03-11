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
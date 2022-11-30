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

#ifndef _BOOST_UBLAS_OPERATION_BLOCKED_
#define _BOOST_UBLAS_OPERATION_BLOCKED_

#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/detail/vector_assign.hpp> // indexing_vector_assign
#include <boost/numeric/ublas/detail/matrix_assign.hpp> // indexing_matrix_assign


namespace boost { namespace numeric { namespace ublas {

    template<class V, typename V::size_type BS, class E1, class E2>
    BOOST_UBLAS_INLINE
    V
    block_prod (const matrix_expression<E1> &e1,
                const vector_expression<E2> &e2) {
        typedef V vector_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;
        const size_type block_size = BS;

        V v (e1 ().size1 ());
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        typedef typename type_traits<value_type>::real_type real_type;
        real_type verrorbound (norm_1 (v) + norm_1 (e1) * norm_1 (e2));
        indexing_vector_assign<scalar_assign> (cv, prod (e1, e2));
#endif
        size_type i_size = e1 ().size1 ();
        size_type j_size = BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size ());
        for (size_type i_begin = 0; i_begin < i_size; i_begin += block_size) {
            size_type i_end = i_begin + (std::min) (i_size - i_begin, block_size);
            // FIX: never ignore Martin Weiser's advice ;-(
#ifdef BOOST_UBLAS_NO_CACHE
            vector_range<vector_type> v_range (v, range (i_begin, i_end));
#else
            // vector<value_type, bounded_array<value_type, block_size> > v_range (i_end - i_begin);
            vector<value_type> v_range (i_end - i_begin);
#endif
            v_range.assign (zero_vector<value_type> (i_end - i_begin));
            for (size_type j_begin = 0; j_begin < j_size; j_begin += block_size) {
                size_type j_end = j_begin + (std::min) (j_size - j_begin, block_size);
#ifdef BOOST_UBLAS_NO_CACHE
                const matrix_range<expression1_type> e1_range (e1 (), range (i_begin, i_end), range (j_begin, j_end));
                const vector_range<expression2_type> e2_range (e2 (), range (j_begin, j_end));
                v_range.plus_assign (prod (e1_range, e2_range));
#else
                // const matrix<value_type, row_major, bounded_array<value_type, block_size * block_size> > e1_range (project (e1 (), range (i_begin, i_end), range (j_begin, j_end)));
                // const vector<value_type, bounded_array<value_type, block_size> > e2_range (project (e2 (), range (j_begin, j_end)));
                const matrix<value_type, row_major> e1_range (project (e1 (), range (i_begin, i_end), range (j_begin, j_end)));
                const vector<value_type> e2_range (project (e2 (), range (j_begin, j_end)));
                v_range.plus_assign (prod (e1_range, e2_range));
#endif
            }
#ifndef BOOST_UBLAS_NO_CACHE
            project (v, range (i_begin, i_end)).assign (v_range);
#endif
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (v - cv) <= 2 * std::numeric_limits<real_type>::epsilon () * verrorbound, internal_logic ());
#endif
        return v;
    }

    template<class V, typename V::size_type BS, class E1, class E2>
    BOOST_UBLAS_INLINE
    V
    block_prod (const vector_expression<E1> &e1,
                const matrix_expression<E2> &e2) {
        typedef V vector_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;
        const size_type block_size = BS;

        V v (e2 ().size2 ());
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        typedef typename type_traits<value_type>::real_type real_type;
        real_type verrorbound (norm_1 (v) + norm_1 (e1) * norm_1 (e2));
        indexing_vector_assign<scalar_assign> (cv, prod (e1, e2));
#endif
        size_type i_size = BOOST_UBLAS_SAME (e1 ().size (), e2 ().size1 ());
        size_type j_size = e2 ().size2 ();
        for (size_type j_begin = 0; j_begin < j_size; j_begin += block_size) {
            size_type j_end = j_begin + (std::min) (j_size - j_begin, block_size);
            // FIX: never ignore Martin Weiser's advice ;-(
#ifdef BOOST_UBLAS_NO_CACHE
            vector_range<vector_type> v_range (v, range (j_begin, j_end));
#else
            // vector<value_type, bounded_array<value_type, block_size> > v_range (j_end - j_begin);
            vector<value_type> v_range (j_end - j_begin);
#endif
            v_range.assign (zero_vector<value_type> (j_end - j_begin));
            for (size_type i_begin = 0; i_begin < i_size; i_begin += block_size) {
                size_type i_end = i_begin + (std::min) (i_size - i_begin, block_size);
#ifdef BOOST_UBLAS_NO_CACHE
                const vector_range<expression1_type> e1_range (e1 (), range (i_begin, i_end));
                const matrix_range<expression2_type> e2_range (e2 (), range (i_begin, i_end), range (j_begin, j_end));
#else
                // const vector<value_type, bounded_array<value_type, block_size> > e1_range (project (e1 (), range (i_begin, i_end)));
                // const matrix<value_type, column_major, bounded_array<value_type, block_size * block_size> > e2_range (project (e2 (), range (i_begin, i_end), range (j_begin, j_end)));
                const vector<value_type> e1_range (project (e1 (), range (i_begin, i_end)));
                const matrix<value_type, column_major> e2_range (project (e2 (), range (i_begin, i_end), range (j_begin, j_end)));
#endif
                v_range.plus_assign (prod (e1_range, e2_range));
            }
#ifndef BOOST_UBLAS_NO_CACHE
            project (v, range (j_begin, j_end)).assign (v_range);
#endif
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (v - cv) <= 2 * std::numeric_limits<real_type>::epsilon () * verrorbound, internal_logic ());
#endif
        return v;
    }

    template<class M, typename M::size_type BS, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    block_prod (const matrix_expression<E1> &e1,
                const matrix_expression<E2> &e2,
                row_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;
        const size_type block_size = BS;

        M m (e1 ().size1 (), e2 ().size2 ());
#if BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (m.size1 (), m.size2 ());
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_assign> (cm, prod (e1, e2), row_major_tag ());
        disable_type_check<bool>::value = true;
#endif
        size_type i_size = e1 ().size1 ();
        size_type j_size = e2 ().size2 ();
        size_type k_size = BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ());
        for (size_type i_begin = 0; i_begin < i_size; i_begin += block_size) {
            size_type i_end = i_begin + (std::min) (i_size - i_begin, block_size);
            for (size_type j_begin = 0; j_begin < j_size; j_begin += block_size) {
                size_type j_end = j_begin + (std::min) (j_size - j_begin, block_size);
                // FIX: never ignore Martin Weiser's advice ;-(
#ifdef BOOST_UBLAS_NO_CACHE
                matrix_range<matrix_type> m_range (m, range (i_begin, i_end), range (j_begin, j_end));
#else
                // matrix<value_type, row_major, bounded_array<value_type, block_size * block_size> > m_range (i_end - i_begin, j_end - j_begin);
                matrix<value_type, row_major> m_range (i_end - i_begin, j_end - j_begin);
#endif
                m_range.assign (zero_matrix<value_type> (i_end - i_begin, j_end - j_begin));
                for (size_type k_begin = 0; k_begin < k_size; k_begin += block_size) {
                    size_type k_end = k_begin + (std::min) (k_size - k_begin, block_size);
#ifdef BOOST_UBLAS_NO_CACHE
                    const matrix_range<expression1_type> e1_range (e1 (), range (i_begin, i_end), range (k_begin, k_end));
                    const matrix_range<expression2_type> e2_range (e2 (), range (k_begin, k_end), range (j_begin, j_end));
#else
                    // const matrix<value_type, row_major, bounded_array<value_type, block_size * block_size> > e1_range (project (e1 (), range (i_begin, i_end), range (k_begin, k_end)));
                    // const matrix<value_type, column_major, bounded_array<value_type, block_size * block_size> > e2_range (project (e2 (), range (k_begin, k_end), range (j_begin, j_end)));
                    const matrix<value_type, row_major> e1_range (project (e1 (), range (i_begin, i_end), range (k_begin, k_end)));
                    const matrix<value_type, column_major> e2_range (project (e2 (), range (k_begin, k_end), range (j_begin, j_end)));
#endif
                    m_range.plus_assign (prod (e1_range, e2_range));
                }
#ifndef BOOST_UBLAS_NO_CACHE
                project (m, range (i_begin, i_end), range (j_begin, j_end)).assign (m_range);
#endif
            }
        }
#if BOOST_UBLAS_TYPE_CHECK
        disable_type_check<bool>::value = false;
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }

    template<class M, typename M::size_type BS, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    block_prod (const matrix_expression<E1> &e1,
                const matrix_expression<E2> &e2,
                column_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;
        const size_type block_size = BS;

        M m (e1 ().size1 (), e2 ().size2 ());
#if BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, column_major> cm (m.size1 (), m.size2 ());
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_assign> (cm, prod (e1, e2), column_major_tag ());
        disable_type_check<bool>::value = true;
#endif
        size_type i_size = e1 ().size1 ();
        size_type j_size = e2 ().size2 ();
        size_type k_size = BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ());
        for (size_type j_begin = 0; j_begin < j_size; j_begin += block_size) {
            size_type j_end = j_begin + (std::min) (j_size - j_begin, block_size);
            for (size_type i_begin = 0; i_begin < i_size; i_begin += block_size) {
                size_type i_end = i_begin + (std::min) (i_size - i_begin, block_size);
                // FIX: never ignore Martin Weiser's advice ;-(
#ifdef BOOST_UBLAS_NO_CACHE
                matrix_range<matrix_type> m_range (m, range (i_begin, i_end), range (j_begin, j_end));
#else
                // matrix<value_type, column_major, bounded_array<value_type, block_size * block_size> > m_range (i_end - i_begin, j_end - j_begin);
                matrix<value_type, column_major> m_range (i_end - i_begin, j_end - j_begin);
#endif
                m_range.assign (zero_matrix<value_type> (i_end - i_begin, j_end - j_begin));
                for (size_type k_begin = 0; k_begin < k_size; k_begin += block_size) {
                    size_type k_end = k_begin + (std::min) (k_size - k_begin, block_size);
#ifdef BOOST_UBLAS_NO_CACHE
                    const matrix_range<expression1_type> e1_range (e1 (), range (i_begin, i_end), range (k_begin, k_end));
                    const matrix_range<expression2_type> e2_range (e2 (), range (k_begin, k_end), range (j_begin, j_end));
#else
                    // const matrix<value_type, row_major, bounded_array<value_type, block_size * block_size> > e1_range (project (e1 (), range (i_begin, i_end), range (k_begin, k_end)));
                    // const matrix<value_type, column_major, bounded_array<value_type, block_size * block_size> > e2_range (project (e2 (), range (k_begin, k_end), range (j_begin, j_end)));
                    const matrix<value_type, row_major> e1_range (project (e1 (), range (i_begin, i_end), range (k_begin, k_end)));
                    const matrix<value_type, column_major> e2_range (project (e2 (), range (k_begin, k_end), range (j_begin, j_end)));
#endif
                    m_range.plus_assign (prod (e1_range, e2_range));
                }
#ifndef BOOST_UBLAS_NO_CACHE
                project (m, range (i_begin, i_end), range (j_begin, j_end)).assign (m_range);
#endif
            }
        }
#if BOOST_UBLAS_TYPE_CHECK
        disable_type_check<bool>::value = false;
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }

    // Dispatcher
    template<class M, typename M::size_type BS, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    block_prod (const matrix_expression<E1> &e1,
                const matrix_expression<E2> &e2) {
        typedef typename M::orientation_category orientation_category;
        return block_prod<M, BS> (e1, e2, orientation_category ());
    }

}}}

#endif

/* operation_blocked.hpp
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
*/
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
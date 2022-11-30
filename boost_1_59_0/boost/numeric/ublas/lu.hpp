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

#ifndef _BOOST_UBLAS_LU_
#define _BOOST_UBLAS_LU_

#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/triangular.hpp>

// LU factorizations in the spirit of LAPACK and Golub & van Loan

namespace boost { namespace numeric { namespace ublas {

    /** \brief
     *
     * \tparam T
     * \tparam A
     */
    template<class T = std::size_t, class A = unbounded_array<T> >
    class permutation_matrix:
        public vector<T, A> {
    public:
        typedef vector<T, A> vector_type;
        typedef typename vector_type::size_type size_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        explicit
        permutation_matrix (size_type size):
            vector<T, A> (size) {
            for (size_type i = 0; i < size; ++ i)
                (*this) (i) = i;
        }
        BOOST_UBLAS_INLINE
        explicit
        permutation_matrix (const vector_type & init) 
            : vector_type(init)
        { }
        BOOST_UBLAS_INLINE
        ~permutation_matrix () {}

        // Assignment
        BOOST_UBLAS_INLINE
        permutation_matrix &operator = (const permutation_matrix &m) {
            vector_type::operator = (m);
            return *this;
        }
    };

    template<class PM, class MV>
    BOOST_UBLAS_INLINE
    void swap_rows (const PM &pm, MV &mv, vector_tag) {
        typedef typename PM::size_type size_type;

        size_type size = pm.size ();
        for (size_type i = 0; i < size; ++ i) {
            if (i != pm (i))
                std::swap (mv (i), mv (pm (i)));
        }
    }
    template<class PM, class MV>
    BOOST_UBLAS_INLINE
    void swap_rows (const PM &pm, MV &mv, matrix_tag) {
        typedef typename PM::size_type size_type;

        size_type size = pm.size ();
        for (size_type i = 0; i < size; ++ i) {
            if (i != pm (i))
                row (mv, i).swap (row (mv, pm (i)));
        }
    }
    // Dispatcher
    template<class PM, class MV>
    BOOST_UBLAS_INLINE
    void swap_rows (const PM &pm, MV &mv) {
        swap_rows (pm, mv, typename MV::type_category ());
    }

    // LU factorization without pivoting
    template<class M>
    typename M::size_type lu_factorize (M &m) {

        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#if BOOST_UBLAS_TYPE_CHECK
        typedef M matrix_type;
        matrix_type cm (m);
#endif
        size_type singular = 0;
        size_type size1 = m.size1 ();
        size_type size2 = m.size2 ();
        size_type size = (std::min) (size1, size2);
        for (size_type i = 0; i < size; ++ i) {
            matrix_column<M> mci (column (m, i));
            matrix_row<M> mri (row (m, i));
            if (m (i, i) != value_type/*zero*/()) {
                value_type m_inv = value_type (1) / m (i, i);
                project (mci, range (i + 1, size1)) *= m_inv;
            } else if (singular == 0) {
                singular = i + 1;
            }
            project (m, range (i + 1, size1), range (i + 1, size2)).minus_assign (
                outer_prod (project (mci, range (i + 1, size1)),
                            project (mri, range (i + 1, size2))));
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (singular != 0 ||
                           detail::expression_type_check (prod (triangular_adaptor<matrix_type, unit_lower> (m),
                                                                triangular_adaptor<matrix_type, upper> (m)), 
                                                          cm), internal_logic ());
#endif
        return singular;
    }

    // LU factorization with partial pivoting
    template<class M, class PM>
    typename M::size_type lu_factorize (M &m, PM &pm) {
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#if BOOST_UBLAS_TYPE_CHECK
        typedef M matrix_type;
        matrix_type cm (m);
#endif
        size_type singular = 0;
        size_type size1 = m.size1 ();
        size_type size2 = m.size2 ();
        size_type size = (std::min) (size1, size2);
        for (size_type i = 0; i < size; ++ i) {
            matrix_column<M> mci (column (m, i));
            matrix_row<M> mri (row (m, i));
            size_type i_norm_inf = i + index_norm_inf (project (mci, range (i, size1)));
            BOOST_UBLAS_CHECK (i_norm_inf < size1, external_logic ());
            if (m (i_norm_inf, i) != value_type/*zero*/()) {
                if (i_norm_inf != i) {
                    pm (i) = i_norm_inf;
                    row (m, i_norm_inf).swap (mri);
                } else {
                    BOOST_UBLAS_CHECK (pm (i) == i_norm_inf, external_logic ());
                }
                value_type m_inv = value_type (1) / m (i, i);
                project (mci, range (i + 1, size1)) *= m_inv;
            } else if (singular == 0) {
                singular = i + 1;
            }
            project (m, range (i + 1, size1), range (i + 1, size2)).minus_assign (
                outer_prod (project (mci, range (i + 1, size1)),
                            project (mri, range (i + 1, size2))));
        }
#if BOOST_UBLAS_TYPE_CHECK
        swap_rows (pm, cm);
        BOOST_UBLAS_CHECK (singular != 0 ||
                           detail::expression_type_check (prod (triangular_adaptor<matrix_type, unit_lower> (m),
                                                                triangular_adaptor<matrix_type, upper> (m)), cm), internal_logic ());
#endif
        return singular;
    }

    template<class M, class PM>
    typename M::size_type axpy_lu_factorize (M &m, PM &pm) {
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;
        typedef vector<value_type> vector_type;

#if BOOST_UBLAS_TYPE_CHECK
        matrix_type cm (m);
#endif
        size_type singular = 0;
        size_type size1 = m.size1 ();
        size_type size2 = m.size2 ();
        size_type size = (std::min) (size1, size2);
#ifndef BOOST_UBLAS_LU_WITH_INPLACE_SOLVE
        matrix_type mr (m);
        mr.assign (zero_matrix<value_type> (size1, size2));
        vector_type v (size1);
        for (size_type i = 0; i < size; ++ i) {
            matrix_range<matrix_type> lrr (project (mr, range (0, i), range (0, i)));
            vector_range<matrix_column<matrix_type> > urr (project (column (mr, i), range (0, i)));
            urr.assign (solve (lrr, project (column (m, i), range (0, i)), unit_lower_tag ()));
            project (v, range (i, size1)).assign (
                project (column (m, i), range (i, size1)) -
                axpy_prod<vector_type> (project (mr, range (i, size1), range (0, i)), urr));
            size_type i_norm_inf = i + index_norm_inf (project (v, range (i, size1)));
            BOOST_UBLAS_CHECK (i_norm_inf < size1, external_logic ());
            if (v (i_norm_inf) != value_type/*zero*/()) {
                if (i_norm_inf != i) {
                    pm (i) = i_norm_inf;
                    std::swap (v (i_norm_inf), v (i));
                    project (row (m, i_norm_inf), range (i + 1, size2)).swap (project (row (m, i), range (i + 1, size2)));
                } else {
                    BOOST_UBLAS_CHECK (pm (i) == i_norm_inf, external_logic ());
                }
                project (column (mr, i), range (i + 1, size1)).assign (
                    project (v, range (i + 1, size1)) / v (i));
                if (i_norm_inf != i) {
                    project (row (mr, i_norm_inf), range (0, i)).swap (project (row (mr, i), range (0, i)));
                }
            } else if (singular == 0) {
                singular = i + 1;
            }
            mr (i, i) = v (i);
        }
        m.assign (mr);
#else
        matrix_type lr (m);
        matrix_type ur (m);
        lr.assign (identity_matrix<value_type> (size1, size2));
        ur.assign (zero_matrix<value_type> (size1, size2));
        vector_type v (size1);
        for (size_type i = 0; i < size; ++ i) {
            matrix_range<matrix_type> lrr (project (lr, range (0, i), range (0, i)));
            vector_range<matrix_column<matrix_type> > urr (project (column (ur, i), range (0, i)));
            urr.assign (project (column (m, i), range (0, i)));
            inplace_solve (lrr, urr, unit_lower_tag ());
            project (v, range (i, size1)).assign (
                project (column (m, i), range (i, size1)) -
                axpy_prod<vector_type> (project (lr, range (i, size1), range (0, i)), urr));
            size_type i_norm_inf = i + index_norm_inf (project (v, range (i, size1)));
            BOOST_UBLAS_CHECK (i_norm_inf < size1, external_logic ());
            if (v (i_norm_inf) != value_type/*zero*/()) {
                if (i_norm_inf != i) {
                    pm (i) = i_norm_inf;
                    std::swap (v (i_norm_inf), v (i));
                    project (row (m, i_norm_inf), range (i + 1, size2)).swap (project (row (m, i), range (i + 1, size2)));
                } else {
                    BOOST_UBLAS_CHECK (pm (i) == i_norm_inf, external_logic ());
                }
                project (column (lr, i), range (i + 1, size1)).assign (
                    project (v, range (i + 1, size1)) / v (i));
                if (i_norm_inf != i) {
                    project (row (lr, i_norm_inf), range (0, i)).swap (project (row (lr, i), range (0, i)));
                }
            } else if (singular == 0) {
                singular = i + 1;
            }
            ur (i, i) = v (i);
        }
        m.assign (triangular_adaptor<matrix_type, strict_lower> (lr) +
                  triangular_adaptor<matrix_type, upper> (ur));
#endif
#if BOOST_UBLAS_TYPE_CHECK
        swap_rows (pm, cm);
        BOOST_UBLAS_CHECK (singular != 0 ||
                           detail::expression_type_check (prod (triangular_adaptor<matrix_type, unit_lower> (m),
                                                                triangular_adaptor<matrix_type, upper> (m)), cm), internal_logic ());
#endif
        return singular;
    }

    // LU substitution
    template<class M, class E>
    void lu_substitute (const M &m, vector_expression<E> &e) {
#if BOOST_UBLAS_TYPE_CHECK
        typedef const M const_matrix_type;
        typedef vector<typename E::value_type> vector_type;

        vector_type cv1 (e);
#endif
        inplace_solve (m, e, unit_lower_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (triangular_adaptor<const_matrix_type, unit_lower> (m), e), cv1), internal_logic ());
        vector_type cv2 (e);
#endif
        inplace_solve (m, e, upper_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (triangular_adaptor<const_matrix_type, upper> (m), e), cv2), internal_logic ());
#endif
    }
    template<class M, class E>
    void lu_substitute (const M &m, matrix_expression<E> &e) {
#if BOOST_UBLAS_TYPE_CHECK
        typedef const M const_matrix_type;
        typedef matrix<typename E::value_type> matrix_type;

        matrix_type cm1 (e);
#endif
        inplace_solve (m, e, unit_lower_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (triangular_adaptor<const_matrix_type, unit_lower> (m), e), cm1), internal_logic ());
        matrix_type cm2 (e);
#endif
        inplace_solve (m, e, upper_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (triangular_adaptor<const_matrix_type, upper> (m), e), cm2), internal_logic ());
#endif
    }
    template<class M, class PMT, class PMA, class MV>
    void lu_substitute (const M &m, const permutation_matrix<PMT, PMA> &pm, MV &mv) {
        swap_rows (pm, mv);
        lu_substitute (m, mv);
    }
    template<class E, class M>
    void lu_substitute (vector_expression<E> &e, const M &m) {
#if BOOST_UBLAS_TYPE_CHECK
        typedef const M const_matrix_type;
        typedef vector<typename E::value_type> vector_type;

        vector_type cv1 (e);
#endif
        inplace_solve (e, m, upper_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (e, triangular_adaptor<const_matrix_type, upper> (m)), cv1), internal_logic ());
        vector_type cv2 (e);
#endif
        inplace_solve (e, m, unit_lower_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (e, triangular_adaptor<const_matrix_type, unit_lower> (m)), cv2), internal_logic ());
#endif
    }
    template<class E, class M>
    void lu_substitute (matrix_expression<E> &e, const M &m) {
#if BOOST_UBLAS_TYPE_CHECK
        typedef const M const_matrix_type;
        typedef matrix<typename E::value_type> matrix_type;

        matrix_type cm1 (e);
#endif
        inplace_solve (e, m, upper_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (e, triangular_adaptor<const_matrix_type, upper> (m)), cm1), internal_logic ());
        matrix_type cm2 (e);
#endif
        inplace_solve (e, m, unit_lower_tag ());
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (detail::expression_type_check (prod (e, triangular_adaptor<const_matrix_type, unit_lower> (m)), cm2), internal_logic ());
#endif
    }
    template<class MV, class M, class PMT, class PMA>
    void lu_substitute (MV &mv, const M &m, const permutation_matrix<PMT, PMA> &pm) {
        swap_rows (pm, mv);
        lu_substitute (mv, m);
    }

}}}

#endif

/* lu.hpp
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
*/
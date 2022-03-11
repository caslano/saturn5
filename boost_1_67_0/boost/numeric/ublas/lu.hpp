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
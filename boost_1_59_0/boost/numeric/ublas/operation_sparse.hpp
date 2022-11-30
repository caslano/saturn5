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

#ifndef _BOOST_UBLAS_OPERATION_SPARSE_
#define _BOOST_UBLAS_OPERATION_SPARSE_

#include <boost/numeric/ublas/traits.hpp>

// These scaled additions were borrowed from MTL unashamedly.
// But Alexei Novakov had a lot of ideas to improve these. Thanks.

namespace boost { namespace numeric { namespace ublas {

    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, TRI,
                 row_major_tag) {
        typedef M matrix_type;
        typedef TRI triangular_restriction;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

        // ISSUE why is there a dense vector here?
        vector<value_type> temporary (e2 ().size2 ());
        temporary.clear ();
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            size_type jb (temporary.size ());
            size_type je (0);
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
#else
            typename expression1_type::const_iterator2 it2 (boost::numeric::ublas::begin (it1, iterator1_tag ()));
            typename expression1_type::const_iterator2 it2_end (boost::numeric::ublas::end (it1, iterator1_tag ()));
#endif
            while (it2 != it2_end) {
                // temporary.plus_assign (*it2 * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                while (itr != itr_end) {
                    size_type j (itr.index ());
                    temporary (j) += *it2 * *itr;
                    jb = (std::min) (jb, j);
                    je = (std::max) (je, j);
                    ++ itr;
                }
                ++ it2;
            }
            for (size_type j = jb; j < je + 1; ++ j) {
                if (temporary (j) != value_type/*zero*/()) {
                    // FIXME we'll need to extend the container interface!
                    // m.push_back (it1.index1 (), j, temporary (j));
                    // FIXME What to do with adaptors?
                    // m.insert (it1.index1 (), j, temporary (j));
                    if (triangular_restriction::other (it1.index1 (), j))
                        m (it1.index1 (), j) = temporary (j);
                    temporary (j) = value_type/*zero*/();
                }
            }
            ++ it1;
        }
        return m;
    }

    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, TRI,
                 column_major_tag) {
        typedef M matrix_type;
        typedef TRI triangular_restriction;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

        // ISSUE why is there a dense vector here?
        vector<value_type> temporary (e1 ().size1 ());
        temporary.clear ();
        typename expression2_type::const_iterator2 it2 (e2 ().begin2 ());
        typename expression2_type::const_iterator2 it2_end (e2 ().end2 ());
        while (it2 != it2_end) {
            size_type ib (temporary.size ());
            size_type ie (0);
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
                    size_type i (itc.index ());
                    temporary (i) += *it1 * *itc;
                    ib = (std::min) (ib, i);
                    ie = (std::max) (ie, i);
                    ++ itc;
                }
                ++ it1;
            }
            for (size_type i = ib; i < ie + 1; ++ i) {
                if (temporary (i) != value_type/*zero*/()) {
                    // FIXME we'll need to extend the container interface!
                    // m.push_back (i, it2.index2 (), temporary (i));
                    // FIXME What to do with adaptors?
                    // m.insert (i, it2.index2 (), temporary (i));
                    if (triangular_restriction::other (i, it2.index2 ()))
                        m (i, it2.index2 ()) = temporary (i);
                    temporary (i) = value_type/*zero*/();
                }
            }
            ++ it2;
        }
        return m;
    }

    // Dispatcher
    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, TRI, bool init = true) {
        typedef typename M::value_type value_type;
        typedef TRI triangular_restriction;
        typedef typename M::orientation_category orientation_category;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return sparse_prod (e1, e2, m, triangular_restriction (), orientation_category ());
    }
    template<class M, class E1, class E2, class TRI>
    BOOST_UBLAS_INLINE
    M
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 TRI) {
        typedef M matrix_type;
        typedef TRI triangular_restriction;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        // FIXME needed for c_matrix?!
        // return sparse_prod (e1, e2, m, triangular_restriction (), false);
        return sparse_prod (e1, e2, m, triangular_restriction (), true);
    }
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, bool init = true) {
        typedef typename M::value_type value_type;
        typedef typename M::orientation_category orientation_category;

        if (init)
            m.assign (zero_matrix<value_type> (e1 ().size1 (), e2 ().size2 ()));
        return sparse_prod (e1, e2, m, full (), orientation_category ());
    }
    template<class M, class E1, class E2>
    BOOST_UBLAS_INLINE
    M
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2) {
        typedef M matrix_type;

        matrix_type m (e1 ().size1 (), e2 ().size2 ());
        // FIXME needed for c_matrix?!
        // return sparse_prod (e1, e2, m, full (), false);
        return sparse_prod (e1, e2, m, full (), true);
    }

}}}

#endif

/* operation_sparse.hpp
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
*/
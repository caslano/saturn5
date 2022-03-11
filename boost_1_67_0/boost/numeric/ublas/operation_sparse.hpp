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
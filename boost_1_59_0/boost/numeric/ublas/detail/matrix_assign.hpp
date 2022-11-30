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

#ifndef _BOOST_UBLAS_MATRIX_ASSIGN_
#define _BOOST_UBLAS_MATRIX_ASSIGN_

#include <boost/numeric/ublas/traits.hpp>
// Required for make_conformant storage
#include <vector>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {
namespace detail {
    
    // Weak equality check - useful to compare equality two arbitary matrix expression results.
    // Since the actual expressions are unknown, we check for and arbitary error bound
    // on the relative error.
    // For a linear expression the infinity norm makes sense as we do not know how the elements will be
    // combined in the expression. False positive results are inevitable for arbirary expressions!
    template<class E1, class E2, class S>
    BOOST_UBLAS_INLINE
    bool equals (const matrix_expression<E1> &e1, const matrix_expression<E2> &e2, S epsilon, S min_norm) {
        return norm_inf (e1 - e2) <= epsilon *
               std::max<S> (std::max<S> (norm_inf (e1), norm_inf (e2)), min_norm);
    }

    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    bool expression_type_check (const matrix_expression<E1> &e1, const matrix_expression<E2> &e2) {
        typedef typename type_traits<typename promote_traits<typename E1::value_type,
                                     typename E2::value_type>::promote_type>::real_type real_type;
        return equals (e1, e2, BOOST_UBLAS_TYPE_CHECK_EPSILON, BOOST_UBLAS_TYPE_CHECK_MIN);
    }


    template<class M, class E, class R>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void make_conformant (M &m, const matrix_expression<E> &e, row_major_tag, R) {
        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());
        typedef R conformant_restrict_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        // FIXME unbounded_array with push_back maybe better
        std::vector<std::pair<size_type, size_type> > index;
        typename M::iterator1 it1 (m.begin1 ());
        typename M::iterator1 it1_end (m.end1 ());
        typename E::const_iterator1 it1e (e ().begin1 ());
        typename E::const_iterator1 it1e_end (e ().end1 ());
        while (it1 != it1_end && it1e != it1e_end) {
            difference_type compare = it1.index1 () - it1e.index1 ();
            if (compare == 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator2 it2 (it1.begin ());
                typename M::iterator2 it2_end (it1.end ());
                typename E::const_iterator2 it2e (it1e.begin ());
                typename E::const_iterator2 it2e_end (it1e.end ());
#else
                typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
                typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
                typename E::const_iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
                if (it2 != it2_end && it2e != it2e_end) {
                    size_type it2_index = it2.index2 (), it2e_index = it2e.index2 ();
                    for (;;) {
                        difference_type compare2 = it2_index - it2e_index;
                        if (compare2 == 0) {
                            ++ it2, ++ it2e;
                            if (it2 != it2_end && it2e != it2e_end) {
                                it2_index = it2.index2 ();
                                it2e_index = it2e.index2 ();
                            } else
                                break;
                        } else if (compare2 < 0) {
                            increment (it2, it2_end, - compare2);
                            if (it2 != it2_end)
                                it2_index = it2.index2 ();
                            else
                                break;
                        } else if (compare2 > 0) {
                            if (conformant_restrict_type::other (it2e.index1 (), it2e.index2 ()))
                                if (static_cast<value_type>(*it2e) != value_type/*zero*/())
                                    index.push_back (std::pair<size_type, size_type> (it2e.index1 (), it2e.index2 ()));
                            ++ it2e;
                            if (it2e != it2e_end)
                                it2e_index = it2e.index2 ();
                            else
                                break;
                        }
                    }
                }
                while (it2e != it2e_end) {
                    if (conformant_restrict_type::other (it2e.index1 (), it2e.index2 ()))
                        if (static_cast<value_type>(*it2e) != value_type/*zero*/())
                            index.push_back (std::pair<size_type, size_type> (it2e.index1 (), it2e.index2 ()));
                    ++ it2e;
                }
                ++ it1, ++ it1e;
            } else if (compare < 0) {
                increment (it1, it1_end, - compare);
            } else if (compare > 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename E::const_iterator2 it2e (it1e.begin ());
                typename E::const_iterator2 it2e_end (it1e.end ());
#else
                typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
                typename E::const_iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
                while (it2e != it2e_end) {
                    if (conformant_restrict_type::other (it2e.index1 (), it2e.index2 ()))
                        if (static_cast<value_type>(*it2e) != value_type/*zero*/())
                            index.push_back (std::pair<size_type, size_type> (it2e.index1 (), it2e.index2 ()));
                    ++ it2e;
                }
                ++ it1e;
            }
        }
        while (it1e != it1e_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename E::const_iterator2 it2e (it1e.begin ());
            typename E::const_iterator2 it2e_end (it1e.end ());
#else
            typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
            typename E::const_iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
            while (it2e != it2e_end) {
                if (conformant_restrict_type::other (it2e.index1 (), it2e.index2 ()))
                    if (static_cast<value_type>(*it2e) != value_type/*zero*/())
                        index.push_back (std::pair<size_type, size_type> (it2e.index1 (), it2e.index2 ()));
                ++ it2e;
            }
            ++ it1e;
        }
        // ISSUE proxies require insert_element
        for (size_type k = 0; k < index.size (); ++ k)
            m (index [k].first, index [k].second) = value_type/*zero*/();
    }
    template<class M, class E, class R>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void make_conformant (M &m, const matrix_expression<E> &e, column_major_tag, R) {
        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());
        typedef R conformant_restrict_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        std::vector<std::pair<size_type, size_type> > index;
        typename M::iterator2 it2 (m.begin2 ());
        typename M::iterator2 it2_end (m.end2 ());
        typename E::const_iterator2 it2e (e ().begin2 ());
        typename E::const_iterator2 it2e_end (e ().end2 ());
        while (it2 != it2_end && it2e != it2e_end) {
            difference_type compare = it2.index2 () - it2e.index2 ();
            if (compare == 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator1 it1 (it2.begin ());
                typename M::iterator1 it1_end (it2.end ());
                typename E::const_iterator1 it1e (it2e.begin ());
                typename E::const_iterator1 it1e_end (it2e.end ());
#else
                typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
                typename E::const_iterator1 it1e (begin (it2e, iterator2_tag ()));
                typename E::const_iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
                if (it1 != it1_end && it1e != it1e_end) {
                    size_type it1_index = it1.index1 (), it1e_index = it1e.index1 ();
                    for (;;) {
                        difference_type compare2 = it1_index - it1e_index;
                        if (compare2 == 0) {
                            ++ it1, ++ it1e;
                            if (it1 != it1_end && it1e != it1e_end) {
                                it1_index = it1.index1 ();
                                it1e_index = it1e.index1 ();
                            } else
                                break;
                        } else if (compare2 < 0) {
                            increment (it1, it1_end, - compare2);
                            if (it1 != it1_end)
                                it1_index = it1.index1 ();
                            else
                                break;
                        } else if (compare2 > 0) {
                            if (conformant_restrict_type::other (it1e.index1 (), it1e.index2 ()))
                                if (static_cast<value_type>(*it1e) != value_type/*zero*/())
                                    index.push_back (std::pair<size_type, size_type> (it1e.index1 (), it1e.index2 ()));
                            ++ it1e;
                            if (it1e != it1e_end)
                                it1e_index = it1e.index1 ();
                            else
                                break;
                        }
                    }
                }
                while (it1e != it1e_end) {
                    if (conformant_restrict_type::other (it1e.index1 (), it1e.index2 ()))
                        if (static_cast<value_type>(*it1e) != value_type/*zero*/())
                            index.push_back (std::pair<size_type, size_type> (it1e.index1 (), it1e.index2 ()));
                    ++ it1e;
                }
                ++ it2, ++ it2e;
            } else if (compare < 0) {
                increment (it2, it2_end, - compare);
            } else if (compare > 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename E::const_iterator1 it1e (it2e.begin ());
                typename E::const_iterator1 it1e_end (it2e.end ());
#else
                typename E::const_iterator1 it1e (begin (it2e, iterator2_tag ()));
                typename E::const_iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
                while (it1e != it1e_end) {
                    if (conformant_restrict_type::other (it1e.index1 (), it1e.index2 ()))
                        if (static_cast<value_type>(*it1e) != value_type/*zero*/())
                            index.push_back (std::pair<size_type, size_type> (it1e.index1 (), it1e.index2 ()));
                    ++ it1e;
                }
                ++ it2e;
            }
        }
        while (it2e != it2e_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename E::const_iterator1 it1e (it2e.begin ());
            typename E::const_iterator1 it1e_end (it2e.end ());
#else
            typename E::const_iterator1 it1e (begin (it2e, iterator2_tag ()));
            typename E::const_iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
            while (it1e != it1e_end) {
                if (conformant_restrict_type::other (it1e.index1 (), it1e.index2 ()))
                    if (static_cast<value_type>(*it1e) != value_type/*zero*/())
                        index.push_back (std::pair<size_type, size_type> (it1e.index1 (), it1e.index2 ()));
                ++ it1e;
            }
            ++ it2e;
        }
        // ISSUE proxies require insert_element
        for (size_type k = 0; k < index.size (); ++ k)
            m (index [k].first, index [k].second) = value_type/*zero*/();
    }

}//namespace detail


    // Explicitly iterating row major
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_matrix_assign_scalar (M &m, const T &t, row_major_tag) {
        typedef F<typename M::iterator2::reference, T> functor_type;
        typedef typename M::difference_type difference_type;
        difference_type size1 (m.size1 ());
        difference_type size2 (m.size2 ());
        typename M::iterator1 it1 (m.begin1 ());
        BOOST_UBLAS_CHECK (size2 == 0 || m.end1 () - it1 == size1, bad_size ());
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
#endif
            BOOST_UBLAS_CHECK (it1.end () - it2 == size2, bad_size ());
            difference_type temp_size2 (size2);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- temp_size2 >= 0)
                functor_type::apply (*it2, t), ++ it2;
#else
            DD (temp_size2, 4, r, (functor_type::apply (*it2, t), ++ it2));
#endif
            ++ it1;
        }
    }
    // Explicitly iterating column major
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_matrix_assign_scalar (M &m, const T &t, column_major_tag) {
        typedef F<typename M::iterator1::reference, T> functor_type;
        typedef typename M::difference_type difference_type;
        difference_type size2 (m.size2 ());
        difference_type size1 (m.size1 ());
        typename M::iterator2 it2 (m.begin2 ());
        BOOST_UBLAS_CHECK (size1 == 0 || m.end2 () - it2 == size2, bad_size ());
        while (-- size2 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
#endif
            BOOST_UBLAS_CHECK (it2.end () - it1 == size1, bad_size ());
            difference_type temp_size1 (size1);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- temp_size1 >= 0)
                functor_type::apply (*it1, t), ++ it1;
#else
            DD (temp_size1, 4, r, (functor_type::apply (*it1, t), ++ it1));
#endif
            ++ it2;
        }
    }
    // Explicitly indexing row major
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_matrix_assign_scalar (M &m, const T &t, row_major_tag) {
        typedef F<typename M::reference, T> functor_type;
        typedef typename M::size_type size_type;
        size_type size1 (m.size1 ());
        size_type size2 (m.size2 ());
        for (size_type i = 0; i < size1; ++ i) {
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type j = 0; j < size2; ++ j)
                functor_type::apply (m (i, j), t);
#else
            size_type j (0);
            DD (size2, 4, r, (functor_type::apply (m (i, j), t), ++ j));
#endif
        }
    }
    // Explicitly indexing column major
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_matrix_assign_scalar (M &m, const T &t, column_major_tag) {
        typedef F<typename M::reference, T> functor_type;
        typedef typename M::size_type size_type;
        size_type size2 (m.size2 ());
        size_type size1 (m.size1 ());
        for (size_type j = 0; j < size2; ++ j) {
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type i = 0; i < size1; ++ i)
                functor_type::apply (m (i, j), t);
#else
            size_type i (0);
            DD (size1, 4, r, (functor_type::apply (m (i, j), t), ++ i));
#endif
        }
    }

    // Dense (proxy) case
    template<template <class T1, class T2> class F, class M, class T, class C>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign_scalar (M &m, const T &t, dense_proxy_tag, C) {
        typedef C orientation_category;
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_matrix_assign_scalar<F> (m, t, orientation_category ());
#elif BOOST_UBLAS_USE_ITERATING
        iterating_matrix_assign_scalar<F> (m, t, orientation_category ());
#else
        typedef typename M::size_type size_type;
        size_type size1 (m.size1 ());
        size_type size2 (m.size2 ());
        if (size1 >= BOOST_UBLAS_ITERATOR_THRESHOLD &&
            size2 >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_matrix_assign_scalar<F> (m, t, orientation_category ());
        else
            indexing_matrix_assign_scalar<F> (m, t, orientation_category ());
#endif
    }
    // Packed (proxy) row major case
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign_scalar (M &m, const T &t, packed_proxy_tag, row_major_tag) {
        typedef F<typename M::iterator2::reference, T> functor_type;
        typedef typename M::difference_type difference_type;
        typename M::iterator1 it1 (m.begin1 ());
        difference_type size1 (m.end1 () - it1);
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            difference_type size2 (it1.end () - it2);
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            difference_type size2 (end (it1, iterator1_tag ()) - it2);
#endif
            while (-- size2 >= 0)
                functor_type::apply (*it2, t), ++ it2;
            ++ it1;
        }
    }
    // Packed (proxy) column major case
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign_scalar (M &m, const T &t, packed_proxy_tag, column_major_tag) {
        typedef F<typename M::iterator1::reference, T> functor_type;
        typedef typename M::difference_type difference_type;
        typename M::iterator2 it2 (m.begin2 ());
        difference_type size2 (m.end2 () - it2);
        while (-- size2 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
            difference_type size1 (it2.end () - it1);
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
            difference_type size1 (end (it2, iterator2_tag ()) - it1);
#endif
            while (-- size1 >= 0)
                functor_type::apply (*it1, t), ++ it1;
            ++ it2;
        }
    }
    // Sparse (proxy) row major case
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign_scalar (M &m, const T &t, sparse_proxy_tag, row_major_tag) {
        typedef F<typename M::iterator2::reference, T> functor_type;
        typename M::iterator1 it1 (m.begin1 ());
        typename M::iterator1 it1_end (m.end1 ());
        while (it1 != it1_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename M::iterator2 it2_end (it1.end ());
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
#endif
            while (it2 != it2_end)
                functor_type::apply (*it2, t), ++ it2;
            ++ it1;
        }
    }
    // Sparse (proxy) column major case
    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign_scalar (M &m, const T &t, sparse_proxy_tag, column_major_tag) {
        typedef F<typename M::iterator1::reference, T> functor_type;
        typename M::iterator2 it2 (m.begin2 ());
        typename M::iterator2 it2_end (m.end2 ());
        while (it2 != it2_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
            typename M::iterator1 it1_end (it2.end ());
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
            typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
#endif
            while (it1 != it1_end)
                functor_type::apply (*it1, t), ++ it1;
            ++ it2;
        }
    }

    // Dispatcher
    template<template <class T1, class T2> class F, class M, class T>
    BOOST_UBLAS_INLINE
    void matrix_assign_scalar (M &m, const T &t) {
        typedef typename M::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;
        matrix_assign_scalar<F> (m, t, storage_category (), orientation_category ());
    }

    template<class SC, bool COMPUTED, class RI1, class RI2>
    struct matrix_assign_traits {
        typedef SC storage_category;
    };

    template<bool COMPUTED>
    struct matrix_assign_traits<dense_tag, COMPUTED, packed_random_access_iterator_tag, packed_random_access_iterator_tag> {
        typedef packed_tag storage_category;
    };
    template<>
    struct matrix_assign_traits<dense_tag, false, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };
    template<>
    struct matrix_assign_traits<dense_tag, true, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<bool COMPUTED>
    struct matrix_assign_traits<dense_proxy_tag, COMPUTED, packed_random_access_iterator_tag, packed_random_access_iterator_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<bool COMPUTED>
    struct matrix_assign_traits<dense_proxy_tag, COMPUTED, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct matrix_assign_traits<packed_tag, false, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };
    template<>
    struct matrix_assign_traits<packed_tag, true, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<bool COMPUTED>
    struct matrix_assign_traits<packed_proxy_tag, COMPUTED, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct matrix_assign_traits<sparse_tag, true, dense_random_access_iterator_tag, dense_random_access_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct matrix_assign_traits<sparse_tag, true, packed_random_access_iterator_tag, packed_random_access_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct matrix_assign_traits<sparse_tag, true, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    // Explicitly iterating row major
    template<template <class T1, class T2> class F, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_matrix_assign (M &m, const matrix_expression<E> &e, row_major_tag) {
        typedef F<typename M::iterator2::reference, typename E::value_type> functor_type;
        typedef typename M::difference_type difference_type;
        difference_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        typename M::iterator1 it1 (m.begin1 ());
        BOOST_UBLAS_CHECK (size2 == 0 || m.end1 () - it1 == size1, bad_size ());
        typename E::const_iterator1 it1e (e ().begin1 ());
        BOOST_UBLAS_CHECK (size2 == 0 || e ().end1 () - it1e == size1, bad_size ());
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename E::const_iterator2 it2e (it1e.begin ());
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
#endif
            BOOST_UBLAS_CHECK (it1.end () - it2 == size2, bad_size ());
            BOOST_UBLAS_CHECK (it1e.end () - it2e == size2, bad_size ());
            difference_type temp_size2 (size2);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- temp_size2 >= 0)
                functor_type::apply (*it2, *it2e), ++ it2, ++ it2e;
#else
            DD (temp_size2, 2, r, (functor_type::apply (*it2, *it2e), ++ it2, ++ it2e));
#endif
            ++ it1, ++ it1e;
        }
    }
    // Explicitly iterating column major
    template<template <class T1, class T2> class F, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_matrix_assign (M &m, const matrix_expression<E> &e, column_major_tag) {
        typedef F<typename M::iterator1::reference, typename E::value_type> functor_type;
        typedef typename M::difference_type difference_type;
        difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        difference_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        typename M::iterator2 it2 (m.begin2 ());
        BOOST_UBLAS_CHECK (size1 == 0 || m.end2 () - it2 == size2, bad_size ());
        typename E::const_iterator2 it2e (e ().begin2 ());
        BOOST_UBLAS_CHECK (size1 == 0 || e ().end2 () - it2e == size2, bad_size ());
        while (-- size2 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
            typename E::const_iterator1 it1e (it2e.begin ());
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
            typename E::const_iterator1 it1e (begin (it2e, iterator2_tag ()));
#endif
            BOOST_UBLAS_CHECK (it2.end () - it1 == size1, bad_size ());
            BOOST_UBLAS_CHECK (it2e.end () - it1e == size1, bad_size ());
            difference_type temp_size1 (size1);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- temp_size1 >= 0)
                functor_type::apply (*it1, *it1e), ++ it1, ++ it1e;
#else
            DD (temp_size1, 2, r, (functor_type::apply (*it1, *it1e), ++ it1, ++ it1e));
#endif
            ++ it2, ++ it2e;
        }
    }
    // Explicitly indexing row major
    template<template <class T1, class T2> class F, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_matrix_assign (M &m, const matrix_expression<E> &e, row_major_tag) {
        typedef F<typename M::reference, typename E::value_type> functor_type;
        typedef typename M::size_type size_type;
        size_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        size_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        for (size_type i = 0; i < size1; ++ i) {
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type j = 0; j < size2; ++ j)
                functor_type::apply (m (i, j), e () (i, j));
#else
            size_type j (0);
            DD (size2, 2, r, (functor_type::apply (m (i, j), e () (i, j)), ++ j));
#endif
        }
    }
    // Explicitly indexing column major
    template<template <class T1, class T2> class F, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_matrix_assign (M &m, const matrix_expression<E> &e, column_major_tag) {
        typedef F<typename M::reference, typename E::value_type> functor_type;
        typedef typename M::size_type size_type;
        size_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        size_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        for (size_type j = 0; j < size2; ++ j) {
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type i = 0; i < size1; ++ i)
                functor_type::apply (m (i, j), e () (i, j));
#else
            size_type i (0);
            DD (size1, 2, r, (functor_type::apply (m (i, j), e () (i, j)), ++ i));
#endif
        }
    }

    // Dense (proxy) case
    template<template <class T1, class T2> class F, class R, class M, class E, class C>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, dense_proxy_tag, C) {
        // R unnecessary, make_conformant not required
        typedef C orientation_category;
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_matrix_assign<F> (m, e, orientation_category ());
#elif BOOST_UBLAS_USE_ITERATING
        iterating_matrix_assign<F> (m, e, orientation_category ());
#else
        typedef typename M::difference_type difference_type;
        size_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        size_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        if (size1 >= BOOST_UBLAS_ITERATOR_THRESHOLD &&
            size2 >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_matrix_assign<F> (m, e, orientation_category ());
        else
            indexing_matrix_assign<F> (m, e, orientation_category ());
#endif
    }
    // Packed (proxy) row major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, packed_proxy_tag, row_major_tag) {
        typedef typename matrix_traits<E>::value_type expr_value_type;
        typedef F<typename M::iterator2::reference, expr_value_type> functor_type;
        // R unnecessary, make_conformant not required
        typedef typename M::difference_type difference_type;

        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());

#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, row_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign<scalar_assign> (cm, m, row_major_tag ());
        indexing_matrix_assign<F> (cm, e, row_major_tag ());
#endif
        typename M::iterator1 it1 (m.begin1 ());
        typename M::iterator1 it1_end (m.end1 ());
        typename E::const_iterator1 it1e (e ().begin1 ());
        typename E::const_iterator1 it1e_end (e ().end1 ());
        difference_type it1_size (it1_end - it1);
        difference_type it1e_size (it1e_end - it1e);
        difference_type diff1 (0);
        if (it1_size > 0 && it1e_size > 0)
            diff1 = it1.index1 () - it1e.index1 ();
        if (diff1 != 0) {
            difference_type size1 = (std::min) (diff1, it1e_size);
            if (size1 > 0) {
                it1e += size1;
                it1e_size -= size1;
                diff1 -= size1;
            }
            size1 = (std::min) (- diff1, it1_size);
            if (size1 > 0) {
                it1_size -= size1;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                    while (-- size1 >= 0) { // zeroing
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                        typename M::iterator2 it2 (it1.begin ());
                        typename M::iterator2 it2_end (it1.end ());
#else
                        typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                        typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
#endif
                        difference_type size2 (it2_end - it2);
                        while (-- size2 >= 0)
                            functor_type::apply (*it2, expr_value_type/*zero*/()), ++ it2;
                        ++ it1;
                    }
                } else {
                    it1 += size1;
                }
                diff1 += size1;
            }
        }
        difference_type size1 ((std::min) (it1_size, it1e_size));
        it1_size -= size1;
        it1e_size -= size1;
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename M::iterator2 it2_end (it1.end ());
            typename E::const_iterator2 it2e (it1e.begin ());
            typename E::const_iterator2 it2e_end (it1e.end ());
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
            typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
            typename E::const_iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
            difference_type it2_size (it2_end - it2);
            difference_type it2e_size (it2e_end - it2e);
            difference_type diff2 (0);
            if (it2_size > 0 && it2e_size > 0) {
                diff2 = it2.index2 () - it2e.index2 ();
                difference_type size2 = (std::min) (diff2, it2e_size);
                if (size2 > 0) {
                    it2e += size2;
                    it2e_size -= size2;
                    diff2 -= size2;
                }
                size2 = (std::min) (- diff2, it2_size);
                if (size2 > 0) {
                    it2_size -= size2;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                    if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                        while (-- size2 >= 0)   // zeroing
                            functor_type::apply (*it2, expr_value_type/*zero*/()), ++ it2;
                    } else {
                        it2 += size2;
                    }
                    diff2 += size2;
                }
            }
            difference_type size2 ((std::min) (it2_size, it2e_size));
            it2_size -= size2;
            it2e_size -= size2;
            while (-- size2 >= 0)
                functor_type::apply (*it2, *it2e), ++ it2, ++ it2e;
            size2 = it2_size;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
            if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                while (-- size2 >= 0)   // zeroing
                    functor_type::apply (*it2, expr_value_type/*zero*/()), ++ it2;
            } else {
                it2 += size2;
            }
            ++ it1, ++ it1e;
        }
        size1 = it1_size;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
            while (-- size1 >= 0) { // zeroing
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator2 it2 (it1.begin ());
                typename M::iterator2 it2_end (it1.end ());
#else
                typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
#endif
                difference_type size2 (it2_end - it2);
                while (-- size2 >= 0)
                    functor_type::apply (*it2, expr_value_type/*zero*/()), ++ it2;
                ++ it1;
            }
        } else {
            it1 += size1;
        }
#if BOOST_UBLAS_TYPE_CHECK
        if (! disable_type_check<bool>::value)
            BOOST_UBLAS_CHECK (detail::expression_type_check (m, cm), external_logic ());
#endif
    }
    // Packed (proxy) column major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, packed_proxy_tag, column_major_tag) {
        typedef typename matrix_traits<E>::value_type expr_value_type;
        typedef F<typename M::iterator1::reference, expr_value_type> functor_type;
        // R unnecessary, make_conformant not required
        typedef typename M::difference_type difference_type;

        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());

#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, column_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign<scalar_assign> (cm, m, column_major_tag ());
        indexing_matrix_assign<F> (cm, e, column_major_tag ());
#endif
        typename M::iterator2 it2 (m.begin2 ());
        typename M::iterator2 it2_end (m.end2 ());
        typename E::const_iterator2 it2e (e ().begin2 ());
        typename E::const_iterator2 it2e_end (e ().end2 ());
        difference_type it2_size (it2_end - it2);
        difference_type it2e_size (it2e_end - it2e);
        difference_type diff2 (0);
        if (it2_size > 0 && it2e_size > 0)
            diff2 = it2.index2 () - it2e.index2 ();
        if (diff2 != 0) {
            difference_type size2 = (std::min) (diff2, it2e_size);
            if (size2 > 0) {
                it2e += size2;
                it2e_size -= size2;
                diff2 -= size2;
            }
            size2 = (std::min) (- diff2, it2_size);
            if (size2 > 0) {
                it2_size -= size2;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                    while (-- size2 >= 0) { // zeroing
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                        typename M::iterator1 it1 (it2.begin ());
                        typename M::iterator1 it1_end (it2.end ());
#else
                        typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                        typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
#endif
                        difference_type size1 (it1_end - it1);
                        while (-- size1 >= 0)
                            functor_type::apply (*it1, expr_value_type/*zero*/()), ++ it1;
                        ++ it2;
                    }
                } else {
                    it2 += size2;
                }
                diff2 += size2;
            }
        }
        difference_type size2 ((std::min) (it2_size, it2e_size));
        it2_size -= size2;
        it2e_size -= size2;
        while (-- size2 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
            typename M::iterator1 it1_end (it2.end ());
            typename E::const_iterator1 it1e (it2e.begin ());
            typename E::const_iterator1 it1e_end (it2e.end ());
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
            typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
            typename E::const_iterator1 it1e (begin (it2e, iterator2_tag ()));
            typename E::const_iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
            difference_type it1_size (it1_end - it1);
            difference_type it1e_size (it1e_end - it1e);
            difference_type diff1 (0);
            if (it1_size > 0 && it1e_size > 0) {
                diff1 = it1.index1 () - it1e.index1 ();
                difference_type size1 = (std::min) (diff1, it1e_size);
                if (size1 > 0) {
                    it1e += size1;
                    it1e_size -= size1;
                    diff1 -= size1;
                }
                size1 = (std::min) (- diff1, it1_size);
                if (size1 > 0) {
                    it1_size -= size1;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                    if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                        while (-- size1 >= 0)   // zeroing
                            functor_type::apply (*it1, expr_value_type/*zero*/()), ++ it1;
                    } else {
                        it1 += size1;
                    }
                    diff1 += size1;
                }
            }
            difference_type size1 ((std::min) (it1_size, it1e_size));
            it1_size -= size1;
            it1e_size -= size1;
            while (-- size1 >= 0)
                functor_type::apply (*it1, *it1e), ++ it1, ++ it1e;
            size1 = it1_size;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
            if (!functor_type::computed) {

#ifdef _MSC_VER
#pragma warning(pop)
#endif
                while (-- size1 >= 0)   // zeroing
                    functor_type::apply (*it1, expr_value_type/*zero*/()), ++ it1;
            } else {
                it1 += size1;
            }
            ++ it2, ++ it2e;
        }
        size2 = it2_size;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
            while (-- size2 >= 0) { // zeroing
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator1 it1 (it2.begin ());
                typename M::iterator1 it1_end (it2.end ());
#else
                typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
#endif
                difference_type size1 (it1_end - it1);
                while (-- size1 >= 0)
                    functor_type::apply (*it1, expr_value_type/*zero*/()), ++ it1;
                ++ it2;
            }
        } else {
            it2 += size2;
        }
#if BOOST_UBLAS_TYPE_CHECK
        if (! disable_type_check<bool>::value)
            BOOST_UBLAS_CHECK (detail::expression_type_check (m, cm), external_logic ());
#endif
    }
    // Sparse row major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, sparse_tag, row_major_tag) {
        typedef F<typename M::iterator2::reference, typename E::value_type> functor_type;
        // R unnecessary, make_conformant not required

//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        BOOST_STATIC_ASSERT ((!functor_type::computed));
#ifdef _MSC_VER
#pragma warning(pop)
#endif
        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());
        typedef typename M::value_type value_type;
        // Sparse type has no numeric constraints to check

        m.clear ();
        typename E::const_iterator1 it1e (e ().begin1 ());
        typename E::const_iterator1 it1e_end (e ().end1 ());
        while (it1e != it1e_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename E::const_iterator2 it2e (it1e.begin ());
            typename E::const_iterator2 it2e_end (it1e.end ());
#else
            typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
            typename E::const_iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
            while (it2e != it2e_end) {
                value_type t (*it2e);
                if (t != value_type/*zero*/())
                    m.insert_element (it2e.index1 (), it2e.index2 (), t);
                ++ it2e;
            }
            ++ it1e;
        }
    }
    // Sparse column major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, sparse_tag, column_major_tag) {
        typedef F<typename M::iterator1::reference, typename E::value_type> functor_type;
        // R unnecessary, make_conformant not required

//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        BOOST_STATIC_ASSERT ((!functor_type::computed));
#ifdef _MSC_VER
#pragma warning(pop)
#endif
        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());
        typedef typename M::value_type value_type;
        // Sparse type has no numeric constraints to check

        m.clear ();
        typename E::const_iterator2 it2e (e ().begin2 ());
        typename E::const_iterator2 it2e_end (e ().end2 ());
        while (it2e != it2e_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename E::const_iterator1 it1e (it2e.begin ());
            typename E::const_iterator1 it1e_end (it2e.end ());
#else
            typename E::const_iterator1 it1e (begin (it2e, iterator2_tag ()));
            typename E::const_iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
            while (it1e != it1e_end) {
                value_type t (*it1e);
                if (t != value_type/*zero*/())
                    m.insert_element (it1e.index1 (), it1e.index2 (), t);
                ++ it1e;
            }
            ++ it2e;
        }
    }
    // Sparse proxy or functional row major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, sparse_proxy_tag, row_major_tag) {
        typedef typename matrix_traits<E>::value_type expr_value_type;
        typedef F<typename M::iterator2::reference, expr_value_type> functor_type;
        typedef R conformant_restrict_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;

        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());

#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, row_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign<scalar_assign> (cm, m, row_major_tag ());
        indexing_matrix_assign<F> (cm, e, row_major_tag ());
#endif
        detail::make_conformant (m, e, row_major_tag (), conformant_restrict_type ());

        typename M::iterator1 it1 (m.begin1 ());
        typename M::iterator1 it1_end (m.end1 ());
        typename E::const_iterator1 it1e (e ().begin1 ());
        typename E::const_iterator1 it1e_end (e ().end1 ());
        while (it1 != it1_end && it1e != it1e_end) {
            difference_type compare = it1.index1 () - it1e.index1 ();
            if (compare == 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator2 it2 (it1.begin ());
                typename M::iterator2 it2_end (it1.end ());
                typename E::const_iterator2 it2e (it1e.begin ());
                typename E::const_iterator2 it2e_end (it1e.end ());
#else
                typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
                typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
                typename E::const_iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
                if (it2 != it2_end && it2e != it2e_end) {
                    size_type it2_index = it2.index2 (), it2e_index = it2e.index2 ();
                    for (;;) {
                        difference_type compare2 = it2_index - it2e_index;
                        if (compare2 == 0) {
                            functor_type::apply (*it2, *it2e);
                            ++ it2, ++ it2e;
                            if (it2 != it2_end && it2e != it2e_end) {
                                it2_index = it2.index2 ();
                                it2e_index = it2e.index2 ();
                            } else
                                break;
                        } else if (compare2 < 0) {
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                            if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                                functor_type::apply (*it2, expr_value_type/*zero*/());
                                ++ it2;
                            } else
                                increment (it2, it2_end, - compare2);
                            if (it2 != it2_end)
                                it2_index = it2.index2 ();
                            else
                                break;
                        } else if (compare2 > 0) {
                            increment (it2e, it2e_end, compare2);
                            if (it2e != it2e_end)
                                it2e_index = it2e.index2 ();
                            else
                                break;
                        }
                    }
                }
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                    while (it2 != it2_end) {    // zeroing
                        functor_type::apply (*it2, expr_value_type/*zero*/());
                        ++ it2;
                    }
                } else {
                    it2 = it2_end;
                }
                ++ it1, ++ it1e;
            } else if (compare < 0) {
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                    typename M::iterator2 it2 (it1.begin ());
                    typename M::iterator2 it2_end (it1.end ());
#else
                    typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                    typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
#endif
                    while (it2 != it2_end) {    // zeroing
                        functor_type::apply (*it2, expr_value_type/*zero*/());
                        ++ it2;
                    }
                    ++ it1;
                } else {
                    increment (it1, it1_end, - compare);
                }
            } else if (compare > 0) {
                increment (it1e, it1e_end, compare);
            }
        }
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
            while (it1 != it1_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator2 it2 (it1.begin ());
                typename M::iterator2 it2_end (it1.end ());
#else
                typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
#endif
                while (it2 != it2_end) {    // zeroing
                    functor_type::apply (*it2, expr_value_type/*zero*/());
                    ++ it2;
                }
                ++ it1;
            }
        } else {
            it1 = it1_end;
        }
#if BOOST_UBLAS_TYPE_CHECK
        if (! disable_type_check<bool>::value)
            BOOST_UBLAS_CHECK (detail::expression_type_check (m, cm), external_logic ());
#endif
    }
    // Sparse proxy or functional column major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, sparse_proxy_tag, column_major_tag) {
        typedef typename matrix_traits<E>::value_type expr_value_type;
        typedef F<typename M::iterator1::reference, expr_value_type> functor_type;
        typedef R conformant_restrict_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;

        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());

#if BOOST_UBLAS_TYPE_CHECK
        typedef typename M::value_type value_type;
        matrix<value_type, column_major> cm (m.size1 (), m.size2 ());
        indexing_matrix_assign<scalar_assign> (cm, m, column_major_tag ());
        indexing_matrix_assign<F> (cm, e, column_major_tag ());
#endif
        detail::make_conformant (m, e, column_major_tag (), conformant_restrict_type ());

        typename M::iterator2 it2 (m.begin2 ());
        typename M::iterator2 it2_end (m.end2 ());
        typename E::const_iterator2 it2e (e ().begin2 ());
        typename E::const_iterator2 it2e_end (e ().end2 ());
        while (it2 != it2_end && it2e != it2e_end) {
            difference_type compare = it2.index2 () - it2e.index2 ();
            if (compare == 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator1 it1 (it2.begin ());
                typename M::iterator1 it1_end (it2.end ());
                typename E::const_iterator1 it1e (it2e.begin ());
                typename E::const_iterator1 it1e_end (it2e.end ());
#else
                typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
                typename E::const_iterator1 it1e (begin (it2e, iterator2_tag ()));
                typename E::const_iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
                if (it1 != it1_end && it1e != it1e_end) {
                    size_type it1_index = it1.index1 (), it1e_index = it1e.index1 ();
                    for (;;) {
                        difference_type compare2 = it1_index - it1e_index;
                        if (compare2 == 0) {
                            functor_type::apply (*it1, *it1e);
                            ++ it1, ++ it1e;
                            if (it1 != it1_end && it1e != it1e_end) {
                                it1_index = it1.index1 ();
                                it1e_index = it1e.index1 ();
                            } else
                                break;
                        } else if (compare2 < 0) {
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                            if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                                functor_type::apply (*it1, expr_value_type/*zero*/()); // zeroing
                                ++ it1;
                            } else
                                increment (it1, it1_end, - compare2);
                            if (it1 != it1_end)
                                it1_index = it1.index1 ();
                            else
                                break;
                        } else if (compare2 > 0) {
                            increment (it1e, it1e_end, compare2);
                            if (it1e != it1e_end)
                                it1e_index = it1e.index1 ();
                            else
                                break;
                        }
                    }
                }
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                    while (it1 != it1_end) {    // zeroing
                        functor_type::apply (*it1, expr_value_type/*zero*/());
                        ++ it1;
                    }
                } else {
                    it1 = it1_end;
                }
                ++ it2, ++ it2e;
            } else if (compare < 0) {
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                    typename M::iterator1 it1 (it2.begin ());
                    typename M::iterator1 it1_end (it2.end ());
#else
                    typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                    typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
#endif
                    while (it1 != it1_end) {    // zeroing
                        functor_type::apply (*it1, expr_value_type/*zero*/());
                        ++ it1;
                    }
                    ++ it2;
                } else {
                    increment (it2, it2_end, - compare);
                }
            } else if (compare > 0) {
                increment (it2e, it2e_end, compare);
            }
        }
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
            while (it2 != it2_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator1 it1 (it2.begin ());
                typename M::iterator1 it1_end (it2.end ());
#else
                typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
#endif
                while (it1 != it1_end) {    // zeroing
                    functor_type::apply (*it1, expr_value_type/*zero*/());
                    ++ it1;
                }
                ++ it2;
            }
        } else {
            it2 = it2_end;
        }
#if BOOST_UBLAS_TYPE_CHECK
        if (! disable_type_check<bool>::value)
            BOOST_UBLAS_CHECK (detail::expression_type_check (m, cm), external_logic ());
#endif
    }

    // Dispatcher
    template<template <class T1, class T2> class F, class M, class E>
    BOOST_UBLAS_INLINE
    void matrix_assign (M &m, const matrix_expression<E> &e) {
        typedef typename matrix_assign_traits<typename M::storage_category,
                                              F<typename M::reference, typename E::value_type>::computed,
                                              typename E::const_iterator1::iterator_category,
                                              typename E::const_iterator2::iterator_category>::storage_category storage_category;
        // give preference to matrix M's orientation if known
        typedef typename boost::mpl::if_<boost::is_same<typename M::orientation_category, unknown_orientation_tag>,
                                          typename E::orientation_category ,
                                          typename M::orientation_category >::type orientation_category;
        typedef basic_full<typename M::size_type> unrestricted;
        matrix_assign<F, unrestricted> (m, e, storage_category (), orientation_category ());
    }
    template<template <class T1, class T2> class F, class R, class M, class E>
    BOOST_UBLAS_INLINE
    void matrix_assign (M &m, const matrix_expression<E> &e) {
        typedef R conformant_restrict_type;
        typedef typename matrix_assign_traits<typename M::storage_category,
                                              F<typename M::reference, typename E::value_type>::computed,
                                              typename E::const_iterator1::iterator_category,
                                              typename E::const_iterator2::iterator_category>::storage_category storage_category;
        // give preference to matrix M's orientation if known
        typedef typename boost::mpl::if_<boost::is_same<typename M::orientation_category, unknown_orientation_tag>,
                                          typename E::orientation_category ,
                                          typename M::orientation_category >::type orientation_category;
        matrix_assign<F, conformant_restrict_type> (m, e, storage_category (), orientation_category ());
    }

    template<class SC, class RI1, class RI2>
    struct matrix_swap_traits {
        typedef SC storage_category;
    };

    template<>
    struct matrix_swap_traits<dense_proxy_tag, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct matrix_swap_traits<packed_proxy_tag, sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    // Dense (proxy) row major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_swap (M &m, matrix_expression<E> &e, dense_proxy_tag, row_major_tag) {
        typedef F<typename M::iterator2::reference, typename E::reference> functor_type;
        // R unnecessary, make_conformant not required
        //typedef typename M::size_type size_type; // gcc is complaining that this is not used, although this is not right
        typedef typename M::difference_type difference_type;
        typename M::iterator1 it1 (m.begin1 ());
        typename E::iterator1 it1e (e ().begin1 ());
        difference_type size1 (BOOST_UBLAS_SAME (m.size1 (), typename M::size_type (e ().end1 () - it1e)));
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename E::iterator2 it2e (it1e.begin ());
            difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), typename M::size_type (it1e.end () - it2e)));
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename E::iterator2 it2e (begin (it1e, iterator1_tag ()));
            difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), typename M::size_type (end (it1e, iterator1_tag ()) - it2e)));
#endif
            while (-- size2 >= 0)
                functor_type::apply (*it2, *it2e), ++ it2, ++ it2e;
            ++ it1, ++ it1e;
        }
    }
    // Dense (proxy) column major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_swap (M &m, matrix_expression<E> &e, dense_proxy_tag, column_major_tag) {
        typedef F<typename M::iterator1::reference, typename E::reference> functor_type;
        // R unnecessary, make_conformant not required
        // typedef typename M::size_type size_type; // gcc is complaining that this is not used, although this is not right
        typedef typename M::difference_type difference_type;
        typename M::iterator2 it2 (m.begin2 ());
        typename E::iterator2 it2e (e ().begin2 ());
        difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), typename M::size_type (e ().end2 () - it2e)));
        while (-- size2 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
            typename E::iterator1 it1e (it2e.begin ());
            difference_type size1 (BOOST_UBLAS_SAME (m.size1 (), typename M::size_type (it2e.end () - it1e)));
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
            typename E::iterator1 it1e (begin (it2e, iterator2_tag ()));
            difference_type size1 (BOOST_UBLAS_SAME (m.size1 (), typename M::size_type (end (it2e, iterator2_tag ()) - it1e)));
#endif
            while (-- size1 >= 0)
                functor_type::apply (*it1, *it1e), ++ it1, ++ it1e;
            ++ it2, ++ it2e;
        }
    }
    // Packed (proxy) row major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_swap (M &m, matrix_expression<E> &e, packed_proxy_tag, row_major_tag) {
        typedef F<typename M::iterator2::reference, typename E::reference> functor_type;
        // R unnecessary, make_conformant not required
        typedef typename M::difference_type difference_type;
        typename M::iterator1 it1 (m.begin1 ());
        typename E::iterator1 it1e (e ().begin1 ());
        difference_type size1 (BOOST_UBLAS_SAME (m.end1 () - it1, e ().end1 () - it1e));
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename E::iterator2 it2e (it1e.begin ());
            difference_type size2 (BOOST_UBLAS_SAME (it1.end () - it2, it1e.end () - it2e));
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename E::iterator2 it2e (begin (it1e, iterator1_tag ()));
            difference_type size2 (BOOST_UBLAS_SAME (end (it1, iterator1_tag ()) - it2, end (it1e, iterator1_tag ()) - it2e));
#endif
            while (-- size2 >= 0)
                functor_type::apply (*it2, *it2e), ++ it2, ++ it2e;
            ++ it1, ++ it1e;
        }
    }
    // Packed (proxy) column major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_swap (M &m, matrix_expression<E> &e, packed_proxy_tag, column_major_tag) {
        typedef F<typename M::iterator1::reference, typename E::reference> functor_type;
        // R unnecessary, make_conformant not required
        typedef typename M::difference_type difference_type;
        typename M::iterator2 it2 (m.begin2 ());
        typename E::iterator2 it2e (e ().begin2 ());
        difference_type size2 (BOOST_UBLAS_SAME (m.end2 () - it2, e ().end2 () - it2e));
        while (-- size2 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
            typename E::iterator1 it1e (it2e.begin ());
            difference_type size1 (BOOST_UBLAS_SAME (it2.end () - it1, it2e.end () - it1e));
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
            typename E::iterator1 it1e (begin (it2e, iterator2_tag ()));
            difference_type size1 (BOOST_UBLAS_SAME (end (it2, iterator2_tag ()) - it1, end (it2e, iterator2_tag ()) - it1e));
#endif
            while (-- size1 >= 0)
                functor_type::apply (*it1, *it1e), ++ it1, ++ it1e;
            ++ it2, ++ it2e;
        }
    }
    // Sparse (proxy) row major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_swap (M &m, matrix_expression<E> &e, sparse_proxy_tag, row_major_tag) {
        typedef F<typename M::iterator2::reference, typename E::reference> functor_type;
        typedef R conformant_restrict_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());

        detail::make_conformant (m, e, row_major_tag (), conformant_restrict_type ());
        // FIXME should be a seperate restriction for E
        detail::make_conformant (e (), m, row_major_tag (), conformant_restrict_type ());

        typename M::iterator1 it1 (m.begin1 ());
        typename M::iterator1 it1_end (m.end1 ());
        typename E::iterator1 it1e (e ().begin1 ());
        typename E::iterator1 it1e_end (e ().end1 ());
        while (it1 != it1_end && it1e != it1e_end) {
            difference_type compare = it1.index1 () - it1e.index1 ();
            if (compare == 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator2 it2 (it1.begin ());
                typename M::iterator2 it2_end (it1.end ());
                typename E::iterator2 it2e (it1e.begin ());
                typename E::iterator2 it2e_end (it1e.end ());
#else
                typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
                typename E::iterator2 it2e (begin (it1e, iterator1_tag ()));
                typename E::iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
                if (it2 != it2_end && it2e != it2e_end) {
                    size_type it2_index = it2.index2 (), it2e_index = it2e.index2 ();
                    for (;;) {
                        difference_type compare2 = it2_index - it2e_index;
                        if (compare2 == 0) {
                            functor_type::apply (*it2, *it2e);
                            ++ it2, ++ it2e;
                            if (it2 != it2_end && it2e != it2e_end) {
                                it2_index = it2.index2 ();
                                it2e_index = it2e.index2 ();
                            } else
                                break;
                        } else if (compare2 < 0) {
                            increment (it2, it2_end, - compare2);
                            if (it2 != it2_end)
                                it2_index = it2.index2 ();
                            else
                                break;
                        } else if (compare2 > 0) {
                            increment (it2e, it2e_end, compare2);
                            if (it2e != it2e_end)
                                it2e_index = it2e.index2 ();
                            else
                                break;
                        }
                    }
                }
#if BOOST_UBLAS_TYPE_CHECK
                increment (it2e, it2e_end);
                increment (it2, it2_end);
#endif
                ++ it1, ++ it1e;
            } else if (compare < 0) {
#if BOOST_UBLAS_TYPE_CHECK
                while (it1.index1 () < it1e.index1 ()) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                    typename M::iterator2 it2 (it1.begin ());
                    typename M::iterator2 it2_end (it1.end ());
#else
                    typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
                    typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
#endif
                    increment (it2, it2_end);
                    ++ it1;
                }
#else
                increment (it1, it1_end, - compare);
#endif
            } else if (compare > 0) {
#if BOOST_UBLAS_TYPE_CHECK
                while (it1e.index1 () < it1.index1 ()) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                    typename E::iterator2 it2e (it1e.begin ());
                    typename E::iterator2 it2e_end (it1e.end ());
#else
                    typename E::iterator2 it2e (begin (it1e, iterator1_tag ()));
                    typename E::iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
                    increment (it2e, it2e_end);
                    ++ it1e;
                }
#else
                increment (it1e, it1e_end, compare);
#endif
            }
        }
#if BOOST_UBLAS_TYPE_CHECK
        while (it1e != it1e_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename E::iterator2 it2e (it1e.begin ());
            typename E::iterator2 it2e_end (it1e.end ());
#else
            typename E::iterator2 it2e (begin (it1e, iterator1_tag ()));
            typename E::iterator2 it2e_end (end (it1e, iterator1_tag ()));
#endif
            increment (it2e, it2e_end);
            ++ it1e;
        }
        while (it1 != it1_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename M::iterator2 it2_end (it1.end ());
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename M::iterator2 it2_end (end (it1, iterator1_tag ()));
#endif
            increment (it2, it2_end);
            ++ it1;
        }
#endif
    }
    // Sparse (proxy) column major case
    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_swap (M &m, matrix_expression<E> &e, sparse_proxy_tag, column_major_tag) {
        typedef F<typename M::iterator1::reference, typename E::reference> functor_type;
        typedef R conformant_restrict_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;

        BOOST_UBLAS_CHECK (m.size1 () == e ().size1 (), bad_size ());
        BOOST_UBLAS_CHECK (m.size2 () == e ().size2 (), bad_size ());

        detail::make_conformant (m, e, column_major_tag (), conformant_restrict_type ());
        // FIXME should be a seperate restriction for E
        detail::make_conformant (e (), m, column_major_tag (), conformant_restrict_type ());

        typename M::iterator2 it2 (m.begin2 ());
        typename M::iterator2 it2_end (m.end2 ());
        typename E::iterator2 it2e (e ().begin2 ());
        typename E::iterator2 it2e_end (e ().end2 ());
        while (it2 != it2_end && it2e != it2e_end) {
            difference_type compare = it2.index2 () - it2e.index2 ();
            if (compare == 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                typename M::iterator1 it1 (it2.begin ());
                typename M::iterator1 it1_end (it2.end ());
                typename E::iterator1 it1e (it2e.begin ());
                typename E::iterator1 it1e_end (it2e.end ());
#else
                typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
                typename E::iterator1 it1e (begin (it2e, iterator2_tag ()));
                typename E::iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
                if (it1 != it1_end && it1e != it1e_end) {
                    size_type it1_index = it1.index1 (), it1e_index = it1e.index1 ();
                    for (;;) {
                        difference_type compare2 = it1_index - it1e_index;
                        if (compare2 == 0) {
                            functor_type::apply (*it1, *it1e);
                            ++ it1, ++ it1e;
                            if (it1 != it1_end && it1e != it1e_end) {
                                it1_index = it1.index1 ();
                                it1e_index = it1e.index1 ();
                            } else
                                break;
                        }  else if (compare2 < 0) {
                            increment (it1, it1_end, - compare2);
                            if (it1 != it1_end)
                                it1_index = it1.index1 ();
                            else
                                break;
                        } else if (compare2 > 0) {
                            increment (it1e, it1e_end, compare2);
                            if (it1e != it1e_end)
                                it1e_index = it1e.index1 ();
                            else
                                break;
                        }
                    }
                }
#if BOOST_UBLAS_TYPE_CHECK
                increment (it1e, it1e_end);
                increment (it1, it1_end);
#endif
                ++ it2, ++ it2e;
            } else if (compare < 0) {
#if BOOST_UBLAS_TYPE_CHECK
                while (it2.index2 () < it2e.index2 ()) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                    typename M::iterator1 it1 (it2.begin ());
                    typename M::iterator1 it1_end (it2.end ());
#else
                    typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
                    typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
#endif
                    increment (it1, it1_end);
                    ++ it2;
                }
#else
                increment (it2, it2_end, - compare);
#endif
            } else if (compare > 0) {
#if BOOST_UBLAS_TYPE_CHECK
                while (it2e.index2 () < it2.index2 ()) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
                    typename E::iterator1 it1e (it2e.begin ());
                    typename E::iterator1 it1e_end (it2e.end ());
#else
                    typename E::iterator1 it1e (begin (it2e, iterator2_tag ()));
                    typename E::iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
                    increment (it1e, it1e_end);
                    ++ it2e;
                }
#else
                increment (it2e, it2e_end, compare);
#endif
            }
        }
#if BOOST_UBLAS_TYPE_CHECK
        while (it2e != it2e_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename E::iterator1 it1e (it2e.begin ());
            typename E::iterator1 it1e_end (it2e.end ());
#else
            typename E::iterator1 it1e (begin (it2e, iterator2_tag ()));
            typename E::iterator1 it1e_end (end (it2e, iterator2_tag ()));
#endif
            increment (it1e, it1e_end);
            ++ it2e;
        }
        while (it2 != it2_end) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator1 it1 (it2.begin ());
            typename M::iterator1 it1_end (it2.end ());
#else
            typename M::iterator1 it1 (begin (it2, iterator2_tag ()));
            typename M::iterator1 it1_end (end (it2, iterator2_tag ()));
#endif
            increment (it1, it1_end);
            ++ it2;
        }
#endif
    }

    // Dispatcher
    template<template <class T1, class T2> class F, class M, class E>
    BOOST_UBLAS_INLINE
    void matrix_swap (M &m, matrix_expression<E> &e) {
        typedef typename matrix_swap_traits<typename M::storage_category,
                                            typename E::const_iterator1::iterator_category,
                                            typename E::const_iterator2::iterator_category>::storage_category storage_category;
        // give preference to matrix M's orientation if known
        typedef typename boost::mpl::if_<boost::is_same<typename M::orientation_category, unknown_orientation_tag>,
                                          typename E::orientation_category ,
                                          typename M::orientation_category >::type orientation_category;
        typedef basic_full<typename M::size_type> unrestricted;
        matrix_swap<F, unrestricted> (m, e, storage_category (), orientation_category ());
    }
    template<template <class T1, class T2> class F, class R, class M, class E>
    BOOST_UBLAS_INLINE
    void matrix_swap (M &m, matrix_expression<E> &e) {
        typedef R conformant_restrict_type;
        typedef typename matrix_swap_traits<typename M::storage_category,
                                            typename E::const_iterator1::iterator_category,
                                            typename E::const_iterator2::iterator_category>::storage_category storage_category;
        // give preference to matrix M's orientation if known
        typedef typename boost::mpl::if_<boost::is_same<typename M::orientation_category, unknown_orientation_tag>,
                                          typename E::orientation_category ,
                                          typename M::orientation_category >::type orientation_category;
        matrix_swap<F, conformant_restrict_type> (m, e, storage_category (), orientation_category ());
    }

}}}

#endif

/* matrix_assign.hpp
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
*/
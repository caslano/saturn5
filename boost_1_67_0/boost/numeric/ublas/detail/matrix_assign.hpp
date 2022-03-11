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
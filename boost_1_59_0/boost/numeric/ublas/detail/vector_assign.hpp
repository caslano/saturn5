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

#ifndef _BOOST_UBLAS_VECTOR_ASSIGN_
#define _BOOST_UBLAS_VECTOR_ASSIGN_

#include <boost/numeric/ublas/functional.hpp> // scalar_assign
// Required for make_conformant storage
#include <vector>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {
namespace detail {

    // Weak equality check - useful to compare equality two arbitary vector expression results.
    // Since the actual expressions are unknown, we check for and arbitary error bound
    // on the relative error.
    // For a linear expression the infinity norm makes sense as we do not know how the elements will be
    // combined in the expression. False positive results are inevitable for arbirary expressions!
    template<class E1, class E2, class S>
    BOOST_UBLAS_INLINE
    bool equals (const vector_expression<E1> &e1, const vector_expression<E2> &e2, S epsilon, S min_norm) {
        return norm_inf (e1 - e2) <= epsilon *
               std::max<S> (std::max<S> (norm_inf (e1), norm_inf (e2)), min_norm);
    }

    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    bool expression_type_check (const vector_expression<E1> &e1, const vector_expression<E2> &e2) {
        typedef typename type_traits<typename promote_traits<typename E1::value_type,
                                     typename E2::value_type>::promote_type>::real_type real_type;
        return equals (e1, e2, BOOST_UBLAS_TYPE_CHECK_EPSILON, BOOST_UBLAS_TYPE_CHECK_MIN);
    }


    // Make sparse proxies conformant
    template<class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void make_conformant (V &v, const vector_expression<E> &e) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
        // FIXME unbounded_array with push_back maybe better
        std::vector<size_type> index;
        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        typename E::const_iterator ite (e ().begin ());
        typename E::const_iterator ite_end (e ().end ());
        if (it != it_end && ite != ite_end) {
            size_type it_index = it.index (), ite_index = ite.index ();
            for (;;) {
                difference_type compare = it_index - ite_index;
                if (compare == 0) {
                    ++ it, ++ ite;
                    if (it != it_end && ite != ite_end) {
                        it_index = it.index ();
                        ite_index = ite.index ();
                    } else
                        break;
                } else if (compare < 0) {
                    increment (it, it_end, - compare);
                    if (it != it_end)
                        it_index = it.index ();
                    else
                        break;
                } else if (compare > 0) {
                    if (*ite != value_type/*zero*/())
                        index.push_back (ite.index ());
                    ++ ite;
                    if (ite != ite_end)
                        ite_index = ite.index ();
                    else
                        break;
                }
            }
        }

        while (ite != ite_end) {
            if (*ite != value_type/*zero*/())
                index.push_back (ite.index ());
            ++ ite;
        }
        for (size_type k = 0; k < index.size (); ++ k)
            v (index [k]) = value_type/*zero*/();
    }

}//namespace detail


    // Explicitly iterating
    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_vector_assign_scalar (V &v, const T &t) {
        typedef F<typename V::iterator::reference, T> functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (v.size ());
        typename V::iterator it (v.begin ());
        BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        while (-- size >= 0)
            functor_type::apply (*it, t), ++ it;
#else
        DD (size, 4, r, (functor_type::apply (*it, t), ++ it));
#endif
    }
    // Explicitly case
    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_vector_assign_scalar (V &v, const T &t) {
        typedef F<typename V::reference, T> functor_type;
        typedef typename V::size_type size_type;
        size_type size (v.size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        for (size_type i = 0; i < size; ++ i)
            functor_type::apply (v (i), t);
#else
        size_type i (0);
        DD (size, 4, r, (functor_type::apply (v (i), t), ++ i));
#endif
    }

    // Dense (proxy) case
    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign_scalar (V &v, const T &t, dense_proxy_tag) {
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_vector_assign_scalar<F> (v, t);
#elif BOOST_UBLAS_USE_ITERATING
        iterating_vector_assign_scalar<F> (v, t);
#else
        typedef typename V::size_type size_type;
        size_type size (v.size ());
        if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_vector_assign_scalar<F> (v, t);
        else
            indexing_vector_assign_scalar<F> (v, t);
#endif
    }
    // Packed (proxy) case
    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign_scalar (V &v, const T &t, packed_proxy_tag) {
        typedef F<typename V::iterator::reference, T> functor_type;
        typedef typename V::difference_type difference_type;
        typename V::iterator it (v.begin ());
        difference_type size (v.end () - it);
        while (-- size >= 0)
            functor_type::apply (*it, t), ++ it;
    }
    // Sparse (proxy) case
    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign_scalar (V &v, const T &t, sparse_proxy_tag) {
        typedef F<typename V::iterator::reference, T> functor_type;
        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        while (it != it_end)
            functor_type::apply (*it, t), ++ it;
    }

    // Dispatcher
    template<template <class T1, class T2> class F, class V, class T>
    BOOST_UBLAS_INLINE
    void vector_assign_scalar (V &v, const T &t) {
        typedef typename V::storage_category storage_category;
        vector_assign_scalar<F> (v, t, storage_category ());
    }

    template<class SC, bool COMPUTED, class RI>
    struct vector_assign_traits {
        typedef SC storage_category;
    };

    template<bool COMPUTED>
    struct vector_assign_traits<dense_tag, COMPUTED, packed_random_access_iterator_tag> {
        typedef packed_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_tag, false, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_tag, true, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<bool COMPUTED>
    struct vector_assign_traits<dense_proxy_tag, COMPUTED, packed_random_access_iterator_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_proxy_tag, false, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_proxy_tag, true, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct vector_assign_traits<packed_tag, false, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };
    template<>
    struct vector_assign_traits<packed_tag, true, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<bool COMPUTED>
    struct vector_assign_traits<packed_proxy_tag, COMPUTED, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct vector_assign_traits<sparse_tag, true, dense_random_access_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<sparse_tag, true, packed_random_access_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<sparse_tag, true, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    // Explicitly iterating
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_vector_assign (V &v, const vector_expression<E> &e) {
        typedef F<typename V::iterator::reference, typename E::value_type> functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        typename V::iterator it (v.begin ());
        BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
        typename E::const_iterator ite (e ().begin ());
        BOOST_UBLAS_CHECK (e ().end () - ite == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        while (-- size >= 0)
            functor_type::apply (*it, *ite), ++ it, ++ ite;
#else
        DD (size, 2, r, (functor_type::apply (*it, *ite), ++ it, ++ ite));
#endif
    }
    // Explicitly indexing
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_vector_assign (V &v, const vector_expression<E> &e) {
        typedef F<typename V::reference, typename E::value_type> functor_type;
        typedef typename V::size_type size_type;
        size_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        for (size_type i = 0; i < size; ++ i)
            functor_type::apply (v (i), e () (i));
#else
        size_type i (0);
        DD (size, 2, r, (functor_type::apply (v (i), e () (i)), ++ i));
#endif
    }

    // Dense (proxy) case
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign (V &v, const vector_expression<E> &e, dense_proxy_tag) {
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_vector_assign<F> (v, e);
#elif BOOST_UBLAS_USE_ITERATING
        iterating_vector_assign<F> (v, e);
#else
        typedef typename V::size_type size_type;
        size_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_vector_assign<F> (v, e);
        else
            indexing_vector_assign<F> (v, e);
#endif
    }
    // Packed (proxy) case
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign (V &v, const vector_expression<E> &e, packed_proxy_tag) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        typedef F<typename V::iterator::reference, typename E::value_type> functor_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        indexing_vector_assign<scalar_assign> (cv, v);
        indexing_vector_assign<F> (cv, e);
#endif
        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        typename E::const_iterator ite (e ().begin ());
        typename E::const_iterator ite_end (e ().end ());
        difference_type it_size (it_end - it);
        difference_type ite_size (ite_end - ite);
        if (it_size > 0 && ite_size > 0) {
            difference_type size ((std::min) (difference_type (it.index () - ite.index ()), ite_size));
            if (size > 0) {
                ite += size;
                ite_size -= size;
            }
        }
        if (it_size > 0 && ite_size > 0) {
            difference_type size ((std::min) (difference_type (ite.index () - it.index ()), it_size));
            if (size > 0) {
                it_size -= size;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                    while (-- size >= 0)    // zeroing
                        functor_type::apply (*it, value_type/*zero*/()), ++ it;
                } else {
                    it += size;
                }
            }
        }
        difference_type size ((std::min) (it_size, ite_size));
        it_size -= size;
        ite_size -= size;
        while (-- size >= 0)
            functor_type::apply (*it, *ite), ++ it, ++ ite;
        size = it_size;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        if (!functor_type::computed) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
            while (-- size >= 0)    // zeroing
                functor_type::apply (*it, value_type/*zero*/()), ++ it;
        } else {
            it += size;
        }
#if BOOST_UBLAS_TYPE_CHECK
        if (! disable_type_check<bool>::value) 
            BOOST_UBLAS_CHECK (detail::expression_type_check (v, cv), 
                               external_logic ("external logic or bad condition of inputs"));
#endif
    }
    // Sparse case
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign (V &v, const vector_expression<E> &e, sparse_tag) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        typedef F<typename V::iterator::reference, typename E::value_type> functor_type;
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
        BOOST_STATIC_ASSERT ((!functor_type::computed));
#ifdef _MSC_VER
#pragma warning(pop)
#endif
        typedef typename V::value_type value_type;
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        indexing_vector_assign<scalar_assign> (cv, v);
        indexing_vector_assign<F> (cv, e);
#endif
        v.clear ();
        typename E::const_iterator ite (e ().begin ());
        typename E::const_iterator ite_end (e ().end ());
        while (ite != ite_end) {
            value_type t (*ite);
            if (t != value_type/*zero*/())
                v.insert_element (ite.index (), t);
            ++ ite;
        }
#if BOOST_UBLAS_TYPE_CHECK
        if (! disable_type_check<bool>::value) 
            BOOST_UBLAS_CHECK (detail::expression_type_check (v, cv), 
                               external_logic ("external logic or bad condition of inputs"));
#endif
    }
    // Sparse proxy or functional case
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign (V &v, const vector_expression<E> &e, sparse_proxy_tag) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        typedef F<typename V::iterator::reference, typename E::value_type> functor_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;

#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        indexing_vector_assign<scalar_assign> (cv, v);
        indexing_vector_assign<F> (cv, e);
#endif
        detail::make_conformant (v, e);

        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        typename E::const_iterator ite (e ().begin ());
        typename E::const_iterator ite_end (e ().end ());
        if (it != it_end && ite != ite_end) {
            size_type it_index = it.index (), ite_index = ite.index ();
            for (;;) {
                difference_type compare = it_index - ite_index;
                if (compare == 0) {
                    functor_type::apply (*it, *ite);
                    ++ it, ++ ite;
                    if (it != it_end && ite != ite_end) {
                        it_index = it.index ();
                        ite_index = ite.index ();
                    } else
                        break;
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
                        functor_type::apply (*it, value_type/*zero*/());
                        ++ it;
                    } else
                        increment (it, it_end, - compare);
                    if (it != it_end)
                        it_index = it.index ();
                    else
                        break;
                } else if (compare > 0) {
                    increment (ite, ite_end, compare);
                    if (ite != ite_end)
                        ite_index = ite.index ();
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
            while (it != it_end) {  // zeroing
                functor_type::apply (*it, value_type/*zero*/());
                ++ it;
            }
        } else {
            it = it_end;
        }
#if BOOST_UBLAS_TYPE_CHECK
        if (! disable_type_check<bool>::value)
            BOOST_UBLAS_CHECK (detail::expression_type_check (v, cv), 
                               external_logic ("external logic or bad condition of inputs"));
#endif
    }

    // Dispatcher
    template<template <class T1, class T2> class F, class V, class E>
    BOOST_UBLAS_INLINE
    void vector_assign (V &v, const vector_expression<E> &e) {
        typedef typename vector_assign_traits<typename V::storage_category,
                                              F<typename V::reference, typename E::value_type>::computed,
                                              typename E::const_iterator::iterator_category>::storage_category storage_category;
        vector_assign<F> (v, e, storage_category ());
    }

    template<class SC, class RI>
    struct vector_swap_traits {
        typedef SC storage_category;
    };

    template<>
    struct vector_swap_traits<dense_proxy_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct vector_swap_traits<packed_proxy_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    // Dense (proxy) case
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_swap (V &v, vector_expression<E> &e, dense_proxy_tag) {
        typedef F<typename V::iterator::reference, typename E::iterator::reference> functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        typename V::iterator it (v.begin ());
        typename E::iterator ite (e ().begin ());
        while (-- size >= 0)
            functor_type::apply (*it, *ite), ++ it, ++ ite;
    }
    // Packed (proxy) case
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_swap (V &v, vector_expression<E> &e, packed_proxy_tag) {
        typedef F<typename V::iterator::reference, typename E::iterator::reference> functor_type;
        typedef typename V::difference_type difference_type;
        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        typename E::iterator ite (e ().begin ());
        typename E::iterator ite_end (e ().end ());
        difference_type it_size (it_end - it);
        difference_type ite_size (ite_end - ite);
        if (it_size > 0 && ite_size > 0) {
            difference_type size ((std::min) (difference_type (it.index () - ite.index ()), ite_size));
            if (size > 0) {
                ite += size;
                ite_size -= size;
            }
        }
        if (it_size > 0 && ite_size > 0) {
            difference_type size ((std::min) (difference_type (ite.index () - it.index ()), it_size));
            if (size > 0)
                it_size -= size;
        }
        difference_type size ((std::min) (it_size, ite_size));
        it_size -= size;
        ite_size -= size;
        while (-- size >= 0)
            functor_type::apply (*it, *ite), ++ it, ++ ite;
    }
    // Sparse proxy case
    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_swap (V &v, vector_expression<E> &e, sparse_proxy_tag) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        typedef F<typename V::iterator::reference, typename E::iterator::reference> functor_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;

        detail::make_conformant (v, e);
        // FIXME should be a seperate restriction for E
        detail::make_conformant (e (), v);

        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        typename E::iterator ite (e ().begin ());
        typename E::iterator ite_end (e ().end ());
        if (it != it_end && ite != ite_end) {
            size_type it_index = it.index (), ite_index = ite.index ();
            for (;;) {
                difference_type compare = it_index - ite_index;
                if (compare == 0) {
                    functor_type::apply (*it, *ite);
                    ++ it, ++ ite;
                    if (it != it_end && ite != ite_end) {
                        it_index = it.index ();
                        ite_index = ite.index ();
                    } else
                        break;
                } else if (compare < 0) {
                    increment (it, it_end, - compare);
                    if (it != it_end)
                        it_index = it.index ();
                    else
                        break;
                } else if (compare > 0) {
                    increment (ite, ite_end, compare);
                    if (ite != ite_end)
                        ite_index = ite.index ();
                    else
                        break;
                }
            }
        }

#if BOOST_UBLAS_TYPE_CHECK
        increment (ite, ite_end);
        increment (it, it_end);
#endif
    }

    // Dispatcher
    template<template <class T1, class T2> class F, class V, class E>
    BOOST_UBLAS_INLINE
    void vector_swap (V &v, vector_expression<E> &e) {
        typedef typename vector_swap_traits<typename V::storage_category,
                                            typename E::const_iterator::iterator_category>::storage_category storage_category;
        vector_swap<F> (v, e, storage_category ());
    }

}}}

#endif

/* vector_assign.hpp
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
*/
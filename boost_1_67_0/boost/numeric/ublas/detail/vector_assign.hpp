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
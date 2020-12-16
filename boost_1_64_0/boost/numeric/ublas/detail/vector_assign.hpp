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
kqX4Y9jefGkSA2+eEABQabL0iAU13qbn9JDN1MWb6v6U2VMqMz4infpOU6tFd+B1WtqYXHs6m++NcaehmgM1dwd+YVgjt4YLZTDbQzcsO4qgzqFcpTqskkkPEiHHe4sEOgvZbct1CY2likPJaM+nAjzWL8I1qFcZeUQnCK/JbuFpvcGeNWgsBiW2rOxf7eAGmK7kagvjjB+38zZmgpE0mCqdTFfkJ3wc0ZDVR6xsmGvnsguneazoa6x45TuxVkZjy8A/wjhKioVFumq0jc+uysYw9CoYPygxrAWbyZnTy1mmHpGdwUShuwNdRzYMj/4ViQe4jYU8FexYjsp0KBYpa6QXVu64F0EZ9a2VCSHHt9WpchiNe0GBL9BBi3nwjwJo6Fg0L4b2tkDWL6zz6NwRRrtkk7xo2sTI1vSZdNPQScgZIXSEY8kyVzmhfQpU2lVJXtxy3D++y22m3zhrOExTPT0WpNGx1GX7KabsCKpOLxkPK5hIBxoOdmK5MSaHu7kAk0nSOgVWi/lquuUHqpmWo8jReFuXF1OWVzGU0YxcxM9JnF6ONEuCjbMyiHDW3oklT5kn6gZKqB7jC6xO0mC8ZOPzsaCPj1kLwEIHlmezOh9svOM9eAurV1SDcYtMYFuf9d4+6aCJis4uLU99iN2WQl52xOgS3bL63XeBUcuUclXLSgaXDh4grQNjHlq8RQGzMdZei5ZVpTSDUkRFyInTwaUn3YHoiXSXuUIzUqvpc+miYIfpCh9fWqrDdDvvM6B1eXti2BuPc0N2EgGbxYxO9BdOeTtpCGd45cbZyUD3OqCSJIzo+nZPbYcjGGsqHZ005KW1GL4FmurpA6MCYGH1yCnov2itEmMDkktlkh2o5cHiLOknGXPdVDU2WJ2Buu58gi4o1jppqkrTAtiRf77KP7m20d0VlEcua25/kbzRbzRrOUxe5s5WbZeWE1E25Mz2mu5RtjYxED6aXqLNVe0L6SNZuciJljrDGzZyMDBI9lUGiB4xTQ3dYdA4CqQcnmMwlOwpxOp1FRODVg1tfNDHGeNo3pFYJZ5wYiq8GhHWEzwby2tfErNKPh/j2wFBPnSk42oignSm8tMbGxI/LClhyENeE091CqrxkOMw7Q/S3ZRzTDxNWOAX1duiZmyQb8mtCtZ8Vrdj9TUQJs1uvfZYEs09NeJUWa0VVY3vdxYHWSoH1n6RqaOomRPkg30gtRXT3cVzIIXe6TIKmFOvHTdVf5FEiBNfP+KKLHy/syvIhvTCxoYT5T3awZUFsjQY60JM9KzCbhM1ltdPbiaVtPXlI631Vqnu8mlZExMPR3bSw0OPlOvuEC1yHCLcx2AcYOtyJx/ra6XTrqRap8g/ana1DnnRe4gujTX2v6geSX2TqUEwFylomSEchwEmangredwPnlZlwnSgKZ2ITjnABwVSR9mNswdzpGPVZHHzvmPni/TYY18ba21TmOktBrGWvOmP3eSTf/aYuS88uob0ykJ8UWNghz5VHHrpa030xiWSrl1jHX/qSmyc7ngVxvIrC89sjFor1ecTLIzqHm1c4XxWY1zjfBuP9EAO0aTNXOAO1yPWt2IOPbnuTAZDoGTf5Wx1EHe1lopiLuol7XEY8qoNdcjbwx7CYEGExm2qtZXDe7n2hCxtjeOSLxrJm1MWeuTWDUYTtGQfuzTdrPiuPCVMdxfUYnyHFb7uLgoa0zj32peNXZVOWQqUDvRXKOar1Oadiqs9t1HyzvR0z6cI12e6uudRhDWaqsKzCPb8w55b2Xi59I19vrwDQ8F24PLWEM7lLwU/TIeJJZx7rmRjKYuto06kwzVfMvFUGK2RoBuvk4Duk1s1UdbBeAtfK/MRUlo=
*/
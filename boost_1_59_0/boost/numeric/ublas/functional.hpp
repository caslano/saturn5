//
//  Copyright (c) 2000-2009
//  Joerg Walter, Mathias Koch, Gunter Winkler
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_FUNCTIONAL_
#define _BOOST_UBLAS_FUNCTIONAL_

#include <functional>

#include <boost/core/ignore_unused.hpp>

#include <boost/numeric/ublas/traits.hpp>
#ifdef BOOST_UBLAS_USE_DUFF_DEVICE
#include <boost/numeric/ublas/detail/duff.hpp>
#endif
#ifdef BOOST_UBLAS_USE_SIMD
#include <boost/numeric/ublas/detail/raw.hpp>
#else
namespace boost { namespace numeric { namespace ublas { namespace raw {
}}}}
#endif
#ifdef BOOST_UBLAS_HAVE_BINDINGS
#include <boost/numeric/bindings/traits/std_vector.hpp>
#include <boost/numeric/bindings/traits/ublas_vector.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#include <boost/numeric/bindings/atlas/cblas.hpp>
#endif

#include <boost/numeric/ublas/detail/definitions.hpp>



namespace boost { namespace numeric { namespace ublas {

    // Scalar functors

    // Unary
    template<class T>
    struct scalar_unary_functor {
        typedef T value_type;
        typedef typename type_traits<T>::const_reference argument_type;
        typedef typename type_traits<T>::value_type result_type;
    };

    template<class T>
    struct scalar_identity:
        public scalar_unary_functor<T> {
        typedef typename scalar_unary_functor<T>::argument_type argument_type;
        typedef typename scalar_unary_functor<T>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument_type t) {
            return t;
        }
    };
    template<class T>
    struct scalar_negate:
        public scalar_unary_functor<T> {
        typedef typename scalar_unary_functor<T>::argument_type argument_type;
        typedef typename scalar_unary_functor<T>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument_type t) {
            return - t;
        }
    };
    template<class T>
    struct scalar_conj:
        public scalar_unary_functor<T> {
        typedef typename scalar_unary_functor<T>::value_type value_type;
        typedef typename scalar_unary_functor<T>::argument_type argument_type;
        typedef typename scalar_unary_functor<T>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument_type t) {
            return type_traits<value_type>::conj (t);
        }
    };

    // Unary returning real
    template<class T>
    struct scalar_real_unary_functor {
        typedef T value_type;
        typedef typename type_traits<T>::const_reference argument_type;
        typedef typename type_traits<T>::real_type result_type;
    };

    template<class T>
    struct scalar_real:
        public scalar_real_unary_functor<T> {
        typedef typename scalar_real_unary_functor<T>::value_type value_type;
        typedef typename scalar_real_unary_functor<T>::argument_type argument_type;
        typedef typename scalar_real_unary_functor<T>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument_type t) {
            return type_traits<value_type>::real (t);
        }
    };
    template<class T>
    struct scalar_imag:
        public scalar_real_unary_functor<T> {
        typedef typename scalar_real_unary_functor<T>::value_type value_type;
        typedef typename scalar_real_unary_functor<T>::argument_type argument_type;
        typedef typename scalar_real_unary_functor<T>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument_type t) {
            return type_traits<value_type>::imag (t);
        }
    };

    // Binary
    template<class T1, class T2>
    struct scalar_binary_functor {
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::promote_type result_type;
    };

    template<class T1, class T2>
    struct scalar_plus:
        public scalar_binary_functor<T1, T2> {
        typedef typename scalar_binary_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_functor<T1, T2>::argument2_type argument2_type;
        typedef typename scalar_binary_functor<T1, T2>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument1_type t1, argument2_type t2) {
            return t1 + t2;
        }
    };
    template<class T1, class T2>
    struct scalar_minus:
        public scalar_binary_functor<T1, T2> {
        typedef typename scalar_binary_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_functor<T1, T2>::argument2_type argument2_type;
        typedef typename scalar_binary_functor<T1, T2>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument1_type t1, argument2_type t2) {
            return t1 - t2;
        }
    };
    template<class T1, class T2>
    struct scalar_multiplies:
        public scalar_binary_functor<T1, T2> {
        typedef typename scalar_binary_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_functor<T1, T2>::argument2_type argument2_type;
        typedef typename scalar_binary_functor<T1, T2>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument1_type t1, argument2_type t2) {
            return t1 * t2;
        }
    };
    template<class T1, class T2>
    struct scalar_divides:
        public scalar_binary_functor<T1, T2> {
        typedef typename scalar_binary_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_functor<T1, T2>::argument2_type argument2_type;
        typedef typename scalar_binary_functor<T1, T2>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument1_type t1, argument2_type t2) {
            return t1 / t2;
        }
    };

    template<class T1, class T2>
    struct scalar_binary_assign_functor {
        // ISSUE Remove reference to avoid reference to reference problems
        typedef typename type_traits<typename boost::remove_reference<T1>::type>::reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
    };

    struct assign_tag {};
    struct computed_assign_tag {};

    template<class T1, class T2>
    struct scalar_assign:
        public scalar_binary_assign_functor<T1, T2> {
        typedef typename scalar_binary_assign_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_assign_functor<T1, T2>::argument2_type argument2_type;
#if BOOST_WORKAROUND( __IBMCPP__, <=600 )
        static const bool computed ;
#else
        static const bool computed = false ;
#endif

        static BOOST_UBLAS_INLINE
        void apply (argument1_type t1, argument2_type t2) {
            t1 = t2;
        }

        template<class U1, class U2>
        struct rebind {
            typedef scalar_assign<U1, U2> other;
        };
    };

#if BOOST_WORKAROUND( __IBMCPP__, <=600 )
    template<class T1, class T2>
    const bool scalar_assign<T1,T2>::computed = false;
#endif

    template<class T1, class T2>
    struct scalar_plus_assign:
        public scalar_binary_assign_functor<T1, T2> {
        typedef typename scalar_binary_assign_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_assign_functor<T1, T2>::argument2_type argument2_type;
#if BOOST_WORKAROUND( __IBMCPP__, <=600 )
        static const bool computed ;
#else
        static const bool computed = true ;
#endif

        static BOOST_UBLAS_INLINE
        void apply (argument1_type t1, argument2_type t2) {
            t1 += t2;
        }

        template<class U1, class U2>
        struct rebind {
            typedef scalar_plus_assign<U1, U2> other;
        };
    };

#if BOOST_WORKAROUND( __IBMCPP__, <=600 )
    template<class T1, class T2>
    const bool scalar_plus_assign<T1,T2>::computed = true;
#endif

    template<class T1, class T2>
    struct scalar_minus_assign:
        public scalar_binary_assign_functor<T1, T2> {
        typedef typename scalar_binary_assign_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_assign_functor<T1, T2>::argument2_type argument2_type;
#if BOOST_WORKAROUND( __IBMCPP__, <=600 )
        static const bool computed ;
#else
        static const bool computed = true ;
#endif

        static BOOST_UBLAS_INLINE
        void apply (argument1_type t1, argument2_type t2) {
            t1 -= t2;
        }

        template<class U1, class U2>
        struct rebind {
            typedef scalar_minus_assign<U1, U2> other;
        };
    };

#if BOOST_WORKAROUND( __IBMCPP__, <=600 )
    template<class T1, class T2>
    const bool scalar_minus_assign<T1,T2>::computed = true;
#endif

    template<class T1, class T2>
    struct scalar_multiplies_assign:
        public scalar_binary_assign_functor<T1, T2> {
        typedef typename scalar_binary_assign_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_assign_functor<T1, T2>::argument2_type argument2_type;
        static const bool computed = true;

        static BOOST_UBLAS_INLINE
        void apply (argument1_type t1, argument2_type t2) {
            t1 *= t2;
        }

        template<class U1, class U2>
        struct rebind {
            typedef scalar_multiplies_assign<U1, U2> other;
        };
    };
    template<class T1, class T2>
    struct scalar_divides_assign:
        public scalar_binary_assign_functor<T1, T2> {
        typedef typename scalar_binary_assign_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_assign_functor<T1, T2>::argument2_type argument2_type;
        static const bool computed ;

        static BOOST_UBLAS_INLINE
        void apply (argument1_type t1, argument2_type t2) {
            t1 /= t2;
        }

        template<class U1, class U2>
        struct rebind {
            typedef scalar_divides_assign<U1, U2> other;
        };
    };
    template<class T1, class T2>
    const bool scalar_divides_assign<T1,T2>::computed = true;

    template<class T1, class T2>
    struct scalar_binary_swap_functor {
        typedef typename type_traits<typename boost::remove_reference<T1>::type>::reference argument1_type;
        typedef typename type_traits<typename boost::remove_reference<T2>::type>::reference argument2_type;
    };

    template<class T1, class T2>
    struct scalar_swap:
        public scalar_binary_swap_functor<T1, T2> {
        typedef typename scalar_binary_swap_functor<T1, T2>::argument1_type argument1_type;
        typedef typename scalar_binary_swap_functor<T1, T2>::argument2_type argument2_type;

        static BOOST_UBLAS_INLINE
        void apply (argument1_type t1, argument2_type t2) {
            std::swap (t1, t2);
        }

        template<class U1, class U2>
        struct rebind {
            typedef scalar_swap<U1, U2> other;
        };
    };

    // Vector functors

    // Unary returning scalar
    template<class V>
    struct vector_scalar_unary_functor {
        typedef typename V::value_type value_type;
        typedef typename V::value_type result_type;
    };

    template<class V>
    struct vector_sum: 
        public vector_scalar_unary_functor<V> {
        typedef typename vector_scalar_unary_functor<V>::value_type value_type;
        typedef typename vector_scalar_unary_functor<V>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E> &e) { 
            result_type t = result_type (0);
            typedef typename E::size_type vector_size_type;
            vector_size_type size (e ().size ());
            for (vector_size_type i = 0; i < size; ++ i)
                t += e () (i);
            return t;
        }
        // Dense case
        template<class D, class I>
        static BOOST_UBLAS_INLINE
        result_type apply (D size, I it) { 
            result_type t = result_type (0);
            while (-- size >= 0)
                t += *it, ++ it;
            return t; 
        }
        // Sparse case
        template<class I>
        static BOOST_UBLAS_INLINE
        result_type apply (I it, const I &it_end) {
            result_type t = result_type (0);
            while (it != it_end) 
                t += *it, ++ it;
            return t; 
        }
    };

    // Unary returning real scalar 
    template<class V>
    struct vector_scalar_real_unary_functor {
        typedef typename V::value_type value_type;
        typedef typename type_traits<value_type>::real_type real_type;
        typedef real_type result_type;
    };

    template<class V>
    struct vector_norm_1:
        public vector_scalar_real_unary_functor<V> {
        typedef typename vector_scalar_real_unary_functor<V>::value_type value_type;
        typedef typename vector_scalar_real_unary_functor<V>::real_type real_type;
        typedef typename vector_scalar_real_unary_functor<V>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E> &e) {
            real_type t = real_type ();
            typedef typename E::size_type vector_size_type;
            vector_size_type size (e ().size ());
            for (vector_size_type i = 0; i < size; ++ i) {
                real_type u (type_traits<value_type>::type_abs (e () (i)));
                t += u;
            }
            return t;
        }
        // Dense case
        template<class D, class I>
        static BOOST_UBLAS_INLINE
        result_type apply (D size, I it) {
            real_type t = real_type ();
            while (-- size >= 0) {
                real_type u (type_traits<value_type>::norm_1 (*it));
                t += u;
                ++ it;
            }
            return t;
        }
        // Sparse case
        template<class I>
        static BOOST_UBLAS_INLINE
        result_type apply (I it, const I &it_end) {
            real_type t = real_type ();
            while (it != it_end) {
                real_type u (type_traits<value_type>::norm_1 (*it));
                t += u;
                ++ it;
            }
            return t;
        }
    };
    template<class V>
    struct vector_norm_2:
        public vector_scalar_real_unary_functor<V> {
        typedef typename vector_scalar_real_unary_functor<V>::value_type value_type;
        typedef typename vector_scalar_real_unary_functor<V>::real_type real_type;
        typedef typename vector_scalar_real_unary_functor<V>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E> &e) {
            typedef typename E::size_type vector_size_type;
            vector_size_type size (e ().size ());
#ifndef BOOST_UBLAS_SCALED_NORM
            real_type t = real_type ();
            for (vector_size_type i = 0; i < size; ++ i) {
                real_type u (type_traits<value_type>::norm_2 (e () (i)));
                t +=  u * u;
            }
            return static_cast<result_type>(type_traits<real_type>::type_sqrt (t));
#else
            real_type scale = real_type ();
            real_type sum_squares (1);
            for (vector_size_type i = 0; i < size; ++ i) {
                real_type u (type_traits<value_type>::norm_2 (e () (i)));
                if ( real_type () /* zero */ == u ) continue;
                if (scale < u) {
                    real_type v (scale / u);
                    sum_squares = sum_squares * v * v + real_type (1);
                    scale = u;
                } else {
                    real_type v (u / scale);
                    sum_squares += v * v;
                }
            }
            return static_cast<result_type>(scale * type_traits<real_type>::type_sqrt (sum_squares));
#endif
        }
        // Dense case
        template<class D, class I>
        static BOOST_UBLAS_INLINE
        result_type apply (D size, I it) {
#ifndef BOOST_UBLAS_SCALED_NORM
            real_type t = real_type ();
            while (-- size >= 0) {
                real_type u (type_traits<value_type>::norm_2 (*it));
                t +=  u * u;
                ++ it;
            }
            return static_cast<result_type>(type_traits<real_type>::type_sqrt (t));
#else
            real_type scale = real_type ();
            real_type sum_squares (1);
            while (-- size >= 0) {
                real_type u (type_traits<value_type>::norm_2 (*it));
                if (scale < u) {
                    real_type v (scale / u);
                    sum_squares = sum_squares * v * v + real_type (1);
                    scale = u;
                } else {
                    real_type v (u / scale);
                    sum_squares += v * v;
                }
                ++ it;
            }
            return static_cast<result_type>(scale * type_traits<real_type>::type_sqrt (sum_squares));
#endif
        }
        // Sparse case
        template<class I>
        static BOOST_UBLAS_INLINE
        result_type apply (I it, const I &it_end) {
#ifndef BOOST_UBLAS_SCALED_NORM
            real_type t = real_type ();
            while (it != it_end) {
                real_type u (type_traits<value_type>::norm_2 (*it));
                t +=  u * u;
                ++ it;
            }
            return static_cast<result_type>(type_traits<real_type>::type_sqrt (t));
#else
            real_type scale = real_type ();
            real_type sum_squares (1);
            while (it != it_end) {
                real_type u (type_traits<value_type>::norm_2 (*it));
                if (scale < u) {
                    real_type v (scale / u);
                    sum_squares = sum_squares * v * v + real_type (1);
                    scale = u;
                } else {
                    real_type v (u / scale);
                    sum_squares += v * v;
                }
                ++ it;
            }
            return static_cast<result_type>(scale * type_traits<real_type>::type_sqrt (sum_squares));
#endif
        }
    };

    template<class V>
    struct vector_norm_2_square :
        public vector_scalar_real_unary_functor<V> {
        typedef typename vector_scalar_real_unary_functor<V>::value_type value_type;
        typedef typename vector_scalar_real_unary_functor<V>::real_type real_type;
        typedef typename vector_scalar_real_unary_functor<V>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E> &e) {
            real_type t = real_type ();
            typedef typename E::size_type vector_size_type;
            vector_size_type size (e ().size ());
            for (vector_size_type i = 0; i < size; ++ i) {
                real_type u (type_traits<value_type>::norm_2 (e () (i)));
                t +=  u * u;
            }
            return t;
        }
        // Dense case
        template<class D, class I>
        static BOOST_UBLAS_INLINE
        result_type apply (D size, I it) {
            real_type t = real_type ();
            while (-- size >= 0) {
                real_type u (type_traits<value_type>::norm_2 (*it));
                t +=  u * u;
                ++ it;
            }
            return t;
        }
        // Sparse case
        template<class I>
        static BOOST_UBLAS_INLINE
        result_type apply (I it, const I &it_end) {
            real_type t = real_type ();
            while (it != it_end) {
                real_type u (type_traits<value_type>::norm_2 (*it));
                t +=  u * u;
                ++ it;
            }
            return t;
        }
    };

    template<class V>
    struct vector_norm_inf:
        public vector_scalar_real_unary_functor<V> {
        typedef typename vector_scalar_real_unary_functor<V>::value_type value_type;
        typedef typename vector_scalar_real_unary_functor<V>::real_type real_type;
        typedef typename vector_scalar_real_unary_functor<V>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E> &e) {
            real_type t = real_type ();
            typedef typename E::size_type vector_size_type;
            vector_size_type size (e ().size ());
            for (vector_size_type i = 0; i < size; ++ i) {
                real_type u (type_traits<value_type>::norm_inf (e () (i)));
                if (u > t)
                    t = u;
            }
            return t;
        }
        // Dense case
        template<class D, class I>
        static BOOST_UBLAS_INLINE
        result_type apply (D size, I it) {
            real_type t = real_type ();
            while (-- size >= 0) {
                real_type u (type_traits<value_type>::norm_inf (*it));
                if (u > t)
                    t = u;
                ++ it;
            }
            return t;
        }
        // Sparse case
        template<class I>
        static BOOST_UBLAS_INLINE
        result_type apply (I it, const I &it_end) { 
            real_type t = real_type ();
            while (it != it_end) {
                real_type u (type_traits<value_type>::norm_inf (*it));
                if (u > t) 
                    t = u;
                ++ it;
            }
            return t; 
        }
    };

    // Unary returning index
    template<class V>
    struct vector_scalar_index_unary_functor {
        typedef typename V::value_type value_type;
        typedef typename type_traits<value_type>::real_type real_type;
        typedef typename V::size_type result_type;
    };

    template<class V>
    struct vector_index_norm_inf:
        public vector_scalar_index_unary_functor<V> {
        typedef typename vector_scalar_index_unary_functor<V>::value_type value_type;
        typedef typename vector_scalar_index_unary_functor<V>::real_type real_type;
        typedef typename vector_scalar_index_unary_functor<V>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E> &e) {
            // ISSUE For CBLAS compatibility return 0 index in empty case
            result_type i_norm_inf (0);
            real_type t = real_type ();
            typedef typename E::size_type vector_size_type;
            vector_size_type size (e ().size ());
            for (vector_size_type i = 0; i < size; ++ i) {
                real_type u (type_traits<value_type>::norm_inf (e () (i)));
                if (u > t) {
                    i_norm_inf = i;
                    t = u;
                }
            }
            return i_norm_inf;
        }
        // Dense case
        template<class D, class I>
        static BOOST_UBLAS_INLINE
        result_type apply (D size, I it) {
            // ISSUE For CBLAS compatibility return 0 index in empty case
            result_type i_norm_inf (0);
            real_type t = real_type ();
            while (-- size >= 0) {
                real_type u (type_traits<value_type>::norm_inf (*it));
                if (u > t) {
                    i_norm_inf = it.index ();
                    t = u;
                }
                ++ it;
            }
            return i_norm_inf;
        }
        // Sparse case
        template<class I>
        static BOOST_UBLAS_INLINE
        result_type apply (I it, const I &it_end) {
            // ISSUE For CBLAS compatibility return 0 index in empty case
            result_type i_norm_inf (0);
            real_type t = real_type ();
            while (it != it_end) {
                real_type u (type_traits<value_type>::norm_inf (*it));
                if (u > t) {
                    i_norm_inf = it.index ();
                    t = u;
                }
                ++ it;
            }
            return i_norm_inf;
        }
    };

    // Binary returning scalar
    template<class V1, class V2, class TV>
    struct vector_scalar_binary_functor {
        typedef TV value_type;
        typedef TV result_type;
    };

    template<class V1, class V2, class TV>
    struct vector_inner_prod:
        public vector_scalar_binary_functor<V1, V2, TV> {
        typedef typename vector_scalar_binary_functor<V1, V2, TV>::value_type value_type;
        typedef typename vector_scalar_binary_functor<V1, V2, TV>::result_type result_type;

        template<class C1, class C2>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_container<C1> &c1,
                           const vector_container<C2> &c2) {
#ifdef BOOST_UBLAS_USE_SIMD
            using namespace raw;
            typedef typename C1::size_type vector_size_type;
            vector_size_type size (BOOST_UBLAS_SAME (c1 ().size (), c2 ().size ()));
            const typename V1::value_type *data1 = data_const (c1 ());
            const typename V1::value_type *data2 = data_const (c2 ());
            vector_size_type s1 = stride (c1 ());
            vector_size_type s2 = stride (c2 ());
            result_type t = result_type (0);
            if (s1 == 1 && s2 == 1) {
                for (vector_size_type i = 0; i < size; ++ i)
                    t += data1 [i] * data2 [i];
            } else if (s2 == 1) {
                for (vector_size_type i = 0, i1 = 0; i < size; ++ i, i1 += s1)
                    t += data1 [i1] * data2 [i];
            } else if (s1 == 1) {
                for (vector_size_type i = 0, i2 = 0; i < size; ++ i, i2 += s2)
                    t += data1 [i] * data2 [i2];
            } else {
                for (vector_size_type i = 0, i1 = 0, i2 = 0; i < size; ++ i, i1 += s1, i2 += s2)
                    t += data1 [i1] * data2 [i2];
            }
            return t;
#elif defined(BOOST_UBLAS_HAVE_BINDINGS)
            return boost::numeric::bindings::atlas::dot (c1 (), c2 ());
#else
            return apply (static_cast<const vector_expression<C1> > (c1), static_cast<const vector_expression<C2> > (c2));
#endif
        }
        template<class E1, class E2>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E1> &e1,
                           const vector_expression<E2> &e2) {
            typedef typename E1::size_type vector_size_type;
            vector_size_type size (BOOST_UBLAS_SAME (e1 ().size (), e2 ().size ()));
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (vector_size_type i = 0; i < size; ++ i)
                t += e1 () (i) * e2 () (i);
#else
            vector_size_type i (0);
            DD (size, 4, r, (t += e1 () (i) * e2 () (i), ++ i));
#endif
            return t;
        }
        // Dense case
        template<class D, class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (D size, I1 it1, I2 it2) {
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
#else
            DD (size, 4, r, (t += *it1 * *it2, ++ it1, ++ it2));
#endif
            return t;
        }
        // Packed case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end) {
            result_type t = result_type (0);
            typedef typename I1::difference_type vector_difference_type;
            vector_difference_type it1_size (it1_end - it1);
            vector_difference_type it2_size (it2_end - it2);
            vector_difference_type diff (0);
            if (it1_size > 0 && it2_size > 0)
                diff = it2.index () - it1.index ();
            if (diff != 0) {
                vector_difference_type size = (std::min) (diff, it1_size);
                if (size > 0) {
                    it1 += size;
                    it1_size -= size;
                    diff -= size;
                }
                size = (std::min) (- diff, it2_size);
                if (size > 0) {
                    it2 += size;
                    it2_size -= size;
                    diff += size;
                }
            }
            vector_difference_type size ((std::min) (it1_size, it2_size));
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
            return t;
        }
        // Sparse case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end, sparse_bidirectional_iterator_tag) {
            result_type t = result_type (0);
            if (it1 != it1_end && it2 != it2_end) {
                for (;;) {
                    if (it1.index () == it2.index ()) {
                        t += *it1 * *it2, ++ it1, ++ it2;
                        if (it1 == it1_end || it2 == it2_end)
                            break;
                    } else if (it1.index () < it2.index ()) {
                        increment (it1, it1_end, it2.index () - it1.index ());
                        if (it1 == it1_end)
                            break;
                    } else if (it1.index () > it2.index ()) {
                        increment (it2, it2_end, it1.index () - it2.index ());
                        if (it2 == it2_end)
                            break;
                    }
                }
            }
            return t;
        }
    };

    // Matrix functors

    // Binary returning vector
    template<class M1, class M2, class TV>
    struct matrix_vector_binary_functor {
        typedef typename M1::size_type size_type;
        typedef typename M1::difference_type difference_type;
        typedef TV value_type;
        typedef TV result_type;
    };

    template<class M1, class M2, class TV>
    struct matrix_vector_prod1:
        public matrix_vector_binary_functor<M1, M2, TV> {
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::size_type size_type;
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::difference_type difference_type;
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::value_type value_type;
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::result_type result_type;

        template<class C1, class C2>
        static BOOST_UBLAS_INLINE
        result_type apply (const matrix_container<C1> &c1,
                           const vector_container<C2> &c2,
                           size_type i) {
#ifdef BOOST_UBLAS_USE_SIMD
            using namespace raw;
            size_type size = BOOST_UBLAS_SAME (c1 ().size2 (), c2 ().size ());
            const typename M1::value_type *data1 = data_const (c1 ()) + i * stride1 (c1 ());
            const typename M2::value_type *data2 = data_const (c2 ());
            size_type s1 = stride2 (c1 ());
            size_type s2 = stride (c2 ());
            result_type t = result_type (0);
            if (s1 == 1 && s2 == 1) {
                for (size_type j = 0; j < size; ++ j)
                    t += data1 [j] * data2 [j];
            } else if (s2 == 1) {
                for (size_type j = 0, j1 = 0; j < size; ++ j, j1 += s1)
                    t += data1 [j1] * data2 [j];
            } else if (s1 == 1) {
                for (size_type j = 0, j2 = 0; j < size; ++ j, j2 += s2)
                    t += data1 [j] * data2 [j2];
            } else {
                for (size_type j = 0, j1 = 0, j2 = 0; j < size; ++ j, j1 += s1, j2 += s2)
                    t += data1 [j1] * data2 [j2];
            }
            return t;
#elif defined(BOOST_UBLAS_HAVE_BINDINGS)
            return boost::numeric::bindings::atlas::dot (c1 ().row (i), c2 ());
#else
            return apply (static_cast<const matrix_expression<C1> > (c1), static_cast<const vector_expression<C2> > (c2, i));
#endif
        }
        template<class E1, class E2>
        static BOOST_UBLAS_INLINE
        result_type apply (const matrix_expression<E1> &e1,
                           const vector_expression<E2> &e2,
                           size_type i) {
            size_type size = BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size ());
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type j = 0; j < size; ++ j)
                t += e1 () (i, j) * e2 () (j);
#else
            size_type j (0);
            DD (size, 4, r, (t += e1 () (i, j) * e2 () (j), ++ j));
#endif
            return t;
        }
        // Dense case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (difference_type size, I1 it1, I2 it2) {
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
#else
            DD (size, 4, r, (t += *it1 * *it2, ++ it1, ++ it2));
#endif
            return t;
        }
        // Packed case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end) {
            result_type t = result_type (0);
            difference_type it1_size (it1_end - it1);
            difference_type it2_size (it2_end - it2);
            difference_type diff (0);
            if (it1_size > 0 && it2_size > 0)
                diff = it2.index () - it1.index2 ();
            if (diff != 0) {
                difference_type size = (std::min) (diff, it1_size);
                if (size > 0) {
                    it1 += size;
                    it1_size -= size;
                    diff -= size;
                }
                size = (std::min) (- diff, it2_size);
                if (size > 0) {
                    it2 += size;
                    it2_size -= size;
                    diff += size;
                }
            }
            difference_type size ((std::min) (it1_size, it2_size));
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
            return t;
        }
        // Sparse case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end,
                           sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag) {
            result_type t = result_type (0);
            if (it1 != it1_end && it2 != it2_end) {
                size_type it1_index = it1.index2 (), it2_index = it2.index ();
                for (;;) {
                    difference_type compare = it1_index - it2_index;
                    if (compare == 0) {
                        t += *it1 * *it2, ++ it1, ++ it2;
                        if (it1 != it1_end && it2 != it2_end) {
                            it1_index = it1.index2 ();
                            it2_index = it2.index ();
                        } else
                            break;
                    } else if (compare < 0) {
                        increment (it1, it1_end, - compare);
                        if (it1 != it1_end)
                            it1_index = it1.index2 ();
                        else
                            break;
                    } else if (compare > 0) {
                        increment (it2, it2_end, compare);
                        if (it2 != it2_end)
                            it2_index = it2.index ();
                        else
                            break;
                    }
                }
            }
            return t;
        }
        // Sparse packed case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &/* it2_end */,
                           sparse_bidirectional_iterator_tag, packed_random_access_iterator_tag) {
            result_type t = result_type (0);
            while (it1 != it1_end) {
                t += *it1 * it2 () (it1.index2 ());
                ++ it1;
            }
            return t;
        }
        // Packed sparse case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &/* it1_end */, I2 it2, const I2 &it2_end,
                           packed_random_access_iterator_tag, sparse_bidirectional_iterator_tag) {
            result_type t = result_type (0);
            while (it2 != it2_end) {
                t += it1 () (it1.index1 (), it2.index ()) * *it2;
                ++ it2;
            }
            return t;
        }
        // Another dispatcher
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end,
                           sparse_bidirectional_iterator_tag) {
            typedef typename I1::iterator_category iterator1_category;
            typedef typename I2::iterator_category iterator2_category;
            return apply (it1, it1_end, it2, it2_end, iterator1_category (), iterator2_category ());
        }
    };

    template<class M1, class M2, class TV>
    struct matrix_vector_prod2:
        public matrix_vector_binary_functor<M1, M2, TV> {
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::size_type size_type;
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::difference_type difference_type;
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::value_type value_type;
        typedef typename matrix_vector_binary_functor<M1, M2, TV>::result_type result_type;

        template<class C1, class C2>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_container<C1> &c1,
                           const matrix_container<C2> &c2,
                           size_type i) {
#ifdef BOOST_UBLAS_USE_SIMD
            using namespace raw;
            size_type size = BOOST_UBLAS_SAME (c1 ().size (), c2 ().size1 ());
            const typename M1::value_type *data1 = data_const (c1 ());
            const typename M2::value_type *data2 = data_const (c2 ()) + i * stride2 (c2 ());
            size_type s1 = stride (c1 ());
            size_type s2 = stride1 (c2 ());
            result_type t = result_type (0);
            if (s1 == 1 && s2 == 1) {
                for (size_type j = 0; j < size; ++ j)
                    t += data1 [j] * data2 [j];
            } else if (s2 == 1) {
                for (size_type j = 0, j1 = 0; j < size; ++ j, j1 += s1)
                    t += data1 [j1] * data2 [j];
            } else if (s1 == 1) {
                for (size_type j = 0, j2 = 0; j < size; ++ j, j2 += s2)
                    t += data1 [j] * data2 [j2];
            } else {
                for (size_type j = 0, j1 = 0, j2 = 0; j < size; ++ j, j1 += s1, j2 += s2)
                    t += data1 [j1] * data2 [j2];
            }
            return t;
#elif defined(BOOST_UBLAS_HAVE_BINDINGS)
            return boost::numeric::bindings::atlas::dot (c1 (), c2 ().column (i));
#else
            return apply (static_cast<const vector_expression<C1> > (c1), static_cast<const matrix_expression<C2> > (c2, i));
#endif
        }
        template<class E1, class E2>
        static BOOST_UBLAS_INLINE
        result_type apply (const vector_expression<E1> &e1,
                           const matrix_expression<E2> &e2,
                           size_type i) {
            size_type size = BOOST_UBLAS_SAME (e1 ().size (), e2 ().size1 ());
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type j = 0; j < size; ++ j)
                t += e1 () (j) * e2 () (j, i);
#else
            size_type j (0);
            DD (size, 4, r, (t += e1 () (j) * e2 () (j, i), ++ j));
#endif
            return t;
        }
        // Dense case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (difference_type size, I1 it1, I2 it2) {
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
#else
            DD (size, 4, r, (t += *it1 * *it2, ++ it1, ++ it2));
#endif
            return t;
        }
        // Packed case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end) {
            result_type t = result_type (0);
            difference_type it1_size (it1_end - it1);
            difference_type it2_size (it2_end - it2);
            difference_type diff (0);
            if (it1_size > 0 && it2_size > 0)
                diff = it2.index1 () - it1.index ();
            if (diff != 0) {
                difference_type size = (std::min) (diff, it1_size);
                if (size > 0) {
                    it1 += size;
                    it1_size -= size;
                    diff -= size;
                }
                size = (std::min) (- diff, it2_size);
                if (size > 0) {
                    it2 += size;
                    it2_size -= size;
                    diff += size;
                }
            }
            difference_type size ((std::min) (it1_size, it2_size));
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
            return t;
        }
        // Sparse case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end,
                           sparse_bidirectional_iterator_tag, sparse_bidirectional_iterator_tag) {
            result_type t = result_type (0);
            if (it1 != it1_end && it2 != it2_end) {
                size_type it1_index = it1.index (), it2_index = it2.index1 ();
                for (;;) {
                    difference_type compare = it1_index - it2_index;
                    if (compare == 0) {
                        t += *it1 * *it2, ++ it1, ++ it2;
                        if (it1 != it1_end && it2 != it2_end) {
                            it1_index = it1.index ();
                            it2_index = it2.index1 ();
                        } else
                            break;
                    } else if (compare < 0) {
                        increment (it1, it1_end, - compare);
                        if (it1 != it1_end)
                            it1_index = it1.index ();
                        else
                            break;
                    } else if (compare > 0) {
                        increment (it2, it2_end, compare);
                        if (it2 != it2_end)
                            it2_index = it2.index1 ();
                        else
                            break;
                    }
                }
            }
            return t;
        }
        // Packed sparse case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &/* it1_end */, I2 it2, const I2 &it2_end,
                           packed_random_access_iterator_tag, sparse_bidirectional_iterator_tag) {
            result_type t = result_type (0);
            while (it2 != it2_end) {
                t += it1 () (it2.index1 ()) * *it2;
                ++ it2;
            }
            return t;
        }
        // Sparse packed case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &/* it2_end */,
                           sparse_bidirectional_iterator_tag, packed_random_access_iterator_tag) {
            result_type t = result_type (0);
            while (it1 != it1_end) {
                t += *it1 * it2 () (it1.index (), it2.index2 ());
                ++ it1;
            }
            return t;
        }
        // Another dispatcher
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end,
                           sparse_bidirectional_iterator_tag) {
            typedef typename I1::iterator_category iterator1_category;
            typedef typename I2::iterator_category iterator2_category;
            return apply (it1, it1_end, it2, it2_end, iterator1_category (), iterator2_category ());
        }
    };

    // Binary returning matrix
    template<class M1, class M2, class TV>
    struct matrix_matrix_binary_functor {
        typedef typename M1::size_type size_type;
        typedef typename M1::difference_type difference_type;
        typedef TV value_type;
        typedef TV result_type;
    };

    template<class M1, class M2, class TV>
    struct matrix_matrix_prod:
        public matrix_matrix_binary_functor<M1, M2, TV> {
        typedef typename matrix_matrix_binary_functor<M1, M2, TV>::size_type size_type;
        typedef typename matrix_matrix_binary_functor<M1, M2, TV>::difference_type difference_type;
        typedef typename matrix_matrix_binary_functor<M1, M2, TV>::value_type value_type;
        typedef typename matrix_matrix_binary_functor<M1, M2, TV>::result_type result_type;

        template<class C1, class C2>
        static BOOST_UBLAS_INLINE
        result_type apply (const matrix_container<C1> &c1,
                           const matrix_container<C2> &c2,
                           size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_SIMD
            using namespace raw;
            size_type size = BOOST_UBLAS_SAME (c1 ().size2 (), c2 ().sizc1 ());
            const typename M1::value_type *data1 = data_const (c1 ()) + i * stride1 (c1 ());
            const typename M2::value_type *data2 = data_const (c2 ()) + j * stride2 (c2 ());
            size_type s1 = stride2 (c1 ());
            size_type s2 = stride1 (c2 ());
            result_type t = result_type (0);
            if (s1 == 1 && s2 == 1) {
                for (size_type k = 0; k < size; ++ k)
                    t += data1 [k] * data2 [k];
            } else if (s2 == 1) {
                for (size_type k = 0, k1 = 0; k < size; ++ k, k1 += s1)
                    t += data1 [k1] * data2 [k];
            } else if (s1 == 1) {
                for (size_type k = 0, k2 = 0; k < size; ++ k, k2 += s2)
                    t += data1 [k] * data2 [k2];
            } else {
                for (size_type k = 0, k1 = 0, k2 = 0; k < size; ++ k, k1 += s1, k2 += s2)
                    t += data1 [k1] * data2 [k2];
            }
            return t;
#elif defined(BOOST_UBLAS_HAVE_BINDINGS)
            return boost::numeric::bindings::atlas::dot (c1 ().row (i), c2 ().column (j));
#else
            boost::ignore_unused(j);
            return apply (static_cast<const matrix_expression<C1> > (c1), static_cast<const matrix_expression<C2> > (c2, i));
#endif
        }
        template<class E1, class E2>
        static BOOST_UBLAS_INLINE
        result_type apply (const matrix_expression<E1> &e1,
                           const matrix_expression<E2> &e2,
                           size_type i, size_type j) {
            size_type size = BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ());
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type k = 0; k < size; ++ k)
                t += e1 () (i, k) * e2 () (k, j);
#else
            size_type k (0);
            DD (size, 4, r, (t += e1 () (i, k) * e2 () (k, j), ++ k));
#endif
            return t;
        }
        // Dense case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (difference_type size, I1 it1, I2 it2) {
            result_type t = result_type (0);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
#else
            DD (size, 4, r, (t += *it1 * *it2, ++ it1, ++ it2));
#endif
            return t;
        }
        // Packed case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end, packed_random_access_iterator_tag) {
            result_type t = result_type (0);
            difference_type it1_size (it1_end - it1);
            difference_type it2_size (it2_end - it2);
            difference_type diff (0);
            if (it1_size > 0 && it2_size > 0)
                diff = it2.index1 () - it1.index2 ();
            if (diff != 0) {
                difference_type size = (std::min) (diff, it1_size);
                if (size > 0) {
                    it1 += size;
                    it1_size -= size;
                    diff -= size;
                }
                size = (std::min) (- diff, it2_size);
                if (size > 0) {
                    it2 += size;
                    it2_size -= size;
                    diff += size;
                }
            }
            difference_type size ((std::min) (it1_size, it2_size));
            while (-- size >= 0)
                t += *it1 * *it2, ++ it1, ++ it2;
            return t;
        }
        // Sparse case
        template<class I1, class I2>
        static BOOST_UBLAS_INLINE
        result_type apply (I1 it1, const I1 &it1_end, I2 it2, const I2 &it2_end, sparse_bidirectional_iterator_tag) {
            result_type t = result_type (0);
            if (it1 != it1_end && it2 != it2_end) {
                size_type it1_index = it1.index2 (), it2_index = it2.index1 ();
                for (;;) {
                    difference_type compare = difference_type (it1_index - it2_index);
                    if (compare == 0) {
                        t += *it1 * *it2, ++ it1, ++ it2;
                        if (it1 != it1_end && it2 != it2_end) {
                            it1_index = it1.index2 ();
                            it2_index = it2.index1 ();
                        } else
                            break;
                    } else if (compare < 0) {
                        increment (it1, it1_end, - compare);
                        if (it1 != it1_end)
                            it1_index = it1.index2 ();
                        else
                            break;
                    } else if (compare > 0) {
                        increment (it2, it2_end, compare);
                        if (it2 != it2_end)
                            it2_index = it2.index1 ();
                        else
                            break;
                    }
                }
            }
            return t;
        }
    };

    // Unary returning scalar norm
    template<class M>
    struct matrix_scalar_real_unary_functor {
        typedef typename M::value_type value_type;
        typedef typename type_traits<value_type>::real_type real_type;
        typedef real_type result_type;
    };

    template<class M>
    struct matrix_norm_1:
        public matrix_scalar_real_unary_functor<M> {
        typedef typename matrix_scalar_real_unary_functor<M>::value_type value_type;
        typedef typename matrix_scalar_real_unary_functor<M>::real_type real_type;
        typedef typename matrix_scalar_real_unary_functor<M>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const matrix_expression<E> &e) {
            real_type t = real_type ();
            typedef typename E::size_type matrix_size_type;
            matrix_size_type size2 (e ().size2 ());
            for (matrix_size_type j = 0; j < size2; ++ j) {
                real_type u = real_type ();
                matrix_size_type size1 (e ().size1 ());
                for (matrix_size_type i = 0; i < size1; ++ i) {
                    real_type v (type_traits<value_type>::norm_1 (e () (i, j)));
                    u += v;
                }
                if (u > t)
                    t = u;
            }
            return t; 
        }
    };

    template<class M>
    struct matrix_norm_frobenius:
        public matrix_scalar_real_unary_functor<M> {
        typedef typename matrix_scalar_real_unary_functor<M>::value_type value_type;
        typedef typename matrix_scalar_real_unary_functor<M>::real_type real_type;
        typedef typename matrix_scalar_real_unary_functor<M>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const matrix_expression<E> &e) { 
            real_type t = real_type ();
            typedef typename E::size_type matrix_size_type;
            matrix_size_type size1 (e ().size1 ());
            for (matrix_size_type i = 0; i < size1; ++ i) {
                matrix_size_type size2 (e ().size2 ());
                for (matrix_size_type j = 0; j < size2; ++ j) {
                    real_type u (type_traits<value_type>::norm_2 (e () (i, j)));
                    t +=  u * u;
                }
            }
            return type_traits<real_type>::type_sqrt (t); 
        }
    };

    template<class M>
    struct matrix_norm_inf: 
        public matrix_scalar_real_unary_functor<M> {
        typedef typename matrix_scalar_real_unary_functor<M>::value_type value_type;
        typedef typename matrix_scalar_real_unary_functor<M>::real_type real_type;
        typedef typename matrix_scalar_real_unary_functor<M>::result_type result_type;

        template<class E>
        static BOOST_UBLAS_INLINE
        result_type apply (const matrix_expression<E> &e) {
            real_type t = real_type ();
            typedef typename E::size_type matrix_size_type;
            matrix_size_type size1 (e ().size1 ());
            for (matrix_size_type i = 0; i < size1; ++ i) {
                real_type u = real_type ();
                matrix_size_type size2 (e ().size2 ());
                for (matrix_size_type j = 0; j < size2; ++ j) {
                    real_type v (type_traits<value_type>::norm_inf (e () (i, j)));
                    u += v;
                }
                if (u > t) 
                    t = u;  
            }
            return t; 
        }
    };

    // forward declaration
    template <class Z, class D> struct basic_column_major;

    // This functor defines storage layout and it's properties
    // matrix (i,j) -> storage [i * size_i + j]
    template <class Z, class D>
    struct basic_row_major {
        typedef Z size_type;
        typedef D difference_type;
        typedef row_major_tag orientation_category;
        typedef basic_column_major<Z,D> transposed_layout;

        static
        BOOST_UBLAS_INLINE
        size_type storage_size (size_type size_i, size_type size_j) {
            // Guard against size_type overflow
            BOOST_UBLAS_CHECK (size_j == 0 || size_i <= (std::numeric_limits<size_type>::max) () / size_j, bad_size ());
            return size_i * size_j;
        }

        // Indexing conversion to storage element
        static
        BOOST_UBLAS_INLINE
        size_type element (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i < size_i, bad_index ());
            BOOST_UBLAS_CHECK (j < size_j, bad_index ());
            detail::ignore_unused_variable_warning(size_i);
            // Guard against size_type overflow
            BOOST_UBLAS_CHECK (i <= ((std::numeric_limits<size_type>::max) () - j) / size_j, bad_index ());
            return i * size_j + j;
        }
        static
        BOOST_UBLAS_INLINE
        size_type address (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i <= size_i, bad_index ());
            BOOST_UBLAS_CHECK (j <= size_j, bad_index ());
            // Guard against size_type overflow - address may be size_j past end of storage
            BOOST_UBLAS_CHECK (size_j == 0 || i <= ((std::numeric_limits<size_type>::max) () - j) / size_j, bad_index ());
            detail::ignore_unused_variable_warning(size_i);
            return i * size_j + j;
        }

        // Storage element to index conversion
        static
        BOOST_UBLAS_INLINE
        difference_type distance_i (difference_type k, size_type /* size_i */, size_type size_j) {
            return size_j != 0 ? k / size_j : 0;
        }
        static
        BOOST_UBLAS_INLINE
        difference_type distance_j (difference_type k, size_type /* size_i */, size_type /* size_j */) {
            return k;
        }
        static
        BOOST_UBLAS_INLINE
        size_type index_i (difference_type k, size_type /* size_i */, size_type size_j) {
            return size_j != 0 ? k / size_j : 0;
        }
        static
        BOOST_UBLAS_INLINE
        size_type index_j (difference_type k, size_type /* size_i */, size_type size_j) {
            return size_j != 0 ? k % size_j : 0;
        }
        static
        BOOST_UBLAS_INLINE
        bool fast_i () {
            return false;
        }
        static
        BOOST_UBLAS_INLINE
        bool fast_j () {
            return true;
        }

        // Iterating storage elements
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_i (I &it, size_type /* size_i */, size_type size_j) {
            it += size_j;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_i (I &it, difference_type n, size_type /* size_i */, size_type size_j) {
            it += n * size_j;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_i (I &it, size_type /* size_i */, size_type size_j) {
            it -= size_j;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_i (I &it, difference_type n, size_type /* size_i */, size_type size_j) {
            it -= n * size_j;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_j (I &it, size_type /* size_i */, size_type /* size_j */) {
            ++ it;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_j (I &it, difference_type n, size_type /* size_i */, size_type /* size_j */) {
            it += n;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_j (I &it, size_type /* size_i */, size_type /* size_j */) {
            -- it;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_j (I &it, difference_type n, size_type /* size_i */, size_type /* size_j */) {
            it -= n;
        }

        // Triangular access
        static
        BOOST_UBLAS_INLINE
        size_type triangular_size (size_type size_i, size_type size_j) {
            size_type size = (std::max) (size_i, size_j);
            // Guard against size_type overflow - simplified
            BOOST_UBLAS_CHECK (size == 0 || size / 2 < (std::numeric_limits<size_type>::max) () / size /* +1/2 */, bad_size ());
            return ((size + 1) * size) / 2;
        }
        static
        BOOST_UBLAS_INLINE
        size_type lower_element (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i < size_i, bad_index ());
            BOOST_UBLAS_CHECK (j < size_j, bad_index ());
            BOOST_UBLAS_CHECK (i >= j, bad_index ());
            detail::ignore_unused_variable_warning(size_i);
            detail::ignore_unused_variable_warning(size_j);
            // FIXME size_type overflow
            // sigma_i (i + 1) = (i + 1) * i / 2
            // i = 0 1 2 3, sigma = 0 1 3 6
            return ((i + 1) * i) / 2 + j;
        }
        static
        BOOST_UBLAS_INLINE
        size_type upper_element (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i < size_i, bad_index ());
            BOOST_UBLAS_CHECK (j < size_j, bad_index ());
            BOOST_UBLAS_CHECK (i <= j, bad_index ());
            // FIXME size_type overflow
            // sigma_i (size - i) = size * i - i * (i - 1) / 2
            // i = 0 1 2 3, sigma = 0 4 7 9
            return (i * (2 * (std::max) (size_i, size_j) - i + 1)) / 2 + j - i;
        }

        // Major and minor indices
        static
        BOOST_UBLAS_INLINE
        size_type index_M (size_type index1, size_type /* index2 */) {
            return index1;
        }
        static
        BOOST_UBLAS_INLINE
        size_type index_m (size_type /* index1 */, size_type index2) {
            return index2;
        }
        static
        BOOST_UBLAS_INLINE
        size_type size_M (size_type size_i, size_type /* size_j */) {
            return size_i;
        }
        static
        BOOST_UBLAS_INLINE
        size_type size_m (size_type /* size_i */, size_type size_j) {
            return size_j;
        }
    };

    // This functor defines storage layout and it's properties
    // matrix (i,j) -> storage [i + j * size_i]
    template <class Z, class D>
    struct basic_column_major {
        typedef Z size_type;
        typedef D difference_type;
        typedef column_major_tag orientation_category;
        typedef basic_row_major<Z,D> transposed_layout;

        static
        BOOST_UBLAS_INLINE
        size_type storage_size (size_type size_i, size_type size_j) {
            // Guard against size_type overflow
            BOOST_UBLAS_CHECK (size_i == 0 || size_j <= (std::numeric_limits<size_type>::max) () / size_i, bad_size ());
            return size_i * size_j;
        }

        // Indexing conversion to storage element
        static
        BOOST_UBLAS_INLINE
        size_type element (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i < size_i, bad_index ());
            BOOST_UBLAS_CHECK (j < size_j, bad_index ());
            detail::ignore_unused_variable_warning(size_j);
            // Guard against size_type overflow
            BOOST_UBLAS_CHECK (j <= ((std::numeric_limits<size_type>::max) () - i) / size_i, bad_index ());
            return i + j * size_i;
        }
        static
        BOOST_UBLAS_INLINE
        size_type address (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i <= size_i, bad_index ());
            BOOST_UBLAS_CHECK (j <= size_j, bad_index ());
            detail::ignore_unused_variable_warning(size_j);
            // Guard against size_type overflow - address may be size_i past end of storage
            BOOST_UBLAS_CHECK (size_i == 0 || j <= ((std::numeric_limits<size_type>::max) () - i) / size_i, bad_index ());
            return i + j * size_i;
        }

        // Storage element to index conversion
        static
        BOOST_UBLAS_INLINE
        difference_type distance_i (difference_type k, size_type /* size_i */, size_type /* size_j */) {
            return k;
        }
        static
        BOOST_UBLAS_INLINE
        difference_type distance_j (difference_type k, size_type size_i, size_type /* size_j */) {
            return size_i != 0 ? k / size_i : 0;
        }
        static
        BOOST_UBLAS_INLINE
        size_type index_i (difference_type k, size_type size_i, size_type /* size_j */) {
            return size_i != 0 ? k % size_i : 0;
        }
        static
        BOOST_UBLAS_INLINE
        size_type index_j (difference_type k, size_type size_i, size_type /* size_j */) {
            return size_i != 0 ? k / size_i : 0;
        }
        static
        BOOST_UBLAS_INLINE
        bool fast_i () {
            return true;
        }
        static
        BOOST_UBLAS_INLINE
        bool fast_j () {
            return false;
        }

        // Iterating
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_i (I &it, size_type /* size_i */, size_type /* size_j */) {
            ++ it;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_i (I &it, difference_type n, size_type /* size_i */, size_type /* size_j */) {
            it += n;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_i (I &it, size_type /* size_i */, size_type /* size_j */) {
            -- it;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_i (I &it, difference_type n, size_type /* size_i */, size_type /* size_j */) {
            it -= n;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_j (I &it, size_type size_i, size_type /* size_j */) {
            it += size_i;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void increment_j (I &it, difference_type n, size_type size_i, size_type /* size_j */) {
            it += n * size_i;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_j (I &it, size_type size_i, size_type /* size_j */) {
            it -= size_i;
        }
        template<class I>
        static
        BOOST_UBLAS_INLINE
        void decrement_j (I &it, difference_type n, size_type size_i, size_type /* size_j */) {
            it -= n* size_i;
        }

        // Triangular access
        static
        BOOST_UBLAS_INLINE
        size_type triangular_size (size_type size_i, size_type size_j) {
            size_type size = (std::max) (size_i, size_j);
            // Guard against size_type overflow - simplified
            BOOST_UBLAS_CHECK (size == 0 || size / 2 < (std::numeric_limits<size_type>::max) () / size /* +1/2 */, bad_size ());
            return ((size + 1) * size) / 2;
        }
        static
        BOOST_UBLAS_INLINE
        size_type lower_element (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i < size_i, bad_index ());
            BOOST_UBLAS_CHECK (j < size_j, bad_index ());
            BOOST_UBLAS_CHECK (i >= j, bad_index ());
            // FIXME size_type overflow
            // sigma_j (size - j) = size * j - j * (j - 1) / 2
            // j = 0 1 2 3, sigma = 0 4 7 9
            return i - j + (j * (2 * (std::max) (size_i, size_j) - j + 1)) / 2;
        }
        static
        BOOST_UBLAS_INLINE
        size_type upper_element (size_type i, size_type size_i, size_type j, size_type size_j) {
            BOOST_UBLAS_CHECK (i < size_i, bad_index ());
            BOOST_UBLAS_CHECK (j < size_j, bad_index ());
            BOOST_UBLAS_CHECK (i <= j, bad_index ());
            boost::ignore_unused(size_i, size_j);
            // FIXME size_type overflow
            // sigma_j (j + 1) = (j + 1) * j / 2
            // j = 0 1 2 3, sigma = 0 1 3 6
            return i + ((j + 1) * j) / 2;
        }

        // Major and minor indices
        static
        BOOST_UBLAS_INLINE
        size_type index_M (size_type /* index1 */, size_type index2) {
            return index2;
        }
        static
        BOOST_UBLAS_INLINE
        size_type index_m (size_type index1, size_type /* index2 */) {
            return index1;
        }
        static
        BOOST_UBLAS_INLINE
        size_type size_M (size_type /* size_i */, size_type size_j) {
            return size_j;
        }
        static
        BOOST_UBLAS_INLINE
        size_type size_m (size_type size_i, size_type /* size_j */) {
            return size_i;
        }
    };


    template <class Z>
    struct basic_full {
        typedef Z size_type;

        template<class L>
        static
        BOOST_UBLAS_INLINE
        size_type packed_size (L, size_type size_i, size_type size_j) {
            return L::storage_size (size_i, size_j);
        }

        static
        BOOST_UBLAS_INLINE
        bool zero (size_type /* i */, size_type /* j */) {
            return false;
        }
        static
        BOOST_UBLAS_INLINE
        bool one (size_type /* i */, size_type /* j */) {
            return false;
        }
        static
        BOOST_UBLAS_INLINE
        bool other (size_type /* i */, size_type /* j */) {
            return true;
        }
        // FIXME: this should not be used at all
        static
        BOOST_UBLAS_INLINE
        size_type restrict1 (size_type i, size_type /* j */) {
            return i;
        }
        static
        BOOST_UBLAS_INLINE
        size_type restrict2 (size_type /* i */, size_type j) {
            return j;
        }
        static
        BOOST_UBLAS_INLINE
        size_type mutable_restrict1 (size_type i, size_type /* j */) {
            return i;
        }
        static
        BOOST_UBLAS_INLINE
        size_type mutable_restrict2 (size_type /* i */, size_type j) {
            return j;
        }
    };

    namespace detail {
        template < class L >
        struct transposed_structure {
            typedef typename L::size_type size_type;

            template<class LAYOUT>
            static
            BOOST_UBLAS_INLINE
            size_type packed_size (LAYOUT l, size_type size_i, size_type size_j) {
                return L::packed_size(l, size_j, size_i);
            }

            static
            BOOST_UBLAS_INLINE
            bool zero (size_type i, size_type j) {
                return L::zero(j, i);
            }
            static
            BOOST_UBLAS_INLINE
            bool one (size_type i, size_type j) {
                return L::one(j, i);
            }
            static
            BOOST_UBLAS_INLINE
            bool other (size_type i, size_type j) {
                return L::other(j, i);
            }
            template<class LAYOUT>
            static
            BOOST_UBLAS_INLINE
            size_type element (LAYOUT /* l */, size_type i, size_type size_i, size_type j, size_type size_j) {
                return L::element(typename LAYOUT::transposed_layout(), j, size_j, i, size_i);
            }

            static
            BOOST_UBLAS_INLINE
            size_type restrict1 (size_type i, size_type j, size_type size1, size_type size2) {
                return L::restrict2(j, i, size2, size1);
            }
            static
            BOOST_UBLAS_INLINE
            size_type restrict2 (size_type i, size_type j, size_type size1, size_type size2) {
                return L::restrict1(j, i, size2, size1);
            }
            static
            BOOST_UBLAS_INLINE
            size_type mutable_restrict1 (size_type i, size_type j, size_type size1, size_type size2) {
                return L::mutable_restrict2(j, i, size2, size1);
            }
            static
            BOOST_UBLAS_INLINE
            size_type mutable_restrict2 (size_type i, size_type j, size_type size1, size_type size2) {
                return L::mutable_restrict1(j, i, size2, size1);
            }

            static
            BOOST_UBLAS_INLINE
            size_type global_restrict1 (size_type index1, size_type size1, size_type index2, size_type size2) {
                return L::global_restrict2(index2, size2, index1, size1);
            }
            static
            BOOST_UBLAS_INLINE
            size_type global_restrict2 (size_type index1, size_type size1, size_type index2, size_type size2) {
                return L::global_restrict1(index2, size2, index1, size1);
            }
            static
            BOOST_UBLAS_INLINE
            size_type global_mutable_restrict1 (size_type index1, size_type size1, size_type index2, size_type size2) {
                return L::global_mutable_restrict2(index2, size2, index1, size1);
            }
            static
            BOOST_UBLAS_INLINE
            size_type global_mutable_restrict2 (size_type index1, size_type size1, size_type index2, size_type size2) {
                return L::global_mutable_restrict1(index2, size2, index1, size1);
            }
        };
    }

    template <class Z>
    struct basic_lower {
        typedef Z size_type;
        typedef lower_tag triangular_type;

        template<class L>
        static
        BOOST_UBLAS_INLINE
        size_type packed_size (L, size_type size_i, size_type size_j) {
            return L::triangular_size (size_i, size_j);
        }

        static
        BOOST_UBLAS_INLINE
        bool zero (size_type i, size_type j) {
            return j > i;
        }
        static
        BOOST_UBLAS_INLINE
        bool one (size_type /* i */, size_type /* j */) {
            return false;
        }
        static
        BOOST_UBLAS_INLINE
        bool other (size_type i, size_type j) {
            return j <= i;
        }
        template<class L>
        static
        BOOST_UBLAS_INLINE
        size_type element (L, size_type i, size_type size_i, size_type j, size_type size_j) {
            return L::lower_element (i, size_i, j, size_j);
        }

        // return nearest valid index in column j
        static
        BOOST_UBLAS_INLINE
        size_type restrict1 (size_type i, size_type j, size_type size1, size_type /* size2 */) {
            return (std::max)(j, (std::min) (size1, i));
        }
        // return nearest valid index in row i
        static
        BOOST_UBLAS_INLINE
        size_type restrict2 (size_type i, size_type j, size_type /* size1 */, size_type /* size2 */) {
            return (std::max)(size_type(0), (std::min) (i+1, j));
        }
        // return nearest valid mutable index in column j
        static
        BOOST_UBLAS_INLINE
        size_type mutable_restrict1 (size_type i, size_type j, size_type size1, size_type /* size2 */) {
            return (std::max)(j, (std::min) (size1, i));
        }
        // return nearest valid mutable index in row i
        static
        BOOST_UBLAS_INLINE
        size_type mutable_restrict2 (size_type i, size_type j, size_type /* size1 */, size_type /* size2 */) {
            return (std::max)(size_type(0), (std::min) (i+1, j));
        }

        // return an index between the first and (1+last) filled row
        static
        BOOST_UBLAS_INLINE
        size_type global_restrict1 (size_type index1, size_type size1, size_type /* index2 */, size_type /* size2 */) {
            return (std::max)(size_type(0), (std::min)(size1, index1) );
        }
        // return an index between the first and (1+last) filled column
        static
        BOOST_UBLAS_INLINE
        size_type global_restrict2 (size_type /* index1 */, size_type /* size1 */, size_type index2, size_type size2) {
            return (std::max)(size_type(0), (std::min)(size2, index2) );
        }

        // return an index between the first and (1+last) filled mutable row
        static
        BOOST_UBLAS_INLINE
        size_type global_mutable_restrict1 (size_type index1, size_type size1, size_type /* index2 */, size_type /* size2 */) {
            return (std::max)(size_type(0), (std::min)(size1, index1) );
        }
        // return an index between the first and (1+last) filled mutable column
        static
        BOOST_UBLAS_INLINE
        size_type global_mutable_restrict2 (size_type /* index1 */, size_type /* size1 */, size_type index2, size_type size2) {
            return (std::max)(size_type(0), (std::min)(size2, index2) );
        }
    };

    // the first row only contains a single 1. Thus it is not stored.
    template <class Z>
    struct basic_unit_lower : public basic_lower<Z> {
        typedef Z size_type;
        typedef unit_lower_tag triangular_type;

        template<class L>
        static
        BOOST_UBLAS_INLINE
        size_type packed_size (L, size_type size_i, size_type size_j) {
            // Zero size strict triangles are bad at this point
            BOOST_UBLAS_CHECK (size_i != 0 && size_j != 0, bad_index ());
            return L::triangular_size (size_i - 1, size_j - 1);
        }

        static
        BOOST_UBLAS_INLINE
        bool one (size_type i, size_type j) {
            return j == i;
        }
        static
        BOOST_UBLAS_INLINE
        bool other (size_type i, size_type j) {
            return j < i;
        }
        template<class L>
        static
        BOOST_UBLAS_INLINE
        size_type element (L, size_type i, size_type size_i, size_type j, size_type size_j) {
            // Zero size strict triangles are bad at this point
            BOOST_UBLAS_CHECK (size_i != 0 && size_j != 0 && i != 0, bad_index ());
            return L::lower_element (i-1, size_i - 1, j, size_j - 1);
        }

        static
        BOOST_UBLAS_INLINE
        size_type mutable_restrict1 (size_type i, size_type j, size_type size1, size_type /* size2 */) {
            return (std::max)(j+1, (std::min) (size1, i));
        }
        static
        BOOST_UBLAS_INLINE
        size_type mutable_restrict2 (size_type i, size_type j, size_type /* size1 */, size_type /* size2 */) {
            return (std::max)(size_type(0), (std::min) (i, j));
        }

        // return an index between the first and (1+last) filled mutable row
        static
        BOOST_UBLAS_INLINE
        size_type global_mutable_restrict1 (size_type index1, size_type size1, size_type /* index2 */, size_type /* size2 */) {
            return (std::max)(size_type(1), (std::min)(size1, index1) );
        }
        // return an index between the first and (1+last) filled mutable column
        static
        BOOST_UBLAS_INLINE
        size_type global_mutable_restrict2 (size_type /* index1 */, size_type /* size1 */, size_type index2, size_type size2) {
            BOOST_UBLAS_CHECK( size2 >= 1 , external_logic() );
            return (std::max)(size_type(0), (std::min)(size2-1, index2) );
        }
    };

    // the first row only contains no element. Thus it is not stored.
    template <class Z>
    struct basic_strict_lower : public basic_unit_lower<Z> {
        typedef Z size_type;
        typedef strict_lower_tag triangular_type;

        template<class L>
        static
        BOOST_UBLAS_INLINE
        size_type packed_size (L, size_type size_i, size_type size_j) {
            // Zero size strict triangles are bad at this point
            BOOST_UBLAS_CHECK (size_i != 0 && size_j != 0, bad_index ());
            return L::triangular_size (size_i - 1, size_j - 1);
        }

        static
        BOOST_UBLAS_INLINE
        bool zero (size_type i, size_type j) {
            return j >= i;
        }
        static
        BOOST_UBLAS_INLINE
        bool one (size_type /*i*/, size_type /*j*/) {
            return false;
        }
        static
        BOOST_UBLAS_INLINE
        bool other (size_type i, size_type j) {
            return j < i;
        }
        template<class L>
        static
        BOOST_UBLAS_INLINE
        size_type element (L, size_type i, size_type size_i, size_type j, size_type size_j) {
            // Zero size strict triangles are bad at this point
            BOOST_UBLAS_CHECK (size_i != 0 && size_j != 0 && i != 0, bad_index ());
            return L::lower_element (i-1, size_i - 1, j, size_j - 1);
        }

        static
        BOOST_UBLAS_INLINE
        size_type restrict1 (size_type i, size_type j, size_type size1, size_type size2) {
            return basic_unit_lower<Z>::mutable_restrict1(i, j, size1, size2);
        }
        static
        BOOST_UBLAS_INLINE
        size_type restrict2 (size_type i, size_type j, size_type size1, size_type size2) {
            return basic_unit_lower<Z>::mutable_restrict2(i, j, size1, size2);
        }

        // return an index between the first and (1+last) filled row
        static
        BOOST_UBLAS_INLINE
        size_type global_restrict1 (size_type index1, size_type size1, size_type index2, size_type size2) {
            return basic_unit_lower<Z>::global_mutable_restrict1(index1, size1, index2, size2);
        }
        // return an index between the first and (1+last) filled column
        static
        BOOST_UBLAS_INLINE
        size_type global_restrict2 (size_type index1, size_type size1, size_type index2, size_type size2) {
            return basic_unit_lower<Z>::global_mutable_restrict2(index1, size1, index2, size2);
        }
    };


    template <class Z>
    struct basic_upper : public detail::transposed_structure<basic_lower<Z> >
    { 
        typedef upper_tag triangular_type;
    };

    template <class Z>
    struct basic_unit_upper : public detail::transposed_structure<basic_unit_lower<Z> >
    { 
        typedef unit_upper_tag triangular_type;
    };

    template <class Z>
    struct basic_strict_upper : public detail::transposed_structure<basic_strict_lower<Z> >
    { 
        typedef strict_upper_tag triangular_type;
    };


}}}

#endif

/* functional.hpp
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
*/
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
+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
*/
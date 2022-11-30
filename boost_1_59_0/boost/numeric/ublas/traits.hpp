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

#ifndef _BOOST_UBLAS_TRAITS_
#define _BOOST_UBLAS_TRAITS_

#include <iterator>
#include <complex>
#include <boost/config/no_tr1/cmath.hpp>

#include <boost/numeric/ublas/detail/config.hpp>
#include <boost/numeric/ublas/detail/iterator.hpp>
#include <boost/numeric/ublas/detail/returntype_deduction.hpp>
#ifdef BOOST_UBLAS_USE_INTERVAL
#include <boost/numeric/interval.hpp>
#endif

#include <boost/type_traits.hpp>
#include <complex>
#include <boost/typeof/typeof.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/typeof/typeof.hpp>


// anonymous namespace to avoid ADL issues
namespace {
  template<class T>
    typename boost::mpl::if_c<boost::is_integral<T>::value,
                              double,
                              T>::type
  boost_numeric_ublas_sqrt (const T& t) {
    using namespace std;
    // we'll find either std::sqrt or else another version via ADL:
    return sqrt (t);
  }

template<typename T>
inline typename boost::disable_if<
    boost::is_unsigned<T>, T >::type
    boost_numeric_ublas_abs (const T &t ) {
        using namespace std;
        // force a type conversion back to T for char and short types
        return static_cast<T>(abs( t ));
    }

template<typename T>
inline typename boost::enable_if<
    boost::is_unsigned<T>, T >::type
    boost_numeric_ublas_abs (const T &t ) {
        return t;
    }
}

namespace boost { namespace numeric { namespace ublas {


    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator+ (I in1, std::complex<R> const& in2 ) {
      return R (in1) + in2;
    }

    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator+ (std::complex<R> const& in1, I in2) {
      return in1 + R (in2);
    }

    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator- (I in1, std::complex<R> const& in2) {
      return R (in1) - in2;
    }

    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator- (std::complex<R> const& in1, I in2) {
      return in1 - R (in2);
    }

    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator* (I in1, std::complex<R> const& in2) {
      return R (in1) * in2;
    }

    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator* (std::complex<R> const& in1, I in2) {
      return in1 * R(in2);
    }

    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator/ (I in1, std::complex<R> const& in2) {
      return R(in1) / in2;
    }

    template<typename R, typename I>
    typename boost::enable_if<
      mpl::and_<
        boost::is_float<R>,
        boost::is_integral<I>
        >,
      std::complex<R> >::type inline operator/ (std::complex<R> const& in1, I in2) {
      return in1 / R (in2);
    }

    // uBLAS assumes a common return type for all binary arithmetic operators
    template<class X, class Y>
    struct promote_traits {
        typedef BOOST_TYPEOF_TPL(X() + Y()) promote_type;
    };



    // Type traits - generic numeric properties and functions
    template<class T>
    struct type_traits;
        
    // Define properties for a generic scalar type
    template<class T>
    struct scalar_traits {
        typedef scalar_traits<T> self_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;

        typedef T real_type;
        typedef real_type precision_type;       // we do not know what type has more precision then the real_type

        static const unsigned plus_complexity = 1;
        static const unsigned multiplies_complexity = 1;

        static
        BOOST_UBLAS_INLINE
        real_type real (const_reference t) {
                return t;
        }
        static
        BOOST_UBLAS_INLINE
        real_type imag (const_reference /*t*/) {
                return 0;
        }
        static
        BOOST_UBLAS_INLINE
        value_type conj (const_reference t) {
                return t;
        }

        static
        BOOST_UBLAS_INLINE
        real_type type_abs (const_reference t) {
            return boost_numeric_ublas_abs (t);
        }
        static
        BOOST_UBLAS_INLINE
        value_type type_sqrt (const_reference t) {
            // force a type conversion back to value_type for intgral types
            return value_type (boost_numeric_ublas_sqrt (t));
        }

        static
        BOOST_UBLAS_INLINE
        real_type norm_1 (const_reference t) {
            return self_type::type_abs (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_2 (const_reference t) {
            return self_type::type_abs (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_inf (const_reference t) {
            return self_type::type_abs (t);
        }

        static
        BOOST_UBLAS_INLINE
        bool equals (const_reference t1, const_reference t2) {
            return self_type::norm_inf (t1 - t2) < BOOST_UBLAS_TYPE_CHECK_EPSILON *
                   (std::max) ((std::max) (self_type::norm_inf (t1),
                                       self_type::norm_inf (t2)),
                             BOOST_UBLAS_TYPE_CHECK_MIN);
        }
    };

    // Define default type traits, assume T is a scalar type
    template<class T>
    struct type_traits : scalar_traits <T> {
        typedef type_traits<T> self_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;

        typedef T real_type;
        typedef real_type precision_type;
        static const unsigned multiplies_complexity = 1;

    };

    // Define real type traits
    template<>
    struct type_traits<float> : scalar_traits<float> {
        typedef type_traits<float> self_type;
        typedef float value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef value_type real_type;
        typedef double precision_type;
    };
    template<>
    struct type_traits<double> : scalar_traits<double> {
        typedef type_traits<double> self_type;
        typedef double value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef value_type real_type;
        typedef long double precision_type;
    };
    template<>
    struct type_traits<long double>  : scalar_traits<long double> {
        typedef type_traits<long double> self_type;
        typedef long double value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef value_type real_type;
        typedef value_type precision_type;
    };

    // Define properties for a generic complex type
    template<class T>
    struct complex_traits {
        typedef complex_traits<T> self_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;

        typedef typename T::value_type real_type;
        typedef real_type precision_type;       // we do not know what type has more precision then the real_type

        static const unsigned plus_complexity = 2;
        static const unsigned multiplies_complexity = 6;

        static
        BOOST_UBLAS_INLINE
        real_type real (const_reference t) {
                return std::real (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type imag (const_reference t) {
                return std::imag (t);
        }
        static
        BOOST_UBLAS_INLINE
        value_type conj (const_reference t) {
                return std::conj (t);
        }

        static
        BOOST_UBLAS_INLINE
        real_type type_abs (const_reference t) {
                return abs (t);
        }
        static
        BOOST_UBLAS_INLINE
        value_type type_sqrt (const_reference t) {
                return sqrt (t);
        }

        static
        BOOST_UBLAS_INLINE
        real_type norm_1 (const_reference t) {
            return self_type::type_abs (t);
            // original computation has been replaced because a complex number should behave like a scalar type
            // return type_traits<real_type>::type_abs (self_type::real (t)) +
            //       type_traits<real_type>::type_abs (self_type::imag (t));
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_2 (const_reference t) {
            return self_type::type_abs (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_inf (const_reference t) {
            return self_type::type_abs (t);
            // original computation has been replaced because a complex number should behave like a scalar type
            // return (std::max) (type_traits<real_type>::type_abs (self_type::real (t)),
            //                 type_traits<real_type>::type_abs (self_type::imag (t)));
        }

        static
        BOOST_UBLAS_INLINE
        bool equals (const_reference t1, const_reference t2) {
            return self_type::norm_inf (t1 - t2) < BOOST_UBLAS_TYPE_CHECK_EPSILON *
                   (std::max) ((std::max) (self_type::norm_inf (t1),
                                       self_type::norm_inf (t2)),
                             BOOST_UBLAS_TYPE_CHECK_MIN);
        }
    };
    
    // Define complex type traits
    template<>
    struct type_traits<std::complex<float> > : complex_traits<std::complex<float> >{
        typedef type_traits<std::complex<float> > self_type;
        typedef std::complex<float> value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef float real_type;
        typedef std::complex<double> precision_type;

    };
    template<>
    struct type_traits<std::complex<double> > : complex_traits<std::complex<double> >{
        typedef type_traits<std::complex<double> > self_type;
        typedef std::complex<double> value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef double real_type;
        typedef std::complex<long double> precision_type;
    };
    template<>
    struct type_traits<std::complex<long double> > : complex_traits<std::complex<long double> > {
        typedef type_traits<std::complex<long double> > self_type;
        typedef std::complex<long double> value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef long double real_type;
        typedef value_type precision_type;
    };

#ifdef BOOST_UBLAS_USE_INTERVAL
    // Define scalar interval type traits
    template<>
    struct type_traits<boost::numeric::interval<float> > : scalar_traits<boost::numeric::interval<float> > {
        typedef type_traits<boost::numeric::interval<float> > self_type;
        typedef boost::numeric::interval<float> value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef value_type real_type;
        typedef boost::numeric::interval<double> precision_type;

    };
    template<>
    struct type_traits<boost::numeric::interval<double> > : scalar_traits<boost::numeric::interval<double> > {
        typedef type_traits<boost::numeric::interval<double> > self_type;
        typedef boost::numeric::interval<double> value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef value_type real_type;
        typedef boost::numeric::interval<long double> precision_type;
    };
    template<>
    struct type_traits<boost::numeric::interval<long double> > : scalar_traits<boost::numeric::interval<long double> > {
        typedef type_traits<boost::numeric::interval<long double> > self_type;
        typedef boost::numeric::interval<long double> value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef value_type real_type;
        typedef value_type precision_type;
    };
#endif


    // Storage tags -- hierarchical definition of storage characteristics

    struct unknown_storage_tag {};
    struct sparse_proxy_tag: public unknown_storage_tag {};
    struct sparse_tag: public sparse_proxy_tag {};
    struct packed_proxy_tag: public sparse_proxy_tag {};
    struct packed_tag: public packed_proxy_tag {};
    struct dense_proxy_tag: public packed_proxy_tag {};
    struct dense_tag: public dense_proxy_tag {};

    template<class S1, class S2>
    struct storage_restrict_traits {
        typedef S1 storage_category;
    };

    template<>
    struct storage_restrict_traits<sparse_tag, dense_proxy_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct storage_restrict_traits<sparse_tag, packed_proxy_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct storage_restrict_traits<sparse_tag, sparse_proxy_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct storage_restrict_traits<packed_tag, dense_proxy_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<>
    struct storage_restrict_traits<packed_tag, packed_proxy_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<>
    struct storage_restrict_traits<packed_tag, sparse_proxy_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct storage_restrict_traits<packed_proxy_tag, sparse_proxy_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct storage_restrict_traits<dense_tag, dense_proxy_tag> {
        typedef dense_proxy_tag storage_category;
    };
    template<>
    struct storage_restrict_traits<dense_tag, packed_proxy_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<>
    struct storage_restrict_traits<dense_tag, sparse_proxy_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct storage_restrict_traits<dense_proxy_tag, packed_proxy_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<>
    struct storage_restrict_traits<dense_proxy_tag, sparse_proxy_tag> {
        typedef sparse_proxy_tag storage_category;
    };


    // Iterator tags -- hierarchical definition of storage characteristics

    struct sparse_bidirectional_iterator_tag : public std::bidirectional_iterator_tag {};
    struct packed_random_access_iterator_tag : public std::random_access_iterator_tag {};
    struct dense_random_access_iterator_tag : public packed_random_access_iterator_tag {};

    // Thanks to Kresimir Fresl for convincing Comeau with iterator_base_traits ;-)
    template<class IC>
    struct iterator_base_traits {};

    template<>
    struct iterator_base_traits<std::forward_iterator_tag> {
        template<class I, class T>
        struct iterator_base {
            typedef forward_iterator_base<std::forward_iterator_tag, I, T> type;
        };
    };

    template<>
    struct iterator_base_traits<std::bidirectional_iterator_tag> {
        template<class I, class T>
        struct iterator_base {
            typedef bidirectional_iterator_base<std::bidirectional_iterator_tag, I, T> type;
        };
    };
    template<>
    struct iterator_base_traits<sparse_bidirectional_iterator_tag> {
        template<class I, class T>
        struct iterator_base {
            typedef bidirectional_iterator_base<sparse_bidirectional_iterator_tag, I, T> type;
        };
    };

    template<>
    struct iterator_base_traits<std::random_access_iterator_tag> {
        template<class I, class T>
        struct iterator_base {
            typedef random_access_iterator_base<std::random_access_iterator_tag, I, T> type;
        };
    };
    template<>
    struct iterator_base_traits<packed_random_access_iterator_tag> {
        template<class I, class T>
        struct iterator_base {
            typedef random_access_iterator_base<packed_random_access_iterator_tag, I, T> type;
        };
    };
    template<>
    struct iterator_base_traits<dense_random_access_iterator_tag> {
        template<class I, class T>
        struct iterator_base {
            typedef random_access_iterator_base<dense_random_access_iterator_tag, I, T> type;
        };
    };

    template<class I1, class I2>
    struct iterator_restrict_traits {
        typedef I1 iterator_category;
    };

    template<>
    struct iterator_restrict_traits<packed_random_access_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_bidirectional_iterator_tag iterator_category;
    };
    template<>
    struct iterator_restrict_traits<sparse_bidirectional_iterator_tag, packed_random_access_iterator_tag> {
        typedef sparse_bidirectional_iterator_tag iterator_category;
    };

    template<>
    struct iterator_restrict_traits<dense_random_access_iterator_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_bidirectional_iterator_tag iterator_category;
    };
    template<>
    struct iterator_restrict_traits<sparse_bidirectional_iterator_tag, dense_random_access_iterator_tag> {
        typedef sparse_bidirectional_iterator_tag iterator_category;
    };

    template<>
    struct iterator_restrict_traits<dense_random_access_iterator_tag, packed_random_access_iterator_tag> {
        typedef packed_random_access_iterator_tag iterator_category;
    };
    template<>
    struct iterator_restrict_traits<packed_random_access_iterator_tag, dense_random_access_iterator_tag> {
        typedef packed_random_access_iterator_tag iterator_category;
    };

    template<class I>
    BOOST_UBLAS_INLINE
    void increment (I &it, const I &it_end, typename I::difference_type compare, packed_random_access_iterator_tag) {
        it += (std::min) (compare, it_end - it);
    }
    template<class I>
    BOOST_UBLAS_INLINE
    void increment (I &it, const I &/* it_end */, typename I::difference_type /* compare */, sparse_bidirectional_iterator_tag) {
        ++ it;
    }
    template<class I>
    BOOST_UBLAS_INLINE
    void increment (I &it, const I &it_end, typename I::difference_type compare) {
        increment (it, it_end, compare, typename I::iterator_category ());
    }

    template<class I>
    BOOST_UBLAS_INLINE
    void increment (I &it, const I &it_end) {
#if BOOST_UBLAS_TYPE_CHECK
        I cit (it);
        while (cit != it_end) {
            BOOST_UBLAS_CHECK (*cit == typename I::value_type/*zero*/(), internal_logic ());
            ++ cit;
        }
#endif
        it = it_end;
    }

    namespace detail {

        // specialisation which define whether a type has a trivial constructor
        // or not. This is used by array types.
        template<typename T>
        struct has_trivial_constructor : public boost::has_trivial_constructor<T> {};

        template<typename T>
        struct has_trivial_destructor : public boost::has_trivial_destructor<T> {};

        template<typename FLT>
        struct has_trivial_constructor<std::complex<FLT> > : public has_trivial_constructor<FLT> {};
        
        template<typename FLT>
        struct has_trivial_destructor<std::complex<FLT> > : public has_trivial_destructor<FLT> {};

    }


    /**  \brief Traits class to extract type information from a constant matrix or vector CONTAINER.
     *
     */
    template < class E >
    struct container_view_traits {
        /// type of indices
        typedef typename E::size_type             size_type;
        /// type of differences of indices
        typedef typename E::difference_type       difference_type;

        /// storage category: \c unknown_storage_tag, \c dense_tag, \c packed_tag, ...
        typedef typename E::storage_category      storage_category;

        /// type of elements
        typedef typename E::value_type            value_type;
        /// const reference to an element
        typedef typename E::const_reference       const_reference;
  
        /// type used in expressions to mark a reference to this class (usually a const container_reference<const E> or the class itself)
        typedef typename E::const_closure_type    const_closure_type;
    };

    /**  \brief Traits class to extract additional type information from a mutable matrix or vector CONTAINER.
     *
     */
    template < class E >
    struct mutable_container_traits {
        /// reference to an element
        typedef typename E::reference             reference;
  
        /// type used in expressions to mark a reference to this class (usually a container_reference<E> or the class itself)
        typedef typename E::closure_type          closure_type;
    };

    /**  \brief Traits class to extract type information from a matrix or vector CONTAINER.
     *
     */
    template < class E >
    struct container_traits 
        : container_view_traits<E>, mutable_container_traits<E> {

    };


    /**  \brief Traits class to extract type information from a constant MATRIX.
     *
     */
    template < class MATRIX >
    struct matrix_view_traits : container_view_traits <MATRIX> {

        /// orientation of the matrix, either \c row_major_tag, \c column_major_tag or \c unknown_orientation_tag
        typedef typename MATRIX::orientation_category  orientation_category;
  
        /// row iterator for the matrix
        typedef typename MATRIX::const_iterator1  const_iterator1;

        /// column iterator for the matrix
        typedef typename MATRIX::const_iterator2  const_iterator2;
    };

    /**  \brief Traits class to extract additional type information from a mutable MATRIX.
     *
     */
    template < class MATRIX >
    struct mutable_matrix_traits 
        : mutable_container_traits <MATRIX> {

        /// row iterator for the matrix
        typedef typename MATRIX::iterator1  iterator1;

        /// column iterator for the matrix
        typedef typename MATRIX::iterator2  iterator2;
    };


    /**  \brief Traits class to extract type information from a MATRIX.
     *
     */
    template < class MATRIX >
    struct matrix_traits 
        : matrix_view_traits <MATRIX>, mutable_matrix_traits <MATRIX> {
    };

    /**  \brief Traits class to extract type information from a VECTOR.
     *
     */
    template < class VECTOR >
    struct vector_view_traits : container_view_traits <VECTOR> {

        /// iterator for the VECTOR
        typedef typename VECTOR::const_iterator  const_iterator;

        /// iterator pointing to the first element
        static
        const_iterator begin(const VECTOR & v) {
            return v.begin();
        }
        /// iterator pointing behind the last element
        static
        const_iterator end(const VECTOR & v) {
            return v.end();
        }

    };

    /**  \brief Traits class to extract type information from a VECTOR.
     *
     */
    template < class VECTOR >
    struct mutable_vector_traits : mutable_container_traits <VECTOR> {
        /// iterator for the VECTOR
        typedef typename VECTOR::iterator  iterator;

        /// iterator pointing to the first element
        static
        iterator begin(VECTOR & v) {
            return v.begin();
        }

        /// iterator pointing behind the last element
        static
        iterator end(VECTOR & v) {
            return v.end();
        }
    };

    /**  \brief Traits class to extract type information from a VECTOR.
     *
     */
    template < class VECTOR >
    struct vector_traits 
        : vector_view_traits <VECTOR>, mutable_vector_traits <VECTOR> {
    };


    // Note: specializations for T[N] and T[M][N] have been moved to traits/c_array.hpp

}}}

#endif

/* traits.hpp
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
*/
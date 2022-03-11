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
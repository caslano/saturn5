#ifndef BOOST_QVM_VEC_OPERATIONS_HPP_INCLUDED
#define BOOST_QVM_VEC_OPERATIONS_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.
// Copyright 2019 agate-pris

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/detail/vec_assign.hpp>
#include <boost/qvm/vec_operations2.hpp>
#include <boost/qvm/vec_operations3.hpp>
#include <boost/qvm/vec_operations4.hpp>
#include <boost/qvm/assert.hpp>
#include <boost/qvm/scalar_traits.hpp>
#include <string>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    BOOST_QVM_INLINE_CRITICAL
    void const *
    get_valid_ptr_vec_operations()
        {
        static int const obj=0;
        return &obj;
        }
    }

////////////////////////////////////////////////

namespace
qvm_to_string_detail
    {
    template <class T>
    std::string to_string( T const & x );
    }

namespace
qvm_detail
    {
    template <int D>
    struct
    to_string_v_defined
        {
        static bool const value=false;
        };

    template <int I,int DimMinusOne>
    struct
    to_string_vector_elements
        {
        template <class A>
        static
        std::string
        f( A const & a )
            {
            using namespace qvm_to_string_detail;
            return to_string(vec_traits<A>::template read_element<I>(a))+','+to_string_vector_elements<I+1,DimMinusOne>::f(a);
            }
        };

    template <int DimMinusOne>
    struct
    to_string_vector_elements<DimMinusOne,DimMinusOne>
        {
        template <class A>
        static
        std::string
        f( A const & a )
            {
            using namespace qvm_to_string_detail;
            return to_string(vec_traits<A>::template read_element<DimMinusOne>(a));
            }
        };
    }

template <class A>
inline
typename enable_if_c<
    is_vec<A>::value  &&
    !qvm_detail::to_string_v_defined<vec_traits<A>::dim>::value,
    std::string>::type
to_string( A const & a )
    {
    return '('+qvm_detail::to_string_vector_elements<0,vec_traits<A>::dim-1>::f(a)+')';
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    convert_to_v_defined
        {
        static bool const value=false;
        };
    }

template <class R,class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_vec<R>::value && is_vec<A>::value &&
    vec_traits<R>::dim==vec_traits<A>::dim &&
    !qvm_detail::convert_to_v_defined<vec_traits<R>::dim>::value,
    R>::type
convert_to( A const & a )
    {
    R r; assign(r,a);
    return r;
    }

////////////////////////////////////////////////

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==3 && vec_traits<B>::dim==3,
    deduce_vec2<A,B,3> >::type
cross( A const & a, B const & b )
    {
    typedef typename deduce_vec2<A,B,3>::type R;
    R r;
    vec_traits<R>::template write_element<0>(r)=
        vec_traits<A>::template read_element<1>(a)*vec_traits<B>::template read_element<2>(b)-
        vec_traits<A>::template read_element<2>(a)*vec_traits<B>::template read_element<1>(b);
    vec_traits<R>::template write_element<1>(r)=
        vec_traits<A>::template read_element<2>(a)*vec_traits<B>::template read_element<0>(b)-
        vec_traits<A>::template read_element<0>(a)*vec_traits<B>::template read_element<2>(b);
    vec_traits<R>::template write_element<2>(r)=
        vec_traits<A>::template read_element<0>(a)*vec_traits<B>::template read_element<1>(b)-
        vec_traits<A>::template read_element<1>(a)*vec_traits<B>::template read_element<0>(b);
    return r;
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==2 && vec_traits<B>::dim==2,
    deduce_scalar<typename vec_traits<A>::scalar_type,typename vec_traits<B>::scalar_type> >::type
cross( A const & a, B const & b )
    {
    typedef typename deduce_scalar<typename vec_traits<A>::scalar_type,typename vec_traits<B>::scalar_type>::type R;
    R const r =
        vec_traits<A>::template read_element<0>(a)*vec_traits<B>::template read_element<1>(b)-
        vec_traits<A>::template read_element<1>(a)*vec_traits<B>::template read_element<0>(b);
    return r;
    }

////////////////////////////////////////////////

template <class A,class B,class Cmp>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim,
    bool>::type
cmp( A const & a, B const & b, Cmp f )
    {
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        if( !f(
            vec_traits<A>::read_element_idx(i,a),
            vec_traits<B>::read_element_idx(i,b)) )
            return false;
    return true;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class T,int Dim>
    class
    zero_vec_
        {
        zero_vec_( zero_vec_ const & );
        zero_vec_ & operator=( zero_vec_ const & );
        ~zero_vec_();

        public:

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }
        };
    }

template <class V>
struct vec_traits;

template <class T,int Dim>
struct
vec_traits< qvm_detail::zero_vec_<T,Dim> >
    {
    typedef qvm_detail::zero_vec_<T,Dim> this_vector;
    typedef T scalar_type;
    static int const dim=Dim;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<Dim);
        return scalar_traits<scalar_type>::value(0);
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<Dim);
        return scalar_traits<scalar_type>::value(0);
        }
    };

template <class T,int Dim,int D>
struct
deduce_vec<qvm_detail::zero_vec_<T,Dim>,D>
    {
    typedef vec<T,D> type;
    };

template <class T,int Dim>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::zero_vec_<T,Dim> const &
zero_vec()
    {
    return *(qvm_detail::zero_vec_<T,Dim> const *)qvm_detail::get_valid_ptr_vec_operations();
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value,
    void>::type
set_zero( A & a )
    {
    assign(a,zero_vec<typename vec_traits<A>::scalar_type,vec_traits<A>::dim>());
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class OriginalType,class Scalar>
    class
    vector_scalar_cast_
        {
        vector_scalar_cast_( vector_scalar_cast_ const & );
        vector_scalar_cast_ & operator=( vector_scalar_cast_ const & );
        ~vector_scalar_cast_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        vector_scalar_cast_ &
        operator=( T const & x )
            {
            assign(*this,x);
            return *this;
            }

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }
        };

    template <bool> struct scalar_cast_vector_filter { };
    template <> struct scalar_cast_vector_filter<true> { typedef int type; };
    }

template <class OriginalType,class Scalar>
struct
vec_traits< qvm_detail::vector_scalar_cast_<OriginalType,Scalar> >
    {
    typedef Scalar scalar_type;
    typedef qvm_detail::vector_scalar_cast_<OriginalType,Scalar> this_vector;
    static int const dim=vec_traits<OriginalType>::dim;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return scalar_type(vec_traits<OriginalType>::template read_element<I>(reinterpret_cast<OriginalType const &>(x)));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return scalar_type(vec_traits<OriginalType>::read_element_idx(i,reinterpret_cast<OriginalType const &>(x)));
        }
    };

template <class OriginalType,class Scalar,int D>
struct
deduce_vec<qvm_detail::vector_scalar_cast_<OriginalType,Scalar>,D>
    {
    typedef vec<Scalar,D> type;
    };

template <class Scalar,class T>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::vector_scalar_cast_<T,Scalar> const &
scalar_cast( T const & x, typename qvm_detail::scalar_cast_vector_filter<is_vec<T>::value>::type=0 )
    {
    return reinterpret_cast<qvm_detail::vector_scalar_cast_<T,Scalar> const &>(x);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    div_eq_vs_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value && is_scalar<B>::value &&
    !qvm_detail::div_eq_vs_defined<vec_traits<A>::dim>::value,
    A &>::type
operator/=( A & a, B b )
    {
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<A>::write_element_idx(i,a)/=b;
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    div_vs_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_scalar<B>::value &&
    !qvm_detail::div_vs_defined<vec_traits<A>::dim>::value,
    deduce_vec2<A,B,vec_traits<A>::dim> >::type
operator/( A const & a, B b )
    {
    typedef typename deduce_vec2<A,B,vec_traits<A>::dim>::type R;
    R r;
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<R>::write_element_idx(i,r)=vec_traits<A>::read_element_idx(i,a)/b;
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    dot_vv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim &&
    !qvm_detail::dot_vv_defined<vec_traits<A>::dim>::value,
    deduce_scalar<typename vec_traits<A>::scalar_type,typename vec_traits<B>::scalar_type> >::type
dot( A const & a, B const & b )
    {
    typedef typename deduce_scalar<typename vec_traits<A>::scalar_type,typename vec_traits<B>::scalar_type>::type T;
    T m(scalar_traits<T>::value(0));
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        m+=vec_traits<A>::read_element_idx(i,a)*vec_traits<B>::read_element_idx(i,b);
    return m;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    eq_vv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim &&
    !qvm_detail::eq_vv_defined<vec_traits<A>::dim>::value,
    bool>::type
operator==( A const & a, B const & b )
    {
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        if( vec_traits<A>::read_element_idx(i,a)!=vec_traits<B>::read_element_idx(i,b) )
            return false;
    return true;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    mag_sqr_v_defined
        {
        static bool const value=false;
        };
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value &&
    !qvm_detail::mag_sqr_v_defined<vec_traits<A>::dim>::value,
    typename vec_traits<A>::scalar_type>::type
mag_sqr( A const & a )
    {
    typedef typename vec_traits<A>::scalar_type T;
    T m(scalar_traits<T>::value(0));
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        {
        T x=vec_traits<A>::read_element_idx(i,a);
        m+=x*x;
        }
    return m;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    mag_v_defined
        {
        static bool const value=false;
        };
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value &&
    !qvm_detail::mag_v_defined<vec_traits<A>::dim>::value,
    typename vec_traits<A>::scalar_type>::type
mag( A const & a )
    {
    typedef typename vec_traits<A>::scalar_type T;
    T m(scalar_traits<T>::value(0));
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        {
        T x=vec_traits<A>::read_element_idx(i,a);
        m+=x*x;
        }
    return sqrt(m);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    minus_eq_vv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim &&
    !qvm_detail::minus_eq_vv_defined<vec_traits<A>::dim>::value,
    A &>::type
operator-=( A & a, B const & b )
    {
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<A>::write_element_idx(i,a)-=vec_traits<B>::read_element_idx(i,b);
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    minus_v_defined
        {
        static bool const value=false;
        };
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value &&
    !qvm_detail::minus_v_defined<vec_traits<A>::dim>::value,
    deduce_vec<A> >::type
operator-( A const & a )
    {
    typedef typename deduce_vec<A>::type R;
    R r;
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<R>::write_element_idx(i,r)=-vec_traits<A>::read_element_idx(i,a);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    minus_vv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim &&
    !qvm_detail::minus_vv_defined<vec_traits<A>::dim>::value,
    deduce_vec2<A,B,vec_traits<A>::dim> >::type
operator-( A const & a, B const & b )
    {
    typedef typename deduce_vec2<A,B,vec_traits<A>::dim>::type R;
    R r;
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<R>::write_element_idx(i,r)=vec_traits<A>::read_element_idx(i,a)-vec_traits<B>::read_element_idx(i,b);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    mul_eq_vs_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value && is_scalar<B>::value &&
    !qvm_detail::mul_eq_vs_defined<vec_traits<A>::dim>::value,
    A &>::type
operator*=( A & a, B b )
    {
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<A>::write_element_idx(i,a)*=b;
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    mul_vs_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_scalar<B>::value &&
    !qvm_detail::mul_vs_defined<vec_traits<A>::dim>::value,
    deduce_vec2<A,B,vec_traits<A>::dim> >::type
operator*( A const & a, B b )
    {
    typedef typename deduce_vec2<A,B,vec_traits<A>::dim>::type R;
    R r;
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<R>::write_element_idx(i,r)=vec_traits<A>::read_element_idx(i,a)*b;
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    mul_sv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_scalar<A>::value && is_vec<B>::value &&
    !qvm_detail::mul_sv_defined<vec_traits<B>::dim>::value,
    deduce_vec2<A,B,vec_traits<B>::dim> >::type
operator*( A a, B const & b )
    {
    typedef typename deduce_vec2<A,B,vec_traits<B>::dim>::type R;
    R r;
    for( int i=0; i!=vec_traits<B>::dim; ++i )
        vec_traits<R>::write_element_idx(i,r)=a*vec_traits<B>::read_element_idx(i,b);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    neq_vv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim &&
    !qvm_detail::neq_vv_defined<vec_traits<A>::dim>::value,
    bool>::type
operator!=( A const & a, B const & b )
    {
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        if( vec_traits<A>::read_element_idx(i,a)!=vec_traits<B>::read_element_idx(i,b) )
            return true;
    return false;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    normalize_v_defined
        {
        static bool const value=false;
        };
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value &&
    !qvm_detail::normalize_v_defined<vec_traits<A>::dim>::value,
    deduce_vec<A> >::type
normalized( A const & a )
    {
    typedef typename vec_traits<A>::scalar_type T;
    T m(scalar_traits<T>::value(0));
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        {
        T x=vec_traits<A>::read_element_idx(i,a);
        m+=x*x;
        }
    if( m==scalar_traits<T>::value(0) )
        BOOST_QVM_THROW_EXCEPTION(zero_magnitude_error());
    T rm=scalar_traits<T>::value(1)/sqrt(m);
    typedef typename deduce_vec<A>::type R;
    R r;
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<R>::write_element_idx(i,r)=vec_traits<A>::read_element_idx(i,a)*rm;
    return r;
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value &&
    !qvm_detail::normalize_v_defined<vec_traits<A>::dim>::value,
    void>::type
normalize( A & a )
    {
    typedef typename vec_traits<A>::scalar_type T;
    T m(scalar_traits<T>::value(0));
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        {
        T x=vec_traits<A>::read_element_idx(i,a);
        m+=x*x;
        }
    if( m==scalar_traits<T>::value(0) )
        BOOST_QVM_THROW_EXCEPTION(zero_magnitude_error());
    T rm=scalar_traits<T>::value(1)/sqrt(m);
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<A>::write_element_idx(i,a)*=rm;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    plus_eq_vv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim &&
    !qvm_detail::plus_eq_vv_defined<vec_traits<A>::dim>::value,
    A &>::type
operator+=( A & a, B const & b )
    {
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<A>::write_element_idx(i,a)+=vec_traits<B>::read_element_idx(i,b);
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    plus_vv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_vec<B>::value &&
    vec_traits<A>::dim==vec_traits<B>::dim &&
    !qvm_detail::plus_vv_defined<vec_traits<A>::dim>::value,
    deduce_vec2<A,B,vec_traits<A>::dim> >::type
operator+( A const & a, B const & b )
    {
    typedef typename deduce_vec2<A,B,vec_traits<A>::dim>::type R;
    R r;
    for( int i=0; i!=vec_traits<A>::dim; ++i )
        vec_traits<R>::write_element_idx(i,r)=vec_traits<A>::read_element_idx(i,a)+vec_traits<B>::read_element_idx(i,b);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class T>
    class
    vref_
        {
        vref_( vref_ const & );
        vref_ & operator=( vref_ const & );
        ~vref_();

        public:

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        vref_ &
        operator=( R const & x )
            {
            assign(*this,x);
            return *this;
            }

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }
        };
    }

template <class V>
struct
vec_traits< qvm_detail::vref_<V> >
    {
    typedef typename vec_traits<V>::scalar_type scalar_type;
    typedef qvm_detail::vref_<V> this_vector;
    static int const dim=vec_traits<V>::dim;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return vec_traits<V>::template read_element<I>(reinterpret_cast<V const &>(x));
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return vec_traits<V>::template write_element<I>(reinterpret_cast<V &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return vec_traits<V>::read_element_idx(i,reinterpret_cast<V const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int i, this_vector & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return vec_traits<V>::write_element_idx(i,reinterpret_cast<V &>(x));
        }
    };

template <class V,int D>
struct
deduce_vec<qvm_detail::vref_<V>,D>
    {
    typedef vec<typename vec_traits<V>::scalar_type,D> type;
    };

template <class V>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_vec<V>::value,
    qvm_detail::vref_<V> const &>::type
vref( V const & a )
    {
    return reinterpret_cast<qvm_detail::vref_<V> const &>(a);
    }

template <class V>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_vec<V>::value,
    qvm_detail::vref_<V> &>::type
vref( V & a )
    {
    return reinterpret_cast<qvm_detail::vref_<V> &>(a);
    }

////////////////////////////////////////////////

namespace
sfinae
    {
    using ::boost::qvm::to_string;
    using ::boost::qvm::assign;
    using ::boost::qvm::convert_to;
    using ::boost::qvm::cross;
    using ::boost::qvm::cmp;
    using ::boost::qvm::set_zero;
    using ::boost::qvm::scalar_cast;
    using ::boost::qvm::operator/=;
    using ::boost::qvm::operator/;
    using ::boost::qvm::dot;
    using ::boost::qvm::operator==;
    using ::boost::qvm::mag_sqr;
    using ::boost::qvm::mag;
    using ::boost::qvm::operator-=;
    using ::boost::qvm::operator-;
    using ::boost::qvm::operator*=;
    using ::boost::qvm::operator*;
    using ::boost::qvm::operator!=;
    using ::boost::qvm::normalized;
    using ::boost::qvm::normalize;
    using ::boost::qvm::operator+=;
    using ::boost::qvm::operator+;
    using ::boost::qvm::vref;
    }

} }

#endif

/* vec_operations.hpp
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
*/
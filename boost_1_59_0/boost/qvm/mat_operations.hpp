#ifndef BOOST_QVM_MAT_OPERATIONS_HPP_INCLUDED
#define BOOST_QVM_MAT_OPERATIONS_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.
// Copyright 2019 agate-pris

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/detail/mat_assign.hpp>
#include <boost/qvm/mat_operations2.hpp>
#include <boost/qvm/mat_operations3.hpp>
#include <boost/qvm/mat_operations4.hpp>
#include <boost/qvm/math.hpp>
#include <boost/qvm/detail/determinant_impl.hpp>
#include <boost/qvm/detail/cofactor_impl.hpp>
#include <boost/qvm/detail/transp_impl.hpp>
#include <boost/qvm/scalar_traits.hpp>
#include <string>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    BOOST_QVM_INLINE_CRITICAL
    void const *
    get_valid_ptr_mat_operations()
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
    template <int R,int C>
    struct
    to_string_m_defined
        {
        static bool const value=false;
        };

    template <int I,int SizeMinusOne>
    struct
    to_string_matrix_elements
        {
        template <class A>
        static
        std::string
        f( A const & a )
            {
            using namespace qvm_to_string_detail;
            return
                ( (I%mat_traits<A>::cols)==0 ? '(' : ',' ) +
                to_string(mat_traits<A>::template read_element<I/mat_traits<A>::cols,I%mat_traits<A>::cols>(a)) +
                ( (I%mat_traits<A>::cols)==mat_traits<A>::cols-1 ? ")" : "" ) +
                to_string_matrix_elements<I+1,SizeMinusOne>::f(a);
            }
        };

    template <int SizeMinusOne>
    struct
    to_string_matrix_elements<SizeMinusOne,SizeMinusOne>
        {
        template <class A>
        static
        std::string
        f( A const & a )
            {
            using namespace qvm_to_string_detail;
            return
                ( (SizeMinusOne%mat_traits<A>::cols)==0 ? '(' : ',' ) +
                to_string(mat_traits<A>::template read_element<SizeMinusOne/mat_traits<A>::cols,SizeMinusOne%mat_traits<A>::cols>(a)) +
                ')';
            }
        };
    }

template <class A>
inline
typename enable_if_c<
    is_mat<A>::value  &&
    !qvm_detail::to_string_m_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    std::string>::type
to_string( A const & a )
    {
    return "("+qvm_detail::to_string_matrix_elements<0,mat_traits<A>::rows*mat_traits<A>::cols-1>::f(a)+')';
    }

////////////////////////////////////////////////

template <class A,class B,class Cmp>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols,
    bool>::type
cmp( A const & a, B const & b, Cmp f )
    {
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            if( !f(
                mat_traits<A>::read_element_idx(i, j, a),
                mat_traits<B>::read_element_idx(i, j, b)) )
                return false;
    return true;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    convert_to_m_defined
        {
        static bool const value=false;
        };
    }

template <class R,class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_mat<R>::value && is_mat<A>::value &&
    mat_traits<R>::rows==mat_traits<A>::rows &&
    mat_traits<R>::cols==mat_traits<A>::cols &&
    !qvm_detail::convert_to_m_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    R>::type
convert_to( A const & a )
    {
    R r; assign(r,a);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    determinant_defined
        {
        static bool const value=false;
        };
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    !qvm_detail::determinant_defined<mat_traits<A>::rows>::value,
    typename mat_traits<A>::scalar_type>::type
determinant( A const & a )
    {
    return qvm_detail::determinant_impl(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class T,int Dim>
    class
    identity_mat_
        {
        identity_mat_( identity_mat_ const & );
        identity_mat_ & operator=( identity_mat_ const & );
        ~identity_mat_();

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

template <class T,int Dim>
struct
mat_traits< qvm_detail::identity_mat_<T,Dim> >
    {
    typedef qvm_detail::identity_mat_<T,Dim> this_matrix;
    typedef T scalar_type;
    static int const rows=Dim;
    static int const cols=Dim;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & /*x*/ )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<Dim);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<Dim);
        return scalar_traits<scalar_type>::value(Row==Col);
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & /*x*/ )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<Dim);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<Dim);
        return scalar_traits<scalar_type>::value(row==col);
        }
    };

template <class T,int Dim>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::identity_mat_<T,Dim> const &
identity_mat()
    {
    return *(qvm_detail::identity_mat_<T,Dim> const *)qvm_detail::get_valid_ptr_mat_operations();
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols,
    void>::type
set_identity( A & a )
    {
    assign(a,identity_mat<typename mat_traits<A>::scalar_type,mat_traits<A>::rows>());
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class T>
    struct
    projection_
        {
        T const _00;
        T const _11;
        T const _22;
        T const _23;
        T const _32;

        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        projection_( T _00, T _11, T _22, T _23, T _32 ):
            _00(_00),
            _11(_11),
            _22(_22),
            _23(_23),
            _32(_32)
            {
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

    template <int Row,int Col>
    struct
    projection_get
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( projection_<T> const & )
            {
            return scalar_traits<T>::value(0);
            }
        };

    template <> struct projection_get<0,0> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( projection_<T> const & m ) { return m._00; } };
    template <> struct projection_get<1,1> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( projection_<T> const & m ) { return m._11; } };
    template <> struct projection_get<2,2> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( projection_<T> const & m ) { return m._22; } };
    template <> struct projection_get<2,3> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( projection_<T> const & m ) { return m._23; } };
    template <> struct projection_get<3,2> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( projection_<T> const & m ) { return m._32; } };
    }

template <class T>
struct
mat_traits< qvm_detail::projection_<T> >
    {
    typedef qvm_detail::projection_<T> this_matrix;
    typedef T scalar_type;
    static int const rows=4;
    static int const cols=4;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return qvm_detail::projection_get<Row,Col>::get(x);
        }
    };

template <class T>
qvm_detail::projection_<T>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
perspective_lh( T fov_y, T aspect_ratio, T z_near, T z_far )
    {
    T const one = scalar_traits<T>::value(1);
    T const ys = one/tan(fov_y/scalar_traits<T>::value(2));
    T const xs = ys/aspect_ratio;
    T const zd = z_far-z_near;
    T const z1 = z_far/zd;
    T const z2 = -z_near*z1;
    return qvm_detail::projection_<T>(xs,ys,z1,z2,one);
    }

template <class T>
qvm_detail::projection_<T>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
perspective_rh( T fov_y, T aspect_ratio, T z_near, T z_far )
    {
    T const one = scalar_traits<T>::value(1);
    T const ys = one/tan(fov_y/scalar_traits<T>::value(2));
    T const xs = ys/aspect_ratio;
    T const zd = z_near-z_far;
    T const z1 = z_far/zd;
    T const z2 = z_near*z1;
    return qvm_detail::projection_<T>(xs,ys,z1,z2,-one);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class OriginalType,class Scalar>
    class
    matrix_scalar_cast_
        {
        matrix_scalar_cast_( matrix_scalar_cast_ const & );
        matrix_scalar_cast_ & operator=( matrix_scalar_cast_ const & );
        ~matrix_scalar_cast_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        matrix_scalar_cast_ &
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

    template <bool> struct scalar_cast_matrix_filter { };
    template <> struct scalar_cast_matrix_filter<true> { typedef int type; };
    }

template <class OriginalType,class Scalar>
struct
mat_traits< qvm_detail::matrix_scalar_cast_<OriginalType,Scalar> >
    {
    typedef Scalar scalar_type;
    typedef qvm_detail::matrix_scalar_cast_<OriginalType,Scalar> this_matrix;
    static int const rows=mat_traits<OriginalType>::rows;
    static int const cols=mat_traits<OriginalType>::cols;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return scalar_type(mat_traits<OriginalType>::template read_element<Row,Col>(reinterpret_cast<OriginalType const &>(x)));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return scalar_type(mat_traits<OriginalType>::read_element_idx(col,row,reinterpret_cast<OriginalType const &>(x)));
        }
    };

template <class OriginalType,class Scalar,int R,int C>
struct
deduce_mat<qvm_detail::matrix_scalar_cast_<OriginalType,Scalar>,R,C>
    {
    typedef mat<Scalar,R,C> type;
    };

template <class Scalar,class T>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::matrix_scalar_cast_<T,Scalar> const &
scalar_cast( T const & x, typename qvm_detail::scalar_cast_matrix_filter<is_mat<T>::value>::type=0 )
    {
    return reinterpret_cast<qvm_detail::matrix_scalar_cast_<T,Scalar> const &>(x);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    div_eq_ms_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value && is_scalar<B>::value &&
    !qvm_detail::div_eq_ms_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    A &>::type
operator/=( A & a, B b )
    {
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<A>::write_element_idx(i,j,a)/=b;
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    div_ms_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_mat<A>::value && is_scalar<B>::value &&
    !qvm_detail::div_ms_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols> >::type
operator/( A const & a, B b )
    {
    typedef typename deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols>::type R;
    R r;
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<R>::write_element_idx(i,j,r)=mat_traits<A>::read_element_idx(i,j,a)/b;
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    eq_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols &&
    !qvm_detail::eq_mm_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    bool>::type
operator==( A const & a, B const & b )
    {
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            if( mat_traits<A>::read_element_idx(i,j,a)!=mat_traits<B>::read_element_idx(i,j,b) )
                return false;
    return true;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    minus_eq_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols &&
    !qvm_detail::minus_eq_mm_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    A &>::type
operator-=( A & a, B const & b )
    {
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<A>::write_element_idx(i,j,a)-=mat_traits<B>::read_element_idx(i,j,b);
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    minus_m_defined
        {
        static bool const value=false;
        };
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_mat<A>::value &&
    !qvm_detail::minus_m_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    deduce_mat<A> >::type
operator-( A const & a )
    {
    typedef typename deduce_mat<A>::type R;
    R r;
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<R>::write_element_idx(i,j,r)=-mat_traits<A>::read_element_idx(i,j,a);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    minus_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols &&
    !qvm_detail::minus_mm_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols> >::type
operator-( A const & a, B const & b )
    {
    typedef typename deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols>::type R;
    R r;
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<R>::write_element_idx(i,j,r)=mat_traits<A>::read_element_idx(i,j,a)-mat_traits<B>::read_element_idx(i,j,b);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    mul_eq_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols &&
    !qvm_detail::mul_eq_mm_defined<mat_traits<A>::rows>::value,
    A &>::type
operator*=( A & r, B const & b )
    {
    typedef typename mat_traits<A>::scalar_type Ta;
    Ta a[mat_traits<A>::rows][mat_traits<A>::cols];
    for( int i=0; i<mat_traits<A>::rows; ++i )
        for( int j=0; j<mat_traits<B>::cols; ++j )
            a[i][j]=mat_traits<A>::read_element_idx(i,j,r);
    for( int i=0; i<mat_traits<A>::rows; ++i )
        for( int j=0; j<mat_traits<B>::cols; ++j )
            {
            Ta x(scalar_traits<Ta>::value(0));
            for( int k=0; k<mat_traits<A>::cols; ++k )
                x += a[i][k]*mat_traits<B>::read_element_idx(k,j,b);
            mat_traits<A>::write_element_idx(i,j,r) = x;
            }
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    mul_eq_ms_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value && is_scalar<B>::value &&
    !qvm_detail::mul_eq_ms_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    A &>::type
operator*=( A & a, B b )
    {
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<A>::write_element_idx(i,j,a)*=b;
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int R,int /*CR*/,int C>
    struct
    mul_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::cols==mat_traits<B>::rows &&
    !qvm_detail::mul_mm_defined<mat_traits<A>::rows,mat_traits<A>::cols,mat_traits<B>::cols>::value,
    deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<B>::cols> >::type
operator*( A const & a, B const & b )
    {
    typedef typename deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<B>::cols>::type R;
    R r;
    for( int i=0; i<mat_traits<A>::rows; ++i )
        for( int j=0; j<mat_traits<B>::cols; ++j )
            {
            typedef typename mat_traits<A>::scalar_type Ta;
            Ta x(scalar_traits<Ta>::value(0));
            for( int k=0; k<mat_traits<A>::cols; ++k )
                x += mat_traits<A>::read_element_idx(i,k,a)*mat_traits<B>::read_element_idx(k,j,b);
            mat_traits<R>::write_element_idx(i,j,r) = x;
            }
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    mul_ms_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_mat<A>::value && is_scalar<B>::value &&
    !qvm_detail::mul_ms_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols> >::type
operator*( A const & a, B b )
    {
    typedef typename deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols>::type R;
    R r;
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<R>::write_element_idx(i,j,r)=mat_traits<A>::read_element_idx(i,j,a)*b;
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    mul_sm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_scalar<A>::value && is_mat<B>::value &&
    !qvm_detail::mul_sm_defined<mat_traits<B>::rows,mat_traits<B>::cols>::value,
    deduce_mat2<A,B,mat_traits<B>::rows,mat_traits<B>::cols> >::type
operator*( A a, B const & b )
    {
    typedef typename deduce_mat2<A,B,mat_traits<B>::rows,mat_traits<B>::cols>::type R;
    R r;
    for( int i=0; i!=mat_traits<B>::rows; ++i )
        for( int j=0; j!=mat_traits<B>::cols; ++j )
            mat_traits<R>::write_element_idx(i,j,r)=a*mat_traits<B>::read_element_idx(i,j,b);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    neq_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols &&
    !qvm_detail::neq_mm_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    bool>::type
operator!=( A const & a, B const & b )
    {
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            if( mat_traits<A>::read_element_idx(i,j,a)!=mat_traits<B>::read_element_idx(i,j,b) )
                return true;
    return false;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    plus_eq_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols &&
    !qvm_detail::plus_eq_mm_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    A &>::type
operator+=( A & a, B const & b )
    {
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<A>::write_element_idx(i,j,a)+=mat_traits<B>::read_element_idx(i,j,b);
    return a;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    plus_mm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_mat<A>::value && is_mat<B>::value &&
    mat_traits<A>::rows==mat_traits<B>::rows &&
    mat_traits<A>::cols==mat_traits<B>::cols &&
    !qvm_detail::plus_mm_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols> >::type
operator+( A const & a, B const & b )
    {
    typedef typename deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols>::type R;
    R r;
    for( int i=0; i!=mat_traits<A>::rows; ++i )
        for( int j=0; j!=mat_traits<A>::cols; ++j )
            mat_traits<R>::write_element_idx(i,j,r)=mat_traits<A>::read_element_idx(i,j,a)+mat_traits<B>::read_element_idx(i,j,b);
    return r;
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class T>
    class
    mref_
        {
        mref_( mref_ const & );
        mref_ & operator=( mref_ const & );
        ~mref_();

        public:

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        mref_ &
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

template <class M>
struct
mat_traits< qvm_detail::mref_<M> >
    {
    typedef typename mat_traits<M>::scalar_type scalar_type;
    typedef qvm_detail::mref_<M> this_matrix;
    static int const rows=mat_traits<M>::rows;
    static int const cols=mat_traits<M>::cols;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return mat_traits<M>::template read_element<Row,Col>(reinterpret_cast<M const &>(x));
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return mat_traits<M>::template write_element<Row,Col>(reinterpret_cast<M &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return mat_traits<M>::read_element_idx(row,col,reinterpret_cast<M const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return mat_traits<M>::write_element_idx(row,col,reinterpret_cast<M &>(x));
        }
    };

template <class M,int R,int C>
struct
deduce_mat<qvm_detail::mref_<M>,R,C>
    {
    typedef mat<typename mat_traits<M>::scalar_type,R,C> type;
    };

template <class M>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_mat<M>::value,
    qvm_detail::mref_<M> const &>::type
mref( M const & a )
    {
    return reinterpret_cast<qvm_detail::mref_<M> const &>(a);
    }

template <class M>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_mat<M>::value,
    qvm_detail::mref_<M> &>::type
mref( M & a )
    {
    return reinterpret_cast<qvm_detail::mref_<M> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class T,int Rows,int Cols>
    class
    zero_mat_
        {
        zero_mat_( zero_mat_ const & );
        zero_mat_ & operator=( zero_mat_ const & );
        ~zero_mat_();

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

template <class T,int Rows,int Cols>
struct
mat_traits< qvm_detail::zero_mat_<T,Rows,Cols> >
    {
    typedef qvm_detail::zero_mat_<T,Rows,Cols> this_matrix;
    typedef T scalar_type;
    static int const rows=Rows;
    static int const cols=Cols;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<Rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<Cols);
        return scalar_traits<scalar_type>::value(0);
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return scalar_traits<scalar_type>::value(0);
        }
    };

template <class T,int Rows,int Cols,int R,int C>
struct
deduce_mat<qvm_detail::zero_mat_<T,Rows,Cols>,R,C>
    {
    typedef mat<T,R,C> type;
    };

template <class T,int Rows,int Cols>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::zero_mat_<T,Rows,Cols> const &
zero_mat()
    {
    return *(qvm_detail::zero_mat_<T,Rows,Cols> const *)qvm_detail::get_valid_ptr_mat_operations();
    }

template <class T,int Dim>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::zero_mat_<T,Dim,Dim> const &
zero_mat()
    {
    return *(qvm_detail::zero_mat_<T,Dim,Dim> const *)qvm_detail::get_valid_ptr_mat_operations();
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value,
    void>::type
set_zero( A & a )
    {
    assign(a,zero_mat<typename mat_traits<A>::scalar_type,mat_traits<A>::rows,mat_traits<A>::cols>());
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D,class S>
    struct
    rot_mat_
        {
        typedef S scalar_type;
        scalar_type a[3][3];

        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
        rot_mat_(
                scalar_type a00, scalar_type a01, scalar_type a02,
                scalar_type a10, scalar_type a11, scalar_type a12,
                scalar_type a20, scalar_type a21, scalar_type a22 )
            {
            a[0][0] = a00;
            a[0][1] = a01;
            a[0][2] = a02;
            a[1][0] = a10;
            a[1][1] = a11;
            a[1][2] = a12;
            a[2][0] = a20;
            a[2][1] = a21;
            a[2][2] = a22;
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

    template <int Row,int Col>
    struct
    rot_m_get
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const (&)[3][3] )
            {
            return scalar_traits<T>::value(Row==Col);
            }
        };

    template <> struct rot_m_get<0,0> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[0][0]; } };
    template <> struct rot_m_get<0,1> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[0][1]; } };
    template <> struct rot_m_get<0,2> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[0][2]; } };
    template <> struct rot_m_get<1,0> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[1][0]; } };
    template <> struct rot_m_get<1,1> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[1][1]; } };
    template <> struct rot_m_get<1,2> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[1][2]; } };
    template <> struct rot_m_get<2,0> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[2][0]; } };
    template <> struct rot_m_get<2,1> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[2][1]; } };
    template <> struct rot_m_get<2,2> { template <class T> static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL T get( T const (&a)[3][3] ) { return a[2][2]; } };
    }

template <class M>
struct mat_traits;

template <int D,class S>
struct
mat_traits< qvm_detail::rot_mat_<D,S> >
    {
    typedef qvm_detail::rot_mat_<D,S> this_matrix;
    typedef typename this_matrix::scalar_type scalar_type;
    static int const rows=D;
    static int const cols=D;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<D);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<D);
        return qvm_detail::rot_m_get<Row,Col>::get(x.a);
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<D);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<D);
        return row<3 && col<3?
            x.a[row][col] :
            scalar_traits<scalar_type>::value(row==col);
        }
    };

template <int Dim,class V,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
typename enable_if_c<
    is_vec<V>::value && vec_traits<V>::dim==3,
    qvm_detail::rot_mat_<Dim,Angle> >::type
rot_mat( V const & axis, Angle angle )
    {
    typedef Angle scalar_type;
    scalar_type const x=vec_traits<V>::template read_element<0>(axis);
    scalar_type const y=vec_traits<V>::template read_element<1>(axis);
    scalar_type const z=vec_traits<V>::template read_element<2>(axis);
    scalar_type const m2=x*x+y*y+z*z;
    if( m2==scalar_traits<scalar_type>::value(0) )
        BOOST_QVM_THROW_EXCEPTION(zero_magnitude_error());
    scalar_type const s = sin(angle);
    scalar_type const c = cos(angle);
    scalar_type const x2 = x*x;
    scalar_type const y2 = y*y;
    scalar_type const z2 = z*z;
    scalar_type const xy = x*y;
    scalar_type const xz = x*z;
    scalar_type const yz = y*z;
    scalar_type const xs = x*s;
    scalar_type const ys = y*s;
    scalar_type const zs = z*s;
    scalar_type const one = scalar_traits<scalar_type>::value(1);
    scalar_type const c1 = one-c;
    return qvm_detail::rot_mat_<Dim,Angle>(
        x2+(one-x2)*c, xy*c1-zs, xz*(one-c)+ys,
        xy*c1+zs, y2+(one-y2)*c, yz*c1-xs,
        xz*c1-ys, yz*c1+xs, z2+(one-z2)*c );
    }

template <class A,class B,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3 &&
    is_vec<B>::value && vec_traits<B>::dim==3,
    void>::type
set_rot( A & a, B const & axis, Angle angle )
    {
    assign(a,rot_mat<mat_traits<A>::rows>(axis,angle));
    }

template <class A,class B,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3 &&
    is_vec<B>::value && vec_traits<B>::dim==3,
    void>::type
rotate( A & a, B const & axis, Angle angle )
    {
    a *= rot_mat<mat_traits<A>::rows>(axis,angle);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_xzy( Angle x1, Angle z2, Angle y3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(x1);
    scalar_type const s1 = sin(x1);
    scalar_type const c2 = cos(z2);
    scalar_type const s2 = sin(z2);
    scalar_type const c3 = cos(y3);
    scalar_type const s3 = sin(y3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c2*c3, -s2, c2*s3,
        s1*s3 + c1*c3*s2, c1*c2, c1*s2*s3 - c3*s1,
        c3*s1*s2 - c1*s3, c2*s1, c1*c3 + s1*s2*s3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_xzy( A & a, Angle x1, Angle z2, Angle y3 )
    {
    assign(a,rot_mat_xzy<mat_traits<A>::rows>(x1,z2,y3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_xzy( A & a, Angle x1, Angle z2, Angle y3 )
    {
    a *= rot_mat_xzy<mat_traits<A>::rows>(x1,z2,y3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_xyz( Angle x1, Angle y2, Angle z3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(x1);
    scalar_type const s1 = sin(x1);
    scalar_type const c2 = cos(y2);
    scalar_type const s2 = sin(y2);
    scalar_type const c3 = cos(z3);
    scalar_type const s3 = sin(z3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c2*c3, -c2*s3, s2,
        c1*s3 + c3*s1*s2, c1*c3 - s1*s2*s3, -c2*s1,
        s1*s3 - c1*c3*s2, c3*s1 + c1*s2*s3, c1*c2 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_xyz( A & a, Angle x1, Angle y2, Angle z3 )
    {
    assign(a,rot_mat_xyz<mat_traits<A>::rows>(x1,y2,z3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_xyz( A & a, Angle x1, Angle y2, Angle z3 )
    {
    a *= rot_mat_xyz<mat_traits<A>::rows>(x1,y2,z3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_yxz( Angle y1, Angle x2, Angle z3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(y1);
    scalar_type const s1 = sin(y1);
    scalar_type const c2 = cos(x2);
    scalar_type const s2 = sin(x2);
    scalar_type const c3 = cos(z3);
    scalar_type const s3 = sin(z3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c3 + s1*s2*s3, c3*s1*s2 - c1*s3, c2*s1,
        c2*s3, c2*c3, -s2,
        c1*s2*s3 - c3*s1, c1*c3*s2 + s1*s3, c1*c2 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_yxz( A & a, Angle y1, Angle x2, Angle z3 )
    {
    assign(a,rot_mat_yxz<mat_traits<A>::rows>(y1,x2,z3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_yxz( A & a, Angle y1, Angle x2, Angle z3 )
    {
    a *= rot_mat_yxz<mat_traits<A>::rows>(y1,x2,z3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_yzx( Angle y1, Angle z2, Angle x3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(y1);
    scalar_type const s1 = sin(y1);
    scalar_type const c2 = cos(z2);
    scalar_type const s2 = sin(z2);
    scalar_type const c3 = cos(x3);
    scalar_type const s3 = sin(x3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c2, s1*s3 - c1*c3*s2, c3*s1 + c1*s2*s3,
        s2, c2*c3, -c2*s3,
        -c2*s1, c1*s3 + c3*s1*s2, c1*c3 - s1*s2*s3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_yzx( A & a, Angle y1, Angle z2, Angle x3 )
    {
    assign(a,rot_mat_yzx<mat_traits<A>::rows>(y1,z2,x3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_yzx( A & a, Angle y1, Angle z2, Angle x3 )
    {
    a *= rot_mat_yzx<mat_traits<A>::rows>(y1,z2,x3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_zyx( Angle z1, Angle y2, Angle x3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(z1);
    scalar_type const s1 = sin(z1);
    scalar_type const c2 = cos(y2);
    scalar_type const s2 = sin(y2);
    scalar_type const c3 = cos(x3);
    scalar_type const s3 = sin(x3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c2, c1*s2*s3 - c3*s1, s1*s3 + c1*c3*s2,
        c2*s1, c1*c3 + s1*s2*s3, c3*s1*s2 - c1*s3,
        -s2, c2*s3, c2*c3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_zyx( A & a, Angle z1, Angle y2, Angle x3 )
    {
    assign(a,rot_mat_zyx<mat_traits<A>::rows>(z1,y2,x3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_zyx( A & a, Angle z1, Angle y2, Angle x3 )
    {
    a *= rot_mat_zyx<mat_traits<A>::rows>(z1,y2,x3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_zxy( Angle z1, Angle x2, Angle y3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(z1);
    scalar_type const s1 = sin(z1);
    scalar_type const c2 = cos(x2);
    scalar_type const s2 = sin(x2);
    scalar_type const c3 = cos(y3);
    scalar_type const s3 = sin(y3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c3 - s1*s2*s3, -c2*s1, c1*s3 + c3*s1*s2,
        c3*s1 + c1*s2*s3, c1*c2, s1*s3 - c1*c3*s2,
        -c2*s3, s2, c2*c3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_zxy( A & a, Angle z1, Angle x2, Angle y3 )
    {
    assign(a,rot_mat_zxy<mat_traits<A>::rows>(z1,x2,y3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_zxy( A & a, Angle z1, Angle x2, Angle y3 )
    {
    a *= rot_mat_zxy<mat_traits<A>::rows>(z1,x2,y3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_xzx( Angle x1, Angle z2, Angle x3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(x1);
    scalar_type const s1 = sin(x1);
    scalar_type const c2 = cos(z2);
    scalar_type const s2 = sin(z2);
    scalar_type const c3 = cos(x3);
    scalar_type const s3 = sin(x3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c2, -c3*s2, s2*s3,
        c1*s2, c1*c2*c3 - s1*s3, -c3*s1 - c1*c2*s3,
        s1*s2, c1*s3 + c2*c3*s1, c1*c3 - c2*s1*s3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_xzx( A & a, Angle x1, Angle z2, Angle x3 )
    {
    assign(a,rot_mat_xzx<mat_traits<A>::rows>(x1,z2,x3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_xzx( A & a, Angle x1, Angle z2, Angle x3 )
    {
    a *= rot_mat_xzx<mat_traits<A>::rows>(x1,z2,x3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_xyx( Angle x1, Angle y2, Angle x3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(x1);
    scalar_type const s1 = sin(x1);
    scalar_type const c2 = cos(y2);
    scalar_type const s2 = sin(y2);
    scalar_type const c3 = cos(x3);
    scalar_type const s3 = sin(x3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c2, s2*s3, c3*s2,
        s1*s2, c1*c3 - c2*s1*s3, -c1*s3 - c2*c3*s1,
        -c1*s2, c3*s1 + c1*c2*s3, c1*c2*c3 - s1*s3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_xyx( A & a, Angle x1, Angle y2, Angle x3 )
    {
    assign(a,rot_mat_xyx<mat_traits<A>::rows>(x1,y2,x3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_xyx( A & a, Angle x1, Angle y2, Angle x3 )
    {
    a *= rot_mat_xyx<mat_traits<A>::rows>(x1,y2,x3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_yxy( Angle y1, Angle x2, Angle y3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(y1);
    scalar_type const s1 = sin(y1);
    scalar_type const c2 = cos(x2);
    scalar_type const s2 = sin(x2);
    scalar_type const c3 = cos(y3);
    scalar_type const s3 = sin(y3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c3 - c2*s1*s3, s1*s2, c1*s3 + c2*c3*s1,
        s2*s3, c2, -c3*s2,
        -c3*s1 - c1*c2*s3, c1*s2, c1*c2*c3 - s1*s3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_yxy( A & a, Angle y1, Angle x2, Angle y3 )
    {
    assign(a,rot_mat_yxy<mat_traits<A>::rows>(y1,x2,y3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_yxy( A & a, Angle y1, Angle x2, Angle y3 )
    {
    a *= rot_mat_yxy<mat_traits<A>::rows>(y1,x2,y3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_yzy( Angle y1, Angle z2, Angle y3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(y1);
    scalar_type const s1 = sin(y1);
    scalar_type const c2 = cos(z2);
    scalar_type const s2 = sin(z2);
    scalar_type const c3 = cos(y3);
    scalar_type const s3 = sin(y3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c2*c3 - s1*s3, -c1*s2, c3*s1 + c1*c2*s3,
        c3*s2, c2, s2*s3,
        -c1*s3 - c2*c3*s1, s1*s2, c1*c3 - c2*s1*s3 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_yzy( A & a, Angle y1, Angle z2, Angle y3 )
    {
    assign(a,rot_mat_yzy<mat_traits<A>::rows>(y1,z2,y3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_yzy( A & a, Angle y1, Angle z2, Angle y3 )
    {
    a *= rot_mat_yzy<mat_traits<A>::rows>(y1,z2,y3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_zyz( Angle z1, Angle y2, Angle z3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(z1);
    scalar_type const s1 = sin(z1);
    scalar_type const c2 = cos(y2);
    scalar_type const s2 = sin(y2);
    scalar_type const c3 = cos(z3);
    scalar_type const s3 = sin(z3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c2*c3 - s1*s3, -c3*s1 - c1*c2*s3, c1*s2,
        c1*s3 + c2*c3*s1, c1*c3 - c2*s1*s3, s1*s2,
        -c3*s2, s2*s3, c2 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_zyz( A & a, Angle z1, Angle y2, Angle z3 )
    {
    assign(a,rot_mat_zyz<mat_traits<A>::rows>(z1,y2,z3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_zyz( A & a, Angle z1, Angle y2, Angle z3 )
    {
    a *= rot_mat_zyz<mat_traits<A>::rows>(z1,y2,z3);
    }

////////////////////////////////////////////////

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE
qvm_detail::rot_mat_<Dim,Angle>
rot_mat_zxz( Angle z1, Angle x2, Angle z3 )
    {
    typedef Angle scalar_type;
    scalar_type const c1 = cos(z1);
    scalar_type const s1 = sin(z1);
    scalar_type const c2 = cos(x2);
    scalar_type const s2 = sin(x2);
    scalar_type const c3 = cos(z3);
    scalar_type const s3 = sin(z3);
    return qvm_detail::rot_mat_<Dim,Angle>(
        c1*c3 - c2*s1*s3, -c1*s3 - c2*c3*s1, s1*s2,
        c3*s1 + c1*c2*s3, c1*c2*c3 - s1*s3, -c1*s2,
        s2*s3, c3*s2, c2 );
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
set_rot_zxz( A & a, Angle z1, Angle x2, Angle z3 )
    {
    assign(a,rot_mat_zxz<mat_traits<A>::rows>(z1,x2,z3));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    mat_traits<A>::rows>=3,
    void>::type
rotate_zxz( A & a, Angle z1, Angle x2, Angle z3 )
    {
    a *= rot_mat_zxz<mat_traits<A>::rows>(z1,x2,z3);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Dim,class Angle>
    struct
    rotx_mat_
        {
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        rotx_mat_()
            {
            }

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }

        private:

        rotx_mat_( rotx_mat_ const & );
        rotx_mat_ & operator=( rotx_mat_ const & );
        ~rotx_mat_();
        };

    template <int Row,int Col>
    struct
    rotx_m_get
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & )
            {
            return scalar_traits<T>::value(Row==Col);
            }
        };

    template <>
    struct
    rotx_m_get<1,1>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return cos(angle);
            }
        };

    template <>
    struct
    rotx_m_get<1,2>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return -sin(angle);
            }
        };

    template <>
    struct
    rotx_m_get<2,1>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return sin(angle);
            }
        };

    template <>
    struct
    rotx_m_get<2,2>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return cos(angle);
            }
        };
    }

template <int Dim,class Angle>
struct
mat_traits< qvm_detail::rotx_mat_<Dim,Angle> >
    {
    typedef qvm_detail::rotx_mat_<Dim,Angle> this_matrix;
    typedef Angle scalar_type;
    static int const rows=Dim;
    static int const cols=Dim;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Row<Dim);
        BOOST_QVM_STATIC_ASSERT(Col<Dim);
        return qvm_detail::rotx_m_get<Row,Col>::get(reinterpret_cast<Angle const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(row<Dim);
        BOOST_QVM_ASSERT(col<Dim);
        Angle const & a=reinterpret_cast<Angle const &>(x);
        if( row==1 )
            {
            if( col==1 )
                return cos(a);
            if( col==2 )
                return -sin(a);
            }
        if( row==2 )
            {
            if( col==1 )
                return sin(a);
            if( col==2 )
                return cos(a);
            }
        return scalar_traits<scalar_type>::value(row==col);
        }
    };

template <int Dim,class Angle>
struct
deduce_mat<qvm_detail::rotx_mat_<Dim,Angle>,Dim,Dim>
    {
    typedef mat<Angle,Dim,Dim> type;
    };

template <int Dim,class Angle>
struct
deduce_mat2<qvm_detail::rotx_mat_<Dim,Angle>,qvm_detail::rotx_mat_<Dim,Angle>,Dim,Dim>
    {
    typedef mat<Angle,Dim,Dim> type;
    };

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::rotx_mat_<Dim,Angle> const &
rotx_mat( Angle const & angle )
    {
    BOOST_QVM_STATIC_ASSERT(Dim>=3);
    return reinterpret_cast<qvm_detail::rotx_mat_<Dim,Angle> const &>(angle);
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows>=3 &&
    mat_traits<A>::rows==mat_traits<A>::cols,
    void>::type
set_rotx( A & a, Angle angle )
    {
    assign(a,rotx_mat<mat_traits<A>::rows>(angle));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows>=3 &&
    mat_traits<A>::rows==mat_traits<A>::cols,
    void>::type
rotate_x( A & a, Angle angle )
    {
    a *= rotx_mat<mat_traits<A>::rows>(angle);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Dim,class Angle>
    struct
    roty_mat_
        {
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        roty_mat_()
            {
            }

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }

        private:

        roty_mat_( roty_mat_ const & );
        roty_mat_ & operator=( roty_mat_ const & );
        ~roty_mat_();
        };

    template <int Row,int Col>
    struct
    roty_m_get
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & )
            {
            return scalar_traits<T>::value(Row==Col);
            }
        };

    template <>
    struct
    roty_m_get<0,0>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return cos(angle);
            }
        };

    template <>
    struct
    roty_m_get<0,2>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return sin(angle);
            }
        };

    template <>
    struct
    roty_m_get<2,0>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return -sin(angle);
            }
        };

    template <>
    struct
    roty_m_get<2,2>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return cos(angle);
            }
        };
    }

template <int Dim,class Angle>
struct
mat_traits< qvm_detail::roty_mat_<Dim,Angle> >
    {
    typedef qvm_detail::roty_mat_<Dim,Angle> this_matrix;
    typedef Angle scalar_type;
    static int const rows=Dim;
    static int const cols=Dim;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Row<Dim);
        BOOST_QVM_STATIC_ASSERT(Col<Dim);
        return qvm_detail::roty_m_get<Row,Col>::get(reinterpret_cast<Angle const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(row<Dim);
        BOOST_QVM_ASSERT(col<Dim);
        Angle const & a=reinterpret_cast<Angle const &>(x);
        if( row==0 )
            {
            if( col==0 )
                return cos(a);
            if( col==2 )
                return sin(a);
            }
        if( row==2 )
            {
            if( col==0 )
                return -sin(a);
            if( col==2 )
                return cos(a);
            }
        return scalar_traits<scalar_type>::value(row==col);
        }
    };

template <int Dim,class Angle>
struct
deduce_mat<qvm_detail::roty_mat_<Dim,Angle>,Dim,Dim>
    {
    typedef mat<Angle,Dim,Dim> type;
    };

template <int Dim,class Angle>
struct
deduce_mat2<qvm_detail::roty_mat_<Dim,Angle>,qvm_detail::roty_mat_<Dim,Angle>,Dim,Dim>
    {
    typedef mat<Angle,Dim,Dim> type;
    };

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::roty_mat_<Dim,Angle> const &
roty_mat( Angle const & angle )
    {
    BOOST_QVM_STATIC_ASSERT(Dim>=3);
    return reinterpret_cast<qvm_detail::roty_mat_<Dim,Angle> const &>(angle);
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows>=2 &&
    mat_traits<A>::rows==mat_traits<A>::cols,
    void>::type
set_roty( A & a, Angle angle )
    {
    assign(a,roty_mat<mat_traits<A>::rows>(angle));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows>=3 &&
    mat_traits<A>::rows==mat_traits<A>::cols,
    void>::type
rotate_y( A & a, Angle angle )
    {
    a *= roty_mat<mat_traits<A>::rows>(angle);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Dim,class Angle>
    struct
    rotz_mat_
        {
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        rotz_mat_()
            {
            }

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }

        private:

        rotz_mat_( rotz_mat_ const & );
        rotz_mat_ & operator=( rotz_mat_ const & );
        ~rotz_mat_();
        };

    template <int Row,int Col>
    struct
    rotz_m_get
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & )
            {
            return scalar_traits<T>::value(Row==Col);
            }
        };

    template <>
    struct
    rotz_m_get<0,0>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return cos(angle);
            }
        };

    template <>
    struct
    rotz_m_get<0,1>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return -sin(angle);
            }
        };

    template <>
    struct
    rotz_m_get<1,0>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return sin(angle);
            }
        };

    template <>
    struct
    rotz_m_get<1,1>
        {
        template <class T>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        T
        get( T const & angle )
            {
            return cos(angle);
            }
        };
    }

template <int Dim,class Angle>
struct
mat_traits< qvm_detail::rotz_mat_<Dim,Angle> >
    {
    typedef qvm_detail::rotz_mat_<Dim,Angle> this_matrix;
    typedef Angle scalar_type;
    static int const rows=Dim;
    static int const cols=Dim;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Row<Dim);
        BOOST_QVM_STATIC_ASSERT(Col<Dim);
        return qvm_detail::rotz_m_get<Row,Col>::get(reinterpret_cast<Angle const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(row<Dim);
        BOOST_QVM_ASSERT(col<Dim);
        Angle const & a=reinterpret_cast<Angle const &>(x);
        if( row==0 )
            {
            if( col==0 )
                return cos(a);
            if( col==1 )
                return -sin(a);
            }
        if( row==1 )
            {
            if( col==0 )
                return sin(a);
            if( col==1 )
                return cos(a);
            }
        return scalar_traits<scalar_type>::value(row==col);
        }
    };

template <int Dim,class Angle>
struct
deduce_mat<qvm_detail::rotz_mat_<Dim,Angle>,Dim,Dim>
    {
    typedef mat<Angle,Dim,Dim> type;
    };

template <int Dim,class Angle,int R,int C>
struct
deduce_mat2<qvm_detail::rotz_mat_<Dim,Angle>,qvm_detail::rotz_mat_<Dim,Angle>,R,C>
    {
    typedef mat<Angle,R,C> type;
    };

template <int Dim,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
qvm_detail::rotz_mat_<Dim,Angle> const &
rotz_mat( Angle const & angle )
    {
    BOOST_QVM_STATIC_ASSERT(Dim>=2);
    return reinterpret_cast<qvm_detail::rotz_mat_<Dim,Angle> const &>(angle);
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows>=2 &&
    mat_traits<A>::rows==mat_traits<A>::cols,
    void>::type
set_rotz( A & a, Angle angle )
    {
    assign(a,rotz_mat<mat_traits<A>::rows>(angle));
    }

template <class A,class Angle>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows>=2 &&
    mat_traits<A>::rows==mat_traits<A>::cols,
    void>::type
rotate_z( A & a, Angle angle )
    {
    a *= rotz_mat<mat_traits<A>::rows>(angle);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int D>
    struct
    inverse_m_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename lazy_enable_if_c<
    is_mat<A>::value && is_scalar<B>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    !qvm_detail::inverse_m_defined<mat_traits<A>::rows>::value,
    deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols> >::type
inverse( A const & a, B det )
    {
    typedef typename mat_traits<A>::scalar_type T;
    BOOST_QVM_ASSERT(det!=scalar_traits<T>::value(0));
    T f=scalar_traits<T>::value(1)/det;
    typedef typename deduce_mat2<A,B,mat_traits<A>::rows,mat_traits<A>::cols>::type cofactor_return_type;
    cofactor_return_type c=qvm_detail::cofactor_impl(a);
    return reinterpret_cast<qvm_detail::transposed_<cofactor_return_type> const &>(c) * f;
    }

template <class A>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename lazy_enable_if_c<
    is_mat<A>::value &&
    mat_traits<A>::rows==mat_traits<A>::cols &&
    !qvm_detail::inverse_m_defined<mat_traits<A>::rows>::value,
    deduce_mat<A> >::type
inverse( A const & a )
    {
    typedef typename mat_traits<A>::scalar_type T;
    T det=determinant(a);
    if( det==scalar_traits<T>::value(0) )
        BOOST_QVM_THROW_EXCEPTION(zero_determinant_error());
    return inverse(a,det);
    }

////////////////////////////////////////////////

namespace
sfinae
    {
    using ::boost::qvm::to_string;
    using ::boost::qvm::assign;
    using ::boost::qvm::determinant;
    using ::boost::qvm::cmp;
    using ::boost::qvm::convert_to;
    using ::boost::qvm::set_identity;
    using ::boost::qvm::set_zero;
    using ::boost::qvm::scalar_cast;
    using ::boost::qvm::operator/=;
    using ::boost::qvm::operator/;
    using ::boost::qvm::operator==;
    using ::boost::qvm::operator-=;
    using ::boost::qvm::operator-;
    using ::boost::qvm::operator*=;
    using ::boost::qvm::operator*;
    using ::boost::qvm::operator!=;
    using ::boost::qvm::operator+=;
    using ::boost::qvm::operator+;
    using ::boost::qvm::mref;
    using ::boost::qvm::rot_mat;
    using ::boost::qvm::set_rot;
    using ::boost::qvm::rotate;
    using ::boost::qvm::set_rotx;
    using ::boost::qvm::rotate_x;
    using ::boost::qvm::set_roty;
    using ::boost::qvm::rotate_y;
    using ::boost::qvm::set_rotz;
    using ::boost::qvm::rotate_z;
    using ::boost::qvm::inverse;
    }

} }

#endif

/* mat_operations.hpp
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
*/
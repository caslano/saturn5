#ifndef BOOST_QVM_MAP_MAT_VEC_HPP_INCLUDED
#define BOOST_QVM_MAP_MAT_VEC_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/mat_traits.hpp>
#include <boost/qvm/deduce_vec.hpp>
#include <boost/qvm/assert.hpp>
#include <boost/qvm/enable_if.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <int Col,class OriginalMatrix>
    class
    col_
        {
        col_( col_ const & );
        col_ & operator=( col_ const & );
        ~col_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        col_ &
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
    }

template <int Col,class OriginalMatrix>
struct
vec_traits< qvm_detail::col_<Col,OriginalMatrix> >
    {
    typedef qvm_detail::col_<Col,OriginalMatrix> this_vector;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const dim=mat_traits<OriginalMatrix>::rows;
    BOOST_QVM_STATIC_ASSERT(Col>=0);
    BOOST_QVM_STATIC_ASSERT(Col<mat_traits<OriginalMatrix>::cols);

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template read_element<I,Col>(reinterpret_cast<OriginalMatrix const &>(x));
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template write_element<I,Col>(reinterpret_cast<OriginalMatrix &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::read_element_idx(i,Col,reinterpret_cast<OriginalMatrix const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int i, this_vector & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::write_element_idx(i,Col,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <int Col,class OriginalMatrix,int D>
struct
deduce_vec<qvm_detail::col_<Col,OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <int Col,class OriginalMatrix,int D>
struct
deduce_vec2<qvm_detail::col_<Col,OriginalMatrix>,qvm_detail::col_<Col,OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <int Col,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::col_<Col,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
col( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::col_<Col,A> const &>(a);
    }

template <int Col,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::col_<Col,A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
col( A & a )
    {
    return reinterpret_cast<typename qvm_detail::col_<Col,A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Row,class OriginalMatrix>
    class
    row_
        {
        row_( row_ const & );
        row_ & operator=( row_ const & );
        ~row_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        row_ &
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
    }

template <int Row,class OriginalMatrix>
struct
vec_traits< qvm_detail::row_<Row,OriginalMatrix> >
    {
    typedef qvm_detail::row_<Row,OriginalMatrix> this_vector;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const dim=mat_traits<OriginalMatrix>::cols;
    BOOST_QVM_STATIC_ASSERT(Row>=0);
    BOOST_QVM_STATIC_ASSERT(Row<mat_traits<OriginalMatrix>::rows);

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template read_element<Row,I>(reinterpret_cast<OriginalMatrix const &>(x));
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template write_element<Row,I>(reinterpret_cast<OriginalMatrix &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::read_element_idx(Row,i,reinterpret_cast<OriginalMatrix const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int i, this_vector & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::write_element_idx(Row,i,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <int Row,class OriginalMatrix,int D>
struct
deduce_vec<qvm_detail::row_<Row,OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <int Row,class OriginalMatrix,int D>
struct
deduce_vec2<qvm_detail::row_<Row,OriginalMatrix>,qvm_detail::row_<Row,OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <int Row,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::row_<Row,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
row( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::row_<Row,A> const &>(a);
    }

template <int Row,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::row_<Row,A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
row( A & a )
    {
    return reinterpret_cast<typename qvm_detail::row_<Row,A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class OriginalMatrix>
    class
    diag_
        {
        diag_( diag_ const & );
        diag_ & operator=( diag_ const & );
        ~diag_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        diag_ &
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

    template <int X,int Y,bool Which>
    struct diag_bool_dispatch;

    template <int X,int Y>
    struct
    diag_bool_dispatch<X,Y,true>
        {
        static int const value=X;
        };

    template <int X,int Y>
    struct
    diag_bool_dispatch<X,Y,false>
        {
        static int const value=Y;
        };
    }

template <class OriginalMatrix>
struct
vec_traits< qvm_detail::diag_<OriginalMatrix> >
    {
    typedef qvm_detail::diag_<OriginalMatrix> this_vector;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const dim=qvm_detail::diag_bool_dispatch<
            mat_traits<OriginalMatrix>::rows,
            mat_traits<OriginalMatrix>::cols,
            mat_traits<OriginalMatrix>::rows<=mat_traits<OriginalMatrix>::cols>::value;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template read_element<I,I>(reinterpret_cast<OriginalMatrix const &>(x));
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template write_element<I,I>(reinterpret_cast<OriginalMatrix &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::read_element_idx(i,i,reinterpret_cast<OriginalMatrix const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int i, this_vector & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::write_element_idx(i,i,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <class OriginalMatrix,int D>
struct
deduce_vec<qvm_detail::diag_<OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <class OriginalMatrix,int D>
struct
deduce_vec2<qvm_detail::diag_<OriginalMatrix>,qvm_detail::diag_<OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::diag_<A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
diag( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::diag_<A> const &>(a);
    }

template <class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::diag_<A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
diag( A & a )
    {
    return reinterpret_cast<typename qvm_detail::diag_<A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class OriginalMatrix>
    class
    translation_
        {
        translation_( translation_ const & );
        ~translation_();

        public:

        translation_ &
        operator=( translation_ const & x )
            {
            assign(*this,x);
            return *this;
            }

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        translation_ &
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
    }

template <class OriginalMatrix>
struct
vec_traits< qvm_detail::translation_<OriginalMatrix> >
    {
    typedef qvm_detail::translation_<OriginalMatrix> this_vector;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const dim=mat_traits<OriginalMatrix>::rows-1;
    BOOST_QVM_STATIC_ASSERT(mat_traits<OriginalMatrix>::rows==mat_traits<OriginalMatrix>::cols);
    BOOST_QVM_STATIC_ASSERT(mat_traits<OriginalMatrix>::rows>=3);

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template read_element<I,dim>(reinterpret_cast<OriginalMatrix const &>(x));
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return mat_traits<OriginalMatrix>::template write_element<I,dim>(reinterpret_cast<OriginalMatrix &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::read_element_idx(i,dim,reinterpret_cast<OriginalMatrix const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int i, this_vector & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return mat_traits<OriginalMatrix>::write_element_idx(i,dim,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <class OriginalMatrix,int D>
struct
deduce_vec<qvm_detail::translation_<OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <class OriginalMatrix,int D>
struct
deduce_vec2<qvm_detail::translation_<OriginalMatrix>,qvm_detail::translation_<OriginalMatrix>,D>
    {
    typedef vec<typename mat_traits<OriginalMatrix>::scalar_type,D> type;
    };

template <class A>
typename enable_if_c<
    is_mat<A>::value && mat_traits<A>::rows==mat_traits<A>::cols && mat_traits<A>::rows>=3,
    qvm_detail::translation_<A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
translation( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::translation_<A> const &>(a);
    }

template <class A>
typename enable_if_c<
    is_mat<A>::value && mat_traits<A>::rows==mat_traits<A>::cols && mat_traits<A>::rows>=3,
    qvm_detail::translation_<A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
translation( A & a )
    {
    return reinterpret_cast<typename qvm_detail::translation_<A> &>(a);
    }

} }

#endif

/* map_mat_vec.hpp
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
*/
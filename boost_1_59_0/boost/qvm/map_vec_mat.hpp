#ifndef BOOST_QVM_MAP_VEC_MAT_HPP_INCLUDED
#define BOOST_QVM_MAP_VEC_MAT_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/deduce_mat.hpp>
#include <boost/qvm/vec_traits.hpp>
#include <boost/qvm/assert.hpp>
#include <boost/qvm/enable_if.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <class OriginalVector>
    class
    col_mat_
        {
        col_mat_( col_mat_ const & );
        col_mat_ & operator=( col_mat_ const & );
        ~col_mat_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        col_mat_ &
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

template <class OriginalVector>
struct
mat_traits< qvm_detail::col_mat_<OriginalVector> >
    {
    typedef qvm_detail::col_mat_<OriginalVector> this_matrix;
    typedef typename vec_traits<OriginalVector>::scalar_type scalar_type;
    static int const rows=vec_traits<OriginalVector>::dim;
    static int const cols=1;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Col==0);
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        return vec_traits<OriginalVector>::template read_element<Row>(reinterpret_cast<OriginalVector const &>(x));
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Col==0);
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        return vec_traits<OriginalVector>::template write_element<Row>(reinterpret_cast<OriginalVector &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(col==0);
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        return vec_traits<OriginalVector>::read_element_idx(row,reinterpret_cast<OriginalVector const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix & x )
        {
        BOOST_QVM_ASSERT(col==0);
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        return vec_traits<OriginalVector>::write_element_idx(row,reinterpret_cast<OriginalVector &>(x));
        }
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat<qvm_detail::col_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat2<qvm_detail::col_mat_<OriginalVector>,qvm_detail::col_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::col_mat_<A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
col_mat( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::col_mat_<A> const &>(a);
    }

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::col_mat_<A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
col_mat( A & a )
    {
    return reinterpret_cast<typename qvm_detail::col_mat_<A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class OriginalVector>
    class
    row_mat_
        {
        row_mat_( row_mat_ const & );
        row_mat_ & operator=( row_mat_ const & );
        ~row_mat_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        row_mat_ &
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

template <class OriginalVector>
struct
mat_traits< qvm_detail::row_mat_<OriginalVector> >
    {
    typedef qvm_detail::row_mat_<OriginalVector> this_matrix;
    typedef typename vec_traits<OriginalVector>::scalar_type scalar_type;
    static int const rows=1;
    static int const cols=vec_traits<OriginalVector>::dim;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row==0);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return vec_traits<OriginalVector>::template read_element<Col>(reinterpret_cast<OriginalVector const &>(x));
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row==0);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return vec_traits<OriginalVector>::template write_element<Col>(reinterpret_cast<OriginalVector &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row==0);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return vec_traits<OriginalVector>::read_element_idx(col,reinterpret_cast<OriginalVector const &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix & x )
        {
        BOOST_QVM_ASSERT(row==0);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<cols);
        return vec_traits<OriginalVector>::write_element_idx(col,reinterpret_cast<OriginalVector &>(x));
        }
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat<qvm_detail::row_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat2<qvm_detail::row_mat_<OriginalVector>,qvm_detail::row_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::row_mat_<A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
row_mat( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::row_mat_<A> const &>(a);
    }

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::row_mat_<A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
row_mat( A & a )
    {
    return reinterpret_cast<typename qvm_detail::row_mat_<A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class OriginalVector>
    class
    translation_mat_
        {
        translation_mat_( translation_mat_ const & );
        translation_mat_ & operator=( translation_mat_ const & );
        ~translation_mat_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        translation_mat_ &
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

    template <class M,int Row,int Col,bool TransCol=(Col==mat_traits<M>::cols-1)>
    struct read_translation_matat;

    template <class OriginalVector,int Row,int Col,bool TransCol>
    struct
    read_translation_matat<translation_mat_<OriginalVector>,Row,Col,TransCol>
        {
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        typename mat_traits< translation_mat_<OriginalVector> >::scalar_type
        f( translation_mat_<OriginalVector> const & )
            {
            return scalar_traits<typename mat_traits< translation_mat_<OriginalVector> >::scalar_type>::value(0);
            }
        };

    template <class OriginalVector,int D>
    struct
    read_translation_matat<translation_mat_<OriginalVector>,D,D,false>
        {
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        typename mat_traits< translation_mat_<OriginalVector> >::scalar_type
        f( translation_mat_<OriginalVector> const & )
            {
            return scalar_traits<typename mat_traits< translation_mat_<OriginalVector> >::scalar_type>::value(1);
            }
        };

    template <class OriginalVector,int D>
    struct
    read_translation_matat<translation_mat_<OriginalVector>,D,D,true>
        {
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        typename mat_traits< translation_mat_<OriginalVector> >::scalar_type
        f( translation_mat_<OriginalVector> const & )
            {
            return scalar_traits<typename mat_traits< translation_mat_<OriginalVector> >::scalar_type>::value(1);
            }
        };

    template <class OriginalVector,int Row,int Col>
    struct
    read_translation_matat<translation_mat_<OriginalVector>,Row,Col,true>
        {
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        typename mat_traits< translation_mat_<OriginalVector> >::scalar_type
        f( translation_mat_<OriginalVector> const & x )
            {
            return vec_traits<OriginalVector>::template read_element<Row>(reinterpret_cast<OriginalVector const &>(x));
            }
        };
    }

template <class OriginalVector>
struct
mat_traits< qvm_detail::translation_mat_<OriginalVector> >
    {
    typedef qvm_detail::translation_mat_<OriginalVector> this_matrix;
    typedef typename vec_traits<OriginalVector>::scalar_type scalar_type;
    static int const rows=vec_traits<OriginalVector>::dim+1;
    static int const cols=vec_traits<OriginalVector>::dim+1;

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
        return qvm_detail::read_translation_matat<qvm_detail::translation_mat_<OriginalVector>,Row,Col>::f(x);
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col==cols-1);
        BOOST_QVM_STATIC_ASSERT(Col!=Row);
        return vec_traits<OriginalVector>::template write_element<Row>(reinterpret_cast<OriginalVector &>(x));
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
        return
            row==col?
                scalar_traits<scalar_type>::value(1):
                (col==cols-1?
                    vec_traits<OriginalVector>::read_element_idx(row,reinterpret_cast<OriginalVector const &>(x)):
                    scalar_traits<scalar_type>::value(0));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(col==cols-1);
        BOOST_QVM_ASSERT(col!=row);
        return vec_traits<OriginalVector>::write_element_idx(row,reinterpret_cast<OriginalVector &>(x));
        }
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat<qvm_detail::translation_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat2<qvm_detail::translation_mat_<OriginalVector>,qvm_detail::translation_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::translation_mat_<A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
translation_mat( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::translation_mat_<A> const &>(a);
    }

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::translation_mat_<A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
translation_mat( A & a )
    {
    return reinterpret_cast<typename qvm_detail::translation_mat_<A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <class OriginalVector>
    class
    diag_mat_
        {
        diag_mat_( diag_mat_ const & );
        diag_mat_ & operator=( diag_mat_ const & );
        ~diag_mat_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        diag_mat_ &
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

template <class OriginalVector>
struct
mat_traits< qvm_detail::diag_mat_<OriginalVector> >
    {
    typedef qvm_detail::diag_mat_<OriginalVector> this_matrix;
    typedef typename vec_traits<OriginalVector>::scalar_type scalar_type;
    static int const rows=vec_traits<OriginalVector>::dim;
    static int const cols=vec_traits<OriginalVector>::dim;

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
        return Row==Col?vec_traits<OriginalVector>::template read_element<Row>(reinterpret_cast<OriginalVector const &>(x)):scalar_traits<scalar_type>::value(0);
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Row==Col);
        return vec_traits<OriginalVector>::template write_element<Row>(reinterpret_cast<OriginalVector &>(x));
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
        return row==col?vec_traits<OriginalVector>::read_element_idx(row,reinterpret_cast<OriginalVector const &>(x)):scalar_traits<scalar_type>::value(0);
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<rows);
        BOOST_QVM_ASSERT(row==col);
        return vec_traits<OriginalVector>::write_element_idx(row,reinterpret_cast<OriginalVector &>(x));
        }
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat<qvm_detail::diag_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class OriginalVector,int R,int C>
struct
deduce_mat2<qvm_detail::diag_mat_<OriginalVector>,qvm_detail::diag_mat_<OriginalVector>,R,C>
    {
    typedef mat<typename vec_traits<OriginalVector>::scalar_type,R,C> type;
    };

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::diag_mat_<A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
diag_mat( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::diag_mat_<A> const &>(a);
    }

template <class A>
typename enable_if_c<
    is_vec<A>::value,
    qvm_detail::diag_mat_<A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
diag_mat( A & a )
    {
    return reinterpret_cast<typename qvm_detail::diag_mat_<A> &>(a);
    }

} }

#endif

/* map_vec_mat.hpp
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
*/
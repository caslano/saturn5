#ifndef BOOST_QVM_MAP_MAT_MAT_HPP_INCLUDED
#define BOOST_QVM_MAP_MAT_MAT_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/deduce_mat.hpp>
#include <boost/qvm/assert.hpp>
#include <boost/qvm/enable_if.hpp>
#include <boost/qvm/detail/transp_impl.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <int Row,class OriginalMatrix>
    class
    del_row_
        {
        del_row_( del_row_ const & );
        del_row_ & operator=( del_row_ const & );
        ~del_row_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        del_row_ &
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

template <int I,class OriginalMatrix>
struct
mat_traits< qvm_detail::del_row_<I,OriginalMatrix> >
    {
    typedef qvm_detail::del_row_<I,OriginalMatrix> this_matrix;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const rows=mat_traits<OriginalMatrix>::rows-1;
    static int const cols=mat_traits<OriginalMatrix>::cols;

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
        return mat_traits<OriginalMatrix>::template read_element<Row+(Row>=I),Col>(reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::template write_element<Row+(Row>=I),Col>(reinterpret_cast<OriginalMatrix &>(x));
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
        return mat_traits<OriginalMatrix>::read_element_idx(row+(row>=I),col,reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::write_element_idx(row+(row>=I),col,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::del_row_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::del_row_<J,OriginalMatrix>,qvm_detail::del_row_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int Row,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::del_row_<Row,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
del_row( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::del_row_<Row,A> const &>(a);
    }

template <int Row,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::del_row_<Row,A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
del_row( A & a )
    {
    return reinterpret_cast<typename qvm_detail::del_row_<Row,A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Col,class OriginalMatrix>
    class
    del_col_
        {
        del_col_( del_col_ const & );
        del_col_ & operator=( del_col_ const & );
        ~del_col_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        del_col_ &
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

template <int J,class OriginalMatrix>
struct
mat_traits< qvm_detail::del_col_<J,OriginalMatrix> >
    {
    typedef qvm_detail::del_col_<J,OriginalMatrix> this_matrix;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const rows=mat_traits<OriginalMatrix>::rows;
    static int const cols=mat_traits<OriginalMatrix>::cols-1;

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
        return mat_traits<OriginalMatrix>::template read_element<Row,Col+(Col>=J)>(reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::template write_element<Row,Col+(Col>=J)>(reinterpret_cast<OriginalMatrix &>(x));
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
        return mat_traits<OriginalMatrix>::read_element_idx(row,col+(col>=J),reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::write_element_idx(row,col+(col>=J),reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::del_col_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::del_col_<J,OriginalMatrix>,qvm_detail::del_col_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int Col,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::del_col_<Col,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
del_col( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::del_col_<Col,A> const &>(a);
    }

template <int Col,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::del_col_<Col,A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
del_col( A & a )
    {
    return reinterpret_cast<typename qvm_detail::del_col_<Col,A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Row,int Col,class OriginalMatrix>
    class
    del_row_col_
        {
        del_row_col_( del_row_col_ const & );
        ~del_row_col_();

        public:

        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        del_row_col_ &
        operator=( del_row_col_ const & x )
            {
            assign(*this,x);
            return *this;
            }

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        del_row_col_ &
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

template <int I,int J,class OriginalMatrix>
struct
mat_traits< qvm_detail::del_row_col_<I,J,OriginalMatrix> >
    {
    typedef qvm_detail::del_row_col_<I,J,OriginalMatrix> this_matrix;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const rows=mat_traits<OriginalMatrix>::rows-1;
    static int const cols=mat_traits<OriginalMatrix>::cols-1;

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
        return mat_traits<OriginalMatrix>::template read_element<Row+(Row>=I),Col+(Col>=J)>(reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::template write_element<Row+(Row>=I),Col+(Col>=J)>(reinterpret_cast<OriginalMatrix &>(x));
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
        return mat_traits<OriginalMatrix>::read_element_idx(row+(row>=I),col+(col>=J),reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::write_element_idx(row+(row>=I),col+(col>=J),reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <int I,int J,class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::del_row_col_<I,J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int I,int J,class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::del_row_col_<I,J,OriginalMatrix>,qvm_detail::del_row_col_<I,J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int Row,int Col,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::del_row_col_<Row,Col,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
del_row_col( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::del_row_col_<Row,Col,A> const &>(a);
    }

template <int Row,int Col,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::del_row_col_<Row,Col,A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
del_row_col( A & a )
    {
    return reinterpret_cast<typename qvm_detail::del_row_col_<Row,Col,A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Row,class OriginalMatrix>
    class
    neg_row_
        {
        neg_row_( neg_row_ const & );
        neg_row_ & operator=( neg_row_ const & );
        ~neg_row_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        neg_row_ &
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

template <int I,class OriginalMatrix>
struct
mat_traits< qvm_detail::neg_row_<I,OriginalMatrix> >
    {
    typedef qvm_detail::neg_row_<I,OriginalMatrix> this_matrix;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const rows=mat_traits<OriginalMatrix>::rows;
    static int const cols=mat_traits<OriginalMatrix>::cols;

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
        return Row==I ?
            -mat_traits<OriginalMatrix>::template read_element<Row,Col>(reinterpret_cast<OriginalMatrix const &>(x)) :
            mat_traits<OriginalMatrix>::template read_element<Row,Col>(reinterpret_cast<OriginalMatrix const &>(x));
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
        return row==I?
            -mat_traits<OriginalMatrix>::read_element_idx(row,col,reinterpret_cast<OriginalMatrix const &>(x)) :
            mat_traits<OriginalMatrix>::read_element_idx(row,col,reinterpret_cast<OriginalMatrix const &>(x));
        }
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::neg_row_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::neg_row_<J,OriginalMatrix>,qvm_detail::neg_row_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int Row,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::neg_row_<Row,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
neg_row( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::neg_row_<Row,A> const &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Col,class OriginalMatrix>
    class
    neg_col_
        {
        neg_col_( neg_col_ const & );
        neg_col_ & operator=( neg_col_ const & );
        ~neg_col_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        neg_col_ &
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

template <int J,class OriginalMatrix>
struct
mat_traits< qvm_detail::neg_col_<J,OriginalMatrix> >
    {
    typedef qvm_detail::neg_col_<J,OriginalMatrix> this_matrix;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const rows=mat_traits<OriginalMatrix>::rows;
    static int const cols=mat_traits<OriginalMatrix>::cols;

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
        return Col==J?
            -mat_traits<OriginalMatrix>::template read_element<Row,Col>(reinterpret_cast<OriginalMatrix const &>(x)) :
            mat_traits<OriginalMatrix>::template read_element<Row,Col>(reinterpret_cast<OriginalMatrix const &>(x));
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
        return col==J?
            -mat_traits<OriginalMatrix>::read_element_idx(row,col,reinterpret_cast<OriginalMatrix const &>(x)) :
            mat_traits<OriginalMatrix>::read_element_idx(row,col,reinterpret_cast<OriginalMatrix const &>(x));
        }
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::neg_col_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int J,class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::neg_col_<J,OriginalMatrix>,qvm_detail::neg_col_<J,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int Col,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::neg_col_<Col,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
neg_col( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::neg_col_<Col,A> const &>(a);
    }

////////////////////////////////////////////////

template <class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::transposed_<A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
transposed( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::transposed_<A> const &>(a);
    }

template <class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::transposed_<A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
transposed( A & a )
    {
    return reinterpret_cast<typename qvm_detail::transposed_<A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Row1,int Row2,class OriginalMatrix>
    class
    swap_rows_
        {
        swap_rows_( swap_rows_ const & );
        swap_rows_ & operator=( swap_rows_ const & );
        ~swap_rows_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        swap_rows_ &
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

template <int R1,int R2,class OriginalMatrix>
struct
mat_traits< qvm_detail::swap_rows_<R1,R2,OriginalMatrix> >
    {
    typedef qvm_detail::swap_rows_<R1,R2,OriginalMatrix> this_matrix;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const rows=mat_traits<OriginalMatrix>::rows;
    static int const cols=mat_traits<OriginalMatrix>::cols;

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
        return mat_traits<OriginalMatrix>::template read_element<(Row==R1 && R1!=R2)*R2+(Row==R2 && R1!=R2)*R1+((Row!=R1 && Row!=R2) || R1==R2)*Row,Col>(reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::template write_element<(Row==R1 && R1!=R2)*R2+(Row==R2 && R1!=R2)*R1+((Row!=R1 && Row!=R2) || R1==R2)*Row,Col>(reinterpret_cast<OriginalMatrix &>(x));
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
        return mat_traits<OriginalMatrix>::read_element_idx(row==R1?R2:row==R2?R1:row,col,reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::write_element_idx(row==R1?R2:row==R2?R1:row,col,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <int R1,int R2,class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::swap_rows_<R1,R2,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int R1,int R2,class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::swap_rows_<R1,R2,OriginalMatrix>,qvm_detail::swap_rows_<R1,R2,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int R1,int R2,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::swap_rows_<R1,R2,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
swap_rows( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::swap_rows_<R1,R2,A> const &>(a);
    }

template <int R1,int R2,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::swap_rows_<R1,R2,A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
swap_rows( A & a )
    {
    return reinterpret_cast<typename qvm_detail::swap_rows_<R1,R2,A> &>(a);
    }

////////////////////////////////////////////////

namespace
qvm_detail
    {
    template <int Row1,int Row2,class OriginalMatrix>
    class
    swap_cols_
        {
        swap_cols_( swap_cols_ const & );
        swap_cols_ & operator=( swap_cols_ const & );
        ~swap_cols_();

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        swap_cols_ &
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

template <int C1,int C2,class OriginalMatrix>
struct
mat_traits< qvm_detail::swap_cols_<C1,C2,OriginalMatrix> >
    {
    typedef qvm_detail::swap_cols_<C1,C2,OriginalMatrix> this_matrix;
    typedef typename mat_traits<OriginalMatrix>::scalar_type scalar_type;
    static int const rows=mat_traits<OriginalMatrix>::rows;
    static int const cols=mat_traits<OriginalMatrix>::cols;

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
        return mat_traits<OriginalMatrix>::template read_element<Row,(Col==C1 && C1!=C2)*C2+(Col==C2 && C1!=C2)*C1+((Col!=C1 && Col!=C2) || C1==C2)*Col>(reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::template write_element<Row,(Col==C1 && C1!=C2)*C2+(Col==C2 && C1!=C2)*C1+((Col!=C1 && Col!=C2) || C1==C2)*Col>(reinterpret_cast<OriginalMatrix &>(x));
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
        return mat_traits<OriginalMatrix>::read_element_idx(row,col==C1?C2:col==C2?C1:col,reinterpret_cast<OriginalMatrix const &>(x));
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
        return mat_traits<OriginalMatrix>::write_element_idx(row,col==C1?C2:col==C2?C1:col,reinterpret_cast<OriginalMatrix &>(x));
        }
    };

template <int C1,int C2,class OriginalMatrix,int R,int C>
struct
deduce_mat<qvm_detail::swap_cols_<C1,C2,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int C1,int C2,class OriginalMatrix,int R,int C>
struct
deduce_mat2<qvm_detail::swap_cols_<C1,C2,OriginalMatrix>,qvm_detail::swap_cols_<C1,C2,OriginalMatrix>,R,C>
    {
    typedef mat<typename mat_traits<OriginalMatrix>::scalar_type,R,C> type;
    };

template <int C1,int C2,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::swap_cols_<C1,C2,A> const &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
swap_cols( A const & a )
    {
    return reinterpret_cast<typename qvm_detail::swap_cols_<C1,C2,A> const &>(a);
    }

template <int C1,int C2,class A>
typename enable_if_c<
    is_mat<A>::value,
    qvm_detail::swap_cols_<C1,C2,A> &>::type
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
swap_cols( A & a )
    {
    return reinterpret_cast<typename qvm_detail::swap_cols_<C1,C2,A> &>(a);
    }

} }

#endif

/* map_mat_mat.hpp
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
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
NL4jlPQRNCGuNd1zoes7sYRYlrXMpa7qA46Cb25u7pXbPLzmO3JHpPcercRD7+V6ykf68Xf0+1EEV29aOr4gEjqIvdDKEavuW1QrVyQQDxl7L4l7U1dWmkctfHyAFwWKT3+/Dv6R63nQNO9Tm4atT1+Ust7q7SuaCQX4kp2wwrkNhR+maY6cihypAzyaz2eXTJjdxmnmO0satq8hVXyN/hZhK4nGjy1H1Tah5O3nTYSgK7X7bmMJIfQQkAq9XtMOTycJw6zZlPBSu+eNJ3Oj1z1Psmea4pBq1fNhvULXnx6BhKenQ+h2PZM9Vq51suTm+cnF1XxxOUtOasazq+vFIbDrYWjqByTzyIeG+4xRJj+ikfnOG4fnDk1TJHWHhoLKY4nUKwJymgtYetvEEgAd4bTQ5YRRmz5w+mNNhyLpsAsqxgT+BKDDPlBQd7oiHQmIypThycdX1/PLq/cdNhUCN7T8JHzS2RuKik2hqH2QwBvETXdaylvssM5fVNBa/WjSo8sqAqgL6TygqyaD/d77T6Ey8jyoeTXxdqOVrfeP4lF0JrJxPlwu+9EQ8wHGo7NlXwxH/ZFYBv9T+YCp/B0Fz71lcV8b/RWNaMz72MfReBANnuWDfnzGT8dZJuLxGRdRJB7wRtOwtXoaHv0f
*/
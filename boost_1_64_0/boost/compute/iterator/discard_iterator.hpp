//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_DISCARD_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_DISCARD_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for discard_iterator
class discard_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for discard_iterator
struct discard_iterator_base
{
    typedef ::boost::iterator_facade<
        ::boost::compute::discard_iterator,
        void,
        ::std::random_access_iterator_tag,
        void *
    > type;
};

template<class IndexExpr>
struct discard_iterator_index_expr
{
    typedef void result_type;

    discard_iterator_index_expr(const IndexExpr &expr)
        : m_expr(expr)
    {
    }

    IndexExpr m_expr;
};

template<class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const discard_iterator_index_expr<IndexExpr> &expr)
{
    (void) expr;

    return kernel;
}

} // end detail namespace

/// \class discard_iterator
/// \brief An iterator which discards all values written to it.
///
/// \see make_discard_iterator(), constant_iterator
class discard_iterator : public detail::discard_iterator_base::type
{
public:
    typedef detail::discard_iterator_base::type super_type;
    typedef super_type::reference reference;
    typedef super_type::difference_type difference_type;

    discard_iterator(size_t index = 0)
        : m_index(index)
    {
    }

    discard_iterator(const discard_iterator &other)
        : m_index(other.m_index)
    {
    }

    discard_iterator& operator=(const discard_iterator &other)
    {
        if(this != &other){
            m_index = other.m_index;
        }

        return *this;
    }

    ~discard_iterator()
    {
    }

    /// \internal_
    template<class Expr>
    detail::discard_iterator_index_expr<Expr>
    operator[](const Expr &expr) const
    {
        return detail::discard_iterator_index_expr<Expr>(expr);
    }

private:
    friend class ::boost::iterator_core_access;

    /// \internal_
    reference dereference() const
    {
        return 0;
    }

    /// \internal_
    bool equal(const discard_iterator &other) const
    {
        return m_index == other.m_index;
    }

    /// \internal_
    void increment()
    {
        m_index++;
    }

    /// \internal_
    void decrement()
    {
        m_index--;
    }

    /// \internal_
    void advance(difference_type n)
    {
        m_index = static_cast<size_t>(static_cast<difference_type>(m_index) + n);
    }

    /// \internal_
    difference_type distance_to(const discard_iterator &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    size_t m_index;
};

/// Returns a new discard_iterator with \p index.
///
/// \param index the index of the iterator
///
/// \return a \c discard_iterator at \p index
inline discard_iterator make_discard_iterator(size_t index = 0)
{
    return discard_iterator(index);
}

/// internal_ (is_device_iterator specialization for discard_iterator)
template<>
struct is_device_iterator<discard_iterator> : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_DISCARD_ITERATOR_HPP

/* discard_iterator.hpp
b+qCdfiGgjZcmBW00/KGi+iztaekaseS7Cb7Xirb8fDkg+p2vP6+sh3p/3fb8cq4oBw22pFvw++ddrzFdtA67Xi9RrPb8d07GhrVSuO53672906f7Wlpdju+WqP1tePjb9DS7XbcuhHRRDsSrdOO6nz3joOyzWSDkUzcQ/1NyDzU1LRty4PbQJM1hY0Ov2u1NMYe6KqW2AOROz/RRD0PdWu5X6vTXyV/fQ69uejrIPBnsuAxMye8OPAfmQfq3vgGNPeloEOHp2bOmLm//zIuuVbPnBbEwYpYe1R7A/PnGjOYOw2AIeNPNX3uajL+qDCn5wCQ4/Y6OvtceLoYtydONPfcQjkOB+Sp9DT65rrNMG7/UMuZH9QyQFvb0dAgH7QDe0AbDpTyFuW8gmb28RPOTBFMx5VPeW5FruX6N+P7Lo8L1MljRw5RufTcTkTZ03Xrnt06plmZBqIgiSybvd3TzdwmVVTxLAuCa90PrA9n5X7gjtoY+H1brnDvMuKz+eMNfY2uikVsHPofidXu0LfbGLk+KFRb91NPt++inMzh8TXn4FF1N/z4f9epGx0an3r4iGxbzCPg9PoBKfav24Td6tjNxsbHRMAnKkk9V9frf9Bq+zxK88TJr9lm1NT/Vlr9fyvqpWJ7Q3ftUL+jDlrOx52CNlgR+UxnxLvRQ9pd5R5BG13/y1tm/YukyIsovOZ7+qb+99Hq/xvUX0Xx96aDaZW4nsjAfnC7xOKbetCo50e3zHES8UqEzLvmXLloZ9INT70brS1Snrg0HTRvILCf+3Vn/Aj/qUMznFTJA7CmXRU3s3z2zCF9L/WtXTUe3wqoFmNxTx8G4tAWa1ZbcJowaVF5/39btH32K1GuiowKn45txu/Soo2z5lNFHcSYWhPqaHmwsUDfoebMv/fSnBk8dU3SpG4kFS8jmi+JFQnv/Z6mf0fB8thxM5f/33MfMbGfZsUTSPIwqLKIERDdtEyTxPKxftabtmu+ya6XBGmRxkzOJHX4Ottgv6iX8SDu53EmosxQDUlt1GBgD5waM86KYRry0Bc++PAjB/ZrQi6wQRKVfpxVbHUwu9bBfs/AFo4TOYkXstXZQRf7UwObll4RJHnBtkgNA9vY6I/+YIf2prGKPVdGI1sbWjHaLhvt7DAvIVwQu7KdCT0znF3aWGr9uhETbsvki0Ke8dwJJR+NFFrgZk7j0Zj2ntbg85hfBF5JLanzrW2eHmytmf7HU1uW738eZU4eCDY5obQYTvDxjk2eigdB6mY1j2jgPp6TW6afsxeWSZgXLQ8laRssSTZ5lr3hLfrnzwPEGaW+r/eKEzNt1gKRectbWF2cg80Cdo2/t/gT8pGQwLY3/FLm2J00mXOLa+KoGdSbmcF8RqVrQu9J+J09eIjVcLcegYO5Qu19f0JntDoVSV3nY+DT6ywrgTo/HJhR7YAipExvhExCQebp/90ODVziB1evQ9scqj0We+Tj0zS5S/+jHrrgO2q5w345Xu9RoMrmQSdbn6DLsUSDCklPsEf44jaTTjUC7dQOk0bnb8jd2N2hiQM66PM30unYP4N+4cY6HXtolB3v0+nSygLeAzcDrZ3p+r5nv06XGw7wfuuWoOkbH5zZzh/ooYvMHfQ3fW/19tsJnIxuMLNxevOMvneKn2rtXaM0jqprTr+sli9z73RpxJ5CPNWfOdRiN7b9D+xhGmu4cwBW3+takgmP+4b/iSfp6GOyyQk8Peoip40VlZxr8JSWfoubdOln9XzZN+3SF4fSog0Z1/dglrRxtrGvS18enm7LuFmXPiSXjTktp9ZvRmJoXG60/X5xU+/3kLniVbnPabWgzqYDxHWToqXI/O0fum6SmlE=
*/
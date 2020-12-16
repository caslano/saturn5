//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_COUNTING_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_COUNTING_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for counting_iterator<T>
template<class T> class counting_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for counting_iterator<T>
template<class T>
class counting_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::counting_iterator<T>,
        T,
        ::std::random_access_iterator_tag
    > type;
};

template<class T, class IndexExpr>
struct counting_iterator_index_expr
{
    typedef T result_type;

    counting_iterator_index_expr(const T init, const IndexExpr &expr)
        : m_init(init),
          m_expr(expr)
    {
    }

    const T m_init;
    const IndexExpr m_expr;
};

template<class T, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const counting_iterator_index_expr<T, IndexExpr> &expr)
{
    return kernel << '(' << expr.m_init << '+' << expr.m_expr << ')';
}

} // end detail namespace

/// \class counting_iterator
/// \brief The counting_iterator class implements a counting iterator.
///
/// A counting iterator returns an internal value (initialized with \p init)
/// which is incremented each time the iterator is incremented.
///
/// For example, this could be used to implement the iota() algorithm in terms
/// of the copy() algorithm by copying from a range of counting iterators:
///
/// \snippet test/test_counting_iterator.cpp iota_with_copy
///
/// \see make_counting_iterator()
template<class T>
class counting_iterator : public detail::counting_iterator_base<T>::type
{
public:
    typedef typename detail::counting_iterator_base<T>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;

    counting_iterator(const T &init)
        : m_init(init)
    {
    }

    counting_iterator(const counting_iterator<T> &other)
        : m_init(other.m_init)
    {
    }

    counting_iterator<T>& operator=(const counting_iterator<T> &other)
    {
        if(this != &other){
            m_init = other.m_init;
        }

        return *this;
    }

    ~counting_iterator()
    {
    }

    size_t get_index() const
    {
        return 0;
    }

    template<class Expr>
    detail::counting_iterator_index_expr<T, Expr>
    operator[](const Expr &expr) const
    {
        return detail::counting_iterator_index_expr<T, Expr>(m_init, expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return m_init;
    }

    bool equal(const counting_iterator<T> &other) const
    {
        return m_init == other.m_init;
    }

    void increment()
    {
        m_init++;
    }

    void decrement()
    {
        m_init--;
    }

    void advance(difference_type n)
    {
        m_init += static_cast<T>(n);
    }

    difference_type distance_to(const counting_iterator<T> &other) const
    {
        return difference_type(other.m_init) - difference_type(m_init);
    }

private:
    T m_init;
};

/// Returns a new counting_iterator starting at \p init.
///
/// \param init the initial value
///
/// \return a counting_iterator with \p init.
///
/// For example, to create a counting iterator which returns unsigned integers
/// and increments from one:
/// \code
/// auto iter = make_counting_iterator<uint_>(1);
/// \endcode
template<class T>
inline counting_iterator<T> make_counting_iterator(const T &init)
{
    return counting_iterator<T>(init);
}

/// \internal_ (is_device_iterator specialization for counting_iterator)
template<class T>
struct is_device_iterator<counting_iterator<T> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_COUNTING_ITERATOR_HPP

/* counting_iterator.hpp
cHjLauPEpbjaWgB3v539OLWFAO5rPTgxniVYwz1rVw9uc2VGvozTcGu7u7ghvtfc09u4zZW6ULwF7cHUGZ8lDvrv9TdocU0Sbrr1xHxZ0GIoPmW4Ku6zQXv5jpa2PKC0Xk9t59KVV5hzKS7crIqD5FrnksiqyFSO8I/RuG7T3zheJu6v6PdjtEee8VbXSe1s0GNuUjp0y3ViMLs+t3CCaurVwy/cXFHKCO8LxVvP8UYi3QPPDwZrMnWJtqZtszFSwUHGT7f30mfWNtYhY36njdk09hLTu0x6k6cHe8PdXbp4rKvLuGJiMJaxj95j0lWCIZTxvBvadHoqLb0btHX4RgYG8wDvZi06ruT1fdNeG7O5bHyHTadre72MV9+4S7e/dcdNTQziMjXz1abT5NLn3+f2dekiIrf0gxBycMaycQuLZza08/J+i67mDex7N7fomytKQitj6hYmprGCoL1s+jMG66vafuP6Wwq69DekaCb1yELcU2tuVm5S8Mi/5vfuw/W16w5r9/F/1uUdKt2g9FwvEW89M9xR34rulTjNYyb9S04/6Kh04KnXxZ13lDl9ThzndULktafNt0l/1Lq3t8WcLZFmqObf1+XXshnVmFub/MK9tJWi9MxtCKMLaXjv0JXf8KJ+dzbko3TJf4/esvF9Mt/DvQhTA2p59zN4gJbr9eOO1NhHuc6JQNX9AYTXC2jqfqhbttE2OG/Qv/8ch1SJMda6cZNO6/AhekcvG8TYc+/s4BoYynrhLgOD3EbIC3cjg27cr+27cU3DYyDp3rxI0tu6fm//CMyMW6o9OfKgEw5dpt9x/Fmj4XmoRn/YAY2+tjQ7R8lgVzT6qduCPtggjMxfp+nUPbeXdHvIgv9ily61Lu4H79ChD2VB2rli+o69GDI7aLEG79SLGT5VtGcj5y4jMHV74g7Mv6vA4Z0xfr8sfxcqSAqA3HN3F78P/2fOuLvfw8b15/74l8J1R3sr68337MEg616Lu/5efTgsbCjzwMEenJUn5KN9GCu/xsvvDYw+HEG/330MOmoM2/p9DXpvTME3mxgjpuDU/UyaHTNwz/1Bt4as1ma9mG7bfuQBfbhu2979gT041bbIr9KLweYAst490YOz+uBZhyRmfQ2Aesd2K8RNFPQNkry6TCsYfr/7g+rfN1bpV21/fOc/j9G6eHpl5uz6Kh2ZDk0cPgralEWbPPIg0LhJOzxxdAq0BZN2ZOLBh0E7Z9KOThxrZb7epD3o0NG2Lh80aVOHjh3GefpzoNXRmilZ8yEKjwj6xS59ckyjX+nSD+t3FfwVhn07Kt2qcjgTdejYkE8a2CKOfOFTwMS3dLCnDKzPuZu5EWeiTTrYBQNb+Z6fhrHLRNt2sGtWfausylyPiT7qYLfM+pZhEuY8Z6Kvu/ZxE5vGXubHBRNjBtiyud+x9m9BlKSpk1xz/BC1f6P+v/HN7nvz3nEKWs84Ba1nnILWM05B6xmnoPWMU9B6x6mkjRynoPeOU9BHj1Oxb3WPUL8/X+xbZT40ucbeVts3/UOujd7s0tyMo+9jjm4zaO6Yfte8w6DNLS3S7Uft4AXM53YbGNJJT22cwFDGv25gYDb18n96Q4O2pZe/9yYNrc4ON+PMUPjOmVLHXLAxLjBtDKt9CqOiHcgWEguIjHivxRi6WYM7q/kBnjX2D+f2E0bbP2CfdnPxO43a+jvE1Qpol0zalmib/dRnDxf3aC8T8ySbPHS43jf/gPZMJ2KH/r94O0jlNu1M//59nChHpo7WsnFXhd9nwkU6R4EmBgNo8uJUt5PotEeuzdMWFGWd26FoolaSB7mI8Ltd1rN2tzRVFvaRY3s02rQIGiqiVho5kkE=
*/
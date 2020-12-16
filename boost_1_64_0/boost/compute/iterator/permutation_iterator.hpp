//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/iterator/detail/get_base_iterator_buffer.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for transform_iterator
template<class ElementIterator, class IndexIterator>
class permutation_iterator;

namespace detail {

// helper class which defines the iterator_adaptor super-class
// type for permutation_iterator
template<class ElementIterator, class IndexIterator>
class permutation_iterator_base
{
public:
    typedef ::boost::iterator_adaptor<
        ::boost::compute::permutation_iterator<ElementIterator, IndexIterator>,
        ElementIterator
    > type;
};

template<class ElementIterator, class IndexIterator, class IndexExpr>
struct permutation_iterator_access_expr
{
    typedef typename std::iterator_traits<ElementIterator>::value_type result_type;

    permutation_iterator_access_expr(const ElementIterator &e,
                                     const IndexIterator &i,
                                     const IndexExpr &expr)
        : m_element_iter(e),
          m_index_iter(i),
          m_expr(expr)
    {
    }

    const ElementIterator m_element_iter;
    const IndexIterator m_index_iter;
    const IndexExpr m_expr;
};

template<class ElementIterator, class IndexIterator, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const permutation_iterator_access_expr<ElementIterator,
                                                                      IndexIterator,
                                                                      IndexExpr> &expr)
{
    return kernel << expr.m_element_iter[expr.m_index_iter[expr.m_expr]];
}

} // end detail namespace

/// \class permutation_iterator
/// \brief The permutation_iterator class provides a permuation iterator
///
/// A permutation iterator iterates over a value range and an index range. When
/// dereferenced, it returns the value from the value range using the current
/// index from the index range.
///
/// For example, to reverse a range using the copy() algorithm and a permutation
/// sequence:
///
/// \snippet test/test_permutation_iterator.cpp reverse_range
///
/// \see make_permutation_iterator()
template<class ElementIterator, class IndexIterator>
class permutation_iterator
    : public detail::permutation_iterator_base<ElementIterator,
                                               IndexIterator>::type
{
public:
    typedef typename
        detail::permutation_iterator_base<ElementIterator,
                                          IndexIterator>::type super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::base_type base_type;
    typedef typename super_type::difference_type difference_type;
    typedef IndexIterator index_iterator;

    permutation_iterator(ElementIterator e, IndexIterator i)
        : super_type(e),
          m_map(i)
    {
    }

    permutation_iterator(const permutation_iterator<ElementIterator,
                                                    IndexIterator> &other)
        : super_type(other),
          m_map(other.m_map)
    {
    }

    permutation_iterator<ElementIterator, IndexIterator>&
    operator=(const permutation_iterator<ElementIterator,
                                         IndexIterator> &other)
    {
        if(this != &other){
            super_type::operator=(other);
            m_map = other.m_map;
        }

        return *this;
    }

    ~permutation_iterator()
    {
    }

    size_t get_index() const
    {
        return super_type::base().get_index();
    }

    const buffer& get_buffer() const
    {
        return detail::get_base_iterator_buffer(*this);
    }

    template<class IndexExpr>
    detail::permutation_iterator_access_expr<ElementIterator,
                                             IndexIterator,
                                             IndexExpr>
    operator[](const IndexExpr &expr) const
    {
        return detail::permutation_iterator_access_expr<ElementIterator,
                                                        IndexIterator,
                                                        IndexExpr>(super_type::base(),
                                                                   m_map,
                                                                   expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

private:
    IndexIterator m_map;
};

/// Returns a permutation_iterator for \p e using indices from \p i.
///
/// \param e the element range iterator
/// \param i the index range iterator
///
/// \return a \c permutation_iterator for \p e using \p i
template<class ElementIterator, class IndexIterator>
inline permutation_iterator<ElementIterator, IndexIterator>
make_permutation_iterator(ElementIterator e, IndexIterator i)
{
    return permutation_iterator<ElementIterator, IndexIterator>(e, i);
}

/// \internal_ (is_device_iterator specialization for permutation_iterator)
template<class ElementIterator, class IndexIterator>
struct is_device_iterator<
    permutation_iterator<ElementIterator, IndexIterator> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP

/* permutation_iterator.hpp
Xj6nqkdRWRWh4oMuA9/hZhzofBUreMWTLNfK0+xAyPOkeBBPUQTUCh2/ZUL07iXanGyosbeIfL6KHzY1P07KMqg0froyoT+tmL4XDb6EidTaheskLZ80J07KBX9AusiyAY492Sw3DcOsjF3UG11SsyF29wGDL2SZSD4eFFmHT6qLQSde/ZTBH7OKFt0yK0ONfzjsVhtr40mDP2A+T0OnrCx2w4CJMb1m8YZOnKQxR9k1HzrKaK8XWu1V+UEoAlW1vGQfX1xqRtXdkdOjU9/E5bmXtnzClIuhbMZtNngj5gd+FhSRwxafsrym5rG8lB0O6pzMT7FyPil+7CNEgPzc9xkUaUc7g/eyxRtmbuJGRcGWZkdN/7bcD4+bMTydvMwcL2TNAtJd28C7Z8ksN82y0kn9RMaGr2+ARI5wCkneBuNGziiDN2NRVGRhULA6ev/pASlv+mK1wNMGatgGLJ1EDP4lKw66H3humjhsxVhGKNek0GNrnTY/tWT2d1DxIA+SSlr35e5pVcwOI9J22Kxjj9huxM4K/cStfJez1TXaTWqp5KE41YK0sbA41NdD6xuSkhepR/2OqSnvqhCJvhPL3foG7oVV6vM6Nn7/N2Av90Gdt2BuTu2XJSFbQxh1ROFbRyy3T43rPImTulFUZewpPTzIJ2/UsaQ1zssKzmMmF2c02NBuMXvNvmTISVnkZnHgBC7TVUF/gyHu955lcx9TFolbRF5lyVDWyadDjK0bJww5Ecs9T0Rc9KV3yhESsLq0dHqW6iESEtD/Nn4WYTP2ijEjp71I7Sjeharc+MMV0jOrp580mBMzd57mj3xU1+xyW73Dl+28NiGtuzyi2OnSPVyLu67HIJ98UMN/fLuRw8VLMuobF+zWur0G/bxsjrsoc8OgCmMw0u5t+OR+XflCgzdknKa+WzgleLEuGeljJt1mHbf6MKuCKnZ834wXr+6eaWDpYpCXwpCRMl4VqcMrV5OBTcTkcHVzfQ71gIzLhoycuYGbB34Y6TKadrCj3yOv0oopI8+zqsiCuE8GFlpLxoQlowx57PlxYcrA6UxvDuiCA2e26/upnKaVG4YOk2dQSwNj7K2YY88teJRnRdDEvkeJxjKt5WAz+F3mZzxKRA4t2/Wi5kOOoxeumDl486CqQkLoXpl2XoTX6zyc5X7uOD7pOtNb01wfPrhi7UHCIq4yqt/q0rxgwu0ilWqX97maF+fkhLtlkufM8O5Q+zWcMVes3BYuFZenKbNdQiw9ftksy/dykdXGA5uWUOzu2FOumnskGjGF63kFmPQWITj2lKvWnjDyqYZhzvrdOzp596ascsMkzTzPq/0G5SShp33o8nad46vWnUWYVY44/3avZzpxPhdWzVj2cZTGCakqecsphxoxWnkltlbNsZk4Fa1YqWsy0X1Rzccavpdb35dWYcZ9J2Wy+5aHM+adDPiut/i8Kg69IEskH4USWTb7A992XucrZUpU7sWimq3VyR6bF0ye3K28OPPAouc9xH78otX+RZolTu4mrGtq6LT/FZ2Xs4JneRyXMXwD0eP6PdOawRMGScx54DPzhtWM9X9Q55nKueOXPK4kS/nIPIcvIc43a1bukqyk/2YRG2U+tfIGn7T4kyBOeVp4bIRZ1ebfMvgTlpPCdX23ZCPMrZ17MYs/zrlIe5za/Cje4v+o/f1lVWYeTWq4TFz9+79lf78fODyKfZN/9PdfsepfuWme5yQI/Ff//gNPMfk97kcVj0vwj/h+5CM0+ENSnKGbi7y1feZk607xpMGbsypPeOh4JRvtrtHJibaly/Ac5oa+XwVFyv6Hy4etk99u1EW86wjKIvJdNtJl3jzLnDf4OQucokg=
*/
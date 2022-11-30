//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_IS_CONTIGUOUS_ITERATOR_HPP
#define BOOST_COMPUTE_DETAIL_IS_CONTIGUOUS_ITERATOR_HPP

#include <vector>
#include <valarray>

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace compute {
namespace detail {

// default = false
template<class Iterator, class Enable = void>
struct _is_contiguous_iterator : public boost::false_type {};

// std::vector<T>::iterator = true
template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename std::vector<typename Iterator::value_type>::iterator
        >::type
    >::type
> : public boost::true_type {};

// std::vector<T>::const_iterator = true
template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename std::vector<typename Iterator::value_type>::const_iterator
        >::type
    >::type
> : public boost::true_type {};

// std::valarray<T>::iterator = true
template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename std::valarray<typename Iterator::value_type>::iterator
        >::type
    >::type
> : public boost::true_type {};

// std::valarray<T>::const_iterator = true
template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename std::valarray<typename Iterator::value_type>::const_iterator
        >::type
    >::type
> : public boost::true_type {};

// T* = true
template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        boost::is_pointer<Iterator>
    >::type
> : public boost::true_type {};

// the is_contiguous_iterator meta-function returns true if Iterator points
// to a range of contiguous values. examples of contiguous iterators are
// std::vector<>::iterator and float*. examples of non-contiguous iterators
// are std::set<>::iterator and std::insert_iterator<>.
//
// the implementation consists of two phases. the first checks that value_type
// for the iterator is not void. this must be done as for many containers void
// is not a valid value_type (ex. std::vector<void>::iterator is not valid).
// after ensuring a non-void value_type, the _is_contiguous_iterator function
// is invoked. it has specializations retuning true for all (known) contiguous
// iterators types and a default value of false.
template<class Iterator, class Enable = void>
struct is_contiguous_iterator :
    public _is_contiguous_iterator<
        typename boost::remove_cv<Iterator>::type
    > {};

// value_type of void = false
template<class Iterator>
struct is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_void<
            typename Iterator::value_type
        >::type
    >::type
> : public boost::false_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_IS_CONTIGUOUS_ITERATOR_HPP

/* is_contiguous_iterator.hpp
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
*/
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
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
9Kv/Df6GSul5WS/ejZHwKm29vI58P+LzMhwAK1FTCe77HXpRrcygQfRy+Ppj9jwHr9+LuB7PyuTh9UvsuYjXv2XXaPMIDns5fL2APS/E64fYdTFe38uu5+D1Dy/RNcHzNbsuIdgirmvvPqPV89xL4XqeeikMw6KXImDDa8+09OSpRexQ6WFRmpkh5Zs8NljcTU4Ou42bRGlGMpr2zaK0F/eP/joLzckGCuiUvBqt+zrOCJ9ksGSv3apNpWqzzlPttF9bLYM25zzV/nLveaqVGGFnvkjEQdUyeGhNuKM3baDrKrxuWqMRja+CAY5K+DMlGoJZyXapTppugsX058OgXwCc+LPAkDorGrcchlvOBZFs+Nlxy6Fqece/80KYgVwv9NLxWdRc3nmae2/meUjpXTkXm7g1qgmRNVFMTVScp4kpZ29C5E0QFtunnzkb+54PiyP3nBcLGjlzpp/RRtEj6wAjiY3YMTu0a9EdKA7mYTntviSYty7y/ZxgVtT93GDqul/HRKLkyMNzx/IzQ34FK0VUnXOuqudS1aMurGqJsRPJpnAzWayZwnM1k0PN7Bx87maywhgUaRVDh2JUT9HryJFN0LJd0tWyTd1GCx6GaZH/fOBnBY/qyl1fUvQexoV/20Z0J+n4StGZSIjzGMRzzgVxMUE8+DwQ552F5hnnqjqVqvYPuiCae1f6EYMvmwgb4sZd0870Qn/x/Bzk
*/
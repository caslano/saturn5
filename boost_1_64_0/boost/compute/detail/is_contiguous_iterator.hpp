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
YTGiHFxa36lxpf/Mg4vph/0b6pf739ofIzacyKHBiBtdWv+4njzi5Lme41eX/N+aGle6rnEmQ4Uec0LXcy51FoSv7zzKtLneDbRDgRZTgjeUNydMON6tf1Bj78bypUCTERsOdmsdJCnRZk79ptolfDN5UKPPgurNPWbJ/i2cT5IyPRYc7NYl6LPiYLfuQIcZSXOotltjYsngWvK3vRyR62iTGBlKdBj/h75Hbyyvm+PDbXPnxdQnS16fGwRvKg7HZEnJpUSXJYsz+z2zz/QFLu7a4W6cElL3/n9qrZbbG4pxI89v+r91FZKUOJJfghwxuQwcE1eTw1vJ1fOF56eeJz2P/dE+ynQYs3dubXJM8/bqcocz+Zu08STGhv+vO9C+tTxu+7+1Gfa4FmlKTDjjNo47FON2xlOs9pE2xCv7nGOLEWvCF/U7dY5JUzp07m4thjYzrub84yPxOeO+2hX/QPzkbm2Gu5GmxNAxayp3xPbwDo6jyKl9S8fs2d/yvLNbTyGlPyvPE2LnOL7f/9aVKNFlQfhQHDrMCN1Wn4mRo8GYq4ldFWN2JfN0txbKnP0z+UweZX1sUzTHxtf29fGucrz7/9ZQaJHZrbcQuMf/1mfY87h2b/32OEGBAQuu5rVjKnQJiBWlyYQj8UqMWJG8u/1cSezje8mTjtgjonJLUaTJiDWXMh8PSVBgJPcFoYuZKxyTpkqXGYEDfyvkbtrJ0WDMqXaOYv/5Om0MPR/d03URVSf6zLmUnKa7NRquRmS39sLlYs7Rp5R+7N/deHKpe6odJ+RpsuUgqh2SxMRYcSMxYmTpk4qp6S3/dy/48VMcK9/gbr2IHB3mjgvs1nFoG6/F9c8aaDKgSOEB3vevfdb/rgla97hL5IHmIk36LHbrKUyvftbA5AH/W3OhxPoBcrK9kteOKNCnTuBEPrYzDk7MM47JUaPHnOtd/qw+B+E95cHqwyEJ8jQYEn6I44hyelZflzk+mzFjeckz+/ph3Jhxs4fKj7ljtxx4XCGzW3Ogy4zQY/WRgdcCPXWxzdJiLyFf7kaaIm3G3Gi3PkLwMfLliCR5mgxZUNitVbBOyP9h5gFRstTos9it5XA17kaGCl1mBB6hDc4gSZE2E7YcJL1GggJNRqyJPFL8R5lnKX145P/WVynt1nLYe7R+sPpPvR2TJul5hTNS6sfykWLYv/c4teBQX2ZcjT6t7wUDVa8PHu35Q/B49ej/rYVRJfFE/WTGpTiDHF22hDNicUiCHBXajFgSfJJzuRlxspRoMmDOlv3d+ghRUq6DAnUGLAlljQsrIrt1Di6X1TYpSrS4mf0nNLnZVT0mR50+c0JXM985IkWRFiNWRK4uF6KcUqXLjID30GnSzy2P9LMMcfI0GbPlcn4OOiZDhR7X262pm6FMhxnBvp+XOKYQ097TtYd1F3wWTD4kcvrxbPtJ/pur+49P9ZsDAP6ge4UQQgghhGEYhuFi+OL6fTEMF8MwDMMQQhiGEMIQQgghhBBCCCGEMIQQQgj58fbjDy9er7fz9DzPOedzPufUtr517rPF8Tw5I3dgbM83Nk6/wDy/0Bpk+iJzszDnnOGc8/q9l0PqDJgRC/u9l9PscEiNHjMOL+41mB6NK6jHgtQV/S7NFjlKNBmyIOmz1qfYYmYcif/ZKyJLmTZzkk8XH3sUaTMm8gzxs0GWCinP8a72DuQjkIvoSz0HyMlJLKsPagxIun6KDA2GLEg+y5phlwINBgTaSLJOmQ5TojlzQelAHTmOvlg8HlfpMSPxHH2zxSFV+sxZfq51zwE1hoSfp03OkqdB05yPiBjfGTKUiR8YB2dpMaZjvuekxFOkxYglc79LkSZjYoc=
*/
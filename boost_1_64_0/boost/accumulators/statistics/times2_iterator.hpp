///////////////////////////////////////////////////////////////////////////////
// times2_iterator.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TIMES2_ITERATOR_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_TIMES2_ITERATOR_HPP_DE_01_01_2006

#include <functional>
#include <boost/detail/workaround.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    typedef transform_iterator<
#ifdef BOOST_NO_CXX98_BINDERS
        decltype(std::bind(std::multiplies<std::size_t>(), 2, std::placeholders::_1))
#else
        std::binder1st<std::multiplies<std::size_t> >
#endif
      , counting_iterator<std::size_t>
    > times2_iterator;

    inline times2_iterator make_times2_iterator(std::size_t i)
    {
        return make_transform_iterator(
            make_counting_iterator(i)
#ifdef BOOST_NO_CXX98_BINDERS
          , std::bind(std::multiplies<std::size_t>(), 2, std::placeholders::_1)
#else
          , std::bind1st(std::multiplies<std::size_t>(), 2)
#endif
        );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // lvalue_index_iterator
    template<typename Base>
    struct lvalue_index_iterator
      : Base
    {
        lvalue_index_iterator()
          : Base()
        {}

        lvalue_index_iterator(Base base)
          : Base(base)
        {
        }

        typename Base::reference operator [](typename Base::difference_type n) const
        {
            return *(*this + n);
        }
    };
} // namespace detail

}}

#endif

/* times2_iterator.hpp
wfSEJ9lap1cjEyVGXMTt83qGgphx4LFnAsACrw55tgSX1psolIK3oThJt1xgksg34Tw55uDANiN2RzvbuF486uwBGx2iK8GVNAyilbEv9rd/remWm7896J7Yxq5WCuGcLqxC7/myqCRcYDR4b0MZU84dCzBOq46LAh7q+RZFXGriKQlj7URs2k1ZeaqQhRVceOGWjjGQ0Dm1fAx8UqmsnPysOrzARGzp4Ct0UejmoaankuoW79KxmhCT8VBrJror0RmvTRHKIxUtXy/EMPcDql+IiTAIn0JKJ1XgaBd0kOYc4CgOpmS/Ckly5GTncwVKYFQY5vyq4hfafFn0EKygupn+NHw5WRM2YwtnD7YB5WybKF3+AM9mbWIwtpHYzF0ez2iugI84HYdNIhnSmApBsyY63R5FlqIC40v2Im7X6GaWGK36Uk6+8eA3Rz4PFbXaAGWfb5d3c3y+6at7buisw0CRxqjZvsa9ei2JzHbU2RsXIvUbbn/hR9vowUoGaYkGdE5SZP3z5+DgAQpU5AneSzgDR/bYYZ9GdtVJBxLRVdYHWEjn/2RjUwUyIQ==
*/
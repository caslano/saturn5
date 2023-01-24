
#ifndef BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED
#define BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/transform_iter.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(F)
    >
struct transform_view
{
 private:
    typedef typename lambda<F>::type f_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;
 
 public:
    struct tag;
    typedef transform_view type;
    typedef aux::transform_iter< first_,last_,f_ > begin;
    typedef aux::transform_iter< last_,last_,f_ > end;
};

BOOST_MPL_AUX_NA_SPEC(2, transform_view)

}}

#endif // BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

/* transform_view.hpp
b8V0e8A7wF8gX8y4+lx1WhiAHZrqGRYB5yDyCP22BJG0ZvxGsytzyFuPP0tiNOAZx4Rl4XwZai2UZgU5ADCmHdUK1C3J3+sre1/ee2xYPhSCpNnaHnRaRbLcz2jT6pNWHbLkPHRqXQdrW+3dvVmHlG+Rz6XGiYWxogDTPsZALhO6WcNzZYdiTGL5PXzIydVvk7Xa1jl5QM1p1uLWps4zkZSc0EgzToMi0O0crq8UH7IEzs607/CXjS1QfEK1UDs2z5kt505zajVBKVlSqPAvoP4pV4bp2QJ1F7RvgbotKzOf+wdXFtR+WX/5MICzoWVQAWGKF/wmwPTHNqbko4l+78qMMw3BVOG8D2IKRZ0eIXdtfHGuCrKlcxdKw/597uViFKSJCKgbQnNBThW0i3ZOEiV+8Sh/PB6ezc1SPq/z7pmMyAp+lxyBHajMftj/tY1vt38ZK132QI7ZroTb4DeHwHSc67OpmsAl2tAsZ2UV2QhCGYVFrYbZMqU9BjL8ueFE3ISS4cS5PtSwJ0Z/rY1GKeOzUoagZAY0Q/JtkB7ZIu8bfZYyveeexgVVZjnDXJYlPgZTBNvhYuK+lLIOa//3LjClzrnDNcq6gkZ3gBpKE4gltdQthcTmon8q6/Gr0eyHTYFiUl/K8oq1xoKL2Vk0QQe3sUT6yjhETN2Ks1wM1oxUiwTK5PeDOGg/V447dbr8kxPJ1o2eP8WRVKbn
*/
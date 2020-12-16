///////////////////////////////////////////////////////////////////////////////
// weighted_skewness.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SKEWNESS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SKEWNESS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_skewness_impl
    /**
        @brief Skewness estimation for weighted samples

        The skewness of a sample distribution is defined as the ratio of the 3rd central moment and the \f$ 3/2 \f$-th power $
        of the 2nd central moment (the variance) of the samples. The skewness can also be expressed by the simple moments:

        \f[
            \hat{g}_1 =
                \frac
                {\widehat{m}_n^{(3)}-3\widehat{m}_n^{(2)}\hat{\mu}_n+2\hat{\mu}_n^3}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^{3/2}}
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.

        The skewness estimator for weighted samples is formally identical to the estimator for unweighted samples, except that
        the weighted counterparts of all measures it depends on are to be taken.
    */
    template<typename Sample, typename Weight>
    struct weighted_skewness_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, weighted_sample>::result_type result_type;

        weighted_skewness_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::weighted_moment<3>(args)
                        - 3. * accumulators::weighted_moment<2>(args) * weighted_mean(args)
                        + 2. * weighted_mean(args) * weighted_mean(args) * weighted_mean(args)
                      , ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                      * std::sqrt( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                   );
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_skewness
//
namespace tag
{
    struct weighted_skewness
      : depends_on<weighted_mean, weighted_moment<2>, weighted_moment<3> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_skewness_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_skewness
//
namespace extract
{
    extractor<tag::weighted_skewness> const weighted_skewness = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_skewness)
}

using extract::weighted_skewness;

}} // namespace boost::accumulators

#endif

/* weighted_skewness.hpp
q3bGDqzaoQXqtldoElSfG4UKWqtT1vABKZVxttKBL319Taef4qmk+2jSLXV4R8fVRLu8d6LzL3bkXZFKPANbtbW/YActr0msVzwz6Mmzk8t7TmBnmopEvqUVBeQrV8R57rzH7B0MsXLswUxbpnsA5r0omNK9pw9zK3rhc/rUR59eiE/RdFlQD3PTPBSfhHgUojii4eLygfjSKLPZZP1H1RhQ/k8Ivp27nSn/lXiow0FFHBx8j7ngfL5MZ4aY/6QomvnPwChMZKniGa7iRariHUxyyn6Flv3nGZpl/ws2a/EC5OBTBy1x1wzdlCjG+uCj+BQg3DiWXbSW+DQXrVneO4fTRwefYBcnxKYsEWC/2sbAvkDAvgRihVyndqSsa5EVEhyYgXWiO1Ef6xbP1S5FNCy3OtW0ozL13E8hGtmQuxc+UkchN/llbindneQ+HS/ZrOHA6hEb/LmdiGz96gi11MorHOVRmYXK0Gj/Gu+wCXz1Gl+OhqUSea52x5xz0Dr6e2NmgmmJ9hfr+//zoSn4vvhdHV8RivES8RWv/ogth5GrenGJ9tYEPZv9bpBefQ5zpun7rTRWp518kObHARNYXyZhzVAPp73eBKR5lqwgf24SJJHECZNnNbu3hXiIvQD/19kZTxP+ylRGRru79B/fzloUb5btIpo3+RmUeRf+8xwxW6d/ixfKVPwevxRai5ZxUhIpoFuFJO33Mc/YZVsxYxuwZfuy4SBtbuoU2SRuz9gy+VY8zwzqI/juRYaZ/ShDxpqCS/yVGYcmwPUZEGQm2PEVEJWT6LyrI6VW7Fmty4q6UeYSC7nbZ3WIb7K9LWqGEdRdiFKNo7eOeFt+uyC6v20h8uRvrGFe8wL7nepLeRK4jfeagjkfkJzqSskVh54NHG4JjyQbA3s/p9l+vJfNnYRf4/tdzNuR+91zH7JHFlLcp47GbJDNTtx0XfjGie13Mt/nvSXzlSa7VoHGae5Yps30Y56X3hAqvb48UKSZ3NnniQMWzb/E53xDHRTwP8VMVauxYdHd6nZfduzjnj2xvi5R5YctLqUDrZAR9rrLeQlYix4icYgfU7fgT468tVkkrCknBFe3zZnykSNjo1Jptz5W5sj40PpwWVarMqSDBZxXltUdr8U7rc+UZdGNkjRTFpsByj9ljly7OcgP/6w+8U/ePF3IkBNwE082EP5raOHF272XIrWvrL3qs8x8BcXktml+PJCWaZ1bqVRWt6bleAUvR/cZOcq6LDrFgW6alKW+MlfTTdOWWqW48V6ziZfakI+w1GaB1PBMKjS5R+Vk/Owelgbx0QfSYLQWxTSjwfulwQWnw5c7db24fFcHdIJMwXLEd4u5hrnfD1B59QFsZGl+ZVckrOa5IvJQkQM9P+4cz6R2poKz7L37wiE9FVt5RaFZKz2vg9OyVd3ZMR4e3ryTCrFbWezmvrpQYgT71sP0NN7P/Zv4FD2ZP8HnBaUGeyxoIETqPwRRubM0MPF5ln9twOL9jVgcOnwGgZ1gnwBGj0hghQlleLTnME+ZGTJlHtvIU0b9EFPmDzDtgPab+3fazFOuaOe+CBM+eflkjWV4RBz33baRkOKDmO6t1Jf/wYjRaa+kFSAMUk2GsjllY0bF2M60/hy4QiLdgeOWvDU4E6yFp0XEAZ+7fFeks4n4FkwTbhBG29tNUJAG/W+BVBvHl1uWReJL9zodX5oj8WXU4l+DL29fFoovzTq+fHHRsfCl5notiCk7aYXlva3dMLMn4IZH0KRa9QIjyDa+wYwfs3wJUfbyBgtdk7+B0eRNQTTpzLsr2lrklT2+IC9tpzNP7LgEc3zkTNlKmKMiFHNU6JgjGxpNz1RkFVe4z1k=
*/
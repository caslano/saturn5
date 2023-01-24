/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
Zkbc7J5eGC5Im5mBdMWQFwdV0O+gERz+RAvjihRWT4UbHcPYbeKQfXYFIIJ1jYIEy7w1KHrdcCNESiyPSYZG7OAq8j1LY8TpUii3pfsmova0uQsAJC8g/XSzDqqds0bgzRSzYoiINFg450P3Pwd9BZsI1wpLhFYxPMQVOtyF3rCxGulQGR+yNwEOEAF8tyLEyiA/Iq0UwQlKYVVFcGiGzVHcGchojYWwhY3guWCqwYx8lBkeaNVi7ycFoRtx6zbrO3GFQVXFx+ibVlQ+7N+7cmX5A5Cage+jRQAIX2lpPbTqrmDD4s32zBixyapDJsa3d85tkL3S4sSqsoLV4ZUgWRh26lzZJiJTraaocBwtnBrKnnv9dbzcSq/YUs/DEtU37zZEcpTCtrlRVL9upD9V+bqxRctib3LdK4ZUgKQkbRPGB+RbYfnQSmNR7r2hCFpINGD0/NB9lLGQK0QIXitZuRQWw5toDuNZTKS/aEFPH+Xzjm/XZTBV0EFG/Dm+mGmrF3HrxKebehFggt0nLAxeYT943onLqpEtYIXdzKrl8weKdTatNlas3IZpOQVFiqPMLnSxt9WdEBoKzYDebPC0fvcvZQPFqQFdOJXfiqhqK2qRJXYc2cVvVFHf4iB/nDwFyUay7dC9NKGNFcPXKnuFZhVdg7JxLevtYzrgl3SS0amu/xKUPJc9JHcBnXsNry3kZtjewZLup9iSCkzG
*/
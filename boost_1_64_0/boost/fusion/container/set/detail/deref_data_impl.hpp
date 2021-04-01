/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<set_iterator_tag>
      : deref_impl<set_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
rd37Sv/mxkrMs1OtDE0tYmMX282AWj7XiS86nGfLuE0lTu1HKda62IOvoyUKOhE1DIfDfloYW5TTzG+DJrw8EQzjQkNNLtgLtFhRk7i2RYNiPe6eYwPxQ3yh4u6t9ojPTUe7adyryTL6C6A5QzVqryZLe8USoVj9MagrSeVpywzFJMuIr4wMS94MFp8FewV4RjA6+6yqb6n6h1YtvOmDZg8IhSEav5V9mKCL4zsTrsGZ++1CqzAsjht5AZdemhJz81jYmVcIce3NDjLpGhxj2A6EQ05FWLuXwcZ6KNDXSYa+/4GT6/kqSTUZkPdAg/tUds+YxQSn4RnqyQ+TnvBK/9p8AhKSAAXxHUHz2Czy9kiFgJGhzbRaS1YEtS7vSGHR6rWo7YoS4TD4mqO3XtCMNCe0/tqsK85VGgpopwCPPF3quTthT0+tnSb0PMvqsNhRNmRH+HsRsEU+3Jwlyxv5ibasBIeOD+0SrlePMNamxt0c+srg+t6iRtgTLNwH+BtgB2vXd+C/szPkMUzbD2L9uHA3Xzj1IZAnOvjYL6OU8lHsDIOBQLbZml6pkg==
*/
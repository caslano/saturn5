/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<struct_iterator_tag>
      : deref_impl<struct_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
R2XrWpzaB999EUazE9+/MvVHAd8OHXFUw8AjNMFb+UXUIEYUHFM5O+3De6724GSBcX7XWTNP1OW4OxUaNz+/GrdIY12AS1J6hq1KKdUEkGdG3mjHJMkhdeIFtpZ1hFkgG5RBrWtowh2SMk4fECQM1+EWbr3+RfPF7M1itFyS+EXD2XQ1nq5HnQLEHBnt+gl94Dw6qSqBvSViPP/QXFOIIuXYDoctqHWGgSy8O1pJ3Gi/QyutnhLhdYnaMZP2iDDvHg7uGWoEHsN8q90doDqjdv5HUXg+W6xGF9H5VTQMJ5PzcPgOG6oj5WDsB9NrB2EWmIKsdTLlsQjqkDrefEgoH8g5a+rYSGCrfqTGWAJFDFQqpwu583rWqIjRpZHcdVmxDp7qRkjYAMVhJGytfq2u4S7eFKxWta4Jmi4+o6+C34qj2HnsKoxiz1CdmibsN1vaZbierNj5vi1i0BGOukQHsW5zuX/AoIMvd79aMHiEw0nZceW8rJK8UtwEj9GuZsPZZMlCOonik9Gn8P18MmLH5+HG6SAetG4oeH8u9nbhh3A8Cc/Hk/HqioVJUh/o8Rz1vH/Wr8+TXfMYUeZYQHt3R7jb6LSB1/x56MVotV5M4UM4WY+adq2nYxTN3tV59JajEYST5QzPZeeLb44O
*/
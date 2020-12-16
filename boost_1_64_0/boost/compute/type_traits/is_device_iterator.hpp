//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP

#include <boost/type_traits/integral_constant.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \c Iterator is a device-iterator.
///
/// By default, this function returns false. Device iterator types (such as
/// buffer_iterator) should specialize this trait and return \c true.
///
/// For example:
/// \code
/// is_device_iterator<buffer_iterator<int>>::value == true
/// is_device_iterator<std::vector<int>::iterator>::value == false
/// \endcode
template<class Iterator>
struct is_device_iterator : boost::false_type {};

/// \internal_
template<class Iterator>
struct is_device_iterator<const Iterator> : is_device_iterator<Iterator> {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP

/* is_device_iterator.hpp
PwN7X3N8Q6zTvtYh9JmI2c7ujgP/lretB9WVUFJqFudXIdYC45dQmirupHaKdybihNXKalkP5trIb3OqHHcmzrPieAwCa4aAh3OLNJUVKwsrm6wAW7vYlrRG0rZJeUHf3WVYu0a2GGkqax2l6RLm82eWU5b2kINB5YZs1aExThuX8oW+wWfgPCdkS6Z1tqZijs3/LoRHqk5Ddl8RstcYbpwLbV9Pio3851cKe57VsuIVy75/4AKEwf7zR8iWbZmRjaxT3tC3dvnWQz/vOmkVcTKJN+ZNNvZjD3Tj4NggI0i2srl9uHXs9lF2lcTbvMGx48d2rnzSJB1Esn0YEdsHcS7ZDe9Zng7uSV0FW1nnyZnT8d+F6Z+xa729v78ZlzjPnI7/nTx/ZmHacYqiuEKHYoWvk8/5tUIqU5mWpDUwrjYPh3yt3/zY9W70zvvF9vGR9G7sb0+iov0oGJ7/6lPp+SZ6/q74/Ilfjs9TfnpBen6QvuMXjh276rHt9adNtjfW4u83js/fE/HhG+n5ylocyXfP3puefauzuXOs1/u++6U9Q+lZ5HZ6E/9aN/pAfE6FkGLiWXVs+uxz9zl2LP42cbSViX/7+OxxEbf/5O7RRD3K8bOT87GPe/5we3Uqn4zkacZpJt+dI999+iC/2/SdPZ7WdZLlmJeYxrQump7fupcfXHWQX7m/vhJPPJvMuD+6WilbvzTp0n6Pvk9Tyje3j2XyT1ynkCf7mfz91y/l+9t52p5wYpDHC9niDFB6dude9rIbY1mftf2c/82bDpgL6wcnJ2nsDLLNmw2yzfXtCwcXc96fZrLthVi1uexatxpk0GZA9g2QxecLmygv526Ty2JiM9lXb5vLcBmE2w+yyFnA9po75bJ4uFCeznsOsv1RHm55n0EWOUhnWvzPZH06b97X1xPvn2ST6HpjmZ26InKmz6/3gPS8e1cmncfY2oU6fttJLEsn+eVt5FdXJHnvY66YrO3EfdS5/NJCJl8Yy4+dyuSnQA5p+2AnT8c4TrpEdG2ol93zdJJtXpzAyzrW/7cxJr2koOPtiyP5xvZ+XJPOdFx8IML0jWeWjqUHjeR763H9Pt7zFdeRp5hrLY0w8QSemN6nbU82d1ZSvqCevjfFbqeKyPP7uuXZ8wk7K+kjuZnwNkyUg3f+WQ9OmMLvZ7o/+hCQd8rv3j//7EPh+Vh5xr/pwxNuf5S2z8DzMd0N37LNq6JvjlStrSkL/+s3J/nu5n6x3Dsfnzbj7082L8b66r8JP7swe56uUJqkD+OxqdxFHgHeJDnb/fhGxAO6Zt8U08lTM0n02Fair35W9GU+SHf2bDNpzER42jSd06aP1Mf6b8RG1D1z5rN38p7Rh7/1+PD1SO145qOvdzUk6yttJv/e1ZF8bWcybeB37+X3veYc+WR/Jx49hnzGy66NcNGhzmTPuy6SpZcN/PRNr4dkyWmmwwcuJRm0uRsizN761s5T17M284kbJXmftPPb8F697sbpOUoy8j2PvclInujQ5m570yhP79Qs++ub8XDU/P3/UYmZugh4Lz95s7ny9Ou0kjNdX7x5iV1PR9+DfPMWpbxzNfCOXeuWpfxC7gIgXx8d4cAlga1n3arEdC4JdDS3LuTpJZjEu3e39gHzqxEG3Bak+ZO3KTHYbcF34rYJN3un+qyDrdO3S/LhXe2k4KzhO3T7hEk+KOG6pgCyb94BydJnCNJ4cKckwz2p7ut+iL8F3xvjUqmAnhfdeSzf3dkdsgJ5WbvLHNzh/sUcs3TXMeapK5uH69l789H485bjg1e5sHWwsYX6SN84PpZH7/GkHPP2q83BrMU16CzfS9dMmLXUyzrYmTzpMEYPboM=
*/
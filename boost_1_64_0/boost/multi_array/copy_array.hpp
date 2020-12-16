// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_COPY_ARRAY_HPP
#define BOOST_MULTI_ARRAY_COPY_ARRAY_HPP

//
// copy_array.hpp - generic code for copying the contents of one
// Basic_MultiArray to another.  We assume that they are of the same
// shape
//
#include "boost/type.hpp"
#include "boost/assert.hpp"

namespace boost {
namespace detail {
namespace multi_array {

template <typename Element>
class copy_dispatch {
public:
  template <typename SourceIterator, typename DestIterator>
  static void copy_array (SourceIterator first, SourceIterator last,
                   DestIterator result) {
    while (first != last) {
      copy_array(*first++,*result++);
    }
  }
private:
  // Array2 has to be passed by VALUE here because subarray
  // pseudo-references are temporaries created by iterator::operator*()
  template <typename Array1, typename Array2>
  static void copy_array (const Array1& source, Array2 dest) {
    copy_array(source.begin(),source.end(),dest.begin());
  }

  static void copy_array (const Element& source, Element& dest) {
    dest = source;
  }

};


template <typename Array1, typename Array2>
void copy_array (Array1& source, Array2& dest) {
  BOOST_ASSERT(std::equal(source.shape(),source.shape()+source.num_dimensions(),
                          dest.shape()));
  // Dispatch to the proper function
  typedef typename Array1::element element_type;
  copy_dispatch<element_type>::
    copy_array(source.begin(),source.end(),dest.begin());
}


} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* copy_array.hpp
pQNlTnKZMMj9xC5kH4uKhowu0+d4mXzbdRLXylU4y0e0lOmRet5gtrRFmrhemaSZOKDa1ZMe3pTFmMcXmKwlktIvM99VaT5sd0MQ46peMeovyMqkdMpAQKy+5cX+Gxsy7CY8AmO+l7T9+8ZbSy4MHV4m3LEC33kykycxencxeU9EWeiWUVaI1fnFjlSwOrnYHdR2QiZriSwLndhPXCG3PSTbFEP/2kEqV4g0jsA9UorCGStNIS2zQGVk6QrLCco8FU+MGoVDmRfxdDK39O3MiYQflWOD0jlCZXKRyTHBtwvhZGOD03kbT6e048wLgkCEmeUMSuckL08aeX5SWKlwxpvpYLv+Pp8LU9/LoqAU1thTcqelbaKvjJfJ9hIn9oJUJK5vSqE/9jyV2ev7SZnmZSxm4XOlTqCjuRcp9xGJFdnweB6MhEty6uDlvsxtlSdpHIRRKuCTurPy3KnnL0nnlZGX1XcM0X0n20vjUtZJT/pOOrX6RfTX/YDZtbTLQnb+QMwvy2f0UYL7nrdTmT15mcd5lpVCRgmb0dzHae6dKfeGonDdNEk9sTDfW9WGQe5OxpUdO/OcRExOT3e6+J7BQ/S3P+WmQo6Luec7gXjymCX74Ip8rJHvAzya8h9RlFYRF4UloHpm5lc4N6TcvX5YFlbs2mIWVtNmWy65/TI7Kq24cKF+pLNwBVxiaD8t80wuk0v7pWUSgAzUJpPR5S3fNkTL6yRhHvlOJqRnAGppWVtI8wXnu9I4rhP4Mg3Ox/jNPE+FCy/apI7mQ74a5XgplSmE7PgyW6Uq+9xyb7W1bR5ldZzAkifyczE7u7DWmzPa5jFex7mfRb7vJnQt22ibJ5h+BzygdhkJOyd03J9hbaJM7TSwylTIeO7tuj/HdMe2YwVhXgo3bNH9NabbDvMwCXwVIZ3r1vyzPC/wAqqsMmE/0W/nn2P8NMxSx00jUdhxO/8i42dJ6ViFpZaa7fzLjO/ZWelHfihctA3jQwHYnlGQpm7keGolQAWQv5XxQ8uPvMyJ5dCcP4zy0fY7KP8GP4+tOIMI7k6L7e9OuY8IC8srXceCJVB73h9E+ftL30ps1y718gclkL+P8lNRhGnkubYqK6x5UAD3HTg/94IotIJUeHkQ5V57ng6wPPlRkdpZUMjy8hrAWPUzlG87Ii4tp4R3duRUpR7tgnW68Risln2RlOXvTzh2XqSFfmMQhZf76yHsz1R2r2/B84SxHCsnVzFGfA/fPaHcUthFahW2tAM8zLs83XyD0ddzP5VzAhH7keVYpSXAvaLKVj/opr4gnr+8Jtdhc8trC9XDuf213zlWzgjWX2lS+KILPiNQUz3ASJ5U5Ou3Kzz/aRl5QR7aYn5JUuVxOMO8q75u69S/4noitvPcSoqyPf+rc5NyAfq8yR749nuTU/12nVI9+4MiKYPC9tQrocp4OpZ/rtvQD7ndUknPQ//6gw2urIA/FffHX0n17Y5deLcmcEVuVeniW0NHKG9f6YeF44exUI3WiSqnkvx3bL5RdIyVL7JyP09lcwTTtAk+Trff9/6Qz8F55vpu6okqOn1rmntivYf6Q/49ECWpHXq+JVRVVl6uXfsWDrQ5wfR3Ntwde+xD5Bj7ADgCCX6rZuz8Y/eT8+UDEWex8+Fu463hrPMzAJcJ12emQO6esIbC31fnYA0i3Uey5Ui8ltuKeOVLqsUVPgL3n00cdtFqXMh8b1M4etom5iZ7c+pckMRBz4EHEXyi9iBNVB9aunyW1HM/pWfsKWNG+R5Q69mucHmOrZ+V+njtsmyBUmB1YuieNXcH5lnyOUel98+7ynXUg/r21Pma7/SU3zaQ+QFkbNwa98ieiZB+w4c=
*/
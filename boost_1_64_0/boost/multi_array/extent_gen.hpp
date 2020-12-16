// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_EXTENT_GEN_HPP
#define BOOST_MULTI_ARRAY_EXTENT_GEN_HPP

#include "boost/multi_array/extent_range.hpp"
#include "boost/multi_array/range_list.hpp"
#include "boost/multi_array/types.hpp"
#include "boost/array.hpp"
#include <algorithm>

namespace boost {
namespace detail {
namespace multi_array {


template <std::size_t NumRanges>
class extent_gen {
public:
  typedef boost::detail::multi_array::index index;
  typedef boost::detail::multi_array::size_type size_type;
  typedef extent_range<index,size_type> range;
private:
  typedef typename range_list_generator<range,NumRanges>::type range_list;
public:
  template <std::size_t Ranges>
  struct gen_type {
    typedef extent_gen<Ranges> type;
  };

  range_list ranges_;

  extent_gen() { }

  // Used by operator[] to expand extent_gens
  extent_gen(const extent_gen<NumRanges-1>& rhs,
            const range& a_range)
  {
    std::copy(rhs.ranges_.begin(),rhs.ranges_.end(),ranges_.begin());
    *ranges_.rbegin() = a_range;
  }

  extent_gen<NumRanges+1>
  operator[](const range& a_range)
  {
    return extent_gen<NumRanges+1>(*this,a_range);    
  }

  extent_gen<NumRanges+1>
  operator[](index idx)
  {
    return extent_gen<NumRanges+1>(*this,range(0,idx));    
  }    

  static extent_gen<0> extents() {
    return extent_gen<0>();
  }
};

} // namespace multi_array
} // namespace detail
} // namespace boost


#endif

/* extent_gen.hpp
DiOit6zQ9/g5xOXyrbYHRDSmHDHS5DwXSPQuzKjmwFnAlYpFz5EiDog2B4kdvrENn1ii+biwSXOgrXFFGIdns+bIVVlFQfnLDQysuNShcfFftKWdo43yAJ3fm1DeUudwRcbmQu/RnmBcuVxf7WCedtxUY1JwgG0+jRzlR5V/0a2JxLm/GeM08DchLh9kejZWD6ZxieHMOGibw1sZxzQO6nrQzRlvYbJXG4foOtLKwUTRzjtu0eSZCeP9kz53uVuF5lx5NqkHcUvE13SO8GzpNo1V/ZhXBblDQ3iL8hxBXZ2o50G34ng9hGka2ui9yJNfNLzfYX7TW1OOKgzKn0ZsbYnXOIlJdhvgTK3NL8xMmKMUcrYDp2WMIjFL38Q55jiG+b1R8YDUPA88fluNzXQWOqsNu9xR7/30ectmHPudt2MYpo/vQSAOoxzfaMDYVcjhVsM4arfXeAWpSpmYXuwSu55v5ahZBNPp7gAOjiFVPP1eH1+4A+B6jgHevPzG69v8osIX5iaqofsJUR5MuNa4VZsPed07tvPqgR55FwbwpHVg/xB5C3dq58FWHI0HdWkQb6UjbdJ5rkpbx4bNbwGxuZTXT1Y8HIGRtEPgElkZIryjT2jy1pb6zHvqGLVZg6dbHHKOlk1OT5puerVafxyW8+WomnPlzk2Fq99fINvHZbUXNbO2uChn/fkZtdf1Ysmvvl8m3CjwxsbHJsrxJwwp7GXVPlgFk424+0jsVQxzUs/Kn1hORONehrtpSsff5LhikBy73md7DaZdHwyv04a7u+9ArOK+i3BJYgp7D8sLbtgp7ATFMGuyvUrsLahTvcSlzkKpLECfkPhbDRw+aikJ7PCRwXZAgwHv1GAeZhjvKMM8PFxToQtJTwady8thA5/pzE6uLSAPx1LCw4YJJKJr54Y2jvyeAR69j0t5vWae7jzC8IF5Okp4pBMADfvq6ChwqiYOHDNXd6zb+ZBq57BhUDV0+Qu29UtGW8d3WuSfhzHbWrlLx/NhjTPbIg/XLshjtpUkfr8GObwUiod3tiiv18zT3UcQZ7Y1eW9CHrOtpuEYt2VU8trti9z7YHxrOt7Ay2bq9kZPj8O5Ppf/HX5GJ7ecICys9Lq/UWUCAtpbXbc3Ph3qFtPTFYz2/wX4bmk9IbW/xnrl8CBOVR6qT2Z+ALeHd2lWkWPUJyWTtfSlVn4790sjyGV1TOiY1zeNMi7j4PpyI3JYWyBUbDdHFXdgFcvy37ey5ybCQ50NC+A8dEXV4YyuPOybp815iPTNh9M68Bws8/gwxdA+jPNp4Jj2BgK/88Y5WALFw7y8jfJ6PC93HmFYa16OIofbH1K5D56rlJx2ewIP7Xi5smNjPj/F7cjmjz3UVq45fyDObek25489DVu55vyBHG5Pl88flNdjeUKbMnxAno4ij9vVNeaPPe12BR6OWYeNMSsoU8uyw+uPA1mNWTgfXVL1VB3k1W0ev+Hkn73M5oqG5X/5cCuOAxXGF2nnsbFkbgNyjDpBMqZ7vo2LPHKvdAR5vH6QyuP5cS5yMN0bkcPqUVNxrlrdKHntdam52E/+NmC8WW2ON9hPbmD9JCQxaymG5WWc08AxbQcE1j84B3Nf89C/Q3k9npcdIwxrzcsR5DB7AgX7xY3Aabel4uV6j9Wcy8syL6x83XO57hcXVb1U557b+sUjqJ0rGusXLXizX7TzjH6BHF4XSOb9oslFHqSL/QJ5vfZ0HzSKHFZ/yOX9ArlYR5gy7xePaK9LzcVvxkst35Uzy5IJedTfnk9trPNgs4iuBJB7/MHAlSo0HfzQ1HEB9tF7CK+Aup84tLA8NblA+UNDy3fV+8+qfTSU4X7JywE30zM=
*/
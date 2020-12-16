// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_INDEX_GEN_HPP
#define BOOST_MULTI_ARRAY_INDEX_GEN_HPP

#include "boost/array.hpp"
#include "boost/multi_array/index_range.hpp"
#include "boost/multi_array/range_list.hpp"
#include "boost/multi_array/types.hpp"
#include <algorithm> 
#include <cstddef>

namespace boost {
namespace detail {
namespace multi_array {


template <int NumRanges, int NumDims>
struct index_gen {
private:
  typedef ::boost::detail::multi_array::index index;
  typedef ::boost::detail::multi_array::size_type size_type;
  typedef index_range<index,size_type> range;
public:
  template <int Dims, int Ranges>
  struct gen_type {
    typedef index_gen<Ranges,Dims> type;
  };

  typedef typename range_list_generator<range,NumRanges>::type range_list;
  range_list ranges_;

  index_gen() { }

  template <int ND>
  explicit index_gen(const index_gen<NumRanges-1,ND>& rhs,
            const range& r)
  {
    std::copy(rhs.ranges_.begin(),rhs.ranges_.end(),ranges_.begin());
    *ranges_.rbegin() = r;
  }

  index_gen<NumRanges+1,NumDims+1>
  operator[](const range& r) const
  {
    index_gen<NumRanges+1,NumDims+1> tmp;
    std::copy(ranges_.begin(),ranges_.end(),tmp.ranges_.begin());
    *tmp.ranges_.rbegin() = r;
    return tmp;
  }

  index_gen<NumRanges+1,NumDims>
  operator[](index idx) const
  {
    index_gen<NumRanges+1,NumDims> tmp;
    std::copy(ranges_.begin(),ranges_.end(),tmp.ranges_.begin());
    *tmp.ranges_.rbegin() = range(idx);
    return tmp;
  }    

  static index_gen<0,0> indices() {
    return index_gen<0,0>();
  }
};

} // namespace multi_array
} // namespace detail
} // namespace boost


#endif

/* index_gen.hpp
lEFwzAg3mTh+xiHnSyZHZw44+pzLLjpewIIHPkNg9Ux8bmzMyIXsCpnv29Z6xwyYy62Hyv6s2oEew3qr8vI9nik9ojB9WhvAVblgnAMK2vQy3BUdZh8D+M15cFhizFeshtPZJbIn+l2TA1f82Zqu4okNnKeHZaTSMwMmt3MYz8Y9ANsZ59QeDqKOvA1tcLUnAN9vHjXw+Rks3ytNTM12mAqmcaPBq9diqGduI8d1beD5N23PPg+/I++J62mC9drr49OcM7g+NjPeVevjLOO218cztzDOVevjEuM266N7E4az+vgbwwbXx+pNKQ/rA/vzZYW3+JDpGZebMY7pZ0be5xRvoPsOee5WxuPLDuov4Dx00Zhnt8dv3uTpb2gcbzWHLWGIjlsgbg5ZOH5+DTjcXwReH8T33dLE1VlG9Od8WuHtp7pqfwqenRjfNphLnBHI/9JV+HAMuDYa5mX8Vlfjr3Ef6Rm+vktD2w1Sq1j/WN33PzwOx1rVPxB79DDBjHZ4WmEDXbpYl90NbTylDNdBgpbp4RCUIEjtQFhpytdLd379MFnbeWWUZ0GZCTesaMg7/ii6BkzyNA19SfAcI45sSNPdkwZpGNl5IuAYVeOOVXmGresS148dKxX12Ud+d/Ug43qhl9mwtqzPaHLuHMuDb5VuajuugA/xRuy8LuVmIrUhSIzrKPKE84SnlOMFyui140upzP7cdTPHsmOBZyJrAZHrPb8zfC0QlZbv+uW6ffC6fF/j5SuC0rfTQMhxHReYLDaLaN0fgrOfCx12pn24hYs8EkMaeXw/iO/zt3PwHof2Uyre/JIiqK0WEkfky+y+upv4cen6if5QUlOeeefvu1827j1lcRL4hYVCMCfDpCalD1fCwzq9izy9Ik4ix3U9FAWvQJ3eqk7vipFeGcHd3CRDoV4zPYyP+xV2f9K1nCINc4GL+TqxVZ2/nZSfi9yxLbcMI0FW+Jg/7TfbQ2VkIw2TwC6DAoVgaTHfkzN9Z3pNefoNm4xT+UzkfpSXVpmhOKmCNf3NOsPStETuJkWRpT4VgoRrwQWd18NMLhSR7ORlZMemXN2GdLqY1zdR+UJIydhKcl+wkbiSWtF5fS9L0xFhaUWRLSu9cXSCf5d/zpDLvdLzvdQWjaNIXO4nTM4WgS+bWVz4wvwUM+IfXTRsmpVx6SeZK9gnGoqh3I2GnBsEUWjLhmp8upnxZLZ9lcek8aMoceKUpcf3TysNGE+EyfsiybM49/LYlCeiGEMlZbKWcNIi8ENbGF+TGOcZ4w9QuUy4TmlHaVAIMttqGaHT6hpphVFW+LkbC+Mzsha0dPlezuRcUbhp4sV2KpqfjhiHQ9v2bUw2Eo4dRmnqhmLA9oBZN59m8qFw8yB2LCcW7dsGOH/Zug0y+UwUVl7YQeKLwdsJaDj0n3yVj12pl+VWVIj+F43hv/8ab0+xaxVFWGRi4BEHftf8flS+EKkXeEWKzYlZel6nuc9I08kgwAwOCC3TEk/zAE8zspPYjVyXiOOAO6Hb0xxL0xK27aRh6lEZGnNiHu+qM7lAuG5RQCwp0bpdzG17jMmGIkzixHMzV7QvJRtroNO8nEFhhUHm2oJ5YCqpJV3OrxnlzD0/8uMoh0vjaqCutwjqxPBO8y+YnC+KNPYLP8uUXJ1fHTqrtpLQ5bxslDOI/dzKYpvKLi7PrC10WF/HsXDb1/k9/TgO/cD1xeQCXFGTsdGg4Xf6sV5sPe9+nc+hWZr4bijTnVw5tLbYWYKoaD11J7++a784hQXX5XaZDle4YeoGeZQJOZ/VouYc3NGyB5msJ9txkQWJk6n4YJNLUn518tmdnszFkrzwyNvGKpMNRWKVfpE7Fpc=
*/
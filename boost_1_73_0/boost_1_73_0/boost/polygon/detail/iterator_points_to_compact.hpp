/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
#define BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
namespace boost { namespace polygon{
template <typename iT, typename point_type>
class iterator_points_to_compact {
private:
  iT iter_, iterEnd_;
  orientation_2d orient_;
  mutable typename point_traits<point_type>::coordinate_type coord_;
public:
  typedef typename point_traits<point_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef coordinate_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const coordinate_type* pointer; //immutable
  typedef const coordinate_type& reference; //immutable

  inline iterator_points_to_compact() : iter_(), iterEnd_(), orient_(), coord_() {}
  inline iterator_points_to_compact(iT iter, iT iterEnd) : 
    iter_(iter), iterEnd_(iterEnd), orient_(HORIZONTAL), coord_() {}
  inline iterator_points_to_compact(const iterator_points_to_compact& that) : 
    iter_(that.iter_), iterEnd_(that.iterEnd_), orient_(that.orient_), coord_(that.coord_) {}
  //use bitwise copy and assign provided by the compiler
  inline iterator_points_to_compact& operator++() {
    //iT tmp = iter_;
    ++iter_;
    //iT tmp2 = iter_;
    orient_.turn_90();
    //while(tmp2 != iterEnd_ && get(*tmp2, orient_) == get(*tmp, orient_)) {
    //  iter_ = tmp2;
    //  ++tmp2;
    //}
    return *this;
  }
  inline const iterator_points_to_compact operator++(int) {
    iT tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_points_to_compact& that) const {
    return (iter_ == that.iter_);
  }
  inline bool operator!=(const iterator_points_to_compact& that) const {
    return (iter_ != that.iter_);
  }
  inline reference operator*() const { coord_ = get(*iter_, orient_); 
    return coord_;
  }
};
}
}
#endif


/* iterator_points_to_compact.hpp
AC1nSlIVIv3NhgMAAIMIAAAhAAkAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTYwMi5jVVQFAAG2SCRgrVR/b9s2EP1fn+LqAoVtaFYmbNhat8M8N+2MGXZgK+gCBCBo8RRxkUSBpJx4y777jpR/Bm3TDpVhizzevXv3eL6o/+2eAPrw5MP8l9FDbx9xodVfmNqPezP2AO2Hoq7p/VSSCA4hD6wHT4c8QNeHsG2W127N2FOJrh039xO5yGvmlmShMBc5VvVGy5vcQnfcg+9fvvwZvoP4LD4L4S2vJBawtFitUN+E8Fp4y685v78fGPwlBLTAi8EWKsmlAaMye8c1Aq0LmWJlUAA3INCkWq5oIyuwOUImC4Tx/OJqMnsfwl0u09yBbFQDJldNISDnawSNKcp1i1FzbUFlFE7gQhpLgI2VqhpQbgSLujQOw6XnhVHA11wWfEWJuIXc2tq8iqK00QWxj4RKTZTuyh/kttxXckUkSr4BVVuwChqDITjPEEolZObeJAgZ62ZVSJOHBzaUqhKR0mCwKBwWxUk0LW2E5Vae0LlBTYyldS+jKuNS3eWqPHEkHR1K1uiKEpEO5CQUyRxCUwnU3tlXvkux1dQL/MmrOfAVoCoiA53REibLDqy4kSaED5Pk9/ll
*/
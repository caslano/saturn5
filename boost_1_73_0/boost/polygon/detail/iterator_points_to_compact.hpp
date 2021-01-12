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
eQy/0/mc6Hi7vm71Ps3UHdbXjxEvn8xjX3e3+4zfmq/NXyv+7D78VueveWLLy7Y7qKNZn5zXrT5XeL/9uTgU9NuLxmlvKPg4x/UuwXi17p7qOjiOfHz50Pr2WMjfv/P8Hgz/fqXnf6nzocPrdSvNV96fO5Ydft7K+RnvuuZ+fOMl3ie4xvG62/z9O+/3Xm77rFenvGc+/YV55lzz0hjjZG3QjrcWeh36BMfNz3cuDeJyif27
*/
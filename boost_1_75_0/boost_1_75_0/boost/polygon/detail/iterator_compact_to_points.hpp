/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_COMPACT_TO_POINTS_HPP
#define BOOST_POLYGON_ITERATOR_COMPACT_TO_POINTS_HPP
namespace boost { namespace polygon{
template <typename iterator_type, typename point_type>
class iterator_compact_to_points {
private:
  iterator_type iter_;
  iterator_type iter_end_;
  point_type pt_;
  typename point_traits<point_type>::coordinate_type firstX_;
  orientation_2d orient_;
public:
  typedef std::forward_iterator_tag iterator_category;
  typedef point_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const point_type* pointer; //immutable
  typedef const point_type& reference; //immutable

  inline iterator_compact_to_points() : iter_(), iter_end_(), pt_(), firstX_(), orient_() {}
  inline iterator_compact_to_points(iterator_type iter, iterator_type iter_end) :
    iter_(iter), iter_end_(iter_end), pt_(), firstX_(), orient_(HORIZONTAL) {
    if(iter_ != iter_end_) {
      firstX_ = *iter_;
      x(pt_, firstX_);
      ++iter_;
      if(iter_ != iter_end_) {
        y(pt_, *iter_);
      }
    }
  }
  //use bitwise copy and assign provided by the compiler
  inline iterator_compact_to_points& operator++() {
    iterator_type prev_iter = iter_;
    ++iter_;
    if(iter_ == iter_end_) {
      if(x(pt_) != firstX_) {
        iter_ = prev_iter;
        x(pt_, firstX_);
      }
    } else {
      set(pt_, orient_, *iter_);
      orient_.turn_90();
    }
    return *this;
  }
  inline const iterator_compact_to_points operator++(int) {
    iterator_compact_to_points tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_compact_to_points& that) const {
    if (iter_ == iter_end_) {
      return iter_ == that.iter_;
    }
    return (iter_ == that.iter_) && (x(pt_) == x(that.pt_));
  }
  inline bool operator!=(const iterator_compact_to_points& that) const {
    if (iter_ == iter_end_) {
      return iter_ != that.iter_;
    }
    return (iter_ != that.iter_) || (x(pt_) != x(that.pt_));
  }
  inline reference operator*() const { return pt_; }
};
}
}
#endif

/* iterator_compact_to_points.hpp
l3zYY/4qCJ+UZfxHl763kxeh6MMAQigaFHVxli+1KyEL24jTugd1tM0Dmr6BussGdEOPJ6V2adAnmHY2NhqX8UCPYUfOURneLLD05ATEEzFswp0BcR0PW1yGGiL2WnV3QDrF+i3fniWkYBuForvfk0El6wi5Z7OjPjMtOrUqpy5Ey7pfsT+6O3cngZepEMftYMNdmbBvFaMBQafahCxOm/IyXOvB7lfl83D66T+QNd+TYlvvb8jK/b+QlfW/IauAwN/a0p7uHs6O0jaW5vZ8/yJWhDPlkCfYe+fiaDmfQS+FatloVvDdckr/quh3LZvInYDZ6Qe5IwalWgbN0TailoWLWMgqgSxbVVws4VCprq7TTr0stkoQM8cPSvwiW9NcJ7xc0Ae4Mh6hTVC9hn6uama/RLOC+dEDZOwYAlPI8ZF5CAka67OGrmbeWkHa01s6lrvgqzEST9uicc985a/Rv6C06ThZqlbx/viTF/I2fHiDLXXUy/W+adOdCCDt4wIRHPW9MlNxh0TbSNbTreCevKLZetEfEoHV+3JJrp9xuZFgO9zioWnzEi+2jj1hgJDYkixaVVCng2jujX7aou7lDs6iiH/741C+yN7eUw/4eah70h2EE6OFSGO+rEUdrbNliDmi7jEy6KdOb+83QyvmE7g6M8l55zeh9yAWSQqLuNJ4HO+ZO8+ZgtytDB1jA/Ze6DHVMy6UScT5ZCw/
*/
/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_GEOMETRY_TO_SET_HPP
#define BOOST_POLYGON_ITERATOR_GEOMETRY_TO_SET_HPP
namespace boost { namespace polygon{
template <typename concept_type, typename geometry_type>
class iterator_geometry_to_set {};

template <typename rectangle_type>
class iterator_geometry_to_set<rectangle_concept, rectangle_type> {
public:
  typedef typename rectangle_traits<rectangle_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
private:
  rectangle_data<coordinate_type> rectangle_;
  mutable value_type vertex_;
  unsigned int corner_;
  orientation_2d orient_;
  bool is_hole_;
public:
  iterator_geometry_to_set() : rectangle_(), vertex_(), corner_(4), orient_(), is_hole_() {}
  iterator_geometry_to_set(const rectangle_type& rectangle, direction_1d dir,
                           orientation_2d orient = HORIZONTAL, bool is_hole = false, bool = false, direction_1d = CLOCKWISE) :
    rectangle_(), vertex_(), corner_(0), orient_(orient), is_hole_(is_hole) {
    assign(rectangle_, rectangle);
    if(dir == HIGH) corner_ = 4;
  }
  inline iterator_geometry_to_set& operator++() {
    ++corner_;
    return *this;
  }
  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return corner_ == that.corner_;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    if(corner_ == 0) {
      vertex_.first = get(get(rectangle_, orient_.get_perpendicular()), LOW);
      vertex_.second.first = get(get(rectangle_, orient_), LOW);
      vertex_.second.second = 1;
      if(is_hole_) vertex_.second.second *= -1;
    } else if(corner_ == 1) {
      vertex_.second.first = get(get(rectangle_, orient_), HIGH);
      vertex_.second.second = -1;
      if(is_hole_) vertex_.second.second *= -1;
    } else if(corner_ == 2) {
      vertex_.first = get(get(rectangle_, orient_.get_perpendicular()), HIGH);
      vertex_.second.first = get(get(rectangle_, orient_), LOW);
    } else {
      vertex_.second.first = get(get(rectangle_, orient_), HIGH);
      vertex_.second.second = 1;
      if(is_hole_) vertex_.second.second *= -1;
    }
    return vertex_;
  }
};

template <typename polygon_type>
class iterator_geometry_to_set<polygon_90_concept, polygon_type> {
public:
  typedef typename polygon_traits<polygon_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
  typedef typename polygon_traits<polygon_type>::iterator_type coord_iterator_type;
private:
  value_type vertex_;
  typename polygon_traits<polygon_type>::iterator_type itrb, itre;
  bool last_vertex_;
  bool is_hole_;
  int multiplier_;
  point_data<coordinate_type> first_pt, second_pt, pts[3];
  bool use_wrap;
  orientation_2d orient_;
  int polygon_index;
public:
  iterator_geometry_to_set() : vertex_(), itrb(), itre(), last_vertex_(), is_hole_(), multiplier_(), first_pt(), second_pt(), pts(), use_wrap(), orient_(), polygon_index(-1) {}
  iterator_geometry_to_set(const polygon_type& polygon, direction_1d dir, orientation_2d orient = HORIZONTAL, bool is_hole = false, bool winding_override = false, direction_1d w = CLOCKWISE) :
    vertex_(), itrb(), itre(), last_vertex_(),
    is_hole_(is_hole), multiplier_(), first_pt(), second_pt(), pts(), use_wrap(),
    orient_(orient), polygon_index(0) {
    itrb = begin_points(polygon);
    itre = end_points(polygon);
    use_wrap = false;
    if(itrb == itre || dir == HIGH || ::boost::polygon::size(polygon) < 4) {
      polygon_index = -1;
    } else {
      direction_1d wdir = w;
      if(!winding_override)
        wdir = winding(polygon);
      multiplier_ = wdir == LOW ? -1 : 1;
      if(is_hole_) multiplier_ *= -1;
      first_pt = pts[0] = *itrb;
      ++itrb;
      second_pt = pts[1] = *itrb;
      ++itrb;
      pts[2] = *itrb;
      evaluate_();
    }
  }
  iterator_geometry_to_set(const iterator_geometry_to_set& that) :
    vertex_(), itrb(), itre(), last_vertex_(), is_hole_(), multiplier_(), first_pt(),
    second_pt(), pts(), use_wrap(), orient_(), polygon_index(-1) {
    vertex_ = that.vertex_;
    itrb = that.itrb;
    itre = that.itre;
    last_vertex_ = that.last_vertex_;
    is_hole_ = that.is_hole_;
    multiplier_ = that.multiplier_;
    first_pt = that.first_pt;
    second_pt = that.second_pt;
    pts[0] = that.pts[0];
    pts[1] = that.pts[1];
    pts[2] = that.pts[2];
    use_wrap = that.use_wrap;
    orient_ = that.orient_;
    polygon_index = that.polygon_index;
  }
  inline iterator_geometry_to_set& operator++() {
    ++polygon_index;
    if(itrb == itre) {
      if(first_pt == pts[1]) polygon_index = -1;
      else {
        pts[0] = pts[1];
        pts[1] = pts[2];
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      }
    } else {
      ++itrb;
      pts[0] = pts[1];
      pts[1] = pts[2];
      if(itrb == itre) {
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      } else {
        pts[2] = *itrb;
      }
    }
    evaluate_();
    return *this;
  }
  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return polygon_index == that.polygon_index;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    return vertex_;
  }

  inline void evaluate_() {
    vertex_.first = pts[1].get(orient_.get_perpendicular());
    vertex_.second.first =pts[1].get(orient_);
    if(pts[1] == pts[2]) {
      vertex_.second.second = 0;
    } else if(pts[0].get(HORIZONTAL) != pts[1].get(HORIZONTAL)) {
      vertex_.second.second = -1;
    } else if(pts[0].get(VERTICAL) != pts[1].get(VERTICAL)) {
      vertex_.second.second = 1;
    } else {
      vertex_.second.second = 0;
    }
    vertex_.second.second *= multiplier_;
  }
};

template <typename polygon_with_holes_type>
class iterator_geometry_to_set<polygon_90_with_holes_concept, polygon_with_holes_type> {
public:
  typedef typename polygon_90_traits<polygon_with_holes_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::pair<coordinate_type, std::pair<coordinate_type, int> > value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type* pointer; //immutable
  typedef const value_type& reference; //immutable
private:
  iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type> itrb, itre;
  iterator_geometry_to_set<polygon_90_concept, typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type> itrhib, itrhie;
  typename polygon_with_holes_traits<polygon_with_holes_type>::iterator_holes_type itrhb, itrhe;
  orientation_2d orient_;
  bool is_hole_;
  bool started_holes;
public:
  iterator_geometry_to_set() : itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(), is_hole_(), started_holes() {}
  iterator_geometry_to_set(const polygon_with_holes_type& polygon, direction_1d dir,
                           orientation_2d orient = HORIZONTAL, bool is_hole = false, bool = false, direction_1d = CLOCKWISE) :
    itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(orient), is_hole_(is_hole), started_holes() {
    itre = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, HIGH, orient, is_hole_);
    itrhe = end_holes(polygon);
    if(dir == HIGH) {
      itrb = itre;
      itrhb = itrhe;
      started_holes = true;
    } else {
      itrb = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, LOW, orient, is_hole_);
      itrhb = begin_holes(polygon);
      started_holes = false;
    }
  }
  iterator_geometry_to_set(const iterator_geometry_to_set& that) :
    itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(), is_hole_(), started_holes() {
    itrb = that.itrb;
    itre = that.itre;
    if(that.itrhib != that.itrhie) {
      itrhib = that.itrhib;
      itrhie = that.itrhie;
    }
    itrhb = that.itrhb;
    itrhe = that.itrhe;
    orient_ = that.orient_;
    is_hole_ = that.is_hole_;
    started_holes = that.started_holes;
  }
  inline iterator_geometry_to_set& operator++() {
    //this code can be folded with flow control factoring
    if(itrb == itre) {
      if(itrhib == itrhie) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
          itrhie = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
          ++itrhb;
        } else {
          //in this case we have no holes so we just need the iterhib == itrhie, which
          //is always true if they were default initialized in the initial case or
          //both point to end of the previous hole processed
          //no need to explicitly reset them, and it causes an stl debug assertion to use
          //the default constructed iterator this way
          //itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept,
          //  typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
        }
      } else {
        ++itrhib;
        if(itrhib == itrhie) {
          if(itrhb != itrhe) {
            itrhib = iterator_geometry_to_set<polygon_90_concept,
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
            itrhie = iterator_geometry_to_set<polygon_90_concept,
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
            ++itrhb;
          } else {
            //this is the same case as above
            //itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept,
            //  typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
          }
        }
      }
    } else {
      ++itrb;
      if(itrb == itre) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
          itrhie = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
          ++itrhb;
        }
      }
    }
    return *this;
  }
  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_geometry_to_set& that) const {
    return itrb == that.itrb && itrhb == that.itrhb && itrhib == that.itrhib;
  }
  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }
  inline reference operator*() const {
    if(itrb != itre) return *itrb;
    return *itrhib;
  }
};


}
}
#endif

/* iterator_geometry_to_set.hpp
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
*/
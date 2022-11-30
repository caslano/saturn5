// Boost.Polygon library detail/voronoi_structures.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES
#define BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES

#include <list>
#include <queue>
#include <vector>

#include "boost/polygon/voronoi_geometry_type.hpp"

namespace boost {
namespace polygon {
namespace detail {
// Cartesian 2D point data structure.
template <typename T>
class point_2d {
 public:
  typedef T coordinate_type;

  point_2d() {}

  point_2d(coordinate_type x, coordinate_type y) :
      x_(x),
      y_(y) {}

  bool operator==(const point_2d& that) const {
    return (this->x_ == that.x()) && (this->y_ == that.y());
  }

  bool operator!=(const point_2d& that) const {
    return (this->x_ != that.x()) || (this->y_ != that.y());
  }

  coordinate_type x() const {
    return x_;
  }

  coordinate_type y() const {
    return y_;
  }

  point_2d& x(coordinate_type x) {
    x_ = x;
    return *this;
  }

  point_2d& y(coordinate_type y) {
    y_ = y;
    return *this;
  }

 private:
  coordinate_type x_;
  coordinate_type y_;
};

// Site event type.
// Occurs when the sweepline sweeps over one of the initial sites:
//   1) point site
//   2) start-point of the segment site
//   3) endpoint of the segment site
// Implicit segment direction is defined: the start-point of
// the segment compares less than its endpoint.
// Each input segment is divided onto two site events:
//   1) One going from the start-point to the endpoint
//      (is_inverse() = false)
//   2) Another going from the endpoint to the start-point
//      (is_inverse() = true)
// In beach line data structure segment sites of the first
// type precede sites of the second type for the same segment.
// Members:
//   point0_ - point site or segment's start-point
//   point1_ - segment's endpoint if site is a segment
//   sorted_index_ - the last bit encodes information if the site is inverse;
//     the other bits encode site event index among the sorted site events
//   initial_index_ - site index among the initial input set
// Note: for all sites is_inverse_ flag is equal to false by default.
template <typename T>
class site_event {
 public:
  typedef T coordinate_type;
  typedef point_2d<T> point_type;

  site_event() :
      point0_(0, 0),
      point1_(0, 0),
      sorted_index_(0),
      flags_(0) {}

  site_event(coordinate_type x, coordinate_type y) :
      point0_(x, y),
      point1_(x, y),
      sorted_index_(0),
      flags_(0) {}

  explicit site_event(const point_type& point) :
      point0_(point),
      point1_(point),
      sorted_index_(0),
      flags_(0) {}

  site_event(coordinate_type x1, coordinate_type y1,
             coordinate_type x2, coordinate_type y2):
      point0_(x1, y1),
      point1_(x2, y2),
      sorted_index_(0),
      flags_(0) {}

  site_event(const point_type& point1, const point_type& point2) :
      point0_(point1),
      point1_(point2),
      sorted_index_(0),
      flags_(0) {}

  bool operator==(const site_event& that) const {
    return (this->point0_ == that.point0_) &&
           (this->point1_ == that.point1_);
  }

  bool operator!=(const site_event& that) const {
    return (this->point0_ != that.point0_) ||
           (this->point1_ != that.point1_);
  }

  coordinate_type x() const {
    return point0_.x();
  }

  coordinate_type y() const {
    return point0_.y();
  }

  coordinate_type x0() const {
    return point0_.x();
  }

  coordinate_type y0() const {
    return point0_.y();
  }

  coordinate_type x1() const {
    return point1_.x();
  }

  coordinate_type y1() const {
    return point1_.y();
  }

  const point_type& point0() const {
    return point0_;
  }

  const point_type& point1() const {
    return point1_;
  }

  std::size_t sorted_index() const {
    return sorted_index_;
  }

  site_event& sorted_index(std::size_t index) {
    sorted_index_ = index;
    return *this;
  }

  std::size_t initial_index() const {
    return initial_index_;
  }

  site_event& initial_index(std::size_t index) {
    initial_index_ = index;
    return *this;
  }

  bool is_inverse() const {
    return (flags_ & IS_INVERSE) ? true : false;
  }

  site_event& inverse() {
    std::swap(point0_, point1_);
    flags_ ^= IS_INVERSE;
    return *this;
  }

  SourceCategory source_category() const {
    return static_cast<SourceCategory>(flags_ & SOURCE_CATEGORY_BITMASK);
  }

  site_event& source_category(SourceCategory source_category) {
    flags_ |= source_category;
    return *this;
  }

  bool is_point() const {
    return (point0_.x() == point1_.x()) && (point0_.y() == point1_.y());
  }

  bool is_segment() const {
    return (point0_.x() != point1_.x()) || (point0_.y() != point1_.y());
  }

 private:
  enum Bits {
    IS_INVERSE = 0x20  // 32
  };

  point_type point0_;
  point_type point1_;
  std::size_t sorted_index_;
  std::size_t initial_index_;
  std::size_t flags_;
};

// Circle event type.
// Occurs when the sweepline sweeps over the rightmost point of the Voronoi
// circle (with the center at the intersection point of the bisectors).
// Circle event is made of the two consecutive nodes in the beach line data
// structure. In case another node was inserted during algorithm execution
// between the given two nodes circle event becomes inactive.
// Variables:
//   center_x_ - center x-coordinate;
//   center_y_ - center y-coordinate;
//   lower_x_ - leftmost x-coordinate;
//   is_active_ - states whether circle event is still active.
// NOTE: lower_y coordinate is always equal to center_y.
template <typename T>
class circle_event {
 public:
  typedef T coordinate_type;

  circle_event() : is_active_(true) {}

  circle_event(coordinate_type c_x,
               coordinate_type c_y,
               coordinate_type lower_x) :
      center_x_(c_x),
      center_y_(c_y),
      lower_x_(lower_x),
      is_active_(true) {}

  coordinate_type x() const {
    return center_x_;
  }

  circle_event& x(coordinate_type center_x) {
    center_x_ = center_x;
    return *this;
  }

  coordinate_type y() const {
    return center_y_;
  }

  circle_event& y(coordinate_type center_y) {
    center_y_ = center_y;
    return *this;
  }

  coordinate_type lower_x() const {
    return lower_x_;
  }

  circle_event& lower_x(coordinate_type lower_x) {
    lower_x_ = lower_x;
    return *this;
  }

  coordinate_type lower_y() const {
    return center_y_;
  }

  bool is_active() const {
    return is_active_;
  }

  circle_event& deactivate() {
    is_active_ = false;
    return *this;
  }

 private:
  coordinate_type center_x_;
  coordinate_type center_y_;
  coordinate_type lower_x_;
  bool is_active_;
};

// Event queue data structure, holds circle events.
// During algorithm run, some of the circle events disappear (become
// inactive). Priority queue data structure doesn't support
// iterators (there is no direct ability to modify its elements).
// Instead list is used to store all the circle events and priority queue
// of the iterators to the list elements is used to keep the correct circle
// events ordering.
template <typename T, typename Predicate>
class ordered_queue {
 public:
  ordered_queue() {}

  bool empty() const {
    return c_.empty();
  }

  const T &top() const {
    return *c_.top();
  }

  void pop() {
    list_iterator_type it = c_.top();
    c_.pop();
    c_list_.erase(it);
  }

  T &push(const T &e) {
    c_list_.push_front(e);
    c_.push(c_list_.begin());
    return c_list_.front();
  }

  void clear() {
    while (!c_.empty())
        c_.pop();
    c_list_.clear();
  }

 private:
  typedef typename std::list<T>::iterator list_iterator_type;

  struct comparison {
    bool operator() (const list_iterator_type &it1,
                     const list_iterator_type &it2) const {
      return cmp_(*it1, *it2);
    }
    Predicate cmp_;
  };

  std::priority_queue< list_iterator_type,
                       std::vector<list_iterator_type>,
                       comparison > c_;
  std::list<T> c_list_;

  // Disallow copy constructor and operator=
  ordered_queue(const ordered_queue&);
  void operator=(const ordered_queue&);
};

// Represents a bisector node made by two arcs that correspond to the left
// and right sites. Arc is defined as a curve with points equidistant from
// the site and from the sweepline. If the site is a point then arc is
// a parabola, otherwise it's a line segment. A segment site event will
// produce different bisectors based on its direction.
// In general case two sites will create two opposite bisectors. That's
// why the order of the sites is important to define the unique bisector.
// The one site is considered to be newer than the other one if it was
// processed by the algorithm later (has greater index).
template <typename Site>
class beach_line_node_key {
 public:
  typedef Site site_type;

  // Constructs degenerate bisector, used to search an arc that is above
  // the given site. The input to the constructor is the new site point.
  explicit beach_line_node_key(const site_type &new_site) :
      left_site_(new_site),
      right_site_(new_site) {}

  // Constructs a new bisector. The input to the constructor is the two
  // sites that create the bisector. The order of sites is important.
  beach_line_node_key(const site_type &left_site,
                      const site_type &right_site) :
      left_site_(left_site),
      right_site_(right_site) {}

  const site_type &left_site() const {
    return left_site_;
  }

  site_type &left_site() {
    return left_site_;
  }

  beach_line_node_key& left_site(const site_type &site) {
    left_site_ = site;
    return *this;
  }

  const site_type &right_site() const {
    return right_site_;
  }

  site_type &right_site() {
    return right_site_;
  }

  beach_line_node_key& right_site(const site_type &site) {
    right_site_ = site;
    return *this;
  }

 private:
  site_type left_site_;
  site_type right_site_;
};

// Represents edge data structure from the Voronoi output, that is
// associated as a value with beach line bisector in the beach
// line. Contains pointer to the circle event in the circle event
// queue if the edge corresponds to the right bisector of the circle event.
template <typename Edge, typename Circle>
class beach_line_node_data {
 public:
  explicit beach_line_node_data(Edge* new_edge) :
      circle_event_(NULL),
      edge_(new_edge) {}

  Circle* circle_event() const {
    return circle_event_;
  }

  beach_line_node_data& circle_event(Circle* circle_event) {
    circle_event_ = circle_event;
    return *this;
  }

  Edge* edge() const {
    return edge_;
  }

  beach_line_node_data& edge(Edge* new_edge) {
    edge_ = new_edge;
    return *this;
  }

 private:
  Circle* circle_event_;
  Edge* edge_;
};
}  // detail
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_DETAIL_VORONOI_STRUCTURES

/* voronoi_structures.hpp
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
*/
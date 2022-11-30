/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_SET_DATA_HPP
#define BOOST_POLYGON_POLYGON_90_SET_DATA_HPP
#include "isotropy.hpp"
#include "point_concept.hpp"
#include "transform.hpp"
#include "interval_concept.hpp"
#include "rectangle_concept.hpp"
#include "segment_concept.hpp"
#include "detail/iterator_points_to_compact.hpp"
#include "detail/iterator_compact_to_points.hpp"
#include "polygon_traits.hpp"

//manhattan boolean algorithms
#include "detail/boolean_op.hpp"
#include "detail/polygon_formation.hpp"
#include "detail/rectangle_formation.hpp"
#include "detail/max_cover.hpp"
#include "detail/property_merge.hpp"
#include "detail/polygon_90_touch.hpp"
#include "detail/iterator_geometry_to_set.hpp"

namespace boost { namespace polygon{
  template <typename ltype, typename rtype, typename op_type>
  class polygon_90_set_view;

  template <typename T>
  class polygon_90_set_data {
  public:
    typedef T coordinate_type;
    typedef std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > > value_type;
    typedef typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::const_iterator iterator_type;
    typedef polygon_90_set_data operator_arg_type;

    // default constructor
    inline polygon_90_set_data() : orient_(HORIZONTAL), data_(), dirty_(false), unsorted_(false) {}

    // constructor
    inline polygon_90_set_data(orientation_2d orient) : orient_(orient), data_(), dirty_(false), unsorted_(false) {}

    // constructor from an iterator pair over vertex data
    template <typename iT>
    inline polygon_90_set_data(orientation_2d, iT input_begin, iT input_end) :
      orient_(HORIZONTAL), data_(), dirty_(false), unsorted_(false) {
      dirty_ = true;
      unsorted_ = true;
      for( ; input_begin != input_end; ++input_begin) { insert(*input_begin); }
    }

    // copy constructor
    inline polygon_90_set_data(const polygon_90_set_data& that) :
      orient_(that.orient_), data_(that.data_), dirty_(that.dirty_), unsorted_(that.unsorted_) {}

    template <typename ltype, typename rtype, typename op_type>
    inline polygon_90_set_data(const polygon_90_set_view<ltype, rtype, op_type>& that);

    // copy with orientation change constructor
    inline polygon_90_set_data(orientation_2d orient, const polygon_90_set_data& that) :
      orient_(orient), data_(), dirty_(false), unsorted_(false) {
      insert(that, false, that.orient_);
    }

    // destructor
    inline ~polygon_90_set_data() {}

    // assignement operator
    inline polygon_90_set_data& operator=(const polygon_90_set_data& that) {
      if(this == &that) return *this;
      orient_ = that.orient_;
      data_ = that.data_;
      dirty_ = that.dirty_;
      unsorted_ = that.unsorted_;
      return *this;
    }

    template <typename ltype, typename rtype, typename op_type>
    inline polygon_90_set_data& operator=(const polygon_90_set_view<ltype, rtype, op_type>& that);

    template <typename geometry_object>
    inline polygon_90_set_data& operator=(const geometry_object& geometry) {
      data_.clear();
      insert(geometry);
      return *this;
    }

    // insert iterator range
    inline void insert(iterator_type input_begin, iterator_type input_end, orientation_2d orient = HORIZONTAL) {
      if(input_begin == input_end || (!data_.empty() && &(*input_begin) == &(*(data_.begin())))) return;
      dirty_ = true;
      unsorted_ = true;
      if(orient == orient_)
        data_.insert(data_.end(), input_begin, input_end);
      else {
        for( ; input_begin != input_end; ++input_begin) {
          insert(*input_begin, false, orient);
        }
      }
    }

    // insert iterator range
    template <typename iT>
    inline void insert(iT input_begin, iT input_end, orientation_2d orient = HORIZONTAL) {
      if(input_begin == input_end) return;
      dirty_ = true;
      unsorted_ = true;
      for( ; input_begin != input_end; ++input_begin) {
        insert(*input_begin, false, orient);
      }
    }

    inline void insert(const polygon_90_set_data& polygon_set) {
      insert(polygon_set.begin(), polygon_set.end(), polygon_set.orient());
    }

    inline void insert(const std::pair<std::pair<point_data<coordinate_type>, point_data<coordinate_type> >, int>& edge, bool is_hole = false,
                       orientation_2d = HORIZONTAL) {
      std::pair<coordinate_type, std::pair<coordinate_type, int> > vertex;
      vertex.first = edge.first.first.x();
      vertex.second.first = edge.first.first.y();
      vertex.second.second = edge.second * (is_hole ? -1 : 1);
      insert(vertex, false, VERTICAL);
      vertex.first = edge.first.second.x();
      vertex.second.first = edge.first.second.y();
      vertex.second.second *= -1;
      insert(vertex, false, VERTICAL);
    }

    template <typename geometry_type>
    inline void insert(const geometry_type& geometry_object, bool is_hole = false, orientation_2d = HORIZONTAL) {
      iterator_geometry_to_set<typename geometry_concept<geometry_type>::type, geometry_type>
        begin_input(geometry_object, LOW, orient_, is_hole), end_input(geometry_object, HIGH, orient_, is_hole);
      insert(begin_input, end_input, orient_);
    }

    inline void insert(const std::pair<coordinate_type, std::pair<coordinate_type, int> >& vertex, bool is_hole = false,
                       orientation_2d orient = HORIZONTAL) {
      data_.push_back(vertex);
      if(orient != orient_) std::swap(data_.back().first, data_.back().second.first);
      if(is_hole) data_.back().second.second *= -1;
      dirty_ = true;
      unsorted_ = true;
    }

    inline void insert(coordinate_type major_coordinate, const std::pair<interval_data<coordinate_type>, int>& edge) {
      std::pair<coordinate_type, std::pair<coordinate_type, int> > vertex;
      vertex.first = major_coordinate;
      vertex.second.first = edge.first.get(LOW);
      vertex.second.second = edge.second;
      insert(vertex, false, orient_);
      vertex.second.first = edge.first.get(HIGH);
      vertex.second.second *= -1;
      insert(vertex, false, orient_);
    }

    template <typename output_container>
    inline void get(output_container& output) const {
      get_dispatch(output, typename geometry_concept<typename output_container::value_type>::type());
    }

    template <typename output_container>
    inline void get(output_container& output, size_t vthreshold) const {
      get_dispatch(output, typename geometry_concept<typename output_container::value_type>::type(), vthreshold);
    }


    template <typename output_container>
    inline void get_polygons(output_container& output) const {
      get_dispatch(output, polygon_90_concept());
    }

    template <typename output_container>
    inline void get_rectangles(output_container& output) const {
      clean();
      form_rectangles(output, data_.begin(), data_.end(), orient_, rectangle_concept());
    }

    template <typename output_container>
    inline void get_rectangles(output_container& output, orientation_2d slicing_orientation) const {
      if(slicing_orientation == orient_) {
        get_rectangles(output);
      } else {
        polygon_90_set_data<coordinate_type> ps(*this);
        ps.transform(axis_transformation(axis_transformation::SWAP_XY));
        output_container result;
        ps.get_rectangles(result);
        for(typename output_container::iterator itr = result.begin(); itr != result.end(); ++itr) {
          ::boost::polygon::transform(*itr, axis_transformation(axis_transformation::SWAP_XY));
        }
        output.insert(output.end(), result.begin(), result.end());
      }
    }

    // equivalence operator
    inline bool operator==(const polygon_90_set_data& p) const {
      if(orient_ == p.orient()) {
        clean();
        p.clean();
        return data_ == p.data_;
      } else {
        return false;
      }
    }

    // inequivalence operator
    inline bool operator!=(const polygon_90_set_data& p) const {
      return !((*this) == p);
    }

    // get iterator to begin vertex data
    inline iterator_type begin() const {
      return data_.begin();
    }

    // get iterator to end vertex data
    inline iterator_type end() const {
      return data_.end();
    }

    const value_type& value() const {
      return data_;
    }

    // clear the contents of the polygon_90_set_data
    inline void clear() { data_.clear(); dirty_ = unsorted_ = false; }

    // find out if Polygon set is empty
    inline bool empty() const { clean(); return data_.empty(); }

    // get the Polygon set size in vertices
    inline std::size_t size() const { clean(); return data_.size(); }

    // get the current Polygon set capacity in vertices
    inline std::size_t capacity() const { return data_.capacity(); }

    // reserve size of polygon set in vertices
    inline void reserve(std::size_t size) { return data_.reserve(size); }

    // find out if Polygon set is sorted
    inline bool sorted() const { return !unsorted_; }

    // find out if Polygon set is clean
    inline bool dirty() const { return dirty_; }

    // get the scanline orientation of the polygon set
    inline orientation_2d orient() const { return orient_; }

    // Start BM
    // The problem: If we have two polygon sets with two different scanline orientations:
    // I tried changing the orientation of one to coincide with other (If not, resulting boolean operation
    // produces spurious results).
    // First I tried copying polygon data from one of the sets into another set with corrected orientation
    // using one of the copy constructor that takes in orientation (see somewhere above in this file) --> copy constructor throws error
    // Then I tried another approach:(see below). This approach also fails to produce the desired results when test case is run.
    // Here is the part that beats me: If I comment out the whole section, I can do all the operations (^=, -=, &= )these commented out
    // operations perform. So then why do we need them?. Hence, I commented out this whole section.
    // End BM
    // polygon_90_set_data<coordinate_type>& operator-=(const polygon_90_set_data& that) {
    //   sort();
    //   that.sort();
    //   value_type data;
    //   std::swap(data, data_);
    //   applyBooleanBinaryOp(data.begin(), data.end(),
    //                        that.begin(), that.end(), boolean_op::BinaryCount<boolean_op::BinaryNot>());
    //   return *this;
    // }
    // polygon_90_set_data<coordinate_type>& operator^=(const polygon_90_set_data& that) {
    //   sort();
    //   that.sort();
    //   value_type data;
    //   std::swap(data, data_);
    //   applyBooleanBinaryOp(data.begin(), data.end(),
    //                        that.begin(), that.end(),  boolean_op::BinaryCount<boolean_op::BinaryXor>());
    //   return *this;
    // }
    // polygon_90_set_data<coordinate_type>& operator&=(const polygon_90_set_data& that) {
    //   sort();
    //   that.sort();
    //   value_type data;
    //   std::swap(data, data_);
    //   applyBooleanBinaryOp(data.begin(), data.end(),
    //                        that.begin(), that.end(), boolean_op::BinaryCount<boolean_op::BinaryAnd>());
    //   return *this;
    // }
    // polygon_90_set_data<coordinate_type>& operator|=(const polygon_90_set_data& that) {
    //   insert(that);
    //   return *this;
    // }

    void clean() const {
      sort();
      if(dirty_) {
        boolean_op::default_arg_workaround<int>::applyBooleanOr(data_);
        dirty_ = false;
      }
    }

    void sort() const{
      if(unsorted_) {
        polygon_sort(data_.begin(), data_.end());
        unsorted_ = false;
      }
    }

    template <typename input_iterator_type>
    void set(input_iterator_type input_begin, input_iterator_type input_end, orientation_2d orient) {
      data_.clear();
      reserve(std::distance(input_begin, input_end));
      data_.insert(data_.end(), input_begin, input_end);
      orient_ = orient;
      dirty_ = true;
      unsorted_ = true;
    }

    void set(const value_type& value, orientation_2d orient) {
      data_ = value;
      orient_ = orient;
      dirty_ = true;
      unsorted_ = true;
    }

    //extents
    template <typename rectangle_type>
    bool
    extents(rectangle_type& extents_rectangle) const {
      clean();
      if(data_.empty()) return false;
      if(orient_ == HORIZONTAL)
        set_points(extents_rectangle, point_data<coordinate_type>(data_[0].second.first, data_[0].first),
                   point_data<coordinate_type>(data_[data_.size() - 1].second.first, data_[data_.size() - 1].first));
      else
        set_points(extents_rectangle, point_data<coordinate_type>(data_[0].first, data_[0].second.first),
                   point_data<coordinate_type>(data_[data_.size() - 1].first, data_[data_.size() - 1].second.first));
      for(std::size_t i = 1; i < data_.size() - 1; ++i) {
        if(orient_ == HORIZONTAL)
          encompass(extents_rectangle, point_data<coordinate_type>(data_[i].second.first, data_[i].first));
        else
          encompass(extents_rectangle, point_data<coordinate_type>(data_[i].first, data_[i].second.first));
      }
      return true;
    }

    polygon_90_set_data&
    bloat2(typename coordinate_traits<coordinate_type>::unsigned_area_type west_bloating,
          typename coordinate_traits<coordinate_type>::unsigned_area_type east_bloating,
          typename coordinate_traits<coordinate_type>::unsigned_area_type south_bloating,
          typename coordinate_traits<coordinate_type>::unsigned_area_type north_bloating) {
      std::vector<rectangle_data<coordinate_type> > rects;
      clean();
      rects.reserve(data_.size() / 2);
      get(rects);
      rectangle_data<coordinate_type> convolutionRectangle(interval_data<coordinate_type>(-((coordinate_type)west_bloating),
                                                                                          (coordinate_type)east_bloating),
                                                           interval_data<coordinate_type>(-((coordinate_type)south_bloating),
                                                                                          (coordinate_type)north_bloating));
      for(typename std::vector<rectangle_data<coordinate_type> >::iterator itr = rects.begin();
          itr != rects.end(); ++itr) {
        convolve(*itr, convolutionRectangle);
      }
      clear();
      insert(rects.begin(), rects.end());
      return *this;
    }

    static void modify_pt(point_data<coordinate_type>& pt, const point_data<coordinate_type>&  prev_pt,
                          const point_data<coordinate_type>&  current_pt,  const point_data<coordinate_type>&  next_pt,
                          coordinate_type west_bloating,
                          coordinate_type east_bloating,
                          coordinate_type south_bloating,
                          coordinate_type north_bloating) {
      bool pxl = prev_pt.x() < current_pt.x();
      bool pyl = prev_pt.y() < current_pt.y();
      bool nxl = next_pt.x() < current_pt.x();
      bool nyl = next_pt.y() < current_pt.y();
      bool pxg = prev_pt.x() > current_pt.x();
      bool pyg = prev_pt.y() > current_pt.y();
      bool nxg = next_pt.x() > current_pt.x();
      bool nyg = next_pt.y() > current_pt.y();
      //two of the four if statements will execute
      if(pxl)
        pt.y(current_pt.y() - south_bloating);
      if(pxg)
        pt.y(current_pt.y() + north_bloating);
      if(nxl)
        pt.y(current_pt.y() + north_bloating);
      if(nxg)
        pt.y(current_pt.y() - south_bloating);
      if(pyl)
        pt.x(current_pt.x() + east_bloating);
      if(pyg)
        pt.x(current_pt.x() - west_bloating);
      if(nyl)
        pt.x(current_pt.x() - west_bloating);
      if(nyg)
        pt.x(current_pt.x() + east_bloating);
    }
    static void resize_poly_up(std::vector<point_data<coordinate_type> >& poly,
                               coordinate_type west_bloating,
                               coordinate_type east_bloating,
                               coordinate_type south_bloating,
                               coordinate_type north_bloating) {
      point_data<coordinate_type> first_pt = poly[0];
      point_data<coordinate_type> second_pt = poly[1];
      point_data<coordinate_type> prev_pt = poly[0];
      point_data<coordinate_type> current_pt = poly[1];
      for(std::size_t i = 2; i < poly.size(); ++i) {
        point_data<coordinate_type> next_pt = poly[i];
        modify_pt(poly[i-1], prev_pt, current_pt, next_pt, west_bloating, east_bloating, south_bloating, north_bloating);
        prev_pt = current_pt;
        current_pt = next_pt;
      }
      point_data<coordinate_type> next_pt = first_pt;
      modify_pt(poly.back(), prev_pt, current_pt, next_pt, west_bloating, east_bloating, south_bloating, north_bloating);
      prev_pt = current_pt;
      current_pt = next_pt;
      next_pt = second_pt;
      modify_pt(poly[0], prev_pt, current_pt, next_pt, west_bloating, east_bloating, south_bloating, north_bloating);
      remove_colinear_pts(poly);
    }
    static bool resize_poly_down(std::vector<point_data<coordinate_type> >& poly,
                                 coordinate_type west_shrinking,
                                 coordinate_type east_shrinking,
                                 coordinate_type south_shrinking,
                                 coordinate_type north_shrinking) {
      rectangle_data<coordinate_type> extents_rectangle;
      set_points(extents_rectangle, poly[0], poly[0]);
      point_data<coordinate_type> first_pt = poly[0];
      point_data<coordinate_type> second_pt = poly[1];
      point_data<coordinate_type> prev_pt = poly[0];
      point_data<coordinate_type> current_pt = poly[1];
      encompass(extents_rectangle, current_pt);
      for(std::size_t i = 2; i < poly.size(); ++i) {
        point_data<coordinate_type> next_pt = poly[i];
        encompass(extents_rectangle, next_pt);
        modify_pt(poly[i-1], prev_pt, current_pt, next_pt, west_shrinking, east_shrinking, south_shrinking, north_shrinking);
        prev_pt = current_pt;
        current_pt = next_pt;
      }
      if(delta(extents_rectangle, HORIZONTAL) < std::abs(west_shrinking + east_shrinking))
        return false;
      if(delta(extents_rectangle, VERTICAL) < std::abs(north_shrinking + south_shrinking))
        return false;
      point_data<coordinate_type> next_pt = first_pt;
      modify_pt(poly.back(), prev_pt, current_pt, next_pt, west_shrinking, east_shrinking, south_shrinking, north_shrinking);
      prev_pt = current_pt;
      current_pt = next_pt;
      next_pt = second_pt;
      modify_pt(poly[0], prev_pt, current_pt, next_pt, west_shrinking, east_shrinking, south_shrinking, north_shrinking);
      return remove_colinear_pts(poly);
    }

    static bool remove_colinear_pts(std::vector<point_data<coordinate_type> >& poly) {
      bool found_colinear = true;
      while(found_colinear && poly.size() >= 4) {
        found_colinear = false;
        typename std::vector<point_data<coordinate_type> >::iterator itr = poly.begin();
        itr += poly.size() - 1; //get last element position
        typename std::vector<point_data<coordinate_type> >::iterator itr2 = poly.begin();
        typename std::vector<point_data<coordinate_type> >::iterator itr3 = itr2;
        ++itr3;
        std::size_t count = 0;
        for( ; itr3 < poly.end(); ++itr3) {
          if(((*itr).x() == (*itr2).x() && (*itr).x() == (*itr3).x()) ||
             ((*itr).y() == (*itr2).y() && (*itr).y() == (*itr3).y()) ) {
            ++count;
            found_colinear = true;
          } else {
            itr = itr2;
            ++itr2;
          }
          *itr2 = *itr3;
        }
        itr3 = poly.begin();
        if(((*itr).x() == (*itr2).x() && (*itr).x() == (*itr3).x()) ||
           ((*itr).y() == (*itr2).y() && (*itr).y() == (*itr3).y()) ) {
          ++count;
          found_colinear = true;
        }
        poly.erase(poly.end() - count, poly.end());
      }
      return poly.size() >= 4;
    }

    polygon_90_set_data&
    bloat(typename coordinate_traits<coordinate_type>::unsigned_area_type west_bloating,
           typename coordinate_traits<coordinate_type>::unsigned_area_type east_bloating,
           typename coordinate_traits<coordinate_type>::unsigned_area_type south_bloating,
           typename coordinate_traits<coordinate_type>::unsigned_area_type north_bloating) {
      std::list<polygon_45_with_holes_data<coordinate_type> > polys;
      get(polys);
      clear();
      for(typename std::list<polygon_45_with_holes_data<coordinate_type> >::iterator itr = polys.begin();
          itr != polys.end(); ++itr) {
        //polygon_90_set_data<coordinate_type> psref;
        //psref.insert(view_as<polygon_90_concept>((*itr).self_));
        //rectangle_data<coordinate_type> prerect;
        //psref.extents(prerect);
        resize_poly_up((*itr).self_.coords_, (coordinate_type)west_bloating, (coordinate_type)east_bloating,
                       (coordinate_type)south_bloating, (coordinate_type)north_bloating);
        iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
          begin_input(view_as<polygon_90_concept>((*itr).self_), LOW, orient_, false, true, COUNTERCLOCKWISE),
          end_input(view_as<polygon_90_concept>((*itr).self_), HIGH, orient_, false, true, COUNTERCLOCKWISE);
        insert(begin_input, end_input, orient_);
        //polygon_90_set_data<coordinate_type> pstest;
        //pstest.insert(view_as<polygon_90_concept>((*itr).self_));
        //psref.bloat2(west_bloating, east_bloating, south_bloating, north_bloating);
        //if(!equivalence(psref, pstest)) {
        // std::cout << "test failed\n";
        //}
        for(typename std::list<polygon_45_data<coordinate_type> >::iterator itrh = (*itr).holes_.begin();
            itrh != (*itr).holes_.end(); ++itrh) {
          //rectangle_data<coordinate_type> rect;
          //psref.extents(rect);
          //polygon_90_set_data<coordinate_type> psrefhole;
          //psrefhole.insert(prerect);
          //psrefhole.insert(view_as<polygon_90_concept>(*itrh), true);
          //polygon_45_data<coordinate_type> testpoly(*itrh);
          if(resize_poly_down((*itrh).coords_,(coordinate_type)west_bloating, (coordinate_type)east_bloating,
                              (coordinate_type)south_bloating, (coordinate_type)north_bloating)) {
            iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
              begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true),
              end_input2(view_as<polygon_90_concept>(*itrh), HIGH, orient_, true, true);
            insert(begin_input2, end_input2, orient_);
            //polygon_90_set_data<coordinate_type> pstesthole;
            //pstesthole.insert(rect);
            //iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
            // begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true);
            //pstesthole.insert(begin_input2, end_input, orient_);
            //psrefhole.bloat2(west_bloating, east_bloating, south_bloating, north_bloating);
            //if(!equivalence(psrefhole, pstesthole)) {
            // std::cout << (winding(testpoly) == CLOCKWISE) << std::endl;
            // std::cout << (winding(*itrh) == CLOCKWISE) << std::endl;
            // polygon_90_set_data<coordinate_type> c(psrefhole);
            // c.clean();
            // polygon_90_set_data<coordinate_type> a(pstesthole);
            // polygon_90_set_data<coordinate_type> b(pstesthole);
            // a.sort();
            // b.clean();
            // std::cout << "test hole failed\n";
            // //std::cout << testpoly << std::endl;
            //}
          }
        }
      }
      return *this;
    }

    polygon_90_set_data&
    shrink(typename coordinate_traits<coordinate_type>::unsigned_area_type west_shrinking,
           typename coordinate_traits<coordinate_type>::unsigned_area_type east_shrinking,
           typename coordinate_traits<coordinate_type>::unsigned_area_type south_shrinking,
           typename coordinate_traits<coordinate_type>::unsigned_area_type north_shrinking) {
      std::list<polygon_45_with_holes_data<coordinate_type> > polys;
      get(polys);
      clear();
      for(typename std::list<polygon_45_with_holes_data<coordinate_type> >::iterator itr = polys.begin();
          itr != polys.end(); ++itr) {
        //polygon_90_set_data<coordinate_type> psref;
        //psref.insert(view_as<polygon_90_concept>((*itr).self_));
        //rectangle_data<coordinate_type> prerect;
        //psref.extents(prerect);
        //polygon_45_data<coordinate_type> testpoly((*itr).self_);
        if(resize_poly_down((*itr).self_.coords_, -(coordinate_type)west_shrinking, -(coordinate_type)east_shrinking,
                            -(coordinate_type)south_shrinking, -(coordinate_type)north_shrinking)) {
          iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
            begin_input(view_as<polygon_90_concept>((*itr).self_), LOW, orient_, false, true, COUNTERCLOCKWISE),
            end_input(view_as<polygon_90_concept>((*itr).self_), HIGH, orient_, false, true, COUNTERCLOCKWISE);
          insert(begin_input, end_input, orient_);
          //iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
          //  begin_input2(view_as<polygon_90_concept>((*itr).self_), LOW, orient_, false, true, COUNTERCLOCKWISE);
          //polygon_90_set_data<coordinate_type> pstest;
          //pstest.insert(begin_input2, end_input, orient_);
          //psref.shrink2(west_shrinking, east_shrinking, south_shrinking, north_shrinking);
          //if(!equivalence(psref, pstest)) {
          //  std::cout << "test failed\n";
          //}
          for(typename std::list<polygon_45_data<coordinate_type> >::iterator itrh = (*itr).holes_.begin();
              itrh != (*itr).holes_.end(); ++itrh) {
            //rectangle_data<coordinate_type> rect;
            //psref.extents(rect);
            //polygon_90_set_data<coordinate_type> psrefhole;
            //psrefhole.insert(prerect);
            //psrefhole.insert(view_as<polygon_90_concept>(*itrh), true);
            //polygon_45_data<coordinate_type> testpoly(*itrh);
            resize_poly_up((*itrh).coords_, -(coordinate_type)west_shrinking, -(coordinate_type)east_shrinking,
                            -(coordinate_type)south_shrinking, -(coordinate_type)north_shrinking);
            iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
              begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true),
              end_input2(view_as<polygon_90_concept>(*itrh), HIGH, orient_, true, true);
            insert(begin_input2, end_input2, orient_);
            //polygon_90_set_data<coordinate_type> pstesthole;
            //pstesthole.insert(rect);
            //iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
            //  begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true);
            //pstesthole.insert(begin_input2, end_input, orient_);
            //psrefhole.shrink2(west_shrinking, east_shrinking, south_shrinking, north_shrinking);
            //if(!equivalence(psrefhole, pstesthole)) {
            //  std::cout << (winding(testpoly) == CLOCKWISE) << std::endl;
            //  std::cout << (winding(*itrh) == CLOCKWISE) << std::endl;
            //  polygon_90_set_data<coordinate_type> c(psrefhole);
            //  c.clean();
            //  polygon_90_set_data<coordinate_type> a(pstesthole);
            //  polygon_90_set_data<coordinate_type> b(pstesthole);
            //  a.sort();
            //  b.clean();
            //  std::cout << "test hole failed\n";
            //  //std::cout << testpoly << std::endl;
            //}
          }
        }
      }
      return *this;
    }

    polygon_90_set_data&
    shrink2(typename coordinate_traits<coordinate_type>::unsigned_area_type west_shrinking,
            typename coordinate_traits<coordinate_type>::unsigned_area_type east_shrinking,
            typename coordinate_traits<coordinate_type>::unsigned_area_type south_shrinking,
            typename coordinate_traits<coordinate_type>::unsigned_area_type north_shrinking) {
      rectangle_data<coordinate_type> externalBoundary;
      if(!extents(externalBoundary)) return *this;
      ::boost::polygon::bloat(externalBoundary, 10); //bloat by diferential ammount
      //insert a hole that encompasses the data
      insert(externalBoundary, true); //note that the set is in a dirty state now
      sort();  //does not apply implicit OR operation
      std::vector<rectangle_data<coordinate_type> > rects;
      rects.reserve(data_.size() / 2);
      //begin does not apply implicit or operation, this is a dirty range
      form_rectangles(rects, data_.begin(), data_.end(), orient_, rectangle_concept());
      clear();
      rectangle_data<coordinate_type> convolutionRectangle(interval_data<coordinate_type>(-((coordinate_type)east_shrinking),
                                                                                          (coordinate_type)west_shrinking),
                                                           interval_data<coordinate_type>(-((coordinate_type)north_shrinking),
                                                                                          (coordinate_type)south_shrinking));
      for(typename std::vector<rectangle_data<coordinate_type> >::iterator itr = rects.begin();
          itr != rects.end(); ++itr) {
        rectangle_data<coordinate_type>& rect = *itr;
        convolve(rect, convolutionRectangle);
        //insert rectangle as a hole
        insert(rect, true);
      }
      convolve(externalBoundary, convolutionRectangle);
      //insert duplicate of external boundary as solid to cancel out the external hole boundaries
      insert(externalBoundary);
      clean(); //we have negative values in the set, so we need to apply an OR operation to make it valid input to a boolean
      return *this;
    }

    polygon_90_set_data&
    shrink(direction_2d dir, typename coordinate_traits<coordinate_type>::unsigned_area_type shrinking) {
      if(dir == WEST)
        return shrink(shrinking, 0, 0, 0);
      if(dir == EAST)
        return shrink(0, shrinking, 0, 0);
      if(dir == SOUTH)
        return shrink(0, 0, shrinking, 0);
      return shrink(0, 0, 0, shrinking);
    }

    polygon_90_set_data&
    bloat(direction_2d dir, typename coordinate_traits<coordinate_type>::unsigned_area_type shrinking) {
      if(dir == WEST)
        return bloat(shrinking, 0, 0, 0);
      if(dir == EAST)
        return bloat(0, shrinking, 0, 0);
      if(dir == SOUTH)
        return bloat(0, 0, shrinking, 0);
      return bloat(0, 0, 0, shrinking);
    }

    polygon_90_set_data&
    resize(coordinate_type west, coordinate_type east, coordinate_type south, coordinate_type north);

    polygon_90_set_data& move(coordinate_type x_delta, coordinate_type y_delta) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          (*itr).first += x_delta;
          (*itr).second.first += y_delta;
        } else {
          (*itr).second.first += x_delta;
          (*itr).first += y_delta;
        }
      }
      return *this;
    }

    // transform set
    template <typename transformation_type>
    polygon_90_set_data& transform(const transformation_type& transformation) {
      direction_2d dir1, dir2;
      transformation.get_directions(dir1, dir2);
      int sign = dir1.get_sign() * dir2.get_sign();
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          transformation.transform((*itr).first, (*itr).second.first);
        } else {
          transformation.transform((*itr).second.first, (*itr).first);
        }
        (*itr).second.second *= sign;
      }
      if(dir1 != EAST || dir2 != NORTH)
        unsorted_ = true; //some mirroring or rotation must have happened
      return *this;
    }

    // scale set
    polygon_90_set_data& scale_up(typename coordinate_traits<coordinate_type>::unsigned_area_type factor) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        (*itr).first *= (coordinate_type)factor;
        (*itr).second.first *= (coordinate_type)factor;
      }
      return *this;
    }
    polygon_90_set_data& scale_down(typename coordinate_traits<coordinate_type>::unsigned_area_type factor) {
      typedef typename coordinate_traits<coordinate_type>::coordinate_distance dt;
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        (*itr).first = scaling_policy<coordinate_type>::round((dt)((*itr).first) / (dt)factor);
        (*itr).second.first = scaling_policy<coordinate_type>::round((dt)((*itr).second.first) / (dt)factor);
      }
      unsorted_ = true; //scaling down can make coordinates equal that were not previously equal
      return *this;
    }
    template <typename scaling_type>
    polygon_90_set_data& scale(const anisotropic_scale_factor<scaling_type>& scaling) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          scaling.scale((*itr).first, (*itr).second.first);
        } else {
          scaling.scale((*itr).second.first, (*itr).first);
        }
      }
      unsorted_ = true;
      return *this;
    }
    template <typename scaling_type>
    polygon_90_set_data& scale_with(const scaling_type& scaling) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          scaling.scale((*itr).first, (*itr).second.first);
        } else {
          scaling.scale((*itr).second.first, (*itr).first);
        }
      }
      unsorted_ = true;
      return *this;
    }
    polygon_90_set_data& scale(double factor) {
      typedef typename coordinate_traits<coordinate_type>::coordinate_distance dt;
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        (*itr).first = scaling_policy<coordinate_type>::round((dt)((*itr).first) * (dt)factor);
        (*itr).second.first = scaling_policy<coordinate_type>::round((dt)((*itr).second.first) * (dt)factor);
      }
      unsorted_ = true; //scaling make coordinates equal that were not previously equal
      return *this;
    }

    polygon_90_set_data& self_xor() {
      sort();
      if(dirty_) { //if it is clean it is a no-op
        boolean_op::default_arg_workaround<boolean_op::UnaryCount>::applyBooleanOr(data_);
        dirty_ = false;
      }
      return *this;
    }

    polygon_90_set_data& self_intersect() {
      sort();
      if(dirty_) { //if it is clean it is a no-op
        interval_data<coordinate_type> ivl((std::numeric_limits<coordinate_type>::min)(), (std::numeric_limits<coordinate_type>::max)());
        rectangle_data<coordinate_type> rect(ivl, ivl);
        insert(rect, true);
        clean();
      }
      return *this;
    }

    inline polygon_90_set_data& interact(const polygon_90_set_data& that) {
      typedef coordinate_type Unit;
      if(that.dirty_) that.clean();
      typename touch_90_operation<Unit>::TouchSetData tsd;
      touch_90_operation<Unit>::populateTouchSetData(tsd, that.data_, 0);
      std::vector<polygon_90_data<Unit> > polys;
      get(polys);
      std::vector<std::set<int> > graph(polys.size()+1, std::set<int>());
      for(std::size_t i = 0; i < polys.size(); ++i){
        polygon_90_set_data<Unit> psTmp(that.orient_);
        psTmp.insert(polys[i]);
        psTmp.clean();
        touch_90_operation<Unit>::populateTouchSetData(tsd, psTmp.data_, i+1);
      }
      touch_90_operation<Unit>::performTouch(graph, tsd);
      clear();
      for(std::set<int>::iterator itr = graph[0].begin(); itr != graph[0].end(); ++itr){
        insert(polys[(*itr)-1]);
      }
      dirty_ = false;
      return *this;
    }


    template <class T2, typename iterator_type_1, typename iterator_type_2>
    void applyBooleanBinaryOp(iterator_type_1 itr1, iterator_type_1 itr1_end,
                              iterator_type_2 itr2, iterator_type_2 itr2_end,
                              T2 defaultCount) {
      data_.clear();
      boolean_op::applyBooleanBinaryOp(data_, itr1, itr1_end, itr2, itr2_end, defaultCount);
    }

  private:
    orientation_2d orient_;
    mutable value_type data_;
    mutable bool dirty_;
    mutable bool unsorted_;

  private:
    //functions
    template <typename output_container>
    void get_dispatch(output_container& output, rectangle_concept ) const {
      clean();
      form_rectangles(output, data_.begin(), data_.end(), orient_, rectangle_concept());
    }
    template <typename output_container>
    void get_dispatch(output_container& output, polygon_90_concept tag) const {
      get_fracture(output, true, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_90_concept tag,
      size_t vthreshold) const {
      get_fracture(output, true, tag, vthreshold);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_90_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_90_with_holes_concept tag,
      size_t vthreshold) const {
      get_fracture(output, false, tag, vthreshold);
    }


    template <typename output_container>
    void get_dispatch(output_container& output, polygon_45_concept tag) const {
      get_fracture(output, true, tag);
    }
    template <typename output_container>
    void get_dispatch(output_container& output, polygon_45_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }
    template <typename output_container>
    void get_dispatch(output_container& output, polygon_concept tag) const {
      get_fracture(output, true, tag);
    }
    template <typename output_container>
    void get_dispatch(output_container& output, polygon_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }
    template <typename output_container, typename concept_type>
    void get_fracture(output_container& container, bool fracture_holes, concept_type tag) const {
      clean();
      ::boost::polygon::get_polygons(container, data_.begin(), data_.end(), orient_, fracture_holes, tag);
    }

    template <typename output_container, typename concept_type>
    void get_fracture(output_container& container, bool fracture_holes, concept_type tag,
      size_t vthreshold) const {
      clean();
      ::boost::polygon::get_polygons(container, data_.begin(), data_.end(), orient_, fracture_holes, tag, vthreshold);
    }
  };

  template <typename coordinate_type>
  polygon_90_set_data<coordinate_type>&
  polygon_90_set_data<coordinate_type>::resize(coordinate_type west,
                                               coordinate_type east,
                                               coordinate_type south,
                                               coordinate_type north) {
    move(-west, -south);
    coordinate_type e_total = west + east;
    coordinate_type n_total = south + north;
    if((e_total < 0) ^ (n_total < 0)) {
      //different signs
      if(e_total < 0) {
        shrink(0, -e_total, 0, 0);
        if(n_total != 0)
          return bloat(0, 0, 0, n_total);
        else
          return (*this);
      } else {
        shrink(0, 0, 0, -n_total); //shrink first
        if(e_total != 0)
          return bloat(0, e_total, 0, 0);
        else
          return (*this);
      }
    } else {
      if(e_total < 0) {
        return shrink(0, -e_total, 0, -n_total);
      }
      return bloat(0, e_total, 0, n_total);
    }
  }

  template <typename coordinate_type, typename property_type>
  class property_merge_90 {
  private:
    std::vector<std::pair<property_merge_point<coordinate_type>, std::pair<property_type, int> > > pmd_;
  public:
    inline property_merge_90() : pmd_() {}
    inline property_merge_90(const property_merge_90& that) : pmd_(that.pmd_) {}
    inline property_merge_90& operator=(const property_merge_90& that) { pmd_ = that.pmd_; return *this; }
    inline void insert(const polygon_90_set_data<coordinate_type>& ps, const property_type& property) {
      merge_scanline<coordinate_type, property_type, polygon_90_set_data<coordinate_type> >::
        populate_property_merge_data(pmd_, ps.begin(), ps.end(), property, ps.orient());
    }
    template <class GeoObjT>
    inline void insert(const GeoObjT& geoObj, const property_type& property) {
      polygon_90_set_data<coordinate_type> ps;
      ps.insert(geoObj);
      insert(ps, property);
    }
    //merge properties of input geometries and store the resulting geometries of regions
    //with unique sets of merged properties to polygons sets in a map keyed by sets of properties
    // T = std::map<std::set<property_type>, polygon_90_set_data<coordiante_type> > or
    // T = std::map<std::vector<property_type>, polygon_90_set_data<coordiante_type> >
    template <typename ResultType>
    inline void merge(ResultType& result) {
      merge_scanline<coordinate_type, property_type, polygon_90_set_data<coordinate_type>, typename ResultType::key_type> ms;
      ms.perform_merge(result, pmd_);
    }
  };

  //ConnectivityExtraction computes the graph of connectivity between rectangle, polygon and
  //polygon set graph nodes where an edge is created whenever the geometry in two nodes overlap
  template <typename coordinate_type>
  class connectivity_extraction_90 {
  private:
    typedef typename touch_90_operation<coordinate_type>::TouchSetData tsd;
    tsd tsd_;
    unsigned int nodeCount_;
  public:
    inline connectivity_extraction_90() : tsd_(), nodeCount_(0) {}
    inline connectivity_extraction_90(const connectivity_extraction_90& that) : tsd_(that.tsd_),
                                                                          nodeCount_(that.nodeCount_) {}
    inline connectivity_extraction_90& operator=(const connectivity_extraction_90& that) {
      tsd_ = that.tsd_;
      nodeCount_ = that.nodeCount_; {}
      return *this;
    }

    //insert a polygon set graph node, the value returned is the id of the graph node
    inline unsigned int insert(const polygon_90_set_data<coordinate_type>& ps) {
      ps.clean();
      touch_90_operation<coordinate_type>::populateTouchSetData(tsd_, ps.begin(), ps.end(), nodeCount_);
      return nodeCount_++;
    }
    template <class GeoObjT>
    inline unsigned int insert(const GeoObjT& geoObj) {
      polygon_90_set_data<coordinate_type> ps;
      ps.insert(geoObj);
      return insert(ps);
    }

    //extract connectivity and store the edges in the graph
    //graph must be indexable by graph node id and the indexed value must be a std::set of
    //graph node id
    template <class GraphT>
    inline void extract(GraphT& graph) {
      touch_90_operation<coordinate_type>::performTouch(graph, tsd_);
    }
  };
}
}
#endif

/* polygon_90_set_data.hpp
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
*/
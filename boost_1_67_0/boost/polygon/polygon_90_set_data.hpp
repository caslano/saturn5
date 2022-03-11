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
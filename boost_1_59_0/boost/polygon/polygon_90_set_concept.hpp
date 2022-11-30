/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_SET_CONCEPT_HPP
#define BOOST_POLYGON_POLYGON_90_SET_CONCEPT_HPP
#include "polygon_90_set_data.hpp"
#include "polygon_90_set_traits.hpp"
namespace boost { namespace polygon{

  template <typename polygon_set_type>
  typename enable_if< typename is_polygon_90_set_type<polygon_set_type>::type,
                       typename polygon_90_set_traits<polygon_set_type>::iterator_type>::type
  begin_90_set_data(const polygon_set_type& polygon_set) {
    return polygon_90_set_traits<polygon_set_type>::begin(polygon_set);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_polygon_90_set_type<polygon_set_type>::type,
                       typename polygon_90_set_traits<polygon_set_type>::iterator_type>::type
  end_90_set_data(const polygon_set_type& polygon_set) {
    return polygon_90_set_traits<polygon_set_type>::end(polygon_set);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_polygon_90_set_type<polygon_set_type>::type,
                       orientation_2d>::type
  scanline_orientation(const polygon_set_type& polygon_set) {
    return polygon_90_set_traits<polygon_set_type>::orient(polygon_set);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_polygon_90_set_type<polygon_set_type>::type,
                       bool>::type
  clean(const polygon_set_type& polygon_set) {
    return polygon_90_set_traits<polygon_set_type>::clean(polygon_set);
  }

  //assign
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if <
    typename gtl_and<
      typename is_mutable_polygon_90_set_type<polygon_set_type_1>::type,
      typename is_polygon_90_set_type<polygon_set_type_2>::type>::type,
    polygon_set_type_1>::type &
  assign(polygon_set_type_1& lvalue, const polygon_set_type_2& rvalue) {
    polygon_90_set_mutable_traits<polygon_set_type_1>::set(lvalue, begin_90_set_data(rvalue), end_90_set_data(rvalue),
                                                           scanline_orientation(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  struct are_not_both_rectangle_concept { typedef gtl_yes type; };
  template <>
  struct are_not_both_rectangle_concept<rectangle_concept, rectangle_concept> { typedef gtl_no type; };

  //equivalence
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and_3<
    typename is_polygon_90_set_type<polygon_set_type_1>::type,
    typename is_polygon_90_set_type<polygon_set_type_2>::type,
    typename are_not_both_rectangle_concept<typename geometry_concept<polygon_set_type_1>::type,
                                            typename geometry_concept<polygon_set_type_2>::type>::type>::type,
                       bool>::type
  equivalence(const polygon_set_type_1& lvalue,
              const polygon_set_type_2& rvalue) {
    polygon_90_set_data<typename polygon_90_set_traits<polygon_set_type_1>::coordinate_type> ps1;
    assign(ps1, lvalue);
    polygon_90_set_data<typename polygon_90_set_traits<polygon_set_type_2>::coordinate_type> ps2;
    assign(ps2, rvalue);
    return ps1 == ps2;
  }


  //get rectangle tiles (slicing orientation is vertical)
  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_90_set_type<polygon_set_type>::type>::type,
                       void>::type
  get_rectangles(output_container_type& output, const polygon_set_type& polygon_set) {
    clean(polygon_set);
    polygon_90_set_data<typename polygon_90_set_traits<polygon_set_type>::coordinate_type> ps(VERTICAL);
    assign(ps, polygon_set);
    ps.get_rectangles(output);
  }

  //get rectangle tiles
  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_90_set_type<polygon_set_type>::type>::type,
                       void>::type
  get_rectangles(output_container_type& output, const polygon_set_type& polygon_set, orientation_2d slicing_orientation) {
    clean(polygon_set);
    polygon_90_set_data<typename polygon_90_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.get_rectangles(output, slicing_orientation);
  }

  //get: min_rectangles max_rectangles
  template <typename output_container_type, typename polygon_set_type>
  typename enable_if <typename gtl_and<
    typename is_polygon_90_set_type<polygon_set_type>::type,
    typename gtl_same_type<rectangle_concept,
                           typename geometry_concept
                           <typename std::iterator_traits
                            <typename output_container_type::iterator>::value_type>::type>::type>::type,
                       void>::type
  get_max_rectangles(output_container_type& output, const polygon_set_type& polygon_set) {
    std::vector<rectangle_data<typename polygon_90_set_traits<polygon_set_type>::coordinate_type> > rects;
    assign(rects, polygon_set);
    MaxCover<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::getMaxCover(output, rects, scanline_orientation(polygon_set));
  }

  //clear
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       void>::type
  clear(polygon_set_type& polygon_set) {
    polygon_90_set_data<typename polygon_90_set_traits<polygon_set_type>::coordinate_type> ps(scanline_orientation(polygon_set));
    assign(polygon_set, ps);
  }

  //empty
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       bool>::type
  empty(const polygon_set_type& polygon_set) {
    if(clean(polygon_set)) return begin_90_set_data(polygon_set) == end_90_set_data(polygon_set);
    polygon_90_set_data<typename polygon_90_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.clean();
    return ps.empty();
  }

  //extents
  template <typename polygon_set_type, typename rectangle_type>
  typename enable_if <typename gtl_and< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                                         typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       bool>::type
  extents(rectangle_type& extents_rectangle,
                             const polygon_set_type& polygon_set) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    return ps.extents(extents_rectangle);
  }

  //area
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::manhattan_area_type>::type
  area(const polygon_set_type& polygon_set) {
    typedef rectangle_data<typename polygon_90_set_traits<polygon_set_type>::coordinate_type> rectangle_type;
    typedef typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::manhattan_area_type area_type;
    std::vector<rectangle_type> rects;
    assign(rects, polygon_set);
    area_type retval = (area_type)0;
    for(std::size_t i = 0; i < rects.size(); ++i) {
      retval += (area_type)area(rects[i]);
    }
    return retval;
  }

  //interact
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if <typename gtl_and< typename is_mutable_polygon_90_set_type<polygon_set_type_1>::type,
                                         typename is_mutable_polygon_90_set_type<polygon_set_type_2>::type>::type,
                       polygon_set_type_1>::type&
  interact(polygon_set_type_1& polygon_set_1, const polygon_set_type_2& polygon_set_2) {
    typedef typename polygon_90_set_traits<polygon_set_type_1>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps(scanline_orientation(polygon_set_2));
    polygon_90_set_data<Unit> ps2(ps);
    ps.insert(polygon_set_1);
    ps2.insert(polygon_set_2);
    ps.interact(ps2);
    assign(polygon_set_1, ps);
    return polygon_set_1;
  }

  //self_intersect
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  self_intersect(polygon_set_type& polygon_set) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.self_intersect();
    assign(polygon_set, ps);
    return polygon_set;
  }

  //self_xor
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  self_xor(polygon_set_type& polygon_set) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.self_xor();
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    return bloat(polygon_set, bloating, bloating, bloating, bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set, orientation_2d orient,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    if(orient == orientation_2d(HORIZONTAL))
      return bloat(polygon_set, bloating, bloating, 0, 0);
    return bloat(polygon_set, 0, 0, bloating, bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set, orientation_2d orient,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type low_bloating,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type high_bloating) {
    if(orient == orientation_2d(HORIZONTAL))
      return bloat(polygon_set, low_bloating, high_bloating, 0, 0);
    return bloat(polygon_set, 0, 0, low_bloating, high_bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set, direction_2d dir,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    if(dir == direction_2d(EAST))
      return bloat(polygon_set, 0, bloating, 0, 0);
    if(dir == direction_2d(WEST))
      return bloat(polygon_set, bloating, 0, 0, 0);
    if(dir == direction_2d(SOUTH))
      return bloat(polygon_set, 0, 0, bloating, 0);
    return bloat(polygon_set, 0, 0, 0, bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type west_bloating,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type east_bloating,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type south_bloating,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type north_bloating) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.bloat(west_bloating, east_bloating, south_bloating, north_bloating);
    ps.clean();
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type shrinking) {
    return shrink(polygon_set, shrinking, shrinking, shrinking, shrinking);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set, orientation_2d orient,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type shrinking) {
    if(orient == orientation_2d(HORIZONTAL))
      return shrink(polygon_set, shrinking, shrinking, 0, 0);
    return shrink(polygon_set, 0, 0, shrinking, shrinking);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set, orientation_2d orient,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type low_shrinking,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type high_shrinking) {
    if(orient == orientation_2d(HORIZONTAL))
      return shrink(polygon_set, low_shrinking, high_shrinking, 0, 0);
    return shrink(polygon_set, 0, 0, low_shrinking, high_shrinking);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set, direction_2d dir,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type shrinking) {
    if(dir == direction_2d(EAST))
      return shrink(polygon_set, 0, shrinking, 0, 0);
    if(dir == direction_2d(WEST))
      return shrink(polygon_set, shrinking, 0, 0, 0);
    if(dir == direction_2d(SOUTH))
      return shrink(polygon_set, 0, 0, shrinking, 0);
    return shrink(polygon_set, 0, 0, 0, shrinking);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type west_shrinking,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type east_shrinking,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type south_shrinking,
        typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type north_shrinking) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.shrink(west_shrinking, east_shrinking, south_shrinking, north_shrinking);
    ps.clean();
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type, typename coord_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  resize(polygon_set_type& polygon_set, coord_type resizing) {
    if(resizing > 0) {
      return bloat(polygon_set, resizing);
    }
    if(resizing < 0) {
      return shrink(polygon_set, -resizing);
    }
    return polygon_set;
  }

  //positive or negative values allow for any and all directions of sizing
  template <typename polygon_set_type, typename coord_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  resize(polygon_set_type& polygon_set, coord_type west, coord_type east, coord_type south, coord_type north) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.resize(west, east, south, north);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  grow_and(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    return grow_and(polygon_set, bloating, bloating, bloating, bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  grow_and(polygon_set_type& polygon_set, orientation_2d orient,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    if(orient == orientation_2d(HORIZONTAL))
      return grow_and(polygon_set, bloating, bloating, 0, 0);
    return grow_and(polygon_set, 0, 0, bloating, bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  grow_and(polygon_set_type& polygon_set, orientation_2d orient,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type low_bloating,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type high_bloating) {
    if(orient == orientation_2d(HORIZONTAL))
      return grow_and(polygon_set, low_bloating, high_bloating, 0, 0);
    return grow_and(polygon_set, 0, 0, low_bloating, high_bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  grow_and(polygon_set_type& polygon_set, direction_2d dir,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    if(dir == direction_2d(EAST))
      return grow_and(polygon_set, 0, bloating, 0, 0);
    if(dir == direction_2d(WEST))
      return grow_and(polygon_set, bloating, 0, 0, 0);
    if(dir == direction_2d(SOUTH))
      return grow_and(polygon_set, 0, 0, bloating, 0);
    return grow_and(polygon_set, 0, 0, 0, bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_mutable_polygon_90_set_type<polygon_set_type>::type>::type,
                       polygon_set_type>::type &
  grow_and(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type west_bloating,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type east_bloating,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type south_bloating,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type north_bloating) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    std::vector<polygon_90_data<Unit> > polys;
    assign(polys, polygon_set);
    clear(polygon_set);
    polygon_90_set_data<Unit> ps(scanline_orientation(polygon_set));
    for(std::size_t i = 0; i < polys.size(); ++i) {
      polygon_90_set_data<Unit> tmpPs(scanline_orientation(polygon_set));
      tmpPs.insert(polys[i]);
      bloat(tmpPs, west_bloating, east_bloating, south_bloating, north_bloating);
      tmpPs.clean(); //apply implicit OR on tmp polygon set
      ps.insert(tmpPs);
    }
    self_intersect(ps);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_up(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>
           ::unsigned_area_type factor) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_up(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_down(polygon_set_type& polygon_set,
             typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>
             ::unsigned_area_type factor) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_down(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type, typename scaling_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale(polygon_set_type& polygon_set,
        const scaling_type& scaling) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale(scaling);
    assign(polygon_set, ps);
    return polygon_set;
  }

  struct y_p_s_move : gtl_yes {};

  //move
  template <typename polygon_set_type>
  typename enable_if< typename gtl_and<y_p_s_move, typename gtl_if<typename is_mutable_polygon_90_set_type<polygon_set_type>::type>::type>::type,
                      polygon_set_type>::type &
  move(polygon_set_type& polygon_set,
  orientation_2d orient, typename polygon_90_set_traits<polygon_set_type>::coordinate_type displacement) {
    if(orient == HORIZONTAL)
      return move(polygon_set, displacement, 0);
    else
      return move(polygon_set, 0, displacement);
  }

  struct y_p_s_move2 : gtl_yes {};

  template <typename polygon_set_type>
  typename enable_if< typename gtl_and<y_p_s_move2, typename gtl_if<typename is_mutable_polygon_90_set_type<polygon_set_type>::type>::type>::type,
                      polygon_set_type>::type &
  move(polygon_set_type& polygon_set, typename polygon_90_set_traits<polygon_set_type>::coordinate_type x_displacement,
  typename polygon_90_set_traits<polygon_set_type>::coordinate_type y_displacement) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.move(x_displacement, y_displacement);
    ps.clean();
    assign(polygon_set, ps);
    return polygon_set;
  }

  //transform
  template <typename polygon_set_type, typename transformation_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  transform(polygon_set_type& polygon_set,
            const transformation_type& transformation) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_90_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.transform(transformation);
    ps.clean();
    assign(polygon_set, ps);
    return polygon_set;
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
  }

  //keep
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_90_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  keep(polygon_set_type& polygon_set,
       typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_area,
       typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_area,
       typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_width,
       typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_width,
       typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_height,
       typename coordinate_traits<typename polygon_90_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_height) {
    typedef typename polygon_90_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef typename coordinate_traits<Unit>::unsigned_area_type uat;
    std::list<polygon_90_data<Unit> > polys;
    assign(polys, polygon_set);
    clear(polygon_set);
    typename std::list<polygon_90_data<Unit> >::iterator itr_nxt;
    for(typename std::list<polygon_90_data<Unit> >::iterator itr = polys.begin(); itr != polys.end(); itr = itr_nxt){
      itr_nxt = itr;
      ++itr_nxt;
      rectangle_data<Unit> bbox;
      extents(bbox, *itr);
      uat pwidth = delta(bbox, HORIZONTAL);
      if(pwidth > min_width && pwidth <= max_width){
        uat pheight = delta(bbox, VERTICAL);
        if(pheight > min_height && pheight <= max_height){
          uat parea = area(*itr);
          if(parea <= max_area && parea >= min_area) {
            continue;
          }
        }
      }
      polys.erase(itr);
    }
    assign(polygon_set, polys);
    return polygon_set;
  }


}
}
#include "detail/polygon_90_set_view.hpp"
#endif

/* polygon_90_set_concept.hpp
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
*/
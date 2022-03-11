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
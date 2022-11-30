/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_SET_CONCEPT_HPP
#define BOOST_POLYGON_POLYGON_SET_CONCEPT_HPP
#include "polygon_set_data.hpp"
#include "detail/polygon_simplify.hpp"
namespace boost { namespace polygon{

  template <typename T, typename T2>
  struct is_either_polygon_set_type {
    typedef typename gtl_or<typename is_polygon_set_type<T>::type, typename is_polygon_set_type<T2>::type >::type type;
  };

  template <typename T>
  struct is_any_polygon_set_type {
    typedef typename gtl_or<typename is_polygon_45_or_90_set_type<T>::type, typename is_polygon_set_type<T>::type >::type type;
  };

  template <typename polygon_set_type>
  typename enable_if< typename is_any_polygon_set_type<polygon_set_type>::type,
                       typename polygon_set_traits<polygon_set_type>::iterator_type>::type
  begin_polygon_set_data(const polygon_set_type& polygon_set) {
    return polygon_set_traits<polygon_set_type>::begin(polygon_set);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_any_polygon_set_type<polygon_set_type>::type,
                       typename polygon_set_traits<polygon_set_type>::iterator_type>::type
  end_polygon_set_data(const polygon_set_type& polygon_set) {
    return polygon_set_traits<polygon_set_type>::end(polygon_set);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_polygon_set_type<polygon_set_type>::type,
                       bool>::type
  clean(const polygon_set_type& polygon_set) {
    return polygon_set_traits<polygon_set_type>::clean(polygon_set);
  }

  //assign
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and<
    typename is_mutable_polygon_set_type<polygon_set_type_1>::type,
    typename is_any_polygon_set_type<polygon_set_type_2>::type>::type,
                       polygon_set_type_1>::type &
  assign(polygon_set_type_1& lvalue, const polygon_set_type_2& rvalue) {
    if(clean(rvalue))
      polygon_set_mutable_traits<polygon_set_type_1>::set(lvalue, begin_polygon_set_data(rvalue), end_polygon_set_data(rvalue));
    else {
      polygon_set_data<typename polygon_set_traits<polygon_set_type_2>::coordinate_type> ps;
      ps.insert(begin_polygon_set_data(rvalue), end_polygon_set_data(rvalue));
      ps.clean();
      polygon_set_mutable_traits<polygon_set_type_1>::set(lvalue, ps.begin(), ps.end());
    }
    return lvalue;
  }

  //get trapezoids
  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                      void>::type
  get_trapezoids(output_container_type& output, const polygon_set_type& polygon_set) {
    polygon_set_data<typename polygon_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.get_trapezoids(output);
  }

  //get trapezoids
  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                      void>::type
  get_trapezoids(output_container_type& output, const polygon_set_type& polygon_set,
                 orientation_2d orient) {
    polygon_set_data<typename polygon_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.get_trapezoids(output, orient);
  }

  //equivalence
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and_3 <
    typename is_any_polygon_set_type<polygon_set_type_1>::type,
    typename is_any_polygon_set_type<polygon_set_type_2>::type,
    typename is_either_polygon_set_type<polygon_set_type_1, polygon_set_type_2>::type>::type,
                       bool>::type
  equivalence(const polygon_set_type_1& lvalue,
              const polygon_set_type_2& rvalue) {
    polygon_set_data<typename polygon_set_traits<polygon_set_type_1>::coordinate_type> ps1;
    assign(ps1, lvalue);
    polygon_set_data<typename polygon_set_traits<polygon_set_type_2>::coordinate_type> ps2;
    assign(ps2, rvalue);
    return ps1 == ps2;
  }

  //clear
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       void>::type
  clear(polygon_set_type& polygon_set) {
    polygon_set_data<typename polygon_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(polygon_set, ps);
  }

  //empty
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       bool>::type
  empty(const polygon_set_type& polygon_set) {
    if(clean(polygon_set)) return begin_polygon_set_data(polygon_set) == end_polygon_set_data(polygon_set);
    polygon_set_data<typename polygon_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.clean();
    return ps.empty();
  }

  //extents
  template <typename polygon_set_type, typename rectangle_type>
  typename enable_if< typename gtl_and<
    typename is_mutable_polygon_set_type<polygon_set_type>::type,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       bool>::type
  extents(rectangle_type& extents_rectangle,
          const polygon_set_type& polygon_set) {
    clean(polygon_set);
    polygon_set_data<typename polygon_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    return ps.extents(extents_rectangle);
  }

  //area
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::area_type>::type
  area(const polygon_set_type& polygon_set) {
    typedef typename polygon_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef polygon_with_holes_data<Unit> p_type;
    typedef typename coordinate_traits<Unit>::area_type area_type;
    std::vector<p_type> polys;
    assign(polys, polygon_set);
    area_type retval = (area_type)0;
    for(std::size_t i = 0; i < polys.size(); ++i) {
      retval += area(polys[i]);
    }
    return retval;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                      std::size_t>::type
  simplify(polygon_set_type& polygon_set, typename coordinate_traits<
           typename polygon_set_traits<polygon_set_type>::coordinate_type
           >::coordinate_distance threshold) {
    typedef typename polygon_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef polygon_with_holes_data<Unit> p_type;
    std::vector<p_type> polys;
    assign(polys, polygon_set);
    std::size_t retval = 0;
    for(std::size_t i = 0; i < polys.size(); ++i) {
      retval += detail::simplify_detail::simplify(polys[i].self_.coords_,
                                                  polys[i].self_.coords_, threshold);
      for(typename std::list<polygon_data<Unit> >::iterator itrh =
            polys[i].holes_.begin(); itrh != (polys[i].holes_.end()); ++itrh) {
        retval += detail::simplify_detail::simplify((*itrh).coords_,
                                                    (*itrh).coords_, threshold);
      }
    }
    assign(polygon_set, polys);
    return retval;
  }

  template <typename polygon_set_type, typename coord_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  resize(polygon_set_type& polygon_set, coord_type resizing, bool corner_fill_arcs = false, int num_circle_segments = 0) {
    typedef typename polygon_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.resize(resizing, corner_fill_arcs,num_circle_segments);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    return resize(polygon_set, bloating);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type shrinking) {
    return resize(polygon_set, -(typename polygon_set_traits<polygon_set_type>::coordinate_type)shrinking);
  }

  //interact
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and_3 <
    typename is_any_polygon_set_type<polygon_set_type_1>::type,
    typename is_any_polygon_set_type<polygon_set_type_2>::type,
    typename is_either_polygon_set_type<polygon_set_type_1, polygon_set_type_2>::type>::type,
    polygon_set_type_1>::type&
  interact(polygon_set_type_1& polygon_set_1, const polygon_set_type_2& polygon_set_2) {
    polygon_set_data<typename polygon_set_traits<polygon_set_type_1>::coordinate_type> ps1;
    assign(ps1, polygon_set_1);
    polygon_set_data<typename polygon_set_traits<polygon_set_type_2>::coordinate_type> ps2;
    assign(ps2, polygon_set_2);
    ps1.interact(ps2);
    assign(polygon_set_1, ps1);
    return polygon_set_1;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_up(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_up(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_down(polygon_set_type& polygon_set,
             typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_down(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  //transform
  template <typename polygon_set_type, typename transformation_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  transform(polygon_set_type& polygon_set,
            const transformation_type& transformation) {
    typedef typename polygon_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.transform(transformation);
    assign(polygon_set, ps);
    return polygon_set;
  }

  //keep
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  keep(polygon_set_type& polygon_set,
       typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::area_type min_area,
       typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::area_type max_area,
       typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_width,
       typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_width,
       typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_height,
       typename coordinate_traits<typename polygon_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_height) {
    typedef typename polygon_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef typename coordinate_traits<Unit>::unsigned_area_type uat;
    std::list<polygon_with_holes_data<Unit> > polys;
    assign(polys, polygon_set);
    typename std::list<polygon_with_holes_data<Unit> >::iterator itr_nxt;
    for(typename std::list<polygon_with_holes_data<Unit> >::iterator itr = polys.begin(); itr != polys.end(); itr = itr_nxt){
      itr_nxt = itr;
      ++itr_nxt;
      rectangle_data<Unit> bbox;
      extents(bbox, *itr);
      uat pwidth = delta(bbox, HORIZONTAL);
      if(pwidth > min_width && pwidth <= max_width){
        uat pheight = delta(bbox, VERTICAL);
        if(pheight > min_height && pheight <= max_height){
          typename coordinate_traits<Unit>::area_type parea = area(*itr);
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

  namespace operators {

  struct yes_ps_ob : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4 < yes_ps_ob, typename is_any_polygon_set_type<geometry_type_1>::type,
                                            typename is_any_polygon_set_type<geometry_type_2>::type,
                                            typename is_either_polygon_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_set_view<geometry_type_1, geometry_type_2, 0> >::type
  operator|(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_set_view<geometry_type_1, geometry_type_2, 0>
      (lvalue, rvalue);
  }

  struct yes_ps_op : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4 < yes_ps_op,
    typename gtl_if<typename is_any_polygon_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename is_any_polygon_set_type<geometry_type_2>::type>::type,
    typename gtl_if<typename is_either_polygon_set_type<geometry_type_1, geometry_type_2>::type>::type>
    ::type, polygon_set_view<geometry_type_1, geometry_type_2, 0> >::type
  operator+(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_set_view<geometry_type_1, geometry_type_2, 0>
      (lvalue, rvalue);
  }

  struct yes_ps_os : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4 < yes_ps_os,
    typename is_any_polygon_set_type<geometry_type_1>::type,
    typename is_any_polygon_set_type<geometry_type_2>::type,
    typename is_either_polygon_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_set_view<geometry_type_1, geometry_type_2, 1> >::type
  operator*(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_set_view<geometry_type_1, geometry_type_2, 1>
      (lvalue, rvalue);
  }

  struct yes_ps_oa : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4 < yes_ps_oa,
    typename is_any_polygon_set_type<geometry_type_1>::type,
    typename is_any_polygon_set_type<geometry_type_2>::type,
    typename is_either_polygon_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_set_view<geometry_type_1, geometry_type_2, 1> >::type
  operator&(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_set_view<geometry_type_1, geometry_type_2, 1>
      (lvalue, rvalue);
  }

  struct yes_ps_ox : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4 < yes_ps_ox,
    typename is_any_polygon_set_type<geometry_type_1>::type,
    typename is_any_polygon_set_type<geometry_type_2>::type,
    typename is_either_polygon_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_set_view<geometry_type_1, geometry_type_2, 2> >::type
  operator^(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_set_view<geometry_type_1, geometry_type_2, 2>
      (lvalue, rvalue);
  }

  struct yes_ps_om : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
    typename enable_if< typename gtl_and_4 < yes_ps_om,
    typename gtl_if<typename is_any_polygon_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename is_any_polygon_set_type<geometry_type_2>::type>::type,
    typename gtl_if<typename is_either_polygon_set_type<geometry_type_1, geometry_type_2>::type>::type>
    ::type, polygon_set_view<geometry_type_1, geometry_type_2, 3> >::type
  operator-(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_set_view<geometry_type_1, geometry_type_2, 3>
      (lvalue, rvalue);
  }

  struct yes_ps_ope : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< yes_ps_ope, gtl_yes, typename is_mutable_polygon_set_type<geometry_type_1>::type,
                                         typename is_any_polygon_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, 0>(lvalue, rvalue);
  }

  struct yes_ps_obe : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< yes_ps_obe, typename is_mutable_polygon_set_type<geometry_type_1>::type,
                                         typename is_any_polygon_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator|=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, 0>(lvalue, rvalue);
  }

  struct yes_ps_ose : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< yes_ps_ose, typename is_mutable_polygon_set_type<geometry_type_1>::type,
                                         typename is_any_polygon_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator*=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, 1>(lvalue, rvalue);
  }

  struct yes_ps_oae : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if<
    typename gtl_and_3< yes_ps_oae, typename is_mutable_polygon_set_type<geometry_type_1>::type,
                      typename is_any_polygon_set_type<geometry_type_2>::type>::type,
    geometry_type_1>::type &
  operator&=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, 1>(lvalue, rvalue);
  }

  struct yes_ps_oxe : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< yes_ps_oxe, typename is_mutable_polygon_set_type<geometry_type_1>::type,
                                         typename is_any_polygon_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator^=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, 2>(lvalue, rvalue);
  }

  struct yes_ps_ome : gtl_yes {};

  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if<
    typename gtl_and_3< yes_ps_ome, typename is_mutable_polygon_set_type<geometry_type_1>::type,
                      typename is_any_polygon_set_type<geometry_type_2>::type>::type,
    geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op<geometry_type_1, geometry_type_2, 3>(lvalue, rvalue);
  }

  // TODO: Dafna, test these four resizing operators
  struct y_ps_rpe : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3< y_ps_rpe, typename is_mutable_polygon_set_type<geometry_type_1>::type,
                                         typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                                coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, rvalue);
  }

  struct y_ps_rme : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps_rme, typename gtl_if<typename is_mutable_polygon_set_type<geometry_type_1>::type>::type,
                                         typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                                coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, -rvalue);
  }

  struct y_ps_rp : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps_rp, typename gtl_if<typename is_mutable_polygon_set_type<geometry_type_1>::type>::type,
                                        typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                               coordinate_concept>::type>
  ::type, geometry_type_1>::type
  operator+(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval += rvalue;
    return retval;
  }

  struct y_ps_rm : gtl_yes {};

  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps_rm, typename gtl_if<typename is_mutable_polygon_set_type<geometry_type_1>::type>::type,
                                        typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                               coordinate_concept>::type>
  ::type, geometry_type_1>::type
  operator-(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval -= rvalue;
    return retval;
  }


  } //end operators namespace

  template <typename T>
  struct view_of<polygon_45_set_concept, T> {
    typedef typename get_coordinate_type<T, typename geometry_concept<T>::type >::type coordinate_type;
    T* tp;
    std::vector<polygon_45_with_holes_data<coordinate_type> > polys;
    view_of(const T& obj) : tp(), polys() {
      std::vector<polygon_with_holes_data<coordinate_type> > gpolys;
      assign(gpolys, obj);
      for(typename std::vector<polygon_with_holes_data<coordinate_type> >::iterator itr = gpolys.begin();
          itr != gpolys.end(); ++itr) {
        polys.push_back(polygon_45_with_holes_data<coordinate_type>());
        assign(polys.back(), view_as<polygon_45_with_holes_concept>(*itr));
      }
    }
    view_of(T& obj) : tp(&obj), polys() {
      std::vector<polygon_with_holes_data<coordinate_type> > gpolys;
      assign(gpolys, obj);
      for(typename std::vector<polygon_with_holes_data<coordinate_type> >::iterator itr = gpolys.begin();
          itr != gpolys.end(); ++itr) {
        polys.push_back(polygon_45_with_holes_data<coordinate_type>());
        assign(polys.back(), view_as<polygon_45_with_holes_concept>(*itr));
      }
    }

    typedef typename std::vector<polygon_45_with_holes_data<coordinate_type> >::const_iterator iterator_type;
    typedef view_of operator_arg_type;

    inline iterator_type begin() const {
      return polys.begin();
    }

    inline iterator_type end() const {
      return polys.end();
    }

    inline orientation_2d orient() const { return HORIZONTAL; }

    inline bool clean() const { return false; }

    inline bool sorted() const { return false; }

    inline T& get() { return *tp; }
  };

  template <typename T>
  struct polygon_45_set_traits<view_of<polygon_45_set_concept, T> > {
    typedef typename view_of<polygon_45_set_concept, T>::coordinate_type coordinate_type;
    typedef typename view_of<polygon_45_set_concept, T>::iterator_type iterator_type;
    typedef view_of<polygon_45_set_concept, T> operator_arg_type;

    static inline iterator_type begin(const view_of<polygon_45_set_concept, T>& polygon_set) {
      return polygon_set.begin();
    }

    static inline iterator_type end(const view_of<polygon_45_set_concept, T>& polygon_set) {
      return polygon_set.end();
    }

    static inline orientation_2d orient(const view_of<polygon_45_set_concept, T>& polygon_set) {
      return polygon_set.orient(); }

    static inline bool clean(const view_of<polygon_45_set_concept, T>& polygon_set) {
      return polygon_set.clean(); }

    static inline bool sorted(const view_of<polygon_45_set_concept, T>& polygon_set) {
      return polygon_set.sorted(); }

  };

  template <typename T>
  struct geometry_concept<view_of<polygon_45_set_concept, T> > {
    typedef polygon_45_set_concept type;
  };

  template <typename T>
  struct get_coordinate_type<view_of<polygon_45_set_concept, T>, polygon_45_set_concept> {
    typedef typename view_of<polygon_45_set_concept, T>::coordinate_type type;
  };
  template <typename T>
  struct get_iterator_type_2<view_of<polygon_45_set_concept, T>, polygon_45_set_concept> {
    typedef typename view_of<polygon_45_set_concept, T>::iterator_type type;
    static type begin(const view_of<polygon_45_set_concept, T>& t) { return t.begin(); }
    static type end(const view_of<polygon_45_set_concept, T>& t) { return t.end(); }
  };
}
}
#endif

/* polygon_set_concept.hpp
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
*/
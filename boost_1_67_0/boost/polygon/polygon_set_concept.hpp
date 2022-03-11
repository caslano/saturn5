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
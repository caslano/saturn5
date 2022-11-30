/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_SET_CONCEPT_HPP
#define BOOST_POLYGON_POLYGON_45_SET_CONCEPT_HPP
#include "polygon_45_set_data.hpp"
#include "polygon_45_set_traits.hpp"
#include "detail/polygon_45_touch.hpp"
namespace boost { namespace polygon{

  template <typename T, typename T2>
  struct is_either_polygon_45_set_type {
    typedef typename gtl_or<typename is_polygon_45_set_type<T>::type, typename is_polygon_45_set_type<T2>::type >::type type;
  };

  template <typename T>
  struct is_polygon_45_or_90_set_type {
    typedef typename gtl_or<typename is_polygon_45_set_type<T>::type, typename is_polygon_90_set_type<T>::type >::type type;
  };

  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type>::type>::type,
                       typename polygon_45_set_traits<polygon_set_type>::iterator_type>::type
  begin_45_set_data(const polygon_set_type& polygon_set) {
    return polygon_45_set_traits<polygon_set_type>::begin(polygon_set);
  }

  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type>::type>::type,
                       typename polygon_45_set_traits<polygon_set_type>::iterator_type>::type
  end_45_set_data(const polygon_set_type& polygon_set) {
    return polygon_45_set_traits<polygon_set_type>::end(polygon_set);
  }

  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_set_type<polygon_set_type>::type>::type,
                       bool>::type
  clean(const polygon_set_type& polygon_set) {
    return polygon_45_set_traits<polygon_set_type>::clean(polygon_set);
  }

  //assign
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type_1>::type>::type,
                                         typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_2>::type>::type>::type,
                       polygon_set_type_1>::type &
  assign(polygon_set_type_1& lvalue, const polygon_set_type_2& rvalue) {
    polygon_45_set_mutable_traits<polygon_set_type_1>::set(lvalue, begin_45_set_data(rvalue), end_45_set_data(rvalue));
    return lvalue;
  }

  //get trapezoids
  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_set_type<polygon_set_type>::type>::type,
                       void>::type
  get_trapezoids(output_container_type& output, const polygon_set_type& polygon_set) {
    clean(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.get_trapezoids(output);
  }

  //get trapezoids
  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_set_type<polygon_set_type>::type>::type,
                       void>::type
  get_trapezoids(output_container_type& output, const polygon_set_type& polygon_set, orientation_2d slicing_orientation) {
    clean(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.get_trapezoids(output, slicing_orientation);
  }

  //equivalence
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and_3<typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_1>::type>::type,
                                          typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_2>::type>::type,
                                          typename gtl_if<typename is_either_polygon_45_set_type<polygon_set_type_1,
                                                                                                 polygon_set_type_2>::type>::type>::type,
                       bool>::type
  equivalence(const polygon_set_type_1& lvalue,
              const polygon_set_type_2& rvalue) {
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type_1>::coordinate_type> ps1;
    assign(ps1, lvalue);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type_2>::coordinate_type> ps2;
    assign(ps2, rvalue);
    return ps1 == ps2;
  }

  //clear
  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type>::type>::type,
                       void>::type
  clear(polygon_set_type& polygon_set) {
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(polygon_set, ps);
  }

  //empty
  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type>::type>::type,
                       bool>::type
  empty(const polygon_set_type& polygon_set) {
    if(clean(polygon_set)) return begin_45_set_data(polygon_set) == end_45_set_data(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.clean();
    return ps.empty();
  }

  //extents
  template <typename polygon_set_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type>::type>::type,
                      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  extents(rectangle_type& extents_rectangle,
          const polygon_set_type& polygon_set) {
    clean(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    return ps.extents(extents_rectangle);
  }

  //area
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::area_type>::type
  area(const polygon_set_type& polygon_set) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef polygon_45_with_holes_data<Unit> p_type;
    typedef typename coordinate_traits<Unit>::area_type area_type;
    std::vector<p_type> polys;
    assign(polys, polygon_set);
    area_type retval = (area_type)0;
    for(std::size_t i = 0; i < polys.size(); ++i) {
      retval += area(polys[i]);
    }
    return retval;
  }

  //interact
  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if <
    typename gtl_and< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type_1>::type>::type,
                      typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_2>::type>::type >::type,
    polygon_set_type_1>::type&
  interact(polygon_set_type_1& polygon_set_1, const polygon_set_type_2& polygon_set_2) {
    typedef typename polygon_45_set_traits<polygon_set_type_1>::coordinate_type Unit;
    std::vector<polygon_45_data<Unit> > polys;
    assign(polys, polygon_set_1);
    std::vector<std::set<int> > graph(polys.size()+1, std::set<int>());
    connectivity_extraction_45<Unit> ce;
    ce.insert(polygon_set_2);
    for(std::size_t i = 0; i < polys.size(); ++i){
      ce.insert(polys[i]);
    }
    ce.extract(graph);
    clear(polygon_set_1);
    polygon_45_set_data<Unit> ps;
    for(std::set<int>::iterator itr = graph[0].begin(); itr != graph[0].end(); ++itr){
      ps.insert(polys[(*itr)-1]);
    }
    assign(polygon_set_1, ps);
    return polygon_set_1;
  }

//   //self_intersect
//   template <typename polygon_set_type>
//   typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type>::type,
//                        polygon_set_type>::type &
//   self_intersect(polygon_set_type& polygon_set) {
//     typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
//     //TODO
//   }

  template <typename polygon_set_type, typename coord_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  resize(polygon_set_type& polygon_set, coord_type resizing,
         RoundingOption rounding = CLOSEST, CornerOption corner = INTERSECTION) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.resize(resizing, rounding, corner);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    return resize(polygon_set, static_cast<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>(bloating));
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type shrinking) {
    return resize(polygon_set, -(typename polygon_45_set_traits<polygon_set_type>::coordinate_type)shrinking);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  grow_and(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    std::vector<polygon_45_data<Unit> > polys;
    assign(polys, polygon_set);
    clear(polygon_set);
    polygon_45_set_data<Unit> ps;
    for(std::size_t i = 0; i < polys.size(); ++i) {
      polygon_45_set_data<Unit> tmpPs;
      tmpPs.insert(polys[i]);
      bloat(tmpPs, bloating);
      tmpPs.clean(); //apply implicit OR on tmp polygon set
      ps.insert(tmpPs);
    }
    ps.self_intersect();
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_up(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_up(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_down(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_down(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale(polygon_set_type& polygon_set, double factor) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  //self_intersect
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  self_intersect(polygon_set_type& polygon_set) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.self_intersect();
    assign(polygon_set, ps);
    return polygon_set;
  }

  //self_xor
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  self_xor(polygon_set_type& polygon_set) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.self_xor();
    assign(polygon_set, ps);
    return polygon_set;
  }

  //transform
  template <typename polygon_set_type, typename transformation_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  transform(polygon_set_type& polygon_set,
            const transformation_type& transformation) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.transform(transformation);
    assign(polygon_set, ps);
    return polygon_set;
  }

  //keep
  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  keep(polygon_set_type& polygon_set,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::area_type min_area,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::area_type max_area,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_width,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_width,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_height,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_height) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef typename coordinate_traits<Unit>::unsigned_area_type uat;
    std::list<polygon_45_data<Unit> > polys;
    assign(polys, polygon_set);
    typename std::list<polygon_45_data<Unit> >::iterator itr_nxt;
    for(typename std::list<polygon_45_data<Unit> >::iterator itr = polys.begin(); itr != polys.end(); itr = itr_nxt){
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

  template <typename T>
  struct view_of<polygon_90_set_concept, T> {
    typedef typename get_coordinate_type<T, typename geometry_concept<T>::type >::type coordinate_type;
    T* tp;
    std::vector<polygon_90_with_holes_data<coordinate_type> > polys;
    view_of(T& obj) : tp(&obj), polys() {
      std::vector<polygon_with_holes_data<coordinate_type> > gpolys;
      assign(gpolys, obj);
      for(typename std::vector<polygon_with_holes_data<coordinate_type> >::iterator itr = gpolys.begin();
          itr != gpolys.end(); ++itr) {
        polys.push_back(polygon_90_with_holes_data<coordinate_type>());
        assign(polys.back(), view_as<polygon_90_with_holes_concept>(*itr));
      }
    }
    view_of(const T& obj) : tp(), polys() {
      std::vector<polygon_with_holes_data<coordinate_type> > gpolys;
      assign(gpolys, obj);
      for(typename std::vector<polygon_with_holes_data<coordinate_type> >::iterator itr = gpolys.begin();
          itr != gpolys.end(); ++itr) {
        polys.push_back(polygon_90_with_holes_data<coordinate_type>());
        assign(polys.back(), view_as<polygon_90_with_holes_concept>(*itr));
      }
    }

    typedef typename std::vector<polygon_90_with_holes_data<coordinate_type> >::const_iterator iterator_type;
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
  struct polygon_90_set_traits<view_of<polygon_90_set_concept, T> > {
    typedef typename view_of<polygon_90_set_concept, T>::coordinate_type coordinate_type;
    typedef typename view_of<polygon_90_set_concept, T>::iterator_type iterator_type;
    typedef view_of<polygon_90_set_concept, T> operator_arg_type;

    static inline iterator_type begin(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.begin();
    }

    static inline iterator_type end(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.end();
    }

    static inline orientation_2d orient(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.orient(); }

    static inline bool clean(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.clean(); }

    static inline bool sorted(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.sorted(); }

  };

  template <typename T>
  struct geometry_concept<view_of<polygon_90_set_concept, T> > {
    typedef polygon_90_set_concept type;
  };

  template <typename T>
  struct get_coordinate_type<view_of<polygon_90_set_concept, T>, polygon_90_set_concept> {
    typedef typename view_of<polygon_90_set_concept, T>::coordinate_type type;
  };
  template <typename T>
  struct get_iterator_type_2<view_of<polygon_90_set_concept, T>, polygon_90_set_concept> {
    typedef typename view_of<polygon_90_set_concept, T>::iterator_type type;
    static type begin(const view_of<polygon_90_set_concept, T>& t) { return t.begin(); }
    static type end(const view_of<polygon_90_set_concept, T>& t) { return t.end(); }
  };

}
}
#include "detail/polygon_45_set_view.hpp"
#endif

/* polygon_45_set_concept.hpp
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
*/
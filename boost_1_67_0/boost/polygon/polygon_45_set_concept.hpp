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
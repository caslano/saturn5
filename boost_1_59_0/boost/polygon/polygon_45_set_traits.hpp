/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_SET_TRAITS_HPP
#define BOOST_POLYGON_POLYGON_45_SET_TRAITS_HPP
namespace boost { namespace polygon{

  //default definition of polygon 45 set traits works for any model of polygon 45, polygon 45 with holes or any vector or list thereof
  template <typename T>
  struct polygon_45_set_traits {
    typedef typename get_coordinate_type<T, typename geometry_concept<T>::type >::type coordinate_type;
    typedef typename get_iterator_type<T>::type iterator_type;
    typedef T operator_arg_type;

    static inline iterator_type begin(const T& polygon_set) {
      return get_iterator_type<T>::begin(polygon_set);
    }

    static inline iterator_type end(const T& polygon_set) {
      return get_iterator_type<T>::end(polygon_set);
    }

    static inline bool clean(const T& ) { return false; }

    static inline bool sorted(const T& ) { return false; }
  };

  template <typename T>
  struct is_45_polygonal_concept { typedef gtl_no type; };
  template <>
  struct is_45_polygonal_concept<polygon_45_concept> { typedef gtl_yes type; };
  template <>
  struct is_45_polygonal_concept<polygon_45_with_holes_concept> { typedef gtl_yes type; };
  template <>
  struct is_45_polygonal_concept<polygon_45_set_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_polygon_45_set_type {
    typedef typename is_45_polygonal_concept<typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_polygon_45_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename is_45_polygonal_concept<typename geometry_concept<std::list<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_polygon_45_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename is_45_polygonal_concept<typename geometry_concept<std::vector<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_45_set_type {
    typedef typename gtl_same_type<polygon_45_set_concept, typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_45_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_45_set_concept, typename geometry_concept<std::list<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_45_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_45_set_concept, typename geometry_concept<std::vector<T> >::type>::type,
      typename is_45_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  bool fracture_holes_45_by_concept() { return false; }
  template <>
  inline bool fracture_holes_45_by_concept<polygon_45_concept>() { return true; }

  template <typename T, typename iT>
  void get_45_polygons_T(T& t, iT begin, iT end) {
    typedef typename polygon_45_set_traits<T>::coordinate_type Unit;
    typedef typename geometry_concept<typename T::value_type>::type CType;
    typename polygon_45_formation<Unit>::Polygon45Formation pf(fracture_holes_45_by_concept<CType>());
    //std::cout << "FORMING POLYGONS\n";
    pf.scan(t, begin, end);
  }

  template <typename T>
  struct polygon_45_set_mutable_traits {};
  template <typename T>
  struct polygon_45_set_mutable_traits<std::list<T> > {
    template <typename input_iterator_type>
    static inline void set(std::list<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      polygon_45_set_data<typename polygon_45_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(std::distance(input_begin, input_end));
      ps.insert(input_begin, input_end);
      ps.sort();
      ps.clean();
      get_45_polygons_T(polygon_set, ps.begin(), ps.end());
    }
  };
  template <typename T>
  struct polygon_45_set_mutable_traits<std::vector<T> > {
    template <typename input_iterator_type>
    static inline void set(std::vector<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      size_t num_ele = std::distance(input_begin, input_end);
      polygon_set.reserve(num_ele);
      polygon_45_set_data<typename polygon_45_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(num_ele);
      ps.insert(input_begin, input_end);
      ps.sort();
      ps.clean();
      get_45_polygons_T(polygon_set, ps.begin(), ps.end());
    }
  };

  template <typename T>
  struct polygon_45_set_mutable_traits<polygon_45_set_data<T> > {
    template <typename input_iterator_type>
    static inline void set(polygon_45_set_data<T>& polygon_set,
                           input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.set(input_begin, input_end);
    }
  };
  template <typename T>
  struct polygon_45_set_traits<polygon_45_set_data<T> > {
    typedef typename polygon_45_set_data<T>::coordinate_type coordinate_type;
    typedef typename polygon_45_set_data<T>::iterator_type iterator_type;
    typedef typename polygon_45_set_data<T>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_45_set_data<T>& polygon_set) {
      return polygon_set.begin();
    }

    static inline iterator_type end(const polygon_45_set_data<T>& polygon_set) {
      return polygon_set.end();
    }

    static inline bool clean(const polygon_45_set_data<T>& polygon_set) { polygon_set.clean(); return true; }

    static inline bool sorted(const polygon_45_set_data<T>& polygon_set) { polygon_set.sort(); return true; }

  };
}
}
#endif

/* polygon_45_set_traits.hpp
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
*/
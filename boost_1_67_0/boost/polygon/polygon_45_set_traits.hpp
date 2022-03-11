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
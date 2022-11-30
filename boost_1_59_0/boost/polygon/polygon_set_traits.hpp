/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_SET_TRAITS_HPP
#define BOOST_POLYGON_POLYGON_SET_TRAITS_HPP
namespace boost { namespace polygon{

  struct polygon_set_concept {};

  //default definition of polygon set traits works for any model of polygon , polygon with holes or any vector or list thereof
  template <typename T>
  struct polygon_set_traits {
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
  struct is_polygonal_concept { typedef gtl_no type; };
  template <>
  struct is_polygonal_concept<polygon_concept> { typedef gtl_yes type; };
  template <>
  struct is_polygonal_concept<polygon_with_holes_concept> { typedef gtl_yes type; };
  template <>
  struct is_polygonal_concept<polygon_set_concept> { typedef gtl_yes type; };

  template <typename T>
  struct is_polygon_set_type {
    typedef typename is_polygonal_concept<typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_polygon_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename is_polygonal_concept<typename geometry_concept<std::list<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_polygon_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename is_polygonal_concept<typename geometry_concept<std::vector<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  struct is_mutable_polygon_set_type {
    typedef typename gtl_same_type<polygon_set_concept, typename geometry_concept<T>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_set_type<std::list<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_set_concept, typename geometry_concept<std::list<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::list<T>::value_type>::type>::type>::type type;
  };
  template <typename T>
  struct is_mutable_polygon_set_type<std::vector<T> > {
    typedef typename gtl_or<
      typename gtl_same_type<polygon_set_concept, typename geometry_concept<std::vector<T> >::type>::type,
      typename is_polygonal_concept<typename geometry_concept<typename std::vector<T>::value_type>::type>::type>::type type;
  };

  template <typename T>
  struct polygon_set_mutable_traits {};
  template <typename T>
  struct polygon_set_mutable_traits<std::list<T> > {
    template <typename input_iterator_type>
    static inline void set(std::list<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      polygon_set_data<typename polygon_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(std::distance(input_begin, input_end));
      ps.insert(input_begin, input_end);
      ps.get(polygon_set);
    }
  };
  template <typename T>
  struct polygon_set_mutable_traits<std::vector<T> > {
    template <typename input_iterator_type>
    static inline void set(std::vector<T>& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.clear();
      size_t num_ele = std::distance(input_begin, input_end);
      polygon_set.reserve(num_ele);
      polygon_set_data<typename polygon_set_traits<std::list<T> >::coordinate_type> ps;
      ps.reserve(num_ele);
      ps.insert(input_begin, input_end);
      ps.get(polygon_set);
    }
  };

  template <typename T>
  struct polygon_set_mutable_traits<polygon_set_data<T> > {
    template <typename input_iterator_type>
    static inline void set(polygon_set_data<T>& polygon_set,
                           input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.set(input_begin, input_end);
    }
  };
  template <typename T>
  struct polygon_set_traits<polygon_set_data<T> > {
    typedef typename polygon_set_data<T>::coordinate_type coordinate_type;
    typedef typename polygon_set_data<T>::iterator_type iterator_type;
    typedef typename polygon_set_data<T>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_set_data<T>& polygon_set) {
      return polygon_set.begin();
    }

    static inline iterator_type end(const polygon_set_data<T>& polygon_set) {
      return polygon_set.end();
    }

    static inline bool clean(const polygon_set_data<T>& polygon_set) { polygon_set.clean(); return true; }

    static inline bool sorted(const polygon_set_data<T>& polygon_set) { polygon_set.sort(); return true; }

  };
}
}
#endif

/* polygon_set_traits.hpp
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
*/
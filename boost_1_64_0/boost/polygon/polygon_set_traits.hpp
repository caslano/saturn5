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
1dzhOZ2pp5mpGwscnhid4GGwL7iFVcxxNeVrhM79bWOBjcdnNOaxUzHG+h58VHgMb9qjwmN40x8ZjuHNfGR6DG+G0e8BnDX6PYBTusfaDpa/ZT0yHLNbTcYAxtXKG9cr4/CMxvDKeN0A1tWAfcPT+JKUPtSPmTQ99rbcLMOxt5vmGI6t/Uwe/yyPzz5lONZWP1eLjPNuU5Z9gC2xG9udNS//9aB9McjAdBn3VbLf67DHLqyXl3SSWjFmNa8P4yPjeLnN1PXjPRPn4QeG52HZhur51xvZhkNyzjtA6a693ixQbENYnGambIEl5zvjbShOXLpjLUA6aZ0c+2spPbXn/4WKuLQT0oRGJsaEaIp9nBuPTdSNn3WWPk1iw5jvJZbxiHJKMzw/+1bOX+kxuT6n4w0qui5SxCWXNpXuYil9l2BT/Ou0Ms4binGPMpeLjCXW8E4kLkrXn7lG+95ZrttJNoW2ST92S7Zfvz/u8pqXLjXYH9dkMNm7WBdfx5XU9VtSsN3KAd3a7VxWzHOfduz2L+sLj+eeuvTPHc8tY6oNxm1nG41J/NJo/FuaPJ5iZoz2JaMx2qeUY7Q5l/lVpq+1eVI8J3VpwbnsnNG+Zd/on7+IvKT1PPGJFQVjFy+aGFct52IZqy3ncDPjrLOMxllr27pBXMl2+XkQL0tbcl1Qjl82iC2d5/fieX9fXfD8g4rnK5/b0j7/fV+dNQXbcd7MmOwMM2Oyj9FeU9azhX+bu/bxY7Lz+o/nh/LEF1Kkv2WsaV9ijEmYrIoIj897bhuel0zRbs876wrWvd94++U6036p4RjtC6sMx2irVxv++8o1hv/+3RrDMdxx6/TPN/zNpKoyR4mcw/9NOVKXY3NzwbEpEwVxxVUx9DSUH2qy/FqkHM8dP91wXilWLEd+wftbeQ9lcP7sVi2/gckSaxilt/Z6s8UgVuaSYZcan0B/w7VHf/00+XnF8Lp+Q2KMkhiJlfHT2uSGghiVA6hL+jtc5t7Pybhp4zHT8pnNcMx3b7mO58p8G7cl5lzKK5zLU/JjjgihNyNCYsP5dBul1r8BLP5cYsWJm/1tMm7tsZNbjX4lxlPac8fWgmMn1+h8+sBobol7RnNL3DaaW0I5ftj0OGFz44qt44et44eLN374FSft3z1vlVvU7amXKzYv2+y6x2n7kX/u+GEOILknxL0iE7+t01XyXT3REfugK/bFbtgP+6I3jkEfjMH+OBMH4GwchBtwMO7EIfg3HIpn0RfP4zC8gCPwJvrhTzgSqxLfKGyC/tgeA9ADR2N3HIPeGIi+OBaDcByqcTzGYhBOxwlIP/B8uSeEkNcPldBX+qGtjGdsh9WxPTZFd/REDxyOHXAydsRE7CTr32oj938gW9bvgKtk/bWkn+tgC6yL7bAedsf62B8boB82xPHoitPQDRdjY9yITXAvNsUT2AzfwOZ4Bp/Ac9hKP55T7g1hYxPjOTWy/VPRFeOlXjDFS+q9I/UqY4DUC5Z6IVgfQ7EnhqMKJ+F0nIxbMRIzMBrfwhh9fHK/BhuaiC9J2pkm7UyXejk8TyP1ykl+rDYF6TzKvarkuvgPbIRvYDN8C7vj++iN2TgOP8Dp+BEuwQu4A/+Fu/EiHsBLeBwvYyZewbcxB6/hVfwev8T7+DVqX9fXsBVeR3f8Fj3xOxyDN3ECfo+heAtj8C4uwp9wBf6Kz+EjPIE22nEtWAbPYFm8jOXwDlbE+1gJbekbO3RAe+yIVdETq+FwrI4B6IDjsQZOwFoYho4YjbUxHuvgbHTCBVgPF6EzrsSGuBEb4XZ0wVRsjgexBWZhS/wMn8AvsDV+hW3wZ2yHj7Arltfme2M77IEdsSf2RC8=
*/
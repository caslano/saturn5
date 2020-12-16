/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_WITH_HOLES_DATA_HPP
#define BOOST_POLYGON_POLYGON_90_WITH_HOLES_DATA_HPP
namespace boost { namespace polygon{
#include "isotropy.hpp"
#include "polygon_90_data.hpp"
struct polygon_90_with_holes_concept;
template <typename T>
class polygon_90_with_holes_data {
public:
  typedef polygon_90_with_holes_concept geometry_type;
  typedef T coordinate_type;
  typedef typename polygon_90_data<T>::iterator_type iterator_type;
  typedef typename polygon_90_data<T>::compact_iterator_type compact_iterator_type;
  typedef typename std::list<polygon_90_data<coordinate_type> >::const_iterator iterator_holes_type;
  typedef polygon_90_data<coordinate_type> hole_type;
  typedef typename coordinate_traits<T>::area_type area_type;
  typedef point_data<T> point_type;

  // default constructor of point does not initialize x and y
  inline polygon_90_with_holes_data() : self_(), holes_() {} //do nothing default constructor

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set_compact(iT input_begin, iT input_end) {
    self_.set_compact(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set_compact((*input_begin).begin_compact(), (*input_begin).end_compact());
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_90_with_holes_data(const polygon_90_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_90_with_holes_data& operator=(const polygon_90_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  template <typename T2>
  inline polygon_90_with_holes_data& operator=(const T2& rvalue);

  // get begin iterator, returns a pointer to a const coordinate_type
  inline const iterator_type begin() const {
    return self_.begin();
  }

  // get end iterator, returns a pointer to a const coordinate_type
  inline const iterator_type end() const {
    return self_.end();
  }

  // get begin iterator, returns a pointer to a const coordinate_type
  inline const compact_iterator_type begin_compact() const {
    return self_.begin_compact();
  }

  // get end iterator, returns a pointer to a const coordinate_type
  inline const compact_iterator_type end_compact() const {
    return self_.end_compact();
  }

  inline std::size_t size() const {
    return self_.size();
  }

  // get begin iterator, returns a pointer to a const polygon
  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  // get end iterator, returns a pointer to a const polygon
  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }

  inline std::size_t size_holes() const {
    return holes_.size();
  }

private:
  polygon_90_data<coordinate_type> self_;
  std::list<hole_type> holes_;
};
}
}
#endif

/* polygon_90_with_holes_data.hpp
i1ewLT7D9liO/bUDdsAu2B27Yi/shhPxXZyM/vgR9sSt+B6ex79gCvbBnzFAvsdyPpT7e3wnkt+LavHv1fJ9Y4/8brAfy+D32A5/QD88gr0wCQfgURyIx3AIHsdxeBL/jj/iPjyFh/EMHsez+BOewzN4Hi/jBXyBKZibOl3EgngFPfAqVsJruAZv4Hf4C57CW3gaf8VbeAdfYio6Kd93sQLew3p4H/3wEa7AXPbst2iPzzE32udiO8f8WAC7Y0EMRAcMw8L4ARbBTeiEe7AY7kcXTMYqeBXfwhdYFZVjdTUsjdWxLNbAclgfPfFt9M9knvXZQ3PaJQ7NmZ1vPTvfena+9Sw+o/ufmG/9EPvyLYpjHM/iUvwpIykLKTspVyj2w3LaeVJ8KTpKPGU9JYmSSnEdzriUXhQ9ZTZlJ+U6xW7E/8czvdmf7E/2J/uTmc+/5vl/oiL7hUa/juf/lef4z2ue4/fMkf55UMdSnBcPm59Bb969detWXYzP8Wfl/cR5S2mewZX5zZb5VZD5lZP52f2Qbn7yLP4/Nz9POWXVkvl5U5wYziv9/HhAyhC7neX5ad8JHYIW7zumaGOxV0p9mivDUxpLLPnYH8yx5LLgGBgiqz5rz8OgKWZc6mjxjuOWuSSmR+oQI3VIsVGHodFh+lBjJbKUw0HqYfGcki5MJzmgzTHuQ4PU9WWRD6COrK9apvY5Ymf5jl+pU0wWtkepk3Z9qDn7n0hbPJT5JaWbn3Zt/H6OV+X5llVJdhm9V1hyqWrzhhODLHW9ZR3rL8MFhof1j7RqP9n+pI3Tx/4ny/2s9hL73wadGc/xqPXyadd0ZmL/efb3WEbLly4fxlDtundEqatFDtrg2OhoZTg1Z20G7XNd3XZst1eqVXspsbfz+HtSbmOs4I+GZbd81kI/ICxGtkXNu5hfX6yt7RjQ7BhcYwzu64u1/U+Lqc0odjanq9I/csLG20cGlMnxaZ5rUyY4HIv498bU1rOT875cD/hTd3usKju+m8QslsJC6I4uWBqN48t5HCrYGN9Dxi+Hrlgey2EFbeytjM+qSRd7W1jGL4L50RHLYlF8A53QG4up05PzKja3Mb2FshyfSH0S0AsXY31cgo1xqUxPR0mR6Q2V6RXEEJnehzK96VgS46V+M7A2zsJ3cDa+i3MwAD/CQJyLkTgPY3C+mt9Qzn9yXlRjnW3EyhbDCbJeJuJbOAlr4GSshR/IdPdTkmS6T2S6JXCrVQz1G+iMb8nyVJN2qi7t5IVN0QfbYB3shHVl+d7GKGyAI7ARTsLGOB2b4CpsimuwGW7A5rgdW2EytsYz2BbvYzt8iO1RYq/kvEa/HOljrzrK8vjJ8nRDD3wXK2EPrIv+sjzvyfL0xo7YF0MwGPUYgmOxH87A/rgYB8pyDMJ9GI5HMRJ/wii8gzqp/2DMQX2jMRfqsRjGYikcgp4Yh5VwOFbDUdgKR2MbHIMO9hn93qv9TTj7HZvZv/lm/+b7v/Cbbxwvq59H2UpJoeQbRY5GSjfKyFHZv9dmf7I/2Z/sT/Yn+5P9yf5kf7I/2Z/sT/Yn+/M6Pn/6/X8ICA8cxjsiY3yUAIDXcP8/xcb9fzfMha7oouSJnG+4Pyjp5zs062kKAMjC/dbiTCc63PLe88Ic6fOtuzKc14J08zPmFmT5JQnYH5qvLCfPW8q7gGS+b1HcGM7PxnzDIsP0WYlzkPlJHIB6D9RiuWfL/OtTClFqU0oxXryN+cs7u72NSeUy/x5d7XK3k/l2k/vpYTLfUEpZhkuxMV9JDR0aYrzXrZM0S5nOYVda5l+C7rQMci+m0t+Q05YNyfrerzKgnVW7HZL6V5P6vyn11y1MV3+rWmc=
*/
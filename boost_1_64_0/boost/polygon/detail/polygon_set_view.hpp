/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_SET_VIEW_HPP
#define BOOST_POLYGON_POLYGON_SET_VIEW_HPP
namespace boost { namespace polygon{


  template <typename coordinate_type>
  inline void polygon_set_data<coordinate_type>::clean() const {
    if(dirty_) {
      //polygon_45_set_data<coordinate_type> tmp;
      //very important:
      //the 45 degree algorithm does not satisfy
      //the precondition of arbitrary polygon formation
      //that vertices be "linearly consistent"
      //therefore it doesn't work to fall back on 45-degree
      //booleans for arbitrary angle polygons
      //if(0) { //downcast(tmp) ) {
      //  tmp.clean();
      //  data_.clear();
      //  is_45_ = true;
      //  polygon_set_data<coordinate_type> tmp2;
      //  tmp2.insert(tmp);
      //  data_.swap(tmp2.data_);
      //  dirty_ = false;
      //  sort();
      //} else {
      sort();
      arbitrary_boolean_op<coordinate_type> abo;
      polygon_set_data<coordinate_type> tmp2;
      abo.execute(tmp2, begin(), end(), end(), end(), 0);
      data_.swap(tmp2.data_);
      is_45_ = tmp2.is_45_;
      dirty_ = false;
      //}
    }
  }

  template <>
  inline void polygon_set_data<double>::clean() const {
    if(dirty_) {
      sort();
      arbitrary_boolean_op<double> abo;
      polygon_set_data<double> tmp2;
      abo.execute(tmp2, begin(), end(), end(), end(), 0);
      data_.swap(tmp2.data_);
      is_45_ = tmp2.is_45_;
      dirty_ = false;
    }
  }

  template <typename value_type, typename arg_type>
  inline void insert_into_view_arg(value_type& dest, const arg_type& arg);

  template <typename ltype, typename rtype, int op_type>
  class polygon_set_view;

  template <typename ltype, typename rtype, int op_type>
  struct polygon_set_traits<polygon_set_view<ltype, rtype, op_type> > {
    typedef typename polygon_set_view<ltype, rtype, op_type>::coordinate_type coordinate_type;
    typedef typename polygon_set_view<ltype, rtype, op_type>::iterator_type iterator_type;
    typedef typename polygon_set_view<ltype, rtype, op_type>::operator_arg_type operator_arg_type;

    static inline iterator_type begin(const polygon_set_view<ltype, rtype, op_type>& polygon_set);
    static inline iterator_type end(const polygon_set_view<ltype, rtype, op_type>& polygon_set);

    static inline bool clean(const polygon_set_view<ltype, rtype, op_type>& polygon_set);

    static inline bool sort(const polygon_set_view<ltype, rtype, op_type>& polygon_set);
  };

  //template <typename value_type, typename geometry_type_1, typename geometry_type_2, int op_type>
  //void execute_boolean_op(value_type& output_, const geometry_type_1& lvalue_, const geometry_type_2& rvalue_,
  //                        double coord) {
  //  typedef geometry_type_1 ltype;
  //  typedef geometry_type_2 rtype;
  //  typedef typename polygon_set_traits<ltype>::coordinate_type coordinate_type;
  //  value_type linput_;
  //  value_type rinput_;
  //  insert_into_view_arg(linput_, lvalue_);
  //  insert_into_view_arg(rinput_, rvalue_);
  //  arbitrary_boolean_op<coordinate_type> abo;
  //  abo.execute(output_, linput_.begin(), linput_.end(),
  //              rinput_.begin(), rinput_.end(), op_type);
  //}

  template <typename value_type, typename geometry_type_1, typename geometry_type_2, int op_type>
  void execute_boolean_op(value_type& output_, const geometry_type_1& lvalue_, const geometry_type_2& rvalue_) {
    typedef geometry_type_1 ltype;
    //typedef geometry_type_2 rtype;
    typedef typename polygon_set_traits<ltype>::coordinate_type coordinate_type;
    value_type linput_;
    value_type rinput_;
    insert_into_view_arg(linput_, lvalue_);
    insert_into_view_arg(rinput_, rvalue_);
    polygon_45_set_data<coordinate_type> l45, r45, o45;
//    if(linput_.downcast(l45) && rinput_.downcast(r45)) {
//      //the op codes are screwed up between 45 and arbitrary
//#ifdef BOOST_POLYGON_MSVC
//#pragma warning (push)
//#pragma warning (disable: 4127)
//#endif
//      if(op_type < 2)
//        l45.template applyAdaptiveBoolean_<op_type>(o45, r45);
//      else if(op_type == 2)
//        l45.template applyAdaptiveBoolean_<3>(o45, r45);
//      else
//        l45.template applyAdaptiveBoolean_<2>(o45, r45);
//#ifdef BOOST_POLYGON_MSVC
//#pragma warning (pop)
//#endif
//      output_.insert(o45);
//    } else {
      arbitrary_boolean_op<coordinate_type> abo;
      abo.execute(output_, linput_.begin(), linput_.end(),
                  rinput_.begin(), rinput_.end(), op_type);
//    }
  }

  template <typename ltype, typename rtype, int op_type>
  class polygon_set_view {
  public:
    typedef typename polygon_set_traits<ltype>::coordinate_type coordinate_type;
    typedef polygon_set_data<coordinate_type> value_type;
    typedef typename value_type::iterator_type iterator_type;
    typedef polygon_set_view operator_arg_type;
  private:
    const ltype& lvalue_;
    const rtype& rvalue_;
    mutable value_type output_;
    mutable bool evaluated_;
    polygon_set_view& operator=(const polygon_set_view&);
  public:
    polygon_set_view(const ltype& lvalue,
                     const rtype& rvalue ) :
      lvalue_(lvalue), rvalue_(rvalue), output_(), evaluated_(false) {}

    // get iterator to begin vertex data
  public:
    const value_type& value() const {
      if(!evaluated_) {
        evaluated_ = true;
        execute_boolean_op<value_type, ltype, rtype, op_type>(output_, lvalue_, rvalue_);
      }
      return output_;
    }
  public:
    iterator_type begin() const { return value().begin(); }
    iterator_type end() const { return value().end(); }

    bool dirty() const { return false; } //result of a boolean is clean
    bool sorted() const { return true; } //result of a boolean is sorted

    void sort() const {} //is always sorted
  };

  template <typename ltype, typename rtype, int op_type>
  typename polygon_set_traits<polygon_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_set_traits<polygon_set_view<ltype, rtype, op_type> >::
  begin(const polygon_set_view<ltype, rtype, op_type>& polygon_set) {
    return polygon_set.begin();
  }
  template <typename ltype, typename rtype, int op_type>
  typename polygon_set_traits<polygon_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_set_traits<polygon_set_view<ltype, rtype, op_type> >::
  end(const polygon_set_view<ltype, rtype, op_type>& polygon_set) {
    return polygon_set.end();
  }
  template <typename ltype, typename rtype, int op_type>
  bool polygon_set_traits<polygon_set_view<ltype, rtype, op_type> >::
  clean(const polygon_set_view<ltype, rtype, op_type>& ) {
    return true; }
  template <typename ltype, typename rtype, int op_type>
  bool polygon_set_traits<polygon_set_view<ltype, rtype, op_type> >::
  sort(const polygon_set_view<ltype, rtype, op_type>& ) {
    return true; }

  template <typename value_type, typename arg_type>
  inline void insert_into_view_arg(value_type& dest, const arg_type& arg) {
    typedef typename polygon_set_traits<arg_type>::iterator_type literator;
    literator itr1, itr2;
    itr1 = polygon_set_traits<arg_type>::begin(arg);
    itr2 = polygon_set_traits<arg_type>::end(arg);
    dest.insert(itr1, itr2);
  }

  template <typename geometry_type_1, typename geometry_type_2, int op_type>
  geometry_type_1& self_assignment_boolean_op(geometry_type_1& lvalue_, const geometry_type_2& rvalue_) {
    typedef geometry_type_1 ltype;
    typedef typename polygon_set_traits<ltype>::coordinate_type coordinate_type;
    typedef polygon_set_data<coordinate_type> value_type;
    value_type output_;
    execute_boolean_op<value_type, geometry_type_1, geometry_type_2, op_type>(output_, lvalue_, rvalue_);
    polygon_set_mutable_traits<geometry_type_1>::set(lvalue_, output_.begin(), output_.end());
    return lvalue_;
  }

  // copy constructor
  template <typename coordinate_type>
  template <typename ltype, typename rtype, int op_type>
  polygon_set_data<coordinate_type>::polygon_set_data(const polygon_set_view<ltype, rtype, op_type>& that) :
    data_(that.value().data_), dirty_(that.value().dirty_), unsorted_(that.value().unsorted_), is_45_(that.value().is_45_) {}

    // equivalence operator
  template <typename coordinate_type>
  inline bool polygon_set_data<coordinate_type>::operator==(const polygon_set_data<coordinate_type>& p) const {
    typedef polygon_set_data<coordinate_type> value_type;
    value_type output_;
    execute_boolean_op<value_type, value_type, value_type, 2>(output_, (*this), p);  
    return output_.data_.empty();
  }

  template <typename ltype, typename rtype, int op_type>
  struct geometry_concept<polygon_set_view<ltype, rtype, op_type> > { typedef polygon_set_concept type; };
}
}
#endif

/* polygon_set_view.hpp
39tZzxxgXs5Iz32t+SPOT/OmP/j5cuoJW8a6AL8y/AhxhXEtfBv7wk8dftz05xT+eDnfV2DPx941f2+ZvYL113PoB/66bIpJx0Qx3g/w7y8QT1LxPxVq05LLUPxSqpHjYux/M+uSafQ/n/7Pov/O52nX9o/482NPsh7pRO7WOKz8h7GjWfRzqpH/IVtPkFss65rN1/Qx+vxX5Jlk7Kz/s7SbQ344cn7AYfIriP/xpj/uu5Ra+Yx/8kxTj4t2Jt5trvsPZj7wQ/5nkWMj68Hx5rrXr438XwlG77Ue9bbshPpfeM2Md/iHzPM81jvBpNRfjjx2zsF/34v8U4j/+PnyTr7fRbx/C7/wIPM7y7rPiiv4xRuRj/zTLVb9SYzzevzyFPqxnPXLQ8RbO57jZ2cz//1D8E/TTH4+8X0Fcj1r6z/fN7A+H5fJPJPucuEv7mdcRfT/VfSnHTkPUL7Vz+mso5zoUSLxnTi6Opf48AD1jDL1nGd96GI9FEv+4TPYzzbkPxf5M769J9H7Nq5n4Cd+jb8qxw/dY/I3Dac/3owX/Z2Mv9nLPCxHvmFZyPlWxvMk8bLSpIlPMW83ICf06gz9PxtOu+lmXg+Rv3g1/RqMPFYzjimyL6t97LYEuw14iX5+gD5oH2W1c4J4fQx92j4C//Ig45zK+vRl/Dj93LkUuYYSh5H7VvYridiDU6nVzgvn0Md5yDeffQXr6p0jsWvddWHcAUqt/CDWuSnc9yrtFrGeYZ84kPWCF/HG9Rzl5iGveNaftHcyl3mJZL3DvnLiVvSR/h1mnPn0Y9ZPuc48nh3KOob+nnzZlNv8KONBf2a/iL87S7xE71PQy+XY8cR046eGI9dT7fhH6vdKx07Qz/6lzOvTlJuBPyEupDznMOO8E7tMZL0i/fG2+ofcd1Xj15zE/0T8AfN1kvk7j35s/wg5TKGfyG3hfPSnDPtmf7ecuH3mfe2zrHKp2DnzvR959X8BP846azX74cXXs26exjkC8ekAen5qMfM8oI9pfwn2NVz5VorebmCew+4z9pRxmviPHMYhn6PYuX8KciCurGBc+29F/4h/exepXqv8x8wD83uY/dfSGexjy4gXdjy9kXbsfQ37VNetfL/T9DMf/Sh/AHliB8sS0YdP8e+pxIPAPkbP6PfOOfhJ1t/5yG8T8ttKfxYT30e+hL4Pxs/jrwYOxO++zf2sQ53Mc8DXibehnMdUUz/78HL0KYzxudzoAXEzvolzkNHIt5x6kPvSWcxPvz7mOuvh1WvRm2zsGn3ICCUdh10+ybiuNve9cC9+BTkeu8vIewP7PPdM4l8I11mvbyCO5tNfL/RmYDzrvvcpZ73TbvVnKvv4EuI550HLf48fptww9iXTyHfuRn6j2d/gX8qwi7OcEx37A/vXH+EXKtWW1X/W9atZfy3EDk4ip/Xo59oP8APE6cOsw5amEX+ex+6OsT6OM+OJZd5dnMOctfdr7Nd9iQOx01nH3W1Sf8l3tCX3j7zNfjeEdf+D2PU9+OkfICfmb5M3fvCrjONB/BzjOMw55bFrTbmApeqD1V9d97bGhx0d4HxhyCf4Z85f3H7EddYTbuxxYjjjymXfHom+cX505k5Tbxl+YNqVpp69rDPPUy5jAeuDJPSL9Z9rBnoRxP6MOJbiol17nfgsfhZ7XM8+JT7RxL/JRzl3y6K9D+hfmvps6WM7cW0w+oSfWFaDXTyLv2QdccZe72Uy74+hf8T1WR9yPtxI3Jiu8lb/HzPXJ6Iv5Z+acmPs84wBSq38B9HjaupH7sOQ86lbmZ9pRm/C1H9fK3VSb7XRn5JiL6XqL+3GYk/L3qNcKOspzr32lqFnEawHExgn+u8=
*/
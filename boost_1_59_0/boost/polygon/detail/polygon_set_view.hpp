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
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
*/
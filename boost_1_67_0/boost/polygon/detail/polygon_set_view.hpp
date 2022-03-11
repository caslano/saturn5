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
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_TREE_VALUE_COMPARE_HPP
#define BOOST_INTRUSIVE_DETAIL_TREE_VALUE_COMPARE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/pointer_traits.hpp>

namespace boost{
namespace intrusive{

//Needed to support smart references to value types
template <class From, class ValuePtr>
struct disable_if_smartref_to
   : detail::disable_if_c 
      <  detail::is_same
            <From, typename pointer_traits
               <ValuePtr>
                  ::reference>::value
      || detail::is_same
            <From, typename pointer_traits
                     < typename pointer_rebind
                           < ValuePtr
                           , const typename boost::movelib::pointer_element<ValuePtr>::type>::type>
                  ::reference>::value
      >
{};

//This function object takes a KeyCompare function object
//and compares values that contains keys using KeyOfValue
template< class ValuePtr, class KeyCompare, class KeyOfValue, class Ret = bool
        , bool = boost::intrusive::detail::is_same
   <typename boost::movelib::pointer_element<ValuePtr>::type, typename KeyOfValue::type>::value >
struct tree_value_compare
   :  public boost::intrusive::detail::ebo_functor_holder<KeyCompare>
{
   typedef typename
      boost::movelib::pointer_element<ValuePtr>::type value_type;
   typedef KeyCompare                                 key_compare;
   typedef KeyOfValue                                 key_of_value;
   typedef typename KeyOfValue::type                  key_type;

   typedef boost::intrusive::detail::ebo_functor_holder<KeyCompare> base_t;

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare()
      :  base_t()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit tree_value_compare(const key_compare &kcomp)
      :  base_t(kcomp)
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare (const tree_value_compare &x)
      :  base_t(x.base_t::get())
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const tree_value_compare &x)
   {  this->base_t::get() = x.base_t::get();   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const key_compare &x)
   {  this->base_t::get() = x;   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE const key_compare &key_comp() const
   {  return static_cast<const key_compare &>(*this);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key) const
   {  return this->key_comp()(key);   }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const value_type &value) const
   {  return this->key_comp()(KeyOfValue()(value));  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonkey
                                             , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key1, const key_type &key2) const
   {  return this->key_comp()(key1, key2);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const value_type &value1, const value_type &value2) const
   {  return this->key_comp()(KeyOfValue()(value1), KeyOfValue()(value2));  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key1, const value_type &value2) const
   {  return this->key_comp()(key1, KeyOfValue()(value2));  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const value_type &value1, const key_type &key2) const
   {  return this->key_comp()(KeyOfValue()(value1), key2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const key_type &key1, const U &nonkey2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(key1, nonkey2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonkey1, const key_type &key2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey1, key2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const value_type &value1, const U &nonvalue2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(KeyOfValue()(value1), nonvalue2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonvalue1, const value_type &value2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonvalue1, KeyOfValue()(value2));  }
};

template<class ValuePtr, class KeyCompare, class KeyOfValue, class Ret>
struct tree_value_compare<ValuePtr, KeyCompare, KeyOfValue, Ret, true>
   :  public boost::intrusive::detail::ebo_functor_holder<KeyCompare>
{
   typedef typename
      boost::movelib::pointer_element<ValuePtr>::type value_type;
   typedef KeyCompare                                 key_compare;
   typedef KeyOfValue                                 key_of_value;
   typedef typename KeyOfValue::type                  key_type;

   typedef boost::intrusive::detail::ebo_functor_holder<KeyCompare> base_t;


   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare()
      :  base_t()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit tree_value_compare(const key_compare &kcomp)
      :  base_t(kcomp)
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare (const tree_value_compare &x)
      :  base_t(x.base_t::get())
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const tree_value_compare &x)
   {  this->base_t::get() = x.base_t::get();   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const key_compare &x)
   {  this->base_t::get() = x;   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE const key_compare &key_comp() const
   {  return static_cast<const key_compare &>(*this);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key) const
   {  return this->key_comp()(key);   }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonkey
                                             , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key1, const key_type &key2) const
   {  return this->key_comp()(key1, key2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const key_type &key1, const U &nonkey2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(key1, nonkey2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const U &nonkey1, const key_type &key2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey1, key2);  }
};

}  //namespace intrusive{
}  //namespace boost{

#endif   //#ifdef BOOST_INTRUSIVE_DETAIL_TREE_VALUE_COMPARE_HPP

/* tree_value_compare.hpp
i2s7vgh5T0DeqwTPi5K8sC84PPS9EnF+e1Q1Zgv/WdtEnzTkSRL5tCCfdYLvT1FyWaUwH76YfegVgucVUVZaHxFbB0spTpb1mTh/SdRs1MYftOzgssQ1ux5tdUF3XJv1a/YiXLOT1dfsQeT1gXcwjBMb5dsUG9M5Ntp3IrZ7F5v+jWl2Ic0QPU03Xy06OGv/Rr5D4But8yVs3Cv3b3JeJwxZNzZC2JQUlazifQbvL95B+lsYJyi+jT7ObxcNb3VCu+8w9hhDe8BxtAeR3+SEcz4X+Wl3p/l/bwr6/Tvpt9z2D3OxYh7H5L8B+jF4mv5uafu8urm790N6m7av7EfJL/e5oriT8ZvE+ZFm+xjeqv+OV/UFyEvRb6j2gpN55TYv9d/vivOLkYb3A3658nAnbvbh7wmeXPDgvrSHfz/EuUmQJW6BtL+J1V9uha/UuIgrpfvLmFbTX8Rv6M8+v33+I47TxtyjTvYp4SPz6SO13KPuOlAP0LUg/fqQ32r1Eew+ugpL0YoLSypRYF5RyYoSb6VLn8lvDc1n8lvdXx/kvGF6fEzRzPV9twieyVof5Ig8RL+n9wVHYiFfHPuCC0VXoOy3jGO3ge+HoOB7HU1Rr++0dlw/AF4hM/TDMeoXtFfnrHhzzaqJP9Wf976w1qV4/MTeyetKCovdtvv4L0KrQys/y5OfEQVPmtn2LxO/uyjqmfnxGXEn6mxfb9bb2LbrTW+TP/K0/T5ar7d1X7Sv3jwB7Y+6Bu/Xyz3xjoB6gl5in1xtqSNUznJupuWyfqod6sfDe5jbBM+z2iX4v0sVk0+Rj2pvsG2CpwTreYaq6gp5uO+nDV7VvVkK8HZx/iB66s7aDpAnOFYg504Y++3fKfif0HJh+btAur/MRUHNCRxTGGl/f2LwpiTSt9Y53MvgWFf61gvI+3mQjts9OrYdO0D3tQv+0RG+ZtaPsr+X+4gWboj2gTgOm4C+DaPV/kPlfwWIopBXXLaipKw44Jm+rGB18cn6uUekfRtP6d20X6rjQjB/dR0nAXeJ829pk/D/F1xfPErIWox8eC0WPLXwus5m7IbbPbA/6E5Q5wSjfvDdhf0Dnqeok3z/tJn7qi2Mgp8S9Wtj45cWW6FDLq70Vrprp0hv107NZ43XBc+0qLgo5d57yEPdvrgWG3vh9MaxrWifqYr2yfTKZyo+24rzo6JOwNYBdSY9NxwVPGOiAp6VWFfXiPK3axcEPBvRTFI/8plfT6zf7G/YAx+sncYjiHGdSATeKfLrpQU8o0jXkdvE+T7ifKGot9VFcn+1W5y/BOfPFP3BMeTRmsz+IN2+jSeSN9XD55Xuvlre9518PiHPAg/7jMsc+gzy+jzm88+v9OefqGnq8R1Zhp0ePv/08O2Xn31kGQ55+OzTc2P32M69pXvUQL4ThqwbTxXCqmTluIX5/HN9Etqxx904z8ta73b1a7z3sfRfs43rZ0rQvtW8X/VF9Q5uk8WVlf6NZUswLLmyoKTM7X0O8grpPgf8ru9VyWvWy10u7kk6wn7meHY/tf3qrPZbU1FUrM/sc2WzuhBtVheCzer+wzbLP8Wf8aAoyEPUbdZktZm4EJcUV7qyGdI7jqF5gC3gwXGlDZHe8RpQ2AnnMX4+T3UNYHrlNYDXoKPifGzUEa2T1IebKpp9b3eUI49vLRS/e9heN6LF+c+V8T9yxLmfY4+yvurrAcusEHy9ldeDRGCpOJ+MPKQYIt7V5fhiXqM2CZ4rMfKQymNRtFmOlsrYRq2ow6ED2VdOs+/X+5M3d6DRr5eLbv1cdOvKMS3ybwA/x7Q2Kca0TL6dA41+3feisl8nX6Mhq6/ZdlyrP451kfr150E7xD0=
*/
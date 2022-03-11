/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SET_ALGO_HPP_JOFA_990225
#define BOOST_ICL_SET_ALGO_HPP_JOFA_990225

#include <boost/type_traits/remove_const.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/concept/container.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/concept/map_value.hpp>


namespace boost{namespace icl
{

namespace Set
{

template<class ObjectT, class ConstObjectT, class IteratorT>
bool common_range(IteratorT& lwb, IteratorT& upb, ObjectT& x1, const ConstObjectT& x2)
{
    // lwb and upb are iterators of x1 marking the lower and upper bound of
    // the common range of x1 and x2.
    typedef typename ConstObjectT::const_iterator ConstObject_iterator;
    // ObjectT may be const or non const. 
    typedef typename remove_const<ObjectT>::type  PureObjectT;

    lwb = x1.end();
    upb = x1.end();

    if(icl::is_empty(x1) || icl::is_empty(x2)) 
        return false;

    IteratorT x1_fst_ = x1.begin();
    IteratorT x1_lst_ = x1.end(); x1_lst_--;

    ConstObject_iterator x2_fst_ = x2.begin();
    ConstObject_iterator x2_lst_ = x2.end(); x2_lst_--;

    typename ObjectT::key_compare key_less;
    if(key_less(icl::key_value< PureObjectT>(x1_lst_), 
                icl::key_value<ConstObjectT>(x2_fst_))) // {x1}   {x2}
        return false;
    if(key_less(icl::key_value<ConstObjectT>(x2_lst_), 
                icl::key_value< PureObjectT>(x1_fst_))) // {x2}   {x1} 
        return false;

    // We do have a common range
    lwb = x1.lower_bound(icl::key_value<ConstObjectT>(x2_fst_));
    upb = x1.upper_bound(icl::key_value<ConstObjectT>(x2_lst_));

    return true;
}


/** Function template <tt>contained_in</tt> implements the subset relation. 
<tt>contained_in(sub, super)</tt> is true if <tt>sub</tt> is contained in <tt>super</tt> */
template<class SetType>
inline bool within(const SetType& sub, const SetType& super)
{
    if(&super == &sub)                   return true;
    if(icl::is_empty(sub))               return true;
    if(icl::is_empty(super))             return false;

    typename SetType::const_iterator common_lwb_, common_upb_;
    if(!common_range(common_lwb_, common_upb_, sub, super))
        return false;

    typename SetType::const_iterator sub_ = common_lwb_, super_;
    while(sub_ != common_upb_)
    {
        super_ = super.find(*sub_++);
        if(super_ == super.end()) 
            return false;
    }
    return true;
}

template<class SetType>
bool intersects(const SetType& left, const SetType& right)
{
    typename SetType::const_iterator common_lwb_right_, common_upb_right_;
    if(!common_range(common_lwb_right_, common_upb_right_, right, left))
        return false;

    typename SetType::const_iterator right_ = common_lwb_right_, found_;
    while(right_ != common_upb_right_)
    {
        found_ = left.find(*right_++);
        if(found_ != left.end()) 
            return true; // found a common element
    }
    // found no common element
    return false;    
}


#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4996) //'std::equal': Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
#endif                        // I do guarantee here that I am using the parameters correctly :)

/** Function template <tt>lexicographical_equal</tt> implements 
    lexicographical equality. */
template<class SetType>
inline bool lexicographical_equal(const SetType& left, const SetType& right)
{
    if(&left == &right)
        return true;
    else return left.iterative_size() == right.iterative_size()
             && std::equal(left.begin(), left.end(), right.begin()); 
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


} // namespace Set

}} // namespace icl boost

#endif


/* set_algo.hpp
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
*/
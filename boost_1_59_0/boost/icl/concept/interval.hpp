/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_HPP_JOFA_100323
#define BOOST_ICL_CONCEPT_INTERVAL_HPP_JOFA_100323

#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/type_traits/unit_element.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/infinity.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_asymmetric_interval.hpp>
#include <boost/icl/type_traits/is_discrete_interval.hpp>
#include <boost/icl/type_traits/is_continuous_interval.hpp>

#include <boost/icl/concept/interval_bounds.hpp>
#include <boost/icl/interval_traits.hpp>
#include <boost/icl/dynamic_interval_traits.hpp>

#include <algorithm>

namespace boost{namespace icl
{

//==============================================================================
//= Ordering
//==============================================================================
template<class Type>
inline typename enable_if<is_interval<Type>, bool>::type
domain_less(const typename interval_traits<Type>::domain_type& left,
            const typename interval_traits<Type>::domain_type& right)
{
    return typename interval_traits<Type>::domain_compare()(left, right);
}

template<class Type>
inline typename enable_if<is_interval<Type>, bool>::type
domain_less_equal(const typename interval_traits<Type>::domain_type& left,
                  const typename interval_traits<Type>::domain_type& right)
{
    return !(typename interval_traits<Type>::domain_compare()(right, left));
}

template<class Type>
inline typename enable_if<is_interval<Type>, bool>::type
domain_equal(const typename interval_traits<Type>::domain_type& left,
             const typename interval_traits<Type>::domain_type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    return !(domain_compare()(left, right)) && !(domain_compare()(right, left));
}

template<class Type>
inline typename enable_if< is_interval<Type>
                         , typename interval_traits<Type>::domain_type>::type
domain_next(const typename interval_traits<Type>::domain_type value)
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    return icl::successor<domain_type,domain_compare>::apply(value);
}

template<class Type>
inline typename enable_if< is_interval<Type>
                         , typename interval_traits<Type>::domain_type>::type
domain_prior(const typename interval_traits<Type>::domain_type value)
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    return icl::predecessor<domain_type,domain_compare>::apply(value);
}

//==============================================================================
//= Construct<Interval> singleton
//==============================================================================
template<class Type>
typename enable_if
<
    mpl::and_< is_static_right_open<Type>
             , is_discrete<typename interval_traits<Type>::domain_type> >
  , Type
>::type
singleton(const typename interval_traits<Type>::domain_type& value)
{
    //ASSERT: This always creates an interval with exactly one element
    return interval_traits<Type>::construct(value, domain_next<Type>(value));
}

template<class Type>
typename enable_if
<
    mpl::and_< is_static_left_open<Type>
             , is_discrete<typename interval_traits<Type>::domain_type> >
  , Type
>::type
singleton(const typename interval_traits<Type>::domain_type& value)
{
    //ASSERT: This always creates an interval with exactly one element
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                 ::is_less_than(value) ));

    return interval_traits<Type>::construct(domain_prior<Type>(value), value);
}

template<class Type>
typename enable_if<is_discrete_static_open<Type>, Type>::type
singleton(const typename interval_traits<Type>::domain_type& value)
{
    //ASSERT: This always creates an interval with exactly one element
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                 ::is_less_than(value)));

    return interval_traits<Type>::construct( domain_prior<Type>(value)
                                           , domain_next<Type>(value));
}

template<class Type>
typename enable_if<is_discrete_static_closed<Type>, Type>::type
singleton(const typename interval_traits<Type>::domain_type& value)
{
    //ASSERT: This always creates an interval with exactly one element
    return interval_traits<Type>::construct(value, value);
}

template<class Type>
typename enable_if<has_dynamic_bounds<Type>, Type>::type
singleton(const typename interval_traits<Type>::domain_type& value)
{
    return dynamic_interval_traits<Type>::construct(value, value, interval_bounds::closed());
}

namespace detail
{

//==============================================================================
//= Construct<Interval> unit_trail == generalized singleton
// The smallest interval on an incrementable (and decrementable) type that can
// be constructed using ++ and -- and such that it contains a given value.
// If 'Type' is discrete, 'unit_trail' and 'singleton' are identical. So we
// can view 'unit_trail' as a generalized singleton for static intervals of
// continuous types.
//==============================================================================
template<class Type>
typename enable_if
<
    mpl::and_< is_static_right_open<Type>
             , boost::detail::is_incrementable<typename interval_traits<Type>::domain_type> >
  , Type
>::type
unit_trail(const typename interval_traits<Type>::domain_type& value)
{
    return interval_traits<Type>::construct(value, domain_next<Type>(value));
}

template<class Type>
typename enable_if
<
    mpl::and_< is_static_left_open<Type>
             , boost::detail::is_incrementable<typename interval_traits<Type>::domain_type> >
  , Type
>::type
unit_trail(const typename interval_traits<Type>::domain_type& value)
{
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                 ::is_less_than(value) ));

    return interval_traits<Type>::construct(domain_prior<Type>(value), value);
}

template<class Type>
typename enable_if
<
    mpl::and_< is_static_open<Type>
             , is_discrete<typename interval_traits<Type>::domain_type> >
  , Type
>::type
unit_trail(const typename interval_traits<Type>::domain_type& value)
{
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                 ::is_less_than(value)));

    return interval_traits<Type>::construct( domain_prior<Type>(value)
                                           ,  domain_next<Type>(value));
}

template<class Type>
typename enable_if
<
    mpl::and_< is_static_closed<Type>
             , is_discrete<typename interval_traits<Type>::domain_type> >
  , Type
>::type
unit_trail(const typename interval_traits<Type>::domain_type& value)
{
    return interval_traits<Type>::construct(value, value);
}

//NOTE: statically bounded closed or open intervals of continuous domain types
// are NOT supported by ICL. They can not be used with interval containers
// consistently.


template<class Type>
typename enable_if<has_dynamic_bounds<Type>, Type>::type
unit_trail(const typename interval_traits<Type>::domain_type& value)
{
    return dynamic_interval_traits<Type>::construct(value, value, interval_bounds::closed());
}

} //namespace detail

//==============================================================================
//= Construct<Interval> multon
//==============================================================================
template<class Type>
typename enable_if<has_static_bounds<Type>, Type>::type
construct(const typename interval_traits<Type>::domain_type& low,
          const typename interval_traits<Type>::domain_type& up  )
{
    return interval_traits<Type>::construct(low, up);
}

template<class Type>
typename enable_if<has_dynamic_bounds<Type>, Type>::type
construct(const typename interval_traits<Type>::domain_type& low,
          const typename interval_traits<Type>::domain_type& up,
          interval_bounds bounds = interval_bounds::right_open())
{
    return dynamic_interval_traits<Type>::construct(low, up, bounds);
}


//- construct form bounded values ----------------------------------------------
template<class Type>
typename enable_if<has_dynamic_bounds<Type>, Type>::type
construct(const typename Type::bounded_domain_type& low,
          const typename Type::bounded_domain_type& up)
{
    return dynamic_interval_traits<Type>::construct_bounded(low, up);
}

template<class Type>
typename enable_if<is_interval<Type>, Type>::type
span(const typename interval_traits<Type>::domain_type& left,
     const typename interval_traits<Type>::domain_type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    if(domain_compare()(left,right))
        return construct<Type>(left, right);
    else
        return construct<Type>(right, left);
}


//==============================================================================
template<class Type>
typename enable_if<is_static_right_open<Type>, Type>::type
hull(const typename interval_traits<Type>::domain_type& left,
     const typename interval_traits<Type>::domain_type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    if(domain_compare()(left,right))
        return construct<Type>(left, domain_next<Type>(right));
    else
        return construct<Type>(right, domain_next<Type>(left));
}

template<class Type>
typename enable_if<is_static_left_open<Type>, Type>::type
hull(const typename interval_traits<Type>::domain_type& left,
     const typename interval_traits<Type>::domain_type& right)
{
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    if(domain_compare()(left,right))
    {
        BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                     ::is_less_than(left) ));
        return construct<Type>(domain_prior<Type>(left), right);
    }
    else
    {
        BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                     ::is_less_than(right) ));
        return construct<Type>(domain_prior<Type>(right), left);
    }
}

template<class Type>
typename enable_if<is_static_closed<Type>, Type>::type
hull(const typename interval_traits<Type>::domain_type& left,
     const typename interval_traits<Type>::domain_type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    if(domain_compare()(left,right))
        return construct<Type>(left, right);
    else
        return construct<Type>(right, left);
}

template<class Type>
typename enable_if<is_static_open<Type>, Type>::type
hull(const typename interval_traits<Type>::domain_type& left,
     const typename interval_traits<Type>::domain_type& right)
{
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    if(domain_compare()(left,right))
    {
        BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                     ::is_less_than(left) ));
        return construct<Type>( domain_prior<Type>(left)
                              ,  domain_next<Type>(right));
    }
    else
    {
        BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                     ::is_less_than(right) ));
        return construct<Type>( domain_prior<Type>(right)
                              ,  domain_next<Type>(left));
    }
}

template<class Type>
typename enable_if<has_dynamic_bounds<Type>, Type>::type
hull(const typename interval_traits<Type>::domain_type& left,
     const typename interval_traits<Type>::domain_type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    if(domain_compare()(left,right))
        return construct<Type>(left, right, interval_bounds::closed());
    else
        return construct<Type>(right, left, interval_bounds::closed());
}

//==============================================================================
//= Selection
//==============================================================================

template<class Type>
inline typename enable_if<is_interval<Type>,
                          typename interval_traits<Type>::domain_type>::type
lower(const Type& object)
{
    return interval_traits<Type>::lower(object);
}

template<class Type>
inline typename enable_if<is_interval<Type>,
                          typename interval_traits<Type>::domain_type>::type
upper(const Type& object)
{
    return interval_traits<Type>::upper(object);
}


//- first ----------------------------------------------------------------------
template<class Type>
inline typename
enable_if< mpl::or_<is_static_right_open<Type>, is_static_closed<Type> >
         , typename interval_traits<Type>::domain_type>::type
first(const Type& object)
{
    return lower(object);
}

template<class Type>
inline typename
enable_if< mpl::and_< mpl::or_<is_static_left_open<Type>, is_static_open<Type> >
                    , is_discrete<typename interval_traits<Type>::domain_type> >
         , typename interval_traits<Type>::domain_type>::type
first(const Type& object)
{
    return domain_next<Type>(lower(object));
}

template<class Type>
inline typename enable_if<is_discrete_interval<Type>,
                          typename interval_traits<Type>::domain_type>::type
first(const Type& object)
{
    return is_left_closed(object.bounds()) ?
                                 lower(object) :
               domain_next<Type>(lower(object));
}

//- last -----------------------------------------------------------------------
template<class Type>
inline typename
enable_if< mpl::or_<is_static_left_open<Type>, is_static_closed<Type> >
         , typename interval_traits<Type>::domain_type>::type
last(const Type& object)
{
    return upper(object);
}

template<class Type>
inline typename
enable_if< mpl::and_< mpl::or_<is_static_right_open<Type>, is_static_open<Type> >
                    , is_discrete<typename interval_traits<Type>::domain_type>  >
         , typename interval_traits<Type>::domain_type>::type
last(const Type& object)
{
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                 ::is_less_than(upper(object)) ));
    return domain_prior<Type>(upper(object));
}

template<class Type>
inline typename enable_if<is_discrete_interval<Type>,
                          typename interval_traits<Type>::domain_type>::type
last(const Type& object)
{
    typedef typename interval_traits<Type>::domain_type    domain_type;
    typedef typename interval_traits<Type>::domain_compare domain_compare;
    BOOST_ASSERT((numeric_minimum<domain_type, domain_compare, is_numeric<domain_type>::value>
                                 ::is_less_than_or(upper(object), is_right_closed(object.bounds())) ));
    return is_right_closed(object.bounds()) ?
                                  upper(object) :
               domain_prior<Type>(upper(object));
}

//- last_next ------------------------------------------------------------------
template<class Type>
inline typename
enable_if< mpl::and_< mpl::or_<is_static_left_open<Type>, is_static_closed<Type> >
                    , is_discrete<typename interval_traits<Type>::domain_type>  >
         , typename interval_traits<Type>::domain_type>::type
last_next(const Type& object)
{
    return domain_next<Type>(upper(object));
}

template<class Type>
inline typename
enable_if< mpl::and_< mpl::or_<is_static_right_open<Type>, is_static_open<Type> >
                    , is_discrete<typename interval_traits<Type>::domain_type>  >
         , typename interval_traits<Type>::domain_type>::type
last_next(const Type& object)
{
    //CL typedef typename interval_traits<Type>::domain_type domain_type;
    return upper(object); // NOTE: last_next is implemented to avoid calling pred(object)
}                         // For unsigned integral types this may cause underflow.

template<class Type>
inline typename enable_if<is_discrete_interval<Type>,
                          typename interval_traits<Type>::domain_type>::type
last_next(const Type& object)
{
    return is_right_closed(object.bounds()) ?
               domain_next<Type>(upper(object)):
                                 upper(object) ;
}

//------------------------------------------------------------------------------
template<class Type>
typename enable_if<has_dynamic_bounds<Type>,
                   typename Type::bounded_domain_type>::type
bounded_lower(const Type& object)
{
    return typename
        Type::bounded_domain_type(lower(object), object.bounds().left());
}

template<class Type>
typename enable_if<has_dynamic_bounds<Type>,
                   typename Type::bounded_domain_type>::type
reverse_bounded_lower(const Type& object)
{
    return typename
        Type::bounded_domain_type(lower(object),
                                  object.bounds().reverse_left());
}

template<class Type>
typename enable_if<has_dynamic_bounds<Type>,
                   typename Type::bounded_domain_type>::type
bounded_upper(const Type& object)
{
    return typename
        Type::bounded_domain_type(upper(object),
                                  object.bounds().right());
}

template<class Type>
typename enable_if<has_dynamic_bounds<Type>,
                   typename Type::bounded_domain_type>::type
reverse_bounded_upper(const Type& object)
{
    return typename
        Type::bounded_domain_type(upper(object),
                                  object.bounds().reverse_right());
}

//- bounds ---------------------------------------------------------------------
template<class Type>
inline typename enable_if<has_dynamic_bounds<Type>, interval_bounds>::type
bounds(const Type& object)
{
    return object.bounds();
}

template<class Type>
inline typename enable_if<has_static_bounds<Type>, interval_bounds>::type
bounds(const Type&)
{
    return interval_bounds(interval_bound_type<Type>::value);
}


//==============================================================================
//= Emptieness
//==============================================================================
/** Is the interval empty? */
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
is_empty(const Type& object)
{
    return domain_less_equal<Type>(upper(object), lower(object));
}

template<class Type>
typename boost::enable_if<is_static_closed<Type>, bool>::type
is_empty(const Type& object)
{
    return domain_less<Type>(upper(object), lower(object));
}

template<class Type>
typename boost::enable_if<is_static_open<Type>, bool>::type
is_empty(const Type& object)
{
    return domain_less_equal<Type>(upper(object),                   lower(object) )
        || domain_less_equal<Type>(upper(object), domain_next<Type>(lower(object)));
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
is_empty(const Type& object)
{
    if(object.bounds() == interval_bounds::closed())
        return domain_less<Type>(upper(object), lower(object));
    else if(object.bounds() == interval_bounds::open())
        return domain_less_equal<Type>(upper(object),                   lower(object) )
            || domain_less_equal<Type>(upper(object), domain_next<Type>(lower(object)));
    else
        return domain_less_equal<Type>(upper(object), lower(object));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
is_empty(const Type& object)
{
    return     domain_less<Type>(upper(object), lower(object))
        || (   domain_equal<Type>(upper(object), lower(object))
            && object.bounds() != interval_bounds::closed()    );
}

//==============================================================================
//= Equivalences and Orderings
//==============================================================================
//- exclusive_less -------------------------------------------------------------
/** Maximal element of <tt>left</tt> is less than the minimal element of
    <tt>right</tt> */
template<class Type>
inline typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{
    return icl::is_empty(left) || icl::is_empty(right)
        || domain_less_equal<Type>(upper(left), lower(right));
}

template<class Type>
inline typename boost::enable_if<is_discrete_interval<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{
    return icl::is_empty(left) || icl::is_empty(right)
        || domain_less<Type>(last(left), first(right));
}

template<class Type>
inline typename boost::
enable_if<has_symmetric_bounds<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{
    return icl::is_empty(left) || icl::is_empty(right)
        || domain_less<Type>(last(left), first(right));
}

template<class Type>
inline typename boost::enable_if<is_continuous_interval<Type>, bool>::type
exclusive_less(const Type& left, const Type& right)
{
    return     icl::is_empty(left) || icl::is_empty(right)
        ||     domain_less<Type>(upper(left), lower(right))
        || (   domain_equal<Type>(upper(left), lower(right))
            && inner_bounds(left,right) != interval_bounds::open() );
}


//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_static_bounds<Type>, bool>::type
lower_less(const Type& left, const Type& right)
{
    return domain_less<Type>(lower(left), lower(right));
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
lower_less(const Type& left, const Type& right)
{
    return domain_less<Type>(first(left), first(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
lower_less(const Type& left, const Type& right)
{
    if(left_bounds(left,right) == interval_bounds::right_open())  //'[(' == 10
        return domain_less_equal<Type>(lower(left), lower(right));
    else
        return domain_less<Type>(lower(left), lower(right));
}


//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_static_bounds<Type>, bool>::type
upper_less(const Type& left, const Type& right)
{
    return domain_less<Type>(upper(left), upper(right));
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
upper_less(const Type& left, const Type& right)
{
    return domain_less<Type>(last(left), last(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
upper_less(const Type& left, const Type& right)
{
    if(right_bounds(left,right) == interval_bounds::left_open())
        return domain_less_equal<Type>(upper(left), upper(right));
    else
        return domain_less<Type>(upper(left), upper(right));
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>,
                          typename Type::bounded_domain_type   >::type
lower_min(const Type& left, const Type& right)
{
    return lower_less(left, right) ? bounded_lower(left) : bounded_lower(right);
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>,
                          typename Type::bounded_domain_type   >::type
lower_max(const Type& left, const Type& right)
{
    return lower_less(left, right) ? bounded_lower(right) : bounded_lower(left);
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>,
                          typename Type::bounded_domain_type   >::type
upper_max(const Type& left, const Type& right)
{
    return upper_less(left, right) ? bounded_upper(right) : bounded_upper(left);
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>,
                          typename Type::bounded_domain_type   >::type
upper_min(const Type& left, const Type& right)
{
    return upper_less(left, right) ? bounded_upper(left) : bounded_upper(right);
}


//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(lower(left), lower(right));
}

template<class Type>
typename boost::enable_if<has_symmetric_bounds<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(first(left), first(right));
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(first(left), first(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
lower_equal(const Type& left, const Type& right)
{
    return (left.bounds().left()==right.bounds().left())
        && domain_equal<Type>(lower(left), lower(right));
}


//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(upper(left), upper(right));
}

template<class Type>
typename boost::enable_if<has_symmetric_bounds<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(last(left), last(right));
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return domain_equal<Type>(last(left), last(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
upper_equal(const Type& left, const Type& right)
{
    return (left.bounds().right()==right.bounds().right())
        && domain_equal<Type>(upper(left), upper(right));
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
lower_less_equal(const Type& left, const Type& right)
{
    return lower_less(left,right) || lower_equal(left,right);
}

template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
upper_less_equal(const Type& left, const Type& right)
{
    return upper_less(left,right) || upper_equal(left,right);
}

//==============================================================================
//= Orderings, containedness (non empty)
//==============================================================================
namespace non_empty
{

    template<class Type>
    inline typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
    exclusive_less(const Type& left, const Type& right)
    {
        BOOST_ASSERT(!(icl::is_empty(left) || icl::is_empty(right)));
        return domain_less_equal<Type>(upper(left), lower(right));
    }

    template<class Type>
    inline typename boost::enable_if<is_discrete_interval<Type>, bool>::type
    exclusive_less(const Type& left, const Type& right)
    {
        BOOST_ASSERT(!(icl::is_empty(left) || icl::is_empty(right)));
        return domain_less<Type>(last(left), first(right));
    }

    template<class Type>
    inline typename boost::
    enable_if<has_symmetric_bounds<Type>, bool>::type
    exclusive_less(const Type& left, const Type& right)
    {
        BOOST_ASSERT(!(icl::is_empty(left) || icl::is_empty(right)));
        return domain_less<Type>(last(left), first(right));
    }

    template<class Type>
    inline typename boost::enable_if<is_continuous_interval<Type>, bool>::type
    exclusive_less(const Type& left, const Type& right)
    {
        BOOST_ASSERT(!(icl::is_empty(left) || icl::is_empty(right)));
        return     domain_less <Type>(upper(left), lower(right))
            || (   domain_equal<Type>(upper(left), lower(right))
                && inner_bounds(left,right) != interval_bounds::open() );
    }

    template<class Type>
    inline typename boost::enable_if<is_interval<Type>, bool>::type
    contains(const Type& super, const Type& sub)
    {
        return lower_less_equal(super,sub) && upper_less_equal(sub,super);
    }

} //namespace non_empty

//- contains -------------------------------------------------------------------
template<class Type>
inline typename boost::enable_if<is_interval<Type>, bool>::type
contains(const Type& super, const Type& sub)
{
    return icl::is_empty(sub) || non_empty::contains(super, sub);
}

template<class Type>
typename boost::enable_if<is_discrete_static<Type>, bool>::type
contains(const Type& super, const typename interval_traits<Type>::domain_type& element)
{
    return domain_less_equal<Type>(icl::first(super), element                  )
        && domain_less_equal<Type>(                   element, icl::last(super));
}

template<class Type>
typename boost::enable_if<is_continuous_left_open<Type>, bool>::type
contains(const Type& super, const typename interval_traits<Type>::domain_type& element)
{
    return domain_less      <Type>(icl::lower(super), element                   )
        && domain_less_equal<Type>(                   element, icl::upper(super));
}

template<class Type>
typename boost::enable_if<is_continuous_right_open<Type>, bool>::type
contains(const Type& super, const typename interval_traits<Type>::domain_type& element)
{
    return domain_less_equal<Type>(icl::lower(super), element                   )
        && domain_less      <Type>(                   element, icl::upper(super));
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, bool>::type
contains(const Type& super, const typename interval_traits<Type>::domain_type& element)
{
    return
        (is_left_closed(super.bounds())
            ? domain_less_equal<Type>(lower(super), element)
            :       domain_less<Type>(lower(super), element))
    &&
        (is_right_closed(super.bounds())
            ? domain_less_equal<Type>(element, upper(super))
            :       domain_less<Type>(element, upper(super)));
}

//- within ---------------------------------------------------------------------
template<class Type>
inline typename boost::enable_if<is_interval<Type>, bool>::type
within(const Type& sub, const Type& super)
{
    return contains(super,sub);
}

//- operator == ----------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
operator == (const Type& left, const Type& right)
{
    return (icl::is_empty(left) && icl::is_empty(right))
        || (lower_equal(left,right) && upper_equal(left,right));
}

template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
operator != (const Type& left, const Type& right)
{
    return !(left == right);
}

//- operator < -----------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
operator < (const Type& left, const Type& right)
{
    if(icl::is_empty(left))
        return !icl::is_empty(right);
    else
        return lower_less(left,right)
            || (lower_equal(left,right) && upper_less(left,right));
}

template<class Type>
inline typename boost::enable_if<is_interval<Type>, bool>::type
operator > (const Type& left, const Type& right)
{
    return right < left;
}



//------------------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, bool>::type
touches(const Type& left, const Type& right)
{
    return domain_equal<Type>(upper(left), lower(right));
}

template<class Type>
typename boost::enable_if<has_symmetric_bounds<Type>, bool>::type
touches(const Type& left, const Type& right)
{
    return domain_equal<Type>(last_next(left), first(right));
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>, bool>::type
touches(const Type& left, const Type& right)
{
    return domain_equal<Type>(domain_next<Type>(last(left)), first(right));
}

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>, bool>::type
touches(const Type& left, const Type& right)
{
    return is_complementary(inner_bounds(left,right))
        && domain_equal<Type>(upper(left), lower(right));
}


//==============================================================================
//= Size
//==============================================================================
//- cardinality ----------------------------------------------------------------

template<class Type>
typename boost::enable_if<is_continuous_interval<Type>,
    typename size_type_of<interval_traits<Type> >::type>::type
cardinality(const Type& object)
{
    typedef typename size_type_of<interval_traits<Type> >::type SizeT;
    if(icl::is_empty(object))
        return icl::identity_element<SizeT>::value();
    else if(   object.bounds() == interval_bounds::closed()
            && domain_equal<Type>(lower(object), upper(object)))
        return icl::unit_element<SizeT>::value();
    else
        return icl::infinity<SizeT>::value();
}

template<class Type>
typename boost::enable_if<is_discrete_interval<Type>,
    typename size_type_of<interval_traits<Type> >::type>::type
cardinality(const Type& object)
{
    typedef typename size_type_of<interval_traits<Type> >::type SizeT;
    return icl::is_empty(object) ? identity_element<SizeT>::value()
                                 : static_cast<SizeT>(last_next(object) - first(object));
}

template<class Type>
typename boost::enable_if<is_continuous_asymmetric<Type>,
    typename size_type_of<interval_traits<Type> >::type>::type
cardinality(const Type& object)
{
    typedef typename size_type_of<interval_traits<Type> >::type SizeT;
    if(icl::is_empty(object))
        return icl::identity_element<SizeT>::value();
    else
        return icl::infinity<SizeT>::value();
}

template<class Type>
typename boost::enable_if<is_discrete_asymmetric<Type>,
    typename size_type_of<interval_traits<Type> >::type>::type
cardinality(const Type& object)
{
    typedef typename size_type_of<interval_traits<Type> >::type SizeT;
    return icl::is_empty(object) ? identity_element<SizeT>::value()
                                 : static_cast<SizeT>(last_next(object) - first(object));
}

template<class Type>
typename boost::enable_if<has_symmetric_bounds<Type>,
    typename size_type_of<interval_traits<Type> >::type>::type
cardinality(const Type& object)
{
    typedef typename size_type_of<interval_traits<Type> >::type SizeT;
    return icl::is_empty(object) ? identity_element<SizeT>::value()
                                 : static_cast<SizeT>(last_next(object) - first(object));
}



//- size -----------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval<Type>,
    typename size_type_of<interval_traits<Type> >::type>::type
size(const Type& object)
{
    return cardinality(object);
}

//- length ---------------------------------------------------------------------
template<class Type>
inline typename boost::enable_if<is_continuous_interval<Type>,
    typename difference_type_of<interval_traits<Type> >::type>::type
length(const Type& object)
{
    typedef typename difference_type_of<interval_traits<Type> >::type DiffT;
    return icl::is_empty(object) ? identity_element<DiffT>::value()
                                 : upper(object) - lower(object);
}

template<class Type>
inline typename boost::enable_if<is_discrete_interval<Type>,
    typename difference_type_of<interval_traits<Type> >::type>::type
length(const Type& object)
{
    typedef typename difference_type_of<interval_traits<Type> >::type DiffT;
    return icl::is_empty(object) ? identity_element<DiffT>::value()
                                 : last_next(object) - first(object);
}

template<class Type>
typename boost::enable_if<is_continuous_asymmetric<Type>,
    typename difference_type_of<interval_traits<Type> >::type>::type
length(const Type& object)
{
    typedef typename difference_type_of<interval_traits<Type> >::type DiffT;
    return icl::is_empty(object) ? identity_element<DiffT>::value()
                                 : upper(object) - lower(object);
}

template<class Type>
inline typename boost::enable_if<is_discrete_static<Type>,
    typename difference_type_of<interval_traits<Type> >::type>::type
length(const Type& object)
{
    typedef typename difference_type_of<interval_traits<Type> >::type DiffT;
    return icl::is_empty(object) ? identity_element<DiffT>::value()
                                 : last_next(object) - first(object);
}

//- iterative_size -------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval<Type>,
    typename size_type_of<interval_traits<Type> >::type>::type
iterative_size(const Type&)
{
    return 2;
}


//==============================================================================
//= Addition
//==============================================================================
//- hull -----------------------------------------------------------------------
/** \c hull returns the smallest interval containing \c left and \c right. */
template<class Type>
typename boost::enable_if<has_static_bounds<Type>, Type>::type
hull(Type left, const Type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;

    if(icl::is_empty(right))
        return left;
    else if(icl::is_empty(left))
        return right;

    return
        construct<Type>
        (
            (std::min)(lower(left), lower(right), domain_compare()),
            (std::max)(upper(left), upper(right), domain_compare())
        );
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
hull(Type left, const Type& right)
{
    if(icl::is_empty(right))
        return left;
    else if(icl::is_empty(left))
        return right;

    return  dynamic_interval_traits<Type>::construct_bounded
            (
                lower_min(left, right),
                upper_max(left, right)
            );
}

//==============================================================================
//= Subtraction
//==============================================================================
//- left_subtract --------------------------------------------------------------
/** subtract \c left_minuend from the \c right interval on it's left side.
    Return the difference: The part of \c right right of \c left_minuend.
\code
right_over = right - left_minuend; //on the left.
...      d) : right
... c)      : left_minuend
     [c  d) : right_over
\endcode
*/
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
left_subtract(Type right, const Type& left_minuend)
{
    if(exclusive_less(left_minuend, right))
        return right;

    return construct<Type>(upper(left_minuend), upper(right));
}

template<class Type>
typename boost::enable_if<is_static_closed<Type>, Type>::type
left_subtract(Type right, const Type& left_minuend)
{
    if(exclusive_less(left_minuend, right))
        return right;
    else if(upper_less_equal(right, left_minuend))
        return identity_element<Type>::value();

    return construct<Type>(domain_next<Type>(upper(left_minuend)), upper(right));
}

template<class Type>
typename boost::enable_if<is_static_open<Type>, Type>::type
left_subtract(Type right, const Type& left_minuend)
{
    if(exclusive_less(left_minuend, right))
        return right;

    return construct<Type>(domain_prior<Type>(upper(left_minuend)), upper(right));
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
left_subtract(Type right, const Type& left_minuend)
{
    if(exclusive_less(left_minuend, right))
        return right;
    return  dynamic_interval_traits<Type>::construct_bounded
            ( reverse_bounded_upper(left_minuend), bounded_upper(right) );
}


//- right_subtract -------------------------------------------------------------
/** subtract \c right_minuend from the \c left interval on it's right side.
    Return the difference: The part of \c left left of \c right_minuend.
\code
left_over = left - right_minuend; //on the right side.
[a      ...  : left
     [b ...  : right_minuend
[a  b)       : left_over
\endcode
*/
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
right_subtract(Type left, const Type& right_minuend)
{
    if(exclusive_less(left, right_minuend))
        return left;
    return construct<Type>(lower(left), lower(right_minuend));
}

template<class Type>
typename boost::enable_if<is_static_closed<Type>, Type>::type
right_subtract(Type left, const Type& right_minuend)
{
    if(exclusive_less(left, right_minuend))
        return left;
    else if(lower_less_equal(right_minuend, left))
        return identity_element<Type>::value();

    return construct<Type>(lower(left), domain_prior<Type>(lower(right_minuend)));
}

template<class Type>
typename boost::enable_if<is_static_open<Type>, Type>::type
right_subtract(Type left, const Type& right_minuend)
{
    if(exclusive_less(left, right_minuend))
        return left;

    return construct<Type>(lower(left), domain_next<Type>(lower(right_minuend)));
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
right_subtract(Type left, const Type& right_minuend)
{
    if(exclusive_less(left, right_minuend))
        return left;

    return  dynamic_interval_traits<Type>::construct_bounded
            ( bounded_lower(left), reverse_bounded_lower(right_minuend) );
}

//==============================================================================
//= Intersection
//==============================================================================
//- operator & -----------------------------------------------------------------
/** Returns the intersection of \c left and \c right interval. */
template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
operator & (Type left, const Type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;

    if(icl::is_empty(left) || icl::is_empty(right))
        return identity_element<Type>::value();
    else
        return
        construct<Type>
        (
            (std::max)(icl::lower(left), icl::lower(right), domain_compare()),
            (std::min)(icl::upper(left), icl::upper(right), domain_compare())
        );
}

template<class Type>
typename boost::enable_if<has_symmetric_bounds<Type>, Type>::type
operator & (Type left, const Type& right)
{
    typedef typename interval_traits<Type>::domain_compare domain_compare;

    if(icl::is_empty(left) || icl::is_empty(right))
        return identity_element<Type>::value();
    else
        return
        construct<Type>
        (
            (std::max)(icl::lower(left), icl::lower(right), domain_compare()),
            (std::min)(icl::upper(left), icl::upper(right), domain_compare())
        );
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
operator & (Type left, const Type& right)
{
    if(icl::is_empty(left) || icl::is_empty(right))
        return identity_element<Type>::value();
    else
        return  dynamic_interval_traits<Type>::construct_bounded
                (
                    lower_max(left, right),
                    upper_min(left, right)
                );
}


//- intersects -----------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
intersects(const Type& left, const Type& right)
{
    return !(   icl::is_empty(left) || icl::is_empty(right)
             || exclusive_less(left,right) || exclusive_less(right,left));
}

//- disjoint -------------------------------------------------------------------
template<class Type>
typename boost::enable_if<is_interval<Type>, bool>::type
disjoint(const Type& left, const Type& right)
{
    return icl::is_empty(left) || icl::is_empty(right)
        || exclusive_less(left,right) || exclusive_less(right,left);
}

//==============================================================================
//= Complement
//==============================================================================

template<class Type>
typename boost::enable_if<is_asymmetric_interval<Type>, Type>::type
inner_complement(const Type& left, const Type& right)
{
    if(icl::is_empty(left) || icl::is_empty(right))
        return  identity_element<Type>::value();
    else if(exclusive_less(left, right))
        return construct<Type>(upper(left), lower(right));
    else if(exclusive_less(right, left))
        return construct<Type>(upper(right), lower(left));
    else
        return identity_element<Type>::value();
}

template<class Type>
typename boost::enable_if<is_discrete_static_closed<Type>, Type>::type
inner_complement(const Type& left, const Type& right)
{
    if(icl::is_empty(left) || icl::is_empty(right))
        return  identity_element<Type>::value();
    else if(exclusive_less(left, right))
        return construct<Type>(domain_next<Type>(upper(left)), domain_prior<Type>(lower(right)));
    else if(exclusive_less(right, left))
        return construct<Type>(domain_next<Type>(upper(right)), domain_prior<Type>(lower(left)));
    else
        return identity_element<Type>::value();
}

template<class Type>
typename boost::enable_if<is_discrete_static_open<Type>, Type>::type
inner_complement(const Type& left, const Type& right)
{
    if(icl::is_empty(left) || icl::is_empty(right))
        return  identity_element<Type>::value();
    else if(exclusive_less(left, right))
        return construct<Type>(last(left), first(right));
    else if(exclusive_less(right, left))
        return construct<Type>(last(right), first(left));
    else
        return identity_element<Type>::value();
}

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, Type>::type
inner_complement(const Type& left, const Type& right)
{
    if(icl::is_empty(left) || icl::is_empty(right))
        return  identity_element<Type>::value();
    else if(exclusive_less(left, right))
        return right_subtract(left_subtract(hull(left, right), left), right);
    else if(exclusive_less(right, left))
        return right_subtract(left_subtract(hull(right, left), right), left);
    else
        return identity_element<Type>::value();
}

template<class Type>
inline typename boost::enable_if<is_interval<Type>, Type>::type
between(const Type& left, const Type& right)
{
    return inner_complement(left, right);
}



//==============================================================================
//= Distance
//==============================================================================
template<class Type>
typename boost::
enable_if< mpl::and_< is_interval<Type>
                    , has_difference<typename interval_traits<Type>::domain_type>
                    , is_discrete<typename interval_traits<Type>::domain_type>
                    >
         , typename difference_type_of<interval_traits<Type> >::type>::type
distance(const Type& x1, const Type& x2)
{
    typedef typename difference_type_of<interval_traits<Type> >::type difference_type;

    if(icl::is_empty(x1) || icl::is_empty(x2))
        return icl::identity_element<difference_type>::value();
    else if(domain_less<Type>(last(x1), first(x2)))
        return static_cast<difference_type>(icl::pred(first(x2) - last(x1)));
    else if(domain_less<Type>(last(x2), first(x1)))
        return static_cast<difference_type>(icl::pred(first(x1) - last(x2)));
    else
        return icl::identity_element<difference_type>::value();
}

template<class Type>
typename boost::
enable_if< mpl::and_< is_interval<Type>
                    , has_difference<typename interval_traits<Type>::domain_type>
                    , is_continuous<typename interval_traits<Type>::domain_type>
                    >
         , typename difference_type_of<interval_traits<Type> >::type>::type
distance(const Type& x1, const Type& x2)
{
    typedef typename difference_type_of<interval_traits<Type> >::type DiffT;

    if(icl::is_empty(x1) || icl::is_empty(x2))
        return icl::identity_element<DiffT>::value();
    else if(domain_less<Type>(upper(x1), lower(x2)))
        return lower(x2) - upper(x1);
    else if(domain_less<Type>(upper(x2), lower(x1)))
        return lower(x1) - upper(x2);
    else
        return icl::identity_element<DiffT>::value();
}

//==============================================================================
//= Streaming, representation
//==============================================================================
template<class Type>
typename boost::
    enable_if< mpl::or_< is_static_left_open<Type>
                       , is_static_open<Type>    >, std::string>::type
left_bracket(const Type&) { return "("; }

template<class Type>
typename boost::
    enable_if< mpl::or_< is_static_right_open<Type>
                       , is_static_closed<Type>   >, std::string>::type
left_bracket(const Type&) { return "["; }

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, std::string>::type
left_bracket(const Type& object)
{
    return left_bracket(object.bounds());
}

//------------------------------------------------------------------------------
template<class Type>
typename boost::
    enable_if< mpl::or_< is_static_right_open<Type>
                       , is_static_open<Type>     >, std::string>::type
right_bracket(const Type&) { return ")"; }

template<class Type>
typename boost::
    enable_if< mpl::or_< is_static_left_open<Type>
                       , is_static_closed<Type>    >, std::string>::type
right_bracket(const Type&) { return "]"; }

template<class Type>
typename boost::enable_if<has_dynamic_bounds<Type>, std::string>::type
right_bracket(const Type& object)
{
    return right_bracket(object.bounds());
}

//------------------------------------------------------------------------------
template<class CharType, class CharTraits, class Type>
typename boost::enable_if<is_interval<Type>,
                          std::basic_ostream<CharType, CharTraits> >::type&
operator << (std::basic_ostream<CharType, CharTraits> &stream, Type const& object)
{
    if(boost::icl::is_empty(object))
        return stream << left_bracket<Type>(object) << right_bracket<Type>(object);
    else
        return stream << left_bracket<Type>(object)
                      << interval_traits<Type>::lower(object)
                      << ","
                      << interval_traits<Type>::upper(object)
                      << right_bracket<Type>(object) ;
}

}} // namespace icl boost

#endif

/* interval.hpp
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
*/
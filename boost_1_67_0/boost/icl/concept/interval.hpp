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
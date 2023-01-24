/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_DIFFERENCE_TYPE_OF_HPP_JOFA_080911
#define BOOST_ICL_TYPE_TRAITS_DIFFERENCE_TYPE_OF_HPP_JOFA_080911

#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/type_traits/is_pointer.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/no_type.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(difference_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_difference_type 
      : mpl::bool_<detail::has_difference_type<Type>::value>
    {};

    //--------------------------------------------------------------------------
    template<class Type> // type_of(T-T)==T
    struct is_subtraction_closed
    {
        typedef is_subtraction_closed type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_numeric<Type>
                             , mpl::and_< has_rep_type<Type>
                                        , mpl::not_<has_difference_type<Type> > 
                                        >
                             >::value)
            );
    };

    //--------------------------------------------------------------------------
    template<class Type>
    struct has_difference
    {
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_subtraction_closed<Type>
                             , is_pointer<Type> 
                             , has_difference_type<Type> >::value) 
            );
    };

    //--------------------------------------------------------------------------
    template <class Type, bool has_difference, bool has_diff_type> 
    struct get_difference_type;

    template <class Type>
    struct get_difference_type<Type, false, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_difference_type<Type*, true, false>
    {
        typedef std::ptrdiff_t type;
    };

    template <class Type>
    struct get_difference_type<Type, true, false>
    {
        typedef Type type;
    };

    template <class Type>
    struct get_difference_type<Type, true, true>
    {
        typedef typename Type::difference_type type;
    };

    //--------------------------------------------------------------------------
    template<class Type> 
    struct difference_type_of
    { 
        typedef typename 
            get_difference_type< Type 
                               , has_difference<Type>::value
                               , has_difference_type<Type>::value
                               >::type type;
    };

}} // namespace boost icl

#endif



/* difference_type_of.hpp
33bTRSDmw2xDbsQq0p7OUz+KeldgIaTa42mm+ArYLMoVf0HsDr9zzsbvW74e7GC/d1J7fscu38pmPxklfdiPCbwDc36O75Iuf1eAdCDS68O9WDUFbRCxopwPiynN5ddI9LmlM6kfXBIMwTgllmuXl+IHSBsMyzk6q2MZujgdRVQZwc5dU4myl/bwssM8pvj950IXbar1ALOkdtHiBsZ/APOeY/gmhm+urWlsdgFfPwP4e59i+IZG1+L6WuCrZkNfPN/I8O5FntrmedU1tVRWXRXigC4vo7ncLU3Vnpo69p72YsThzv4Ho9U01tRXtyAOB1rBHOx/feQGRquud1e3UDyNdTjOvYLhFy/CmhLwJ6oQL7viUV626jbebuvPRi77F1+Jkua8hFhqwB0jYzc55/aCjnlED0UY317yDUk5d0U6SAeK8GeRaz89Z7Clg9jcQX7ABviNeFfO8kdZXbcuj3J+5CjMyPnZEx3LqoPEyaUrJ7Rt5kJOkW8lZLDQBcWXnY4+WPHrlQ3ei3vgkS/q7aJ9rRr4o8NWEuWk4THfRE9HO76l9UFXbUuNuh/tcjpsLcf9S5Y0uF31S9yNxC7oJVMCDb3Tci9xOBynUd7J0IU52S8GQ1GfP9KhOkmb1uN9zq+3ErnVzc3V50Mw8JPPxXduWEc5a4M0ngh8WQ3q6vbHO1wBejZ88wx2p3iu89rDREZL9bxaKmdu42LS
*/
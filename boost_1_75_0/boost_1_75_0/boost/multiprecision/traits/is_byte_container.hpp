///////////////////////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_IS_BYTE_CONTAINER_HPP
#define BOOST_IS_BYTE_CONTAINER_HPP

#include <iterator>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_cv.hpp>

namespace boost { namespace multiprecision { namespace detail {

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_member_const_iterator, const_iterator, false)

template <class C, bool b>
struct is_byte_container_imp
{
   // Note: Don't use C::value_type as this is a rather widespread typedef, even for non-range types
   typedef typename boost::remove_cv<typename std::iterator_traits<typename C::const_iterator>::value_type>::type container_value_type;
   static const bool                                                                                              value = boost::is_integral<container_value_type>::value && (sizeof(container_value_type) == 1);
};

template <class C>
struct is_byte_container_imp<C, false> : public boost::false_type
{};

template <class C>
struct is_byte_container : public is_byte_container_imp<C, has_member_const_iterator<C>::value>
{};

}}} // namespace boost::multiprecision::detail

#endif // BOOST_IS_BYTE_CONTAINER_HPP

/* is_byte_container.hpp
T3CGBU6XVtApLDrGAXgjPaRy+U/2BhloO+7xn7O6liGF+WfjTPQC01oXvfNbiV/GpVXfqbkzPEyk9zK5ZbjW2SNBoKRBwxz1z7sN0Zimbs5g0ZijpgD90CZcS349CKcZ18IcB6/1RQ3QNEmadxW82VHdagBGdsy7DE5s83qm235GEYjISM2D2T+dFk0ueZKnNt9f4jnX22eFD8ZX7R9I792t7oYDkD+ilCDFvo6r+LihOcm0lrmoU0NrGdk/eb8Efw7hH1XyvBtNevXH6hvPYCB3Hs1Q+ooG11uVfxDpzwTJQigouhPBPVIFYhybdCAjWBI3FCZY21ifQy7bVzQCdKT+Nl9XkOVzQorv3S1JwcfHqjsDaeMD43wuGVaOcmCkCo/igLRKjNQHrSt1Vm3JS2RAqI7AZ1Aw7ivqTGrj+6wTyReCElS2z1eNz6M2BMIZtR6Qb9oOWbF/KfPk8ykuQd98Hs2adN9HqhMbi4MdvkHtTH0Ybwuw7MHpFoG0DUT7p+o9z5v1orVPhPSiWN70mJ3MUp90IiNHQmGMSc5/JQdlp/qpB3CZpOWnpHJcdXpwiB3zh//ChRHdb15DBFi2AKXAMGdwSEsAUqu7XRlbZNt+aGyDxof0xvOosS8X4AUcnlo0LO2+E7ivr9+/8RoWpAn5KclFl6SVHgdB4E/uVzQE/vbxXSgHc604Xftr+xR1SHub8vDwxKJ+WQMS
*/
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP
#define BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME data
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_contiguous_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

namespace boost {
namespace container {
namespace dtl {

template <class Container>
struct is_contiguous_container
{
   static const bool value =
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<Container>::value && 
      boost::container::is_contiguous_container_detail::
         has_member_function_callable_with_data<const Container>::value;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_CONTIGUOUS_CONTAINER_HPP

/* is_contiguous_container.hpp
EStIE12P00L1qTtRV+UelBh9FX8+iVgVp9HW9TeRrq4+OqH6ECkesEMLl6aiFbLpaMvObHRAKR+pnS5GevquaHHhbbQ91RxdKKSj7dW38LPTDXTzMR2Zmd9BN+5YoYcPrZDnvbvocZg5eul7H5lbO6DHDi7IxjcYuTg7I08vH/T8hT8KDAxEMff0sa4PUMNDY5Tn9gQ1uVmhiOeuKN/VAcV7e6L0l54oPvwVevcqALUEuKKgDyGoI+UGaq2/gbISfVF7HM5v9kRBryJRQHQc8m8vQOGFZSg2Lg7lJcSiuKwclJObizpzElDhhwhUVFKMOityUWpRGcqurESVVdUIPn1A0FCDyprrCYaKs5Z/xZ5zQ2NdXWNjXVkurvlr4cfhI1Zv3EJ+6JqVi5mZzEYcmHVfKbJntZjm1cePXPwY1gnJWbmEl5KRm4ul9MMvt0lT4+zZqw8OP39hk5xNBBB+ZmNuXW52bllSX/Z1v58UEcJPXZeXHHJ2tc2t4/I3luEmZCfn9uVfP2/I4IEDVdVOnfpBZseOw3llHH7CnZuVlJSb3Jt91zTxo6pqaupXfp0zZ/5CGZkdRWV1OBB2zJ30Rf3Tpg07duaiqf6v06ZPl5BYuHDh/txcijk5YeyYcUlZ2VlZ2XzsKtOmTbmkqb94voyMjMT06dOnTpXOyspKTho3bsyYsQkZWKcy3K98jZ3861zJpVJ/rFx56IDM
*/
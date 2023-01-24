/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_SAFE_MODE_ERRORS_HPP
#define BOOST_MULTI_INDEX_SAFE_MODE_ERRORS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace safe_mode{

/* Error codes for Boost.MultiIndex safe mode. These go in a separate
 * header so that the user can include it when redefining
 * BOOST_MULTI_INDEX_SAFE_MODE_ASSERT prior to the inclusion of
 * any other header of Boost.MultiIndex.
 */

enum error_code
{
  invalid_iterator=0,
  not_dereferenceable_iterator,
  not_incrementable_iterator,
  not_decrementable_iterator,
  not_owner,
  not_same_owner,
  invalid_range,
  inside_range,
  out_of_bounds,
  same_container
};

} /* namespace multi_index::safe_mode */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* safe_mode_errors.hpp
vlVIR6Fn4G9ulWeqj+gVuuSZ6nZIzFTQIPR4iQbBJT8e6S46mfcYDB9iaYa9rkPKwG4TL+43sJsk3xNFhcswXUxdLWCMfE8slo1wutBZQ3ZXkkMlqitk93YqJC/vANSpluTOn8Nnvqn4beSigPx1IGa+rUxNOT9xMQCZ8z19BgyE147yXXdJnorZLHhHh7tKBtZ33DxLmB/iC/EgINpVNBkZi3nNwQOy7zDOGIor2uccr7sYb9Yda/JRaDfUPqrSRXp/Syu+C2ZB+W8YywyTMVqpMuXCxEUe2cv+RFIipnIrxjiaurDEs8Z1vPo1AeYen+p358K3PPydTdAC73EchC5NBgFH4ISJhsBDPXaIh3TV6LAXgfCgF3c7Kg35j5pIEJi8lZxu5no8Q/1sO6oPGMs3t/PNi/nmMby5Q3XY+GY1b+LPVKNrsvdqFGZvaAij+BALx4eIDAfTzK4Do9CW9FaRLr/dOUc/vH0Oi25yEYtyBfhX6YMNlCvp93L6Pd72L3WHcrQtOiAcpOOv6Liafre15WqYv8zmXmrhb8j439yW439faMEvIUf4JfzxfGvcAC6tD2ulX8JFuS36Jcx9vgW/hBzyg24VQE+fDQvhl+C/ezy6kjXWvVkozC1i8pO67u00lfU66sLchy7SKMlfozotXyrgHNq6egVB+mKRjbP0YaiLuO8W4t8ntCHdw9pF1wu6orHPVqDjdPTw
*/
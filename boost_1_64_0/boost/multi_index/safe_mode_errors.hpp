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
Zf69aj2ReWfePkArv+l5nJxUn3JKCUHu4Nz7Zpg4vIDlPq1MnrU6/EA0Y3cPxPn5h0Buziq4QriYALHiYUzXSh7xk1rYfvrDzicnTPspoJZZglpKlM1mLKg1SIvOa3bQBCdEuKeIMGrd9To2KYtGPwSpjH99PYzZ/OqScLsaVjLtKblZr4Vfi1m7tT7hQIh7O0H2+r986mHI1jFk6TNmfAxWJgsXqqkKQuXJPZ2umUCNVYNEbKYaTX0t3iPlqisMdQMz5CjHAT9bnbUEXMe+zMblmmw1aaRdEMoMQLd1wE1TNE53Ndm6ZDVD4z+BoPFzi2rgVtH9HhYnelBSJStVBFIhl7u61XTiZDvqspxVlvTxFmzRqhcLKzIsA+lngI4nxapWl3ML+rUohSqvM6/o+JznlvS+YKPVB1hUl6MZwxWvebw9EiJ5Sbk4k3BXQ4a9qgvkxUnCEbuu5P+tZp+QCDgGpIod9OlQMNu4qfwxqs5PkMP4z8j7kbcDZW7Hmv5i9yBydp02U4wjttkh4hZse/xBZexzDionGVH25SEGlpXv8VCc2151lcJ76A==
*/
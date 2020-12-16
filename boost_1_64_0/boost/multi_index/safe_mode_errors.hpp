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
CKPELe2QXlvnvKQ9lzJWV55txXmQpQId5ZEzbt3vTlOe2aJIrMQNPWRp3Kt/OstfJvzAkYNPlm+LgCk6n3rv+7qMxW60kyC041wM9C4P9/OZcb/IDoLYdSNRaQ6mbrSBMcMoXwbPetywdGO1DDAtmNTdLzMeb9zNvSz1QzjqN7mQ53LGdRs7S6I09I0nBnz87MqNu4Gp47t5KufwOngSsPDxirHob5ez9s0KO/Uz30JWTI28r55h6RWiyC0/zDK13owO2GTcg6MyDtieFXqOlatpQr/h6WKc85yvUVlsOUWUp2LU2UX9/h7vTDF+GLOlXXrNNq/bYkHzvdDg83w/LgtLdn7ok43OuID+RHid5kHihUmR0WcJ+OZI18d7Kc9M4CZwwTUWsjKwXw2wL1IsPNmNZO2lnhhg/2j2xa/kPF6+H4eFF3nYr9p00AtGv7KL1Mrd0LRhYQXYuj8Wxj0ZPwicIMb7+fWWrG0rMtQNC173oVXEuev4jX1rxdnDtbYw3ryHpZUWUabnklF7Xj2PHKf89/BjO7GDMhL93qLxvr8w3mzbSVImWQlazBblE6gXFny/FKdBZKeW6DYsmcOynSm4HhEnuRVnNpRtxO0QbjM5W7A38Xah9uWQY5iJ0Ia7gHYlir+nk2eWW5SJxvOYuJ8puJ8+J3HSpPT/67O/u8s7Pte8kRwPyja+hZvAQfcxcxsbY9MSD7Gmdx8E/BWMy/IBO/DcWfL8WaZxFHnaHaXNb56G/Cj5y1tjdXYQfxbxppGZoGGfUJf3EuJHWofr3I9h/tN7mmVmjY/5f9hNZX/bGos5ukOdnwuIZ8ZVxEEeni7lHpsluHaRkAeFfR1iW42aTDbU4Z5DgMdFpRV8m7oujiG2WQd3qOtgvR2j6xVxFxHHjFWsjqA86/cCHDFOcRjW5Q8Qx4xRrLzvkLjy3oBrNfI02mfiMGDp1oMD4a7c9WQdPlzh5OjS4ceBWOctvacsg6KbPq7nF09snFiWMKzfmftwHNYuyKrbK23DkL5+5zpPZxDXDI3UXVFgxJ6jWG5M0GhM/yJi6YYemxfrbua+iGObY+xTur+aOFIWwICsywrDd4k1DOeC8n6AGbnZa8wdL0R8+6ZLM9y57q/fQXxbGL8lNqaOCY01NX+sJ5xTX4ZYroSbbUv7yXlDvu4mGvPJm8k6a8GY8/krLI0ZqVA26u0C8rQphap8mNffybze0Wb5wPFD+9QH7ca8TPOL69WYo3FMyRg5Fx5DPF24R8+Fn0B842AYsRgbR57rf7TTPr7YfYJJjuNjS+J0jBjENeelHkl38RqAGx0eAGMJIY7PXQqj79BdEzF8XiJ3MX7QhgEhBHP0WhpjXMuhcV8QM6qf99h9unIX4tvamt1b+4qBJRlATHhtxJjXhfFewTnEjAwlgXUnrqOxbO1mbfVeijFvFBPf4TPXRdxovUrXj76X28bDE0Ds4d2IHXW9Gdvpg4gdqSPxerheE6+FYl5NjOnmmsZ6uj5i2+flHrnXQrF8vLKxdfgGDNcoPJYdcSPnQ1avYg/gR+parP+dQyxfD1V8Et1ON+QYILK4/Ehnay+AME933IuYEW7CyV1OxI7uO/tuhJhRrsQR+2rEjgpHQmKD3BiwfE2v/dQNYyDdpImh9fUipLPQf9juu2/K6H1jMKGc5xo4nc5eHX/rZkBXziBPUB/Uu28O39GfNRCR9gVNA+dJFQnlPf0WSAMu/P7LW+rvA/iO+74leofJiYSfukVWlP9F/ML5BVH7B37QPcE/sOXMOUePUb/KcM/xYx1N0eHbh76Tb95hdPCKibTXcRr4isUxumcbo8F9Mh1xDR4OoIxncxx4BEbaxSFNucY=
*/
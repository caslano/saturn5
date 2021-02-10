/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP
#define BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

namespace boost{

namespace multi_index{

/* dummy type and variable for use in ordered_index::range() */

/* ODR-abiding technique shown at the example attached to
 * http://lists.boost.org/Archives/boost/2006/07/108355.php
 */

namespace detail{class unbounded_helper;}

detail::unbounded_helper unbounded(detail::unbounded_helper);

namespace detail{

class unbounded_helper
{
  unbounded_helper(){}
  unbounded_helper(const unbounded_helper&){}
  friend unbounded_helper multi_index::unbounded(unbounded_helper);
};

typedef unbounded_helper (*unbounded_type)(unbounded_helper);

} /* namespace multi_index::detail */

inline detail::unbounded_helper unbounded(detail::unbounded_helper)
{
  return detail::unbounded_helper();
}

/* tags used in the implementation of range */

namespace detail{

struct none_unbounded_tag{};
struct lower_unbounded_tag{};
struct upper_unbounded_tag{};
struct both_unbounded_tag{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* unbounded.hpp
qIqYCuNsKt9BbDU1An9za/Z8Y+AFkoGmMwVv2oQFkUzacOcFt6NZAHfOZOL4wRxGN+D4c53sg+cPcOsZggmgD6WgEsEFsLzMGI23mD/u6TYa3X0VVYGKKSoVjJGe3lSIiSLAV8imFPxh09E3/mEDKSVaoDXLMlhQLDlJqKCFMnoK1FlSoYNMjtoZlxDtJ1ZEWRVTaGqcTto8NOU0j+miWhqzVPo2QJQSUbP46294C81b3HsO/YxX8dl90ew9OUr2Dw0VHmoShxHJsgWJPlsmul0qYe/W9fD0UiDiwoYVZzG0cdcoyVuNfxuwWweS86pQiGs8sTi90IMuCsYVwdo3WAboYw9rUiipawRgibUNvALMmtHC0hW0WqBzA3JUeOaeLfVw4Qt+Lc2lVVPRNoSNyo1lKtCO9vOE2uWr2b40Gg1W1Lu5VWE2GdbF9XEGbUP6Lfiz4bC3NUY81l1Bolm/uuGN4w3dQej5XqB9sGyzoeZ+HZ4DvKjKVI4kKvw70LlDqa3QTtM9TK2NWV1mfEGykOGRszRY+H44unaGoTMctuBsR2D0YadZUgqsJ7GkQkAUo/kiSwsSbEk0xlNhdHlSJnCnQehOJuHvzm+jSXjtDGq18WcrgslFidxsM/Vqomfa/n0CB0Ev4A8ZRhkl
*/
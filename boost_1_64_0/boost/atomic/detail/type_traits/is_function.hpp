/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_function.hpp
 *
 * This header defines \c is_function type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/is_function.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::is_function;
#else
using boost::is_function;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FUNCTION_HPP_INCLUDED_

/* is_function.hpp
n/+MnZjrWcycd7mkS1F/RCdpvm3iDIl7uhW2zyPHjA7lWSSN/mFIO72Hil+YTo1Oiu8TpV5rmsJ2kfukhZnueh2xH9+VbFEi+nV9n+fsjthbkKZrd6nrZpyqaKC+lzjq+wpzXy11To7dXTc+mfcxKt33XNrPviptAD276n+mfiv/Kpz950W4ZXY/+Vpd/efppcGxLFKfT5Z0U+hpEq0RONOHyvEevvMHw014hukny8Ufb+pQSJ+JI/V9sIQXWUfw/ySc1HeTT1d3X2767iwJn8mZmlkTcbKnrUmX7h4jHXvaShyz/yx9VdTxMVfijqd/7Wgdo3MBw4xciVa9590mGC/dz5lZsErqi+jNjJfuPjPbZww9QevGhjSv/eCDnKf6tYj9oEwRjTt11Ckjho4dyp8YOWr7feBwj+0g6fbcxpH8jG2gs4yr2nvL+AhxawLLKAaOQWUkXVT7RsL33L7xgcMbtm+MvKc2pINXrsttG8PXI3LJhqb55SVmTtgti8ZNdcwfx15W8jNldZZrk0+5PiZuZr1yiWG0aYPucmW6ypWVEnu5yM+3XGUdveXaQbmy65eLChqoL+Luef106cs8J4zo5C3XLcQtqV+ukjkl0XVGfLNWsVbC7egzyounmz7UxDHz3I0ov9Gr4x2ztXLMnKeevtMO8cq1HLmWuuQqLy0Mkknjpjrup0qMvfdwR7hZb9hDeaStmfGTc7iu0TYfWb5Alsr6sqhldGD9IX7UvoPwPe87tqc33Hd8BXeFgmxVG2+j7G8jG2RTG2QzHWSjHGRLHWQb3XjbYn+b2mDb6HaT7OPf5rePn9ypKuflEdN+OXit9Urjbab9bYKDbH+DbKmDbIiDbaa/UTtgfrJW14K6MM2uL46/Jzv+Pt3xd675W+6JxU7wbP6ucvyd3d3EkfXPY+02auepfw/ETdS/b8btJKxXnK5v6xo+YfJeeae4uv2SusLusK/6j9b9lk7U43b8Q+Fw3X9qlB6/DPaF18DD1P74cLUDzYD3wiPgQ7pf0CO6X9CTuj/Qi7o/0B91f6C3dV+gzbof0D/hcTBkywYPgserPW0W7AwHwW5wCDwSDoUD4MnwePVnqT8bngKL1H8eHA2vgtnwGjgGPggvhavhEvg4HAZfgqfCl+F4+BacADfDibAG5sKv4CS4G06GneNos7A/PBOeAPPgEDgNngrPgqNgITwdngOnwrmwAJbD+XAevAqeB38PF8MH4CXwQdgdPgx7wTfgRfBd+HO4A14MW8fzH//aw4WwI7xM7VULzZqcrEtKffmpRflDejMcqrUPHw2Pg2NgFhwLR8BxcAycACfDibAQ5sLZcDI8F54OfwHz4KVwGlwNp8MqWABfgDPhH2EhfBUWwQ3wHLgJzoL/grNhPGUshq3hHJgK58J0WA6PhufBk+D5cCi8AI6BF8IJ8OdwOrwYlsAKOB8uhAvgIrgY/gLeBS+Bz9r1Ba6Fl8N18Ar4CpwCd8BfwS/gUvgNvE7tnal3uuYjdUX03dx8+oB2QLwUOBD2hNRpaadZ8Eh4AhwLT4Q59nHNdzmuWvN9S/NNhldqvtvU/n2H7gP6ufYDX8DBsEbtxptrvl/iL4Tfwgq1B79c7blv1eN3qF33b2Ez+Limf07twjdAS8vH+XUNQNYbpHwdxE699vcE8dvAZ6B9/Fl4iL4v0UP9GfrexGi4Vt+f2KzvS7wEz4avwLn6vsRCfU9isfovVf/1sFrL/5r2V6/DR9W+fA18C1bDv8B39Dxb9XhLyr4RJkH7+MHwPdhX/NquLJ3XhQv1erSEUyx9/lf9L4X99H2HAfq+w0n6fsMk3b92ir7nMB3eonLequ+F3Gbs+3X+U+c=
*/
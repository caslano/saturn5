// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef MINIMUM_CATEGORY_DWA20031119_HPP
# define MINIMUM_CATEGORY_DWA20031119_HPP

# include <boost/iterator/minimum_category.hpp>

namespace boost {

// This import below (as well as the whole header) is for backward compatibility
// with boost/token_iterator.hpp. It should be removed as soon as that header is fixed.
namespace detail {
using iterators::minimum_category;
} // namespace detail

} // namespace boost

#endif // MINIMUM_CATEGORY_DWA20031119_HPP

/* minimum_category.hpp
KkpS16GUKo7iSv+kfqZD7A77i+CXcoPGmEj8Bix1yxn2MYLSlpWu1SNi2+khgms5Ype2HJG0VFVqtdpuTyEHCOdvrM9bxwBU0nJbXaqIbcXqiaqqyqJFerbodHqOSlTSoUr3AKB7CCAftS67nfOOfd4RuxKVRbWl9MRe27LEruJIbseRHHJesd6Q39g/HkCXSu45kVui5VoKZoh2RcxXW1S7rtOWiNwmvcMMyVIFoVOaFy6b708eiZVaKchJvGEJXwufbUalUmMMmyou7WXEmP61wValziz2trh1nig74FcktLQr0c8x3eLvJ59/og+E6eE2+pPG2Csbr2/b+LUZyS7+UqFlv+SB/QgO2W9cREoRcz6Pmvvhge/posuH7L9QSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAABYACQBjdXJsLW1hc3Rlci9zcmMvbWFjb3MvVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlLGplbQlgMAAMgGAAAkAAkAY3VybC1tYXN0ZXIvc3JjL21hY29zL01BQ0lOU1RBTEwuVFhUVVQFAAG2SCRgdVXbbuM2EH0vwH8YuA9OAFd6K7aLtsAizS6MNusATlC/FWNqFHFDkVqS8uXv95CynSBBg0BOoOHMuQ199+lmtaYr5xPd
*/
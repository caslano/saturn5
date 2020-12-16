/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP
#define BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
void adl_swap(T& x,T& y)
{

#if !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  using std::swap;
  swap(x,y);
#else
  std::swap(x,y);
#endif

}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* adl_swap.hpp
enalCuC6gJ/X935UXuq7lS/4ILWFXVxWlycPHZHvs/Y5b9yOc6LPObcd58l9zucNDlywBNNSmta3tuHQtH6xDYem1fjQMM70EZrWvm04NK2D23AgrdvV909LxWF1h9gFEztRYW+Ykd8tA9Nxwl3U8sOA8TpC7CMc03E2ZiT2UY7RODsaw7og2Mc4puMcm5HYxw3syVyn9cvB+wR9G54RwMldAeovYhQxfo+A6MSOf5CPg6BwgywN8usdCDeFu+uyLNUmt7Lzfkf179k5y0nUWZcMe08VVhZF2ozmvAzCQfa9/XB2jvWrkXrb3OZnXO4IwYyz8PcQDHbzRA7eE0UMlmtMN0cweoaLZzQax218X5+1OAZYXQJ4p3Oly3wLXaY4ZIpgnx+nmBQl8d5vB8U229LygPlY+KTCdS1jwhj3wQmKc19SZznW2ej05f7MMXjnlvki+LW2GdhcWpiSN7DrDgZDDXnlyLa8Bx+ZaSDvBwbvQdNTR2qeunOP74OObsuDoYO8O4xty1N38dHvyvY8uFOOvLnxbXlwrxx5l7bnwd1yHHNPfCe/u+X6uetb8XXf3VL3YGU9ElUc8+FzaWRQMUl1ze7INhzjPtIVxjOVlP3xI8ZMHgxMfheU42isgpwD4yZnRWcbOecGOTrbeP60uGOA023KEb3ZBi3w8mab2AtcHOAqty+IpxMGDrMCfUfexGErZSRG89/bOcg36+HPA5ytdcgVjWd1F3KYIpbeiT9AfXTUhw1f1fuDd3AbSfCH4ttp/n9mJDnyWL3+fye9F+CIsPSLJPYLgTJb8LN2HZcDLLS/pHEXoii8ICryuIr6OiKk37bfjDAXCogtjwBGXaeQMx2NQXNSWbS9BpxdkUFsfJeJzSB2/jaAsW6C2Kn9BDPS23M7wJhLBsQ6d6QYTy89SDAjzvP3Boy5kMC5853vMG24c9v2r99HBl23/7byRcPsA583UoVr+2Z6R1mFb1UCaKM4psNBgNjDzKg7S3ZqJd5Ut/IriT4pjlIMfUsi3uCy6K8S1o0flmvKZVUX86vSwaSE1xb1/bofwzdBCc0y3wjfkP/9bsR7VNmsZeRak96PnxwBXL0xjmHvVGHVmgR9mI5C2OBcc3H/eD+/87ys525LscGyXroNxQfLej9S1nlS1p9iWe2Bsl4mZZ2fPjRllvXykLJeHlLWy6Sseu78ydvo3JmINLCiIrW9//m5cxVNxk+CffnX9T7g7aQ8oSfcPPOyzMkEyrQHpzpyr8mGnxR+LPhJ4MeDH5XyLPw0Oa+AH0eREXgM/Myh7OzVblMNzZjSuXxOnz/QMrmZCLM4Ch0nF2iD3sJqav3jcsop/b9SXvhO4N6w8TY6xqNH6THxM4kdoBi4i11rqT3WL8n4L61jVgYyRDfy+xE+peA8P0IxGL7E7wnDbhjwPXtlFHCdF/1SZn8/8YsxisMYm8Rz/OVxE9MrS+J7dgflqPtEci87D0siHKvPUBzQ+SgfrBheTkC4fAF3k4d/XoV3pS+mNgAYfnonhh+eIWP+o2/hYz6w4zxJ7P+zId8f8wffysd85LpZkEX+v2fM2//KGPinx/wH38rHvGvnYVRmzn9+zP9L5cUxv+Oo3Oe+mXzryJifkNh5ipExv/sofgeHjvk/jNBPKx/ziJljnmJDxzzgOi/DxzziA2OeY8PHPOFsO+aBA2P+yGFzzP9BjXke/nkIHzrmMRwE8E77d0bJnXZ5FvUUcehIg+AXKd6VSqoav6f+BlH80bPWbLuXykJ4cGAjDvd5HzR4AeVN1n4x7i/37Kr9K+/Wch6UVdFp3Ei2/wFo/6jo+68Fl3MjMgT2qorH9WCLIxrvIor+EBADBKw=
*/
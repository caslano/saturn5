
#ifndef BOOST_CONTRACT_DETAIL_INLINED_OLD_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_OLD_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/old.hpp>
#include <boost/contract/detail/declspec.hpp>

namespace boost { namespace contract {

BOOST_CONTRACT_DETAIL_DECLINLINE
old_value null_old() { return old_value(); }

BOOST_CONTRACT_DETAIL_DECLINLINE
old_pointer make_old(old_value const& old) {
    return old_pointer(0, old);
}

BOOST_CONTRACT_DETAIL_DECLINLINE
old_pointer make_old(virtual_* v, old_value const& old) {
    return old_pointer(v, old);
}

} } // namespacd

#endif // #include guard


/* old.hpp
sx8hLToGbnMegEcOVpAlcxLCidBeDPlNFvKZYmTzR7Sr3NvoMdDNgIEhdD2BxrEUaAfwvB6gHo2hoQzxRByb0HUzwrNKgNYq9DnCi2qAl3Xo83yYzA6F/vH38OBhHo7/s9/z/xX5nv/sxznISM+A4CMH4Yn9NbjLshPikO3Tv+SaUsT/MeLfgji342y/F9ketU2xr0W+HQvQ2Yq41iKuNQBtqHyB0I64vnwC8AqhswHhKUDvM1TWwUxOKAyNoDW4vBJu3br1/j/lv7i0BAWVjyDklCAUqkhDxDrk81Sr8ZqPeFYgv6lD/t6KfOYVzvaI/zs0rtnTzMieyMZ9HQAdzYhrE+KHyi6E7hbEF6HvOUA/wkAbwPArgME2WCqOhzcjw1D7tBln/8//Kf/l5RWo6+iCCHkpiNhICFEoZ6ZsWs2VON+pQvyfItu/wPkO4j6GxjCJ4uGTuSLAUA/ihXaCve2IK0I/wgAaz2DHKt+RToBRpPO6F+BtP8B4Pyw/vg/vh/qgvXcA/57lP+X/6dMnaBsahSgVBfDDrO6JcfnyAeJfsmPV95u+xi3Od9A4PqD5+BziCDD5DvHrQ1y7EVfEc7R3lesb1DY+CPB+GGBiDOm9AZh5DzA7CSvPSuFdz0sYfjcJ4WFheP4nkzQAh1/lf9RE6BuWl5fh1chriLhiDAG4M9+G1XyZi9sfIP41ON9HvtOF+A8wYuAtaps7
*/
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP
#define BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/container_rebind.hpp>
#include <boost/container/detail/is_container.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class AllocatorOrContainer, class ToType, bool = is_container<AllocatorOrContainer>::value>
struct container_or_allocator_rebind_impl
   : container_rebind<AllocatorOrContainer, ToType>
{};

template<class AllocatorOrContainer, class ToType>
struct container_or_allocator_rebind_impl<AllocatorOrContainer, ToType, false>
   : allocator_traits<AllocatorOrContainer>::template portable_rebind_alloc<ToType>
{};

template<class ToType>
struct container_or_allocator_rebind_impl<void, ToType, false>
   : real_allocator<ToType, void>
{};

template<class AllocatorOrContainer, class ToType>
struct container_or_allocator_rebind
   : container_or_allocator_rebind_impl<AllocatorOrContainer, ToType>
{};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP

/* container_or_allocator_rebind.hpp
3w9WIMyX172iDCbdZpvb9OpmMiyCzJ/Z9LVzFDANGT+HkLkTx8K0ZPzc66dKTsL0ZE4FZBL1d7vQYc5HWPqfDja5CEvAY1gmmQez6IILT2BGMndmrUZdeAjLE3Kvj8ybA7OQuTE79uvoQliBkBtb8rwE5nTRNtdVfWkHTEbmwvdstZ/VQsk8manDGj6HKclsrt1784/A4gQr26nDKZheqNdl/4bXsHQyPsPfjRs8gmUJvQwuNWUtLJeMn0P+4Jf5MJMw+4nY3QdhFjJnZncbuCbDCoQ+R43vlQmTXHKwuU/+mBFrNSfBJg1LGAyTkvH3hmuehy6FhZKVZbbVfdxwmIqM72dIblc3mFbIrQhtLoOlCbltNZP3w7LI+H76JO58CMsVci9GD1bBLGT+zDbMGrYMJjE5SMoxe2tMXgiTk/E1n1Vvba2nFCwruG8RLI6M79ne6JPbYSlC7mDiw5Uwg2CLFhwrhBnJfJlVy76yCGYm4+d+trrXGVi+YJ9vOUyGFQl9psZY4mHSyw4SP2YP2i6LhCnIgpjtbNhlMUxDFsis3idXP5iezJfv9eP+d2CZZPwcFF7LrH3mCjlJ223PYBYyb2alqxb1gxWRuTHbpvXVwJyu2Obyb36x7qecTMbs3ZN772FKMndmmtFVL8HUZF78bE8q9sC0ZPxsr6f3zYKlkfH5+j773ASWJaz5tezEirBcIdevyS4jzCLMF1uyaX1YkdBLRMaaCzDZVds1H0b4nYJFkPkwq7FtzX8wtWDrTRs6wrTCmltrydbC0sg8mFUe4N0KlknG97q803E5LEdYM3vdoUyYSVjz3Ki1t2H5Qp/tsl5bTXLN1grvZgyCych4PX9LlBkWQcb389WcWG+YhiyQWR37C41hejJ+RucdItfBDIIlfLlYF5Yj9Dmr6++hsDwyvme/9ei3C2YmC2BW9q/nV2GS67bPkU/O3I+CyQV72UG9F6a8Lrxu+reqBYsjkzFLWR/9AKYnc2PmdXPMXFg6mSszvzXnrsMyycoyOzFo1x5YLpkLs7/fOu6Hmcg8mKU624+E5ZPxvd4f9bkMTHLDQSJldn9oz0cwGZkns1Dp6//BFGROzI4ffO8EUwrW//Awq6nJvPgMhQ+bwLRk/NyXpg8JhOnJ+Pu/qg+vbIKlkfF9UTlubQMzCDnDUV06LJOMn0PI5vR6sByhl6LHt9bA8sj8mU1bZjwHyxdmf+08TAMrInNnFtRsfS+Y001bU493HAWTkfFeHieMjIMpyPi5D3IMWAZTkfkyG53z4AhMK+TOTeg3BKYXctF64zBYJpkzs7qrG66B5ZDxcyjsWLgQlkvmxix4e2oizCT04t43+z0sn0zOLGB3oHUGqdnB5rOZ0b+N9ob5COaycXYQTCbY4nkb/oUFCPa/Fn3/gcnJSjJ7dSf8L1ioYIsblA2DKcj4no08mdcdphRsw5lFMliMsOYZg8cFmIaM73WFE8NuwbRkfK+vLb/nB0sRrLxp3RZYGpkTs8RrlX8+jgSruU99FJZFVpqZacE2M8wo2HBp756wk2T8M4+hH15rYBcE+xrt9gZ2TdiXZeb922AWMv6YzljYxQgrEOy3DgmZMMkt2z7/bTX/AEwqWOKEaqNgAWT2rJfbDc5kw+RkUn5/9qp9DVgdMj5fgrKcGdZYsI9jNpaFqcj4fatysltJmFawkrpbN2BpZM7MLh8u2xdmIONn+zQ+uw8si8yX2dwlQeGwPDK+n3dWV1gFM5N5MVt7MCEAVkBWjtnHmHulYdLbtnv231nP/3N132FNnV8cwBMRDDvsMBTcUVDjJE7iqMa64kZFxVVxR1w4Gzfu4K/VuHHHHerCneLCVeOoxR0=
*/
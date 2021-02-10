// Copyright 2016 Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_DLL_DETAIL_GET_MEM_FN_TYPE_HPP_
#define BOOST_DLL_DETAIL_GET_MEM_FN_TYPE_HPP_

namespace boost { namespace dll { namespace detail {

template<typename Class, typename Func>
struct get_mem_fn_type;

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...);
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<const Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) const ;
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<volatile Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) volatile;
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<const volatile Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) const volatile ;
};

}}} // namespace boost::dll::detail


#endif /* BOOST_DLL_SMART_LIBRARY_HPP_ */

/* get_mem_fn_type.hpp
q8YngEkpFChZ6A3rOOB9JTLeKJ4DU5BzlXVijQ+iAV1yKETFYRrN74LwHxc2pcjKAWcre1Cl7KscSvbAoeMZFw8WpmWdBlkgAuLnQmnE7LWQzRjdc9C8q9UAQ0GwSklgD0xUbI3umIZS61a9mUyyvqswk0kuMzXJdlSMS10/yeoOo6nZFmSrQUvoFXeB9rtQy1wUdEWK8GXbryuhSvcQFjps8onsQPGqGuDQVHBlU+AQD2y5tBNajF5ouijZKPK2KWV9shFpHYCKvmvQHdKC+3KJxLvQNznvzH5DxM7LwLKh/DslO8Seg2wwKhh5MQTxCNZMCeXCbZBcR8sEbr3FwguTO4jegxfeDXgfgvAKtSHQawf8se24wig6EHVbCZ6fOP+pne6Mk2uYLhezaJ6k82Du33pBAq9gdPESbrB6qOvfRjCqxJoKD3+Mf301foEv6CnlTG1TxTWVGL+oJoWA8TWE3o3v/A919Rw2DOtUYGKtaHklGtHcT+q+0qKt+CM+GOv4LozmcRA7v4gmq/qcw1tyZ6VXvnMMcibx/dMozmgFnpUoigq18TQCFyrZ3Jsgzv8yrq78eLoI5kkQhU6MrbkqAlpdFXNSx8WMfjWKEHYE4DMWpyC1yEM2DOXZNDj4kAJccPCpEF1NFcx5
*/
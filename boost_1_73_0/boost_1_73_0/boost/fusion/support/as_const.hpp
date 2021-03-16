/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_SUPPORT_AS_CONST_HPP
#define BOOST_FUSION_SUPPORT_AS_CONST_HPP

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    // A customization point that allows certain wrappers around
    // Fusion sequence elements (e.g. adt_attribute_proxy) to be
    // unwrapped in contexts where the element only needs to be
    // read. The library wraps accesses to Fusion elements in
    // such contexts with calls to this function. Users can
    // specialize this function for their own wrappers.
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline const T& as_const(const T& obj) BOOST_NOEXCEPT
    {
        return obj;
    }

}}}

#endif

/* as_const.hpp
cpDk8mNYtsnZsqSfg/vLEDlGjVycFE7T1cjlh4yUuiGSAV3RXdw/BYVzyRVSl8nVmI5dGTp4Z+ipmxEFMZ3NRFuJAKbouLpsuT5Ax5pEwHHlHL3JmpvMV+an2N0dhfJ8EeUXL4nsEqRcZtO2zBYRMjM9E0vbUqpMIM383DZ2f47cA46TG6ct85VxNn1ifgbJpmerKXHDJnfMIbdPU/nx6my5tl8ol6fHw73daA8VZ6JUTNHazk9NTxRDxZi2QeY=
*/
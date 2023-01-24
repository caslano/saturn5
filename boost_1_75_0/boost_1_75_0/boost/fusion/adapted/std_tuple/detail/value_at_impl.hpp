/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09242011_1744)
#define BOOST_FUSION_VALUE_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : std::tuple_element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
9/mz8GAmJ4V4KrjBahlK3SYKEFOLYajrpT6mjJ4MWTMLHn8JdXRckybmhmpFzwdWBI1ScB/0w5iRGG+ndMYYf1YikBsSJtdndD/bnxXPjROmYYeMyW+pL0hLyB55Ytf5x4t+DfGvqb0U7mfnd4Jzak2sM8DLXOXjReJjJE2mLeJ5kErNTzELQCJPL0YfXKVNHUFtqpegwSqT2SXB/UWmxnYcWtiKHPKB3/dDqRxt4Fqth5lWaXkxKZQqm6bOY2fxSJ1c30jNGzS4jstcH6UpCHoOGCC9ZgrZLvjN2fB5V/Aoquwu+y6KVZhTpqDyy8gaZ3oHamqiK7HG3pTBSbHckONtIy+vcVceUj9gGCX4csi0WPLVRNi/zeDtb9w/gteNuF5S+F+BwUl0Qo5eDHh0yUK483tKkS+irSTaH9gykPcH4BbtD5wRt4y3MuxiuiQUxZiaYZdTAJvkF+RxKbaJ+oTPwn6gJ2LovbzoT1t+B/gvBjIPXST0MV5MGGrPE3+snSP+iBV/HN/RUqsVpuaarwY6zIoyMaYrdFlAHWn619AaPsdoksFy9ZhNdETYhdQRpdwRyuFATTw9kocDcps/2+/YJB7VZrm96YJ3+5RlcQgbCt7pvu7gnT43VHaP9K7FlZZNzosEkYtU/bhH0VN4GG7c/RPsbLNZzo3no4wc84g3Rzmj95h3PXJ0jxCT12KWezUOOPDkoeKXmMAT
*/
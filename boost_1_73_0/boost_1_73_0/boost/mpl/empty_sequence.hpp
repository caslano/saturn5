
#ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
// Copyright Alexander Nasonov 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace mpl {

struct empty_sequence
{
    struct tag;
    typedef empty_sequence type;
    struct begin { typedef random_access_iterator_tag category; };    
    typedef begin end;
};

template<>
struct size_impl<empty_sequence::tag>
{
    template< typename Sequence > struct apply
        : int_<0>
    {
    };
};

}}

#endif // #ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

/* empty_sequence.hpp
OraJlJW8/Zyfrid/vxKyEWSpHaNVhkIb83PD8R77hq3qBi+kjH4qRi8htYES+1/sX5gaVKbH5MfJXkH23z1hkNWvZ5IDPLesCjFkWT/oBiRGD8RwvzrJBAZGoMCCroHYwq4eer9TZopZ5enytt+/5gELV2CC6/INeRi1IzCKUPiBRAn9BC4+1jdPPKsxCcXAuaSXFpg6dp0LjVVXkXTQevtZlNXxfNieiq9jWX2czsV3pded/+EMH3fp5z/+AVBLAwQKAAAACAAtZ0pSLHkDM5IBAAB9AwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1NTFVVAUAAbZIJGDFU8Fq3DAQvQ/sPwyEEAh1ZbtJIEYYSlqypZvukrgfoMrjtYhXWqRxlvx95bUTB3JrDzlJo3kz7+mNJJkCaxWoBGls4+LySM8H5+tQwq7v2IAU84kUIwhO8IH8E/kkmJpAetp3zzFdK1YlLKtqI7LPGX5Jc1z/hG+KqcCqp0+YXuMv94R5mqWYXRQX10Wa4u1dBTfOMllOVmS33BZ4BSunFRtnCxTZ5WWWpmkOkDTOJVHGSHTky98Q5rHbPxJmGYCn2njSTPVEkU8cuiX9WL7Nv4NOECkmL6JFN50ZGEaL9DGIgHA0roSW
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_10022005_1619)
#define FUSION_EMPTY_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct empty_impl;

    template <>
    struct empty_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::empty<Sequence> {};
    };
}}

#endif

/* empty.hpp
TvozjGYnWMpgQoaH0fx2cj/HQ3867Y/nC0y+oz9eJLKfo/GQW29YzIOea0+BxT3Mqq4MqYPm+1neKbT06A64cUKRcpEHd+Gs4KJF7DeNrZt4/qVzSpY7hLz75m8ETPYHUEsDBAoAAAAIAC1nSlJJTDUjbwcAAFMXAAAYAAkAY3VybC1tYXN0ZXIvbGliL2R5bmJ1Zi5jVVQFAAG2SCRgxVdfc9M4EH/Pp1hgBpKSJr3e3MsVmAtp4TJXUqZJh+kA41FsOdbhWB5JThpov/vtSrLjpEnbB3qYKbG12tXub/+qu/fzngbswb1PYP8CfPDXcnxU8l8emu27g+Aa3D/k+oK/9x3ShRXLddCC+1muoWlZAn/KK3oPgvsO+kK60X9d4vwS0CuuIBtx9mW+VGKaGGj2W3B4cHjQhmOWCZ7CyPBswtW0Da8iu/JXwq6uOpq/aQM3wNKOlzFOhAYtY7NgigO+pyLkmeYRMA0R16ESE/wQGZiEQyxSDv2zj5eD4fs2LBIRJiRkKQvQiSzSCBI256B4yMXcyciZMiBjZEfhkdAGBRZGyKyDZ3MwXM00yaDjWaolsDkTKZvgQcxAYkyu/+x2w0KlqH03kqHuhqXdncTMKksuUYkZW4LMDRgJheZtoJ1tmMlIxPSLgOBi
*/
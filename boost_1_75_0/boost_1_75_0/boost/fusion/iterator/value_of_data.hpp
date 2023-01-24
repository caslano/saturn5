/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP
#define BOOST_FUSION_ITERATOR_VALUE_OF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct value_of_data_impl;

        template <>
        struct value_of_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template value_of_data<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct value_of_data
          : extension::value_of_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* value_of_data.hpp
3JCuU+PObnw81lk3Av+dxW5upMPyCxwhp2ztstu/6mMcEmED3svaL+j0w8AOfcp+v7LDRfG0WrFTaSTADuv26u3BtLUXzNCk4Hzase+D4cNIXlHnTX267DuqZ+L6vrWJT+XC69DZSSeDCC/qyZHMhzaZLEmV9ZfF04moqScjnWC/Lvg4WS7BfxXQRpSv4e5STMdnbONzvUlNjMgAdMOtnKdoAckq0jFlWilO9BvUQ5RDiVL4VwGc4V00r4UpbGdqu4j5KVGOaMVylfDTxvC3UszsYo9BqdwcGfyWCXWqWynzjeOEtG4LaRpAhNrbn8PryayNZ/WXKJNpff4hBJtb87nJBE9T1Bs99wv9uaf6szsxaRjxubWx595Rp8BzyseIq+ByfCyF/khAJDhE5Xhwx40LU4865KwlvXPlLFlxplEdk+BitMWtHPQpJXZ8YDsWSY8VCZ6hctnU0TqfItunKumHZU7JxMAyWu10JakOfUxItTVODrahYPTI96INP1Ll56RpcQJ/T2qU9RRP45xoCuXsW7GshjuwpnrHJKxmElQzMw23gzPULYSexC13Eky+vo2iFYXjbkbrX7rfQgrKkn5IukblG2846Vt6+aOX06fC3AV90J88Rp8faYJsNIH6glIpKeHGFUNntO1AncNeBSbhtbBuXOF5r5u0+paZtIXi+g0X+MKlacSK6Xt5GhmDcNY2SxZTNMW1Ddce
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };

    template <>
    struct end_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
g5jWHqhoG47uMC14LheYeBtantPGnDeJ2Hnps2xS/kbJnrjnIDiygoEbwzQewJpIJm24niaXwSKBazeKXD9ZQnABrr/s8a6m/jlqg6HXBuh93VCJLBpgm7piNH/m/Lt2uuUklzBZRLMgTNKvgbtILsfpmedGXgRHMDg8gd9bjuo+/HEAg4qtdfnh2Dk6dg5wQ/9KKZEPqaRKFxq/qCmJsPEl+O7cs/4He7UPsqYZ6gACt1UljJ0DIFmm41bilnKDEC/9IIynsfUD41nV5hROtctOhOUny6BnAvdfMhnqN/ChRHlUqJLXWaAgS9LAB+Nw7xfj8tyLJ9E0TKaBb4UE2ZD+UN9FZENRI33j7dqtFowblWvV8Laq9rWOGCdaDiY+S8d3RlEtDbhdmIn2CgVWGXsDtlh7uEyS0Ibp3MV7GIRHRt3xPAmxE5o7lLelSuxF2da1wH7W3p6ypx9Ew/4kugRwoZluRXPrWJYvFP0IF+jpFWjbwCCFBjia6CfTGjeU0wYDMK975oay1Qe9poaI1ifcMWLOrYrpLtWL2Iu0AoZHe6si7JWBZPS4Idos64jmAtuaC9XNLHR8S2ltwHRH8RucRwL7E0iBOcU8KKU39Ryzdphd3S7cxSyx/MVsZjbCKEiCSTCLrVeCNie8
*/
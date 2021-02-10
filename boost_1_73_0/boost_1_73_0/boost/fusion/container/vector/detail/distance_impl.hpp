/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_09172005_0751)
#define FUSION_DISTANCE_IMPL_09172005_0751

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct distance_impl;

        template <>
        struct distance_impl<vector_iterator_tag>
        {
            template <typename First, typename Last>
            struct apply : mpl::minus<typename Last::index, typename First::index>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename mpl::minus<
                    typename Last::index, typename First::index>::type
                call(First const&, Last const&)
                {
                    typedef typename mpl::minus<
                        typename Last::index, typename First::index>::type 
                    result;
                    return result();
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
Jxed0/M2bXKnO/h4LgDs8BSOqGu7PSh5ZMvRCOhwspzhfsN4kxq0wxnAqDWNgP3eeYC71B7g3xb2dhk1XLnYrW/zZBsii/4hk0mNP9br4hdxUCew45om8A2BQWydgUzIchTO2u0cJaHJWDwb/z3eamig4IZ8g/8Q4aA7F52qMAaHq0QAmFR2TF+ffupdnorxcj6/5wf4VZOwAkB+yM/MFuBO3QXZLE+yqFbejwh4VJ1fKVGBAoUziIdq0Dm3eOKIcX4z+44hNRYXhoX9RzJCgcTufgmwDVE7v/jY65wCzWK3ZrvxQ72A3PDTvTo/b4iDhtgmODfUA/y3LjZfW9RYjxxlstcocqTQxBu5Bmus60XAqt7L/Bx4fhsZaa2uoPJNMy+WIlCuwzGQfP6cna+msM7FxWVv0EO5suFNwl3SU4hsLSTdAVaSGcPGFbHMa8hS/iQsfQp4cBp/LnyIdz4dQLQ8agEs+UM4Er2++B0Y0f1MMpv9v4tXBd79JwBuPQN3Ace/8Mk3c4qeXF2ej5Kx3MjgvJrJaKHFo0cdppblq9ewjdjFD+WW8BSkQLdfFJdxhWI3jBq4fzCp1PSFByislQRDtZPuDx7XuZwDvo/lXf3YfgH9HKBWfijCOUoTbCeYLwBGknoCAY0MQDgF
*/
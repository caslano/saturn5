/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_09162005_0150)
#define BOOST_FUSION_COUNT_09162005_0150

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/count_if.hpp>
#include <boost/fusion/algorithm/query/detail/count.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count(Sequence const& seq, T const& x)
    {
        detail::count_compare<T> f(x);
        return fusion::count_if(seq, f);
    }
}}

#endif


/* count.hpp
jz5tma7ly34xaUsWJ4sag9qHxO5B0ZO2RfSoL3RvmNQhpl95smqoX8l7JW8ki380z2i//kOvXeKbuxRfsbqf3nHT3Vfy+RRVP5lUrF4eob49yi5xR85G1PoNiKjv9pdUn1X1KVWnRBerB6n9C1CHm78Gdbj7L0Q87xFT8vnomJLPr1Z1SqVi9W0Rz6vEGv+UmONNn6ade8RGugb3PsT/tj+eX8aYJkrMd3Dtd+PWOdfgG4iZ
*/
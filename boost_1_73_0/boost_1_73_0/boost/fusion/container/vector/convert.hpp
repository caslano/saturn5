/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09222005_1104)
#define FUSION_CONVERT_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/detail/convert_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_vector
        {
            typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence>::type
    as_vector(Sequence& seq)
    {
        typedef typename result_of::as_vector<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence const>::type
    as_vector(Sequence const& seq)
    {
        typedef typename result_of::as_vector<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
IZOcvqpzeM1ZR67uXxtOlduqbzKxnZ2cPCUrX3fA2Ax94hi+Zft9YwzlMbgMbkGtD7FsS96k2x7z5NEVubhzkAQCjAOmB0UiyniDtReaZllrnJ8dTWOBj7cm+GBpKRN/4hr+ae/CLK0UIgba3hQ3xiuuUDZ3+DwyOe0hQIVYj1RdzBNSPbReWxOvbcevippPeG0Z4XaMOZNjpExeLNgNoQ425OOfxJ2Mx5g+nt/qd4r7L+vp4rTn3+hGJfBNTXwGRZTqgURvXDrQrIy0f/qgCRcvV4lmJWbUUwko2fXl066NCnka6eLDe2sjN9SCDKxobUTfZKcRdj0Z7lj3BUu8YV8bd5nAN7aCunaQBogLZXyTSQFP+fiDj7HmuMbziwISkIm32iHLQZNlWubu++7Pkv3DrDhaBOEcPh/ZroxNpTRsdyUwOP86Pv10fpSFy0fUX0sMC2/8QnGWBZCD7zZ6rrEGyRU8/TX+uuH188vxJk51o8WOnsmkqsg8sUzd7hvrDrY88+TBVQyvDfVrY6sL8odHfdPVoA+QHrqW5zauecbQkjcKG69WVr66aFi2O9bXRsOJkTGCMn51QrvUTIucvnpFv0ByTLH/I3hf9m1ZA5Q7K1kg5oerMgyukvfTYjaj+bu/vap4ISDotl9R
*/
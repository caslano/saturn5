
#ifndef BOOST_MPL_LIST_HPP_INCLUDED
#define BOOST_MPL_LIST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/list.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_LIST_HEADER \
    BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE).hpp \
    /**/
#else
#   define AUX778076_LIST_HEADER \
    BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_LIST_HEADER)
#   undef AUX778076_LIST_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER list.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/list.hpp>

#   define AUX778076_SEQUENCE_NAME list
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_LIST_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_LIST_HPP_INCLUDED

/* list.hpp
ldm7lPX1CiATOiTUcaVdXtpVzYsSdbcXQCQFzO0XSFW1HgpRvbx51IPxBetRfOV1dp0JCqgM6HP0bHWeIFZu8l8EHrI9n4ichtdwudlGy8ep2k46mPKi6Nl8DuixK+WIR5KEol8XT9G/eQzhVBDk8wVF/xD/sTRAoOVfS8MpC6IgU+kuq0cI+vuLA2Wbjq8g3CMlobXQ8ZvR7HIqBl2qVtL9moP5WAsyps2Lx8eWmVF8BFra+UwQdLBrZlifTi6U6lEV2sR/HXPPqVhWxcRBPwI7fWdIKmsAxn/55awgfs46j6f1IfY+UD7gnM+U7RKsC9eXe/tPk5MRrPsQQyjTfwYSFYHFp6Nm/5lIlXXwEAWfkOkjVVDrcYdf+Z+mx/1cH71ep0/X+uAW6PoeS79YY9MvKoSEW3i+WrKPsF9DjtouXXIkJIHaLvmMDi7VTN8k6D/TIvZLeJnfi5v8FH5hrNiD5iNUAidNNCYwwYV8W9I88Vj5grf6T51Pca5AUTF+LHnwHw3rgOj0Yy7vRKcTvVG0DXCUHNxekDzz/olgUigvPitp9XluAqASvg8g+DXm0nB+abYMt9hyGDZBvvZq5UuVxuNHcvzD0Tbe9LssSd5o++aTfq0fkMXxDGglmdoXu3wdzeft08M0nr39eQQH96oraMT1Ole+xkckwsCpn5y6e5oVdv7gCp3jpQV7rDogojaxRuYiEuAONhSoMUQn/HYPjJ6wN+kuumA2UEXaH33WeajnWgWRIL4zhw8z+1+ejD3Tgt9ybnL2TJRoZovpqvMT2sPaLb9oVMLykfTiMMrgCGbmCZcl0z4L/otzkmsfSlx8AMd/PS8hfe2WXzEyYfnK4dB/Lw6/r1pni3jnz+J7qRgh7xwiz72zSvoZ9S6+XsdDfA4sezTKh5yt7DsmJQQ5ElyNuOBaVeRnRMU1E83Te+BdQqle4cWk/OqU/Cp62dJoFDhVxDU/qhOx9FiUf6mrHKeqXP07Jcpn0jk51UfXVHEZFQM2TxA8Or+WXNu+iSZ4jigdyrGGeTV1WxVRXEPx0LvLFxS3Gj9owoprReCxfQvlq01bhVDZdkmSQmUPPuHz9SliZNR8lavggz3VU8aR5Z26/GUxyztR/oJ45SsH4P33i+znefVh5z51YbsoM2wzVWttTRF46OWu679IoU4zhw3Cfsjsehyit8EtJFXGcDuPZB42PtQnQd5RLcxR110oAAMyzUJ6qox3KX5b1gDOgkCtKURmgS2zu1J7c2gLbIEMtIEw6aGr+GI2IWcvjXRb5uvMho9oZZb7Okqq5KTvh1ESBiwnPURJGIx49rXWeuju2mGWHwyPRQypYRBHbgDhwrXY7JltV2Oo4Ur1aeAlnGJwO8vEXbJaYIU9YSoBg0gooFQcF79fHg+tCBCvDJXVeOTFqPrQbGOQU08t/zyaGRecAQJR4FZVoJEej7kQ35k+86/iOx7CfVR8hwfLveI7Ip3domDqyU4/Hd9xuzx/5B69XP3LfLR8fPICPd7bIt+RNm3R//RcqAsb7zVhcURbI0b/VrxMmLHe5HNcM/V4vEhk/oSx1Uhnn5gJjTycrnESLZeMsQ+6KTzIeZCsw7V/dyGG1+H5Vqy+8U4VgXCrOHj9dbY1jA+S0yBj4XtElBD0LQIsxwa2C5l1VqbLlrkDmbVW5md9rcwNyKyxMjfbMh9BZrWV+bgtczEyqyy6b6RMNbKvqAA19eLl1wlnSiWoGkICMpon7HdFUkWskvPDFK85TVTeWa2YZOZvoEp6kHed2BeqZ+UoX3iMEKP12jNfrB7HFGOOYMw/ep41L+6l72rM30Lf1ZhfSN/VvJglvxNrzOniOwIinq9gqug=
*/
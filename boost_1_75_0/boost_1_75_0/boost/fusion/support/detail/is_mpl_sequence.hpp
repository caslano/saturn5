/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105)
#define FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct is_mpl_sequence
        : mpl::and_<
            mpl::not_<is_native_fusion_sequence<T> >
          , mpl::is_sequence<T> >
    {};
}}}

#endif

/* is_mpl_sequence.hpp
8lV1q390usQIjwwEPv38Rp1WNqS73jUY7qh7MY6texUk+0dBnlTT7K8kV2sV0haT4ViPe52oXlcR4++aXYD1aSv1/ElM8GE9s9OUThECnukbvoDj+0ojAwquLYvlqfloBa8IJdWWsH9aDrjzdnkcXKEcNji5XbIFn2QKvq66PzExOrFTdDY60a7d11ev135w8Gdz0TuAWJ2dvNHNxzz3dHjYRjto25WwWfITabPq/KMZNowgZxWeoYG8utls3v0GvpJQyYvxp/ZzjyWpUddi7H7t5gF/FLvQdf5Z884pt1L22HVrkReQbk/uLzyz3SmfgEkFfsvTxhlmRK4fSwW6XlyUA9jf4ts2LYLNGY1XwRhVfk8YbPu2RtjxSP7TQu9OCyPEbZnK2zh2hRrRQF4Eo3lsMq5yNg+yyjsqJp0M/E1Ews0evGuSAiMLsvOKL0yFmVgbv1pXPOub1H5gsldoLX9D+PjNSMIe/KTR8daN6B6kb27SvdCaqFybj2OKcR5mt+A6ribqKp3geYOIcyCv32u8R+87D2BTuEFwybaBJY0K94O3zdmEdy3YdJa/JfdS7ZVVxWu/yXEP/elncrTxpEp4rBVdLVRveZ52TlaJjmQKIOt/UhRtTpOUAtCxiJQvfr5eeVKk5pLacLmYQ34w2SJlw3lm9yCtuufAvTSqe6hVt/KfmNcf/snzlUb9pn750w+bYIHntYIeee/e
*/
/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_1142)
#define FUSION_EQUAL_TO_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_equal_to
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) == extension::as_const(*b)
                && call(fusion::next(a), fusion::next(b));
        }

        template <typename I1, typename I2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };

    template <typename Seq1, typename Seq2>
    struct sequence_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& /*a*/, I2 const& /*b*/)
        {
            return false;
        }
    };
}}}

#endif

/* equal_to.hpp
dlTEEJgtuIc7RFgft+FrFXPVKuNKy0P+TGH98Di4uQ1vLoWbeLi5FW8SS/Me6OSPFzbiiE2gE+YuRy2eFKdoKXWUHG1Wd+wX2ihJCHxzJgnTd2FsIbWwWMtB+1BUpugw6uKkpXzPrFJMIj4ve3Og2TznDnWzfEdC4HBz/hfzbkZD06Tt5Qf98Y7aSBqIMuSRpqPu/Mppg9zCBzVSoOXIzCyM+CexsTakAsaA8nXDZHTyGDUoJUvBXC0rHc/AbHQUdiyMSahT7fvCRM2eGGMX1nMsYzoadtKT3cyjKTnZ1EYX5mEJEd/uAch+inRxT6pHFn3SgeRQNhA2O8X8XcLyF3F5Lfe8GjO4PUlU67YBoWHDj2ePbs6uSqqB4U1GmWqyV3Xz5p+ZGT9aHnqDZ9IWt5zcrfwn3C2t9XXDvCqJuDvaMAiQudSxRzkMF4oN2qw2YcJDpWkQ1tApv/j4vH6UUDpY3Eh5WTA5waTtJNpRCujZnPUh/1iClme+rV0cqFOw7AeJdWaPNYIGXX5w1lgmHufGUWe2COA7kyo5/HUKt7cJBUsHgiBIQCCuiBq7CZIEDYgcHQgdgMZOsTKndW5vLWd7iwt9XDsL638wYBkPsLhkWIK1heTfFxMkpcGBj2mQXNkOEsqIrIFT6gwO1tMjc4Du4QCdjSecwvpj7CjFnvr1nmSTUnw9EHkTNxnvF5mKPFjkZFtBN4kvdVmq
*/
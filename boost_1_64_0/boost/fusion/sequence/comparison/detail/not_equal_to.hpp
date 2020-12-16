/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_1141)
#define FUSION_NOT_EQUAL_TO_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_not_equal_to
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) != extension::as_const(*b)
                || call(fusion::next(a), fusion::next(b));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };

    template <typename Seq1, typename Seq2>
    struct sequence_not_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            return true;
        }
    };
}}}

#endif

/* not_equal_to.hpp
uvqdc3BMAaMMGLbNctn3mueD0Q7LQtiUYKDMrirT8YyQpaIOc2/DMucMrP8VIjMxAivwPDty62XOrawWgq2yzumpOC7+u8X+FvX3RD8ncmHvFKVxBlvBernk8n8eBMWeaMcDqpzIgJk7iK3EqZdDJzYmR8wPF1Q5RzLTN5M8YNM0t/MWuA+quJfDJTUc9kLwjHMCOoau7iE+TRC/O4dDjSFGPbUX+/gA8V3MvSR3YJMxcfjIy49OHnvFVGV83jOGVV1Dx0pjOAdCS78C99sY52UPbZ9WEkSRmyX17TO/CMNM/4Iw34r+MDpK56e0FdstN7Aa5PXX6/qDn7C/ZJz5qlwnMPwADma56z1QrpM2yhX1vzhKY3vAEMvSViusl6tpi3cOuC8r4h3qCyTcOZHYGF0N1xN7N7RHyJ/KMHxtQaqkX+d03CnwQpgdwlePDVDp3D7h0DFuBzA9k510ZyGgt9yTG5uAZ5DIO99V7lNHByt0vovEHOMavdMncS80Ouwclbu+eDOna203t7wCZkVqjAdnuBYrVMJYUFebcJ0eFws3hKqvwtYmfF/mGx+px1Rt+Bc1XE+LBXJTx5BYIPE2nQ7F4Jv0ZU5XvgfS9m1HGn4L9E3gNPod5Ju7WdyL87idxaMF/N/K6myxi1V9Q3fUYfk0prRFf2cVhx9Vvi1UMCinB+Xhnb+GIR8SY0ZpOEh62WsTG5WZ3RVMmU4CbjOKrN/Qh3gdm3GrPO7PLIiWdu97GL4Awh16H6bMHvbxC6NII4VBVfsskMmS+p6zF7DFWQrHDGn7+0jX+iLpYx97ch2uh33hxfsknZeBc8K1ggYX4atzEKkVts2zsCVW8yU9BejsLNeg4/cIvVnHt+wnOE3HW0hHHWXciqeWtNWaMoh9/1gdDnwaFDsAE86LalV4UE7EXNMxOO5RzmN1mLXzKuZzNZhq3IuJp9dgepC2V8F8tg6DsTGk3bz5gHPyp3W6Fsfz0DMAg+8wwK3QPkZo1PZi7HFGe5fW917Ic7l0s4NwXTQLA6kLFSunl+J5hi26a6vlWxzH3llhWDhJzc+xJlh9pdjDPJnGrvJt8PJ37CLRNcTX0FMdwx/0k1Z5j+dmZMVmbhoirBD662OuFhU/5VoOHFdhV34aYpWlCAc82r8/mdonu3DuCCK4c9QDjuGZdXSfuoe0LQ/OV3AWddJpembdR3CtJIvhhtUyTp2s7DXHVNwrPMeyQQUbbvqVqG9C30P7aC6aBGroGLU5UbCOUypPDFs+P0nsPFTTqmjt4qs8cHVpBi7bzxknMbAZnOYcasd8eh/NTZO3vCh33FD5Wi9/0De3xL05keMbvpPFXuC08CvWiqG6XCIyYsN3szh0LfldH6IN2vyqcqbiHNIHwksMf2NTkqgDdFn0wa+pPMec1HGtEKoB/YNwGAJ/g+AjOw0TJ8pYP6nH3yQ6Waltm5nrif6CdiVGKsZEpT0zMwl8MFuheXUeniQI8xU9Re3X4CHciuEBDCTIJEE9fHdUsTn4r6RhK4HK0X6EOttCZwP4SOz+1Iuy3NqwPZHQ+YNPbFLa2IULRHaOKLJ0a2+wfXKfaGcmHJASz2CmwNob5vsI1nfgOtF3Y4MFTBFYnDc+QtrNczM49wUwpAKHzhsXVdyRBIBJmrfga5Uw6QNF7jKjqOWGEQzRBd4PqA/UU8i8YbXMMAdsNbZkG+fR/w6q/T7NgzxPEkOzjHq2kpPeIDHddDvUfYOAkbYacv9T/D5XjamG65c/xOis+UUGG0nLh5FWfkuFBqHwgQb2F9Ai3PURaTu3chrOTco5qKDB3XZDnLVPbqujy/i6Z7YD/RHiyn6N4PR1f2qHRtfux68LjB4=
*/
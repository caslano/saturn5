/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_begin( seq )
    //{
    //    return make_segmented_iterator( segmented_begin_impl( seq, nil_ ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_begin
    {
        typedef
            segmented_iterator<
                typename segmented_begin_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq)
        {
            return type(
                segmented_begin_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_begin.hpp
I4wAGVL2xfI+DW8WGWv0HXb4l7/8yFrs1cGrwyY78ZKQR2yS8WTG05sme+3TyF8X3qdPbcnfNBnPmBe1NavpIpRMiiBbeyln8DkK5zyR3GeeZD6X8zScwZcwYdmCsyCMOOuPLq/Phj832XoRzhfI5F6smFyIVeSzhXfHWcrnPLxTPJZemjERADkw90OZAcNVFoqkDbI5y3gaS+SB4r1ICubdeWHkzUCQl7FFli3lUaczX6URaN/xxVx25mb57UUW25VcgxKxd8/EMmOZYCvJmwxnNlks/DDA32AQGFyuZlEoF81cGxCV+B2RMsmjCHkBXcilUpuziTZPE6exJWgcZvhLikSiqPVCxKWJYEfkEqzSBASBHWCSL8DMTbZKfJ7SZFq5EaFtSgbe6ZpcX5+JBJRh9d6EnU3qbObJUDbZ+7PpL6OrKXvfG497w+k1G52y3vAamb07G56A60MQljL+aZlyCcJTFsbLKOS+lvnH/XRqte/CZB6tfM7q6D1X8my1bC/q+CAAKwSsfzU+d0/OJr235wP39Ox8QI/wyS+9vw3c4WB6Bv/cs6H7S87sdcKzEP51wqS9eFP7jifg3E26k7ebJP5sx+ze+LLnkpwihZcuvQ6K2S3DPTvdFNIJgx3zJ9cT92zUn56XSOS9
*/
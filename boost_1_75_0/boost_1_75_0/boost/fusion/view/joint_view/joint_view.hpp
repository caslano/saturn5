/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOINT_VIEW_07162005_0140)
#define FUSION_JOINT_VIEW_07162005_0140

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view/joint_view_fwd.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/view/joint_view/joint_view_iterator.hpp>
#include <boost/fusion/view/joint_view/detail/begin_impl.hpp>
#include <boost/fusion/view/joint_view/detail/end_impl.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    template <typename Sequence1, typename Sequence2>
    struct joint_view : sequence_base<joint_view<Sequence1, Sequence2> >
    {
        typedef joint_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef typename
            mpl::eval_if<
                mpl::and_<
                    traits::is_associative<Sequence1>
                  , traits::is_associative<Sequence2>
                >
              , mpl::inherit2<forward_traversal_tag,associative_tag>
              , mpl::identity<forward_traversal_tag>
            >::type
        category;
        typedef mpl::true_ is_view;

        typedef typename result_of::begin<Sequence1>::type first_type;
        typedef typename result_of::end<Sequence1>::type last_type;
        typedef typename result_of::begin<Sequence2>::type concat_type;
        typedef typename result_of::end<Sequence2>::type concat_last_type;
        typedef typename mpl::int_<
            result_of::size<Sequence1>::value + result_of::size<Sequence2>::value>
        size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        joint_view(Sequence1& in_seq1, Sequence2& in_seq2)
            : seq1(in_seq1)
            , seq2(in_seq2)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq1); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        concat_type concat() const { return fusion::begin(seq2); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        concat_last_type concat_last() const { return fusion::end(seq2); }

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(joint_view& operator= (joint_view const&))

    private:
        typename mpl::if_<traits::is_view<Sequence1>, Sequence1, Sequence1&>::type seq1;
        typename mpl::if_<traits::is_view<Sequence2>, Sequence2, Sequence2&>::type seq2;
    };
}}

#endif



/* joint_view.hpp
0fOf6fb6JTN3fT7q+JA5b+15IWZN/aZrx6XPW/9748mLH14w2LnylxV3XbqrxzdNb/rr3IHnTiTMHthyyQePbfi/xkdHd/lt84yEVVOGNmxy46apWWP/eabmtOjoHXe881FTMCbmpQc3pgz8fWHktLYrLls5a8s343ctebJ26B9xWzrdV7rhjiYn9318aeFrmafCto7a9tDzA042+e3HP0aE/lA/5rHrzsX9mbgvdtjv1+3eM75R+NT1ywZs/jSj1ukdY3p+9sIXMZu6RW6p/VbI4P+8v/vS1of2R22qE7Nh22XP7b3+2ZNtb2u1s9cLEU0fPBpb+tUr0de/93LqqoQdY5zp7WaefTzziu2g9fKBCVM7n2s4a0da1q62zvmTnxgSO6lf9/ELHn/tq8z6P9w7umFpzILSuVOXLj7e84kaby06teKTsM3H84OGNXam7Wt+Pbh1d9OweT3aPbi944QjN38UFTX2sU0xswc/fl/B3CV3b+6XMO1U8HWRcz/d+MFzlzw+buTHOb1cr0+PebLFp9e/NKfhuJR75zXbccfKiPUlr7SMXHH0Wpqvctxkdb7KsCnqfJXjHlTnq1w3QZ2v8uhEdb7Kw8W4nD5VJf86tq2Adx843oFde4mLjV+u1q+Q8VfrV/B4qvUr6KnWr+Dyav0KLq/Wr5AJaORUHD2oCJ3kRaA/+pOM7r5LkC0TvUmv1reQ8VSwvsUJ
*/
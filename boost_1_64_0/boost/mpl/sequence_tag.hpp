
#ifndef BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED
#define BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED

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

#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// agurt, 27/nov/02: have to use a simplistic 'sequence_tag' implementation
// on MSVC to avoid dreadful "internal structure overflow" error
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300) \
    || defined(BOOST_MPL_CFG_NO_HAS_XXX)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct sequence_tag
{
    typedef typename Sequence::tag type;
};

#elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)

// agurt, 07/feb/03: workaround for what seems to be MSVC 7.0-specific ETI issue

namespace aux {

template< bool >
struct sequence_tag_impl
{
    template< typename Sequence > struct result_
    {
        typedef typename Sequence::tag type;
    };
};

template<>
struct sequence_tag_impl<false>
{
    template< typename Sequence > struct result_
    {
        typedef int type;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct sequence_tag
    : aux::sequence_tag_impl< !aux::is_msvc_eti_arg<Sequence>::value >
        ::template result_<Sequence>
{
};

#else

namespace aux {

template< bool has_tag_, bool has_begin_ >
struct sequence_tag_impl
{
    // agurt 24/nov/02: MSVC 6.5 gets confused in 'sequence_tag_impl<true>' 
    // specialization below, if we name it 'result_' here
    template< typename Sequence > struct result2_;
};

#   define AUX_CLASS_SEQUENCE_TAG_SPEC(has_tag, has_begin, result_type) \
template<> struct sequence_tag_impl<has_tag,has_begin> \
{ \
    template< typename Sequence > struct result2_ \
    { \
        typedef result_type type; \
    }; \
}; \
/**/

AUX_CLASS_SEQUENCE_TAG_SPEC(true, true, typename Sequence::tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(true, false, typename Sequence::tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(false, true, nested_begin_end_tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(false, false, non_sequence_tag)

#   undef AUX_CLASS_SEQUENCE_TAG_SPEC

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct sequence_tag
    : aux::sequence_tag_impl<
          ::boost::mpl::aux::has_tag<Sequence>::value
        , ::boost::mpl::aux::has_begin<Sequence>::value
        >::template result2_<Sequence>
{
};

#endif // BOOST_MSVC

BOOST_MPL_AUX_NA_SPEC(1, sequence_tag)

}}

#endif // BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED

/* sequence_tag.hpp
HjlmDSc4CcArFoDMp+1bm4EEYL8slfftp++Xzrkv1l9GO9a2dKAEyL7GviSdQTxcCm+PnWcpAMbQZ7Fg4LBjR8BKGCgSQFyii1HursetZJdT7nxGYouGxxHtm6zbYCv9NLhsM+v5lVXuTewwGij80VYuNMYqP5rKI6zTcah4CCHVIDYYIk7S4bsEEfmUm7CfBDjG+aFKC/hV6qJkOvrli5LpwJYvSh5EjrZm74u1ioNyj7NyV+YDgfypsN28vdYCmS8yAZLIxKpQEM3eK3Um3I2qasmXukooTN61ZdpEmbD09tFeR6c8YCWLG2IAf1hNg7Oyd8CBHNNutXIsUzkm044rWMoGrL2IlHl0vpplieSXoTnDarY7Ks80b6DZYe2qp9Ds0fKfWP0LbpJCWtqzeKBJhSDWu+XtKf2pAKM7qyZKRwOfJcizJ2Ek7mKuo1y5pmih4Qb6R/o/NMVvuM/Q0yv0a0wvHP2dia5yodvu+hme4Sd1XVBi1Vxurrv92/G4//f+rPtPqdlqyrmJA9vPnvwi2sXnWnVxiVHLm84HwlIUgwMk69+lJSLiIwz6mRqzLP5MbFs7xxEhYi/cCh5xigyAaT7xhWTkrdXHClpV33fhO9QwNDIYtVfvUuAzaQEh2JEnAGuM4dTDX61w3b2EKWCrxWB/8TgzWC8Y7LrLAe0Aj6/u37futPrXj/5tdXR46xim6Ulo4PAv9aJ2lKBydOqJX6qOQJgKKAwAuLj9HQ4jHHkudf8lgd8QjD/hpyMmtMUzdqk1lirp5zU3LjCqdWfPNeq4s28JsTZvLSWZXyzTSwHlvskS51Xus2Tu28Uq0Quz/fobLdYzT3xOR1AEvxAK/n6OlXa+U7ElGM5eZruR5ZvpyKaurJ+iNzDEXSBB7FYnJW6QFvYwQ4TaT30foUgOzrW8ejHQyG9lpJioXgHm3S/BPpoXItHgn+oGz1ENNhZzgx8SU+pt0ftviPZC5SXuZQ5kBo7Fvc1PLgUwdPN9Gs61Ck6BhHM2wVFM1yWcR91g0o1glHKLHKzYQhtrZcj4m53t0aFQejvY2Rms7sW/tevR/YWutlJV+1iQq92hvJ6/dGATiBH5I7aW6Kz3IY6qXR/BejJ+7M+VsO5UyswyXgbXLFSD3N94Whebp4odxsUiF4nlEDgsudoq8Hx8gc/ruMCxLCujjJKnp/xUmVlEi740HcQUla7UI6ylo+wxy1/oxrMxchB9J9fiGY0/j4j636KB/W5/+jz5k5/EngeZe8N27V2VufAsPrDF1T04t4NQcA5PgQ3zZEeSha7PXHaFkpZElhNg+yLutYaVe+FZ6P/okxyyucewRBtkYEkv/Ik1LuuD+2LWEHfe705ub45tU/T5/zLdP3FmzdNwen4MFCrdz4qy4sg3tgt5ZtEZ0H/MFvqPm+Psmw8P7Y99s7R/icHPlQC/y6fH4PcHG36VhF+oNs4+/ZbF+2+fHl4a749SAoz+fGYMRr+xYVRFGH21KM4lJbivLikp+M9o+oge/9sS4b+8Phr/QB+JPDxKCf8T4vAfPXc/8RejsvLmuPNfmGKVVuK7vizw3BTi6Yv2pt4/2p6+b4XSkMTr/2+N8d8he46X5+yX/w5BuLo8Ff8dMvZ4hGNvaGMP1aCU/E+s+nrP6cQfZxAdZ1zdlLp/DeW/pYv5vT9v6twfh5o896IU/XEo76ipnfjjDEo8H/CeHzs/nlqi7O+67v+Ugr+PL+a9IN7/Z2py/58lyh7FNoHRJ+Yb06Im8ADjAYsBGUGew1ULormin6T7aK7t78Is7sj+J9SBv8wU4Nd2dwyDuUAht5iR23Jj3JJyyrX7tqRofP66WNmXxfXXkKkx/ZU=
*/
/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_SIZE_08112006_1141)
#define BOOST_FUSION_SEGMENTED_SIZE_08112006_1141

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/mpl/begin.hpp>
#include <boost/fusion/mpl/end.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // calculates the size of any segmented data structure.
    template<typename Sequence>
    struct segmented_size;

    ///////////////////////////////////////////////////////////////////////////
    template<typename Sequence, bool IsSegmented = traits::is_segmented<Sequence>::value>
    struct segmented_size_impl
      : mpl::fold<
            typename remove_reference<
                typename add_const<
                    typename result_of::segments<Sequence>::type
                >::type
            >::type
          , mpl::size_t<0>
          , mpl::plus<mpl::_1, segmented_size<remove_reference<mpl::_2> > >
        >::type
    {};

    template<typename Sequence>
    struct segmented_size_impl<Sequence, false>
      : result_of::size<Sequence>::type
    {};

    template<typename Sequence>
    struct segmented_size
      : segmented_size_impl<Sequence>
    {};

}}}

#endif

/* segmented_size.hpp
gOvSrJTHCAaVMCYvJTPs6RDNFbF0kcaRavUq2NZvo5x7NAKzqn4KFAXkFkSPLun6vhZLLz7ZXdS3Ual7folNzCTBL8LsrrRKxXHtXWz4XwDMJRTPTsFNTx0lMcGVv1oLA7SJY2F/fcZLtEs1bkJRU+kuXJDV0X31HenNdCE+KBGpPb4bqq87YbIxGAF33brvnUuN+H9YAvlQAPN4Z6fiWd+zEK0kgdSXH2DVoXsRNpX/I4mrOOz3cbKZah9aJQTbHeRsBEhv4AUUrGe+qcdPk7ddT/STvV4piXCRqGOWqwQr+hPErZFamRXYtuKZGGzqweSSCdoRHzJtHoq3lAMqhyZEpVv3pDevuuGTJA2FnSXF5ShqGuNRuymB+xekTnAY2bzK1SFb9nXjOKRYbss/cxPM1GdPqPlEo8cgkmgXun5fJPxGdZanDpnPo7JMkaOjibSJFSmUr3RLCWC/I25bxc1sFbQr9W1aaTp7HWuz1DDt1uCagMlEBH7nKqp+jtjW22spAcM+DRgJVvHv0+aPef2+DGpGhoCaRIAoDutJab9JpK6OVdt/r5wleQ==
*/
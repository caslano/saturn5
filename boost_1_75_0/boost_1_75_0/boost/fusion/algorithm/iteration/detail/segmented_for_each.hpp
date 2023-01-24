/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/algorithm/iteration/for_each_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_for_each_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_for_each_fun(Fun& f)
          : fun(f)
        {}

        Fun& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef void_ type;
            typedef mpl::true_ continue_type;

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&, Context const&, segmented_for_each_fun const& fun)
            {
                fusion::for_each(seq, fun.fun);
                return void_();
            }
        };
    };

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each(Sequence& seq, F& f, mpl::true_) // segmented implementation
    {
        fusion::segmented_fold_until(seq, void_(), segmented_for_each_fun<F>(f));
    }
}}}

#endif

/* segmented_for_each.hpp
XpyTtToN6Atb1Y1oz4UxDfc1BwXPXZUbTfOSCX/QhYCbxP1oDuW3Z+ZAOKtkl3ioK15JgruTDiQbnypqIK/woqe9Ddz4MKS5k93gpf87PFrESeNPHvVhisB4JbEwMcfoek1zgn5BLAUwyKTOLXwtSTMDgyHCHV0ZBIAiVRfLzDNIvdGTS3dfFLsHfXtmZ11uq3yBjyz7nxY9kM0V0UTYbrTQXkpHdwHY/L/iodgfYrg55zUH2XHA0OJsX6Y84HCS3UM+cSs7vXFqb1EqEBXchraI2VmXlV7EdTUG7eNFXYH3QQDqgIALHgx9LD7Okx8fOFd8HOMKbqsxjF/0SRQuA5XNHIhYWJqWCXeSd2UPOWirAD+WLqUR1C5hNgJJQ9ypU0/r7051K854HNtdgi4INImfDrc/SeDngUkmjWoqUhv26CsFcY4EIT2Tbyrsu2P0GRrIcY5eFGmBaTCEadi7LSaOcyTK14t3EBjIIEf78fsGsp+ASg6ZDZGO1J93gfGyKE8xjpAFyo1uBB8/W3Yl0+xfhFWIBQEH93cRXoI9vMsUIuQZRkIeEkJsVmd+jQBc+TbgI9h/uKvVtAFJRtf5X0eT2fDDDoYYI0HXiuVwC8gT35/dR36vRWOag1VrMRUni5/5YqPB3i3Ngvtf6NBdeAkMVAxiKbqsCHTXVz4zGu2fQVzZ1OEksd+FaP8G1QeSBb7LVu6CI2MiWTPT
*/
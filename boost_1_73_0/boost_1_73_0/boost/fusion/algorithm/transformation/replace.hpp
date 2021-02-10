/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0830)
#define FUSION_REPLACE_08182005_0830

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct replace
        {
            typedef transform_view<Sequence, detail::replacer<T> > type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace<Sequence const, T>::type
        >::type
    replace(Sequence const& seq, T const& old_value, T const& new_value)
    {
        typedef typename result_of::replace<Sequence const, T>::type result;
        detail::replacer<T> f(old_value, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace.hpp
koORc7RkieObm3kkFZXVaoNFUN/oOAWrPV9YacG3kt0AuGdsiGMaquyPTNNeDpIjPvuTVrM4UQ6HXdPwIe5l/b8xGQmiUYFxSPzDWVMPvJakzaYbOoJQDMqCZCMLHPDL0b6quVe6PWY8qvKQdgTSthfbG19dBSTuBEx07ombI2I+jTVBQKjOoxc+htd0AqUQhFGCNweDbxP/m39OB22k3YUmlyPl18Kf7utP91Uuj/375ADlAqYbybvoWfX9wAmFS/aWwGCSx8W0mDL8oz82kmjj6KhbNb/NkgEyxfzB2Y8zMywCvxp88v2BuB59bnZNR2dISt79/4wj9Tkh+AMhVbKFY/EzfUqzpaTGA81E5JkKV7uxcsVLuQhXK8UYOHgFV+tmt5tjCVyt+K7P3f2mnaTfXC/perev+if8ZSpYMO1+12q1nmLD9JxbLRcrxjUgAcXwLlZ7KKvoJDMD1VU1t5XGTeKf13L5IhpuZhjkHJBma8wwAKSz9VfPZJ1obafT6funV43gWwayqkWzFU7CgdMKaNI6C6fRLMyMnNszg6qGjRG+5M7o6cti23F35GhLTx1tjYvFVksBq8oWazFpDf3m2NfSHSoDjrZYGP0ZNdcYJfiEVBCSad7ckrNolfyWmY71tSWv7tCbwxH9
*/
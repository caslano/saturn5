///////////////////////////////////////////////////////////////////////////////
/// \file end.hpp
/// Proto callables for boost::end()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012

#include <boost/range/end.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::end()
    struct end
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::end(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::end(rng);
        }
    };

}}}

#endif

/* end.hpp
JQqWJFiyYOsFSxFsi2CpgqUJli7YfsEyBMsULEuwbMFyBMsVLE+wfMEKBCsUrEiwYsFKBCsVrEywcsEqBKsUzGjC+81YMFPBzAWzEMxGMHvBHAVzEcxNMA/BPAXzEsxbMB/BfAXzE8xfsADBAgULEixYsBDBQgULEyxcsAjBIgWbIViUYNGCxQgWK1icYPGCJQiWKFiSYMmCrRcsRbAtgqUKliZYumD7BcsQLFOwLMGyBcsRLFewPMHyBSsQrFCwIsGKBSsRrFSwMsHKBasQrFIwo4nvN2PBTAUzF8xCMBvB7AVzFMxFMDfBPATzFMxLMG/BfATzFcxPMH/BAgQLFCxIsGDBQgQLFSxMsHDBIgSLFGyGYFGCRQsWI1isYHGCxQuWIFiiYEmCJQu2XrAUwbYIlipYmmDpgu0XLEOwTMGyBMsWLEewXMHyBMsXrECwQsGKBCsWrESwUsHKBCsXrEKwSsGMIt5vxoKZCmYumIVgNoLZC+YomItgboJ5COb5b+LuByq2KYrj+HhSIyMjSTIyEkIIIVYIoUUIIYT8DyGEEEIIIYQQQgghhBBCCCGEJIQQQgix8ucnM7dr2F//ea3xnvexz9l7n3PunWYqYJlgWWDZYDlguWB5YPlgBWCFYEVgxWAlYKVg+4KVgZWDVYBVglWBVYPVgNWC1YHVgzWANYI1gTWDtYC1grWBtYN1gHWCdYF1g/WA9YL1gfWDDYANgg2BjYCNgo2BjYNNgE2CTYFNg82AeQ60LQrMC+YD84MlgCWBBcCCYGlg6WAZYJlgWWDZYDlguWB5YPlgBWCFYEVgxWAlYKVg+4KVgZWDVYBVglWBVYPVgNWC1YHVgzWANYI1gTWDtYC1grWBtYN1gHWCdYF1g/WA9YL1gfWDDYANgg2BjYCNgo2BjYNNgE2CTYFNg82AeQ6yLQrMC+YD84MlgCWBBcCCYGlg6WAZYJlgWWDZYDlguWB5YPlgBWCFYEVgxWAlYKVg+4KVgZWDVYBVglWBVYPVgNWC1YHVgzWANYI1gTWDtYC1grWBtYN1gHWCdYF1g/WA9YL1gfWDDYANgg2BjYCNgo2BjYNNgE2CTYFNg82AeQ62LQrMC+YD84MlgCWBBcCCYGlg6WAZYJlgWWDZYDlguWB5YPlgBWCFYEVgxWAlYKVg+4KVgZWDVYBVglWBVYPVgNWC1YHVgzWANYI1gTWDtYC1grWBtYN1gHWCdYF1g/WA9YL1gfWDDYANgg2BjYCNgo2BjYNNgE2CTYFNg82AecptiwLzgvnA/GAJYElgAbAgWBpYOlgGWCZYFlg2WA5YLlgeWD5YAVghWBFYMVgJWCnYvmBlYOVgFWCVYFVg1WA1YLVgdWD1YA1gjWBNYM1gLWCtYG1g7WAdYJ1gXWDdYD1gvWB9YP1gA2CDYENgI2CjYGNg42ATYJNgU2DTYDNgnkNsiwLzgvnA/GAJYElgAbAgWBpYOlgGWCZYFlg2WA5YLlgeWD5YAVghWBFYMVgJWCnYvmBlYOVgFWCVYFVg1WA1YLVgdWD1YA1gjWBNYM1gLWCtYG1g7WAdYJ1gXWDdYD1gvWB9YP1gA2CDYENgI2CjYGNg42ATYJNgU2DTYDNgnkNtiwLzgvnA/GAJYElgAbAgWBpYOlgGWCZYFlg2WA5YLlgeWD5YAVghWBFYMVgJWCnYvmBlYOVgFWCVYFVg1WA1YLVgdWD1YA1gjWBNYM1gLWCtYG1g7WAdYJ1gXWDdYD1gvWB9YP1gA2CDYENgI2CjYGNg42ATYJNgU2DTYDNgnsNsiwLzgvnA/JbpkRC2yP8/uuKSXHHrRowZAAuCpYGlg2WAZYJlgWWD5YDlguWB5YM=
*/
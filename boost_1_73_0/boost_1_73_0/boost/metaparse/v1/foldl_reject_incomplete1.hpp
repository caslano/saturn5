#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl_reject_incomplete1
      {
        typedef foldl_reject_incomplete1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl_reject_incomplete<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete1.hpp
U3E1XZRRElKrAqSVMQKPLWpnBloCY+zhLV0Jb1Y6ngTTKY9i2YVY/ZvilUNk1AKhrnkYjGsW21yp3efxXH2V+W4my+OpUmp/eDtgls2CzHG2usUITzYu15Qp/w95295xDDQ1jKNn4Zp7NK2QR+kI54fHzgT8JXK4CR3LBvQ1YdHtQRTAY80N5biHIc1cCwm0tqc5f44pW2z/IrR62qjX//4DUEsDBAoAAAAIAC1nSlLqXJAxMQEAACQCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI0M1VUBQABtkgkYI1STU/DMAy9+1dYm3YsEYNTFXpBQnDaGBWcQ+PSam1cGndj/56kpZvgxCVW4uf3YUULeSmMpwx07UoOZU+nI/fWZ5A/5NvxwLfdM2h16Wg1gWEJS7xvanKS+NoS6GK8BISn/kB9BlJKF/DzFbUzLU3c6MlZPNZS8SA4vnAnNTuPPX0OwZkPeDUNoC64bY2zGSQ5NvyhovXr9e3NlXwJRplUqdXj5iV/2qaryLbd7HKlMEliM3Gc/LAHO2cuXdYNYZS4W/wlXWRgsKgGt0cuwRoxEBwLoDBOeQJTnI8LmYOPK3mlvi5P2HkaLGPXs3DBDZpSqEepCKMMVsbjO5HDha9YFqAP
*/
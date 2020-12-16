#ifndef BOOST_METAPARSE_V1_TRANSFORM_ERROR_MESSAGE_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_ERROR_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_message.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class F>
      struct transform_error_message
      {
        template <class R>
        struct rejection :
          reject<
            typename F::template apply<typename get_message<R>::type>::type,
            get_position<R>
          >
        {};

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            rejection<typename P::template apply<S, Pos> >,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef transform_error_message type;
      };
    }
  }
}

#endif


/* transform_error_message.hpp
29es9JV7ZinZRPIZpumEv8tuofpxi6NG/5ti2gJ6fBaJVn6TgwSczLi6H+vHWBOe564J441Ue7zZrgFPIn69U4wFEextcMvyyWx7BwVlN1648G3m3l5gvx/LuIgvDfXL25Ym2hqPD9BxROH92a4Reysh+yrvErbAEsib3BOfDv/md8z20wZz+qClvp3efDJ7z1YX+GF0Qz9uPMdRt/Dj9uO4atIFkNkg7owc3AQbl+yidrEyuT9kcnnU4xMpSXLLcVRQjuN8mcyTSBW29YijjoX0S3jf1glslx0/Ok6qaxhOTtA4Gy1O7MeK72p8B75NVlhZYb5bv4pRWRc/blVUlsWPWx0V+gxwa2wc8R33YSbQQLU2OpZzQEu888bhjk3U7fN1Nj9dUEkOdmQHWObpXZ3B7iSHJ1Ef7enoIhDn3OHQID0SRoTUOSy7TWU7edDHpyMOfRzn4ty3siptGHdBQJf6eyrZ69uRywjPPNJ6vTs5fYnXkSvjcuJ8UIaVXkcilaH3y/qHMlVCN6zx8VmVERXxLSI+hvh6oteO+D7qmtYNJep5DtHb4PXR+TKbxdJtiNr9KEiMdUZm45so/rRcvP8WTTn1mWahS7qNTjAqlQc9hHnMaZG+Uytcey5C4U9XunZGG2yp9uhI2IsU7HrAnhgC++6pLuxGwG7Kyf44Gg+Fn9gQHKcoW/NU4Ei4dp71QzxUYuB1fWj1Enk6kQe+Gth3Hb+BRWU2P0sbOODFETiSki7KeCbB//EQ83PpbkaeLcgTqtPHMBbY+5NReU6Ty63LuzXqr+v0gnYf8sGGRZ3lX13X/b0B5E2LdjpdtNOgwwPGk4lqXCVeFriGkGehs79OGsDxu8dj9Al2Xsl70a0UnqT2otdF/TPMafTrDRQuJ12QTbCNcZLRITbO2BQd2WB+epq1H2z8UGdvyu+foFsJ/31BXBfFzbbvVA5lk8JW6bF6hc4+Q++kKLzAhhOEmAqA/P2GL4hPwX7ZRnFxYx+lenYGcMMUV4c4C0nxgV/e7aLPH1PEOYtVXqj+hn2yQejtjUJnb/JYV28y+nCgX7yfvFOUpXxUm9fOdcj2c+c674ZcnBkV57dV2llSHwCH1j9nA/Z9bv8gWPQN/KiPOuue5yDfuSof4Sce8E/n+yDyfUiM35dUinICB/LxniXyfRT5Ar7UqXntxwH3CckXlXaB5AtwaD15IWAviuqyEbyC/TRgd7m6ArCaj66uuDgKHoTkpTI5vNR5L0Pey1UbaLq6DT6HfFeofJqmzvd55LuqAD0Dq/NdjXzXhNeR7BSMHyLvEOr4JeS9NpQm+9HQNK9Hvi/nyXcKfjrfV5Dvq0pHcz6dp8S7EXluctcNkUfD7+d9A/A3h8iWlsNbAHurxg1YjftbgL/NLT/gw8t/O/J8R/TJupD8hs93huS/C/m/K/ITHfbh7cqIxfM9+n5ljsY10fs+cP0gRHdpnfBDwN4bqoPyy/+Pke8nso4qn67jz5DnPt0OyKPb4ReAv1/Bk20FWYecA/5XgP+1go9UhPto/i3gHwC81IG7Kv20B5G2p0Ts26tzYCWws63RjHH0PZSv1F9nsJ55gvj3GhsC8bAkcvFliDeHqAaRGuR7P6WXI91aG4j/gLEtEG8sCTurCe6zU1oF0jartI8YfSHSupObaQ/Cy6XNRpqdSQm/fh+jtHlIsyvnie5UpmswRZOVjuC+yvnWBrEDsFP3T1obxMZz3REfR3xY3T9lbBKky7p/xszZEW/qnh0gciZrdqdtm0spfYlIX5UeHDid/Gumhs1shmpGZc7S9fbjV/h22mcJfjngN48B/kqCXynwd/QQcQkKnn2B4NYw3rxwXyS4FsY=
*/
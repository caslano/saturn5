#ifndef BOOST_METAPARSE_V1_IMPL_FWD_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_FWD_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl;
      }
    }
  }
}

#endif


/* iterate_impl.hpp
cD6FrfX63IZEMIFICF9ar60dmegA7fMk2WGj08hwDo5ZTZ5AQjicFhpHRqRcDQfC24QsqlhEQE5bl3oDLCDXgIA5Uz6gVaokSIzQ/2tcGDtR2q51ozwaD2CV5fX90xtT8eVElKx4FIqbyAwYxJIiCP6iGlWGqVdVR2X1aQQDRRlXE8NcIUhHm1DkRpVNmu5bD0fVtJhuD7xbW4uEZ4j62DG4Fnc1U9e51DoTl2xl9haRN9KmMkMGomC3Ha2fAtkdehJ/HGO9oQwvYrRNqR9fD3G0tMCvV43UruQnLeH4umc/ncN/F6egPIFQi8ompG0v515WOf7HyzY4Xn5B79Nznl2pGaEGU/CIj299d8uLYcZv1HIJVukY74WcP7WWxuDXV6e0K0aXKnP3Z87t4eJ2RtNfui0flQLwqN6qrBwb+IFp8xiupPOFPNqHsHTQon1cA+Ajc6IpN2nfPvfrp7VyzfKT8TYqjV5PzGfE2dVd62ajFitPkMLvDlGWu6MrFbCxvdY+Aky/6AcRxTDxq9wDepXcs+WWDt9cCsVlSwtUD5Ok/llJrRCg5wG85a00ZX/sdj4zHSXMcKVRw7ASkyM0jKvbKYXAU8yXUb6DLq8doiNOUP8u2OVDDMb/5KkyKBLq7ylIYtXmwJHf7XWOE386I1xfDKwfZCp21U8c0KNNXS+uP7waaE5Ti3Mq8ZVpcdlZ3I8xv/intP8qcMdi
*/
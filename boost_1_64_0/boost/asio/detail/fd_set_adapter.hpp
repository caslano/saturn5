//
// detail/fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/posix_fd_set_adapter.hpp>
#include <boost/asio/detail/win_fd_set_adapter.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
typedef win_fd_set_adapter fd_set_adapter;
#else
typedef posix_fd_set_adapter fd_set_adapter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

/* fd_set_adapter.hpp
yYR4gtVoZIgtDEBJMmSwGsHRaswo5gVhM3KfJ7QaAZKtyCvtVZ3VCJxbjZGy20Wr0VjrfWk1NiH9WW/nrMYGpldnNYKiRRgxYyGnMTWtRkCxGnHRMBMzmLI+txpB0WoEoNWYMbg1EZ5SDlB5ZzU6QtTOrcZIUU0ODDKrkRwrUW0FOpApBsYrxkJ0ViMJHZ3RajTg4rE4FoZMLxbAOQ63yjnFY4y+Gu0NGHVdflnnq2h5Ra5vhk8Vbawqt7GqohU1yWytY4NhCM6N1AKx22LjdUcuTcApTfhlmiqATEtQXksQBS2PBZtrBc4pEYjdAjNbmNG5znWuc53rXOc617nOda5znetc5zrXuc51rnOd61znOte5znWuc53rXOc617nOda5znetc5zrXuc51rnOd61znOte5znWuc53rXOc617nOda5znetc5zrXuc51rnOd61znOte5znWuc53rXOc617nOda5znetc5zrXuc51rnOd+3+563dd5fTF8Xuj/t6qv7fr7136e5/+PqS/j+nvU/r7nP6+pL+vyW/ZrcnL+05dI/k79zT5vfSNVeX3U/k9/DP53fRz+V31C/n9TX8vPX01/CLKM1aX+/WFn39Tfg9cOfGt7s7FFlshXQxE3zcUr6T4TcVrKR4o3kbxoYr3Uvyx4nnFI8WXKj5C8TWKj1T8mOJFit9V/JnivxQfpXjVoeCjTT/F9yjeWPErindWPK/4eMV3Kz5X8V2Kb1S8oPg5xZXiHxVPFC99qODjFK+p+HjFmyo+QfHhik80fRSfZPml+F7Ftyu+T/Frik9W/K3i+y2/FD9g5XmY4AdNP8UPmX6Kv7fyVPyw6af4FCs/xY+YfooftfxSfKriTxXfYfop/sr0OVzwaVZ+ih+z8lP8teWf4set/BSfbvoo/tLyS/EZin9TfKblz0jwW6aP4idMH8VPmj6KPzV9FP9g+ig+y/RR/Lnlj+KzrfwUn6N46SMEf2H6KH5K8dqK37byU/yO4gMVv2vlp/g8Kz/F55t+ip+2/FJ8gZWf4gut/BS/bPl3pOCLrD0qfsb0U3yx1S/F71l/ofgSyz/F75t+ij8w/RR/aO1R8aXWny0S/Kzln+LLTB/Fl5s+iq+w/FJ8peWX4uesv1J8lZWf4o+sfil+3fLnKMFXW/kpvsb6U8XXWvkpft76I8XfWP1RfJ31l4q/NX0UX2/6KH7R9Dla8A1WXoo/sfxRfKPVb8U3KT5d8c1WPopvMf0Uv2r6KH5B8dJjfd5af674Nru/4pfs/oq/s/srfs3KR/HtVj6Co9t0ScnffSFPF4KPNzwv+FLDiy0n6avly0n8hlcS/Knh0yX8j4ZvFLzYfoqfE7yS4XcFr234PsGbGj59Oamfhr8V+eGGL11R9Df8m8jPre+3vORPHV7TU8e/gqTH8JqaHsOLrSj1p5YvlfDS+1v6V1wh0YY3FfnGhncWvI3hb5eX9Bj+bTlp/4ZPX0rK1/Clgq8xvJiEv6++v+DXDB8o+FvDawv+y/BzK0j+H2DlubzUf8M7C97U8I1Lib6G7xM8b/jAFSS/Db+7vLTXGq8g+hpebGlpH4bXXk7ab41XFP3r+AUv1jd9lpP8NrzS0pLfhjddUfQ1vObSom8tF3yp4Z2XFv0Mry34NcOXriD12fCBS0t+Gp5fWvQ50PRbQfLP8KVLiz6GVxL54YbXFHy84cVWEP0Mb7qc5KfhnVcUfQ2/u5zoW8en5V+H1/Kv5StK+R9k8S0p+ht+TvPT8NrLSP01fKDgAw3/trzob/jGZUR/w/cJvt3wt9re6vhXEP0Nr7Ss6F/rt5zoX/sX+dIHW/qWFf0N7yx4bcMHCt7G8LeC96o=
*/
//
// impl/system_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP
#define BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline system_context::executor_type
system_context::get_executor() BOOST_ASIO_NOEXCEPT
{
  return system_executor();
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

/* system_context.hpp
ObKf30eQLOIdRh9PuCzkJG7r4E7kNO7HOM5Bfgf1xFbCnuB3OL8DB0MlV3G8632NQXAO0he/BNzX8XsrMoPfe+AY3LOQYuwogeuQcmQF/kdVWFjRE3KMIAauDvH7IG4nkb7o45EspFT5ISeQ+CHkDTmp0oVt87GFD1dX8zsSjkDfr2xGktDDnsNOpIjfOwmzT8XH9p2EuwG3JOWHHEY/jRzDfwfufgnkv8DHiEL2oO9HonCrhAkFhIWpMLQXx8Q9Es6BJbithknoO+AcWICU416BfgQpR9+PnC5Ah6WUT1AhaSBn0BMUCZcK2w5FYojD71xV5uhJyCH0ncSrQKr4HUWYItzDGPiLQQahz0DKiLMXScItC/2Iqgu4Dn014cuRreiHYQUMG8ZvmACPE/bQQoj4baf8lf8i8oTfCmQT5RaDvpXf+5FQFQaeIVwMvzPw20eYwFjC8ztwOHFgJfZE4lbB7yQ4BylGViM7keMqHowi/AlVN/weQ3rHYAJuc5CT/PbrzTGRYvQIGFVEHpEzpL8CDsJtHX47kJ3oyejHYCppFfB7P+5t+UDvNG4n+B25mDaHHjQCe/HvC5ORAuQMdqTit0npxN8Lywizmt/lcB9yFLeTSNBI4pHWYdwi+Z2IGH2oP7gOWUE6u2AobsWEi4CDkLLtxMH9BJKq/JDVyE5kP+EqYOgo8sDvXYQNu5p4SBRuSXAMPESYSuQk0qAvx7+Q9o1fFn6rkXIk4nnObxiG/wk4CI5HshBjNHYQvpTfFbAt+nEYDwOXEBdJ5XcJMmYJYWEW3Ev4I8hxZBdu5bid5vd+eBT9BAwqxo3fMXCXKud+9CVIDDKmmLC4JfA7XvV/2JiL20nyGTqGcuN3Kn65SBn9U+AOzkvcBuF3FM6ABUgJ/oHXEF7ppFEO74SluI/AfS+/jyAGi3ZEIOORAmQrcgRRHzjFIKnIamQXUokE/olzD8lCypCDyBkk4kXOLaQE2YVUIoH7CItkIZuQfUgVEvqSrxGPZCClyB6kEgl6mfBILnInsh85ibTlZdAIpAApQ/YjJ5G2+3FHspA7kb3IEcTvVexBEpBUpATZhOxCDiMnkaAD2IAkIrlIKVKOHEKqkCBeNEUhI5A5SAlShlQgxxG/g75GOJKApCLFyCZkL1KJ+L2OfUg8koTkIquRHcg+pBI5g4S9wbULSURykVKkHDmInECC3sQfSUaKka3IPuQ40uAQNiKJSAFSiuxEDh7CH/F7i3JAEpAZSBGyCdmHHEFOI6FvU89I3V/dX91f3V/dX91f3V/dX91f3V/dX91f3V/dX93f7/fnp3fHtwXrNa8GzsjJZdf7nMK82enmz/ysnrMKM7Pm9IyNjo2OmdtzYX7vmNg4y6+of9+e+RlpeelzeuaxY1lafro9xOy8xbkFOTPU2vj6n5SFfaJzZl3JGrqDgo1UNZ7RjO/jn0kzLE7InJ2Xk58ztyA88pJu4ZPU8vSZV2dmzwsfnrMgNzMrPY/vN8YHf9SDbxZkXX41H1QTaYcsQRrGMyazSq/LrzfCGZmcxFaPF0+ayEYU6WlsqTZrccrEi839+uvH6/0lipz2ZpG44da+1alaT3daaz87c46Eb2bYw/d08p+dl1mAv6zFn6H9Z2k9w0o/UodPCNZr96cVpBnWPtiztf8YrU+2wncSf5vxjNZDdfypIXrF0HQOZ8V/SPsHeQzfWJeaqgXHPim52j/RsK83/7cgvjlFPqacvwky15uPsVqL570XEmB9ve+MLstqe4lQXuKWaLnpMtJuyeiUA266HPQ68/b6rZK1RH5EOslYY0A8/9xQc/1OGjbWW/1K3F5WefXS+rM6fCtdH47yGWeFj7I=
*/
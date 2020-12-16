//
// Copyright (c) 2015-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FILE_HPP
#define BOOST_BEAST_CORE_FILE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/file_base.hpp>
#include <boost/beast/core/file_posix.hpp>
#include <boost/beast/core/file_stdio.hpp>
#include <boost/beast/core/file_win32.hpp>

namespace boost {
namespace beast {

/** An implementation of File.

    This alias is set to the best available implementation
    of <em>File</em> given the platform and build settings.
*/
#if BOOST_BEAST_DOXYGEN
struct file : file_stdio
{
};
#else
#if BOOST_BEAST_USE_WIN32_FILE
using file = file_win32;
#elif BOOST_BEAST_USE_POSIX_FILE
using file = file_posix;
#else
using file = file_stdio;
#endif
#endif

} // beast
} // boost

#endif

/* file.hpp
/xbvsIkJXwh6F8+ZY571j8asq6xAQfksRFhVU7Mqh8WfrcqRMsF0F8Dt0OW2sdKqey2O03RrcXrhX67ILutfm5MXed2rSIuXgHKxzXDVCf988H8i/OdDtnBeQU+UFXlZj9IHp6BfhQXbo+xD8a8AG3nR24Ic8XYjcDlHyr0cJ1XOM4Wn10mXc5zwhXWpnAvA31vCF8s4EoFJe0u0axwxi7XQblcvKj7jCPO5ROKHq/lokbiTOxxHlglPKMczK048aiNUxpaT2bPVIGME6tuSYzWWoD7pl6C/r3q9s7TRTv5iJl5KWW6b4CvLDRsDtjH5FwdqT4bnqXo6OIHvcx20JdP0K5/XS1ixtNsR3C871t1uo7vQbj+32k3lp/P3y7e82u2gV7t1dT/Wl22zFp4BkMzE+4Imyh/vNqtHAQLOZcif3OH7Fnn0dyv1jhAsYQld3oemP+O4v5Bl5H297K2mx/mW80O0c7arnGYBEWsUxvCAZSRvcsA2HSnhiR2UISVgGfQ5Znm82+ZtFJ/NG4bC35VXLgyaWRbT6mWIr+2VhZ92VguKyHjJ7G9891PtYoX3VnsRm8Tdi21Jftap1V4NE7UzK1Qa0Z3axfXURWBerTUSJc+4H3nzVLvqeRgfs4n71CZnue0K5gWdvv19fxf/z9/6fsRNmy9pm/XmpxW1SwcdgU0w2bd4dHvKLVnP1X9+yce7nrh014AHwW8z/RsOrt36ybEhL73+zWnJw98d90wgu4Inv0+wSPYb3nf73dMvCwn+x9TKsffXvzO2ItA+ysD7JbfKfsmPtk+KWb1jz5W3/3zKkq257y8XW3HwPzZ1bvL6jKu2fzdh4lU9jvzjD5gfy31nFlYmvVt6fHiPhuQjF48+8UzgfZrbskz/pO9t2v55Wul3rmiZvXfrUw+/Eni/ZK7wv3bh6y998cnVxzdeOaDPo9uXhgXev/mF8C9/6sJd0W8475196fvn1p0ovR3vYcGm/x0lz4dEbf3bQ6n73kjN+NbsSYHsIga0A6nvx5RnwBHUy5uGa76Sgt8lhqwxye+53I/ZYHD9mGvlKV52fM6iva08YCZwGvfbTQfOAM7gfrqZwNXAs2l3MB94Jd03AKcAd9Bt3hdxuL6KtV/eNxK4jPftx31xA2m3LZX74zJoRyiN9nvSgQuAg2g/aDD3yw0BNpHfKucB3u8yP+UcBr544JnAJGA2y50LHAIcyfvlcF/haNoPGwOsA44FNgDHAy+SeLRrZq07ca0rxcuu2bO870ss5w9px+yXwDF0T6D9xmLgq8BG2nFsJt/FwNeBZrle4z7QQ9y3+FPad3wD+Izw046UjWs1XOtJAaWLnTD84X5TE+tpv66B7X8N7eU1ArPpHsH9pWPoHgvcAJxI91ncbzqV7mncb5pP99nATcBCuudyH2ox3QtpR2oJ3UuBlwLLtf2dW4Ar6V4F3Aqso3st94020t3E/aMtdG8Ebgdupvti4FXALXRfzv2k20w36++EYa1nIK+sv2SxT+e6bgRfb+C3gPF096V7BPePlgB3sh3vAG6gfc9W2lncCdxFe4h3A/cA7+U+3d20+/cQ2/Vh2u9sB75G+4hvM513uL/0d9xf+gHwSeAXvJ+5X3UvsD/wEdr5exQ4FXgfcAXwAeD5wD0sf5HB91ngMMq1vo87FnzBQCcwGdgHOAiYCBwCTAJm0J1Jt2Vv7xjT3cR0dXt7FZTLFcBQYCUwjvunU4DV3Me7UtkL4/yZc/sUL3thC5leCdNbBEwElgJTaYfxDNpfHEX7i6OB53K8Wa7ssnGOyHlaipddtgLeZy4wATiP8jBfK3e2Fv+IV7kPM/6bwCDaa40C/gLYB/gW03s=
*/
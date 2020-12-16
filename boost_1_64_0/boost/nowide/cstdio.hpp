//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDIO_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDIO_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <cstdio>

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::fopen;
    using std::freopen;
    using std::remove;
    using std::rename;
#else

    ///
    /// \brief Same as freopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* freopen(const char* file_name, const char* mode, FILE* stream);
    ///
    /// \brief Same as fopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* fopen(const char* file_name, const char* mode);
    ///
    /// \brief Same as rename but old_name and new_name are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL int rename(const char* old_name, const char* new_name);
    ///
    /// \brief Same as rename but name is UTF-8 string
    ///
    BOOST_NOWIDE_DECL int remove(const char* name);
#endif
    namespace detail {
        BOOST_NOWIDE_DECL FILE* wfopen(const wchar_t* filename, const wchar_t* mode);
    }
} // namespace nowide
} // namespace boost

#endif

/* cstdio.hpp
kZGIweYQfVm61scvD0B72h2iLbMlloj7SEcWyGz8kRVlMF4cDuHtJS3PjzlgiX4OMVOzGmnHv8hi/5G/FTjEFCFt3rq2W9CeZBmZnRz5bhHKy+4QJ5j1bf73TZh/+ulcZBfM0n71nSjP63I5RAeTtCbj5O94njwOcUZIW+W7ZBEswCGqMbuUIRV1iSfzZ9ZskrkG2oUsOytv8l8h9+R6VhiDZMoa7GQWmH7segzSRZNlhenHbpyBJRhYElktzUKU31ND8jpEE82qp53bxPwBiyfrw8xdMWcI0tHrqAEmaRNefK2KdPkdIpKlm7I9vgPapQC1p1nanW0PUjCWCjlwH6xa2n2GrqM3Y54v7BBrmT2tVKMh2pMWGLzJLFOVBufQnkUdoiuzg3MGynm3mAPPSFRN66OFvfLiWEVmZTbJ55kf+p2bsu5rCDflvcEwMn9my/2T5PcieTplDdpoxdptuZ8N7UJmgSlrhvN0yru58dzUtZV5nup5CNlWZvnzVRuGPIvr2/Na3EMX0ilW//vd+9Hv3JT3/1wlHCI3M3eXzGizEDKeLkMBf3l/ULH8W7csQHuSlWf2T6ENaOtEJV1qseYDUU+yCsyO/XdhC9SlpEPUYRbqtVFed5A5mb08cjECbU3WkNmWLBe2YQyWcoj6zMrdPj8bMZDlYyburk9CP5BVZxZX/TPKE6Ud4i0fE9m350IMbodYw+xq6Mga6IfvHaIZs9sb6pxFXcgqMXse++srtCdZDpjy/SMyC0z5BlcZms9gyrchDCyEbLdmVWjDifF35b2gYAet4ynt/M0GTRBfOYdYytKtuT12GuZPxQq+G4P44ss7xERm59eXQHyeCnqbnWtfSZRX0SGmMZuWIw9iTyBrzWxbc4s85lRyiBvM2r4OHov5pbJD9DNJ21PP3gltVtUhyrF0je/Mfou5h+wesxoTJ8o10as58BxEZdpQq3GYF/qWzM8krUNSsyOoZwiOt2T64200WV1mF/+47Y22JqsE07975a5B56bMNnUehLaOI8vBrPy5a8PRnmRVmRWYcVN+46GmQ0QwCytyUN4fJNvO7MWus9MRQy2HGMHsQpmg1mjr2g7xO7N+Bf8ohPLqOEQeZp0uugdj7JLxdOaMa6si9rrpp/OQleJt7XO5IWIgm8SszYcTJoyXenQMZ9b59vyxiI8sJ7OEFS12IU+yfMzi9z0chzFB9g+vy3DLJ/mbRvoxBNWXx6NKyprobsWqtvwqr6u4KevChZGlMHv66v5UxNdAb/teiMbYpxs6RCKzt4uztcFYakTHB2Y7qn+Wv/sq1m+fGdeporHeFu0KrYfYyXw0q6hcd7jJLJpVUJ67CCGzw/TrSISROZn1PlwSfRvB81TXWSBryez+wMFP0X9kFZgNXncmAXVp4hCXTdI+TCwqnz0Pc4i5zI5GRHvBmmvHP83cRwbMRXlkjZi9iH4vEF8LmpeY/bxmZg7kSdaaWZsh1W+jH1o6xEBm17MsGIN0ZFlhyncmyXLA9MexRANLJvODKd/TaJV+eW4DCzOwCAOLMbB4A0skSy+GZDILTDmGt04/zyADCyHrqFl52pDzUm4v7H9k2Zi9rPu6HPY/sj+YOZb1ToG1oXkCpqzLQXaWWYb1d3PA2tJxjJlv7XbHUc92dB+F2Yieo16inootultLniu2p7kApqxbQZZefNFk45j9W/fCArTnfxwiE7OnTS77oTyyo8y8D7umwzpQ38KU+zZkWWHKfRsyj2blaEO1zrYe6PeOFANMH0MQmRWmf37JTVYNpm/raLLOzFyuTain6ETtCdOvSRJExtN9WTCvq1wjMv16JpBlgunbM6mTjOEH5bmnZDJ/Zks=
*/
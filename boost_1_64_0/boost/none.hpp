// Copyright (C) 2003, Fernando Luis Cacciola Carballal.
// Copyright (C) 2014, 2015 Andrzej Krzemienski.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
#ifndef BOOST_NONE_17SEP2003_HPP
#define BOOST_NONE_17SEP2003_HPP

#include "boost/config.hpp"
#include "boost/none_t.hpp"

// NOTE: Borland users have to include this header outside any precompiled headers
// (bcc<=5.64 cannot include instance data in a precompiled header)
//  -- * To be verified, now that there's no unnamed namespace

namespace boost {

#ifdef BOOST_OPTIONAL_USE_OLD_DEFINITION_OF_NONE

BOOST_INLINE_VARIABLE none_t const none = (static_cast<none_t>(0)) ;

#elif defined BOOST_OPTIONAL_USE_SINGLETON_DEFINITION_OF_NONE

namespace detail { namespace optional_detail {

  // the trick here is to make boost::none defined once as a global but in a header file
  template <typename T>
  struct none_instance
  {
    static const T instance;
  };

  template <typename T>
  const T none_instance<T>::instance = T(); // global, but because 'tis a template, no cpp file required

} } // namespace detail::optional_detail


namespace {
  // TU-local
  const none_t& none = detail::optional_detail::none_instance<none_t>::instance; 
}

#else

BOOST_INLINE_VARIABLE const none_t none ((none_t::init_tag()));

#endif // older definitions

} // namespace boost

#endif // header guard


/* none.hpp
yXCU+GBGyNuqDcrMYHhN79PSYsgL2QPHUAU93g2al7E6vbKUo0vaoFEZLoU5VRyns1Vtg2ZneESeGRTIQOz1pR5iz7fHfW+WeHZjfhDCAiF7DlUoWusJABt0H/eQ9Ao4AFjO7/2ZBPEsp2uYQjxnm203yYr+vRQlQZjGr7t2UJMhPCnqIgle8AbLKrrkDLtXCJ32szPOVmfGrJgd/1OnObRj6b99kvxRqXXk6kr/7UUWNd+p9N+/ddZ/X0rxx5Ed9F/D4o8ngz/2VlzB4orTe1pa790WV6xyClc8/W/tXPFV4+U0NqmrJh3IIlesHviZcsXk1jqVXWXFDZ0kGKF1s/2mtx0BTHdxXizKq+gDm6gdu2IQPe00uVLZ425LivrVSXctLFdvXHuBcgQ7/dUD/CuCL7fTT1TvdCBy4DGpV3nB9tSWKYl2c4a1p5qmiPi1bFlQYZUlWmfnJTXrZhP/7nVA3tZJ7sq7pUt3i5VuQ6buUCXNRjjICif0+xa77z1kl01Dtqh03xfTVIu/OTzjaSvjO8hoV6l/sUdtkM+WJuAd2ih1+1rm/Lr5UWuHPPcV6Sn9Ak62Htl/PCbjG/CWOPE8Xaj3wgkf3BrE7v3ArVrMsQtKrA3PhnSVSg6qnKcqYJOydjuzulldftMm8DRSB7n3G8n73w7rUrNdVfVcKsPah22yMh6TDBmwFUQqtRW6AbRtUr0mObebDR54S8wG5Sp6G8H5hkr5osIMkDIPDIlkhExzaUw9G54+6r6p6KELBQnue/eC2fH7vSdJzohF37DmzfVq3rz+5/Z5s8t4zDxgwgeaqB6+k0gF2al4ARSpFE12pFNkJCNFgMpTGGGDG5T7zZ94TFKlLN4tXXjI6tFgt9pXSUF0i4JoVAeIdjd/yQo0QJSjHrrWcViCMJ0E9dearzH/b/Yfj8V/t/T4EP6bcyKZYV8Vnmzvnzrx38T6o/HfR3Z+KP+1mZZUeo81ajnKZ+2nf2oftZ3G+IMH0OTZqskoskjUhQM+Y/6bvF9SbHAd9I1aT1LfSEnumugbaecqhrryZWJBGZ0eJvsZQ5nSsdbYfabFBL7J1KGuqGGH7cR9z7XCuTbz1E9JqPYVZzh+1sE/sJcZIySEJXZkeBN+MeKjF+KOKJhSFiMRKYNxKQrijb8A5LvC3WsRD90V6e60MguQ2Tll4BEpeUek5FopvNEWlh43c2A8YdLI7s7nsRvrcAGw4XoWxrYOH/TFB4RIvWXjjdCEuidTso5I8RyRknlEiuuIFCd6zhQ2x0SV+QKtQoAvEr+hhYYkjzu2RAQyoBIYhjLnqMEle8ZkMHUuDsrC2hfcpLMn8uNblcanKY1PXcHx8TS+f+3vWPP31BM/ZP5O6Mb5ayoT/sW/7zR/89cdbf7uePlD5+81PSz5KWbNX4fiui//rqPP6U/3c/52VfJT/e/U/J3R/180f8e0IyXjBOv6QFgKqHDLnZF+SE68IrYBllwITonR3C0QX8NBZysDwgebU2g5x894t43mcuNQQtaf7Ii1b6SQIjsBRIrBD0dt4YeoSlnhx3YK9P3xbERsI5sqsmJCxZnsiRwEFocDDOwX1QroEU9QZa6gzlAf0G9y8aJp0knJjMmIqodQ5hIdCiD6a3dmhChm8DcvbIUHpj1N7xJicODyfCy5i7CTy5RIldOOm4Z8Kyth+3X29Mec95n10EhhksU0nLnVH91VEoo2S3Mznwnr0gZaxcGcE7SyFQiP3oAv8NPrO8L4aWxIED9qFoxmTNNfq5toendP2hGcN1l2hOAwujw0BBtUlLumiLgUhGoTl2nVpvr1C/dvCsdGrx6JPl4Vz4InanADIif3REjMN7RYpAs=
*/
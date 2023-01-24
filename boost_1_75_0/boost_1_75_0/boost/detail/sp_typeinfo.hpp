#ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED
#define BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_typeinfo.hpp
//
//  Deprecated, please use boost/core/typeinfo.hpp
//
//  Copyright 2007 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/core/typeinfo.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED( "<boost/core/typeinfo.hpp>" )

namespace boost
{

namespace detail
{

typedef boost::core::typeinfo sp_typeinfo;

} // namespace detail

} // namespace boost

#define BOOST_SP_TYPEID(T) BOOST_CORE_TYPEID(T)

#endif  // #ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

/* sp_typeinfo.hpp
YetadJAfFEx+NgaqO+K8g0V/qaR/SdDT8hP01LPDfo+jBYQmEcWM8EviGIuYlIMf/BhkL5TFHXKMhByyz2UqaqF8IaZFFgy0JqI/N/RmlSihjSRLJovrSrK4Lgumag2XRFy5wVQaPjjYPoQerf+MBMrlwVQaHJj8Dia7/ohEoAGlInjLVgQfm2/qzRTBx+Z6vZki+Ni8V2+mCD42l+jNFMHH5kydFcH75tcJliLIBXF/boVQBO+bGxItRYA5MRVCEZSVoyIIx/8Tl/sLL6WJPrj8ThT6T7WkD7qJrBb0wVOn1wdPnV4fPHVafTD1hhTVTH6irLk6trVFsMzSFquFtnBfw9pi3em0hXl7X4xBBeCvOQdveQa8/6NymcgF1p370c7NdITQD1T7+AOneln6gVLE3DgIDexO1g//Wpqq+WgqKCs0UDdWUXw7PMIRrSDSBXdxfhY8rD/Il0wMUaazTvB70qMUwh/QKfqJQ3q343qvgCf/0p26sZwMeCNFH3goMLV8Z/EscH+SgyX9Y4qH6gN3FF+Fa0awHXHOrS26RnrIl6hHVnHobFhyVt+FicVA4fAZBxWXqLQXSNm79lIPHNIH0lOK10H57XDwJIBwiSVKqnrulB0gILYkympeD9XMqnx7O7UHzr/8Jd6iBUKMgMfZEfC+SD3waOl5URQisx1k+vrVZinNVOq5Ev944anUQna49EvgDR86smj5
*/
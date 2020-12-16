//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP
#define BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
//../../../boost/chrono/detail/no_warning/signed_unsigned_cmp.hpp:37: warning: comparison between signed and unsigned integer expressions
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//

#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

namespace boost {
namespace chrono {
namespace detail {

  template <class T, class U>
  bool lt(T t, U u)
  {
    return t < u;
  }

  template <class T, class U>
  bool gt(T t, U u)
  {
    return t > u;
  }

} // namespace detail
} // namespace detail
} // namespace chrono

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

/* signed_unsigned_cmp.hpp
A77D/KPM/wR4TOsH4J+B3zPf4XLnNwZ+gPSmwBrgZUAtvy/zhwH/ivQcpo9ieh7wM6QXML2I6WXAr5E+i+lzmH4P8BzSlzN9JdM3AJ3AzUyvZPouYCjwGRfby/R9wDjgfqa/zHTq/3N/Re7ZGP0aUk86nnrSKdSTbkq96BbUl+5KfenuwGW8jpfznMEKrs8reT5gFXAk+blOcl8Ea7fJOjlEoL+Bw4FxwBE8J3I1zwNcA8wGjgQOB44CgsRo4E3AMUDqo2MPwtrPYRPqo6dRH7059dHT2U+TQYL895A/EjhBcgPpZzSPfh4LqPdfCBwGLAJew/SxwCnAIuAt9Gc4FXgrsNjB85ROvgvyPVT7vWvd521kWMP+Xwe8hnrpucBtwJnUQ19NPfSd1D8/CNwJfBO4C/gu9dD/DNwN/Br4O+A54AHqp/8a6KB/QBdwPzCC/gEvAR4G9gceAQ4CHgUOA74LHAE8BpwP/AC4BPhX4HLgCeC9wE+B9wM/Az4AjEL7twCjgduAMcAnqCf+DHAwcA9Qa/dLwBGIHwBeD/wQuEGT14mhArYFbga2B/4emA18FTgC+DpwGvANYCmwBrgO+CFwL/Aj4DHgx8APgY2182fAWOCXwHhgiMvtvzMBmArMAKYB2wHTgZ2BrYAXAccAewHHAgcA23J9aAccA+wInAzsBLwdeDFwCbAbcC2wB3ArsCfwCWBv4B7gtcBq4GjgIeBlwPeAfYH/BPYHukIw54HhwL8LyAn8AtgJeA54EfAb4EDgt8DhwO+AI4EO8N0EdAHLgKHAucBGwAXAcOAi4PVAXid4h7K+TmbwOinjdTKL18lsXidzgNcwfSxwHq+TO3idzOd1sgCYQb+Ii16PFFtB1SBr34jA1/+/fCPqzwmINyJ/sLMC9fGNuLBDeND+ERPfwLiBRoPKQRWg7aBXQDWgs6DYNyNFe1AWaMKb9pkAO9jBDnawgx3sYAc72MEOdvhfDj+G/j/sO2rK+vXW/4f/P6kL2vsX2ncZrdryuSVFuVOmTykXHZFXrn1zkXmFM3IN2bkzIG0uvj7nCp4TmJqE73PU967mOYHFoBh+R3tes+u9Tul731wkVdRQWWHRHIHg1ctA8qz8Yvwh7S9nAaskX5HSTZ9GXYrvEmr3NZTMdsxr6mljwYyZ08uRrv/GzN/00cmf4OT3MLajCei3aEfWek875Di4dQap//VCGvW1pyn9M5ZvSf25utnSf0HqMsj6DP4Dz1K2UN28q0bZEqNssqML8ouLJ+YXTKUCtpWc5A2lrntg2cL9ZVPjv9LlL9s+lF1oJltpEZSWrGVa2EAyZYT4y/SiNif9ZWI3WctU0UAy7Q4x76dKE5noPMNSpsoGkik71F+m/ShbZSITqCxQP1U1kEzHTGR6CWWr/WWiLqi1TNUNJFNJmHk/HfaXifqU1jIdbiCZQhr5y/Qyytb4y0S9JmuZauopUzfKFMtDP/157qUn6ADKnvaRifrK1IPCjYb+qeKFp2y68qEZ/ZD05aHTs5qeP63Iq7MUJvPbUO/Kw5+s2irYVo9+bposn3xevi3c9w8pr48uk5TJsGafZl9EukF+S/w95Ml5yNgXZXVYs928kdJe8RLpD9XAyT5Q5c5rPFORpjGhfqQZ6jfMv+oI//a9pumo+rYviHXfzeM+k3GnbBc59Dbb69GmZLYJdSNN1W1oz9JI//Yc0u6xvu0J4p7h5omU+QtleySHaktJPdoSz7YslG2R9RraMS7KfFwW+rYjiPvMQr9xIYcaF5SpR1uM46LqNt7Lo/3b80ftXu7bniDuUZKH4zI/ReZLFuUvph5t8YwL6kWarNfQjhMm7Xgd/JW+7QjiviY=
*/
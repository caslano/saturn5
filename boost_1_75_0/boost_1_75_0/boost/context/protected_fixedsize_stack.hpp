
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
# include <boost/context/windows/protected_fixedsize_stack.hpp>
#else
# include <boost/context/posix/protected_fixedsize_stack.hpp>
#endif

/* protected_fixedsize_stack.hpp
1C0Ac/AfZinAt+gDsMW/Lgrga9+4freU7ojJNH7i8JULP2YCfhJhq/VN6MuVnqQHJ5OjjH/3R/DlXSyv9SDLmD7xDl4+f46sk5PLG9h7UUh3v86d932VkXmavXKPZPcNDKv3snHmCBOpKEsVNrRSOCUo61Em9tPVKtSi69CY03kVR1bHRBoVFISNm6M2ynXc3UdST3zo5JP4mMNfh/kaSy9IQwZG9t9FX91JFOTg59fKwksdmpxZ8BppqDhyqt0kRBrBgjpVMdxTGhIyLxLsCJbedAmGF+n4DgbNpJowrSaMqhInjqKbQSIMR3soFZpWiC+ZlBPSfIwiJR0YkpMXSfU9jKP1nuMBakheowHqyUYK8Qof24GFRqEmtLEWmGviWSMIotDJ/Gu1Dx9eU7Nrqhn8P8Dwq1YosFEGswSDg6E/mvOo+QNoH9lkAjqhnE657+4BRW7Y9vN+f7sGYHt7m6qqWBiWI4RW4KMDF3oN63WjAMrL43frVFKlwDsbLZYw3XF0EFSVoLQB48NkH+dJUcj1ZfLyOFJododDtKvorHbRch+2BDOwpJ0Cmb6b5x+/g/UTz3DizJ8xGvdJ+2tMcIwnHpMZEjyu3owGkMgBxKk0XgVXQGmPUfVM+AAXlcTGHZHYqnP1fRS4YJADhBfnIxKYCbv3qlWhRqxwi1Vr1geG34VEIeXCuUxUKl4klMhHX1V8SHn1fmZFZ0Jf
*/
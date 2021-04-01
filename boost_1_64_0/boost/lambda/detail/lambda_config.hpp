// Boost Lambda Library - lambda_config.hpp ------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_CONFIG_HPP
#define BOOST_LAMBDA_LAMBDA_CONFIG_HPP

// add to boost/config.hpp
// for now


# if defined __GNUC__
#   if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) 
#     define BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
#     define BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING
#   endif
# endif  // __GNUC__
 

#if defined __KCC

#define BOOST_NO_FDECL_TEMPLATES_AS_TEMPLATE_TEMPLATE_PARAMS

#endif  // __KCC

#endif








/* lambda_config.hpp
QGVFlgXfLByK0txKCp1cxBpI/vOYci57KYDabfTFSLJawNDgucnX0ZhAo9VUHpb2DzZdk8nafDtN/J8pxF0qVxVInYfZwgD7FS2b+5AfnT5hQGNJKGmX0DXKDSYs8FQwRKG+d/lBUpLGiruCTx/J1Mohahp0HYA9qnmj/Wu9tfO4ffg7R90AbUmbQqOiFdk+tukhWFOYvG3lMy+MyKV6myAa/vJOI5BxffY0lJkwuc0Loun6yre/SZK8bU/3TVO/15I6H2kqYiOKx5N2660+97st5OuGXrfJFyWh+kgRbvsvfREFtdSEKBx+NtgdlruGbYoBAvXsWYfI+SKN/PuiAlMp5sD+Z6CC/DYiPyXR6+KYvWlhmp4VRUvhcIjHXuzDb1fi7YXk1c6JYbHS138zOtPQd+ZdrcM47/q1bdbAoJRqbxQbrKkrhAdCvHKysoJ4l+QzmEThpVDqkslV6zJ2049nJThfTRdr18lRsLSgQhjiq0J9+swtPn2NZpMFccKBugC/s9GpphHDd+Q/K18RzHB8k0hAQNN5MJDmRU5da+1F2ZrOL4s9gRYaHg==
*/
#ifndef BOOST_CONFIG_HELPER_MACROS_HPP_INCLUDED
#define BOOST_CONFIG_HELPER_MACROS_HPP_INCLUDED

//  Copyright 2001 John Maddock.
//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_STRINGIZE(X)
//  BOOST_JOIN(X, Y)
//
//  Note that this header is C compatible.

//
// Helper macro BOOST_STRINGIZE:
// Converts the parameter X to a string after macro replacement
// on X has been performed.
//
#define BOOST_STRINGIZE(X) BOOST_DO_STRINGIZE(X)
#define BOOST_DO_STRINGIZE(X) #X

//
// Helper macro BOOST_JOIN:
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in BOOST_DO_JOIN2 but does in BOOST_DO_JOIN.
//
#define BOOST_JOIN(X, Y) BOOST_DO_JOIN(X, Y)
#define BOOST_DO_JOIN(X, Y) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2(X, Y) X##Y

#endif // BOOST_CONFIG_HELPER_MACROS_HPP_INCLUDED

/* helper_macros.hpp
N7Vv7/RUf1LiHcVnjRN/3L0z8IRnCjHiL/sx0wOwkzJl9F4g/q6j3nKoBpajqi5guJ8n+IPUZmAPGHh+UP+HuN9b6p1QM6DeUnBaVasjsFCl3DOEe3iY+SDgoE0rxoU5Qs0EzsodDWc9i7tcWpxWplAfNLegrsIeWa63JHEdPsa5Dxj0lqrjj1IutZIFuDZWk5VyTPc/iY/vQmmdOtFzF888CO90XESf5o8x/nldfIv2JINpCDAzlyHltDQ1N+gp7F4mr59l23/OylyGUkxiuQ9UvE/PTbf2nx9uxg4ie3ewo52XaRy5rgDmEfhVyyzBr9Pwaw5+TSNw6J7wew/8qv2KmQAeYvLv2VR/IMrcC/3cc2r9dSterMUm4Hfd+9Uz0SkM5WSj1ZeovbX5wXQ7IlPxLh2nrHVX8KuP8Vyo04O/chLXXUvmbIXpq4TveUWSBsWq9e1rkxLCrzqEo/pvPNDDZo7L+hVfJHEZZbmstPfyffDHDOz+4/3JOXhko1xuaeu/5qxEjDlgF/Fvtxrd5mGv5h8Kjx+UlOoqQe2D+8VqDa6CU1cJckfKwDd3ndapfkUeSXxqG+N8feemvvUNHjdPwVMItBuzVmEY5nR/ZW4GfVegXQjGmZnrUTs66zXG6yvid95IceUs/TGPVJY75sfuiOfygE+qHnx6Ckw6zcwtTjatCC8Q4/uImWsDd9jH99Yt8J21P8TWX5djk/Mtds1WwFibbnXeADEUxLvTz7R9HCZx4rhC5zA4xNAWSvgc5iyTC4TvpUnl+4kRhE0OlLTWGm9ksoko4iTNiyrUssYEDAw4qj/sGV+B/0abDFS+gvNVWfp+JNpagRYE5nDta6Uzi6NQiXlaCAKzo+vgPoklW1ZV6CaFr2Whjg3J4rr3Wfw9cJlXYRlnIkzkETD+0QNpy+f+dipTiiIL06KMXAH5oh4qQP06afvx3G31v2EuiyCrfGGq6/GVR+6d7Z1RFW4ofcKSjYNKFq6MULaR26tUDMkeY7KBkHEVB6oLRFmwVzKpZyDW/PAsk/VEGaWhCz6S5+bneyegd1EBq92fuRNzy0YW6xCTrd/zwXl2ItRTE/C6eOo4WClffKQWH5g6BPOxv6r+5/zdoH/SBUjma7eGt87qjkN/D8PZnO12xLb4+8mcTZNx3rbD5NG12nETYFU763CWYW/0vdRHGKzM506oSSnzeQJndu8z/Y7m0LnjH9YAznXAk2LKOb+WchYWCQ3j+fJ2ngHRXJqeXcJ11LlnsDqZhFXqFEEiaKi2rZ/zVMYrRJkmqofwV38eoXSCPvRX8Ay29s3Tql7pq1a0AlsKfqnt+xn+3yl/f5AGZRHqUe3QPQ/ODPvXoO08F0WUhKWn+Hvggv+ymtOSQLCtPtPyO15lpZOnrPrbtit2Uxkpcj9MfRllRkab/uHhCCpzj7TIkzIpvDpu4Ge3jRgJR/K4pTKKvTxsuwSvKkM7bo+gMoXwwiCIy1gKU0z7p9tyhrb0LtWWLtR1GLfDJpsCadrSexT++RqHnJhTe4uPaxn6rOYDigNxmSwq/wF5UM8JPmS+JfojOVf5l/p5b43CUHF3PFDRVbo+M8E3KWuRO9eEyvyuIS9f18XTESXt6JedPG4P7wnrOzkrg6V6jEDe9g1dPNznR975IR73NYbhbuzkYbhoF3UT8jRN2bYieo6NM9yOPvKuMJ4dHPEXttniDXQVp/6srm1z6k4Vwzp3nU68KWxqo/F6Nk87hyZhPe/6yFGPEgc9eAZB365e3gY4zs1Q90tuBN+hlqHueppDbTeP3xg4LFsRu3KTFoMcABDtQe/gGOQOyjGM38c7dzOCQROj9qtv0WL66HGwSGT/sJM=
*/
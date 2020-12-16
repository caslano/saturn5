//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Greenhills C++ compiler setup:

#define BOOST_COMPILER "Greenhills C++ version " BOOST_STRINGIZE(__ghs)

#include <boost/config/compiler/common_edg.hpp>

//
// versions check:
// we don't support Greenhills prior to version 0:
#if __ghs < 0
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0:
#if (__ghs > 0)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif



/* greenhills.hpp
lWB9/zyG58ctWt0/yoENO83vH2M4jtJfx5huaF9HeWwttnyQYwNeZmzf1S3evkmYxVWS3bUdBvrxpOmdt7GNpCx17bMjkLNhOcdew3f+Z3+8xc9ZVBBHWRwm4sJppxDhxTJw7v1A47mXR/Rj8TiTr4TJQ5sbrYR7nlFdhDfI7Rk5JBDljWPCyL1Gbl+KnPXvGf+2xfwOFIWqgioWkECSd/QdPKOl/OmwjGUlTSIgq9pxhhMrWzHZ3jWyckdClsYkSRKJS5vuPe9SbzDoLaNDRWpsQv1jXKLlzKyJoqQMhZtj+Pn+/ZQ3Y6vcdU6hBDtFhxO9qD2n63O72zRQWZTIrkKNb9IqajqFtwzGErZ92i661KVKQyk6D5GQUMrPFa9QmULEYRUVOs2ErCqnCK0q8bPP61TmnImK3MrACiwayQz1r63rI33uQ9VmeapKpUgp15fBxeVu3SFgdAbpYF1be4BHWV3LVMugioLaPSVy4d7/+y9wfX+sfrveW1nYXd+Z78NTg/pt4I+InV/pvhMXYx7b+F0NyucqtC9FHJ/n9bZxIsJznREeUiAtPNPzOZsbSEPeCw+M8rbWlkfS+84oD55LIQ/tUg9SHp/XbnnYYI/6fe2QxxtTv7nDPmd8/Y4f8Xnj6/dnn8frh314cxJ5MPW3ZhT4FuPyUcBhZiU4vEQhnAeOIce36ETOh15MOJDE4tYWPEagdpTXXuJxVgbwph7TeOSlHu7+7V2tnzwg51cv8zhbi+SteuPT8j6fs8bivT/yihbHTx2tN6bz01cDb/CxZukR5JdCiJyGZZl7zSjupvfdHvnmTXrfvFxleZkUd72moOuHd5L+7F3jNtgP7+M4gNj++wHDvkaHCdiHBznec0HilnHPizZlwGG60CSEnJl7RjlNMsh5/FnAoX2AyWB5H7vX59TJYD/mzwWctz8+JCL2FLf/vA/tJGpdaWrWzmf4VvG7+4HHyt2Qei3n5veQg2Vq0ulhHNtNb50TK2Ok+r/ty6DPz7M+52dOX9nHcQBpWy/vB9zvV37mIg4jx687cn44iRysu5/Xv44Ch/UJcl6JNoSc44+rB+5FnI8r0lc/flVj8ztmT/rKtt8z5NB9XYl2JH4/BUVSxuUz9lMzrp9meD+5zQbx4XCE4wDi+fgkxzbdpxoIzOfnPcCBXIdJL5F2/8ezWwykAMduRM5njrUcyKP5+AAd+wbeKSMHPilgWba1S+b5+44DznQA64mxrF8JnOXeNhiNkbSvvAp+H+l3xCdOjOBQCMx78tWIc70gfX79SmMrDqT2boP5OkJ8T725rpEzVm+EpzdFEeY6jJ+xb9JGb3D9eW2T+SlLMhsmmftCTLldCCzGiQ/K9XZ9/WUqcza2mZNIQxGBHQ8REC3/K5Q/HSuVJ0mVCT99AfajyUudHmwAf2fh6im3/JzgvivPET11p0ad/8b9gDH9Bxhl7SHEMWF87wnYUK/cK0fwKrkF6o34rcMevuOe75GxMXVvh2+tu90X0dlfP6/FoDx8bKCd8fGWA7jre5r2KxCrA+26EL2YtjiBGJlb62oj58m3IoeOGSDht+zpqVHO5lbvWh9o1Bb8HPCaKjY7bIxPPwPY3uMrOT+Kw6NaLOc4HB7Vkn3PrXXPT0SuqzyLClH2dgZLC7B1rF8knsa9Y+ez9WkmW4gqjIsiT6PaY57dXVxfW7ownfVcBJKgtZZ16bA9OKZ1YoPHEkvKKgvCMqjTukRj4GwtgGOGJnX3ML8rGMZ+YGkZUURpqoo6JdW8E4Vq1UuHkQJNdPHNVlk6mYiN1nkcxXVKs87iemHHmSOPqx3fjz5M0zlndVwpUwiX4XT3p8l8i8Y5OMvfP+I=
*/
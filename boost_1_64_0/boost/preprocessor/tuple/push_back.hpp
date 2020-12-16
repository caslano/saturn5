# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_PUSH_BACK */
#
# define BOOST_PP_TUPLE_PUSH_BACK(tuple, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_PUSH_BACK(BOOST_PP_TUPLE_TO_ARRAY(tuple), elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP

/* push_back.hpp
eA1f3vJ11T8ofb90nX2JOPA1xrIkyWfyuDp6/F+H+//WLovHS+eEt63X8LiWzs/Py6AXR6k/JH+tmLOk8UCvb7J2fM569VVRT2S3+viqXiNdDntG96nrWncv/zOhu4U1YU/5jIz5luXGXnOflBTKSpOu6cuS8a4sf3bwVQU9JzBYULNhzN3QgLdr0G9ifFs/MwvBXZ6rYaZhe537fbexF2zPkY6I6Wu7BWBX4Vb2T9f1pnlConuxcNJcLNznWSx85VUszPAuFtwsxcJTdYuFFn7Fwn7/YqFnYLFwMahYyKtXLPwSUiwsbNCZvdXgqFAe6sXeDD0pHA7zYmfCTgmvh3uxd8OPCieaerELTY8Ix5p7sXPNTwunI7zYBxGnhHOtvNiVVseFC5Fe7MvII8K5qIvseJtytiF6P8tv+5TgFnvTrUWncfp1Xd7TUVtFpn+hc47Om0XoeumMLJLbq+01MX5B/caspfvD7j3Z6+bV7K8enmyVh5F94XFTf4/PNIMuYJCLaM8Y9PvfyW66YWeGavhb5/1k4X5R5m/CCKEla8rPb59TXwke0hJ9ZTy4nm+42ffsoF3sscF+eFfewoKhfyT0P055Jw31MfVoU5CYH9IJ5bhL19PZbAPkmkPOg+SuD11kjmAhnhHsea9INts7kvW3RLKP60aySX6RTAiIZEsDI1mj4Ej2fD20uH4ke7tBJMsIjWQ/NIpkDzeOZD5NItn6pvi7eSQ7EBHJDreKZEciI9nBqEh2MjqSnY5BnjhgQiQ7d28ka9UhnBV0msMe6TyXXe06h+m7z2WlKY+wUb3mssZ957KjvL7FKv/xy6m+HQRP1lhQ3JcVpufmZGTnFEpy69zE8ROBuxej/MyW+psb6877Xyt38s1t7ACZVFbCmgh+LEVIxHc8R7GuOk98tzYRr0aOZVl6T/aQPpEd0U9gj+BeeKshhn1lSOJ6MdOR3gBm4dyvo+PIvj1wE6++TvKHTCpkGlI7Ph7q2rFD4B60VWzLKWqr+C4xxi6fy3MhK7dzfF5RRj4e8VrThiFNc9y3taZP/taa9xOeXjRZ1vulvbx8b+BInCiV12VNOa/Nj4r1jsY8ER/7YOxQw63EDYaDHa/oX+zSXVevWx3Jj33ZYVHuENmjLo6nECdhuCo0kS5fxM04IcY90iGF5Ua1blOXWaIb6HfF1mXL4uL037a7X2ez25OUtycL5vPK1VdpHu52nEVH12lb3/PhJL0xTjmnwNNpALsvtij2QcM11G9Vx/GsRace+tldLEwcy2u7xQvXuruw+j2e5fXFjl7Kh7FI9eU2RV1t15pHqK6lEfvYKy38K9n9JKSGYVd9FrUrUNLlCne2h9p82ma7x3MdT7KopCLdtS5FhqMpccZI9IEE8G+dM1ZjznhDb3Tpxua4d2M/eCSwRnWSWGdLGzaybg7z83WnMd0e8tax/+VgcexfdZnIgnD+CkNaEtLepDL1fUPQ5x6M3S/cStwvbO9YwN7r2pL64Atk58wxsDDZd9F31r6RLhJK78WLfjsYpZ373Xq9aFGs94RxmwVQv13bN7MOE0Y3E4SQdsPZH+3K2Psdwn3CuH2ybogyi81r2QzhBd1bQgPjDCHa1Ut3yc1f6FiJz04p+1jbgJcDy31WRBjZqYizzL1VF11aZGfPF+8dy6Lbj9UN7vQsK+wcZXy9+4fsjx7eLK3SfKsLELnzMRwUBJeerIfravabqydrZBqoU8/BX3k01tWvk8zCvFezd7w9WVuf+4VLljfoOt8iPRO3tjWY99kfXcT54QTuJULZEMxGuSxeGMX7Rz+DmNbUHMVGoJen6jroWwtTDL5sl+FZNs5oZA8YM1mQi5E1dyk=
*/
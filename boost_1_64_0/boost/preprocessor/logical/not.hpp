# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_NOT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOT(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# else
#    define BOOST_PP_NOT(x) BOOST_PP_NOT_I(x)
#    define BOOST_PP_NOT_I(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# endif
#
# endif

/* not.hpp
RL1xsAMKJxyPkinmkDvoepdkNN0QCKlp2KFKL7+sNQ70WiDJe0LqpsE7OlWLx+7aPPVYlQNo+trDw1Bz1Xc3cy23E7Pdt9NQTVRa735TSb6wu9YYg2BXCAwzedGONvUcBaFCZmTWigQlznGLaWtClIR5OJT9dvMwOI7AglCBO7lM02rSIvUgh3uFcwunJscW5hvF/SdGbF09foU+58cXZuWFuj4qz4dOnT0lT4I/IlrAt7pihp3yCHYgbF7uFus7O+1wb6kYGCiAgWKweVHdBycfPOn8/HhGpNfQ717tHttNva8vK4tL0pql6KB3yHJLQ5Y0FgRTyCW0WSbJNjB7v/F5HhqeqxyKEiF1vI0nEf9A3ZvnkVLWyflE0g80kSpV5SeyB9Fswxgx1ptTK623qVnVmqhpSfGukRSHQO9H4nVDX06W+/dtE+OFOlJP5j4T5MlobG7Twq8N+5Y/p1NbU7n7dN1apLfF9Gyd4Sm9qAdFv1HlNKxtc6IQx/YAudvYQQ4iFJ6Wq3a3AaGq5bk3SUbj7SyjSfNc2brSz0CB74LcBpvLej6tL3cJejPkIQdq8r6rL9qXnkhfeqLJgFTfhaVB/WwtXYQ+vNBytvaRC2j0sgPQN107TiBprcOWF+ssg0eGhkeOHrvi+F1P3G3s1PjE5On7nDl73/tN3X96ZvYBc/ML5x74oAc/5KFLyyuM2ufXNx79mM0txCQfy2J998LjLj7+CSL7F68a1kT/4E3QwryVqXCo8xncg9K7vnAd7xhXVREvyQ7iYd1iJwjsnNYy8aZAxwkOHeKRncc8TLyVdcOKjpndre2uy2misvLChjBhg/Bmj3S7erBiqd3RNTnqmQZETDISxtGzvxxri3Zr08hq9Tt8CT9C4zKJPsUx4Gxc7EEbBUnTcYPZZZm5UzRBKl9nQJOsY7LL+ZUHrRdslyQcwDvgx2XgfLHwIJfH2+Gkkk1uWlOqim43WoazPsrop/MhS51MZ0TKwZJK4CF8aJWluP+8YEuujKl1Y50lC6NhFExpIu/UidI4cgbfyqYgumpjxEl055ZRriztpRsfq9Pk+i/UBFft/KwopDPF8yT5CobHZaK5/fBIqq3eDwQ5P0kjKh2/87iWFDV5p4cHzTf9iehvbKtS3mi+IRG5PQXxE/YnEoXL7aQyO6orNfLj58ZlZyADgnhoLzdr5wSzpyZrDTL3BDei1YnnJDa9Wu8njRu0Ek8fnPA0Lzi51WpyIl/0Uc1y6kQY7hrDyamUxt2jfLmWxNT976flLfyizRI66tAaZHMnWm6gZaeNVeOlBDM54rxBExpFA02276hUIJGCWGTzZ8aGD0v7liJOz6H2KWOtJkq4ThuUsIfphfy5Ev9s3KUsg+0/caD9r25WSsnh28DPX+m0uq21nZIvc6BP6DP1S5+oey/7Mo1lh1M9i+bfm2lhfT3IIh2xplI14ijPz3w3YHNdXCiwtCLuQ90idbdIKqdJWetoIVcjX6IX1ZGuQ1Z7r+oua8H1TmoSt7Q7uiWy+lXzvXYSXNeb88WYTf3avXZo3SaFNE5q1mMyHX92K8eTG/6yjj3rzVvNux00niu3i/GcM1DUIiSc82hH28v8XpKmOMbbBcLlDmP3dmyBkdcXRg2XxFLhx0wnnXT4u6reI3+vrNCoQpzR0vSVLS+dDzJh58sx73Zddat9z69zjUTmaBzwI97T8agKZx6tMa5ztKvYKl8szOJpGS46bUhA90gdoqyaypbKalJA3+uFj9WjudM45Xidk+9B44npv6emTfGTW+2dx9edNA3nkjTskLg7rqonwtH9hYehxqJ4hr1INkYw5ebzoB8wS6H7fKR6730HS7fJJss=
*/
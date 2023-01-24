# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_TO_ARRAY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_ARRAY(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# else
#    define BOOST_PP_SEQ_TO_ARRAY(seq) BOOST_PP_SEQ_TO_ARRAY_I(seq)
#    define BOOST_PP_SEQ_TO_ARRAY_I(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# endif
#
# endif

/* to_array.hpp
hSGTN0b26tXijm/Md+V4AI8fYmo4cy2pM78CXA3WqdT7OqJ4e0q9z+TYe7s2AViZI18Rdox3454Qp164QpejzyY1GiLmX5dgWONjUqxoA/cQTmcB3lBtgLRWqbIWSt8UUpRkPq9jOfaCOEudmNRm5FNdyHf6lzAde4rb39p3U0O6l2i1dw10sXuDFnco/npk1Iy0U+/aSL0NntPSlXyUyUBaoPa0eddvhJhrpdduQf+ObJK/Ixt0G6k66u6r0MqG0/JsX4/36c1tGblanDqbXsgeamwJTDsqW6sR6VHOyRWrr6fzdheNxJHqTUtNgjnfw4FeSCNFCXvWni5FxzCqCkMvWNtMOT+hjYQfvbrg8QWlvXVXLW81C7kndpuWtyvdmhZcD6bB6V+JUaOlDFiihWJb9SxygGDFYWFEKyDN8sHVihSErJjW/ZUtr+SVTPOhcHZCC6nO2O087X0g1dxo1eNa3UHA2limHtaBQf2ITMrCarSh1N6o7Te9lJvT/b3lSz7W8ZNH8rq9/RvAgs9ZTtfFtJox03wxMKsK0Cw8JpD1oWVKq5cQaZJZp71mjrXjo+Pd8x5E4BxS5deyQUOx39uYG1eRYD9QRuE+h37aQNOy8lumt1fqEc3yQhrC+hhwum39w0AayE3BiPu4HtNIk/WN6jEhmOvWDAVy+DE7fOun5jdWHq2ME6XPpfwoGRLGxY9J+Cxy+CTgtpfn
*/
# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
#
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_EMPTY_OR_1 */
#
# define BOOST_PP_IS_EMPTY_OR_1(x) \
    BOOST_PP_IIF( \
        BOOST_PP_IS_EMPTY(x BOOST_PP_EMPTY()), \
        BOOST_PP_IDENTITY(1), \
        BOOST_PP_IS_1 \
    )(x) \
    /**/
#
# endif

/* is_empty_or_1.hpp
HdUC4QZKz4fsXMA6BDjdOP1dAohD7Mmjbv619Iak+vDg9iIxxbgW/kzjD1cP+tqvu8vkcfuI4Bs2Y4nu+/svb2kCj52GEeGphnfGf3apP98hCJLt2cWCOCJA1j9eHv1y5bCKXn4h792/KVTx1V+3X7GjXDz3G7sNEPdypuMFNXuzM4nBhWkCLrWKJM4utEo2ZeEXb/4B1lqFxqFv/u+g53+9u8TF9Y+3uIWjrZOMs4OFpdt/rGzqL+qCJpso9eNyBCOTD4B8yvZ8jqc6UcmtniIOum77866cY0p8M0LVZobAlkTProoKfqfUcz97tLB3yTMpOMxz4g2xVWb2skPBTR7mYV/QVoO9YnCO2rEHh0jZAoOnq3e8J9q0U4lWm8bheULAi5vcmufcm6DsmntKaIWx7uNOeO7SpSMzJnpZzMawv62uGpW76g895DBWSOLk4frxi0qvPvMLRqnJmhZwVycuJd4XtRb/CFULKQ2lIoSnhwjX0bY0qwDOuI1wOmJEMUlU+KBAw2P7y4Mlna+y6Lo389B9r3vFTg1R+bJmqLh6PSObCUoIyPVNuND5eDL6SeITOaoU6gVA7gt2pKKaeWJcgBkAzpfAaT6pG/Gnq0dL+gDYeyFAeLJGtERh1DoxkJ9JOMhzcGKR/+KM4kSbhsi/025f+a7yI/UPaPrpOcQR9RWPihxvINSbOoCz1R6Tt9QQGcEmxMyxvRlE
*/
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
# ifndef BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
# define BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/slot/slot.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_LOCAL_ITERATE */
#
# define BOOST_PP_LOCAL_ITERATE() <boost/preprocessor/iteration/detail/local.hpp>
#
# define BOOST_PP_LOCAL_C(n) (BOOST_PP_LOCAL_S) <= n && (BOOST_PP_LOCAL_F) >= n
# define BOOST_PP_LOCAL_R(n) (BOOST_PP_LOCAL_F) <= n && (BOOST_PP_LOCAL_S) >= n
#
# endif

/* local.hpp
88wr1WQxZpl4PQ/GuDIHqioYdP80e6vhEiKItzFEG52b3LvISBBLVhU0a1K66rstJzibqBlV/YkcEadhOlQP7BXLJbQfh84SaNU4C9eZOfGNZlfuxWrXh9TC/FIT2q+S9bUhXz76p10VFtGKwfwHMs/Z8ywF7jnGmk6O/pef3dQojKEVYcBIw156wPC8Cn7O7wdIq/riJsxDzTZ1S/IW00SwQAbc6LyhmGx9Wk9Nr54NvWHy399ASjPra3FgxNwkq93p0C836ySF7HOOUMoBIZ+eEzEWX8UP2i9FAqLkVy3xWvNzc2MNfBP0KBJt9A+nyQG05/74+loUFAQSfLIABcUkYrfrKjuVbpyKL/EgRfk+frz6K4+/DBqzagEH17tjhcAzBtQjtLix7ypeC8dASxMd9LRmeoynZ0W3UzbRLi9Po4OqSMIagbewK+RQzLZPsdQji2x9D10p7H5R6sRb8/rDbi3vGw7z9v95OMQPV0bUVKwA0jxtKWS5qoOPSO++Z57DL6AhywVqF1YZtqkNMMkedW4z0TibRNEPOEU/77AUfYHoehkUl7FD538ja4SlqUKeuAyqr5+ws32TR7RekJJ5R5vMfP5wy/OrBss3ix6SAAUtkhNqMMjnblWFK2bWACttTPXVTm41grwyR9QLh6R4mybn0nuvT8Ia5K3MKzBFytUc9s9C8fdSYWvIX/UFOjGLphm8x4l3UWCVOv2N3h8DXyU7+qowsBnrALFDG0e6h9CfLziA/h00fZS6KMZXe4Q33AE07GMkGKGmpAvjCzSVgBsSAbKqkizVMSyNvEfa3oV4qhndZdAI6cIuuwsn3FYXLqYubGvLOChN43bL21WTw+oLr4cYN0bYYW7hMIHEJ8DGgyTWUZQ4yzoXpIQ4jRkcMJMapSqpNd/AMlo3nRb5L67UK0BIXZsu57JuorwmFtApvsWIvOYttnqjaHv0jgL0jmd221fVrxxh+kARSV6AmGtprE3CaISU4jGbA0H9ZpQHdeBe0X2kXxN8QtTufOXV0qtwH4Z3/n922xrCctRzP7nlwalBh3h9KkAtEOEeU9ow87aqZqx7v0y1v8fR+Tdf62n5DY4Jethy6rc1Tf0AU9/xiqr0BlHeCwVyiG1xNPzEVUCK2ClJfsqRmXfUq9LN+KX9WIY8pNq8Cnrn72JGNk7uXWh8sFRv9gamkIrgHy8I/YjyDfDQ6jvC0SC2l1zLbVdUn3qLnAamOE1Qq+EEutLHLNxcGN+oqUqPtyCqEm0MG4lsFjZG/aLv3Zx0676Xndr32v8ofY8kyFA0nHz/XcfqwSEzcazO4RoRjdkR9ax1Mo3eHmGylAj146Pu94j6Y9jHCImlNVyMSU637g2k0kktlxDmKe5xXEJgbRFUjW79Egfvr7FNdhCEf+BcsSof//RN8J56B/R7dZZZ0SeDgXRn9GzAvDOgMb47QVSkqiRm2X+gOTR7RB3c5GUO8lK9PLKl522BG80o557ulPtzaAJV3CTh2iWiCi8PuWCUDzJK9KPYGUa9k8ul2MJp43jJcOI50or2uROkDkFEf2M3nCA+oQ6g9d3kVSVDdN4HWWTht3zWYvRe55w12EGfrdEHgb7n/sTl+NBqXvdnd6KczYkL8XmvutRF8HhNqWsVvqcCzgAUAPoBLgVUAq4B3AyYCLgLcB9gIeB5wM+AjOngAwB0AdQDfgs4D/A7wE2A2wEzAQ8AngZsBLwLOAbIQNptAB0B3QAXAC4GXAaIAEYBHHrS+z4Pa60J4N2hDvxIR7eRclZVoe+5yHUD3FeBqqSuhVU4fTpyuBIrXHcJx30IIUMRml/oap0vYSOqBfxJA04XfPVLAj4iF0D5TRY=
*/
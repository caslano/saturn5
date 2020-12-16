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
# ifndef BOOST_PREPROCESSOR_SEQ_TRANSFORM_HPP
# define BOOST_PREPROCESSOR_SEQ_TRANSFORM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SEQ_TRANSFORM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TRANSFORM(op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_TRANSFORM(op, data, seq) BOOST_PP_SEQ_TRANSFORM_I(op, data, seq)
#    define BOOST_PP_SEQ_TRANSFORM_I(op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_TRANSFORM_O(s, state, elem) BOOST_PP_SEQ_TRANSFORM_O_IM(s, BOOST_PP_TUPLE_REM_3 state, elem)
#    define BOOST_PP_SEQ_TRANSFORM_O_IM(s, im, elem) BOOST_PP_SEQ_TRANSFORM_O_I(s, im, elem)
# else
#    define BOOST_PP_SEQ_TRANSFORM_O(s, state, elem) BOOST_PP_SEQ_TRANSFORM_O_I(s, BOOST_PP_TUPLE_ELEM(3, 0, state), BOOST_PP_TUPLE_ELEM(3, 1, state), BOOST_PP_TUPLE_ELEM(3, 2, state), elem)
# endif
#
# define BOOST_PP_SEQ_TRANSFORM_O_I(s, op, data, res, elem) (op, data, res (op(s, data, elem)))
#
# /* BOOST_PP_SEQ_TRANSFORM_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TRANSFORM_S(s, op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_TRANSFORM_S(s, op, data, seq) BOOST_PP_SEQ_TRANSFORM_S_I(s, op, data, seq)
#    define BOOST_PP_SEQ_TRANSFORM_S_I(s, op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# endif
#
# endif

/* transform.hpp
5WX84A5B0dttda9tq2fb1fT1/Ukdi0bW8LALTT3bsBYvWYvncvbWfquj9rue7TXC/u1kP7o7/7s+Udurpp+ha99Bj9Or91GOLk4OxenRX/HLXmFVf6hOfyjp9z4WDNPpDiPdo48FI3X6I4V+z74t6+brdPNJ9+h9uUinXxSR9h2yPs57tXl9MtXvAIpbqotbGrUcQWmW7FTSH6fTHxfFRwz6QHVe2kHhB01iLcN7W8ilm5c/pPDdJtFGQJ3USFKFrbsofDjLZHFKeUAtIf1c9j7pfGHqNnYVamOXD2NXNqRXi/lsCXgp+BrwL8HLwNeCl4OvS9HGuBXgBccY464Xad4gxrobo4x3KVHGu/W18njnc2vz5zvKGkiMWXHKOKT0fSFP6jGWyWNmSsSYmabdu5zKeNdtHNXGu+2UntbnsiHPUfLv1rfkOEOVcVbpQyL9YVHG5JERY7Kimx9l7C2KPvZSO71Dlvv8woZxSrpaG+05Thd2X08uSxZ1AucP4H4D7kpD+Wu1cdrrd7odcpF7jr9Rx2se/2jjkdYfPie9Iz3HcDWNnuNT1DGc9LUxPGClNSP1G75OPrOOhxVg3DN36zciLVpT8nwOUp8UhdX1y+UUfybulbRbOlt169xRFP5bCu8kj+Khki7+iRTuZ4Xoe4m4X4n8fwW+ibO4vhl8i+g/t4JvA98eZb2ZFKX/vFKn9Z8M6j89+0o270NHacNJ0dsw+YbaGveXMs8rz3mLZEMWo/GcIfAAQnbXae2nw+nxdd/r4a++ubT92x0zuO4F+I36U1V/lZwtxkmug6uHSCclSlvjeWlj7tcpIv0u6Ijx8ARK67K4U8zj+vRsZ1r8VHXMxm/c0mjAaL/RfvjIkZ2Uxoosba9STmFehO2lsCuyMnjboDBfR6vX2YY+E1bSaPv2yJFd9VxvSaY2trfyXNSx/ZlzeXgGdpgxartaPxMyWDlI+OFhun8s2c5WMZvJylpML5uqLT9P4HnEwZYKsqVogLym0tatPHwfbEho4OG+TK0d4y8EtqFtCL/nUfhZmeNi+7MXY9ewG+I29qUwXkOU95Hk/myKaa1pi2mp5eoEnc/kPafI63zY8inZsjSrx1woyrKwnYd/QPpLYNuN5J93MzV9X2eHbp4uaOLhNtYl6vXeRn7/G0sOi0dtnGa6HP5YCb4f/Cx4G/hj8GFwf7OVnQQeC64Fu8FzwNeA7wJvBP8J/A8zdosW6IOHgcdb0liLxcYWWgawQlEnZzh4vrfGPcBmsD7mXDbZvJk9Z1nA/mC9jyXEtrGbY89gn8bOZh1xWbLt/FyC2m8Mu4nbjqvzyc9ZmXb80cWgKZs9YbaxLeD3wV+D+1mS2WDkWwKeAj4f90HgleBbwA+C/wj+O3g3OMZqY9nWZDYOXAM+H/ed4JvAT4JfA39gHcDGxAxjg/oMZPfFLmPuOCt7IW6j6Y0Ee0Jiho1liHq5spnb9m3iILYowZZYIdcn6udmqp+3dfUT5rMXhW9G+IMU/nwm7yOX0vjqR5py3Y2i8tb3yWPrYt6PaVX9cpPsF3X9zOS5Wd7nI81zqA39ZICaJ82jcvgjCP8rhd+ZpbVDV7vkuhDjoKyzGO1wMNk1Xafj8eHHePFzrmItDR1dWCjUKQWVdlyKsD9S/IcyU9U+U16GjktD5yBRvlPIjkvS3jI9Evto/NPs+oR18S1paWo5t1PfiaU0N8DuWWfT/QCtHzq9HmdIbeue8+TzigwRfw7dD4XEwn4C5ukMg21XUDp79eX3BsPBTr4KSoXOJuS1kOzfl1nSbyRktL4GoepomaGNw4fIxs0YWYap4/ABksWobeOFc8jffavZy6ZSszzuPI08TiI=
*/
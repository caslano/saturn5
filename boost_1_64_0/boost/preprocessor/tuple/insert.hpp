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
# ifndef BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
# define BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/insert.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_INSERT */
#
# define BOOST_PP_TUPLE_INSERT(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_INSERT_D */
#
# define BOOST_PP_TUPLE_INSERT_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_INSERT_HPP

/* insert.hpp
kYeeP14+bqvzhCm49ZbqnLCR6xIp5JUW0x6HvtHKNF5pf552uXKaVOfUSvGTJPnRm5TxY6XyL9viRVMpyl+CPKbNyjS5fErbokyTy79eSd8kWX6rMn4sxT+B+C+Jl8KsmPRxRTabLEf81ZNifHK3gemoEX4WxD+N+BsUX5SVq4ib/gaPi1bI2eLaWuNWi3JvinHQx8tZK44JisvIKUL5bRTxS07J8dGK+Hmn5fi23I4W4JcHqbyMqTn4SMGUCTC5bPtvKC07J6twRsFkHn/CF22k+JypcMmbbRvfz6KMULxAqWO9k7u3SR+Y0rlNOp6iUxvWI+065SmcQr44uP4bFDe+UFnm8m2II18YmHNyrLIbkH/Yc2L8hIzxfBxvQhw7RDpziqbkT7bNCVsQXxIh1kN8hj851zaPbBPH/Wu2eYTn4WnPIc37GLezKm070pKO8fEhp1LaTqT1O24bO1IS1WOXWB7Vo3BCdnoR5lxrW6ZA701qd35GATxt+PO4C8e53fMnZo3DMc2vGvurilX7q7BfCXHa+5V+wBmkI/e9keDK371GMCH0QfhSHF/rdEzA6+vosFmZWeltohPwdQUyeDq+XVFA+xD0Br7fqEjTDwfXISj2LFBXkvY4jKX07pRu9aGSOWWMwsfMeErvIPkN+9Gn5n41xLr58brhmbbU3uYm7faWqtqbGF379pZW096Xq2nvwT+hvYFu2u1l6yu1Nzo2rvbthQ6H7XVd77i9nuvvfHtHu1uFhyOYEe7j7e0ntzdvbI5z/bmf3F65PdFoD99nlEHpKXb5GEbp/Wgv0PdiBM6f4wuoPGlP0XCS8Zd8BhfQcTzzZM3s8jiKZHpIPF6Dopp+58Yej9vM2jyWVuLRyXFSDY9HquFxXw14fEXF45ka8HjoT+Dxqoc2j94blDw6N/6gwyGPjTY45jFwQ/U8BkNGyWPUhup5bLDhzvPY3kuex8yKeazAymPXAff1G9Q3fWzWeHFkZ2RkW1lkNeIROhzOY9MpPdkhTw+oeFpCxy3BUz27PD1EMveS3mOkF/VPz5o8nck2LCGZRInL67fBZRfOZVQdq/AwBBPCUM7lYSuX4kVqTnZOWzoxVOqUNeTzcDV8vs77nT1eTqv6z0934LwQ6q19HgzdKLV5grPthQ6H7W220fF5sDXSlefBittor81f4zH6H32M533QNl54ewd2Ti/KGzuhVu205hU09nDzfayU3pL5Mld5HFBcDMZBOPXzKdR+FI3LcKWf8lkk15NFMrNqPpN9R84hmbHYS6VTcy35Z5tJMhOhSa8xXuX9xg+QXAFmRxeVXeR9w7NJZhzrxgTJ7+7Pij2taht519JGxdhPT8htNIvb6KpkI+5Tk1tJbSPuP5PLBylthTjHtorcJKa3Qr1kW/lQXCxs1cRqK6Ztqz9Id292DzNLdXCjvGPt2s5I6XmsqwPb3SS9k6DZse1+JblC1suB7XRU3njWQ2G7G3fAdrb55CYKodpx2xXZxheVW9yta3JKehYWxabAc+G4HJsF7dqQ5wuTbCjHof5SG/GyA8yYniGfH+aRzAi7c89MSs+xe+6isUAy2aTjEMmMyx6jsPdsSs/EnkbZZ+syihug6CfYjY5+ovzO2WMkM0jyw/yLD2zn4zz3tnGzzV97brsqca+c3Wo2tyGvw/HSenPVuc0bcXxuU9iI1gNQuqLvb65+3rq5qWbz1q+bqp+3dJvlecuf5lxlvWAk5VjeJM270jj57Q6Mk3bcVgWBVuGHua2KbeNkM7eVNMvVYIwgj2qeQ5xju+2m9NbMX2G3pRQXB7s1dWi3OSR3P0t2dL4hmUKWWt35huSKWG9H5xuSmQDbcrsx+3Y=
*/
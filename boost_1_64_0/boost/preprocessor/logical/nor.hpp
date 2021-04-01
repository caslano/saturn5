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
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitnor.hpp>
#
# /* BOOST_PP_NOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOR(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_NOR(p, q) BOOST_PP_NOR_I(p, q)
#    define BOOST_PP_NOR_I(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* nor.hpp
x/5tfJweyERe3LSguUbSsV1dhWXspDbtElCO2koWmpcNzbCT++8fQNFw0JyDqI4eLy38csg62WdaIJ46jS+oHnmFFCO6EsWeweIDUzMk5oL9u5OLJixmikeB8f3Ldxo5S6HhA/n7ilNh5fc6+UbAhdhnHjvoG7MbraLciNGSgbXQ4pP8XvM+TPfEx6tVzowtjBwCP/DsggU6z81XQIXDdsca7MHGIcz42kn7A/3IMWySQ+yatCivQ145jA7mCJRaenJTOkervbnlUJILD2hRcU3EpMQQV5KVbfL2FbS9MCXdB++Y75EmSRHR1079w/TlN7i3Ft3wp6XrVVM1vZmQ885vYjkHnSpL+PVw1v8St3d+vFZDgJwix+dM/FSBp9sO0AM9hIhh3JfhE9lVztZqkVlxhigZ5yW6DYfi9laN4pqzFWrumEcTlM16k9GcE7O1+DGOeONefTP8WeVE+QBz4hTUoqdqmYOqMwtQv2ZxDHQF6o6eh/a+PduCeFhMLKZggVd61+JpQyvhrsxHAZ3qI1eRFAtoeTwJUBrV0EQSMT27DxtBiiekrpbOAA==
*/
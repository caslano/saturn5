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
# ifndef BOOST_PREPROCESSOR_CONTROL_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_I(bit, t, f)
# else
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_OO((bit, t, f))
#    define BOOST_PP_IIF_OO(par) BOOST_PP_IIF_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_ ## bit(t, f)
# else
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_II(BOOST_PP_IIF_ ## bit(t, f))
#    define BOOST_PP_IIF_II(id) id
# endif
#
# define BOOST_PP_IIF_0(t, f) f
# define BOOST_PP_IIF_1(t, f) t
#
# endif

/* iif.hpp
jPcdgEeHVkBHpkOk1hOLJmMguBzTZBWJobq+y5zmhUTQsuDjzlNvK9PhZDpZxD8RBhEYzT+TMKtBX6WDiG1fO60JeV2FXfxm+IMmPHNYWEFXPjMKXSnva62DA9cMIv65vWggd0EYY4aANc4Wgzw7FFuia8uoNOtPKVFwrf9Sx6bAa3qdHmV9E/neKt5oe4FeLENB6dS81pS4D2mfjuXF9STAaDoo8ogzVNGRK2+q7KOll9AzdY9X5dFgxC1fMdL2uWGXUYIQpynWkveo+A3l7KCcX3tmAKKyidyRwXF5OPzs186Y0d2MszFXSwYMLVhoeP9V9C0NYtbmZehMyaPSTGPwU9QwrajGy4uF/uGuPi6qryBsSnjhNvYnU9lq1yO+6Egq8hLClJIb4ahpSTsd89ebq678N/lD/a2OHQxeH7Tc0WwKr5innS/YaYMEzEUWErv49fz5Vz7muBR6axDRWO/gbB6n1HJW0oTFuYq2QfA6vxuKLKMqN8FNtXQDrWTca/SnM5/HoHuRjO2a7qQHBH4evio0c9QlcwKalCB561BRZ7ltNm5VQIwkKg==
*/
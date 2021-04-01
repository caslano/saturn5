// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_FUNCTION_PROLOGUE_HPP
#define BOOST_FUNCTION_PROLOGUE_HPP
#  include <cassert>
#  include <algorithm>
#  include <boost/config/no_tr1/functional.hpp> // unary_function, binary_function
#  include <boost/throw_exception.hpp>
#  include <boost/config.hpp>
#  include <boost/function/function_base.hpp>
#  include <boost/mem_fn.hpp>
#  include <boost/type_traits/is_integral.hpp>
#  include <boost/preprocessor/enum.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/inc.hpp>
#  include <boost/type_traits/is_void.hpp>
#endif // BOOST_FUNCTION_PROLOGUE_HPP

/* prologue.hpp
oCFGv1LQqSXe16B9EbhvTJgXDCV6ImeJilOOjfButrtcHyrZt7vWK85ovOPb08lguXqcfpHrkzxKMkPZvl6vHhG2KgsDWw1vOqHiWd6O3TH6RG4yaW6XcTdU8/36q9CVlzeqmc34tLvuaKLOPSFtwwUuw0eP1vJwqLnf1wDJqVmUeAemoAvnwSxQRLOe97ARq0Pkd9It1FQ9KBgqqlj39ajZ3Esq2+svWHQ2tXU5bGFjmqMBir/NA09mIPtGu3qJq5HBYICYn6ubuPPLHmVOdZHIFjLAJB0pPw7tG5NwsqPWsmPpnfgyVR4KZ1vWbN7QMV2VxE4WXHub+waUtH6uZv1DoyoX7zjcvJb+WC7PtLlg7LcrVAnyBifebaMvahqcddL7kb2TdeTnanDje+5XBeO23dtNRSszP796uJ5B5ndXlD6AX8ynIh0RvMzfw4VZUWMGSRqgPhQAVqUQn2fY6pQzM3iEVotZxFLTVp9LMjk8eZiit5VIGLDUZkHHZ+Bb0hS/kOVWxBCGDGsLo9JsKNFyuYbWifsZv795r12dlZ7jfbFrJkSrWmXuNg==
*/
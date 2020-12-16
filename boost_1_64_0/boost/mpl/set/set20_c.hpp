
#ifndef BOOST_MPL_SET_SET20_C_HPP_INCLUDED
#define BOOST_MPL_SET_SET20_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set10_c.hpp>
#   include <boost/mpl/set/set20.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set20_c.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(11, 20, <boost/mpl/set/aux_/numbered_c.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET20_C_HPP_INCLUDED

/* set20_c.hpp
AbGHv6dKd4wK7Jio26AqvSkYa/O6KqF5880TdEON3pBf6UmJ5jBp7hanWd2v3zwwxI5qmtfU9jSX3hyviUc/6gMs+yU10pKqcztE2jlx2lVSRFOVeSm8pjanKajaZLr6b9hhXfP8nkG6pQm6Pp0c1rTm/2iuvSJOs1KVvJqkd9XpMTavq0HSdcXplvuOiMqqea/ChcXzgQwGg8FgMP5y2Nf/VzYe1NAc+9dntebt/2x5BoPBYDAYDAaDwWAwGKnFJP7/as97mHM8YTr6YGveQ1K1uXhdQJOmqLE5cEf0ZpHeOB19jF0P06M6yZ2yz6uZsy2YzwsjcZ5zbShAG+zvIei3t6EGeyx/2QjHtT8j7WCcNvYk2rTrYoPvmPZu5roHmo/vtGvrU6c27YgpLpwbd/PcryB91a5fFQ0HdeUkg+9kG8zrvR0FDLa3oVLfg2p0m+f3GAwGg8FgMBgMxj8Gdv//gKbqxj/y/P0/W57BYDAYDAaDwWAwGAxGapHo///RZ58mzv+fY86H7idFIt4uqULpN/fROqJnzX/T0aeZerQle27H4XjicB0ecKz2eDVZCbU4rx2gufcTbdpYZeBDj1swA6/0NWmGtOB9ngwGg8FgMBgMBoPB+JuRDjuYfOLOWW14m41XlaVIWx1WTKs9kl/G8um2Xp+mKMFIW0+k16dqeSF4tb1SWFUO9+zmLi4qKnYXutuUjsP9bf0lu7X5wlGPX46E85CCtdrwrcU0IdYRm8CnPr9dECf61nPDmtwjHymHuqZVKj1hOSipeBdORtZ7mUI0NDd4KsvnzKkor9zXU11/YF3j3Ho0Fx71nKydp+gambG9AOSPv5iGmAb4UfAbO2Jt9iLdP1/D45EjXo+31ysHvR1BySOHZA0aG2eW2cYjgxg4rkAItHVW1g+rVq3aTKTh2PWzFuOzhnQ8c65Xingi0bD+dDLJjyQjfwXyT9xZiBo8YCqqSrYABJ6ziPylyPfmYJl4wwF1VTJyqdyrVG846NX0IvoT/IwakJaN/LeRj2FEiCEUxevS9NMTxFfUuWbWGHgF+t4Nvutp9BWsaz2JMnNnY1+CT3V7IohF0P4L3cYpfpF7Hd4FuMYOQ+8NT1+61jdPNPS90rdVW1SINiM9q/nlKw6Z2TA1tPWjc8uL3ofAmUZ6Tb0v+73W8dx1w1suPXbXlQ8KccW1evqjr9x4y9mne6qOePuKvZf8kPMhXo1npC+7oCi/Zd7M1+6b6nr54Y1OqRRioVFP97mvneBdlvfT2V9JV8z5ZNdqIb4w0ufXbzx80s571Od0HLzRGgcdHMCzBq/X01846sVFq746e3ze6VtPueOMQxBSOcBI3/m80oXv7nvPl1N+Wveab149dQchTjXSo+sWbtSy0P/mpUNDB4082tEkxEZGewbrXrjt402mXPnMOrtMeXTqpdNxrRjHlxw+/SZ//cUXTXvikV2ePfROnJDlRvp5JzWtvG/qGee47/JcuX73ni/gGWo36OnFx5SPv/7Bt7Ovnzr6xXPTr8jAeTXSr7mws3E0fflbC6+aueqSBfOvisWpBrZ3ictg98D8dWmiFNa6e5oYnpUmFiNtBSxzB5dwwxpgpcgLg+fvgXzYOCy3NE2UwYKwIdiMPdNEM8wPE7PTRBXsItiTsFdhK2EZe6WJon3SRD/4HNQ3Ch6DucqQDhuAnQG7DDasG45xlaeJElgtrBX2JNJaK9LE/H3QFvBS2DistDJNtMHmw66HfQRbhmMZDAaDwWAwGAzGPw/O+/+6Wx3B3PuE/79Givx/Pf8K+LdJsj0HFsbiA41T9P3qmXHz9TvD9I+5sM9Q/9AL2fg+6GlsrvTUofWyNygfKQk=
*/
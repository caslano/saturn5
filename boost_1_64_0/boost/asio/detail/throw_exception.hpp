//
// detail/throw_exception.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP
#define BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
# include <boost/throw_exception.hpp>
#endif // defined(BOOST_ASIO_BOOST_THROW_EXCEPTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
using boost::throw_exception;
#else // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

// Declare the throw_exception function for all targets.
template <typename Exception>
void throw_exception(const Exception& e);

// Only define the throw_exception function when exceptions are enabled.
// Otherwise, it is up to the application to provide a definition of this
// function.
# if !defined(BOOST_ASIO_NO_EXCEPTIONS)
template <typename Exception>
void throw_exception(const Exception& e)
{
  throw e;
}
# endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)

#endif // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

/* throw_exception.hpp
9Yw9IxCjLrZvX12eFmfJt+9ZOr1Nq535ljwpIdFTf4dyJoZuMenTdbpnq930V2WC5RG7Tsp11uX2Ib1Ap7drtSveZE5NaG1JjDqOKbyJ3b4lqzgf9Lm155mq/ICEbKLFBL4NTz1L+29zxDSnu62PdH2rEtomdLN9X5dOmWLzRbe5vuaFCU9bfeQcJ/W5NgmbW0+Lvxb55uWTKtCfWeA4zZdm+w6fMmOazT9eJ51fmXCetcJ8/36uzz1Or8wz7wlLfnNkyW+MC3S7t2jVhxWxoxI2MvGwzXe3rY6l+normDt9KM850/7b+MZ+CduGedovRwH3yQoa3UZ9w6VkW47vW+H5KSsQ+25yeusuxL77zNuXS+C6m9PZqfrbsOaOcD9LWcIzAp50eIgzd3F6SmpwDS2Mr2KTQBy9mlo+NJ1x9ISvVt3jOo7eCX3Cv+d7k24j/iVV3Lq34P/N9g36OmT/HsVmqkkfTJedFfoNWuPxDbrAReestsm4dXrea399eWeaGM9GL+3jVs3Xc4rrsW0YPbajtR7bNze3eeLod2/Y+4xbe9UPuKXf+V76al76Z156b/88vbTm6p+5xxv01m/7wUIGWzy6Kq77qsSjq08w8ejM//yWl//BTYP/83zTx7VQqvnf/+xZBM9A9YawnT8k+D/PE/O/xJST/SdZW1sUZj8z0NjZyP4RmOLCt6ONrybK69Xb+bxjj7FX4l3vzja+NVFcb6Ql+wuyR1HVwhhl1MvafXTyVtVGbt9gqE74thQ+uz7jldKeq8CNwavBLuBiWz2NUbbHOieK9pj1Pr1Oqfm6q/aA6sgVe8Y9wcGS3gXMB3eT80XgXuD+4GiwVNJlkj4MLACPAMeCc8FCcJ6k54NF4DmSXijpi8C9wVfAceBbkn5X0r+C40HV+AlgBrgP2A3cF+wPTgT3BPcE9wIngXtL2gceAE4HDwSrwFKwFpwMXgxOAa8Fy8AbQR9YD061x86TfhZXTSH9fK2NryhKvqoo+Wqj5KuPkq/RxoeMnrGL1kbJl3FudHw5UfB1DnyLy2+JRWExhCrE3noWuB1YDY4GZ4NjwMvByeCRYC04B7wYPBq8UtKLJb0SnCfzrkbs8E+SebcA3ExiBeaCZ4NjwFpwHKjt68EjwaPAi8GLQFX/EvAc8DHwPPA1cCH4FXg++DV4OvgzeCb4K3g82AZ5TwTTwGPAPuCl4FDwMrCrtn+MrNscsIMs+wo9yq+ap+t89y1xfed/s77z6lv+nTrPzYn/E43eczDmT1z/+Z+m/3z3V8gMJa2lL6CJUA20DGqAPoYyvkYWqARaANVDa6CUbzgPlUG10N3Qasj6Fpm/jetVx4/4ET/iR/yIH/Ejfqhjw+v/lw5cX/b/W9ns/0sS3HWSG06NXicZ3iZ1kh8+tWU6yYGYPwtaOeOYDRjKmsopohM4y5c3vrC/b1TewPHF40YV7umxH5qp2y3luFoP61C995grMuZqnUc63BbzrdUCxXuKtb/Ej5O9UblGpuxZGl02s7+4vS5XhD1FitlD82VEF/9D4om57jWNBGkn52lnWD9Vi555o/TTk9BApfe/IODToXn95C+3J+usHUw/hewVC+9oG28vq5PmHekyb7pI3zysee+3evP3YOhm6dcic51MMx5W2Hj84pfF6km/VkFKp+0MOvf9RNGbSzw6bdu0vujMtU4Lq9/oGeboednLdd6Wk99H528lOnPE7pM9xVs6+nESdHPHyOOo9hD/WGD2ECOOa/geYpH9noj75/1b9vtu1vt9wzKO3ffOvvOm3br45LsHPp39q9f+3b/H38T68qu7vvx0aH+Jtn3AnrIPKPtTvGuC+1M9W7g/NceS5zc=
*/
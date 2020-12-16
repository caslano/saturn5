// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_ENV_INIT_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_ENV_INIT_HPP_


#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/environment.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

template<typename Char>
struct env_init;

template<>
struct env_init<char> : handler_base_ext
{
    boost::process::environment env;

    env_init(boost::process::environment && env) : env(std::move(env)) {};
    env_init(const boost::process::environment & env) : env(env) {};


    template <class Executor>
    void on_setup(Executor &exec) const
    {
        exec.env = env._env_impl;
    }

};

}}}}



#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_ */

/* env_init.hpp
QPSCR+mbcWLw/vqw9w5rpei1kfCqtOO3++kFEl4T3nZEi99NkX5N/qupgtD3G9Li1KMctK5Uz76Ov5HwF5lvAyE/9bmOA+9WupKu9emYxMB7/iXTQ89sN2NvYL8DrapwjKE/k2s6Vt69hMLYRRgbAmFELzkrFMYt+n4mTXU+T9c1ov5LnvBHdfbHRbt9f7DDbNomtD70khfNO58IndPRuT8FnfrL0kI6D6SE60xFZ0oyOvHL64d0tkSEszQUV9yyo8eKaxM65wbCqbfsfVNOETp7QuHELnvTbU0rOnzY13KIWvY7f3y839Pa/VuM008v/NyVGPCzPNUfH+P39HL340zLxLaalvrLzzhWnhahc2cg3HrLM46lsx6dHoFwGqx41+27jdQ/OvcEwom59LHIMl7GntZTsZ+frOtuzbngut+0mgdTAvz7jVm3G3GW+G8xd+k735oUCI9iTkd2NdyG7EWIXGTDMNuRJcMUTMDtoRQxxv9C1b8e8zCyy+CjmB38fbAR+YM+8W/vnf2o6j0GG0asJ74RqiEOO+yd/P04ZpV+I7/P8d38NzBgfovZhblRZboeWfiEbZd3MGsTT2yP7BcutNceF1SH1vH2Nntan2PL+oVkZ9qyviHZIFvWJyTrbst6h2SdbFmvkKylLesZkiXbsh4hWawt6x6SfVtlZBkh2Z+MrJdJ8xO2zKR5my0zab7dlpk0X2vLTJpX2DKT5gW2zKR5ji0z6TurqvZe5ANtmUnfKbbMpK+NLTPpS7FlJn2xtsyk75vK2nubP2TLTPo2V9be23y9LTNpvtqWmTQvs2UmzfNtmUlziS0zac63ZSbN4ytd1q/bMtMOzrBlJh8ZlbXP7D/Jlpl8NLFlJh8bqsPXuacik3dF5qGFV8j6TrnRQuSOte4yxvk717oH3p+JnnmvpnudI+d9h/M7Be86VOZ4B4KcdwXue5S/YMLWZ3qVrw3Tt9/N7kBuvl+obBayacmh9FWKbCmy3SnIQuNEZBuNnhkTinwFcpnL4xh7IWdMpfN27LGWyDchbyP6Zmyl4WhezLhJv6/oe+Ia3Xhhlc7nWQn7UVaLfxqom8XBjU8Cn92Kprl8R7fHr2+LfkePy7thDcuDTL7j8RcBsrtH6Fk2Ff5CdC72tCR1IzFLrP2u7+o1LPvbuTzTuX87d+reGpw3N9f5HFt6UcB1MsOQaN6bnOJ8h2++GxyUMNJkXPlicugbpD3+ridhvG/dYLVRGXaRxXrikTveseFPDogxY94uotecuGLNfJug3ySP/cw6N7+4utCMYzeK+7HjuinRxEXrsJ/dkkVvPzqjk3L5NlDche+h8h2xm36fcIy1VGd9SMdTEvjgztZH/vjoY4211M8u/Dwlc2UWXxw5jhqDPVm+g9hmt85hCfx9n2OO3e/4+/cq/4PyRsweM9flx+e3uH1LSdX+hHaITNth5JwWbVPy7Uq/Q5afEgy4GuPRPiqXMNKDe1xVFkofpN9Sgs8K2F2/P+Insg1X0qTsNtVe3Mus4fzvdg2of1MPrVPcvy1FHaM8qoJ9mOkz40y+JR3/F2cpHC0MyHvsGJkWU7L7tjYP/OHR77cO/nXdWQp1Zykc31kKX1r8PLX3DDk32f67hy2XZ9Zy2TuC50zH3xscf9/j+Hu942/n3iNT7PClb14Jz8E8Zf/NewCjI3Mda+BVmLWOv9fZf8u8qiPkJYO/tzr+vtH+W+YG7YWLSNOt+vdK/j4MO3l0jrrOed8L22JaaPl8z5brfhjlsxa3gzHwVBgHs2ADOB4mwakwGVbBRnARbAJXwaZwDWwGfwXT4IOwOXwdtoL7YRv4CWwLvaThJFgPdoJJ8GSYCjvDprA=
*/
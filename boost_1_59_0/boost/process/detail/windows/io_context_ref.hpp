// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_IO_CONTEXT_REF_HPP_
#define BOOST_PROCESS_WINDOWS_IO_CONTEXT_REF_HPP_

#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/windows/async_handler.hpp>
#include <boost/process/detail/windows/is_running.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/windows/object_handle.hpp>
#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/fusion/container/vector/convert.hpp>


#include <functional>
#include <type_traits>
#include <memory>
#include <atomic>
#include <vector>

#include <boost/type_index.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<typename Executor>
struct on_exit_handler_transformer
{
    Executor & exec;
    on_exit_handler_transformer(Executor & exec) : exec(exec) {}
    template<typename Sig>
    struct result;

    template<typename T>
    struct result<on_exit_handler_transformer<Executor>(T&)>
    {
        typedef typename T::on_exit_handler_t type;
    };

    template<typename T>
    auto operator()(T& t) const -> typename T::on_exit_handler_t
    {
        return t.on_exit_handler(exec);
    }
};

template<typename Executor>
struct async_handler_collector
{
    Executor & exec;
    std::vector<std::function<void(int, const std::error_code & ec)>> &handlers;


    async_handler_collector(Executor & exec,
            std::vector<std::function<void(int, const std::error_code & ec)>> &handlers)
                : exec(exec), handlers(handlers) {}

    template<typename T>
    void operator()(T & t) const
    {
        handlers.push_back(t.on_exit_handler(exec));
    }
};

//Also set's up waiting for the exit, so it can close async stuff.
struct io_context_ref : boost::process::detail::handler_base
{

    io_context_ref(boost::asio::io_context & ios)
            : ios(ios)
    {
    }
    boost::asio::io_context &get() {return ios;};

    template <class Executor>
    void on_success(Executor& exec) const
    {
        auto asyncs = boost::fusion::filter_if<
                      is_async_handler<
                      typename std::remove_reference< boost::mpl::_ > ::type
                      >>(exec.seq);

        //ok, check if there are actually any.
        if (boost::fusion::empty(asyncs))
        {
            return;
        }

        ::boost::winapi::PROCESS_INFORMATION_ & proc = exec.proc_info;
        auto this_proc = ::boost::winapi::GetCurrentProcess();

        auto proc_in = proc.hProcess;;
        ::boost::winapi::HANDLE_ process_handle;

        if (!::boost::winapi::DuplicateHandle(
              this_proc, proc_in, this_proc, &process_handle, 0,
              static_cast<::boost::winapi::BOOL_>(true),
               ::boost::winapi::DUPLICATE_SAME_ACCESS_))

        exec.set_error(::boost::process::detail::get_last_error(),
                                 "Duplicate Pipe Failed");


        std::vector<std::function<void(int, const std::error_code & ec)>> funcs;
        funcs.reserve(boost::fusion::size(asyncs));
        boost::fusion::for_each(asyncs, async_handler_collector<Executor>(exec, funcs));

        wait_handler wh(std::move(funcs), ios, process_handle, exec.exit_status);

        ::boost::winapi::DWORD_ code;
        if(::boost::winapi::GetExitCodeProcess(process_handle, &code)
            && code != still_active)
        {
            ::boost::asio::post(wh.handle->get_executor(), std::move(wh));
            return;
        }


        auto handle_p = wh.handle.get();
        handle_p->async_wait(std::move(wh));
    }


    struct wait_handler
    {
        std::vector<std::function<void(int, const std::error_code & ec)>> funcs;
        std::unique_ptr<boost::asio::windows::object_handle> handle;
        std::shared_ptr<std::atomic<int>> exit_status;
        wait_handler(const wait_handler & ) = delete;
        wait_handler(wait_handler && ) = default;
        wait_handler(std::vector<std::function<void(int, const std::error_code & ec)>> && funcs,
                     boost::asio::io_context & ios, void * handle,
                     const std::shared_ptr<std::atomic<int>> &exit_status)
                : funcs(std::move(funcs)),
                  handle(new boost::asio::windows::object_handle(
                          asio::prefer(ios.get_executor(), asio::execution::outstanding_work.tracked), handle)),
                  exit_status(exit_status)
        {

        }
        void operator()(const boost::system::error_code & ec_in = {})
        {
            std::error_code ec;
            if (ec_in)
                ec = std::error_code(ec_in.value(), std::system_category());

            ::boost::winapi::DWORD_ code;
            ::boost::winapi::GetExitCodeProcess(handle->native_handle(), &code);
            exit_status->store(code);

            for (auto & func : funcs)
                func(code, ec);
        }

    };

private:
    boost::asio::io_context &ios;
};

}}}}

#endif /* BOOST_PROCESS_WINDOWS_IO_CONTEXT_REF_HPP_ */

/* io_context_ref.hpp
ZFTkHazW9Mr+wDpRfp6ke58LiV7XKOOyv5u5VGs1M49evz6UlHYBwT1zaoZjhnuG15qp1hP+wJIO3MbkbFKOpfYUPSkNDHgXnoQu2g8V2kQUjtfJjHJvU93V8z7zRThodJSRr2IS5ldSAyoYJNm+yfe0iTSP0CtNbicIG3phxwL2DRKe5SLX4OyPxsIaJzqeg/S4MXnCkyvw3TOWTN5zS4F9u9Xmg2bFleAozjuzd3UxXcEMobxU8If5VVEkS7uKEVdWESBFJY+o6U9iFsR/onlZt7OGkryWgzyZ348aWMVxUz4t43oFxpYeUJJ6NGWcaBQEK7cUHEQcqncSvXpeXRhE1DgoeEO/d40E4iZ7vNaLzhyMAoTxlPN55rXKugPK2SZraVuwS0t0UZgAgxVXQQlcM73Btar9SHCeUoDspp1/roEaGYJu+nOkHCV5BUApTLjZJEAZVSgyoFf/euu5pveY0WveUooARSrLIdU8IbooYQDxIPlvPmVcLc7Xr1hfA3XV3Q0jFvcG+htnKJLloCecjDydZ4m8srW8oRAIvb5YmDvflnOxK3RcYZtmgIjF0g2Gk1fdgeOIbzE4DkDeUd7zdFQoJkvOdAWdqT5jfmc1UrDRajDo1epucI10L5nwkUDIGhBq99iZftiXcY9hi3lBik14zHSu59FeQlwAszim8LCPGrDHW8DdOZjSDPcm/TaSqF4FjooqH4Vw7VW5J7cYXeruak7cVFab7aDyILqrvPMwoU/3H0L/afrj8wPM/iTba57/2u4yTMPlE1VkCt1TZ1EDtwn1Z/f8+WpiSZK4oBmfzll+YidVoTzr0AYTVEFPf2OfJHVhMulfFO8k/HAuuHABfYL6EtFdpt/NCJQmuy5Bbm/hrcDyzpoVhAarskytzwVyMlyKf/du2/Z0Ra4Gat7cswwNlr0ZPiX6N8aDYqr4m2xZz8pHHMN54O9mthNuYP7iniDHd/iICtkYsmYHRK83F9L+RY/S+ogOeTuAuLX+erVWzjBViOHzr+8qMPox5svkb1Beb7zKVtnd0OHEsB+sazIW9pmmgEpUVIHNLtTCPiD9kl3osMJdcAZfX7w1/ebz/Z9c+KeUH03XQisIt13v7i+PZez/XOnc8JU1XWH86I0wP8reVH+ht+88meH3ZLXTacwtd/+nCB4TvTeaO6g+NIzRM2mwMywv6iZHrgwxru6IK4Pr2/ZSssVlwX9QJrspx8eK/bK+fCXNZFsjfOJIDafo3tWISev9/ZCkLqSGN2OwTwB7pt5/Q2f/v9HQd/sNdRBdUcpRhCW2vusgsUTi9hJFWw/xhNUikamDlAg4TZzN98X8vtHA5JiEk8gGmtAiFOrmvtAUBvWBt82UBD/5ovMTQ/dndhoDtt0I2E7ND2fqhLPKN9FmCanqxTLzDlukCTWdskBG5Khvx24J5h6wDVkk950a9vU9XU0D3FlrCIb9wyYAhObqNcIdXRTzsurlXHjPWQl4+jhcCXdcN4mgJOEAf8THYqhJb/f350M+X63iErQS0Du804e5IefMq+qWAx7mKR6XFL7PCKF4v9Kt5trft5vlXI2e4TC4JSSD8SjVS9Xu8OVtlRhLnhpYFTsBfvMTFbOfUky4ngE4h3db/fZCmMib4P303B6HpSQOUyHXQLW/cFRS8HgbJjedLzxCtr49ArGY3UXOdx21Lr6MgCp93B/I+LpK4n3VqYNJIjkVg8C7WuXZLxQfYbwMmAVUrhCoUh559Ub0UeR0bsnZCEIvT88VbZHzPyMa7I6Soqgkz06dkTmYzKJchUaxo2Siz7nV6fc4SP1O9kBRx568hg75CIwn2+x3apy8TnkqWdZftNo1qIy6nPWl6Ynd3G0HAHgckgSBZnd1B6yZU3Sg3o/xFAN09+LFZPUx0DNya2VFXewPGWHUtl7joUQXnVUbaDTipp28IBxRU+Fs9xBu/BOUwfgQ6HUPfh7uSBLfVdpEuFWVxA2ffUxGKXki+39h4SKl1F2tfYnRdK7D+O2wwGOrqLThpIf3M8x2BIb2/b5yeeojncBro9wJDY+ZwtliNJ28b6bKWiHHCaGfhs2GLkLcXN5klYHrBvp2yDW3rMcG3XOyQDJLjTHsxis5COGAPAbAUdXvNOlUaRi4MZuklGfsnrbmPBXM+lYg02L5Z68Z+lioFwF9Pzykt9WjWVCY9XSwkqBag5ppX5VL9Wy9OU0I+Zp8+4FQnqXYsq+LzDXUSuz+WPS6ucVwsbL4MtF/N3Ycc406sB+trLP8TypOkfmxuKMOGTHisIV6k70Uf7QL7TsxKJQVlaItY/eMPDzDbQ+j728fd4i4ATtHbah/5MDauc/cn7ViCqolGUuBvM9uGZOHOze2rifLel2FFq2mW4GANzMMHIDj5O4q8K/1zS3iP1yhWyeVWuB2sEr0A66sjaQOT6bJQd3Wj9pWiJ1dhKdfRVPQKQUIItYJRIHsry+v+P83/819DzORJcq0lsEhAuOwhG771e1jJsoY1N/v8aOYVCv77Wa3oGHGJabd8j41yEyb2FL2n3i5VbNM0HDgzS1Ja/tdbAKKMsRSc/vNyN2urMKEzZWjI04Tl9sPoMYqRmnzyYFCVfyQywEniHtnJ+Zj1omh6IoAuc1hkhKVYSSMC4ETpcqJkSbPVDxLc7A+ixfWG38ZrB9f5yaYfcQovElO7Jjjytt4Z3NxVrc8oybcXNVOpUgXEAsXvoNGJKRiKjOSipjzzuEXMA6DJ1wootyqbzbPukd0/9zotbnYbbcg+Se5/udGEMe+0ZYkdcHooxEAuxxXNTE5TWquOoTMRyw0dG8OUv+RUgKRM9HWLM0gVcvTq6Y5dMNd/dKQkOqFZm9rQo/kH5/B9ZHEV6AER4a9u06Tak6Juw4ksJlUGBcD2LJ8v7ergLE419lejK8Y2ds1siM0r9f+QcjFx8U4rIeBKU1MavY2yX7VZu1eb23c2U5IccGn/dKatv8ga0eapR++IpL8VwUcQWTEZ4rOURP7FFuiNmg5C/GmZ4eAGofBTuMLEAvDAZyFFlx//60LIgRE9L1gEd7pF0y014LPHsahzXkIq4f8/pSxB75qMMMLAwTFiyhUSp/QSI/bjMHW92pT+vxrhaoIz8NhBkJml/VYat6NfeBeNbd4kBFTLvmuIXsMVmaL1YzjElP506+pGuGdqdHLm5dpBIwk6BrvPZuvs4d8KzD45H0uvvu7BDnlQ23v1gdIaISoRtF80UCDhpXsgqyDZHLtzMRHoqvnl6harYObi7XsbnBeXO0fNdY7WgexAAaQmJQaDpDB+WhuaAbv/Zo04ryX3b/iqb3tNS1VLmXx0TeiD/4ORPEvcelBfEBvcQx6Ce2TWSewAe+TMhYgxL8JQqSGoiF5cSB3J67a3vLZdRCCKqED8mmdp4a8ub8XWt2VF44K0eEkjzKU0w5HQxo0w64sGV2ZCmwXTs5CbGzBPjY8GZh6cvR7DNq/OpesCdf5VQ0YpX+rCIkffGTkCX55Eavg/ZQ+7oxVeHkoILl4KHB/1Jhz26KVwxm64m8Wquh3Rx6d2pxu3OvfcJH0xCz0bpowzLNDH+89WtYR8e6q7mQwYmphFgZcLcaS49AVB+IrgxyaD/Dpm2QeyXy8jrhxrR+EalWKdgCoLKr9R7uSsrc0GJgA5pV4wSjdIKR4XoevpG1icaUzWCY6uv5wV68qm6m3HHYo+ZO0Df4qXHsxfMH+0WrOvjOPzL5HDSikpiKsSMI5YNNtwygOKKJQOzdGuz4hiyTdwxrFBdlMHFDSJNZ5FSBeyMzVrlpvxt0GRWTgadJ4W+3arD43RssrxPdo4o/d623JCYL+IpcOknR693NUC2ptr3Q2222yz15JrK32WR+7/sRIcHhtJTWQdcPuo89rmG6E2dHEZrhgnE9pDcZ5r3R0CCj3waf0OkDhEkbrI6k9kflxO2auMsVsQzhvIVyhA7TQVWra3Nm1/DGON56oJlG4r7+rNE4bh6TEbFA1I6yaBrWSh0h166dJedWOmerTtzeWY6f9FRpon62DrM4tpXosFdTvQaLvU4jZqCTmaFya57/a9eXc85esAvaGZshWB3tDQRW0Wq85spB1ALrvx2Cr1vVYspexs+3OcJ2Pr1UAOdziLcAzy02gTeu3gOkEZO7vR2KJc1Dvc5S3uMPu6cQ0d902St4VdKIeU1bLybA39Hp70bMinTQtxIvDpi+oE2dG/qOa//+Xj3gDxPVFMDOXktYuhz9Rft/DffGa+9ejkqYUy8V7I2s/pFfPWorOVDWrCmWMePkh6mdShNQ8397hPS26+ulXUbRBx7HjyyrjOWZSK4afL+X9d/pNy827J7L51Dzp/uEYH4R6yvTAbePZa7b7I4hK7f89iAM+KNT9XduZww+JuJcZiGufLYVCBm1l4UOQ657a3GoO/4bXVOBWDa+CKA/FW/zFVk99RrzIeSS4XL8oGGqPk6uw/Cej5hArgfVvIqY+Ki2gnZRd1fxnOZLkm14Mub4f+FfJwXB1/O8V5J81OQ95l61iSr+l97cPlIcXfQeSbjnEVooz81s4sp983+MWXt7dn1rt2qX3ynWQCs9Oh7VaNVvfbf4spxG6JlDS9Dgxz27X6ZnPLZsm/Lz01jLjdkK84MK33oO9BhGCgxxqi33o9SlyivDoNL3RFT4WB3PstSqk6Q7F6txxGNFweOZ9juDZKeBd4cv0tZzsWC2VAuSS3WzaZmzWTnb4zsVlWmgHjdXx35kZPgmxPQ/d9fhZXdvbvWYaHPFwoV54JcuYZezwdN+ken5xdOMcaCfiqp0QAH2NIM9UsMP4a8x/avLfV3xuuTAdduflboXXTTc3pXTvBwse1MAGPkAj8qwOxaTh8cJ3Kx+ujv3BoCqv8C+/iHB2Q94sRbvJs6CfH5KjCEVB3awU9kKaxihaDrLJfzEo1L5HW0YJ88PhodAy9kSmuiwhABxFOQvFc1+UCB8rkQNIihq77VawpgP09gd9+znAC7Vxyd0+rToMXQkCTcIMvObme/7wwtCh0BtW+yvblldj6HDuLb8zO/Dj2mm1n8EbhP/m3ZY0yrxsTFzlerHpGJ6vcneacy4kwOm3aPT26bHBFfAn3s1XXy3CeCbQWwHQTrH/IjZC0FMGRXcq51syvG97G+dLhFzolsrBB5+Awz6sP+BGcisNRoXwFt9ptnI4DH/Mi6+7S9z59OGQz7rOf0i6Kyvl9jOQvMBfko7EELHsxV7+S1CsdQSlYCsMu9/aFoEMoymqu7QK3we/+qQdHdzXAM0+gxoDtmH4yabEnn7m+u88P+CMWNY7O4HelDpvPlLhY8V2CnTIGT6Xn2bQZq6hC4+79Qz/Qb6MILuCPUUgHgUJTFpqex2G6FqAxqU0qIbKJvJTsKQ3Oj+FRvw1FZUPI1q6myfplIvbe2RsRI54ROaE2TF63s0+yKOjSh/YWVjhrttZ2GAqMqJsr0gWnnUG5vnPza0NfiGBoLG+1wX3DEVuziYLMbfjj8GcmBJA+vfQwucfwXZLAXb06cOT8Sqml5gBDGVG/iL6PQj1aRQnZFIr9HT3PeGhoKmqw81vMr2pr8KlKsKYKxpPHF4yHtPV/91jpUqKmx7l3vBGGd76PbT6Xv1Rn1Wm8+Su+npHRMbbFDtMuhglNc7N/OjKB8CToyvXUQ//IZKA0HTEvpxa9ltB6IMp5SajVcsavvUsmfvQ1HI9eee9nt6r51k2ZfbhwwHil1Do+Ux41P3wIG65ImUhUzJrEX/NNLF7+JYgEPS4f8Eytf1c6ouNTYdZa1c7hotRvHL4QwWG++7bqQXg5Fc94kF45adJC3yqNf7ANqgjhhvmgHH4T6J2CDBFHmpPzKCqnISsc2T3QUO86ZoneIt2l5xbYqLQCg5jTHHrQxjhGYwnvPbVA6SqA13zKWQqFKFTtH99gQlEmYNymeI8u5QPy+jcHW1s5zZU10y+64xOtlX1TPp8Wni1xsIDR7UMoT9ZxUVUuwc8LlR1AoPK5CrjOth7T7wSEV6yqEdlXliiHTC47/GKdvDHjf36hRy0rC4ue+kTamE3PijaCVNN8D19lzVJTkcyTSMA372myN8qoyXcfFSWYm9vs8yqxEK/uU9K7RJDo90HTWNrDjgwoDhCM5xf90C7pxhqWEWJuQE+3rxEMGNe2Pa8G5VTj3oHuzCjBrimtRBPy9M594PlckSISjpcatxS/680ZhhY5dZGPPJt5kJ76dO+r/uIbXKFuUqXOU+LBi08K7uA4AAlvZwV9UXqQ5vPeVSl2bUtE+YuJjZVomFvSVGKF2rTDm+HYx7ETmGajvRr7JMiGnQsRNLu0+r7M3mnOvcERxVdZivLBMjJaeiwybiDNlslRv5WlNf0lp5XZ4hWHIUQKomJuLBdBJTIaBpnElKiisz3yJisPfIAordhj5yXjpGz79ABcGE6Az3pjM/qrexhAeTozPdYlMPht/4ODMGgMSqHw93naTNACAYbDz+NajT6vQ09FZb6i12atuDo+1qOquBkp1WODGs/4oF+dz+NGz+iXZyohF2is04tmg4toHqjlwlGjbE1lxF3thxeSDORXIz0zfy/W6+3i9Rz5l/+TBIzHU5EEfRh/g564O5y0yXKNqI86LYOXMzW6xzKWLgkzfzPFXWt/h2VpCculBYb1RmxG66E8F9PtxHaFr2b5JEJkRTY9KRIuD28NexKWfYPeE54pXKTZztk7AuMxBLZimlPSfsVwr91Na0R5FBNa9Oy/xNpqd1GZXJIWCWPG3WG1FAsKuglQe8OfuSmJdK4btidQ7hgvAKy7mdn/5Ui/f0aKiRncIq0vQAKLPXTWgIP0a8XxhxcGzcv25LDvYmWnZMrQyxEDJS9Z3yvvRX/zxTleXNPrZH8ah7nXf95t+vkUY7QpEQxXXHghebvfe1k0sFX+o6dPIr4O+x+1J7Vfpp1AK3SaiVYpRRowfwaVA+FGGTv72sT5HYbE+UnUzF7ePFS6KRFWMNjlPY7Zgb4VL38AmL8vivgqD3O7+fxMbFTr5Fff2GfHEKLv5lp69UhXQSG/zn356kVqew3r/V9Ag6fgVYOWi2sDvtVZP5x1G0ETk94dVBWN6tL3XxjG9/vgKuiOrms9+79Na3uv2d/CRs8PsbMfyHvcHfBuArwvQJ2rqwLdMKzki8w27BqO+I/FfTVhhOT1dl3A450fmYn57GKLrymKw3HEmML7dwjHTSGUyn/+afl6coNf/OPve3wymlFid+ywi9dNWadxtTKSamOhdy8whWP1ZJosr2iCTL4wroZbDfVugm2oP3xrlWmW9YM/hQDdq3TTFcAcy2rXJjL34IDliOEsEzzoSLx4ojnKOzKcvJXppKrw8sO5KPmBcuXhtNpA7kRzxetRdH0899OvXYQnHJnz5OIipjuCOsr2e7b71OIH0E+qrZ8jO+jC8Pra4AqWFBTxPN7sKbhq5kAT1teHKcgKuy28Cgh6PTmTUoGEQFK2252xglI/JF5JvnwT3Dk2OVUI6/8qxuyHvCVFJ0nEdvB6surUNWgBQkaUWbHNR8ZF3Mp1BSrFgCzSZA1vc2Xt5RP86od50NIaTlcklPr6CWNZIdAR7KenPfk9w7YLiVPbJMiJsyqVT7XqVoZhJQ/G1Bf
*/
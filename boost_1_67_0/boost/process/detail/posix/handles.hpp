// Copyright (c) 2019 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_HANDLES_HPP_

#include <vector>
#include <system_error>
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
#include <boost/process/detail/posix/handler.hpp>

namespace boost { namespace process { namespace detail { namespace posix {


using native_handle_type = int;

inline std::vector<native_handle_type> get_handles(std::error_code & ec)
{
    std::vector<native_handle_type> res;

    std::unique_ptr<DIR, void(*)(DIR*)> dir{::opendir("/dev/fd"), +[](DIR* p){::closedir(p);}};
    if (!dir)
    {
        ec = ::boost::process::detail::get_last_error();
        return {};
    }
    else
        ec.clear();

    auto my_fd = ::dirfd(dir.get());

    struct ::dirent * ent_p;

    while ((ent_p = readdir(dir.get())) != nullptr)
    {
        if (ent_p->d_name[0] == '.')
            continue;

        const auto conv = std::atoi(ent_p->d_name);
        if (conv == 0 && (ent_p->d_name[0] != '0' && ent_p->d_name[1] != '\0'))
            continue;

        if (conv == my_fd)
            continue;

        res.push_back(conv);
    }
    return res;
}

inline std::vector<native_handle_type> get_handles()
{
    std::error_code ec;

    auto res = get_handles(ec);
    if (ec)
        boost::process::detail::throw_error(ec, "open_dir(\"/dev/fd\") failed");

    return res;
}


inline bool is_stream_handle(native_handle_type handle, std::error_code & ec)
{
    struct ::stat stat_;

    if (::fstat(handle, &stat_) != 0)
    {
        ec = ::boost::process::detail::get_last_error();
    }
    else
        ec.clear();

    return S_ISCHR  (stat_.st_mode)  //This macro returns non-zero if the file is a character special file (a device like a terminal).
        || S_ISBLK  (stat_.st_mode) // This macro returns non-zero if the file is a block special file (a device like a disk).
        || S_ISREG  (stat_.st_mode) // This macro returns non-zero if the file is a regular file.
        || S_ISFIFO (stat_.st_mode) // This macro returns non-zero if the file is a FIFO special file, or a pipe. See section 15. Pipes and FIFOs.
        || S_ISSOCK (stat_.st_mode) ;// This macro returns non-zero if the file is a socket. See section 16. Sockets.;
}


inline bool is_stream_handle(native_handle_type handle)
{
    std::error_code ec;
    auto res = is_stream_handle(handle, ec);
    if (ec)
        boost::process::detail::throw_error(ec, "fstat() failed");

    return res;
}

struct limit_handles_ : handler_base_ext
{
    limit_handles_() {}
    ~limit_handles_() {}
    mutable std::vector<int> used_handles;

    template<typename Executor>
    void on_setup(Executor & exec) const
    {
        used_handles = get_used_handles(exec);
    }

    template<typename Executor>
    void on_exec_setup(Executor & exec) const
    {
        auto dir = ::opendir("/dev/fd");
        if (!dir)
        {
            exec.set_error(::boost::process::detail::get_last_error(), "opendir(\"/dev/fd\")");
            return;
        }

        auto my_fd = ::dirfd(dir);
        struct ::dirent * ent_p;

        while ((ent_p = readdir(dir)) != nullptr)
        {
            if (ent_p->d_name[0] == '.')
                continue;

            const auto conv = std::atoi(ent_p->d_name);

            if ((conv == my_fd) || (conv == -1))
                continue;

            if (std::find(used_handles.begin(), used_handles.end(), conv) != used_handles.end())
                continue;

            if (::close(conv) != 0)
            {
                exec.set_error(::boost::process::detail::get_last_error(), "close() failed");
                return;
            }
        }
        ::closedir(dir);
    }
};

}}}}

#endif //PROCESS_HANDLES_HPP

/* handles.hpp
Qgd+lRBcHcSzQ/iT0KOUpBXczkWt2S8GvAoglGQCkieGY950VI9XXBrLnjhXgGWuxLFlSWdJVChXsEgOzbmLw+sd61cC9iHCJixXYD5+I2J/NHecxo05+1hGGJIoHyHLKzyTWy9UaqCZfHAMdHC2aOJMROJMZCwgl/RITrF4ocw7tKRrc+b0mMKKJx9zMTjXZHPhWRvRDdhBI9IKtD+V7lzSw7UkEIrnwg+qJQMlv9VYE9SCjcw/sMc39/08ax7WeX7SYjBBD9ForDb6Na32pPyBHjXNn43vIag//Nj8teEf5sw/ZPtbVRQ6ZQnAklRbv6agMNv8QrYlZaw+n7aredHuFpMdBDz8l0kj//DyxXs6DS30qwqKEpbyGLClTABdDjrfnJlZrjkyr5B+S55nyL3zubYt2AzwzKXlO1RK/tUR18YXgtZGHpkAca2D/aWGPnQ+9xKb/43tb10cdsD3lfWW53sP7s+y7XwfVHtyJ4efSzSqfJDsuevLWpXprfc5rl6Et7XrIerD7sZ+kGLH1HWIHmqLisViB3N0TwbtibZq0Vq+Ktr3B2bRDUnoXlSOS1cEhAf1FZdcbn6m/9I1n57BNVvdOdqz4eH57bVdG1b9hq1ia1v6vLzz1nNHS7XmTtkA2A4W2WZgfQ4XmUK0U8h+ZIXEPHvfKmlpvq4brcE93RolYPpLDIX3hZcBRHd2Kgba4aSX70RIxNDSlXx3tq6PAMAuDXPFx3sXOstgHAnUPlS/bPGF2ivx+g7570RaX74ZlatX4E3TB4WKjf13Uouq6iod23mJ+0GyUMDnG7fE5Ur6w6W5Up/fXymGSF3SWp+md3vhE7sbEhltUjvJqEyq1v0iqCsN86hEcQdQP3XmxbI9bdzZ0gAsiQcCoU/KUBeF/q+88kOl1W7mrJS8CrMOqlcQp3XtGQ1vrhMRwv48W1VtMhfNGSHJQsvxEAHkG5pjkVmy/RgHiAE5CQzODbzGjRyDhXaKGKCure8mNaGWA4bWS0UOdFjHnmHpKSJczuG8FIrrUCy2CNDwYvnGNmrWTQvX7Cr8NKLsnSIDWHmdWjkIZDzKljZF/Ov2pB7Ky71nEe7ZdHmW+dC9A2pMDibSNnL3T3pp60FK55ug6UhTG4r3jblE4oydUV5gXEMODcsX0fH1dKFf9QSM0lgIl406xnCpovVrEseTaDZcIhwGWLVK/YOhB8taQ1F1OkhQPDsfyUU2RFKwip4d3WtDjRj91jr2iqfbC4g8uknkXhhpwilqjDRqVs3hLR1MVJwhRy/mbqHuYNq8ZjRb2gZ9MvajZ1eJF8PuvmT1rkA1E7btoc2rExLHqBzs9RHZFmY0I1bZOJti5ZppC+bTBRxH4uoOd9L7AxlxBiz0MZFfUkAvhrZJOt0IX1LH3IP5Jflmk5NXZkjbJF8g0Xh2MP9oiJcQ1elBIRtOyc59Ol12b+n8DKRPsNky7dPvZoDmb85ytxY/UwPcpSYfTt2sPiZzJqU5w0zo7A5/xPlaGbgpprhmsrQJnFaZ2IX6oYty5j31ucbHU32d7+Xf1iEeIkyN/M10j8as9tnhid1P2FJxuX8MbkLmcGS6jf8duV3WQ2760W9Q/vhi5Ur0ExXoncAXMJGBQ2WViUYFEfkazDTIaHNhBOy6hVvUvzT7vO9Lylf7c1QFL7aZK7JSgCRrIT7kLcFw7P19Eqzqhw7MG1lR4c3JLAdSFlJ4e5Kf2hsWbfmW5BwizMcetpO1M7b2+lui17ICGYirIaloTVVGybq6J9+52GQSUiSwRG53uRZa0jPbVcFyAdGPpes1jMwgjKv2jeMNDMK6qkzIw1x7zCcp79DxgXxF6n7NS7uS6AFf9iaDD/nkCVR44KbOCpXh04HWq3z74y/AhIEKoiTxVIqMltZX+XlvHvKoWlxrroNgKAQXHKx9HKQRew1UpDuiDFpF4KxiWVEF3Uhk1QnxJaU4OTLXp/+TO5ZrukM09WM3hyP/Ut8CADYrIyGeDt5iF8a9cu5OU4fBQU2lzUkQ8B0iCRUx+LCmp0TzzAapOv9VZ9mf54d59Yd/fVZ2qMOm3lRZW397S8rHg+611Pip1hXW+6cjOZmbu+P/fmxP1tPBu1k3dIJUUFGjUzb9xeCHFB+0Hjc1PIz8jKHd4Z1dwpNk3xL/fHtxx3l8Ttey5K99SarLmt7CcU43KTRSALGLlNlwea2d+y7LiTxR57fI1D+a9y4ssp9ufbzhl4IaeaSVb6/xBf0m/c7Mzv5I/5EegHe9z1ZUHDrS83Vmip/ErFP63LY1f9oO5Sb2j6PkGer/be3pPW/lBd3+7efGb75LVO57+/Bz9l0twtn7lDb1/wi3WkfFBw4TZFPVJPY14xBpYBUdpizEyVIhPIFDgtMSpxITMPM/DwlQhEsGZB+HCxRpqgMpxFerhnB0M2BUGQEvYSCEmopJ99rPghM6GNbPmExpkojBXQeTRi9MnK4UjKK/BMpLoCurmKpcWwHGmETHLB+k06cFN3mha40zBX7bSGeICsKeGFvhXaZGPs+5xiCu5Raglid9F0OYyS7OqMrg1AOyY7AkB5YBp2+o0mpAV4pkD4gqSPGmYcJDvJ8YJ9xGkLJAh4RjKQoFB2zWaScN/qrWDTzYj9h3neECXq6PZeSPXmgAFQiIIVLZZsHlG7CGCVeaGNCpgWdxwGqgUbhfvXjS9+gXA4nYAmp2+0ZmcSVWOoA3FeHacIQHw2mgfc0u3HEBqamzWDH1m5nI4m3i4jOHUEc8uIJCBbKDKbg8x7EzH1+okisHiB9Zr9iNESPcrn+5duO4MTUWX1DdrI0zSM2IPEAB1p6PTZfgo923cLM/CBgvIu8ypBECoZ0CPSYOCEeA0mDBg8BssQt/Uu4PUnPF74b15f0MvROWrqvTBpigg18kUtVCjFEil+wNRakd50mjbksGi0z7swJ7KyrhTDQNGs2HhuOQNd+5OGS8B01epzIuvJ4IhCfnOK7lELOOatRmkgMxRF8GruYPk/Xwcy7tvl0Bg9uLEo3Z2MHJ6ch+CyH+c8y1WADEXq2xGwAumSQRXumXnKzH6Zurh2Slp4j73DRaSIVoEMUHmL4wP8voWxVniBM4UPzwFucU26aCBqhrPQ+cusDD2ZHUwcg5ztk7kXjKAujX31AAJeMXPdreBC/HxH7GjjA8xC0VQb6aQgmrPKeA5PdBpaJrGmf/ZWGq6/Sm23QLWrnvZJrTA/jkDbn19w0Q/o7C42NUr6kJb4VQIzGIJaOe82L8aQKRMSVq2PS1+a6nIVF7SKI0wLYl6JvlTxfpNeILdDVr7R+KCfI/rex4WvN7AboCgYTXRwokK3ohQUzJELJnKmQwWaAP6SdL0xb8eO7bQf3JaEHDehi9/WAVjfwqq3iVoYDdqoTqUfYugfnWhnlgqVX0bhI15bFIyRVT5z8KtIgGoG8tkaDW1Vx2rQeDIkUTuQY8HcmL5XaS1s8RNnd6Oj5/0WIpVS05u7HNVRG3LqwBhpZgaGqjpL9US9myW3MBkJeqE9eIc70RezQKTabNetgwsIxukax7GmBmYSpAQStLlKN4waA2AWt7n7ZfSDyf3TxcdzSCAC5YNFplRPzl4GEXbSN6/rxWnRAgCQOo1hP+i+nJ4Ojb9BTe9OE9ItNqhnt3FjGVRIVwf1DG5v4AXODfIIMZDE2TyAIMo9CO8gTRlpEQ/u9pYxRM4lHmutegwrOI1gsVVDzDmqFkwa69LCnyGbvo0ZuB0vZiY0oWNl6+4yHxUh/6cEBOlp0CPbAl8GVdO3AJdY+XWUqMHA34cL9xjeUs+NCEoqLAM6P1+CDUEw9Ksj+kx/ezg1VaFQukahZrlBesh7sM5UNJVZdVXTEWEB1p/udnCksxuMXhGk0Ws3+zu2JjF3rhkZSEXXCrBlpOdeBAVYp5XlJn/LgHb2QfQsFev5CopAXGIa0w019QSAuXL37LBZPkNs/5AIQ8+BgaOtQvmy4rpm/ktSQtzlUporoMcI0GSTLKhvvFd+YHUzBD6fMo/ahgCzu6m4dLd8BfZTOenQFP8KYY5TekkOeeL2ZArnJiqIGbuAy0o5sDpuB0W4YUV3xhzwZAUJX3O7uYvP7s/A4mKWVSI9TqsHEDkKC7QWoVWNx+AgdJi1zU/yFSPX024r8KgvWwSDbWX5b0z4Dxk04ddXXyQ+AmiTdHlS/hUC7E0aTTgaYRBehloLcRoiPLz46LxZDn1Zb9pUkPNkWYKqIV0ueF9SbA03+8QxrbpqxJ+NFWCz6nwTny1huRCDUign+E6KU3dFMGc2C7JSe7i1Z2UpnVPyCadu0jFgVUOHSPw/aTfvsNjOqLp3vGx+0U2Ty1jWTbCbm/7X6l3Ku7rdOe9x3kPWkLeJCCNQJ1/DJBUEMSnYRjr2inEECb5FH4/Vw2Ay8WDDfdZENPuKoMLlvgEtboZ1pm/NKawZE6JYhqoWP4AwdGXfrZq4E2jpVN7IHf9O6B2OQdS9YlO+odULkihJ2FH6ez0wJ3KVMlNeLGehKSy793r7MMPlVKzaVeuJyJp0TTDPeQ2Mag/UE7W7NpsB1npYjEgRY9136t7coDwt4CKamToydWxeb9qFag+zAZkIxynDVpVs5MsoWkRZV9WxSoYqv8JznlMs5gCgFh00fEUsDaxNsIhUJ/AqJGRH2CfJNLXW3FObFqj36gJblps8lyRHNFYz0pEuqcR9X2iPoIvIyusrzcStbpgo5aLdSs/wpiWQl4BQKU8TdZvVvL3r1YWbGSNXrTi/CBtGTcEEHEeXI6GXPCqqaK2qFni+tY1gJS1ijMyoxPMhI4yhsS1gN0PDKNO5qC5c/+S1XeF0Wdr/DRLsP9abhRcPwr4jzkeHCHZ6C0BhWur1JncA9Kr5VaDL07nE6wn7ZKfniR2LSW0kJdRwALJLkIiXkZs7h2eWtJ/m++9oOMGYUBsMOslI9M4P7gy5xUPoQLq+c40jOHdBy4kgDh0HHNgITKB67NExMCVRrbAissRSw1QdUNPOoNEYYG79nOkfiaAWWFmLZ47VORYGJQ6eqDdVmnlnyIt/4HS8tT4SxT7jiKqJI8SmUkw73MrGQCKMfWsLcWdwMUZBqaAwQesCMrseczVw53qQWbHUtSQ2OROsOpIwXKWtwlzkX32Fh3eIGfaxFMB/Npu1ZPSHRWmfvfTVFH3abfWiEylMFqm6LXTtPdqKIv1hDL3gaTL4wB8LqgSbNEEZLbFDXjHoarbzFrVsZYnIef3CmuDRkeycukZ13RLav5ZIUk25SwSHPoJ8CJzipGIJRIogSaT33hG96Oy9WKpElfRNYG5gk3LC0naomwsiL3QieDtAitMTlyYvnZef713h5rdO3IT7nZZZ4HoaOQMISlKN7zntjKmo0c/U9/X++cSja12MoiMauybO9j5eouDslVAWvkZUqsZysiOaI8PI38DVI7avck8tbsHZPc1Uz3pDE12+TzCRfJDHe812Totx502fP2RSqwKJ72t2pm460UqbNDbaNIXpFzB93yNzMacAhigLlrnqk5S+2pnnN6CVHdFVStrDyXQE9ckUQwRzxiRL8AywnBmnYAh5RxNxTBXsOn7tIIN9yGS56O3Ca9Chj6EwUzaEx9bZ8oDwhsgoCMmnE1MeWonQMY/txfsUxndArnR/zGC23FBv6Sgm25bWaZoV5dHLhxADXiiF3tPBPOoFoz1t6bZxo3kkTI3Dnm1eMkKKCzZfILUOoV8OdlieczoXzyiEa3AGuGqMdL4KC/IFWQq0kSxjzf7TumrWA1C3kioXQgwkTCmVP325BtTopSFGY+qz0q+1QMHk94USScbrTGxM2LIu6UYHp2T/HaI7vFolh9DfQpRexAagnK0oMyglHm0CDKKp4iMH0sGSp4FRFGb5VHhY4W4bM+TCEzTwLx65Vr6y2hTWruFBiyfr99mo30fT+ShqjJiGgHJsYJKVMp2BAS7RWWrKyHodOi7s1iijiv5xFIK62NRHRRpd3LvwJRwIS0TeW+57i9wBhpBsR+DjHMWm3d21ocW1PS9hIHkWTDdgot2+a0myBhL/cS1A/xpsb1u0GNVY+JtfuS50Pti9PSHZL7BJ0OYwKNrGIv7X//5g/pGY6rjU7Zp6EvuNvou9+YkzH0BqBPu+w4E7Gf5EPEHl2c4G9AKNs1yWHgH8g1AOEFd9TF0frIuNf6W2SVJXseWSyeMG3RWdJJ8hVNxdKhGrDkMSohPBzaDKusRV9i2+kKN7qFV20R4ucGqP7RlavkusVeKFy7jUYaOutjAL+HnyqQDmEq2Thw9xGVHmiei7fWsjD3UaRR2kXDUkR/S4V5On6/4YNSWcKZd5ADlii8hDgUgjJNPF7mAoiLBnOgdawdLAhDU6SNagWL0R05/zFKMmLXNn7AKcWF4oGYPl9Bo44DNa+J6fHwUYLozzum+Ds9IgAnrPkx+wrcYhh7P29rpCEhD5AvGje7xeQOn4skJ0dbBR1A/wLIXW579RkBT7DTuiFe96PjWHG+usI/OtGklTMyUBSsQWzEg1cJ7Us4d3WAX+Vjs8nnCoO/cbyBu7SJLkcpjB4xHH2O/+B6GC5MGAs/ypBjOCnqxwqkxFXlMHBQGvEtWCciw+wfHRUx5WCU7hKdv5RVC49KypLaIcFS2Na0tumQBWROTHPvL4GAlR2O4l8WI2i3yhhmT4eq4Fc1pRg+uXpjjmWd0EQWxAjSVsTbwlhRFElvsazPVT0ignva0tHDA4i3iff2OeGOaE2aH53EKrVvcWcWqLvvAj3WvUiYIXAyKXy13POekWe9pmBZvpFvs0QJvi1rpX24xEFf4ZCtYyNREXAY90d6ScovpfNcFDvzzLWCRyNMhDWbyUVaoSGDfG5XXw6LbQJzWs80IXC/DZkvfFwO+7Vv6+KPzOgPHOKOU8V1QP+NKzRthtCJxHxr38xfzC4PbEt6zfJMHmVmsTRhYw9tzA8jk3b4Jn5UhJhKA32sWgMoileey5tGuVOEVcoOkYrGIsG8vbXe2OL5pSBpgJYPN4D2GfN9nf12Fi8bA2O7EHp2LPtYD9zxex9jVml0bEWyCtxVcx/qCr9N2IrMJIDUhmjhkTthPIMwKloq2TKEaRq1gPYjU7vj9NhqxVqz2AuGBhacHQcbyqEBOxCZOps/hhvx3cH8qFvaf+SYuaKt6LemLyzir4VlN0o05brh8Ep+1BwA2GclcAWZ/TgQiXCMhOEHRfywXAo6vWBjUbFKEAMtJCMEypHmuxATDGgW8KStsXZ8LAYecbJocpsQS7m789gYpV3ATmORT3LI9edc8oSL5RVyubgOe3Z7DHXYMshzW+Ee6QrSgrLvQeZXe2/gCehERwpvL50xnpDk97fFhRjDRcL5jyvVjZ1d02BIclJvYxkHEOXvhXw1xh9RMLJBcvsDq7ZetdomK7o9nQgVjJ4Jy2CadwB9sfYo7DhRUGUbLFMXKgtMz4g4+8AfNarM8WCtC4DrnvyzZrxcZIlWxb5hTzKLHO8bqDfdrjQHK7qUZvatVEYhe8H4g/IP5ai7Kaj6AXB4A7nJ9Pv5EuSP+oA+MRKSjxmmD0egktjssltZYHCUshJRHQ96llBE5/kDEgHmHfwsDlgVXcxf2jrgcrrhQMW1IyapTIMN5hykAEfBaFOpa3LkakM13xChGCD5I/chenVS7CiRiywdBSgIyiTn8+maZeE9+1/EiXag7FwcfidBZmVQsQ7grAcOAV3cNoyObvKzNjeTxOoKfDTuw8ntqdRqB4fntPTsnzFIRdnCVfEOb4dJBs4hHvqTTACPyoSP606ZJDVKKH37TfpuxPOL5JD7MU5/vhfxkk1xB1zmy8Ob8iMjUdzD4dGGGC1hFJ4azMpHSgYX/cjpdIdxqyPtkNJobq0sHyCZ9JgIxEIDXzfO+ag8pwz5qQRKf3CShkCjqVoSd39YWkXjAAAs/9NLYjHfuFV2ixyJSxrmunMtum3WGP0tj2Y1b1OYpjpDT+X49FOHH4SA+32fouzSUX27hcX/VD8ib9G/14qEy+IDJPPDJq+XhIH16mRH0pWLGtHWoOp4M56HS0bpmxIun9qK/JVDybZJa4BOariwHxDcX7TjMvHg/FTB60SEP3h43wUkkQZJrjLumPUxYBgS0zhJlS6+X9vKQH/CbgLHR21wMBgrdMxNYmWi34bRmvK1pblf98CDGOIeLTXC3B2ZEOoOVhxOwqnXUyjPtAgs34qOi2S30e/cEoAyknSJTNDjIyqIBA2ZnQKle8FrMwENSpFV82PgL9D7W0dnBUaBYFhSYOW4pCa0o7GF9G3q4fHJkTFcau4jLJ/PhwIh3krloJsQL4D9Ev1JZkUWclQw2L4eoSLZMIrNb+PmvZXRLazYMYygSPX4LTh+MhKKzMVT5tmLBCkwztwWD5YX3lNaetRuEzH2ucigHlg51aAbkQH3+pieILXQ7HiYPld4hyvwGBpN7GQCILcW3CDiEMnVEaemTR3uF1Z+m1plhYDcGgOJIy7OMIUY6N+2XmZmp0I0bHluUp8Ybjq2mFed28rOcSqkfo5qalKC9MfVPBSVMSSccEa7XD/m85Nwq0dcK86j2oGdGcQJ3ARKGUw6IxM3xYgiHczADBke+XsgSQpIznIem9AVGJpxW0pKJVdox35xTXbC3PmDkkf1jPbMvcDztkcBAnXWw4StSIZCCD4bQNyqDjgY+49iUT2eAdhbto8bD+7dEOrQw5LhN2D4p/hfsPgSxqXY9GpGXrnh5Dr5cNLe2t12i9lYy9u1sGjU8p0EDbgvxcMrd4MMo/jmwHoUMXL8/C4rXr8Le0qgLqTHsC1w5AH+0OeMjCVrxs9bvFUANNjHsWLvNqesoRkv2+r0Xpxc1NA/aJwGDQuAYAzZScKBVvXMGBDwqhrkj/SX52R1+87GIA96/M6rZBf5uPlTBPKT0DBZLx4B2wmj936+WWtt8ICMxmdzohtN4owBheDSuvMN612rRLlgWhlwj3P5TsNT7GBhEYx1x3YLGQNQMv4e5UHqBm3o9C8CQaHKHtFjf9Y/3+7TUEObLB7goRQc7WfqZElCfOlbNVyeBA3E12rcNCIYNiPRLPQDB6W5dC0YKyDoZNqmgZ/t6EeJS/st2Vkotx96hQzMelvfk+4Q0f08TSySVCMD8XnaD4xl1uOEJhtz3oVCXR8EGsD3208=
*/
// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_CHILD_HPP
#define BOOST_PROCESS_WINDOWS_CHILD_HPP

#include <boost/move/move.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/process.hpp>
#include <boost/winapi/jobs.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

typedef int pid_t;

struct child_handle
{
    ::boost::winapi::PROCESS_INFORMATION_ proc_info{nullptr, nullptr, 0,0};

    explicit child_handle(const ::boost::winapi::PROCESS_INFORMATION_ &pi) :
                                  proc_info(pi)
    {}

    explicit child_handle(pid_t pid) :
                                  proc_info{nullptr, nullptr, 0,0}
    {
        auto h = ::boost::winapi::OpenProcess(
                ::boost::winapi::PROCESS_ALL_ACCESS_,
                static_cast<::boost::winapi::BOOL_>(0),
                 pid);

        if (h == nullptr)
            throw_last_error("OpenProcess() failed");
        proc_info.hProcess = h;
        proc_info.dwProcessId = pid;
    }

    child_handle() = default;
    ~child_handle()
    {
        ::boost::winapi::CloseHandle(proc_info.hProcess);
        ::boost::winapi::CloseHandle(proc_info.hThread);
    }
    child_handle(const child_handle & c) = delete;
    child_handle(child_handle && c) : proc_info(c.proc_info)
    {
        c.proc_info.hProcess = ::boost::winapi::invalid_handle_value;
        c.proc_info.hThread  = ::boost::winapi::invalid_handle_value;
    }
    child_handle &operator=(const child_handle & c) = delete;
    child_handle &operator=(child_handle && c)
    {
        ::boost::winapi::CloseHandle(proc_info.hProcess);
        ::boost::winapi::CloseHandle(proc_info.hThread);
        proc_info = c.proc_info;
        c.proc_info.hProcess = ::boost::winapi::invalid_handle_value;
        c.proc_info.hThread  = ::boost::winapi::invalid_handle_value;
        return *this;
    }

    pid_t id() const
    {
        return static_cast<int>(proc_info.dwProcessId);
    }

    typedef ::boost::winapi::HANDLE_ process_handle_t;
    process_handle_t process_handle() const { return proc_info.hProcess; }

    bool valid() const
    {
        return (proc_info.hProcess != nullptr) &&
               (proc_info.hProcess != ::boost::winapi::INVALID_HANDLE_VALUE_);
    }
    bool in_group() const
    {
        ::boost::winapi::BOOL_ value;
        if (!::boost::winapi::IsProcessInJob(proc_info.hProcess, nullptr, &value))
            throw_last_error("IsProcessinJob Failed");
        return value!=0;
    }
    bool in_group(std::error_code &ec) const noexcept
    {
        ::boost::winapi::BOOL_ value;
        if (!::boost::winapi::IsProcessInJob(proc_info.hProcess, nullptr, &value))
            ec = get_last_error();
        return value!=0;
    }
};

}}}}

#endif

/* child_handle.hpp
uOm7dd3Lx400fcJ21GGftPYKSM8TziTD+aq0OWUav9LmlMuwvxDvsC9At3Cz/dJZupPZ4qW9Jk1wgm8Nt3HJKWrwF5YpJdwqhzPXCstkY8kxRDUpI0/ZpnqaVlme0d+MQOg0VedzFzI9zER/emR5oiFngD5FuajIlU7zUlLCkc06kC5CZkHSD2WmH5RfDoWhttmZdA5AJTuaNYMNSl7Zc9zgaNu0hDxs/xEl21eZB/vHB8A6wZIlVuOKdeQSfZM7I3ohB2TWChWxr2eX5V10foKtf+WQmFBig9b8QiXMBtIROmuSfZbvQqFSGSHNSkmH3E6HYjzXNnUGh2mjIXnTCbOsCEunGsZwfi/jaK2kkfDMmknsagsRrsCWmuLt7/FI3XIDiDfolp4+4+INasZoK6jhGoJBuarSjpg2hJkQL0VEW7NbfGrwuooq/o4qplqQcsiqyOrp5+9176kJPFiOM9HJTDCwWhp8aqDCNy27T/ym8gabmhsZeTuxAZ9800mn28Cb6AjVCm/Qp9zARvKS2c6NDHl0sFco34EOtCLIizDstjfI/g47gFCFzWDCs4lKS14nqbJGZpVxpC26oaAmftjzWA3TtM+WQWpnepQZH2uB5tpAJzC46G2DuL9ZFEtdQUFNrKLZ8Kyp0dvih+lAHbiS+qd3JLMKwFjSpAwcDmfbw0oPYrer6J2c+bS32uvj6ZAeV6a7xFVUfYZ33xBgiMQqsOGEJ+hc6eWb6VSyxS+JeZIZRV4OUL87jnxxhhH7d7/ltSuvh3RLNC8+bohZXKs7YssDPgnB8mo1SKKG+EFP1ZM26V8WHRKS9IlnU+DHqHdurMOlDCNOY2isY4gyAHa1eZ412xLjjVhTc6zmnGTv6GnJnGi/ZFa05wwseDAclv0TZz3bRWfwJxUs5HAW7E469CKnzNAQMWyGrSQo3htnjROJo/Rafb/GO1J6MNWy1TCgPO0RAk5DPNLMSa9uCZVyKuXDVPPiPDogsrOpOuSh+gUVIK6jDqEQON8dh4vnwgep8FwUbnCiMG1EMY5Kw0clgph4XJJZCyLmH8dxefBDiw1d8DZIkNqcmwj0JErQztbmOrW5Lm2uGyQGG8aZpmsN97EgdS1+j+tvWkLukA/ZfTFfPswSf5UP4SoqBvVHZGLMH4sJOp7oMsISo8DXmqunQ2BOuXkOmE6JPFuFSm63SSPeoeNDyU7zOAZY4zAHwK1YYTbuJQDSuQvga2q2Qi67zrx7ne/WmnfrtkpBD+2RwkeIZV/zocV+x1qHZzqfEqtdcDisFTf71KGKozDp8ql5dLhnzXmujQBVCzSKd4j01r0wtiw11OaE6uZwguvXrw/pdeuN3yLzJPTG7MpV3FzwQWI5uqxNF1qgyb9dxjn0BZ0yTpjvN+wGcZq+HHNSVKS4ilQ3lU32qA0Ino+A2xHIBeHepi/HTLJM8P2u/DY9MMQRYJK+Q1/+lPnGeL8jvyNWMdSmDBS53FGEtkMICAK9rMKJejHtZOlqLOoJDbWwifdyTJMv2O6peswGZNYoZb4sUqZeC9+CLgPBex3RfpwFKmFm7Y12rdcCDVEmtKzEUqPugOygy0zT8jH3pRfRLTIh/cfINrQMzekDoudLPj4lam4ym4V4aY/YidRFGeJnK//v42Dhh8oTg7BRTqwyD8hi00I6mscql4J9+b52BaaTYaTsmKTy5xhrkfsudZT/IUPc+bOfZ4g7XdXnhgjwfl8PbljU/sKkN6/wSP53q+0QnZdi/c95N/cq5ZcfIbriU7Joq+iBkJfEwgdcpcZIGnak5o5cLzvICvdAGKy1xnZ6oyNpIWiY7W+z9ajI2kLMypQ28eNmJgx/qGe+Ixqs3oZtoMre/HYH7eXDvjcwOk/VaAgmEsXrxG8WS9qURd6dmtqElJKq0FQzcioi1G7GzucApDqTATcqiUC9mZRaZ6xwkrDcjMa5TKFdNkHJD4hSR6Ah8QYKB4liwEJz8qgD+XV2nU2Aixvzi1sTFTV2Hdz5+iMNsJujf9YHEQthvfwmducW2sHVHBWYnmJeUlFyq8WCMoylOohxXQPjgYXlusNYWGYG7UQIYXpVglC4q++w47xGSS+VTMS4Z9TjBO6Kq5nrkw2JR9/pNCW968TGRYQBXtifIYDLgKNf3pd2aXJDJO+S6BDhFhiqRIfHwnbiL78D/Q/XVmxNPcd0YiUyFrCWpgupiXBGG73vQ2hhl4RSmC+8iyw/nFi51kK0vwW8oR8OpG02EW2Fh1HYug6Tc+Vm5nI7UW91FyDlq3+wsNhzrwmMD7hNPonT50hh8SN/x9ZqhWg4y2+yiJ/fYwL6JLclyK2/A2LXZkb3g/0sdi00BbnXBsU5T7lt+TtmKhcUKUOKFHeRenFk9fhcb9SePJ26OJtaTQ5hGwg4XiX78EvcruxKMUF934ZEthkc4sXX4CkLcjuqeQcc+oeUyHZQL3ZE7s0m/nvlABpglJ4XHKQz4emnfjQM/w+msqUwL2XVTjP8p1+CTsb0RrPmIjvGNhsHW0M0GN+ZwBKeKgSUEf+OsgQCVYmbe9PCxvEzKD0Ecv9JBMjfZYk1KHEJldD74PMQ8mu+hbKJOF6Vyv297tMsYNqx5iv51V09Ow0mjN/CLU3Bnk46u6P2yNvAtikNazr/JX+GqfjPJjrEuHMtcwhOhE/2ZS1qfa4XeoufQelzMr+RxswPaIVklLlQiINWEmdN2K6EyKdQUGxohq/hsEQcz6iyJ1DZgS6ISvCTT3B1Uqd5K/5mpyHHn5C1qr3Nxu/o0WlERs8n+Eisxv0a+t54Cz9lARb+G2sw7rIbIffBQ/a/R9QqgnSQ43OPU4f5e4zVzmN9wrz7YSPu1pp339Bdyy95aqziH2zMKM4gWoMnvE/08e3649hFkMOct02f3H7k0zN2FxgTwzQBtGyo9rz3SsKJxEvo/NYJhC74J2sYSm/qgg7vykR85Y88Q1xoNcxtRqZGl6O9wzCj00Tsir9IP+3Qiq18Gj8PMxDZiUwhqEX+5QRqQq+HUh9HcxnlxkT84Yz6R3L9MjaiePlHzMzD8iPu1NdvQan1UxBDj/SxEB0gyfiArXw0ncFimKBw0m1kueTGF5h8TWq0WSKHWAtzos04WGVvQaMtth0j4F/2HmHJ6mnzLUkBZ/11haO2UqJoGy4E9d0RFEO22226zZ4DfKXnqAOig4xFTn0/60ejBLVU01w6XlNZ05CaGQFobJwkUlM7lGvE/LtoawyB7Q1ClXSKJzEFqpvOfakeMsOgu3CEGY/WSSgq1tUOK1KNS0aqgSfHuUSAom0wJkyVxCoVYthjHNgEfNuoTusTYX7yX8LklmGKJAszUjan8jXjkNWKhbhwGw24WEgiqGP9jHw65eyBdiDZkMg+HSehSa6MXWVliwPR8XMMSqa1wflAjZkToeSKO+eb5NrUEXHOjTtuR0GNOeuwx4hmGfc5U1xOZ4azeTVLhlWPwZlwiBP71GuzJQfK+Px0zmAarPD88qwYXv02UOnZdWwsumJND2hyiV8aEg5HvakosdpWvGjhgHsczETtk2C1bTAs/vVXhy1SfRbhpO9uJ+JJC+yVLpjjjI1QuuornqK/xsbV+L3qCfx9fC3CdDyj9IAVX4levHeqsRGqY7PKUvHxnXROZBXU6KvYOuFMUC6ASY37p6188ywZCARygMzg8B/qq1BAt4eNjfgyTEcbEZOlxmoX072qSw4kWWYG7rnI+sBYXUNjC0bc64d4RXsUSWFpCL1ql63sI7kRpoBk8xX1WsUBWD5XcBRXs1FO63ZIddhkFCFlYPeq9TrxQEcq3ku3qDni/NoUC5IZLedVogeTLlQAEMkUIYT1SkXsPc7ncA9inEA4WPY8HNCCOCmtUskQWckEgdK6hQ5I+i4XGyx4gjI8Q9VYCgOfQ2IrQVSGOHIb9QkMt3I29SGPcEPJ4eOGZ1NN+IQoQplKPLSN7OCQQZwRoe8XOBGbxKVfRWzsnhs422qblcwQYi5R1pvjbRGuKeDwcoAUGXmrfEouzRpH5dq6gP/ey38Bk2Lw1YQ9825nbhSAJlY6iBj3yAeAQrEYD7puk5wtHsynB7FVgFP6ByAK1aTGhgwSVLStL/FfGSZsHf/F+gKLgTUdkUu7p2xnijVFp+no6cGsKXB+fLfSQyemxwg6dW4TTOjZG3BAPWXe9eO7J8w7B93JIYOOqLUrRC2JabdwziD50CY+mS+RNJAzzZXYvzNTh0y7J8XQaPPSDE2tPTeS62357eudRjS3+mb0fOsO1vTp6HBGT6MucQ4+JDhxI7F6rQ1fYksSl9GkxVBcPB6FoQlrIOO7ieZz0ckivp2L9toShc7gu9g4Zt7MgTZCVrU5xIjZk1eJy8GJdSSc77hApouN6W8IVvAFcFR7/QBvNTi3+VrOfK0yS/8DWiVuow1qM6Ltg/d2GaXiJfoYUzET9hBh6pLYviOt6BTZnxw3ONdqLwNuZKZErzvQp2auNgfDFPe91pm2f5mbnj/zOJhxiuNAPxp7F90j7PAmnWJqDzrsnoB6xWZswnPq7qf3goVxaoEN1H49eKqXgoKIKhkODukgOmTEt2gHnSIvISqcXvGm/hBvWTjK7dUC1TAwjHNY8YfYoiVQrT/EQIU8lQs4bhzskeg4cgTMWt/UAs3I2J2jFbdzjPKVQEcdcYO248N3HDfYWuzWedS5URBsmJy3vhHV6o7I+cs4+l+JsYi481IjGNEdYcmHU+dG4UglFr+L49d9/BzOX6Q4asT6vLBanr3mu47Md7/u9i5WUW0opYcDXqcajI0tH3ya16WeaajVOs8pYi4P7KjHYVdD2Nhmp1EjA0hxu7gNc0rzhlrSuZraawPtrLd76VUiXhH/bgtLKNDNLZZ4wjpurxKH54DheNN4jQlGr/EamDwY3H7pLDF5zS0poQ7c8giT3WeMuoNT3uzNyPh0Z7stdmeH7eRofdE+IdGPVtqKoLfXJDv2BMXyR6yJ2GuamUlKhAu1moVmPQIn8A10bmA3baD5e5j3nklZfB3PCD2GCIoS2ys9gXKrORGzie4mgoRHgmMAT/p0+KlvGIkOsL5ZZ30THVL9KyCP5e8yg/nX2aZx0Wkg/cFgNqcZzEs3YYWaYYP43AjphRmpi4DfbzQDhbWJJzeylH+ovs83u43ORrWNOKItQDhOMFcCVtNs/bPA/BC6uzvkR6fjo1bEoGgNRWbgGwfxNgJumGKg7JgQy44fM22Y8lBDcSPTu1NkZtjTaMuAke0XFDMSbttM/47KHG0FkyvScOj+l8GbNoI3XZUPUGEbolkvM286/V3Jm7rvhuHr3rtzzfiSsVUj5KEykg+V3QU12iqOe7uqGVhiBQwjxZc/ZNGDNgIp8TH/hAeD2MM/GZvW8M9cOkfEW/wzL4fWoOVP9DsarF6PRbhzKy2C6jIF/eYx++Y8mK/ErnV61tTQEP9rLBoifHd0GWEWpnTt7pJBYSpesSVmv6k69NkvJQozDSD0HoitH0I2QIWZiswnZSc9QSDCw4VerzIk9i7HmVE8GW+h6LEELp+8Rwh61FYTQVsKJj1Hyi+YhfjoLaKoXdoqzJA+zqmtwLRBL7ICMwrl04qR/INA8kqAZEprJDUI1e92EaE4Dm9SOs3EdPfUYIl8v6i+y5i9PdemLx9DZSxGBA0sr8PSLEdSD6D7ghrfcqRNUF2+5Qh6pfQp+MC3nBNlPrZd354h0TnFYvMCyyX3FbuUs8wF/e+h1II2H7IWNDlUQoV4/1AKHnYdSsHDZvrZLdWztrze7KKcwhARTZ8WGLEHFQeR3p6qn4FMZ/SmXO3bzM7ulwnvzwxof8BIeUMZLBRjNVCoBZKaNFNxbQYSVNy+zUCK0kiM8LNdrfRtxgyoi3zUUryNflKzdtUqWPU5/ZVoTq9wpxiysHgSOS/kcQFTWeNjfYJC7fWNdWSpZ8U2S3ZsoMR9zI4BQYbFbb+W6JE+4OCP8FK50ayWaF3ZULGrVPhQ/1ir/lLjE3QLFXbj70pFP7NCKlFgJPnsSvGGVKM5bS45bUqeGQ41x4yGWuhM9un2SSajCL8KYVMGFYFlSw6M2pZv41X1/jfLlszRl4M9Z56r14wd0ewZEk8kVozuARqo5RxazX1zWh7cftwKWkfcy5CE6rKUCvqn60XgCdrXH/i3l4/Qi4f4HsWsKT2WT3Itw9Q8yok9+/seZWDNiU1ywaFqkksS47mpTtK0wyKZNZXIUPEwqz3//Rco8tnwfshAwivr3rbURr5nEba6Nqf1btDeDNdbM1BZRae2lY3pt2KKRNZQB3v5MhgDZx46w2FCMmPdr/gWm4HlSx/yLTYEC4p28i02Bcs63qLbaNYMmPCj3dhuQ69nhW0TN7iW/67jvzJSKeuTKhXZQY23pca7Utt6Jf/lLV5ZrrFKW9sKNKE9LrvPyplVN/AnRfz3Jvx9hkXiW9lTYOsYrgQYQuNocRonztW2VvPfLfy3ht9yVMOt9fyXYxty4Bht61P8F4suoz/nvi11XI9g0i+rTjESmG0rd8bLR+kATM9K3o8WEuE56/ejdV7wjGb9aGEOnu8fjlo4hcWSzXyLhWNG4iO6NRmJC+8n1LyiOmXzPJ3oge2xJk+4qChqn6OcXQTI7h0T2erp2ms8xtcw3qTbusMcFBi+t02c+TaD4Qgm4c+rlxmAlNNlMhilj79e7Vc7vgyca9Kl3VeWdGhLynxjc2n3qefIXagOEHefB2N/X5kb1v598FAbhSJmcnpXteNcmrWjGzFrsAlhFVo/2jguxvXE/tB5k7xUX4GVhPHLYEm3nSAKSboJQ3Dkj1AMVhO8kYp9Wzm6S8AM2+ryMYypCOEJcfoB7FjVHYWtFm2CqGFtVHi2iGcvlZlWUXIblRQjNsmIHwuqX8dK/xV9DniJfzDUXC1QrweG0MLPrtMCDWI9LbfMpv4J8HKNrwJ+IKCndiIVeWCvv9azCjIB/xdqth6oS/bWA/WxY3ba1oEGLdDoq8hVzqZ3rsQKQEVyZGIFgAUlzk+s4BPnTPkacJDsl1gB8MDrnATHXoeTSkWjp+pCPpOfCsLNcOA00NYwAxxiqK9I6ZMeWCkPOj3wsDynqdNxZPeFd0FTKREcNDPGwNVSpbNB7L6ly2D9fRj59qiWekhBAjX+WuWX1MqbMv2iuUaSAmjQuWLiYKSV+5umxKdYyLWLOqiqjShibJTJaRpRN1W1kur2f6H0CqUrVmuMgRF0nGbS9IHYdAsI1Ffkc0N9ySww/QANTi9+WLs+qE2e5qsYqlK3mnGWvCd25BEVOP2AoQ7V34OX7jFCeRNocfyz93oejnSxs6JyNsJ5j1oDgv5jX0W9ko2YD/SrAb8ajI/FZW8RQAyxmMrhjO6x99vF+iNYf8Q6q7rVBIChBAC89m1EWwQ6fBVtnlXn0LsQHSxqux7oQEw0RLrsDcalA6BQPFQr7vRVDCFQqE2DAr2T0JABCrVpUODXgAYLFPQ2HPRV2BEwdcPid8rFJyhT+8+PVXzrWtQD/+TdD+sEF+F+vBnAj2hH3XnMBT2Io8CYGKvosKkD9UC7XtyoreTVLW7SVmLt4gZUw1S3mLU7i8CpUSuEwlArnBY/qPSorqmpsSX7UiG2c8l+DgsBKxff2TI2TCeMcwY7bAaskzpo7wTaPA9/TStxCy+FPirCHfZi7mk92P6FJhW3Q42P4bs2BNjkC+zMP7/uJjSGSXcp93k2qS7/ESvm3Ozpx3lDr+nKsoVL6ReULYPbWdHTCy+SBEzJEeL1s9hShb4xU4m2il/QJ0QV5EVsIxn6S03rFfO93iZuohJ0HjjfSBPHpSDYDonH/ge3R5dNuTwE1CamQiZHdFyHKOJfuXqDuJbtZCEDjNqIaQqLdccNY+4tZhTFEIvV5qxnE1QZF9onRZBQXsE/RhpirOW/fKA+wwcqR4o+QV7iewanWnlvmni2jmJzsVssG4qM3Oo6IuAXHAwXGBP0Q+ftME/YQLN6pq9SUYdILO+pStogVcbp6Ikj200q2rroHnAdimj2B23tZs41TXbSxM49zY7PFr6KZuU0ibvVfj6mEpSe5hDpLZMK6swME7VvaMrkRCSvw8deE/GfJgmNZF/ZBFUiiQ2rEiWXSqueTJEuNy+U3JC0uevucLRPfPT88TT3fv4ii3uHDiTGxIItrFyZIXW9kXoGiY1Sqc+B0LWxiYWuIVPoCs8FCF2Tc7HJpEnaycSROjBjrEepB7Kr4VOJxPQVWOJ4TWWfqIxZbwzc8hF3/fTn2RozFYg8rB8tOOg/pmT75sIq0T/1uOGb7VLP0d8FiUMv7qUXyl2hEJvUpbs6vTSxCSX0vjIFT57ilsCdu91hS54eHRcuFSWDYeus9NH7IiEMMRGX1Dhs+lX+H5RBvjl5Sj8oTrlWSw02Z26m60gGJFo2oyD3lFtSAHYidHFSGtYmnCIpDQfIINBrzjBUNTaiRrpvkOlfYPDX8ZxcXHiZTFIyJTMn7Y2UMyxR98wbxfbTiRloDrO/26fEJMVAuAD3MMozZVZaQCg9Y8yhEEUV5tJAakIvbpa9DIqLKrpYZqIHmpnMsXxsGeReX2iporCEBQcJ7rBow8MnY4BTRZGfG8m2mya9KfvNLBp1hsy/NPEaSGU9h2bJQxNWU0+D68hRHLELaAXjh6HOc+n2aD8jOCzpKRULSlmWrPcLGlOHz2EZRtvNGZbF81mhaCoxULMy6NTC3IIaaWuRwcuL+WuPG9YizG6pQ1AvEyPetDYDI3Ybo4UXT5yPU2JEbAipvKANqB+SW+rkHXgyItj7LLYhWIK5c6welpSwNBnUs42DDwMnhvQzgQpKsYE+DIpr4DdZxzYpWnEHwtaFoSk9/XvEl3QReViFnKy0ZyKQSInzglS8bebM+GFlaIy5FJsyALqDg8eN8+lmyFj64yVumQ7S4g7swvpDZk3q3+ijWf4jyowYk8U29eaUU5g9AssCVi5TZX+AU/gi7t4fnoXe2bRWnJGnL8orjbaXGgNvamAhrkRbIeLAZcYkmCtmCDMI8NNutEEwn4dpcP5dyiwIPhtZpV0SLg0lx/q7lIlhOcRxN7PObpdygW8DMx5n+TYwGT+IgbW01FiQp/ETCbK0/MWdogWw0OE/pr6VNtGkk9ZOYKYWxXgBbcp1lrb4KokJZcc2PWPi5LM=
*/
// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_PIPE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct pipe_in : public ::boost::process::detail::handler_base, ::boost::process::detail::uses_handles
{
    ::boost::winapi::HANDLE_ handle;

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    pipe_in(::boost::winapi::HANDLE_ handle) : handle(handle) {}

    template<typename T> //async_pipe
    pipe_in(T & p) : handle(p.native_source())
    {
        p.assign_source(::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::winapi::SetHandleInformation(handle,
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);

        e.startup_info.hStdInput = handle;
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
    template<typename WindowsExecutor>
    void on_error(WindowsExecutor &, const std::error_code &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }

    template<typename WindowsExecutor>
    void on_success(WindowsExecutor &) const
    {
        ::boost::winapi::CloseHandle(handle);
    }
};

class async_pipe;

struct async_pipe_in : public pipe_in
{
    async_pipe &pipe;

    template<typename AsyncPipe>
    async_pipe_in(AsyncPipe & p) : pipe_in(p.native_source()), pipe(p)
    {
    }

    template<typename Pipe, typename Executor>
    static void close(Pipe & pipe, Executor &)
    {
        boost::system::error_code ec;
        std::move(pipe).source().close(ec);
    }

    template<typename Executor>
    void on_error(Executor & exec, const std::error_code &)
    {
        close(pipe, exec);
    }

    template<typename Executor>
    void on_success(Executor &exec)
    {
        close(pipe, exec);
    }
};


}}}}

#endif

/* pipe_in.hpp
e7owm4czJuv1GUTDWWzJ8qU7tmI4dgDy9NfVi73uyxd7AI1g3iu2gURKwK3VFikzIbD1vxAdwY9rqIP2Hs5J5YD4N92JzuzyN0KX4FCy+4qAnuEJPKCd/CVg0p5RdX36xuNPNfqLK/cyW6set8s5Ev+ret5/UPjABhIAugBkivDEB8kUV9Y2JWA1fczzdWqknhcX0XpqmY34Z91zrAbRngOA5BipU67L2eLbVIHrLwTcR8MUUQKZwhBrpscDnTv8VBYQTkWvudQtY611H1RLyUuirDRaNi/N5gkxnal2lcz2xKjV4g8ZMnVridZkloEkjV40hbXUsWFu9gzw+sllOOcoUEEHhn7UCE1sOUNiQTJPpNCfU5VeQuPLdYZnynXsh+cEhEzygEiGmh248t938y9W3ePZeLjLjfcGun/KEMEMG3zBbK7thwGly6NRlrsXLQ51rVNu582arkK3JjpkcuM/WufEN06tsi8Dh7o8FHm0rAslY6J2XtH85H3H+AzgU6/Gc8Idkv7KSalo4MMjntEfukILRix3MxnJT0s+vcp7n9wmpLyYlladJxazcEXQxlIFjkW70y7auZgEUzvP6J7UVYe5YmsL8imhPNqdGV0Rf5Bc4ay87VM1kXH2Btau/sn3vG6dFzbVDdpDC42Jf94FjBEevBSnY7anIHhraBYFgVTt5OjvfzAUfwdrQsntKU3fYaZTa02OCK/gGrNyh1G1QpNlBpdwtdmQgygB6wrNhUu4V4n6xtGHTHkyWKf+WcbQ9UR8Qf7fBieZfRJLynGs8oO44PUSifk+BwroR3UUCtn7sPRW7oJSbke8OPj+y7Q2O7PUa73HfCfltRPq6Q1rhitxFrmnXEt5bdtJNy/Q2x8eYDd3v5Cb1apaPt09smM11nIy4v3aMNeh357OIotJEPzf0MVWXCy0hgvryXsEWCfBdNQkGWp3xJaQLg+1WTEcpbR6MDO+vIlMPrlDOTc3s/08JMqv589v4ldo5Nd0Vo/ueZRmPCUt/zk33zWCHOIcoUXUWshvUxmu/UcFobRQkG85KaT7OED9A5xiVj/FlfTYN0WgUbvgJDWzIHBl9x30637bqcO/+jH14vGPGmt8A+h/kArwi8MrsBHLVWaMYcj3h7jcnn4/XKjyuo/WhkvrH/3OX4krg5KfM8dNzp5mtxK7dGUtJQdoHaQV9E3JUHVMoDVVYI9O16WbC29QAqW9NzXKQ67znV8lbv0z78V3VH9YvgoNkFilhktdWuQXB3PZQZbD5PM3t56adjRzXvyuXSseX1+ba11ZzeM0WxVZUw8a+pTPWQEBUELeBrNc7Q5oAxJg+ME4smek17ow4RZ7H9pz+po1mwvufnYgsQjUQHLqiGn/wsXRz2lOIFM8ZK9U0/dENFM64ykg+35VcPo7+Adg6to87Y5/bXp2y7Nl7E7a8jT/2Qsn2xLgzQ4jJEEY3j06lGqw0Z8YcKEpIOF9oTmfOW13ljl9PiVYeOq8c2pcu38EKrGZ/gsRAndvX1CKUzdESxXIbQmu78r5Lb1sHrQsdj5cks2/XxXLpywsakrOjqv9WV99c1M3KLu1JtAwZ3HpvElKnwrzyCEn+0ipUuS5UfgL3j7r4kh0bpUpnpaEOQ3ZAmBMtwRDx4EvXdv21TvG8teRqYUWD6NygJ0PrXthheKM7oVeDpYXXM1uoi453JfrOEeU5rGYgAqah269cZgFVXVts2X50zhR6sWnnsStYdJQJXzUShlJO/m6ensi8bo2RkdBaZNKQQnTp3TW+ipm2K+tjo/RFPA9D8wUodCt1vZb/rqh52+a14LVCAj9+nKPrcJegwmu69NzSAmW+uljvalTzdB71xO9iAeKut8OXMLMBFS+udV+G/aTp9nR5YHcZ1PRHP5IQ3oqZMnj6BcA13/30dH8+St4PWc4/EWeCipwJ7kbbzKIUQBOktPCY99NZAzl7oM4VNWrVPd24x982vQpLwCX6sp6ST9GVc71mGoVY36L9LjU1H9Q4XVu7qB28h4w3ooAF6FammrF56BjT9Q7oSIU8Q1CS/o7Ez7HkFuLOSF76akhor8mkJY457N1J/KvcVcPWkFvdOMqXaIFdJi+qjsSrUpW4IESX7mpsJ2J5vtKa8mWjYph6XhulH9s2u86X3MsB0dOP8OSBCBDo1CQULGOLmh3RvAjTMPJd/V1PDNcyKx6XhB4cndA66D7x+ebrt6rbCSwEuWcMpz7LaUpz030MP/vxZqhuPHNkrSq0fJe1hzz3Pyd6bLCt2zBYk2IhQoDBZVbFxmg/S1GAqlTQH9DyaK0BtmM9L8W2In9Pa06/gMwHSkC0/4tu9SKkThF0jbCBUl8Nhj0ZMZkLxRym4B1kot77UA0xR2icHQ/z0riKOcsNrMnFd/xtzHuJN2vNje/NPg5+YMNOVYYHs/a6EZmUGicixyayN7mlR+2mTe67tKmD4rphERVPctjQH0UH6doTqRKTFTMGwngEC7ovNdvIREXngz+zhxB2TpiJuC8X7iF4Hkm3DVTlrrIaFO0e/D6cj46eXhCE3IwoXmKPP7C3HrDrK8Y3AgiERFOQ5pzh1Bsen4f8chM7ZXtrhV8fregXAwU37nwmtwhA7erYA9cark7P+c6NSb6TYnZJAblOw3l/dDxstaBjxnd3qk2TDswAMAc0LjdX6Zqif2JIdr/sXh+wzgtuUWXBXaFv4bybvJcRT0R/Kt4cCC5KsV8X+G/86gniP0/ljdmIM641xzGOzSHG7z2F69HdrQHW/s2s+YFDbdQm0lLqwzXeCkzBym2W04pIWawPdf298l+afsN3AUsv3a6IbiYnRW3Bwk3xMiE72mX+OG7JcTI8eRsht68lCi1tO2T/H5fAclwD2ACOnWeDJXxJWFFQVKdh5ZpyYIgIBTvBWD+P5bE9pBW1/y1+wVQO/g8Qrrawy9U5KBUDo+1yeXFySUTvmy+tLxaLr895W7pVNp/Itj90HLTzPal7sWaC7vqzmDiExINpQ3DUhzLoQ5Lu41cvzzptWWAbPBJSOEfRkIgJLrhcX+ImaeDxcG769DBwNAvcpwEixZ4m/OUSXYsOKAuB/yDbQkVf5jilf9wnui7g9YX3Voy8JJBi7MGRNECM2iGmYEb+dtJx+/ir3yXF7FchJZwaxWkYYuBjeACzsS70pLH2SvyS7YYH6Yd3bU2N5Mxevx1DTKrA0Ef57msKeQh53J3ypV3ygO0FGo80jpb686WpmDHoBjOGSB1Gnbdp8IN7dPD+Wnpz/xCt6bjN82FJPEvr/yhzMe7HuWNWPxmucTrn/iLZhQdRww9EjDCZqnY+58MywfbvcI0bPHyAZQqLEFtM8PEwkUUrIaueTGE/nle1Nr1eV5f19e6GmEpPhbGwY2nAaVbenEm0oTSNcx4TLwxgl86LQpy5eViAtjPn106lEtis6HpHBXuu1/Gg9jl/v6Gxl/3lcjqQZdkoOK3jUCQT1eNaCDRn81rU6hVDH+b3UzxCx4JYZFQ93q1iVjDmBWPg9zxdyuGL4ISOmg6z+lFOIrcaH4m3HA2hlDNABN/YGeC276h2PvyQxmOWLofo8Z/7Mp5FiAE1n9c6lIGJPP0MReCxauRN2usVXEwE97Xn5/a3ubjY+mEHjWq3vjlUEdWtjnHXbXxbWZdCkukx6Ko/cKgt0xJVL8n6cQY7uMH2GxCVrSA+aWu2X/WXPvQkfGR55E45Ti7xEiqMqovTw6eHJBO5MV15OeQmRtoq2S3PnH7FYfYfnkV6vfwy2NoRCYc3EXlAcPdqSI4uQ8gvSIMfwBClXfQZfe/IJ8YpaJQuHdwBtonlvyvP95Q1VHRldgI7YxKyfMYgQelGKtC0Pp6Fj8o7SjEi+L+Y1u+En8XqcLx8Geg6EmDQz0JX6QmnrDVXNHcj9bMvCH/gCj39J6UP0kbIc9PUHOiW/CngMj78bnPVXhzn4uPjnuitVQRl8f3aA4MRgITSnEVXd6fof4DNOlpiNWY2jEVn3GCk6VJTIUxH9r7J3r9bJLdZUSvMQm4rTNB+NUkAk125lbncm9mxB9G8+by4AOTyDF+IR5bDrihSHvCxDvTMnBkAqmxhbrxsDablubXXoloNZMwN0ePrqjZwyJdO7MN9qAImdygCCW/5Xm1i8ew1JYGgsC/pNVWcttNH6GTTQXDsU0FS/Q7ctcOu1xXTbMXbXU5/EGMmLxMCkz5jdwSqNlZNZh6jxHyIAHv+hKjrT3+mzlkyAtyGFTmBWpN9hFrvGgJPnruqXBZgWx3zd1Gjon8Ot21uQuk+pMDT+7KMdaPDY1m/g+7tZLkB3VefSFmVLqaqt9FeZgcLQLeaNwOWqrf9MC1DHjStaTwzpylCKxAhgqPdpDwAkhYPLzuX4l2SHVxpEO6P7XbZKtPkR3m6ucKmzAlkR1WurI9EjW8P6hHZeFedp8U+CVGRJZn2YV7Ka55CdyltRfmh9hmto+gU2W8krU/HR6Ce6CbtgrVtJLh15slqE5mRQYVOUJs0IFQ3J3XAABAtv/hRlJwysu09R38Xh4zm/mIZ/VHS/UGrzfktNuPGmYa2DVU/sBrqiNo18TJnZ1cwAhH3Yq03YsOS+l37eeMBQeJDx6gDnIoqasqM98kjqsXGCI+GXajbo1GxILJSuFJmzCbdqmjfO0BDo/BuOOf9P1P/Q7Km7LytWbsv8Uw2387wKAERpDfW7DKn2+ER9o9pfamLKckL6A95Vim/X8OoyTbaFlwkplZ8bC8q1e93Bucrm5pORGo9QNVzF6Q6M+MOpDrPnufznellNh3qVQo5g92SqC8Zm9+C8LBnbP4D6srGIYtpS2w3Ii9bef9C4B97K0BEhzIB1fe0yE/v9pHKfdTF2hb4mAuM19Af2Z2IQOG9I6E04Vpmvu0Ld2i8l0dBs2QurwHm7E1Iz7sOfFCS0fJuHersvoF7Ryk805Xp7h3z7uUCyyCAE/pihAE3x0xXkI8GjekZEsoXDZRUM/7ScHXajekZ4UIAq3PDF8exS1C+J5VjGeQzDfXEc93VeE7GjMQOK7IEJx0AKkqTuV5Pp56XrAPEABLf9AWqVOqkvEpB3uEcO8kXJX+UP2S9lKLm08Zda3BPWTvwD10OPZpuavymThE5yQlYsQ3SEaxM1922A30qJodLSco8sX/8bVF0OP770tc2hCmBtU/v96entlsFj9pD3pPq0cI3LW7LWzYdvTHvBMrOWISe+2W3jGLaZmwcjO6IPwKqaShlwneNg0/bB8iccYQ7cWFMnmyoDlvkTD+xRuaU6GlXdGrJlbhTArPqX3EnPNBuoYXQKN9d6ofciFDAQiCyaLOc28uW80Pt93u/rUNwR7Ip39tyDwMtOGHg4GdEdyvydBuuXUK9EBO/k10tPZCPq1tue2ubrnB//ZC8lwiQN1s7h+lVm/8pVbhLPtfoYCMYhBEQBXrxhWt4CwYDQjWJwdIfSTHOnBHK6AtyLEkf8JAd3Vh2PiKMIWEmjDAF/0eSy/eLRCFfk8+rUEPKNOwBzLOs4Wt4n3N7GqujFQnY3iJofwURd2D4iCGiq3GGdUFdDcft+06XTCttvl9VYKcuSlBRFsK3VYJDqoVzU+XesRZ6sJdWv61jJr9ZSPStfVW8nu204+YW+khk9Me7IE02EdG1Xt1EsLw4RBeax+X7tGKpPf/sU9mltmZH25J0jJkOnqee2XwrtM+4e7pqSaAIlAjmOJBkAOzHjQBSvVzl3H2dek8zHoTvrikvq6/pQzWZzWQ4+w8kpqKzYPqJOZXLCmeBMT4TwemaXNAyU6khmPz7GjkInIDMwJmvN5W6IP3BQIFLovsBe78PeRuA23kbtfVUUQZgpxQp/mmoo39eE7IVgVoVW8TWQCAhRwAIPDbVMbCOch6PfW1k287q0MCZGMt9dninCd500apHEvzsP+exRiPDmRbbR6iJRuEtyrmh3d5Pg+gWPMq2rhzdaiYbbB7n4EIIdA9HAQMSs/0SuPJWM/zjDlu9iy3/jxVoT4JjGxLflaScrbNwz1+jQZqjId8cKHKXh5g5kGa35iOtf/TeOPpsG2QPeD9WhD+6GStjeAhDjJmZkq0ulgeEaCKFuDSxtghq+hiSO8kAB7yTbMB8sWcH9nGtJVHmc1ghw9xMlSSkCVi8jwzTu1Y+bmYRQ8o9VM4h9SuxQ1SBSb3fXLZpW2oz0G4fYhiBi5AVPmsOLHRhEgU52FNNgYonPj9F4THI5SXT+z9nagzT2OpSNmN9q5/QE9ZERx52WlfP5jFwuSRmR+gKtpWfxNkufAWgqICa5KHhZ7g3G5f4/3ixGb6y4yHOHbKL43k9AdRW0NFZ0OMSIHN+VLM3xHqnaYDWsP8kNRfgl02tg2rHzqGIrY6YbQsmdCPtlem2rnB+30SEcgmYLHNgvgsXH7CK71fntntAEaq/QiAzfLWjO4eLo8ldXZco7ywO/0F/sPmgn2xYAmpcYl3jJF8ZkD1iUnvyS+GMLdV6h6aueMIr6MI0kfqzfFc9o/2H5iiarDGFGt1VUR5i2F/T78Tbh0yvGEJIUOxJW7DPYYvg5gBgB/+rB43wJupN9SWz16EHArabGgDIH85MB1vYoYDP8gu6rKPAaWLpKtfpMHkbts09T3yuKlyvbJZT5e+jIRinyGHJ1aG/rizjTVC5wL04N1KPbhnTGX5OFCMSJJPhuSQw+sp1egrLd/q/Cwq0hFPhMUGlbg+msEfiGASzrD03UAistv14PKT5pFA40Hgyog8ohbPa6edfIB+hpYSb5VAhWHD3f5dQUID8z/cNCCeb3bCd9zUJnA0hjDcO3qJIHaIkFWbjUuazxiixy2WtkGDsdJQ9Q1PygeNmWmi4OLgF5x1DHuuUEJUpuuG7E66WsupxTbFlXIAwHIaDLsrseyKhCoYQV+GD5aYnsY+VI5iI+qKmboids+dYcbZJlMtaRYDgQ3XL51NfShbNljd7f1GGpGKsJrQHux5tLQp+vM4L8pqbRDTw4vSAY6CspfcDG3V0FCCgjPkfyPymutrfkQHpN1yT/ZjcRUt1VHYkw7YL/EqrtBtKts3hfxRLdO+YQRD31Ppvb2yR3POKG3ixH12XsmKi9PnlrxIjDqjVlZJnop7o5ERvyP8ZkWD+GfiAPtNukZ/yocdFo5s4zhbL6HxnKn6j9JgdGg5erUG4+P1kOt10X64GTTVfijvmGSPu0FPcV9KWfRHi2Cq9U+Bw6LQ4/iZOJyfD0WeOLTEWFEA1pQoOIRwdXsCv0s41acKOGjAcsW9+NehqNlaZfkpMCb7MAuerWwtDEpUDPT53XP4+1Gw3169WcarwvIAplAb7ckZZmUIVt3bdLJHvbmenE/DMIfjJ8PPd6yIv4zXTslehhM2vFfvW3EluGmbJTxxBMF4qHfMrZohpA5pZ/A/I6bvPV8O3qhbZPB74OzOtoUJ6b23i3iMKnPZUnCKEKA6p2MTXMYJOr/ftDtsWd6XqaSxKmhgyBXsGvSpebWZSS/Rj7MaT94j8N2eDhOzza9OfR6S9dPaStOdeJK0IJEPmjXoti37aGFmRNSP1Aj4lv2EfJecn1zHGkK54h6HSqJqw0oqZpsNuHiVEdsrtYz4ZXNtjj3NatW9JOea0RPWMqT8ekCfIE/U
*/
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_

#include <boost/process/detail/windows/handler.hpp>
#include <boost/winapi/jobs.hpp>
#include <boost/process/detail/windows/child_handle.hpp>
#include <boost/process/detail/windows/job_workaround.hpp>
#include <system_error>

namespace boost { namespace process { namespace detail { namespace windows {

inline bool break_away_enabled(::boost::winapi::HANDLE_ h)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;

    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
        throw_last_error("QueryInformationJobObject() failed");

    return (info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0;
}

inline void enable_break_away(::boost::winapi::HANDLE_ h)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;

    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
        throw_last_error("QueryInformationJobObject() failed");

    if ((info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0)
        return;

    info.BasicLimitInformation.LimitFlags |= workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_;

    if (!workaround::set_information_job_object(
                h,
                workaround::JobObjectExtendedLimitInformation_,
                static_cast<void*>(&info),
                sizeof(info)))
        throw_last_error("SetInformationJobObject() failed");
}

inline void enable_break_away(::boost::winapi::HANDLE_ h, std::error_code & ec)
{
    workaround::JOBOBJECT_EXTENDED_LIMIT_INFORMATION_ info;


    if (!workaround::query_information_job_object(
                    h,
                    workaround::JobObjectExtendedLimitInformation_,
                    static_cast<void*>(&info),
                    sizeof(info),
                    nullptr))
    {
        ec = get_last_error();
        return;
    }

    if ((info.BasicLimitInformation.LimitFlags & workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_) != 0)
        return;

    info.BasicLimitInformation.LimitFlags |= workaround::JOB_OBJECT_LIMIT_BREAKAWAY_OK_;

    if (!workaround::set_information_job_object(
                h,
                workaround::JobObjectExtendedLimitInformation_,
                static_cast<void*>(&info),
                sizeof(info)))
    {
        ec = get_last_error();
        return;
    }
}

inline void associate_completion_port(::boost::winapi::HANDLE_ job,
                                      ::boost::winapi::HANDLE_ io_port)
{
    workaround::JOBOBJECT_ASSOCIATE_COMPLETION_PORT_ port;
    port.CompletionKey  = job;
    port.CompletionPort = io_port;

    if (!workaround::set_information_job_object(
            job,
            workaround::JobObjectAssociateCompletionPortInformation_,
            static_cast<void*>(&port),
            sizeof(port)))
        throw_last_error("SetInformationJobObject() failed");
}

struct group_handle
{
    ::boost::winapi::HANDLE_ _job_object;
    ::boost::winapi::HANDLE_ _io_port;

    typedef ::boost::winapi::HANDLE_ handle_t;
    handle_t handle() const { return _job_object; }

    explicit group_handle(handle_t h) :
        _job_object(h),
        _io_port(::CreateIoCompletionPort(::boost::winapi::INVALID_HANDLE_VALUE_, nullptr, 0, 1))
    {
        enable_break_away(_job_object);
        associate_completion_port(_job_object, _io_port);
    }


    group_handle() : group_handle(::boost::winapi::CreateJobObjectW(nullptr, nullptr))
    {

    }
    ~group_handle()
    {
        ::boost::winapi::CloseHandle(_job_object);
        ::boost::winapi::CloseHandle(_io_port);
    }
    group_handle(const group_handle & c) = delete;
    group_handle(group_handle && c) : _job_object(c._job_object),
        _io_port(c._io_port)
    {
        c._job_object = ::boost::winapi::invalid_handle_value;
        c._io_port    = ::boost::winapi::invalid_handle_value;
    }
    group_handle &operator=(const group_handle & c) = delete;
    group_handle &operator=(group_handle && c)
    {
        ::boost::winapi::CloseHandle(_io_port);
        _io_port = c._io_port;
        c._io_port = ::boost::winapi::invalid_handle_value;

        ::boost::winapi::CloseHandle(_job_object);
        _job_object = c._job_object;
        c._job_object = ::boost::winapi::invalid_handle_value;
        return *this;
    }

    void add(handle_t proc)
    {
        if (!::boost::winapi::AssignProcessToJobObject(_job_object, proc))
            throw_last_error();
    }
    void add(handle_t proc, std::error_code & ec) noexcept
    {
        if (!::boost::winapi::AssignProcessToJobObject(_job_object, proc))
            ec = get_last_error();
    }

    bool has(handle_t proc)
    {
        ::boost::winapi::BOOL_ is;
        if (!::boost::winapi::IsProcessInJob(proc, _job_object,  &is))
            throw_last_error();

        return is!=0;
    }
    bool has(handle_t proc, std::error_code & ec) noexcept
    {
        ::boost::winapi::BOOL_ is;
        if (!::boost::winapi::IsProcessInJob(proc, _job_object,  &is))
            ec = get_last_error();
        return is!=0;
    }

    bool valid() const
    {
        return _job_object != nullptr;
    }

};

inline void terminate(const group_handle &p)
{
    if (!::boost::winapi::TerminateJobObject(p.handle(), EXIT_FAILURE))
        boost::process::detail::throw_last_error("TerminateJobObject() failed");
}

inline void terminate(const group_handle &p, std::error_code &ec) noexcept
{
    if (!::boost::winapi::TerminateJobObject(p.handle(), EXIT_FAILURE))
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();
}

inline bool in_group()
{
    ::boost::winapi::BOOL_ res;
    if (!::boost::winapi::IsProcessInJob(boost::winapi::GetCurrentProcess(), nullptr, &res))
        throw_last_error("IsProcessInJob failed");

    return res!=0;
}



}}}}


#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */

/* group_handle.hpp
IOJLXhZS5xIpvUQBwNowu0v/sSWLrtG1XnoXlH70n9+74qvDPMUj/1c2o7zZNL7MtdYxZ4jGpUJZuTtDp4J1ca9QHy2RoOh55z0m6wJ2FVIbytqId3uWT7MQx/v2/GDYcQSJvgfOhGwR8tseth99Hm8PAx8tASyAvqyXvosH1RdzQD7uR+9r3spwbgOIrPoc8oHl2+fGTLb3MZgLu3aetq7c1BM7qKp324IFLGXo7q1dmp5fF6V6A/f2M1IY+zJIT/WmfmP4O8sPt3RRvyRrZ1L8h0ZpBEFHwPsGMxD2s5DcSGL9ESLlkJBNisHwDcxHn7YUSjE+geDWMQTsFtUB6cxf3eoMvzpOuXO7cp8sEqJT6sxhYSEYUwYybAjm1VPebVgSSifCfjRUJAxLcy7h5MXE4ykO6C1IilUZQYUwgQ+ru/tQ0RRzXwLycRjrza56CNFe0Ov79mm4Y4Z1/FYpVOANMB74+kjWX043oX0qJsm8N3L6rnqS0Lf3LA4IyX6T8yyWFRo3mb3+d2OoUv/lWQpn7F3yFzEIxfcSmJn2GUg8jkzJ01jazkR27j7jyuZTtTSj/mDAzq3Q4X6mqQ7Gzx4sCr5RPKJ3iClbfZlyLFttBuKcUNtXYMk8iANQQgp0fjvIS9ddzZ4ePEQ1breooO1p++49+PuaFpw6u4+O2/KB1U2NltgI9SO13P/A2aIvp8dnTilVSK8sw3J/Kxoz5EaIRHuYcceC/MmFQ+CCPQOwjb5dOhBKZHgs7EP+1p3VMUqTfrx2yhWmEC5mhNA2X/f/kuOtcnW5+L4W9PfubBVe1Pa3TAactI9o0dXiittu1nAgak5eYWtI2GRNvDFJqfcrur0yObuYKLBXSheYEh0buJRZqJC5CnJRqBhFZ+nul1zc87YpSyAuvl4XzaYHgW/5+7KlLc6993wpHYIoUv/0fWAnNVdo3Ay49nwpc+N0b7DTSZ1rVRG54BRL5NCnXKjWWlQUVf262Xxi84oLbuUGObxb7CMPXLr52yHNO5Vo12bsZvuoGpxjQEZ/xClUNB/0e1ray2Xj2LWJXUdi0NPusOP1fS14SXVNYyIYNvcH/dtbV3MRPMi1ICJgcfUCW+74sN/a72cxc8RXulZO0dKrUwGIvdfxViBf5poz3/RAdTIH9TJ6l5021JkldJo7mw3l1U/0HpnDn4J1wiV4dFKhd10LFzaEkR+hjyxu10iZO6VVWs0n/LVmE0jz80g3TEV/rjxaubxgLJT1jQcyWz3dPc1Pe7YTVydVzeHuu3ZToca0ewS3KQZN3jASZzZ0pdKzOai8DYsHvMG6vDtRtQwxEbgAmXOjuubMhpba++ArR+0iSBTdiM3cm4NH1zi3jzQf7a1D80kmI29FWNcOaXbh+QYpx0qUr2AJA9UL09ztvJ8patezSlMAUhUn0qIOP4d6ZSlzK2dX3r76rdv2LqCTvGHBcT3+F4QirKpS88RFGOu91MUmK3SPfgzxYv9xUS0Tbdme/ax2n7OHvLidyz+o2L3tVx7bt4QsrqGCzfdbAbGqNykPXGosZbSntArRWzIMamO6VURvTJW0RZjsDfS0i/PNZfKLpEk9W1eKn/lM69dCfg1YvHasRzrgNYqetT3hG/wP9gaU7Y8xbio9dmp95i19vjLu8gx1/HnHo1M0AU/l+jVDdhZv0J9m7XhOw3zgevodanFhubX0zfhiVTzEzhmB3hcreGgGpt2ZntS/w9zkkozCJoAPAmLNYP+HaEgbfEz4lugoBrFMf5xNj5hPwvDYucIrrvx5jbrW2mOem0qj4/xfMPJB8iU3nM6p79du1rci3rIK963/qTULRUwG/F3s1FYCbYcSQouD2r39GkUTjLyv7sX8fBbEXgt6Q1A46VBjuJdfNh7BeGKDjrEYA272qmiAN4oBcdiT3fTtTUqMasyNJ5FTrPL7GyNtSAOUctAhPMze8Qfe+r0CyKrzNqNzGZOag5Rf1x1sb0Ncy8r6KYLqkCwKo5HYk4BqqZOVxouD8NtBUyq7a3hkZ583dwDh93l7pMOpg+paQMduHE7lu1LjFVGdLzUHxcdfpRngfA/OPb9dzDvK/cl/xVTN4Wolio60mH3XIh2nvCF8yVf5IzsTIK0zySrZ0OAG692WFOcBGv9ZjxgHk55XNgzOBpb7NQ01k088Q1qfbZGu0vKcqaEK3fGMjG5RbF3mKh6vPNWGgXaaxe4sfi8+7/Q6DX+TW2g13zkOGz66f7P342Z3jGYlcsZyvQgJQtEh/Vzw9JnIbp0sgfJFnun+PM/xWubK8WueuB0nH8KAaN7iJ2+CaLxZv0OrIjnX0w9hiRjiMRoUp1Vei/NjHTcHPDeI7dVsRsJqO6mZEL/TBOogbyAO+XdrM0A0qzIiyLc04uXTljWROv9nZ9pRq6vNicWr9x/4i5afe/s/FRyyL114tx7W5zMxM01EAxMY6Tqkv0AxmfIu8+gB7Dt5b1WZnHSk4c7K7ZZLLNO+Alzq/E/s4SoDKt4/jIBHOKYBTwoYBH+V50EPLveE2/aQr9Ye3UPDbyuIPP+FnbeXUAaaOmxOS8V9kCsRgIDSIhV86AM0AeviCKlPCZvHX5GnNtGWjCiCCvQwiSGKieRNqn/7BMHWg2zTC+FiOR6rLxxF9QLUx+3h31441wYy+7GZsq9u+cUMVPoBhXIJ1KU357/65MorWvJCz5gff4T41Rn/+X1PkgD80XdD0HjdUfKkOeBkFjNS1MH2u7yl4f6W3lnmpde7rcf08OYNl1u/90C2rwB4eOPIZYVW1n/1k/LI75FN0bDGv95q7jLJB/6WawuUfmEH7ivq9/zKavsH90WGu/OT7jYt8jZ17rWDb0XQSmV8qz/ePACXuDsW2rjS28PS2mcacuiIajLiMwivv8Tfokg4dlVLnfkpAxLfK3aw7vns13KPQzLKggrfZc57II6fPvUoQlppFjCXNOo6lGQlJt8kHM0nGfOaz/pzq4X5TWGsEUKtcqQZjXi318F8czUUBIx4Y+5WEJxFuNiFQUw9xvc49+x278y6hr7GpuSu40XezPf7yEd8fxZwFs/iq00WK4v34f0wxSrO9X2zb7JfPTclYKMVpmvaIKNv57IyBz5cQf/V4Lk+EsRfJLs3ETh636ZdVu2edK/deXTvaCN9I6xY9nxACjw9Oo+IBctP3HGFvaPo6JyCu4mmfdqU8CG+Zs4PuKUlNQIS32ug8Mx6qdrk4b5pmzpAgtZdSTPQr8q/+5XlrCMWxt3Q3el4U1+t8h0D4xxmHfPs9hTZanyoirRzbppvfmf155I5s4Dr5vnnqBEei2q+QbzTwB76ma46j5scHkoK3WZ4n0TTTo3n+fuc44I1KoEo/80mqGDb7b7QWeQX6IXDmEv3Js6Yeewx2+wMKuDABtb98NxyMtqv78yhokiMxkwx0J4f/m6CwoGPgn46cWhmqxUSCI4S1ps1vwxSutf+BJ1OyiptqBaTXmg4vFB+chBnp34ZNXmRATPjNj/3UK0EOf/LcFfrU2Ae/A9jRCf9gZi275DUqyWDCqHtBetfD2lmMbtCeJDti6/xMiw95robFJ10PVp93SyC0QnC99IOqxc2Bw/qNJCVj2VGkBkznjXjmg8yLiJMRDHv0IZpNvU2yfKXO7uBCVE34gIjsU85IxbZfjLMxhyQHV1qHIRfi71t33zm85uVu6SZ9dmxbkUg8YSlUwNpa3ZQ5Lwcbv+lkky0jA6xabIQeLVT84wxBWyjNDiR/dnYZ3LlaDgumxeSM1C/pGD8ZfD0bPe6yc+7XqZVvitJaYwrH2GXmPdyuonEyJFZxZaoM269FG2qabWXspn7ytdMsVV/vfQT9UzAjpdsk6ZBLMMeUhKpdE8uM6iCgqQcbQwtvHTzF9vuyL72JFjuDijM+It7P/tGEVAvqxjiDOWGILxPBdx7O/HQ9zSV6R/UfjRey6asy4MV17M+Un/jYgjinqJTmlgjsS99kqXzDpUdK0TiRFGeG/ic9rRW+yV4592J1dAdV+zv+B2Pb8+hV6PhzdEp2wDyw6A4cyRzmLl7pn7ZR5ADySv21u/AzoVzjGblu1o5qcYbLtNZqiWY7kq7LlA/B5Y7LWPKt/SLnOEOZ/MTlVHb5x54ffpLcijPuYCvrf+OLKz/MBXx9cG+KrYj/Uppq+QVJoB9wOmAad5sFCvYckYdpqwlvFhrUieQ3Q08PTFpgpq83Ep4BPPB8SalBD6+i62v6Pz8/Pk5z1f0U2CA/97MWNATg/2gJ4PmHW9QJSO076UpTWEhF7Jtabu2WjP+TzsCJsbuup4MIlLnKQ7cuqtpdsvPHIRT3bJ3PbqJo888WhKbv+VUik8QvUd//dXAsrMvE5ahrG8fNgo9PKohN1Y/Z+0GsM1BoV5KWnX3IItP6RRfcu/ThjH+G6TlEL2/V4hD/+TNGPV1LYRPstjw4QMSru6EzWk0+FECMayE0iXNbycW9tlvGlT5Rc+MVvNPHAiXhJmTgZvMaI6FmuHZ/IuRF+lUoegBE7GucmYwu0x6s7QZ5KJqpy8DugvMGo9hDRTNXO78c8qQNFOI+jwzey9om7WDzSjeo9DIfAWSEHHwv1Oc+/scc44NAVjnNgO5kb1TiM/tCTn9fn1EEnC6wQcl4JP52gvBewJP+e48j/nRvyy4hunl62Hmbw0bqh1VqE55VoqQY4jBIIpS+NNEKAP5dtDYwxWf/nzeZ8o8GOhj6KU9ZR4gARG2FESqcjDoR5m3sCA+cE6hdifagX7t4g322CDtrRbqCQjWEuopCaEYYE1IhAtlcCxPJZREu184nR+KtSPm/XLvHxSLHYR+Je/2WC2UohlwJbfuhV5NvUeRvYEMMM0q7eOohe2UftWEzE1bH5WU/BYoadqMmy2z495t+ghVaATn/lg/qKdFM/IvGDF/vYrKeeMLiF61nYD26ocm/PfwnqCLlbonnevcirBDJ8QnJ2YDqxliDuK+9TPZf7gbqHYGbF4GdBKiol+sg9QvPc5T+5vAHzqZgTuGWAqBLGa/V7a71yNUKn9clPJa6u4TE2f7Mi7fDTRGG7zLM4y8eNonofl5wOKILGqfFA0bsaeHKQrfQzJRoQLbdxPt8jKDw0Y5r3Pw3Fr/dr1LAaim/UEnk3/wrFSbve9VdPr9MFXyR8umOrldRC6Aibl2Q/vU6zrgTdF+M58eqjciTRWTYbRMB8iGOuwX1J6C4r9yDDRgidfHzlU47qHy5y+FUflm558tYVdFCQWnAfcuPzbguhs8n9bV18+t+zhdHPOxGaub1+JifugQ9HuMEQWt7O9LhmN6tIxiiHj+gVaA9IkJ1dYV1BE3KOEdbM2Z0oUY2bWUxHKo4AHxmkNXSB5+kwQeyH2Kr9ak3Vem2HPSIsmGTxj335TsNkqmN2DwmVW7Xh1DcWTSqwE93mlyD56XY/eK64iACpZ4k+QKE5AJ9C3s3Ol6u2OnZR7cDcdIHFNEJlcClLFhU41Y6bACLUFDJKGDDxxS6zny2GH/QOcP9hOhmqCmSbBi8BoW/06RcLCdjjQI3IOhpRsDfe85gagPoI1JOYIMKiHPZaP8mb/WuOzj3uYKYS8fKZuBC07SqyhqyEkLzLqnriYZgkIfVs7zyp/n2H1qjlyA38tuZTt/eDbvhFzfJI+GecJeV2HR5ZQE2I7V7HeBvqmvWQ4CKT1xDhLKXcDMfr4D69tHKZE65l1v7rcnQiSF9p9r7cN4l0maoLGIzAsM1yr28F4mdl8/dr8r80JGOA8Qvu13YlOQa/afm7TzyALCfPSd32unTH8A+Pp7C5Zb6Jd0Gs+8j3Xma3OngrxTlGcCu+T0rw5AynY6s2FeaewxN5iIjI92m+gClYa82mmJLfMN8VSDKDCZv/IJ/0PkVvHfKZnloNuqvJbFiUhazzN61sLvA1YrrIcuY6OjGMtXNnxxo8+0ZBnsRVxZ5vD9nhokzZ3GlXcojnrofINUGf8oycltqokozr4e2tiVCGmbvWQoTRt1ig2rV2CkNTVaFo/GxA0EGSc+p3HJPPg5bxN1sXHyfGrbjXnX42kb9TcXjvgCwfl0zaoSu+y8m6I2J39oWJtznBzFvXkBnGpI9tn//buQJdPVXcgsuCqWV9AeW64vfM9E4zU5lZ8U9UPqb5Qio7XlB8V4T5pc4l6p18oDEkuipppqPBpRmUoidPZpHNaKrO1qiIxTtpcMut5hxFP2CuIiRcRfD5dU0tsaXvIx1C75wYEJmfCJznSiX3pUSYpdHYg1SCt8HY4FIurP063LgQp3akbc9oNPJskg0hfVj69lnrjhBVfjfTje5hYJYy5RIOkui/e1JFr/rfxQRJs3OGLuyNHJgbFEmLLs87R5J7vRO+GT04aY/8no/luJ3/TsyE0miqALhoPLI74BT66LlPHpvScJwZg2/OjGpLZ0MtNF6ipZFOR2H8ng4vn5B4JWxTpgJF/rDgPX1NX3jf81FLZ4GfctcsKR0A+Yqs+6/0otesSziLMsx5FEK4NJrTnFN32pBZa2dAKkimsxLxASk9OcUN4V2wKuxPoGSj7Bxu/cpKKfoAomWMovnZY9lrectJ1pB2ckHkFjBpdqP1ZzrX99Mgiw8E66r5c85bR5GsjIacYpZCwQO/g89CIoPCv4fVmeG0vPoM62cellvBN+9X4sAO+gNPHIPFfLI96MzpypAh/7mAjcpSIQa3D0Hdma+rf8Sq9e5QTEJfDfYHX22WzMNgxOPdjcHkJ+vrWAx1GLfV3/fYPl91G59m+WLoDAOjfBAYvA+gjucS977UVusPloKTiH+xYgivuP2DZmaCvHDvWbzqeBwSEuMPoeyFA35zpTj0Cngl2pXBvm6DFmmuZS85aiVKTh4L8ercj3v+fNi4DmxvgADdqYhcxXdxKEcuxPBGrPW/HBfZmAlVenF86XlCM5YcjwIPJicMO7cj2K0qLlTAokbD+ytFYnBLWJxCQiEIM5Mz6v9xeZRg6dkIHe161Bxx9Wk3NCJRwgCzy2RafOEYEN4tqIAIxuDqxdKnyoWSUyhALFqdTlJCVVe+lkEV+o0sUU7L5Qhi7EcBy21YH7kIMcMLPKu8MvB83i8WPVVBvyhguNFzutPIndm5n4RknEJ5HuvTHDHhwba+edIzhNqJvXVZJ+/KnpXvw8zKle8F5vdqu8ByzNp1bLd7tuHC2O7FQP/DXvo44SSf0ouEU05gd4fr9ZiDpyIms2p0z72vmjS/O3phf90W5kQOy7wuAHD+lVqnOrH8xuO5lhCcfhlxa925Z+mqYAGb+djae1HYtB73ihS2hLYN6nclmgaHWLZfNo6xQXZ6fTHe1tkLcYJ6ezF84vGN9bF5Jjzgigj5f6OTJdBYUoRBu/heAp166zBLFkWmrljc6jjPcsJausnCtytWrTob27Y1eWo8MNG7MySdBmDtJdaTzC/S+yuSAtqHdN5qg31LFFr/ZVhFnd0ZRn7ixTJ/OwNY/OOu7uibzk6voBfVHevXfD7bBsAhvY/pmhFyICxZOwBWrkSvTL5T8W4jrxADUhM7SeTSykCYwCAPOYl8e0p1cXsnLEJF9/oyz9MBEDBCdes/WPqhN6CGrdckeCbEjczFwHFXLSIw2cf3KXLJsb4WawXF6jUshrg15s
*/
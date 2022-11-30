//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_BIND_DEFAULT_EXECUTOR_HPP
#define BOOST_BEAST_CORE_DETAIL_BIND_DEFAULT_EXECUTOR_HPP

#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/handler_alloc_hook.hpp>
#include <boost/asio/handler_continuation_hook.hpp>
#include <boost/asio/handler_invoke_hook.hpp>
#include <boost/core/empty_value.hpp>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class Handler, class Executor>
class bind_default_executor_wrapper
    : private boost::empty_value<Executor>
{
    Handler h_;

public:
    template<class Handler_>
    bind_default_executor_wrapper(
        Handler_&& h,
        Executor const& ex)
        : boost::empty_value<Executor>(
            boost::empty_init_t{}, ex)
        , h_(std::forward<Handler_>(h))
    {
    }

    template<class... Args>
    void
    operator()(Args&&... args)
    {
        h_(std::forward<Args>(args)...);
    }

    using allocator_type =
        net::associated_allocator_t<Handler>;

    allocator_type
    get_allocator() const noexcept
    {
        return net::get_associated_allocator(h_);
    }

    using executor_type =
        net::associated_executor_t<Handler, Executor>;

    executor_type
    get_executor() const noexcept
    {
        return net::get_associated_executor(
            h_, this->get());
    }

    // The allocation hooks are still defined because they trivially forward to
    // user hooks. Forward here ensures that the user will get a compile error
    // if they build their code with BOOST_ASIO_NO_DEPRECATED.

    friend
    boost::asio::asio_handler_allocate_is_deprecated
    asio_handler_allocate(
        std::size_t size, bind_default_executor_wrapper* p)
    {
        using boost::asio::asio_handler_allocate;
        return asio_handler_allocate(
            size, std::addressof(p->h_));
    }

    friend
    boost::asio::asio_handler_deallocate_is_deprecated
    asio_handler_deallocate(
        void* mem, std::size_t size,
            bind_default_executor_wrapper* p)
    {
        using boost::asio::asio_handler_deallocate;
        return asio_handler_deallocate(mem, size,
            std::addressof(p->h_));
    }

    friend
    bool asio_handler_is_continuation(
        bind_default_executor_wrapper* p)
    {
        using boost::asio::asio_handler_is_continuation;
        return asio_handler_is_continuation(
            std::addressof(p->h_));
    }
};

template<class Executor, class Handler>
auto
bind_default_executor(Executor const& ex, Handler&& h) ->
    bind_default_executor_wrapper<
        typename std::decay<Handler>::type,
        Executor>
{
    return bind_default_executor_wrapper<
        typename std::decay<Handler>::type, 
            Executor>(std::forward<Handler>(h), ex);
}

} // detail
} // beast
} // boost

#endif

/* bind_default_executor.hpp
LA0i+vqH+wcjBERJ80kki2noxkCMj8XytLTx0wUAvrdFx8nU0GyLLvnfD0Z0w9PbMle5Nb+28y/9MPzI4cUlxBtG19I6zxz4Dt88Lvil3nihT240RXS2RLO7nvDAQmLCkoDnGQ3l/l6j/b22LdLhp1KtY2hlfEslGSeriUPh1y623Ds+3LMEsyB9uan2Lrt9eW/zrb0xa21srK+XWF/t1G5rkFgXVpHZHJgc29x/yb/NcVM4UkcBJ4IMx+kZZOR752PMrzoH6hPvu+4gzsMbTpkeWJvrx0gn3b6H/kMppmMyo6Ep4GtJkJh6vH+sEObLFy4zkQMTqycZKoeLOFxrevvokTWq3UgPbmRgQLluHH5TfpkQE94+L0LJJoOLi2QtqiX0hIrG888N+eyf4SF8KiRrAXRO+c08+S6vVMaR9vgu7QnNmJCPG6lVzvJZWhHPLH1OQ9uNJNsfouKMl6/Ck/7Hbwvh69TN6ati83t6FwH7qPtlEvS0WealaTk+TUX7lduYzZyuDbSan3c6L5/VaaQVwAfvOSc2TvSlP0RArSsYMY9RJ/jO4DJmqrQkXpxjUbC7DIsjrMQxuur2WxXMYfmJuqBVFamQqf26HS0nHrFqSWXozMQCmEHQV4wbptXJccXcDiWJnTPNdND7Kf9w8/ZcBFb1UWI/XgTjbl1TlZzCnLlJ6IrBgv+E93d0egqACUic9pdMLdJsPmkQSI0V2O5dTRMdAGDKzekD1esDYQKj2ZAqa0Mzu0nYYoKrKeWE9fuN/lj58PSuvES9fSVkiU4NLn4FfCvCRJXFdGY2hFSmJQY1Jh4EKd0JoMxuj6lOrQ1NBopuDiwMTwqpSj2qmyCiK/+Iqvqqkigpsem5otFiO0lkxYSJrg8Mj6/jFhT1Vs6/rN3kAsqbkJqQEIZ+/tlFePQBJABzv39l3DRaJbe3t7+9lUeIY4iPR0CMv51lVPjN4ZLhEbeQkJKU6RYSY5iUEJAW7WcYmgE4ODgkLF2BPNZAk5c41vAhAv2Dg8SERHtExAcN8YgJ9V+93z43AHm8gLOAEPn5o4Cxs3l5c3k9boB1vixP8r3kCGzHC35HQHhtCn4Toh/Ubnj+ILCg5aBYsAQwo5evyfDvfC/oNm+xeqCvtwehbcCucNd+h6ocks0EsWxyerY/58p4vjwCBNjo1Ct2oF+9L5R9fk+Ufb3vSTu6kRDcrRy1aWUg8PRxqUGpmVHiSbIqSKPDY3RQh3sJSYeBbSh4DnBsiIyQknhqkoqIepB0Dnp6imySbJCKiHK2anp09T+nShzfEdKAVQB5eOnCNZLh0hHgAv1QP+TqgA67lz9RPKDs9JTcN/o8IUmViWEPg9a3RlQG8R+kCkaKbqwOzk6+9pimfL0q98SkxiVviXZvmqc/Nz0hwEyEn2Y7Sqkcp2197yoFvKdeYSF6aOPLYapmvHBlZCTzVa0f52lIZJvzL3mMTBXEyG3tCnTzzXzPUUYbTFlRrEsP8ELNYAu7x9jorx+ZGaTBQvN0d19yHdUseE4IDKqhDShnKjvviFojDxZBBlu8XbeWoh4wDkcHSkAdNI53Hvp03gs4bx196dQbbib7Np6vuW90klk2EEkeBgtPpvUDkyNuL9msGe3eC3zQ0aByUZrwNvayMlvtEK3s/mXeFiPBpb28Zl6JLLVZSiUAdiLJK+L9TSmWZJH63gjUasuV1iuoY9uYIDAGHckgYrNoAkDxm0iSe7o2SmImuOwvbng1eXN3kD8EmG/MU/ehFYER7UsFI9QblS9AyDmDqMjksLmbceHqCOFj6DiIEVe0UDmly/OpZFohublC2Coxb8dkWZRkh7jW2LMKCuR3p9WTd/+8VTYLaSMF4vgHqYN8SY1MuuQm+tFJtdzjTBXaQKM/OXimfIgU+DuRXVvr0OyM25pArqaAN3y14wtS6N6vxNpqqlQUVLn4akCC5kVcoaC/FG3P8y0mRxsGCSb+yfXahJ4OS+wuxURSxXTBdK0mw8FZQ1AtL94JJOdCuyJ123kZri3papZpEh2YsMDtOCs1sD4SuyOOYEl6D9TIzwBLpAik4hctffd2CkqGuwprJPTp6278iI+8Ou07ACR8p5XgFcSt7Z9MHvbJQRl/YB4RgDb8RDsmAHF+B/Gjsjo0upvjRQV2tLQ00AWFV8ZEdAdyDel2pAsqZXJ08EtsPfrr9Gq0BBMPAVnjVGsYTxK2mBxcD5JMFZjv/wFsb9/ZvAuyqG8o47bgWOdJg6a8hUd7UVi/gd37wne81Knq4sflZr+p/ZudnSoq2z809Rdl9E3657N/Ah9IwZcDxv+Nfvv6Jzz2Zy/HAkBqFmCUGQBryI3vVc179PML4l3+G/WdEYUGB0ZE7AHl9nSOuEycwb53LA9PcLCvgFdshAS440+cckNEmvGP/T/4mj1EgP3IXtuA19pIMVdUmgtNrqnUMhkTsB1mVNRrmO198e0T2Y32bUfKaCulEtbMaXGQkma/140ikOWvSAiq7y1USx2jO4s0TvU/X0BhOlR4XBHIl2Jv3yDzudWCdxa2VnP8k2dXylobiwKiFs+cPCdfju4+h8sgZITIYOTl0Le41qwztt022xd42yaP8O1mywrfLeq5d0uPZU0Dgy2R+cdWSZHn/07QNrqdt5jWvjJdXJ6WpdE+S2inlB5N8ycoaVIEVLJ5BQ/0U+mEau3Y6qXnL2qgkXQkap96yM5T3KcvS6icQW84mstX0egxklftCzs7uH7WjWL3sUZwdOjpYArgqSKumFxb0cCOwGpV29/SqGBuXipSzpf522nPdl5XX/2NSVtJzsHUU3jedlpfVV6TTbkY6+suZykw/UAdS/VFL+fIAkDgEpBjWpChdjy6Pbi9N67iKTZy9jg5+hypmBkn+IvqUM3XWQRMWAbs6iOcpqwZFzEea6HJAcZ2quK+205fe63AL/3MwH9+lH1GHR/kO+BhgZ8gng08pGAVfSgwKDDCLT6p/EBAYYNMAyPkhmsCAY2dxkJR3xqP9bf4Pj+W5I5nmbKk12rfxtbC6mkElY5BzVjkLVedLKvcFlAHhp0teVGgO6qsTsj+uV2RDuY0/DDJuXy2uAiNmYc5Wt5IL7nqhLNrYRpffPLVQP5Nw7w92KD1mQPttr4/TLPAq/iCE5CjKax8lLprH1lhYBQWEZ5INjNmYSQ9qVuaDTdGSaUqcNAMA0jeyBAQ6gUQwWVnZcqqXH1zZ62axzgKK2R1bkH43QvrqwNOLxTQy7VylFlmt7erYbTO1f3N17kPMkLEBpspykmixn2YLRLMq83SRsIaPCrSRJSqXfMq/FfCaTMgAJUEKN0FCh3/ub3sphp9D422vgwNypT6eQvRNsXJSzWwQcmbyTEVA4Pja6lfThyuCFn+3bFK9fnllb7Y3/Bw6CU47EolRRNa0cGT8fzUIabiOKbKDJ9TGHefG1+fmx7RG4kZ1EfoqPwvvTBiNPmvPcIp12DoKMGP9sTLDFpGciYOJjq91wq+EHNFL3WYxtXWYMJG7MXun2QLW/aHeYaIgbqQq6Y0ABzT+sJnt1DAT3wmGDjXlh/e0ICXPxgKfp4oXr9FGx5+SBn8ddpPlfe9izTrb0xERXZI58cWPhHhUqqBVcJ+se3i/twNsiUa9JdnQmbkzSROJjYMx7V9MkvFEsK7v/xFOVegRR8LHvt3VHVllsPJqy+spO/bMYVfvShfJmaCvk4t3137EQjqiC6/anPrAgxgdycreJRof2GWCuAsBzOzuxvQShBURgcGjtPntb6sd/qG3o2WD8i4dexIFmvZzfeYcZ5Ie2VnzHkbHQV4doHDmXSI8MdItbMC3L49SB6Y5hdPA9ltQiDzb9xuKjT9fdq8EKRmA5tKKWzn5qTeL1eSvfn6+MzA6IxQApSPO9ex8/n+exO0JES6eyfac5bLcqM4uYT7NUds71cqaf2jrEwD//FTQ4kG8CUu6wkC6h8Q4qtAuh5G+YwIQ3OZqwoJpiuKGiQzNASaiDM6DPfxqU+2BoLPWnqJjBlAFaZMiJ+xImNDv/C3hganeIQ5GHPi4441uLEBlCqR3gdzyS68X0Oom3MLakMFMZ0MAWu7iQG820okS1T29oylmT4k77O8yG7ctcht3PXVds8aJnRXWdhSfx7tCXu1eUATjSaf7spQOvuVytoze+XY5JiuIhfOxOvd6kpfxbYeQKr2kOv0RrW33RtTXql3Zcue8hVzfmXPgsonPqpSeVZUGalRFCN5zTVNAaG4M7uZL3m834/rGYma5dHD3Py0EknFJcLILYvSjm/XhTSrrG7YTA6hlr1hzp+wadnB0V5sLVLnGj7JYzfJyoaWltbmd5JFVEbEfGFgY2e2SSiAlvotShw8uN7YQs8lclejn2uFJDWrIPXUOBbwF3RhhGxiuVzPAXHnluDApHndTZwVWlm78cg+3BFDZU5fqKoUFpHTw0jxptmXFjyCwT1GVhbe4zQ0xjvINjU3OzQ3u8xqJwwksI0PUZdPAukUt6abhP/5GEN+UONvag/nIXB4maHm4SQdfyD8Z9jy+DYq2hKhw7nTcFG3qCdnSYFEwc4x00tz3WTiF6LDIjOaLD10QNBDZSqtGK4zlDWcPFjKg99CbBoVKZB3STXWJT0hHXAQQHlX5CUJpM76cBMd/uU3Gr7q4f/jFQ2BflvbyLh7V4jfyHimHO7yxYT74xHwXScQIfzTeKaj09T6rZPTl5fJIIbnjoKgdol4BFIkai6LAF0dDFqzqr8Nl4tQDVpUfHU1lJW1E5m9o/Fkq9f1Flnfa2BCcuPjuPP3KPYPySIesVvqxMoTrr/LSX9C+Ypy3FlncXb7sl68X8MJL+edqh/8wXL2jL9BJP2Nmc3W0uDJn62i9e0aQvwFTmr+iHtnsouJJAxXEt7h2mUX1rcjEoy+qRdohZ6Qc/jGc2iPCgKAS9uO88EkwJl3LIA+yru4UIQyv1I0nB/lj0Zrnh+vRSBsgKfazuLYve+p6fNcFAOWZuWH1m9voTfEhr/MNDme7iVEsv7sYJ9bCJ/vyN+d2yef4t21f/avbQUrwElA+S7pvxPr4xxZ794yt2r5YcDBX/xw4G48mI10Vv+gmHF9trbsYi35wl3eDwXcuQPw8OJNnYRoONsAN/J5FLg8gDAohafZWhnVa2bY7lo52/vrkFSKH4I8kMseaFmJOgcO5exP0Xo212ec70/hzcHLJCJCzHCXyAeBWduUM9TDW0pXjOT2L2g31CP3y8fGaLMJOOS3U8wfLKzaxU9IVJ1092FUKHNMFFYk53ZJUTItrzQ1M8bdsaFBzqD8GYk0pnDEMc0z46QRUmWf9j0zZGS3BoLelJyfs043rs7L2t/HPKQfz0+EEwRAysM/1tq7RL4gGe+bVgl5eRrDC/gAe95e5TOIepsvH8iAAADh28P5voBw+Hr5QmPEdGDFZ3eDDgvDNZXgIlV3glbHFqdWAoTTo4Ojk6ODtIWj07OFs9VTUyNEU4WmxpbA5UOgRCBKPjQ82PferfTg4N7Q5uCBoaiMmxXOP5dTYtqHIpvuvVr5XA3wWN1yaHbwXTUC/15NeJfVJNDEQ+KhQNrYuVoFaP9pkBwfHvvQZ5OENUS17tSIF3KjglATAXOTyT5QRjkT4jLcGZHyr4Lezboq5zi6WvHoiwJln0BlEeWd5DovEq6Ve6j6m+FdRazIpaaVkIZnt1KOsHD7ERJbY0oIT0R10YOiV9gkWfLB82Ha3rH+yYYreIVd4PPoX+p2YlK+7Iqbcxch5bPS/02UgwKOklkS2hWhZC9Who/1rzDNMmyzIHLakuqQqWDAlmmyDdkJcWsWBOZRTe3UsmWzgOYni0jns3GcrTgh8nAy1tLWxjTxDO2zpkCKiiWKWok2lyE8gjF8LvVggAR6TOfdAnIi2MiKbjKE6TRjna4Ub2b07gq0nDwTuhZjiiRHpj5N/RXhR5X0uw6U/L5u4fj35WxyZIh41/T+r4Cj3Z/GkGyavzoSe/TJSXw6OykiO+Yhv7B6U4LTF+bv6WALOzI6+gk8IiU2NfVF7ACMrwQhsVH/84XVLfhw7FaH3xwfphuyFzYzoji1F7SS2qjK3tcDLUaRAhpruJJlwv3tZw1srxV81PMMmCOQx08ecZefj+TE1Pj4RyJAwj2QByHoj1k2p3nIw0hcxq7FWpecX+vg01l8eoZ3siErUPqdzpMr9SSyu84HnNFHs7ix5Lm8a8GmqA/+HKpCwhHvg88/Rrn3yVQYX3KqkbO4IHhS58qfQ9ejfbI/yH+TO4dnYndqQ7tL2odvQhrKWLxcwpm1+8yBeVAjAhQA5kN7sx6nclQWc7JNqKZQhl8r/Ha0CVv7KtFtB6QfOA7SzQ/4MoXzRyegvWmfxuoVtE8PFdNdhk9ax+auhsK6J1T2WwNyzKy4snOw5YyPN2wJmyq7JDM19LXlT5aFiUABzeq0Z0gQBb0MCeMvjaXxBlvplwQ+u1RJDjBub2ktwT5ZLYTBvq2Ng3oKVtzUM0MmlwW+REN6QIoA+TsDaKuh8OPBuhyCyNkmWojgALNhu586CZ9HT2u46+vwJMNHJkRUKQsxiBf38yCuakkdJK+zzIO8gNXke+FcvGTSd67ZYV+trW/J6m+eaa/xeofciuUn+0/PLMYGCaDDIoKanLhjV8TEBJD3MBolAvYd+CkTWYStUyhgqv8hYUaCdGU2k5jQ2Cfs/CyniRLkhxw1/sny+GTpXKqba1xpZA4H91I5wcsHBGMT05+IolJCLeFPTpqdQ8C5LLewtySwu93WmbAE4bB/d25pJhyAe6be1hmUVi9918ZoNsM6K5MAUVMNLOHjGL1OHfCu0IVYdlTxylbjoyVuFtQQ2Jg/zTfIaz7Mz69FbRTvZTCiS+sw+2j/6ya+zA5XV2hsOR1UqoIQm1fhvxPWuncDtfPqqPgdh9Rt66957TPuZbGAO3x8uO/w6iBjVl2TDufb11RUowbe/91eATyo1SGzjqPbpid6i5bHFzlswjWloyBOD2HG9HDpEGBv1s26aP6S6lzmnjin2xTX0xkjMJMwq6j0l2CB5ZxljOiExEwOec2+ZUUejIJ21mZ8AWpe5NiiGqPF8IodlA10WNRZ6vHf22mzeTsjVWVyzYB86VeLQSeUg6swZaNAMUF7+Gj1KG264g3jTRtCv3wg3LwuZObX4eythnbHK9LUDQBjOOS8/QFjRP3acTRlQUp9jMecRcJg3RcYESpLsU+1xx5QAeYhTf0RNtjSn5+RhR1Ej9z+9ed/PCZ6BohkqC26YRvR+1BJcDjnihwl1wKgWawi8UOmPdxQfHLuf+AFVlPwAeVmyIOSa20gCDgnCTircGyN7BYKtm2tTXLB8ImH3/nibVr1wjYkWnqnOqr/EkWwVzhKthXLB6P4V1XkeV8Bjp2qgFMmRgmkNWwZZ79LBbhSxnP9XcGxfGb77mRpX8hS/vNBm3qJXjBEODOUb7qeFJUX33mAvS6jYmKagOMzQ+Mzg+NAOHfrAyERehMV/LExYfOH5Bl1fjiGItHsOLKVF/qlNX7jj8RlZn6MkxLZizKh/hiiXWcAND2xyan++itAQdRHhZBvoQxdFikeBZ4vdqAv60tHbAjbtMQ/GoWqHzaub6iM86I6HIjxZ/6Z
*/